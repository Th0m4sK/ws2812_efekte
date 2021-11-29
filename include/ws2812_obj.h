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
int setStatus(Adafruit_NeoPixel &strip,uint32_t *bak,LEDSTATUS _status,uint32_t _color1,uint32_t _color2,unsigned long wait);
    
};

ws2812_obj::ws2812_obj(int _Start, int _Ende)

{
    LED.Start=_Start;
    LED.Ende=_Ende;
    //LED.Zähler1=_Start;
}

int ws2812_obj::colorWipe(Adafruit_NeoPixel &strip,uint32_t color,direction dir,unsigned long wait) {
    int ret =0;
     
   
    if (millis()-LED.oldTime1>wait){
        LED.oldTime1=millis();
    
      if (LED.Zähler1>LED.Ende){
         LED.Zähler1=LED.Start;
         ret =1;
         return ret;
         }  
      if (dir==forward){
        strip.setPixelColor(LED.Zähler1, color); 
            }
            else{
                strip.setPixelColor((LED.Ende-LED.Zähler1)+LED.Start, color);

            }
        


     LED.Zähler1  ++;
    
     }    
  return ret;
}



int ws2812_obj::colorSwitch(Adafruit_NeoPixel &strip,uint32_t FirstColor, uint32_t SecondColor,unsigned long wait)
{
    int ret = 0;
    
   
    if (millis()-LED.oldTime1>wait){
        LED.oldTime1=millis();
        uint32_t col1=FirstColor;
         uint32_t col2=SecondColor;
        if (strip.getPixelColor(LED.Start)==FirstColor){
            col1=SecondColor;
            col2=FirstColor;
        }
        for (int i = LED.Start; i <=LED.Ende ; i++)
        {
            if (i&1){
                strip.setPixelColor(i, col1);
            }
            else{
                strip.setPixelColor(i, col2);
            }
        }
        
  
    }
return 1;
}
  


int ws2812_obj::colorPoint(Adafruit_NeoPixel &strip,uint32_t PointColor, uint32_t BackColor,direction dir,unsigned long wait) {
    int ret = 0;
    
   
    if (millis()-LED.oldTime1>wait){
        LED.oldTime1=millis();
    setLEDColor(strip,BackColor);
    if (dir==forward){
        strip.setPixelColor(LED.Zähler1, PointColor); 
            }
            else{
                strip.setPixelColor((LED.Ende-LED.Zähler1)+LED.Start, PointColor);

            }
    
     
     LED.Zähler1  ++;  
     if (LED.Zähler1>LED.Ende){
         LED.Zähler1=LED.Start;
         ret=1;
         }
     }

return ret;   
  
}
void ws2812_obj::setLEDColor(Adafruit_NeoPixel &strip,   uint32_t color)
{
    for (int i=LED.Start; i<=LED.Ende;i++){
        strip.setPixelColor(i, color); 
    }


}

void ws2812_obj::init(){
 if (LED.oldStatus!=LED.status){
 LED.Zähler1=LED.Start;
 LED.oldTime1=0;
 LED.oldStatus=LED.status;
 
 }   
 ;
}

void ws2812_obj::setColor1(uint32_t _color){
LED.Color1=_color;
}
void ws2812_obj::setColor2(uint32_t _color){
LED.Color2=_color;
}
int ws2812_obj::setStatus(Adafruit_NeoPixel &strip,uint32_t *bak,LEDSTATUS _status,uint32_t _color1,uint32_t _color2,unsigned long wait){
    LED.Color1=_color1;
    LED.Color2=_color2;
    LED.status=_status;
    init();
    int ret=0;
    for (unsigned long long i=0;i<sizeof(bak);i++){
        strip.setPixelColor(i, bak[i]);
    }
    if (_status==CLEAR){setLEDColor(strip,0x0000);}
    if (_status==COLORWIPE_F){ret=colorWipe(strip,LED.Color1,forward,wait);}
    if (_status==COLORWIPE_B){ret=colorWipe(strip,LED.Color1,backward,wait);}
    if (_status==COLORPOINT_F){ret=colorPoint(strip,LED.Color1,LED.Color2,forward,wait);}
     if (_status==COLORPOINT_B){ret=colorPoint(strip,LED.Color1,LED.Color2,backward,wait);}
      if (_status==COLORSWITCH){ret=colorSwitch(strip,LED.Color1,LED.Color2,wait);}
      if (_status==SETCOLOR){setLEDColor(strip,LED.Color1);}
      for (unsigned long long i=0;i<sizeof(bak);i++){
        bak[i]= strip.getPixelColor(i);
    }
      return ret;

}


