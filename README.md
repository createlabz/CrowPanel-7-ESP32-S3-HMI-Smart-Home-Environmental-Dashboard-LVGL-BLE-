🌍 CrowPanel 7" ESP32-S3 HMI Environmental Monitor
LVGL Touchscreen Dashboard + BLE + Real-Time Charts

An Environmental Monitoring Dashboard built for the CrowPanel 7.0" ESP32-S3 HMI Display (800×480 RGB) using LVGL, LovyanGFX, and BLE communication.

This project demonstrates how to build a fully customizable smart touchscreen dashboard capable of monitoring environmental data with interactive charts, gauges, BLE communication, and configurable alerts.

📦 Project Repository

GitHub Repository

https://github.com/createlabz/CrowPanel-7-ESP32-S3-HMI-Smart-Home-Environmental-Dashboard-LVGL-BLE-

🖥 Project Preview

The dashboard includes:

✔ Temperature Gauge
✔ Humidity Gauge
✔ Temperature Trend Chart
✔ Humidity Trend Chart
✔ BLE streaming status
✔ Touchscreen threshold configuration
✔ Hardware LED alerts

The interface is built using LVGL widgets, which means the entire UI can be customized easily.

You can modify:

charts

gauges

widgets

colors

layout

sensor displays

smart home controls

✨ Features

🚀 LVGL GUI on 7" RGB display
🖐 GT911 capacitive touchscreen support
🌡 Temperature monitoring (DHT11)
💧 Humidity monitoring (DHT11)
📊 Temperature trend chart
📊 Humidity trend chart
📱 BLE command interface
🎛 Configurable alert thresholds from touchscreen
💡 Hardware LED alert indicators
⚡ PSRAM optimized display buffering
🔧 Fully customizable LVGL dashboard

🧰 Hardware Used
Component	Description
CrowPanel 7" ESP32-S3 HMI Display	800×480 RGB Touchscreen
SKU	DIS08070H
DHT11 Sensor	Temperature & Humidity
LEDs	Alert Indicators
Resistors	220Ω
💻 Software Versions (Tested)
Software	Version
Arduino IDE	2.3.7
ESP32 Board Package	2.0.15
LVGL	8.3.11
LovyanGFX	1.2.19

These versions are confirmed working together without compatibility issues.

📚 Required Libraries
LVGL

Custom LVGL copy used in this project:

https://github.com/createlabz/lvgl

Version used:

LVGL 8.3.11
LovyanGFX

Display driver for ESP32 RGB displays.

LovyanGFX 1.2.19
GT911 Touch Driver

Touch controller driver used for the CrowPanel.

https://github.com/TAMCTec/gt911-arduino

📂 Repository Structure

This repository already includes the required configuration files so you do not need to manually configure the display or touchscreen.

CrowPanel-7-ESP32-S3-HMI-Smart-Home-Environmental-Dashboard-LVGL-BLE
│
├── EnvironmentalDashboard.ino
├── gfx_conf.h
├── touch.h
├── touch.cpp
└── README.md

These files contain:

✔ RGB display configuration
✔ LVGL display driver setup
✔ Touchscreen initialization
✔ LVGL touch input integration

⚙ Arduino Board Configuration

Select board:

ESP32S3 Dev Module

Configure Tools → Settings exactly like this:

Setting	Value
USB CDC On Boot	Enabled
CPU Frequency	240MHz
Core Debug Level	None
USB DFU On Boot	Disabled
Erase All Flash	Disabled
Events Run On	Core 1
Flash Mode	QIO 80MHz
Flash Size	4MB
JTAG Adapter	Disabled
Arduino Runs On	Core 1
USB Firmware MSC	Disabled
Partition Scheme	Huge APP (3MB No OTA / 1MB SPIFFS)
PSRAM	OPI PSRAM
Upload Mode	USB-OTG CDC
Upload Speed	921600
USB Mode	Hardware CDC and JTAG
🔌 Wiring Diagram
DHT11 Sensor
DHT11 Pin	CrowPanel Pin
VCC	3.3V
GND	GND
DATA	IO38
🌡 Temperature Alert LED
LED	CrowPanel Pin
Anode	IO43
Cathode	GND

Wiring

IO43 → 220Ω → LED → GND

LED turns ON when temperature exceeds threshold.

💧 Humidity Alert LED
LED	CrowPanel Pin
Anode	IO44
Cathode	GND

Wiring

IO44 → 220Ω → LED → GND

LED turns ON when humidity exceeds threshold.

📍 CrowPanel Pin Map Used
Function	GPIO
DHT11 Sensor	IO38
Temperature LED	IO43
Humidity LED	IO44
LCD Backlight	IO2
Touch SDA	IO19
Touch SCL	IO20
📊 LVGL Dashboard

The interface includes:

✔ Temperature Gauge
✔ Humidity Gauge
✔ Temperature Trend Chart
✔ Humidity Trend Chart
✔ Alert Threshold Inputs
✔ BLE Streaming Status

Example threshold values:

Temperature Alert: 30°C
Humidity Alert: 75%

Users can change these values directly from the touchscreen.

🎨 Customizing the Dashboard UI

The UI is based on the LVGL Widgets Demo.

To customize the dashboard layout, edit the file:

lv_demo_widgets.c

Working path used for this project:

C:\Users\dev\Documents\Arduino\libraries\lvgl\src\demos\widgets

Inside this folder you can modify:

UI layout

charts

gauges

widgets

colors

animations

sensor displays

This makes it easy to turn this project into a smart home dashboard or IoT control panel.

📡 BLE Features

The ESP32 operates as a BLE device.

Device name

CrowPanel-HMI

Tested with

Serial Bluetooth Terminal
📡 BLE Commands
Command	Function
ON	Turn display backlight ON
OFF	Turn display backlight OFF
READ	Start streaming sensor data
STOP	Stop streaming sensor data
📤 BLE Data Output

When READ is sent, sensor data streams every 2 seconds.

Example output

TEMP: 27.5 C
HUM: 65.0 %
🚨 Alert Logic

Temperature Alert

if temperature >= threshold
    Temperature LED ON

Humidity Alert

if humidity >= threshold
    Humidity LED ON

Threshold values are adjustable from the touchscreen UI.

⚡ LVGL Memory Optimization

RGB displays require large buffers.

LVGL buffers are allocated in PSRAM.

Example buffer size used

800 x 80

This ensures stable LVGL performance on ESP32-S3.

🧠 System Architecture
DHT11 Sensor
      │
      │
ESP32-S3 MCU
      │
      ├── LVGL Graphics Engine
      ├── LovyanGFX RGB Driver
      ├── GT911 Touch Controller
      └── BLE Communication
            │
        Smartphone App
🚧 Future Improvements

Possible upgrades:

WiFi MQTT sensor publishing

SD card data logging

Home Assistant integration

LVGL popup alerts

OTA firmware updates

additional sensors (CO2, soil moisture, light)

🙏 Credits

Libraries used

LVGL
https://lvgl.io

LovyanGFX
https://github.com/lovyan03/LovyanGFX

GT911 Touch Driver
https://github.com/TAMCTec/gt911-arduino

📜 License

Open source project.

Free to modify and reuse.

⭐ If you find this project useful, consider starring the repository.