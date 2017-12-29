#include <SoftwareSerial.h>
#include <IRremote.h>
#include "arduino.h"
#include "audio.h"
#include "font.h"
#include "color.h"
#include "clock.h"//加载一堆头文件，代码更清晰点不是
#define INTERVAL_Time 10//更新时间
#define humanHotSensor 4//PIR传感器D4
#define buttonPin 12//led灯

bool isUP = true;
int val = 0;
int music_vol = 5;
bool humanHotState = false;
boolean on_off;
boolean statusChange;
bool playing = false;
int i = 0;
int pos = 0;
int soundNum = 1;
unsigned long Time_millis = millis();//定义一堆东西

void setup() {
  Serial.begin(9600);//接受端口
  pinMode(buttonPin, INPUT);//LED
  pinMode(humanHotSensor, INPUT);
  audio_init(DEVICE_Flash, 4, music_vol);//设置初始音乐播放值
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  dateTime = {2017, 12, 3, 6, 16, 30, 00};
  alarm = {2017, 12, 3, 6, 16, 31, 00};//设置初始时间
  timer = millis();
  rtc.clearAll();
  rtc.setDateTime(dateTime);//通过RTC模块计算时间
  irrecv.enableIRIn();//红外接收开启
}

void loop() {
  humanHotState = digitalRead(humanHotSensor);//从人体红外探测读取数据
  rtc.getDateTime(&dateTime);//读取rtc模块的数据存储为datetime对象数组

  if (humanHotState) //检测到动作
  {
    colorWipe(strip.Color(0, 125, 0));
     // 绿灯亮
     audio_choose(1);
      audio_play();//第1首歌播放
      delay(1000);
      dateTime.second++;//秒数增加
      u8g.firstPage();
      do {
        u8g.drawXBMP(0, 16, 32, 32, u1);
        u8g.drawXBMP(32, 16, 32, 32, u2);
        u8g.drawXBMP(64, 16, 32, 32, u3);
        u8g.drawXBMP(96, 16, 32, 32, u4);
      } while ( u8g.nextPage() );//显示“欢迎光临”字样
      i = 0;
    }
  else
  { 
    audio_pause();//暂停播放
    colorWipe(strip.Color(125, 0, 0));//红灯亮 
    if (millis() - timer_draw > init_draw)
    {
      pkj -= 4;
      u8g.firstPage();
      do {
        draw();
      }while ( u8g.nextPage() );//显示时间、闹铃规定时间、滚动显示Welcome
      timer_draw = millis();
    }
  }
  }
