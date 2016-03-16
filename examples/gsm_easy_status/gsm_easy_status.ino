/*
GSM_easy_dialvoicecall.ino - Example to perform a voice call 
Version:     1.2
Date:        01.01.2013
Company:     antrax Datentechnik GmbH
Use with:    Arduino UNO (ATmega328) & Arduino Duemilanove (ATmega328)


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
  // ok, the ME is registered in the GSM network ... now let's find out all the info and stati of the module
  
  delay(2000);
  result = GSM.Status();                                             // query the current status
    
  Serial.print  ("Current Status: >");                               // => no! ERROR while sending a DTMF tone
  Serial.print  (GSM.GSM_string);                                    // here is the explanation
  Serial.println("<");


  while(1);
}
