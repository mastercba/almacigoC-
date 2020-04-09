/*
 *  almacigo TTGO-CALL
 */

 #include "variables.h"
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
        //init internal SETUP counter control!  
            looptime = millis(); Serial.println(millis());
            Serial.println("Setup Loop Running.....");
        
        //init RELAY
            pinMode(water,  OUTPUT); digitalWrite(water,  OFF);
            pinMode(riego,  OUTPUT); digitalWrite(riego,  OFF);
            pinMode(mezcla, OUTPUT); digitalWrite(mezcla, OFF);
            pinMode(nutre,  OUTPUT); digitalWrite(nutre,  OFF); 
            pinMode(LED_BLUE, OUTPUT); digitalWrite(LED_BLUE, HIGH);
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




        delay(15000);                    
}
///////////////////////////////////////////////////////////////////////////////////////////////////