#include <IRremote.h>
#include <Wire.h>                                  //调用库  
#include "./ESP8266.h"
#include "U8glib.h"
#define  sensorPin_1  A0

#define SSID           "aaaa"                   // cannot be longer than 32 characters!WIFI账号密码
#define PASSWORD       "11111111"

#define IDLE_TIMEOUT_MS  8000      // Amount of time to wait (in milliseconds) with no data 
                                   // received before closing the connection.  If you know the server
                                   // you're accessing is quick to respond, you can reduce this value.

//WEBSITE     
#define HOST_NAME   "api.heclouds.com"
#define DEVICEID   "20457297"
#define PROJECTID "106504"    //设备号、对应id
#define HOST_PORT   (80)
#define setFont_L u8g.setFont(u8g_font_timB14)
#define setFont_S u8g.setFont(u8g_font_timB10)
#define setFont_M u8g.setFont(u8g_font_timB18)
#define setFont_V u8g.setFont(u8g_font_7x13)//设置字体
#define INTERVAL_LCD     20
String apiKey="NBUrYowJXKKzHjyI=HzUKWnv5BU=";
char buf[10];
int pause=0;
int RECV_PIN = 10;
#define humanHotSensor 4//PIR传感器D4
int num_p=0;
String mCottenData;
String jsonToSend;

//传感器值的设置 

#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); /* RX:D3, TX:D2 */
ESP8266 wifi(mySerial);
bool humanHotState = false;
String postString;                                //用于存储发送数据的字符串
IRrecv irrecv(RECV_PIN);  //定义IRrecv对象来接收红外线信号
decode_results results;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
unsigned long lcd_time = millis(); 
void prin()
{
  u8g.firstPage();
  do {         
      setFont_M;         
      u8g.setPrintPos(80, 45);        
      u8g.print(num_p);   
      u8g.setPrintPos(4, 45);        
      u8g.print("num :");   
      }while( u8g.nextPage() );
  }
  int wi=0;
void setup(void)     //初始化函数  
{       
  //初始化串口波特率  
    Wire.begin();
    Serial.begin(115200);   
    while(!Serial);
    pinMode(sensorPin_1, INPUT);
  pinMode(humanHotSensor, INPUT);
   //ESP8266初始化
    Serial.print("setup begin\r\n");   

  Serial.print("FW Version:");
  Serial.println(wifi.getVersion().c_str());

  if (wifi.setOprToStationSoftAP()) {
    Serial.print("to station + softap ok\r\n");
  } else {
    Serial.print("to station + softap err\r\n");
  }

  if (wifi.joinAP(SSID, PASSWORD)) {      //加入无线网
    Serial.print("Join AP success\r\n");  
    Serial.print("IP: ");
    Serial.println(wifi.getLocalIP().c_str());
  } else {
    Serial.print("Join AP failure\r\n");
  }//检测是否连接wifi成功

  if (wifi.disableMUX()) {
    Serial.print("single ok\r\n");
  } else {
    Serial.print("single err\r\n");
  }

  Serial.print("setup end\r\n");
    irrecv.enableIRIn(); // 启动红外解码
  
}
void loop(void)     //循环函数  
{   
  if (irrecv.decode(&results)) {      //解码成功，收到一组红外线信号
    if(results.value==33444015)
    {num_p=0;
     prin();
    }
    irrecv.resume(); //  接收下一个值
  }
   if(pause>=100)
  {
    updateSensorData(); 
    pause=0;
     
    }
   
  
 humanHotState = digitalRead(humanHotSensor);
 Serial.print(humanHotState);
  if (humanHotState) 
  {wi++;
  if (wi==27){
    num_p++;
    prin();
    Serial.print(num_p);
    wi=0;
  }}
  delay(100);
  pause++;
  humanHotState=false;
     
}

void updateSensorData() {
  if (wifi.createTCP(HOST_NAME, HOST_PORT)) { //建立TCP连接，如果失败，不能发送该数据
    Serial.print("create tcp ok\r\n");

jsonToSend="{\"Number\":";
    dtostrf(num_p,1,2,buf);
    jsonToSend+="\""+String(buf)+"\"";
    jsonToSend+="}";//发送数据，通过json格式

    postString="POST /devices/";
    postString+=DEVICEID;
    postString+="/datapoints?type=3 HTTP/1.1";
    postString+="\r\n";
    postString+="api-key:";
    postString+=apiKey;
    postString+="\r\n";
    postString+="Host:api.heclouds.com\r\n";
    postString+="Connection:close\r\n";
    postString+="Content-Length:";
    postString+=jsonToSend.length();
    postString+="\r\n";
    postString+="\r\n";
    postString+=jsonToSend;
    postString+="\r\n";
    postString+="\r\n";
    postString+="\r\n";//按照规定格式发表

  const char *postArray = postString.c_str();                 //将str转化为char数组
  Serial.println(postArray);
  wifi.send((const uint8_t*)postArray, strlen(postArray));    //send发送命令，参数必须是这两种格式，尤其是(const uint8_t*)
  Serial.println("send success");   
     if (wifi.releaseTCP()) {                                 //释放TCP连接
        Serial.print("release tcp ok\r\n");
        } 
     else {
        Serial.print("release tcp err\r\n");
        }
      postArray = NULL;                                       //清空数组，等待下次传输数据
  
  } else {
    Serial.print("create tcp err\r\n");
  }
  
}