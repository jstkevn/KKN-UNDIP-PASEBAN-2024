#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include "HTML.h"

//AP
const char *ssid = "KKN-UNDIP-2024";
const char *password = "";
String ssidNew = "", passNew;
ESP8266WebServer server(80);

#include "CTBot.h"
CTBot bot;
TBMessage msg;
String token = "telegram TOKEN";

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
    P.print("Tunggu");
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
  MDNS.begin("sobatmiring");
  
  bot.wifiConnect(ssidNew, passNew);
  bot.setTelegramToken(token);
  P.begin();
  pinMode(5,OUTPUT);
  digitalWrite(5,HIGH);
  delay(150);
  digitalWrite(5,LOW);
  
  P.print("  KKN");
  delay(1000);
  P.print(" UNDIP");
  delay(1000);

//  Serial.println(__FILE__);
//  Serial.print("LIBRARY VERSION: ");
//  Serial.println(HX711_LIB_VERSION);
//  Serial.println();
  scale.begin(dataPin, clockPin);
  scale.set_scale(226.44);
  scale.tare(20);
}

void buzz(){
    digitalWrite(5, HIGH);
    delay(500);
    digitalWrite(5, LOW);
    delay(500);
  }

void dns(){
  if(ssidNew == ""){
    server.handleClient();
  } 
  MDNS.update();
  }

void loop() {
  dns();
  if (scale.is_ready())
  {
    float sensor = 0;
    sensor = (scale.get_units(2));
    float berat = 0;
    berat = sensor/1000;
    float abs_berat = abs(berat);
    delay(100);
    char isi[6];
    dtostrf(abs_berat,3,1,isi);
    char absberat[10];
    sprintf(absberat,isi);
    P.print((String)absberat + " Kg");
    
    if(abs_berat >= 8.0){
      P.print(" OVER");
      delay(1000);
      buzz();
      P.print((String)absberat + " Kg");
      delay(500);
    }

  //  ini untuk tele
  if (CTBotMessageText == bot.getNewMessage(msg)) {
    if (msg.text.equalsIgnoreCase("/cekstatus")) {
      bot.sendMessage(msg.sender.id, (String)"Berat sampah : " + float(abs_berat) + (String)" Kg");
      }
    else if (msg.text.equalsIgnoreCase("/botol")) {
      bot.sendMessage(msg.sender.id, "Anda memilih jenis sampah botol yang terdapat pada timbangan. Berikut saran pengolahan sampah botol agar memiliki nilai guna yang tinggi \nhttps://www.youtube.com/watch?v=ogE3n_KdYfg");
      }
    else if (msg.text.equalsIgnoreCase("/kaleng")) {
      bot.sendMessage(msg.sender.id, "Anda memilih jenis sampah kaleng yang terdapat pada timbangan. Berikut saran pengolahan sampah botol agar memiliki nilai guna yang tinggi \nhttps://www.youtube.com/watch?v=u4m9C03KLIE");
      }
    else if (msg.text.equalsIgnoreCase("/kertas")) {
      bot.sendMessage(msg.sender.id, "Anda memilih jenis sampah kertas yang terdapat pada timbangan. Berikut saran pengolahan sampah botol agar memiliki nilai guna yang tinggi \nhttps://www.youtube.com/watch?v=7h7Xh-c4KJ0");
      }
    else{
      bot.sendMessage(msg.sender.id, "Maaf keywords tidak sesuai");
      }
   }
  }
}
