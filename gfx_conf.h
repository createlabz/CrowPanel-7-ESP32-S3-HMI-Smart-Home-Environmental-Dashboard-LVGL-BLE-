#pragma once

#include <LovyanGFX.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>

class LGFX : public lgfx::LGFX_Device
{
  lgfx::Bus_RGB _bus;
  lgfx::Panel_RGB _panel;

public:

  LGFX(void)
  {
    { 
      auto cfg = _bus.config();

      cfg.panel = &_panel;

      cfg.pin_d0  = 15;
      cfg.pin_d1  = 7;
      cfg.pin_d2  = 6;
      cfg.pin_d3  = 5;
      cfg.pin_d4  = 4;

      cfg.pin_d5  = 9;
      cfg.pin_d6  = 46;
      cfg.pin_d7  = 3;
      cfg.pin_d8  = 8;
      cfg.pin_d9  = 16;
      cfg.pin_d10 = 1;

      cfg.pin_d11 = 14;
      cfg.pin_d12 = 21;
      cfg.pin_d13 = 47;
      cfg.pin_d14 = 48;
      cfg.pin_d15 = 45;

      cfg.pin_henable = 41;
      cfg.pin_vsync   = 40;
      cfg.pin_hsync   = 39;
      cfg.pin_pclk    = 0;

      cfg.freq_write = 12000000;

      cfg.hsync_polarity    = 0;
      cfg.hsync_front_porch = 40;
      cfg.hsync_pulse_width = 48;
      cfg.hsync_back_porch  = 40;

      cfg.vsync_polarity    = 0;
      cfg.vsync_front_porch = 1;
      cfg.vsync_pulse_width = 31;
      cfg.vsync_back_porch  = 13;

      cfg.pclk_active_neg = 1;

      _bus.config(cfg);
    }

    { 
      auto cfg = _panel.config();

      cfg.memory_width  = 800;
      cfg.memory_height = 480;
      cfg.panel_width   = 800;
      cfg.panel_height  = 480;

      cfg.offset_x = 0;
      cfg.offset_y = 0;

      _panel.config(cfg);
    }

    _panel.setBus(&_bus);
    setPanel(&_panel);
  }
};