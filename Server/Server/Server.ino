#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TridentTD_LineNotify.h>

#define BLYNK_PRINT Serial

String LINE_TOKEN = "fXxcUzWftehg6PYTrN7qh2EvsSTiWmRqvKjF93QO85E";
//char ssid[] = "@3BB";
//char pass[] = "glo123456";
//char ssid[] = "JP-TRUE";
//char pass[] = "123456789";
char ssid[] = "galilao";
char pass[] = "buu123456789";
//char ssid[] = "GALILAO";
//char pass[] = "BUU1234PM";

char auth[] = "e3a9bf2135c948e785f72faa7f738f50"; //Token ของ Server 
char auth1[] = "aab3c5e267ff48fabd01536c720e81d5";  //Token ของ Node A 
char auth2[] = "c15305ea2c864c15be6d357be49d1986";  //Token ของ Node B 
char auth3[] = "478006ceff8e4e7990fa3d36813c8519";  //Token ของ Node C
char auth4[] = "643abd48f884450fa2a9722b8fb518a5";  //Token ของ Node D 
char auth5[] = "a51a5608f6274f62a3b212b4bc8c9d95";  //Token ของ Node E 
char auth6[] = "3a9d4a8f058948d5b6b8ad0d83fc2fc0";  //Token ของ Node F 
char auth7[] = "c79e3fff6dc84c1b9a2680507faf903a";  //Token ของ Node G 

BlynkTimer timer;

float H_A;
float T_A;
float H_B;
float T_B;
float H_C;
float T_C;
float H_D;
float T_D;
float H_E;
float T_E;
float H_F;
float T_F;
float H_G;
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

WidgetTerminal terminal(V1);
WidgetBridge bridge2(V22);
WidgetBridge bridge3(V64);
WidgetBridge bridge4(V99);

void setup(){
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass, "oasiskit.com", 8080);
    LINE.setToken(LINE_TOKEN);
    
    timer.setInterval(10000L, Compute);
    timer.setInterval(10000L, Control_Temp);
    timer.setInterval(10000L, Control_Humi);
    
    if (Blynk.connect()){
        bridge2.setAuthToken(auth1);
        bridge3.setAuthToken(auth7);
        bridge4.setAuthToken(auth4);
           
    }
}
    
void loop(){
    Blynk.run();
    timer.run();
    Compute();
    Control_Temp();
    Control_Humi();
}

void Compute(){

    
    int diff_T01 = abs(T_A - T_B);
    int diff_T02 = abs(T_A - T_C);
    int diff_T03 = abs(T_A - T_D);
    int diff_T04 = abs(T_A - T_E);
    int diff_T05 = abs(T_A - T_F);
    int diff_T06 = abs(T_A - T_G);
    int diff_T07 = abs(T_B - T_C);
    int diff_T08 = abs(T_B - T_D);
    int diff_T09 = abs(T_B - T_E);
    int diff_T10 = abs(T_B - T_F);
    int diff_T11 = abs(T_B - T_G);
    int diff_T12 = abs(T_C - T_D);
    int diff_T13 = abs(T_C - T_E);
    int diff_T14 = abs(T_C - T_F);
    int diff_T15 = abs(T_C - T_G);    
    int diff_T16 = abs(T_D - T_E);
    int diff_T17 = abs(T_D - T_F);
    int diff_T18 = abs(T_D - T_G); 
    int diff_T19 = abs(T_E - T_F);
    int diff_T20 = abs(T_E - T_G);
    int diff_T21 = abs(T_F - T_G);

                                    
    terminal.print("Humi A : ");terminal.println(H_A);
    terminal.print("Temp A : ");terminal.println(T_A);
    terminal.print("Humi B : ");terminal.println(H_B);
    terminal.print("Temp B : ");terminal.println(T_B);
    terminal.print("Humi C : ");terminal.println(H_C);
    terminal.print("Temp C : ");terminal.println(T_C);
    terminal.print("Humi D : ");terminal.println(H_D);
    terminal.print("Temp D : ");terminal.println(T_D);
    terminal.print("Humi E : ");terminal.println(H_E);
    terminal.print("Temp E : ");terminal.println(T_E);
    terminal.print("Humi F : ");terminal.println(H_F);
    terminal.print("Temp F : ");terminal.println(T_F);
    terminal.print("Humi G : ");terminal.println(H_G);
    terminal.print("Temp G : ");terminal.println(T_G);
    terminal.print("diffT A,B : ");terminal.println(diff_T01);
    terminal.print("diffT A,C : ");terminal.println(diff_T02);
    terminal.print("diffT A,D : ");terminal.println(diff_T03);
    terminal.print("diffT A,E : ");terminal.println(diff_T04);
    terminal.print("diffT A,F : ");terminal.println(diff_T05);
    terminal.print("diffT A,G : ");terminal.println(diff_T06);
    terminal.print("diffT B,C : ");terminal.println(diff_T07);
    terminal.print("diffT B,D : ");terminal.println(diff_T08);
    terminal.print("diffT B,E : ");terminal.println(diff_T09);
    terminal.print("diffT B,F : ");terminal.println(diff_T10);
    terminal.print("diffT B,G : ");terminal.println(diff_T11);
    terminal.print("diffT C,D : ");terminal.println(diff_T12);
    terminal.print("diffT C,E : ");terminal.println(diff_T13);
    terminal.print("diffT C,F : ");terminal.println(diff_T14);
    terminal.print("diffT C,G : ");terminal.println(diff_T15);
    terminal.print("diffT D,E : ");terminal.println(diff_T16);
    terminal.print("diffT D,F : ");terminal.println(diff_T17);
    terminal.print("diffT D,G : ");terminal.println(diff_T18);
    terminal.print("diffT E,F : ");terminal.println(diff_T19);
    terminal.print("diffT E,G : ");terminal.println(diff_T20);
    terminal.print("diffT F,G : ");terminal.println(diff_T21);
    terminal.println("-------------------------------------"); 
   
  
  
  delay(5000);
  
  Serial.print("Humi A : ");Serial.println(H_A);
  Serial.print("Temp A : ");Serial.println(T_A);
  Serial.print("Humi B : ");Serial.println(H_B);
  Serial.print("Temp B : ");Serial.println(T_B);
  Serial.print("Humi C : ");Serial.println(H_C);
  Serial.print("Temp C : ");Serial.println(T_C);
  Serial.print("Humi D : ");Serial.println(H_D);
  Serial.print("Temp D : ");Serial.println(T_D);
  Serial.print("Humi E : ");Serial.println(H_E);
  Serial.print("Temp E : ");Serial.println(T_E);
  Serial.print("Humi F : ");Serial.println(H_F);
  Serial.print("Temp F : ");Serial.println(T_F);
  Serial.print("Humi G : ");Serial.println(H_G);
  Serial.print("Temp G : ");Serial.println(T_G);  
  Serial.print("diff Temp A, B :");Serial.println(diff_T01);
  Serial.print("diff Temp A, C :");Serial.println(diff_T02);  
  Serial.print("diff Temp A, D :");Serial.println(diff_T03);
  Serial.print("diff Temp A, E :");Serial.println(diff_T04);
  Serial.print("diff Temp A, F :");Serial.println(diff_T05);  
  Serial.print("diff Temp A, G :");Serial.println(diff_T06); 
  Serial.print("diff Temp B, C :");Serial.println(diff_T07);  
  Serial.print("diff Temp B, D :");Serial.println(diff_T08);
  Serial.print("diff Temp B, E :");Serial.println(diff_T09);
  Serial.print("diff Temp B, F :");Serial.println(diff_T10);  
  Serial.print("diff Temp B, G :");Serial.println(diff_T11); 
  Serial.print("diff Temp C, D :");Serial.println(diff_T12);
  Serial.print("diff Temp C, E :");Serial.println(diff_T13);
  Serial.print("diff Temp C, F :");Serial.println(diff_T14);  
  Serial.print("diff Temp C, G :");Serial.println(diff_T15);
  Serial.print("diff Temp D, E :");Serial.println(diff_T16);
  Serial.print("diff Temp D, F :");Serial.println(diff_T17);  
  Serial.print("diff Temp D, G :");Serial.println(diff_T18);
  Serial.print("diff Temp E, F :");Serial.println(diff_T19);  
  Serial.print("diff Temp E, G :");Serial.println(diff_T20);
  Serial.print("diff Temp F, G :");Serial.println(diff_T21);

  
           
  
  bridge2.virtualWrite(V22, diff_T01); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V23, diff_T02); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V24, diff_T03); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V25, diff_T04); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V26, diff_T05); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V27, diff_T06); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V28, diff_T07); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V29, diff_T08); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V30, diff_T09); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V31, diff_T10); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V32, diff_T11); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V33, diff_T12); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V34, diff_T13); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V35, diff_T14); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V36, diff_T15); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V37, diff_T16); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V38, diff_T17); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V39, diff_T18); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V40, diff_T19); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V41, diff_T20); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V42, diff_T21); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node A
  bridge3.virtualWrite(V43, diff_T01); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V44, diff_T02); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V45, diff_T03); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V46, diff_T04); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V47, diff_T05); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V48, diff_T06); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V49, diff_T07); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V50, diff_T08); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V51, diff_T09); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V52, diff_T10); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V53, diff_T11); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V54, diff_T12); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V55, diff_T13); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V56, diff_T14); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V57, diff_T15); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V58, diff_T16); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V59, diff_T17); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V60, diff_T18); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V61, diff_T19); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V62, diff_T20); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V63, diff_T21); //Server ส่งค่าผลต่างอุณหภูมิไปให้ Node G 

  bridge2.virtualWrite(V64, T_A); //Server ส่งค่าอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V65, T_B); //Server ส่งค่าอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V66, T_C); //Server ส่งค่าอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V67, T_D); //Server ส่งค่าอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V68, T_E); //Server ส่งค่าอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V69, T_F); //Server ส่งค่าอุณหภูมิไปให้ Node A
  bridge2.virtualWrite(V70, T_G); //Server ส่งค่าอุณหภูมิไปให้ Node A
  bridge3.virtualWrite(V71, T_A); //Server ส่งค่าอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V72, T_B); //Server ส่งค่าอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V73, T_C); //Server ส่งค่าอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V74, T_D); //Server ส่งค่าอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V75, T_E); //Server ส่งค่าอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V76, T_F); //Server ส่งค่าอุณหภูมิไปให้ Node G
  bridge3.virtualWrite(V77, T_G); //Server ส่งค่าอุณหภูมิไปให้ Node G 
 
  bridge4.virtualWrite(V99, H_A); //Server ส่งค่าอุณหภูมิไปให้ Node D
  bridge4.virtualWrite(V100, H_B); //Server ส่งค่าอุณหภูมิไปให้ Node D
  bridge4.virtualWrite(V101, H_C); //Server ส่งค่าอุณหภูมิไปให้ Node D
  bridge4.virtualWrite(V102, H_D); //Server ส่งค่าอุณหภูมิไปให้ Node D
  bridge4.virtualWrite(V103, H_E); //Server ส่งค่าอุณหภูมิไปให้ Node D
  bridge4.virtualWrite(V104, H_F); //Server ส่งค่าอุณหภูมิไปให้ Node D
  bridge4.virtualWrite(V105, H_G); //Server ส่งค่าอุณหภูมิไปให้ Node D
  

 
}

BLYNK_WRITE(V11) {H_A = param.asInt();}
BLYNK_WRITE(V12) {T_A = param.asInt();}
BLYNK_WRITE(V13) {H_B = param.asInt();}
BLYNK_WRITE(V14) {T_B = param.asInt();}
BLYNK_WRITE(V15) {H_C = param.asInt();}
BLYNK_WRITE(V16) {T_C = param.asInt();}
BLYNK_WRITE(V17) {H_D = param.asInt();}
BLYNK_WRITE(V18) {T_D = param.asInt();}
BLYNK_WRITE(V19) {H_E = param.asInt();}
BLYNK_WRITE(V20) {T_E = param.asInt();}
BLYNK_WRITE(V21) {H_F = param.asInt();}
BLYNK_WRITE(V22) {T_F = param.asInt();}
BLYNK_WRITE(V23) {H_G = param.asInt();}
BLYNK_WRITE(V24) {T_G = param.asInt();}

void Control_Temp(){


    if ((T_A > 18 && T_A < 22 )||(T_B > 18 && T_B < 22 )||(T_C > 18 && T_C < 22 )||(T_D > 18 && T_D < 22 )||(T_E > 18 && T_E < 22 )||(T_F > 18 && T_F < 22 )||(T_G > 18 && T_G < 22 ))
    {
        {
            if ((diff_T01 > 2)||(diff_T02 > 2)||(diff_T03 > 2)||(diff_T04 > 2)||(diff_T05 > 2)||(diff_T06 > 2)||(diff_T07 > 2)||(diff_T08 > 2)||(diff_T09 > 2)||(diff_T10 > 2)||(diff_T11 > 2)||(diff_T12 > 2)||(diff_T13 > 2)||(diff_T14 > 2)||(diff_T15 > 2)||(diff_T16 > 2)||(diff_T17 > 2)||(diff_T18 > 2)||(diff_T19 > 2)||(diff_T20 > 2)||(diff_T21 > 2))
            {
               
                Serial.println("พัดลมเปิด");
            }
            else 
            {             
                Serial.println("พัดลมปิด");
            }
         }
    }
    else 
    {
        LINE.notify("อุณหภูมิของฟาร์มอยู่นอกเกณฑ์ พัดลมเปิด");
        Serial.println("พัดลมเปิด");  
    }  
}

void Control_Humi(){

     if ((H_A < 85)||(H_B < 85)||(H_C < 85)||(H_D < 85)||(H_E < 85)||(H_F < 85)||(H_G < 85))
     {
             LINE.notify("ความชื้นของฟาร์มต่ำกว่าเกณฑ์ เครื่องทำความชื้นเปิด");
             Serial.println("เครื่องทำความชื้นเปิด");
     }
     else   
     {             
             Serial.println("เครื่องทำความชื้นปิด");
     }
 
}
