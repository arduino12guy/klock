//*********************// Starts here //**************************//                                   
                                                                                                        
                         ######################                                         
                         ######################                                         
                    ######++++++++++++++++++++######                                    
                    ######++++++++++++++++++++######                                    
                    ######++++++++++++++++++++######                                    
                    ################################                                    
                    ################################                                    
                         ######          ######                                         
                         ######          ######                                         
                         ######          ######                                         
                         ######          ######                                         
                    ###########          ###########                                    
                    ######                    ######                                    
                    ######                    ######                                    
               #####++++++++++++++++               ######                               
               #####++++++++++++++++               ######                               
         ######++++++++++++++++++++++++++++++++++++++++++######                         
         ######++++++++++++++++++++++++++++++++++++++++++######                         
         ######----------------++++++++++++++++++++++++++######                         
         ######----------------++++++++++++++++++++++++++######                         
         ######----------------++++++++++++++++++++++++++######                         
         ######+++++++++++++++---------------------------######                         
         ######+++++++++++++++---------------------------######                         
         ######++++++++++++++++++++++++++++++++++++++++++######                         
         ######++++++++++++++++++++++++++++++++++++++++++######                         
          ##########++++++++++++++++++++++++++++++++##########                          
               #####++++++++++++++++++++++++++++++++#####                               
               #####++++++++++++++++++++++++++++++++#####                               
                    ################################                                    
                    ################################                                    
                                                                                        
                                                                                                        


//**********************|| Librarys & Links ||***********************//
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include "potion.h"
#include "Org_01.h"
//**********************|| Librarys & Links ||***********************//


//**********************|| Definations ||***********************//
TFT_eSPI tft = TFT_eSPI(); 
const char* ssid       = "Your WiFi ssid(Name)"; //Enter your WiFi name here.
const char* password   = "Your WiFi password";   //Enter your WiFi name here.
WiFiUDP ntpUDP;
int timezone  = 19800; //Enter timezone of your country here.
NTPClient timeClient(ntpUDP,"pool.ntp.org",timezone , 37440);
int lastMinute = -1;   //To update the time after every 1 minute.
//**********************|| Definations ||***********************//

//***********************|| setup part ||**************************//
void setup() {
  tft.init(); //Initialize display
  tft.setRotation(1); //Rotate Display.
  tft.setSwapBytes(true);
  timeClient.begin();  //ntp server begin.
  Serial.begin(115200); //Initialize serial.
  WiFi.begin(ssid, password); //Nothing to do here.
  while ( WiFi.status() != WL_CONNECTED ) { //Nothing to do here.
    delay ( 500 ); //Nothing to do here.
    Serial.print ( "." ); //Nothing to do here.
  }
}
//***********************|| setup part ||**************************//


//***********************|| Graphics part ||***********************//
void loop() {
 int currentMinute = timeClient.getMinutes(); 
 Serial.println("hours:");  //Serial output.
 Serial.println(timeClient.getHours()); //Serial output.
 Serial.println("min:");    //Serial output.
 Serial.println(timeClient.getMinutes()); //Serial output.
 timeClient.update();       //ntp server update (to update time).

if (currentMinute != lastMinute) { //To update the time after every 1 minute. 
lastMinute = currentMinute;   //To update the time after every 1 minute.
tft.fillScreen(TFT_BLACK);    //Graphics 
tft.pushImage(-25, 0, 240, 240, potion); //Graphics
tft.setTextSize(20); //Graphics
tft.setFreeFont(&Org_01); //Graphics
tft.setCursor(220, 100); //Graphics
tft.print(timeClient.getHours()); //Graphics
tft.setCursor(220, 160); //Graphics
tft.print(timeClient.getMinutes()); //Graphics
tft.setTextSize(18); //Graphics
tft.drawString(":", 200, 100); //Graphics
 }
}
//***********************|| Graphics part ||***********************//


//*********************// Ends here //**************************//