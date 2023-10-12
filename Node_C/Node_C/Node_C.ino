#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
//#include <BH1750.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> 

//BH1750 lightMeter;
  
#define OLED_RESET LED_BUILTIN
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define BLYNK_PRINT Serial

//char ssid[] = "@3BB";
//char pass[] = "glo123456";
char ssid[] = "JP-TRUE";
char pass[] = "123456789";
//char ssid[] = "galilao";
//char pass[] = "buu123456789";
//char ssid[] = "GALILAO";
//char pass[] = "BUU1234PM";
//char ssid[] = "stemlab2";
//char pass[] = "stemlab2019";
//char auth[] = "998c19840b11499092236f38c020fd4d"; //Token ของ Node C ของเม
//char auth1[] = "c0ba87394c8a4379924136cfc0661848";  //Token ของ Server ของเม
char auth[] = "2a92371b58e744108f9f235b8d60c955";  //Token ของ Node C ของหอม
char auth1[] = "6f14574d7fd641e5963d1888f40e51c7"; //Token ของ Server ของหอม
//char auth[] = "ba180d1d02f34a199bdbd73f214c352b";  //Token ของ Node C ของคอม
//char auth1[] = "6a00494a6ba0424fa8183104b80851e3"; //Token ของ Server ของคอม

BlynkTimer timer;

WidgetBridge bridge1(V15);

//String hum;
//String temp; 
//String LI;
float h;
float t;
float lux;


#define DHTPIN  D3              // pin of sensor connected to
#define DHTTYPE DHT22           // DHT22 if useDHT22
DHT dht(DHTPIN, DHTTYPE);

void setup(){ 
  
    Serial.begin(9600);
    dht.begin();
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
    display.display();
    delay(2000);
    display.clearDisplay();
    Blynk.begin(auth, ssid, pass, "oasiskit.com", 8080);  
     
    if (Blynk.connect()){
        bridge1.setAuthToken(auth1);
    }
        
    //timer.setInterval(5000L, sendSensor_LUX);    
    timer.setInterval(5000L, sendSensor_DHT);  
  

    //Wire.begin(D5, D6);
    
    //lightMeter.begin();
    
    

} 

void loop(){ 
    
    Blynk.run();
    timer.run();
    display.setTextSize(1.5);
    display.setTextColor(WHITE);
    display.setCursor(1,0);
    display.display();
    delay(1000);
    display.clearDisplay();
      
}

/*void sendSensor_LUX(){
    
    float lux = lightMeter.readLightLevel();
    //String LI = String(lux) ;
    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lx");
    delay(1000);
}  */

void sendSensor_DHT(){

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    //String hum = String(h) + " %";
    //String temp = String(t) + " °C";

    if (isnan(h) || isnan(t)){
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
  
    Serial.print("Humidity is: "); Serial.println(h);
    Serial.print("Temperature is: "); Serial.println(t);
    display.print("TEMP : "); display.print( t); display.println(" C");
    display.print("HUM : "); display.print( h); display.println(" %");
    display.display();
    delay(2000);
    display.clearDisplay(); 
    
    
    Blynk.virtualWrite(V1, h);    //เอาไว้เชคว่ารับค่าความชื้นได้มั้ย
    Blynk.virtualWrite(V2, t);    //เอาไว้เชคว่ารับค่าอุณหภูมิได้มั้ย
    bridge1.virtualWrite(V15, h); //Node C ส่งค่าความชื้นไปให้ Server
    bridge1.virtualWrite(V16, t); //Node C ส่งค่าอุณหภูมิไปให้ Server
    delay(1000);
    

}
