/*
GSM_easy_ping.ino - Example to send a PING to an internet server 
Version:     1.2
Date:        01.01.2013
Company:     antrax Datentechnik GmbH
Use with:   Arduino UNO (ATmega328) & Arduino Duemilanove (ATmega328)


EXAMPLE:
This code will try to to send a PING to www.google.com

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
  // connect to GPRS with the correct APN (server, access, password) of your provider
  // ATTENTION: you MUST set your own access parameters!
  
  result = GSM.connectGPRS("internet.t-mobile.de","t-mobile","tm");  
  if(result == 0)                                                    // => everything ok?
  {
    Serial.print  ("GPRS Init error: >");                            // => no! Error during GPRS initialising
    Serial.print  (GSM.GSM_string);                                  //    here is the explanation
    Serial.println("<");
    while(1);
  }
 
  //---------------------------------------------------------------------------------------------------------------
  // send a PING to "www.google.com" and be pleased of the result
  
  result = GSM.sendPING("www.google.com", 10);  
  if(result == 0)                                                    // => everything ok
  {
    Serial.print  ("PING error: >");                                 // => no! we have a "PING Error"
    Serial.print  (GSM.GSM_string);                                  //    here is the explanation
    Serial.println("<");                                             //    = response of AT+QPING (page 168)
    while(1);
  }
  else
  {
    Serial.println("PING successfully ...");                         // => yes!                    
    Serial.print  (GSM.GSM_string);                                  //    here is the answer of the web server
                                                                     //    = response of AT+QPING (page 168)
  }

  while(1);                                                          // END OF DEMO
}
