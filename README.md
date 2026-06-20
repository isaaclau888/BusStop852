# BusStop852
<img width="1920" height="1080" alt="BusStop852_2026-Jun-12_03-25-09PM-000_CustomizedView46320833250_png" src="https://github.com/user-attachments/assets/3e0790ea-186b-4de9-9126-10159c797cc0" />

As a student who always goes to school by bus, I have to check my phone when I go downstairs to catch the bus. I got some inspiration from Threads; some people have made this kind of display board already. MTR, HK Bus and Flight Display Boards already exist, using the same display that I'm using: ESP32 Cheap Yellow Display(CYD).
I want to build one by myself, so I created one :D

## What's it for?
It's for Hongkongers to check when they should go downstairs to catch the bus. Without opening the APP1933 - KMB . LWB app or other kinds of Apps like Wheels made by Anson Chung @anscg (https://github.com/WheelsTransit), you can easily look at the display and check.

## How to build it?
Please print all the 3D parts. <p>
<img width="579" height="545" alt="螢幕截圖 2026-06-16 下午1 37 14" src="https://github.com/user-attachments/assets/8b120550-36af-4ace-8297-a887d58a8e39" />

# 3D Parts Assembly
First, place the round bottom part. <p>
<img width="247" height="149" alt="螢幕截圖 2026-06-16 下午1 41 08" src="https://github.com/user-attachments/assets/8892fdaa-03ee-482a-a54f-ec845ce3795c" />

Secondly, screw the round bottom part onto the pole. <p>
<img width="250" height="343" alt="螢幕截圖 2026-06-16 下午1 41 58" src="https://github.com/user-attachments/assets/b5722bb4-861a-48e7-b4e6-c89deff53667" />

Thirdly, screw the upper part of the pole to the middle part. <p>
<img width="220" height="400" alt="螢幕截圖 2026-06-16 下午1 42 49" src="https://github.com/user-attachments/assets/e902be1a-e796-410f-93a8-b638db9327db" />

Last but not least, screw the top part into the middle part. <p>
<img width="255" height="548" alt="螢幕截圖 2026-06-16 下午1 44 09" src="https://github.com/user-attachments/assets/f44093df-22d4-4ecf-b3ef-8509297f35d1" />

# Screen Assembly
For the screen, just place it in the middle and use the 3D screws to screw it in. <p>
<img width="423" height="449" alt="螢幕截圖 2026-06-16 下午1 46 05" src="https://github.com/user-attachments/assets/4312ef96-6104-409c-8328-abca6e19e7bc" />

## How can you use it?
1. Please install Arduino IDE from the official Arduino website.
2. Install ESP32 Board in Arduino IDE:
Open Arduino IDE and go to File > Preferences.
In the Additional Boards Manager URLs field, add the following URL:
https://dl.espressif.com/dl/package_esp32_index.json
Go to Tools > Board > Boards Manager, search for "ESP32", and click Install.
4. Open Library Manager(A stack of books on the left sidebar)
Search and install lvgl, GFX Library for Arduino and ArduinoJson.
5. Select Your Board and Port:
After installing, select the ESP32-WROOM-32 board: Tools > Board > ESP32 Dev Module
Select the correct Port under Tools > Port.
5. Upload Code:
Write or load BusStop852_App in the Arduino IDE. Please download the whole BusStop852_App folder. 
Click the Upload button. After a few seconds, your code will be uploaded to the board.
6. And now you can use it, yay!!!

## Why did I make it?
I decided to make this because I want to make my life more convenient lol. Without looking at my phone, I can see when the bus comes to my bus station.

## How do you really use it?
<img width="725" height="137" alt="螢幕截圖 2026-06-15 下午6 56 58" src="https://github.com/user-attachments/assets/0d286a66-086e-4468-bc23-026d82d0c428" /> <p>
So on the main screen, you can see there are bus numbers; it shows the ETA time. <p>
If you click on one of them, it will show the timeline for when you will arrive. <p>
If you click the WiFi: Connected or SIG: -65dB, it will bring you to the System Monitor Page. <p>
And clicking on the time, it will bring you to the Departure Alarm Page. <p>

But you need to edit the .ino file first; you need to enter your WiFi Name and Password. Then edit the Target Route, Stop ID, and Direction.

## How I made it?
I used Fusion 360 to make the body and screws, Arduino IDE for the coding part, SquareLine Studio for the UIs and last but not least, the ESP32 Cheap Yellow Display (CYD).

# Fallout Zine 
<img width="4405" height="6250" alt="BusStop852 Fallout Zine" src="https://github.com/user-attachments/assets/3165a23a-7270-4959-804f-9a6dea69d4cb" />
