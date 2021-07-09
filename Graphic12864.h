#ifndef Graphic12864_h
#define Graphic12864_h

#include "Arduino.h"
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#include <SD.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define ENCODER_BTN         35
#define ENCODER_CLK         33
#define ENCODER_DT          31
#define SD_CARD_CS          53
#define SD_CARD_MOSI        49
#define SD_CARD_MISO        50
#define SD_CARD_CLK         52

class Graphic12864
{
  public:
    Graphic12864();
    void Initialize();
    void delayns();
    void draw();

  private:
    void printDirectory(File dir, int numTabs);
    void print_from_sd_card(const char* print_file);
};
// extern Graphic12864 LCDA;
#endif
