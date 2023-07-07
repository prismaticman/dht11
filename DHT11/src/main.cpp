#include <Arduino.h>
#include <DHTesp.h>
#include <U8g2lib.h>


DHTesp dht;
U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 2, /* data=*/ 4, /* cs=*/ 16, /* dc=*/ 17, /* reset=*/ 5);

void setup() {
  //初始化DHT11驱动
  dht.setup(15,DHTesp::DHT11);
  //初始化U8G2库
  u8g2.begin();
}

void loop() {

  delay(dht.getMinimumSamplingPeriod());

  double h = dht.getHumidity();
  double t = dht.getTemperature();

  u8g2.clearBuffer();//清除缓存
  u8g2.firstPage();
  u8g2.setFont(u8g2_font_ncenB18_tr);//字体

  //温度
  u8g2.drawStr(0,35,"T:");
  u8g2.setCursor(40,35);
  u8g2.print(t);

  //画圆
  u8g2.drawCircle(105,20,2,U8G2_DRAW_ALL);
  u8g2.setCursor(110,35);
  u8g2.print("C");

  //湿度
  u8g2.drawStr(0,60,"H:");
  u8g2.setCursor(40,60);
  u8g2.print(h);

  u8g2.setCursor(105,60);
  u8g2.print("%");

  u8g2.sendBuffer();//显示
}
