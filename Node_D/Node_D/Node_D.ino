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
//char ssid[] = "galilao";
//char pass[] = "buu123456789";
char ssid[] = "GALILAO";
char pass[] = "BUU1234PM";
//char auth[] = "e16139e0bc534e889fc69c3570a77cfb"; //Token ของ Node D ของเม
//char auth1[] = "c0ba87394c8a4379924136cfc0661848";  //Token ของ Server ของเม
char auth[] = "c07aa73c3c634b3fad5e81b4c1c2d7bc";  //Token ของ Node D ของหอม
char auth1[] = "6f14574d7fd641e5963d1888f40e51c7"; //Token ของ Server ของหอม
//char auth[] = "a276bedf0fa544d2a0d2b1888906289c";  //Token ของ Node D ของคอม
//char auth1[] = "6a00494a6ba0424fa8183104b80851e3"; //Token ของ Server ของคอม

BlynkTimer timer;

WidgetBridge bridge1(V17);

String hum;
String temp; 
String ldr;
float h;
float t;
float H_A;
float H_B;
float H_C;
float H_D;
float H_E;
float H_F;
float H_G;
//int diff_H01;
//int diff_H02;
//int diff_H03;
//int diff_H04;
//int diff_H05;
//int diff_H06;
//int diff_H07;
//int diff_H08;
//int diff_H09;
//int diff_H10;
//int diff_H11;
//int diff_H12;
//int diff_H13;
//int diff_H14;
//int diff_H15;
//int diff_H16;
//int diff_H17;
//int diff_H18;
//int diff_H19;
//int diff_H20;
//int diff_H21;

#define DHTPIN  D3              // pin of sensor connected to
#define DHTTYPE DHT22           // DHT22 if useDHT22
DHT dht(DHTPIN, DHTTYPE);

void setup(){ 
    Serial.begin(115200);
    Blynk.begin(auth, ssid, pass, "blynk.iot-cm.com", 8080);  
     
    if (Blynk.connect()){
        bridge1.setAuthToken(auth1);
       // bridge4.setAuthToken(auth1);
    }
        
    timer.setInterval(10000L, sendSensor); 
    timer.setInterval(10000L, Control_Humi);            
    
    
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
    else {

    Serial.print("Humidity is: "); Serial.println(hum);
    Serial.print("Temperature is: "); Serial.println(temp);

    oled.init(); // สั่งให้จอ Oled เริ่มทำงาน
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
    bridge1.virtualWrite(V17, h); //Node A ส่งค่าความชื้นไปให้ Server
    bridge1.virtualWrite(V18, t); //Node A ส่งค่าอุณหภูมิไปให้ Server
    }

}


void Control_Humi(){

    Serial.print("Humi A : ");Serial.println(H_A);
    Serial.print("Humi B : ");Serial.println(H_B);
    Serial.print("Humi C : ");Serial.println(H_C);
    Serial.print("Humi D : ");Serial.println(H_D);
    Serial.print("Humi E : ");Serial.println(H_E);
    Serial.print("Humi F : ");Serial.println(H_F);
    Serial.print("Humi G : ");Serial.println(H_G); 
    
    if ((H_A < 85)||(H_B < 85)||(H_C < 85)||(H_D < 85)||(H_E < 85)||(H_F < 85)||(H_G < 85))
    { 
           digitalWrite(D4,LOW);
           Serial.println("เครื่องทำความชื้นเปิด");
    }
    else   
    {      
           digitalWrite(D4,HIGH);       
           Serial.println("เครื่องทำความชื้นปิด");
    }
        
  
}
  bridge4.virtualWrite(V99, H_A); //Node D รับค่าอุณหภูมิจาก Server 
  bridge4.virtualWrite(V100, H_B); //Node D รับค่าอุณหภูมิจาก Server 
  bridge4.virtualWrite(V101, H_C); //Node D รับค่าอุณหภูมิจาก Server 
  bridge4.virtualWrite(V102, H_D); //Node D รับค่าอุณหภูมิจาก Server 
  bridge4.virtualWrite(V103, H_E); //Node D รับค่าอุณหภูมิจาก Server 
  bridge4.virtualWrite(V104, H_F); //Node D รับค่าอุณหภูมิจาก Server 
  bridge4.virtualWrite(V105, H_G); //Node D รับค่าอุณหภูมิจาก Server 
  
BLYNK_WRITE(V78) {diff_H01 = param.asInt();}
BLYNK_WRITE(V79) {diff_H02 = param.asInt();}
BLYNK_WRITE(V80) {diff_H03 = param.asInt();}
BLYNK_WRITE(V81) {diff_H04 = param.asInt();}
BLYNK_WRITE(V82) {diff_H05 = param.asInt();}
BLYNK_WRITE(V83) {diff_H06 = param.asInt();}
BLYNK_WRITE(V84) {diff_H07 = param.asInt();}
BLYNK_WRITE(V85) {diff_H08 = param.asInt();}
BLYNK_WRITE(V86) {diff_H09 = param.asInt();}
BLYNK_WRITE(V87) {diff_H10 = param.asInt();}
BLYNK_WRITE(V88) {diff_H11 = param.asInt();}
BLYNK_WRITE(V89) {diff_H12 = param.asInt();}
BLYNK_WRITE(V90) {diff_H13 = param.asInt();}
BLYNK_WRITE(V91) {diff_H14 = param.asInt();}
BLYNK_WRITE(V92) {diff_H15 = param.asInt();}
BLYNK_WRITE(V93) {diff_H16 = param.asInt();}
BLYNK_WRITE(V94) {diff_H17 = param.asInt();}
BLYNK_WRITE(V95) {diff_H18 = param.asInt();}
BLYNK_WRITE(V96) {diff_H19 = param.asInt();}
BLYNK_WRITE(V97) {diff_H20 = param.asInt();}
BLYNK_WRITE(V98) {diff_H21 = param.asInt();}

BLYNK_WRITE(V99)  {H_A = param.asInt();}
BLYNK_WRITE(V100) {H_B = param.asInt();}
BLYNK_WRITE(V101) {H_C = param.asInt();}
BLYNK_WRITE(V102) {H_D = param.asInt();}
BLYNK_WRITE(V103) {H_E = param.asInt();}
BLYNK_WRITE(V104) {H_F = param.asInt();}
BLYNK_WRITE(V105) {H_G = param.asInt();}
