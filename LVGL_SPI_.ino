#define LV_CONF_INCLUDE_SIMPLE

#include <lvgl.h>
#include "gfx_conf.h"
#include "touch.h"
#include "esp_heap_caps.h"
#include <DHT.h>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

extern "C" {
#include <demos/widgets/lv_demo_widgets.h>
}

LGFX lcd;

#define BACKLIGHT_PIN 2

/* DHT11 */
#define DHTPIN 38
#define DHTTYPE DHT11

#define TEMP_LED_PIN 43
#define HUM_LED_PIN 44

DHT dht(DHTPIN, DHTTYPE);

/* BLE */
BLECharacteristic *pTxCharacteristic;
bool deviceConnected = false;
bool streamData = false;

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

/* Required by lv_demo_widgets */
float g_temperature = 25.0;
float g_humidity = 60.0;

float temp_alert_threshold = 30.0;
float hum_alert_threshold = 70.0;

/* LVGL draw buffer */
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *buf1;
static lv_color_t *buf2;


/* DISPLAY FLUSH */

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = area->x2 - area->x1 + 1;
  uint32_t h = area->y2 - area->y1 + 1;

  lcd.startWrite();
  lcd.setAddrWindow(area->x1, area->y1, w, h);
  lcd.writePixels((lgfx::rgb565_t*)color_p, w * h);
  lcd.endWrite();

  lv_disp_flush_ready(disp);
}


/* TOUCH READ */

void my_touch_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  ts.read();

  if (ts.isTouched)
  {
    data->state = LV_INDEV_STATE_PR;
    data->point.x = ts.points[0].x;
    data->point.y = ts.points[0].y;
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
}


/* BLE CONNECTION CALLBACK */

class MyServerCallbacks: public BLEServerCallbacks {

  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  }

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
    streamData = false;
    pServer->getAdvertising()->start();
  }
};


/* BLE COMMAND HANDLER */

class MyCallbacks: public BLECharacteristicCallbacks {

  void onWrite(BLECharacteristic *pCharacteristic)
  {
    String rx = pCharacteristic->getValue().c_str();

    rx.trim();
    rx.toUpperCase();

    if(rx == "ON")
    {
      digitalWrite(BACKLIGHT_PIN, HIGH);
      Serial.println("Screen ON");
    }

    if(rx == "OFF")
    {
      digitalWrite(BACKLIGHT_PIN, LOW);
      Serial.println("Screen OFF");
    }

    if(rx == "READ")
    {
      streamData = true;
      Serial.println("Start streaming sensor data");
    }

    if(rx == "STOP")
    {
      streamData = false;
      Serial.println("Stop streaming sensor data");
    }
  }
};


/* SETUP */

void setup()
{
  Serial.begin(115200);

  lcd.begin();

  pinMode(BACKLIGHT_PIN, OUTPUT);
  digitalWrite(BACKLIGHT_PIN, HIGH);

  pinMode(TEMP_LED_PIN, OUTPUT);
  pinMode(HUM_LED_PIN, OUTPUT);

  digitalWrite(TEMP_LED_PIN, LOW);
  digitalWrite(HUM_LED_PIN, LOW);

  lv_init();

  touch_init();

  dht.begin();

  /* BLE INIT */

  BLEDevice::init("CrowPanel-HMI");

  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_RX,
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pRxCharacteristic->setCallbacks(new MyCallbacks());

  pTxCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_TX,
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  pTxCharacteristic->addDescriptor(new BLE2902());

  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->start();

  Serial.println("BLE Ready");

  /* LVGL BUFFER */

  buf1 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * 800 * 80, MALLOC_CAP_SPIRAM);
  buf2 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * 800 * 80, MALLOC_CAP_SPIRAM);

  if (!buf1 || !buf2)
  {
    Serial.println("PSRAM buffer allocation failed!");
    while(1);
  }

  lv_disp_draw_buf_init(&draw_buf, buf1, buf2, 800 * 80);

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);

  disp_drv.hor_res = 800;
  disp_drv.ver_res = 480;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;

  lv_disp_drv_register(&disp_drv);

  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);

  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touch_read;

  lv_indev_drv_register(&indev_drv);

  lv_demo_widgets();
}


/* LOOP */

void loop()
{
  static unsigned long lastRead = 0;

  if (millis() - lastRead > 2000)
  {
    lastRead = millis();

    float t = dht.readTemperature();
    float h = dht.readHumidity();

    if (!isnan(t) && !isnan(h))
    {
      g_temperature = t;
      g_humidity = h;

      /* TEMPERATURE ALERT LED */

      if(g_temperature >= temp_alert_threshold)
        digitalWrite(TEMP_LED_PIN, HIGH);
      else
        digitalWrite(TEMP_LED_PIN, LOW);

      /* HUMIDITY ALERT LED */

      if(g_humidity >= hum_alert_threshold)
        digitalWrite(HUM_LED_PIN, HIGH);
      else
        digitalWrite(HUM_LED_PIN, LOW);

      /* BLE STREAM */

      if(deviceConnected && streamData)
      {
        char msg[64];

        sprintf(msg,"TEMP: %.1f C\nHUM: %.1f %%\n",
                g_temperature,
                g_humidity);

        pTxCharacteristic->setValue((uint8_t*)msg, strlen(msg));
        pTxCharacteristic->notify();
      }
    }
  }

  lv_timer_handler();
  lv_tick_inc(5);
  delay(5);
}