#include <Arduino.h>
#include <DHTesp.h>
#include <U8g2lib.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

DHTesp dht;

U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, 
/* clock=*/ 2, 
/* data=*/ 4, 
/* cs=*/ 16, 
/* dc=*/ 17, 
/* reset=*/ 5);




void setup() {
  //初始化DHT11驱动
  dht.setup(15,DHTesp::DHT11);
  //初始化U8G2库
  u8g2.begin();
  
  SerialBT.begin("检测装置001"); //Bluetooth device name
 
}

void loop() {
  
  /*****************温度读取*****************/
  //等待读取
  delay(dht.getMinimumSamplingPeriod());

  double h = dht.getHumidity()-10;
  double t = dht.getTemperature()-2;

  /*****************蓝牙发送*****************/
  
  SerialBT.printf("湿度%lf温度%lf",h,t);
  SerialBT.println();

  /*****************oled显示*****************/
  u8g2.clearBuffer();//清除缓存
  u8g2.firstPage();
  u8g2.setFont(u8g2_font_wqy16_t_gb2312);//字体

  u8g2.drawUTF8(0,14,"温湿度检测");
  
  //温度
  u8g2.drawUTF8(0,35,"温度");
  u8g2.setCursor(40,35);
  u8g2.print(t);

  //画圆
  u8g2.drawCircle(85,20,2,U8G2_DRAW_ALL);
  u8g2.setCursor(90,35);
  u8g2.print("C");

  //湿度
  u8g2.drawUTF8(0,60,"湿度");
  u8g2.setCursor(40,60);
  u8g2.print(h);

  u8g2.setCursor(90,60);
  u8g2.print("%");

  u8g2.sendBuffer();//显示
}
