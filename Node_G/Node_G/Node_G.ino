#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>

#define BLYNK_PRINT Serial


//char ssid[] = "@3BB";
//char pass[] = "glo123456";
//char ssid[] = "JP-TRUE";
//char pass[] = "123456789";
char ssid[] = "galilao";
char pass[] = "buu123456789";
//char ssid[] = "GALILAO";
//char pass[] = "BUU1234PM";
//char auth[] = "b7947746c598449d9562606f95f54965"; //Token ของ Node G ของเม
//char auth1[] = "c0ba87394c8a4379924136cfc0661848";  //Token ของ Server ของเม
//char auth[] = "a2939dc3be5445ebab4f55ae2a3ee8f7";  //Token ของ Node G ของหอม
//char auth1[] = "6f14574d7fd641e5963d1888f40e51c7"; //Token ของ Server ของหอม
char auth[] = "6a00494a6ba0424fa8183104b80851e3";  //Token ของ Node G ของคอม
char auth1[] = "5d1bad64243b42018b98e459c9b337d9"; //Token ของ Server ของคอม

BlynkTimer timer;

WidgetBridge bridge1(V23);

String hum;
String temp; 
String ldr;
float h;
float t;
float T_A;
float T_B;
float T_C;
float T_D;
float T_E;
float T_F;
float T_G;
int diff_T01;
int diff_T02;
int diff_T03;
int diff_T04;
int diff_T05;
int diff_T06;
int diff_T07;
int diff_T08;
int diff_T09;
int diff_T10;
int diff_T11;
int diff_T12;
int diff_T13;
int diff_T14;
int diff_T15;
int diff_T16;
int diff_T17;
int diff_T18;
int diff_T19;
int diff_T20;
int diff_T21;
#define DHTPIN  D3              // pin of sensor connected to
#define DHTTYPE DHT22           // DHT22 if useDHT22
DHT dht(DHTPIN, DHTTYPE);

void setup(){ 
    Serial.begin(115200);
    Blynk.begin(auth, ssid, pass, "blynk.iot-cm.com", 8080);  
     
    if (Blynk.connect()){
        bridge1.setAuthToken(auth1);
    }
        
    timer.setInterval(10000L, sendSensor);    
    timer.setInterval(10000L, Control);
        
    dht.begin();
    Wire.begin();

    pinMode(A0, OUTPUT);
    pinMode(D4, OUTPUT);
    
} 

void loop(){ 
    
    Blynk.run();
    timer.run();
    
}

void sendSensor(){

    int sensorValue = analogRead(A0);
    
    String ldr = String(sensorValue)+ " ";
    
    Serial.print("Light Intensity : ");Serial.println(sensorValue);
    
    
    if (sensorValue<=150)
    {
      Serial.println("บริเวณจุด A มีความเข้มแสงต่ำกว่าเกณฑ์กำหนด");
      //LINE.notify("บริเวณจุด A มีความเข้มแสงต่ำกว่าเกณฑ์กำหนด");
        
    }
    else
    {

      Serial.println("บริเวณจุด A มีความเข้มแสงอยู่ในเกณฑ์กำหนด");
    }
    
    
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    String hum = String(h) + " %";
    String temp = String(t) + " °C";

    if (isnan(h) || isnan(t)){
        Serial.println("Failed to read from DHT sensor!");
        //delay(1500);
    //return;
    }
    else 
    {
    Serial.print("Humidity is: "); Serial.println(hum);
    Serial.print("Temperature is: "); Serial.println(temp);
    
    oled.init();         // สั่งให้จอ Oled เริ่มทำงาน
    oled.clearDisplay(); // ล้างภาพหน้าจอ
    oled.setTextXY(0,0); // เลื่อน cursor ไปที่บรรทัดที่ 1 ตำแหน่งที่ 0
    oled.putString("Hum : ");
    oled.setTextXY(0,5); // เลื่อน cursor ไปที่บรรทัดที่ 1 ตำแหน่งที่ 5
    oled.putString(hum);
    oled.setTextXY(1,0); // เลื่อน cursor ไปที่บรรทัดที่ 0 ตำแหน่งที่ 0
    oled.putString("Temp : ");
    oled.setTextXY(1,5); // เลื่อน cursor ไปที่บรรทัดที่ 0 ตำแหน่งที่ 5
    oled.putString(temp);
    oled.setTextXY(2,0); // เลื่อน cursor ไปที่บรรทัดที่ 2 ตำแหน่งที่ 0
    oled.putString("LI : ");
    oled.setTextXY(2,5); // เลื่อน cursor ไปที่บรรทัดที่ 2 ตำแหน่งที่ 5
    oled.putString(ldr);
    
    Blynk.virtualWrite(V1, h);    //เอาไว้เชคว่ารับค่าความชื้นได้มั้ย
    Blynk.virtualWrite(V2, t);    //เอาไว้เชคว่ารับค่าอุณหภูมิได้มั้ย
    bridge1.virtualWrite(V23, h); //Node G ส่งค่าความชื้นไปให้ Server
    bridge1.virtualWrite(V24, t); //Node G ส่งค่าอุณหภูมิไปให้ Server
    }               
}

void Control(){
  

    //Serial.print("ผลต่างความชื้น : ");Serial.println(diff_H1);

    Serial.print("Temp A : ");Serial.println(T_A);
    Serial.print("Temp B : ");Serial.println(T_B);
    Serial.print("Temp C : ");Serial.println(T_C);
    Serial.print("Temp D : ");Serial.println(T_D);
    Serial.print("Temp E : ");Serial.println(T_E);
    Serial.print("Temp F : ");Serial.println(T_F);
    Serial.print("Temp G : ");Serial.println(T_G); 
    Serial.print("ผลต่างอุณหภูมิ A,B :");Serial.println(diff_T01);
    Serial.print("ผลต่างอุณหภูมิ A,C: ");Serial.println(diff_T02);
    Serial.print("ผลต่างอุณหภูมิ A,D: ");Serial.println(diff_T03);
    Serial.print("ผลต่างอุณหภูมิ A,E :");Serial.println(diff_T04);
    Serial.print("ผลต่างอุณหภูมิ A,F: ");Serial.println(diff_T05);
    Serial.print("ผลต่างอุณหภูมิ A,G: ");Serial.println(diff_T06);
    Serial.print("ผลต่างอุณหภูมิ B,C: ");Serial.println(diff_T07);
    Serial.print("ผลต่างอุณหภูมิ B,D: ");Serial.println(diff_T08);
    Serial.print("ผลต่างอุณหภูมิ B,E :");Serial.println(diff_T09);
    Serial.print("ผลต่างอุณหภูมิ B,F: ");Serial.println(diff_T10);
    Serial.print("ผลต่างอุณหภูมิ B,G: ");Serial.println(diff_T11);
    Serial.print("ผลต่างอุณหภูมิ C,D: ");Serial.println(diff_T12);
    Serial.print("ผลต่างอุณหภูมิ C,E :");Serial.println(diff_T13);
    Serial.print("ผลต่างอุณหภูมิ C,F: ");Serial.println(diff_T14);
    Serial.print("ผลต่างอุณหภูมิ C,G: ");Serial.println(diff_T15);
    Serial.print("ผลต่างอุณหภูมิ D,E :");Serial.println(diff_T16);
    Serial.print("ผลต่างอุณหภูมิ D,F: ");Serial.println(diff_T17);
    Serial.print("ผลต่างอุณหภูมิ D,G: ");Serial.println(diff_T18);
    Serial.print("ผลต่างอุณหภูมิ E,F: ");Serial.println(diff_T19);
    Serial.print("ผลต่างอุณหภูมิ E,G: ");Serial.println(diff_T20);
    Serial.print("ผลต่างอุณหภูมิ F,G: ");Serial.println(diff_T21);
    
    if ((T_A > 18 && T_A < 34 )||(T_B > 18 && T_B < 34 )||(T_C > 18 && T_C < 34 )||(T_D > 18 && T_D < 34 )||(T_E > 18 && T_E < 34 )||(T_F > 18 && T_F < 34 )||(T_G > 18 && T_G < 34 )) 
    {
        {
            if ((diff_T01 > 2)||(diff_T02 > 2)||(diff_T03 > 2)||(diff_T04 > 2)||(diff_T05 > 2)||(diff_T06 > 2)||(diff_T07 > 2)||(diff_T08 > 2)||(diff_T09 > 2)||(diff_T10 > 2)||(diff_T11 > 2)||(diff_T12 > 2)||(diff_T13 > 2)||(diff_T14 > 2)||(diff_T15 > 2)||(diff_T16 > 2)||(diff_T17 > 2)||(diff_T18 > 2)||(diff_T19 > 2)||(diff_T20 > 2)||(diff_T21 > 2))
            {
                digitalWrite(D4,LOW);
                Serial.println("ไฟติด");
            }
            else {
                digitalWrite(D4,HIGH);
                Serial.println("ไฟดับ");
            }
         }
    }
    else {
        digitalWrite(D4,LOW);
        Serial.println("ไฟติด");
    }        
}
BLYNK_WRITE(V43) {diff_T01 = param.asInt();}
BLYNK_WRITE(V44) {diff_T02 = param.asInt();}
BLYNK_WRITE(V45) {diff_T03 = param.asInt();}
BLYNK_WRITE(V46) {diff_T04 = param.asInt();}
BLYNK_WRITE(V47) {diff_T05 = param.asInt();}
BLYNK_WRITE(V48) {diff_T06 = param.asInt();}
BLYNK_WRITE(V49) {diff_T07 = param.asInt();}
BLYNK_WRITE(V50) {diff_T08 = param.asInt();}
BLYNK_WRITE(V51) {diff_T09 = param.asInt();}
BLYNK_WRITE(V52) {diff_T10 = param.asInt();}
BLYNK_WRITE(V53) {diff_T11 = param.asInt();}
BLYNK_WRITE(V54) {diff_T12 = param.asInt();}
BLYNK_WRITE(V55) {diff_T13 = param.asInt();}
BLYNK_WRITE(V56) {diff_T14 = param.asInt();}
BLYNK_WRITE(V57) {diff_T15 = param.asInt();}
BLYNK_WRITE(V58) {diff_T16 = param.asInt();}
BLYNK_WRITE(V59) {diff_T17 = param.asInt();}
BLYNK_WRITE(V60) {diff_T18 = param.asInt();}
BLYNK_WRITE(V61) {diff_T19 = param.asInt();}
BLYNK_WRITE(V62) {diff_T20 = param.asInt();}
BLYNK_WRITE(V63) {diff_T21 = param.asInt();}


BLYNK_WRITE(V71) {T_A = param.asInt();}
BLYNK_WRITE(V72) {T_B = param.asInt();}
BLYNK_WRITE(V73) {T_C = param.asInt();}
BLYNK_WRITE(V74) {T_D = param.asInt();}
BLYNK_WRITE(V75) {T_E = param.asInt();}
BLYNK_WRITE(V76) {T_F = param.asInt();}
BLYNK_WRITE(V77) {T_G = param.asInt();}
