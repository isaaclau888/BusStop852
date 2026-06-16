#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Arduino_GFX_Library.h>
#include <Wire.h>
#include "src/BusStop_852_UIs/ui.h"

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

#define RGB_PANEL_BACKLIGHT_PIN 2
#define TOUCH_I2C_SDA_PIN 19
#define TOUCH_I2C_SCL_PIN 20
#define TOUCH_I2C_INT_PIN 18
#define TOUCH_I2C_RST_PIN 38
#define TOUCH_I2C_ADDRESS 0x5D

unsigned long lastExecutionTime = 0;
const unsigned long apiInterval = 30000;

Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
    45, 4, 5, 21, 39, 40, 41, 42, 2, 0, 9, 14, 47, 48, 3, 6, 7, 15, 16, 8,
    1, 1, 43, 8, 1, 1, 12, 8, 1 , 16000000, true, 0, 1, 1 
);
Arduino_RGB_Display *gfx = new Arduino_RGB_Display(800, 480, rgbpanel, 0, true);

int16_t touchX = 0; int16_t touchY = 0; bool touchPressed = false;

void update_bus_eta_data() {
    if (WiFi.status() != WL_CONNECTED) return;

    HTTPClient http;
    String url = "https://rt.data.gov.hk/v1.1/transport/citybus-nwfb/eta/CTB/002517/20X";

    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode == 200) {
        String payload = http.getString();

        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, payload);

        if (!error) {
            const char* next_bus_eta = doc["data"][0]["eta"];

            if (next_bus_eta != nullptr) {
                String eta_string = String(next_bus_eta);
                String display_time = eta_string.substring(11, 16);

                Serial.print("Next Live Bus Arrival Target Locked: ");
                Serial.println(display_time);

                lv_label_set_text(ui_FooterWifiLabel, display_time.c_str());
            }
        }
    } else {
        Serial.print("API Server Connection Interrupted. Code: ");
        Serial.println(httpResponseCode);
    }
    http.end();
}

void read_touch_hardware() {
    Wire.beginTransmission(TOUCH_I2C_ADDRESS);
    Wire.write(0x81); Wire.write(0x4E);
    if (Wire.endTransmission() != 0) return;
    Wire.requestFrom(TOUCH_I2C_ADDRESS, 1);
    if (!Wire.available()) return;
    uint8_t status = Wire.read();

    if ((status & 0x80) && ((status & 0x0F) > 0)) {
        uint8_t buffer [6];
        Wire.beginTransmission(TOUCH_I2C_ADDRESS);
        Wire.write(0x81); Wire.write(0x50);
        Wire.endTransmission();
        Wire.requestFrom(TOUCH_I2C_ADDRESS, 6);
        for(int i = 0; i < 6 && Wire.available(); i++) buffer[i] = Wire.read();
        touchX = ((int16_t)buffer[3] << 8) | buffer[2];
        touchY = ((int16_t)buffer[5] << 8) | buffer[4];
        touchPressed = true;
    } else {
        touchPressed = false;
    }
    Wire.beginTransmission(TOUCH_I2C_ADDRESS);
    Wire.write(0x81); Wire.write(0x4E); Wire.write(0x00); Wire.endTransmission();
}

void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
    uint32_t w = lv_area_get_width(area);
    uint32_t h = lv_area_get_height(area);
    gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)px_map, w, h);
    lv_display_flush_ready(disp);
}

void my_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data) {
    read_touch_hardware();
    if (touchPressed) {
        data->state = LV_INDEV_STATE_PRESSED;
        data->point.x = touchX; data->point.y = touchY;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(RGB_PANEL_BACKLIGHT_PIN, OUTPUT);
    digitalWrite(RGB_PANEL_BACKLIGHT_PIN, HIGH);

    gfx->begin();
    gfx->fillScreen(0x0000); 

    pinMode(TOUCH_I2C_RST_PIN, OUTPUT);
    digitalWrite(TOUCH_I2C_RST_PIN, LOW); delay(10);
    digitalWrite(TOUCH_I2C_RST_PIN, HIGH); delay(10);
    Wire.begin(TOUCH_I2C_SDA_PIN, TOUCH_I2C_SCL_PIN, 400000U);

    lv_init();

    lv_display_t *disp = lv_display_create(800, 480);
    lv_display_set_flush_cb(disp, my_disp_flush);
    static uint8_t buf1[800 * 40 * 2]; 
    lv_display_set_buffers(disp, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);

    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, my_touchpad_read);

    Serial.println("Connecting to Network... ");
    WiFi.begin(ssid, password);
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 15) { delay(500); Serial.print("."); attempts++; }

    ui_init();

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConnected! Syncing Live Timetable Records...");
        update_bus_eta_data();
    }
}

void loop() {
    lv_timer_handler(); 

    unsigned long currentMillis = millis();
    if (currentMillis - lastExecutionTime >= apiInterval) {
        lastExecutionTime = currentMillis;
        update_bus_eta_data();
    }
    delay(5); 
}