#include <Microduino_RTC.h>
#include <IRremote.h>
#include "Wire.h"
RTC rtc;//使用RTC模块
DateTime dateTime;
DateTime alarm;//设定两个数组
#define init_draw 10  //设置刷新时间10ms
#define setFont_L u8g.setFont(u8g_font_timB14)
#define setFont_S u8g.setFont(u8g_font_timB10)
#define setFont_M u8g.setFont(u8g_font_timB18)
#define setFont_V u8g.setFont(u8g_font_7x13)//设置字体

unsigned long timer_draw, timer;
int pkj = 0;
int pause;
int place = 0;
int RECV_PIN = 10;
IRrecv irrecv(RECV_PIN);
decode_results results; //通过红外遥控

void draw()
{
	setFont_L;
	u8g.setPrintPos(4, 16);
	u8g.print(dateTime.year);
	u8g.print(" ");
	u8g.print(dateTime.month);
	u8g.print(" ");
	u8g.print(dateTime.day);
	u8g.print(" ");
	switch (dateTime.weekday) {
	case 1:
		u8g.print("Mon");
		break;
	case 2:
		u8g.print("Tue");
		break;
	case 3:
		u8g.print("Wed");
		break;
	case 4:
		u8g.print("Thu");
		break;
	case 5:
		u8g.print("Fri");
		break;
	case 6:
		u8g.print("Sat");
		break;
	case 7:
		u8g.print("Sun");
		break;
	}//根据rtc不同数值显示星期
	u8g.setPrintPos(pkj, 64);
	u8g.print("Welcome!");//滚动显示Welcome
	setFont_M;
	u8g.setPrintPos(12, 40);
	u8g.print(dateTime.hour);//时
	u8g.setPrintPos(44, 40);
	if (dateTime.second % 2 == 0)
		u8g.print(":");
	else
		u8g.print(" ");//使冒号闪烁，模拟时钟的感觉
	u8g.setPrintPos(60, 40);
	if (dateTime.minute < 10)
	{
		u8g.print("0");
		u8g.print(dateTime.minute);//分
	}
	else
		u8g.print(dateTime.minute);//显示日期、时分、欢迎字样

	setFont_V;
	u8g.setPrintPos(88, 41);
	u8g.print(alarm.hour);//设定的时
	u8g.setPrintPos(102, 41);
	u8g.print(":");
	u8g.setPrintPos(110, 41);
	u8g.print(alarm.minute);//设定的分
	if (place == 0)
	{
		u8g.setPrintPos(112, 28);
		u8g.print("*");
	}
	else
	{
		u8g.setPrintPos(92, 28);
		u8g.print("*");
	}//显示闹铃响铃时间，*标记便于修改
	if (((dateTime.hour) == (alarm.hour)) && ((dateTime.minute) == (alarm.minute)) && (dateTime.second) <= 8)
	{
		u8g.firstPage();
		setFont_M;
		u8g.setPrintPos(60, 35);
		u8g.print("Wake Up!");
		audio_choose(2);
		audio_play();
		delay(8000);
		dateTime.second += 8;
		audio_pause;
	}

	if (irrecv.decode(&results)) {
		Serial.println(results.value, HEX);
		if (results.value == 33480735 || results.value == 33460335)
			place++;
		place = place % 2;//使设置在时、分之间转换

		if (results.value == 33464415)
		{
			if (place == 0)
				alarm.minute++;
			else
				alarm.hour++;
		}

		if (results.value == 33478695)
		{
			if (place == 0)
				alarm.minute--;
			else
				alarm.hour--;
		}
		irrecv.resume(); //通过红外遥控器修改规定时间
	}
