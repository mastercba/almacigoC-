



 #include "OneWire.h"
 #include "Wire.h"
 #include "DallasTemperature.h"





// WaterLEVEL Sensor block!
//--------------------------------------------------------------------------------------------

          const int  waterLevelPin = 36;     
          int  waterLevelState = 0;                                          //1:empty  0:full

int waterLevelStatus(){
        //init waterLevel pinMode    
          pinMode(waterLevelPin, INPUT);               
          Serial.print("Water level: ");
          waterLevelState = digitalRead(waterLevelPin); Serial.print(waterLevelState);
          if(waterLevelState==0){Serial.println("lleno!");}else{Serial.println("vacio!");}
            //lee nivel de agua
                for (int c1 = 0; c1 <= 5; c1++) {waterResult[c1] = ' ';}
                waterLevelState = digitalRead(waterLevelPin);
                if(waterLevelState == 0){     			//1: sensor negro    //0:sensor blanco
                  waterResult[0] = 'O'; waterResult[1] = 'K'; waterResult[2] = '.'; 
                  waterResult[3] = '.'; waterResult[4] = '!';
                  Serial.println(waterResult);
                }else{
                  waterResult[0] = 'F'; waterResult[1] = 'A'; waterResult[2] = 'I'; 
                  waterResult[3] = 'L'; waterResult[4] = '!';
                  Serial.println(waterResult);
                } 
          delay(50);
          return (waterLevelState); 
}
//--------------------------------------------------------------------------------------------
