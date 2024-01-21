#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "HTML.h"

//AP
const char *ssid = "KKN-UNDIP-2024";
const char *password = "";
String ssidNew = "", passNew;
ESP8266WebServer server(80);

#include "CTBot.h"
CTBot bot;
TBMessage msg;
String token = "6384928892:AAF3kAr3I0b4JT3SrJSkLepuYc2dbNIGxWs";

//inisialisasi loadcell hx711
#include "HX711.h"
HX711 scale;
uint8_t dataPin = 2; //D4
uint8_t clockPin = 0; //D3

//inisialisasi dot matrix
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN   14 //d5
#define DATA_PIN  13 //d7
#define CS_PIN    15 //d8

MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);


void handleRoot(){
  server.send(200, "text/html", index_html);
}

void handleForm(){
  ssidNew = server.arg("ssidNew");
  passNew = server.arg("passNew");
  server.send(200, "text/html", sukses_html);
  delay(2000);  
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssidNew, passNew);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
}

void setup() {
  Serial.begin(115200);

  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(IP);
  server.on("/", handleRoot);
  server.on("/action_page", handleForm);
  server.begin(); 
  delay(1000);
  
  bot.wifiConnect(ssidNew, passNew);
  bot.setTelegramToken(token);
  P.begin();
  analogWrite(5,255);
  delay(150);
  analogWrite(5,0);
  
  P.print("  KKN");
  delay(1000);
  P.print(" UNDIP");
  delay(1000);

  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(HX711_LIB_VERSION);
  Serial.println();
  scale.begin(dataPin, clockPin);
  scale.set_scale(226.44);
  scale.tare(20);
}

void loop() {
  if(ssidNew == ""){
    server.handleClient();
  } else {
    Serial.println("connect");
    delay(1000);
  }
  
  if (scale.is_ready())
  {
    float sensor = 0.0;
    sensor = (scale.get_units(2));
    float berat = 0.0;
    berat = sensor/1000;
    float abs_berat = abs(berat);
    delay(100);
    P.print(abs_berat,1);
    
    if(abs_berat >= 8.0){
      P.print(" OVER");
      delay(1000);
      P.print(abs_berat);
      delay(500);
      analogWrite(5, 255);
      delay(500);
      analogWrite(5, 0);
      delay(500);    
    }

  //  ini untuk tele
  if (CTBotMessageText == bot.getNewMessage(msg)) {
    if (msg.text.equalsIgnoreCase("/cekstatus")) {
      bot.sendMessage(msg.sender.id, (String)"Berat sampah : " + float(abs_berat) + (String)" Kg");
      }
    if (msg.text.equalsIgnoreCase("/botol")) {
      bot.sendMessage(msg.sender.id, "Anda memilih jenis sampah botol yang terdapat pada timbangan. Berikut saran pengolahan sampah botol agar memiliki nilai guna yang tinggi \nhttps://www.youtube.com/watch?v=ogE3n_KdYfg");
      }
    if (msg.text.equalsIgnoreCase("/kaleng")) {
      bot.sendMessage(msg.sender.id, "Anda memilih jenis sampah kaleng yang terdapat pada timbangan. Berikut saran pengolahan sampah botol agar memiliki nilai guna yang tinggi \nhttps://www.youtube.com/watch?v=u4m9C03KLIE");
      }
    if (msg.text.equalsIgnoreCase("/kertas")) {
      bot.sendMessage(msg.sender.id, "Anda memilih jenis sampah kertas yang terdapat pada timbangan. Berikut saran pengolahan sampah botol agar memiliki nilai guna yang tinggi \nhttps://www.youtube.com/watch?v=7h7Xh-c4KJ0");
      }
   }
  }
}
