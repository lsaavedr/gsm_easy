/*
GSM_easy_httpget.ino - Example to send a HTTP GET to an internet server 
Version:     1.2
Date:        01.01.2013
Company:     antrax Datentechnik GmbH
Use with:    Arduino UNO (ATmega328) & Arduino Duemilanove (ATmega328)


EXAMPLE:
This code will try to send a HTTP GET to the antrax test loop server.

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

  result = GSM.connectGPRS("internet.t-mobile.de","t-mobile","whatever");     // example for T-Mobile, Germany
  // result = GSM.connectGPRS("gprs.vodafone.de","whatever","whatever");      // example for Vodafone, Germany  
  // result = GSM.connectGPRS("internet.eplus.de","eplus","whatever");        // example for e-plus, Germany 
  // result = GSM.connectGPRS("internet","gprs","whatever");                  // example for O2, Germany 
  if(result == 0)                                                    // => everything ok?
  {
    Serial.print  ("GPRS Init error: >");                            // => no! Error during GPRS initialising
    Serial.print  (GSM.GSM_string);                                  //    here is the explanation
    Serial.println("<");
    while(1);
  }

  //---------------------------------------------------------------------------------------------------------------
  // send the following HTTP GET: http://www.antrax.de/WebServices/responder.php?HelloWorld
  // this is a HTTP GET to the "antrax Test Loop Server" and you can look for the result 
  // under http://www.antrax.de/WebServices/responderlist.html
  // The parameter is "HelloWorld"
  
  result = GSM.sendHTTPGET("www.antrax.de", "GET /WebServices/responder.php?HelloWorld HTTP/1.1");  
  if(result == 0)                                                    // => everything ok
  {
    Serial.print  ("HTTP GET error: >");                             // => no! Error during data sending
    Serial.print  (GSM.GSM_string);                                  //    here is the explanation
    Serial.println("<");
    while(1);
  }

  // Serial.println("HTTP GET successfully ...");                    // => yes!                    
  Serial.println(GSM.GSM_string);                                    //    here is the answer of the web server


  while(1);                                                          // END OF DEMO
}
