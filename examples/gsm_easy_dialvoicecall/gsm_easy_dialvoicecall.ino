/*
GSM_easy_dialvoicecall.ino - Example to perform a voice call 
Version:     1.2
Date:        01.01.2013
Company:     antrax Datentechnik GmbH
Use with:   Arduino UNO (ATmega328) & Arduino Duemilanove (ATmega328)


EXAMPLE:
This code will try to perform a voice call to a given telephone number and send some DTMF tones when the line is established.

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
  // ok, the ME is registered in the GSM network ... now let's dial the telephone number for a voice call
  // ATTENTION: you MUST set the right destination telephone number!
   
  result = GSM.dialCall("+491701234567");                            // dial!
    
  // Serial.print  ("List current calls of ME: >");                  // => status list
  // Serial.print  (GSM.GSM_string);                                 // here is the explanation   
  // Serial.println("<");

  //---------------------------------------------------------------------------------------------------------------
  // let's beep with a DTMF tone (key = 1)
   
  delay(2000);
  result = GSM.sendDTMF('1');                                        // let's be noisy!
    
  if(result == 0)                                                    // => everything ok?
  {
    Serial.print  ("DTMF error: >");                                 // => no! ERROR while sending a DTMF tone
    Serial.print  (GSM.GSM_string);                                  // here is the explanation
    Serial.println("<");
    while(1);
  }

  //---------------------------------------------------------------------------------------------------------------
  // exit the call
   
  result = GSM.exitCall();                                           // bye bye!
    
  if(result == 0)                                                    // => everything ok?
  {
    Serial.print  ("Hang up error: >");                              // => no! ERROR while hanging up
    Serial.print  (GSM.GSM_string);                                  //    here is the explanation
    Serial.println("<");
    while(1);
  }
  
  
  while (1);
}
