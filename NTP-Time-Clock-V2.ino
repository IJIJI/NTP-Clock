#include "Arduino.h"

#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 RTC;


#include <TFT_ST7735.h>
#include <SPI.h>

#include "icons/ethernetIcon.h"
#include "icons/updateIcon.h"
#include "icons/updateIconGrey.h"

/*  
The pins used for the TFT chip select (CS) and Data/command (DC) and Reset (RST)
signal lines to the TFT must also be defined in the library User_Setup.h file.
Sugested TFT connections for UNO and Atmega328 based boards
  sclk 13  // Don't change, this is the hardware SPI SCLK line
  mosi 11  // Don't change, this is the hardware SPI MOSI line
  cs   9   // Chip select for TFT display
  dc   8   // Data/command line
  rst  7   // Reset, you could connect this to the Arduino reset pin
*/

TFT_ST7735 tft = TFT_ST7735();  // Invoke library, pins defined in User_Setup.h


// #include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>


// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {
  0x90, 0xA2, 0xDA, 0x0D, 0x6B, 0xB9
};

unsigned int localPort = 8888;       // local port to listen for UDP packets

EthernetUDP ntpUDP; // A UDP instance to let us send and receive packets over UDP

// const char timeServer[] = "time.nist.gov"; // time.nist.gov NTP server
// const char timeServer[] = "europe.pool.ntp.org";
const char timeServer[] = "nl.pool.ntp.org";

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets


#include <TimeLib.h>


bool ethernetConnected = false;
bool lastEthernetConnected = false;
bool gettingTime = false;
bool lastGettingTime = false;
unsigned long gettingLastTime = 0;

unsigned long lastMaintain;

unsigned long updateMoment = 0;
bool updateNeeded = false;
unsigned long NTPTime = 0;

struct lastTimes {
  byte sec;
  byte min;
  byte hour;
  byte day;
  byte month;
  byte year;
};

lastTimes lastTime;


struct buttonState{
  long long lastChange;
  bool curState = HIGH;
  bool prevState = HIGH;
};

buttonState button1;
buttonState button2;

#define button1Pin       2
#define button2Pin       3


void setup() {

  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button1Pin), buttonPress, CHANGE);
  attachInterrupt(digitalPinToInterrupt(button2Pin), buttonPress, CHANGE);


  Wire.begin();


  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  tft.setCursor(0,0);


  terminalPrint();

  tft.println(F("Initializing... "));

  terminalPrint();

  tft.print(F("Syncing time with RTC.."));

  DateTime time = RTC.now();
  setTime(time.unixtime());

  tft.println(F("Done."));


  if (connectEthernetPrint()){

    terminalPrint();

    tft.print(F("Sending NTP packet..."));
    sendNTPpacket(timeServer);
    tft.println(F("Done."));
    
  }

  unsigned long delayMillis = millis() + 3000;

  while(millis() < delayMillis && ethernetConnected){
    adjustTime();
  }

  tft.fillScreen(TFT_BLACK);

}


void loop(){

  // if (millis() > 300000 && lastGettingTime < 300000 && !gettingTime){
  //   sendNTPpacket(timeServer);
  // }


  if (ethernetConnected) {
 
    adjustTime();

    if (millis() > lastMaintain + 10000){
      
      Ethernet.maintain();
      lastMaintain = millis();

    }
  }

  DateTime tempTime = RTC.now();
  time_t tempTTime = tempTime.unixtime();
  checkUpdate(tempTTime);


  if (button1.prevState != button1.curState && !button1.curState && button1.lastChange + 1000 < millis() && button2.prevState != button2.curState && !button2.curState && button2.lastChange + 1000 < millis() ){
    button1.prevState = button1.curState;
    button2.prevState = button2.curState;
    
    if (ethernetConnected){
      // tft.fillScreen(TFT_YELLOW);
      if (gettingLastTime + 1500 < millis()){
        sendNTPpacket(timeServer);
      }
    }
    else {
      // connectEthernetPrint(true);
      // sendNTPpacket(timeServer);
      // unsigned long delayMillis = millis() + 1500;

      // while(millis() < delayMillis && ethernetConnected){
      //   adjustTime();
      // }

      // updateAll(now());

      software_Reset();  //call reset
    }
    
  }
  else if (button1.prevState != button1.curState && button2.prevState != button2.curState && button2.curState ){
    button1.prevState = button1.curState;
    button2.prevState = button2.curState;
  }

}


void terminalPrint(){
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.print(">> ");
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
}

void software_Reset() // Restarts program from beginning but does not reset the peripherals and registers
{
asm volatile ("  jmp 0");  
}

//? Ethernet stuff VV


void adjustTime() {
  
  if (ntpUDP.parsePacket()) {


    ntpUDP.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    // the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, extract the two words:

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);

    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    NTPTime = secsSince1900 - 2208988800UL + 3600; // make ntc time from 1970 and add one hour for timezone.


    // Now get the fractional part
    unsigned long NTPFractional = (packetBuffer[44] << 24) | (packetBuffer[45] << 16) | (packetBuffer[46] << 8) | packetBuffer[47];

    // Get the fractional part as milliseconds
    unsigned long NTPMillis = (int32_t)(((float)NTPFractional / UINT32_MAX) * 1000);

    // Increment the seconds as we are waiting for the next one
    NTPTime++;  

    // Burn off the remaining fractional part of the existing second
    updateMoment = millis() + 1000 - NTPMillis;
    updateNeeded = true;


  }

  if (updateNeeded && millis() > updateMoment){

    RTC.adjust(NTPTime);
    // setTime(NTPTime);

    updateNeeded = false;
    gettingTime = false;
  }

}


// send an NTP request to the time server at the given address
void sendNTPpacket(const char * address) {
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  ntpUDP.beginPacket(address, 123); // NTP requests are to port 123
  ntpUDP.write(packetBuffer, NTP_PACKET_SIZE);
  ntpUDP.endPacket();

  gettingTime = true;
  gettingLastTime = millis();
}

int connectEthernet() {
  if (Ethernet.begin(mac) == 0){
    if (Ethernet.hardwareStatus() == EthernetNoHardware){

      return 2;
    }
    else{

      return 1;
    }

    ethernetConnected = false;

  }
  else{
    ntpUDP.begin(localPort);
    lastMaintain = millis();
    ethernetConnected = true;

    return 0;
  }
}

bool connectEthernetPrint() {
  return connectEthernetPrint(false);
}

bool connectEthernetPrint(bool blacktab) {

  if (blacktab){
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(1);
    tft.setCursor(0,0);
  }

  terminalPrint();

  tft.println(F("Connecting ethernet... "));

  int data = connectEthernet();

  if (data == 0){

    terminalPrint();

    tft.print(F("Ethernet connected at ip: "));
    tft.print(Ethernet.localIP());
    tft.println("  ");

    return true;
  }
  else if (data == 1){

    terminalPrint();

    tft.println(F("Error: "));
    tft.println(F("Ethernet shield was not found."));

    return false;
  }
  else {

    terminalPrint();

    tft.println(F("Error: "));
    tft.println(F("Failed to configure Ethernet."));

    return false;
  }

}


//? Button update VV

void buttonPress() {
  // button1.prevState = button1.curState;
  button1.curState = digitalRead(button1Pin);
  button1.lastChange = millis();

  // button2.prevState = button2.curState;
  button2.curState = digitalRead(button2Pin);
  button2.lastChange = millis();
}


//? Display update VV

#define color TFT_RED
#define greyColor 0x632C

void checkUpdate(time_t time){

  if (lastTime.sec != second(time)){

    lastTime.sec = second(time);
    updateSec(time);
  }

  if (minute(time) != lastTime.min || hour(time) != lastTime.hour){

    lastTime.min = minute(time);
    lastTime.hour = hour(time);
    updateHour(time);
  }

  if (day(time) != lastTime.day || month(time) != lastTime.month || year(time) != lastTime.year){

    lastTime.day = day(time);
    lastTime.month = month(time);
    lastTime.year = year(time);
    updateDate(time);
  }




  if(ethernetConnected && lastEthernetConnected != ethernetConnected){
    // tft.setTextColor(TFT_WHITE, TFT_BLACK);
    // tft.setTextSize(1);
    // tft.setCursor(10,115);
    // tft.print("con");
    drawIcon(ethernetIcon, 5, tft.height() - 5 - ethernetIconWidth, ethernetIconWidth, ethernetIconHeight);


    lastEthernetConnected = ethernetConnected;
  }
  else if (lastEthernetConnected != ethernetConnected){
    // tft.setTextColor(TFT_WHITE, TFT_BLACK);
    // tft.setTextSize(1);
    // tft.setCursor(10,115);
    // tft.print("   ");
    tft.fillRect(5, tft.height() - 5 - ethernetIconWidth, ethernetIconWidth, ethernetIconHeight, TFT_BLACK);

    lastEthernetConnected = ethernetConnected;
  }

  if(gettingTime && lastGettingTime != gettingTime){
    // tft.setTextColor(TFT_WHITE, TFT_BLACK);
    // tft.setTextSize(1);
    // tft.setCursor(135,115);
    // tft.print("get");
    drawIcon(updateIcon, tft.width() - 5 - updateIconWidth, tft.height() - 2 - updateIconWidth, updateIconWidth, updateIconHeight);

    lastGettingTime = gettingTime;
    
    
  }
  else if (lastGettingTime != gettingTime && gettingLastTime + 1500 < millis()){
    // tft.setTextColor(TFT_WHITE, TFT_BLACK);
    // tft.setTextSize(1);
    // tft.setCursor(135,115);
    // tft.print("   ");
    tft.fillRect(tft.width() - 5 - updateIconWidth, tft.height() - 2 - updateIconWidth, updateIconWidth, updateIconWidth, TFT_BLACK);

    lastGettingTime = gettingTime;
  }

}

void updateAll(time_t time){
  tft.fillScreen(TFT_BLACK);
  updateSec(time);
  updateHour(time);
  updateDate(time);
}

void updateSec(time_t time){

  tft.setTextColor(color, TFT_BLACK);
  tft.setTextSize(3);
  tft.setCursor(38,74);
  // tft.setCursor(65,72);


  if (second(time) < 10)
    tft.print("0");
  tft.print(second(time), DEC);

  tft.print(" ");

  tft.setTextColor(greyColor, TFT_BLACK);

  if (60 - second(time) < 10)
    tft.print("0");

  tft.print(60 - second(time), DEC);

}

void updateHour(time_t time){

  tft.setTextColor(color, TFT_BLACK);
  tft.setTextSize(5);
  tft.setCursor(8,29);


  if (hour(time) < 10)
    tft.print("0");
  tft.print(hour(time), DEC);

  tft.print(':');

  if (minute(time) < 10)
    tft.print("0");
  tft.print(minute(time), DEC);

}

void updateDate(time_t time){

  tft.setTextColor(0x632C, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(22,5);


  if (day(time) < 10)
    tft.print("0");
  tft.print(day(time), DEC);

  tft.print('/');

  if (month(time) < 10)
    tft.print("0");
  tft.print(month(time), DEC);

  tft.print('/');

  tft.print(year(time), DEC);
}

//====================================================================================
// This is the function to draw the icon stored as an array in program memory (FLASH)
//====================================================================================

// To speed up rendering we use a 64 pixel buffer
#define BUFF_SIZE 64

// Draw array "icon" of defined width and height at coordinate x,y
// Maximum icon size is 255x255 pixels to avoid integer overflow

void drawIcon(const unsigned short* icon, int16_t x, int16_t y, int8_t width, int8_t height) {

  uint16_t  pix_buffer[BUFF_SIZE];   // Pixel buffer (16 bits per pixel)

  // Set up a window the right size to stream pixels into
  tft.setAddrWindow(x, y, x + width - 1, y + height - 1);

  // Work out the number whole buffers to send
  uint16_t nb = ((uint16_t)height * width) / BUFF_SIZE;

  // Fill and send "nb" buffers to TFT
  for (int i = 0; i < nb; i++) {
    for (int j = 0; j < BUFF_SIZE; j++) {
      pix_buffer[j] = pgm_read_word(&icon[i * BUFF_SIZE + j]);
    }
    tft.pushColors(pix_buffer, BUFF_SIZE);
  }

  // Work out number of pixels not yet sent
  uint16_t np = ((uint16_t)height * width) % BUFF_SIZE;

  // Send any partial buffer left over
  if (np) {
    for (int i = 0; i < np; i++) pix_buffer[i] = pgm_read_word(&icon[nb * BUFF_SIZE + i]);
    tft.pushColors(pix_buffer, np);
  }
}