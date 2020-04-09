




// init GPRS-SIM800L Module 
//--------------------------------------------------------------------------------------------
void initGPRS(){
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
