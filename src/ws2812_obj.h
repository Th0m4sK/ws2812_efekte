#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
 enum direction{
        forward,
        backward
    };

     enum LEDSTATUS{
        CLEAR,
        COLORWIPE_F,
        COLORWIPE_B,
        COLORPOINT_F,
        COLORPOINT_B,
        COLORSWITCH,
        
        SETCOLOR
    };


class ws2812_obj
{
private:
    struct LEDOBJ
    {
    int Start;
    int Ende;
    int Zähler1;
    int Zähler2;
    unsigned long oldTime1;
    unsigned long oldTime2;
    int status;
    int oldStatus;
    uint32_t Color1;
    uint32_t Color2;
    bool flash;
    unsigned long flaschTimeON;
    unsigned long flaschTimeOFF;
    


       
    };
   


    LEDOBJ LED;

 void init();   
    
public:
    
   
ws2812_obj(int _Start, int _Ende);
int colorWipe(Adafruit_NeoPixel &strip,   uint32_t color,direction dir, unsigned long wait);
int colorPoint(Adafruit_NeoPixel &strip,uint32_t PointColor, uint32_t BackColor,direction dir,unsigned long wait);
int colorSwitch(Adafruit_NeoPixel &strip,uint32_t FirstColor, uint32_t SecondColor,unsigned long wait);
void setLEDColor(Adafruit_NeoPixel &strip,   uint32_t color);
void setColor1(uint32_t _color);
void setColor2(uint32_t _color);
int setStatus(Adafruit_NeoPixel &strip,LEDSTATUS _status,uint32_t _color1,uint32_t _color2,unsigned long wait);
    
};

