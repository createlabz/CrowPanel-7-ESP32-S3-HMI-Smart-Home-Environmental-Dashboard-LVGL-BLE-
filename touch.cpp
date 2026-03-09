#include "touch.h"

TAMC_GT911 ts = TAMC_GT911(TOUCH_SDA, TOUCH_SCL, TOUCH_INT, TOUCH_RST, 800, 480);

void touch_init()
{
   Wire.begin(TOUCH_SDA, TOUCH_SCL, 100000);

    ts.begin();
    ts.setRotation(1);   // try 0–3 if touch direction is wrong
}