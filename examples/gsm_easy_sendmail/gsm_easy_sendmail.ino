/*
GSM_easy_email.ino - Example to send an email 
Version:     1.2
Date:        01.01.2013
Company:     antrax Datentechnik GmbH
Use with:    Arduino UNO (ATmega328) & Arduino Duemilanove (ATmega328)


EXAMPLE:
This code will try to send an email

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
    Serial.print  ("ME Init error: >");                              // => NO! Error during GSM initialising
    Serial.print  (GSM.GSM_string);                                  //    here is the explanation
    Serial.println("<");
    while(1);
  }
  
//---------------------------------------------------------------------------------------------------------------
  // connect to GPRS with the correct APN (server, access, password) of your provider
  // ATTENTION: you MUST set your own access parameters!

  result = GSM.connectGPRS("internet.t-mobile.de","t-mobile","whatever");  // example for T-Mobile, Germany
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
  // configure the SMPT server with the correct server name, port, user name, password
  // ATTENTION: you MUST set your own access parameter!
  
  result = GSM.EMAILconfigureSMTP("smtp.antrax.de",25,"m0187ef4","2wx8wgqMNeLRgJmbhi");  
  if(result == 0)                                                    // => everything ok?
  {
    Serial.print  ("SMTP server Init error: >");                     // => NO! Error during initialising
    Serial.print  (GSM.GSM_string);                                  //    here is the explanation
    Serial.println("<");
    while(1);
  }
 
  //---------------------------------------------------------------------------------------------------------------
  // configure the information of sender
  // ATTENTION: you MUST set your own access parameter!
  
  result = GSM.EMAILconfigureSender("Harry Potter","test@potty.de");  
  if(result == 0)                                                    // => everything ok?
  {
    Serial.print  ("Sender information error: >");                   // => NO! Error during initialising
    Serial.print  (GSM.GSM_string);                                  //    here is the explanation
    Serial.println("<");
    while(1);
  }

  //---------------------------------------------------------------------------------------------------------------
  // setting the recipient[s] 
  // ATTENTION: you MUST set your own access parameter!
  
  result = GSM.EMAILrecipients(1, "willi@butz.de");                  // 1 means: TO 
  if(result == 0)                                                    // => everything ok
  {
    Serial.print  ("Recipients Init error: >");                      // => NO! Error during recipients setting
    Serial.print  (GSM.GSM_string);                                  //    here is the explanation
    Serial.println("<");
    while(1);
  }

  //---------------------------------------------------------------------------------------------------------------
  // setting the recipient[s] 
  // ATTENTION: you MUST set your own access parameter!
  
  result = GSM.EMAILrecipients(2, "manuela@mustermann.de");          // 2 means: CC (copy)   
  if(result == 0)                                                    // => everything ok?
  {
    Serial.print  ("Recipients Init error: >");                      // => NO! Error during recipients setting
    Serial.print  (GSM.GSM_string);                                  //    here is the explanation
    Serial.println("<");
    while(1);
  }

  //---------------------------------------------------------------------------------------------------------------
  // setting the title and text 
  
  result = GSM.EMAILbody("Hello World", "This is my very important test message ... just send from my GSM-easy! - Shield");  
  if(result == 0)                                                    // => everything ok?
  {
    Serial.print  ("Titel/Text Init error: >");                      // => NO! Error during title/text setting
    Serial.print  (GSM.GSM_string);                                  //    here is the explanation
    Serial.println("<");
    while(1);
  }

  //---------------------------------------------------------------------------------------------------------------
  // send it out to the SMTP server 
  
  result = GSM.EMAILsend();  
  if(result == 0)                                                    // => everything ok?
  {
    Serial.print  ("Email send error: >");                           // => NO! Error sending the email
    Serial.print  (GSM.GSM_string);                                  //    here is the explanation
    Serial.println("<");
    while(1);
  }
  else
  {
    Serial.println("Email sending process successful");
  }
  
  
  while(1);                                                          // END OF DEMO
}
