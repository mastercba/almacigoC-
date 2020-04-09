/*
 *  almacigo TTGO-CALL
 */

 #include "Adafruit_FONA.h"
 #include "variables.h"
 #include "sensores.h"
 #include "sim800.h"
 #include <string.h>
 #include <stdio.h>
 #include <stdlib.h> 
 #include <math.h>



//-----------------------------------------------
//WATCHdog
        void interruptReboot(){ 
                    //reset-ESP
                        esp_restart();
        }
//-----------------------------------------------        
///////////////////////////////////////////////////////////////////////////////////////////////////

void setup(){
        //init serial ports  
            Serial.begin(115200);  delay(10);            // the PC<->ESP32 baud rate
            Wire.begin(21,22,400000); //Wire.begin(18,19,400000);  Wire.begin(sda,scl,BusSpeed);
        //init internal SETUP counter control!  
            looptime = millis(); Serial.println(millis());
            Serial.println("Setup Loop Running.....");
        
        //init GPIOS & RELAY
            pinMode(water,  OUTPUT); digitalWrite(water,  OFF);
            pinMode(riego,  OUTPUT); digitalWrite(riego,  OFF);
            pinMode(mezcla, OUTPUT); digitalWrite(mezcla, OFF);
            pinMode(nutre,  OUTPUT); digitalWrite(nutre,  OFF); 
            pinMode(LED_BLUE, OUTPUT); digitalWrite(LED_BLUE, HIGH);
            pinMode(SIM800L_POWER, OUTPUT); digitalWrite(SIM800L_POWER, HIGH);
        //init SIM800L GPRS    
              initGPRS();
        //set system clock & date        
              SetTimeDate();                                      //set time and date from operator
        //WATCHdog
            watchdogTimer = timerBegin(myTimer, 80, true);      //timer 0 divisor 80
            timerAlarmWrite(watchdogTimer, 700000000, false);     //60000000--> 1min
            timerAttachInterrupt(watchdogTimer, &interruptReboot, true);
            timerAlarmEnable(watchdogTimer);                     // enable interrupt 

        //end internal SETUP counter control!
            looptime = millis() - looptime;
            Serial.print("Time in loop: "); Serial.print(looptime); Serial.println("ms \n\n");
}
/////////////////////////////////////////////////////////////////////////////////////////////////// 

void loop(){
        // Reset WDCounter -----------------------------------------------------         //WATCHdog
              timerWrite(watchdogTimer, 0);              // reset timer feed dog
        // blueLED interval ----------------------------------------------------  
                if (millis() - prevMillis > interval) {
                  ledState = !ledState;
                  digitalWrite(LED_BLUE, ledState);
                  prevMillis = millis();
                }
        // Time request --------------------------------------------------------
              timeRequest(); delay(500);
              if(Year <= 18){SetTimeDate(); timeRequest();}
        // WaterLevel sensor ---------------------------------------------------
              nivelAgua = waterLevelStatus();                  //1:empty  0:full        
              delay(10);
        // DS18B20 temperature sensor ------------------------------------------
              Serial.print("Temperature: "); tempAguaTanque = readTemp();
              Serial.println(tempAguaTanque);         
              delay(10);
        // EC,TDS,SAL,SG Water Quality sensor ----------------------------------
              Serial.print("TDS: "); char* tds = waterQuality();
              Serial.println(tds);        
              delay(10);


        delay(5000);                    
}
///////////////////////////////////////////////////////////////////////////////////////////////////