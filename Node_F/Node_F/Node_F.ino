#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>


#define BLYNK_PRINT Serial


//char ssid[] = "@3BB";
//char pass[] = "glo123456";
//char ssid[] = "JP-TRUE";=['/]
//char pass[] = "123456789";
//char ssid[] = "galilao";
//char pass[] = "buu123456789";
char ssid[] = "GALILAO";
char pass[] = "BUU1234PM";
//char auth[] = "232337a51f2640d38e054c27da8547ee"; //Token ของ Node F ของเม
//char auth1[] = "c0ba87394c8a4379924136cfc0661848";  //Token ของ Server ของเม 
//char auth[] = "47101c6f14a74677a245a06b23b0745e";  //Token ของ Node F ของหอม
//char auth1[] = "6f14574d7fd641e5963d1888f40e51c7"; //Token ของ Server ของหอม
char auth[] = "277d014b229446028c35bc5b363e5180";  //Token ของ Node F ของคอม
char auth1[] = "6a00494a6ba0424fa8183104b80851e3"; //Token ของ Server ของคอม

BlynkTimer timer;

WidgetBridge bridge1(V21);

String hum;
String temp; 
String ldr;
float h;
float t;


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
          
    dht.begin();
    Wire.begin();

    pinMode(A0, OUTPUT);

     
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
    bridge1.virtualWrite(V21, h); //Node F ส่งค่าความชื้นไปให้ Server
    bridge1.virtualWrite(V22, t); //Node F ส่งค่าอุณหภูมิไปให้ Server
    }               
}
