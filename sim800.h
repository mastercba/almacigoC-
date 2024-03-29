





//--------------------------------------------------------------------------------------------
void initGPRS(){                                                   // init GPRS-SIM800L Module 
      Serial.println("ON && Init SIM800L module.....");
	  	delay(10000);

    // Make it slow so its easy to read!
        sim800lSerial->begin(4800, SERIAL_8N1, SIM800L_TX, SIM800L_RX);
        if (!sim800l.begin(*sim800lSerial)) {
          Serial.println(F("Couldn't find GSM SIM800L"));
          digitalWrite(SIM800L_PWRKEY, LOW); delay(5000);
          delay(10000);
          esp_restart();
          //while (1);
        }
        Serial.println(F("GSM SIM800L is OK"));

    // Set up the FONA to send a +CMTI notification
    // when an SMS is received
        sim800lSerial->print("AT+CNMI=2,1\r\n");
        Serial.println("GSM SIM800L Ready");
}
//--------------------------------------------------------------------------------------------
void SetTimeDate(){                                                         // Set Time & Date 
      Serial.println("Set Time&Date.....");

    // enableNetworkTimeSync
        if (!sim800l.enableNetworkTimeSync(true)){
          Serial.println(F("Failed to enableNetworkTimeSync")); 
          digitalWrite(SIM800L_POWER, HIGH);
          delay(10000);
          esp_restart();
        }
        delay(5000);
    // enable NTP time sync
        if (!sim800l.enableNTPTimeSync(true, F("pool.ntp.org"))){
          Serial.println(F("Failed to enableNTPTimeSync"));
          digitalWrite(SIM800L_POWER, HIGH);
          delay(10000);
          esp_restart();          
        }
        delay(5000);            
    // Get time!    
        char gTime[23];
        sim800l.getTime(gTime, 23);  // make sure replybuffer is at least 23 bytes!
        Serial.print(F("Time = ")); Serial.println(gTime);  

            sim800lSerial->print("AT+SAPBR=3,1,\"Contype\",\"GPRS\"\r\n"); delay(5000); 
            sim800lSerial->print("AT+SAPBR=3,1,\"APN\",\"3GNET\"\r\n"); delay(5000);             
            //GSM.println("AT+SAPBR=3,1,\"APN\",\"entel.bo\"");
            //delay(5000); SSD(); // 
            sim800lSerial->print("AT+SAPBR=1,1\r\n"); delay(5000);
            sim800lSerial->print("AT+SAPBR=2,1\r\n"); delay(5000);            
           
            sim800lSerial->print("AT+CNTPCID=1\r\n"); delay(5000);        
            sim800lSerial->print("AT+CNTP=\"88.147.254.227\",-16\r\n"); delay(5000);               
            sim800lSerial->print("AT+CNTP?\r\n"); delay(5000);
            sim800lSerial->print("AT+CNTP\r\n"); delay(5000);
            //GSM.println("AT+CTZU=1"); delay(5000); SSD(); //    

            sim800lSerial->print("AT+CLTS=1\r\n"); delay(5000); 
            sim800lSerial->print("AT+CENG=3\r\n"); delay(5000);

    // Get time!    
        char gTime1[23];
        sim800l.getTime(gTime1, 23);  // make sure replybuffer is at least 23 bytes!
        Serial.print(F("Time1 = ")); Serial.println(gTime1);
}
//--------------------------------------------------------------------------------------------
void timeRequest()												           // UPDATE Time&Date
{ 
      Serial.println("update Time.....");
      at =""; 
    // Get time!
        sim800lSerial->print("AT+CCLK?\r\n");
        while(!sim800l.available())
        {delay(50);}
        while (sim800l.available())
        {
          char timeBuffer = sim800l.read();
          at += timeBuffer;
        }
        Serial.println (at);
    if (  at.indexOf("+CCLK: ") > -1   ) { 
      Date = at.substring(at.indexOf("+CCLK: ")+8, at.indexOf("+CCLK: ")+16);         //дата
      Hr =   at.substring(at.indexOf("+CCLK: ")+17, at.indexOf("+CCLK: ")+19).toInt(); //часы 
      Min =  at.substring(at.indexOf("+CCLK: ")+20, at.indexOf("+CCLK: ")+22).toInt(); //минуты
      Sec =  at.substring(at.indexOf("+CCLK: ")+23, at.indexOf("+CCLK: ")+25).toInt(); //секунды
      Year = at.substring(at.indexOf("+CCLK: ")+8, at.indexOf("+CCLK: ")+10).toInt();
    }
        Serial.print ("Date  "),Serial.println (Date);
        Serial.print ("Hr  "),  Serial.println (Hr);
        Serial.print ("Min  "), Serial.println (Min); 
        Serial.print ("Sec  "), Serial.println (Sec);
        Serial.print ("Year  "), Serial.println (Year); 
}
//--------------------------------------------------------------------------------------------