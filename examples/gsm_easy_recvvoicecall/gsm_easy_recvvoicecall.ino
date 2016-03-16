/*
GSM_easy_recvvoicecall.ino - Beispiel für einen hereinkommenden Sprachanruf 
Version:     1.2
Date:        01.01.2013
Company:     antrax Datentechnik GmbH
Uses with:   Arduino UNO (ATmega328) & Arduino Duemilanove (ATmega328)


EXAMPLE:
This code prüft, ob ein hereinkommender Ruf ankommt ("RING") und beantwortet diesen mit einem DTMF tone.

We only use basic AT sequences (with the library), for detailed information please see the "M95_AT_Commands_V1.0.pdf"

WARNING: Incorrect or inappropriate programming of the mobile module can lead to increased fees!
*/

#include <gsm_easy.h>

void setup()
{
  GSM.begin();
  // Serial.println("init GSM_easy-Shield!");
}

void loop()
{   
  int result;    
  
  //---------------------------------------------------------------------------------------------------------------
  // let's register in the GSM network with the correct SIM pin!
  // ATTENTION: you MUST set your own SIM pin!
  
  result = GSM.initialize("1357");                                   
  if(result == 0)                                                    // => everything ok?
  {
    Serial.print  ("ME Init error: >");                              // => no! Error during GSM initialising
    Serial.print  (GSM.GSM_string);                                  //    here is the explanation
    Serial.println("<");
    while(1);
  }
  
  //---------------------------------------------------------------------------------------------------------------
  // ok, the ME is registered in the GSM network ... let's wait of an incoming call
   
  int time = 0;                                                      // timeout variable
  
  do
  {
    time++;
    result = GSM.RingStatus();                                       // ringing?
  }
  while((result == 0) && (time < 10));

  if(result == 0)                                                    // => RING detected
  {
    Serial.print  ("no incoming call!");                             // => no one calls me
    Serial.println("");
    while(1);
  }
  else
  {
    // Serial.print  ("incoming call: >");                           // => yippi ... someone calls me
    // Serial.print  (GSM.GSM_string);              
    // Serial.println("<");
  }

  //---------------------------------------------------------------------------------------------------------------
  // pick up the phone ...

  result = GSM.pickUp();                                             // pick up the phone

  if(result == 0)                                                    // => everything ok?
  {
    Serial.print  ("pick up error: >");                              // => no! ERROR while pick up the phone
    Serial.print  (GSM.GSM_string);                                  //    here ist the explanation
    Serial.println("<");
    while(1);
  }

  //---------------------------------------------------------------------------------------------------------------
  // ... and say "Hello" (with a DTMF tone)
  
  result = GSM.sendDTMF('1');                                        // let's be noisy!

  if(result == 0)                                                    // => everything ok?
  {
    Serial.print  ("DTMF error: >");                                 // => no! ERROR while sending a DTMF tone
    Serial.print  (GSM.GSM_string);                                  //    here ist the explanation
    Serial.println("<");
    while(1);
  }

  //---------------------------------------------------------------------------------------------------------------
  // exit the call
   
  result = GSM.exitCall();                                           // bye bye!

  if(result == 0)                                                    // => everything ok?
  {
    Serial.print  ("Hang up error: >");                              // => no! ERROR while hamging up
    Serial.print  (GSM.GSM_string);                                  //    here ist the explanation
    Serial.println("<");
    while(1);
  }
  
  
  while (1);
}

