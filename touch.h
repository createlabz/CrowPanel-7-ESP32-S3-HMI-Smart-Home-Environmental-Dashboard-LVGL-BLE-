#pragma once

#include <Wire.h>
#include <TAMC_GT911.h>

#define TOUCH_SDA 19
#define TOUCH_SCL 20
#define TOUCH_INT 38
#define TOUCH_RST -1   // important

extern TAMC_GT911 ts;

void touch_init();