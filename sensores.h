



 #include "OneWire.h"
 #include "Wire.h"
 #include "DallasTemperature.h"






//--------------------------------------------------------------------------------------------
          const int  waterLevelPin = 36;                           // WaterLEVEL Sensor block!
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
    #define ONE_WIRE_BUS 4                               // DS18B20 Temperature Sensor block!
        OneWire ds(4); // on pin D4 (a 4.7K resistor is necessary)
        int sensorPin = A0; float celsius, fahrenheit;  
        String stringTemp = ""; char charTemp[]="25.4"; 
         // Setup a oneWire instance to communicate with any OneWire devices 
         OneWire oneWire(ONE_WIRE_BUS);
         // Pass our oneWire reference to Dallas Temperature. 
         DallasTemperature sensors(&oneWire);        
//routine
float readTemp(){                              //read DS18B20 and test if it's a real measure!
      float temAux;
    do{
      sensors.requestTemperatures();     // Send the command to get temp
      temAux = sensors.getTempCByIndex(0);
      delay(10);
    }while( (temAux>40)&&(temAux<0) );

    return (temAux);
} 
//--------------------------------------------------------------------------------------------