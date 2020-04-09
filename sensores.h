



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
char* waterQuality(){                                     // EC-EZO WaterQuality Sensor block!
                                                     //read waterQuality: EC TDS SAL SG Sensor
                                                                    //set K=0.1 for tds sensor
      Serial.println("Setting K0.1...!");     
        for (int clw1 = 0; clw1 <= 45; clw1++) {ec_data[clw1] = ' ';}
        for (int cl1 = 0; cl1 <= 15; cl1++) {computerdata[cl1] = ' ';}
          computerdata[0] = 'K'; computerdata[1] = ','; computerdata[2] = '0'; 
          computerdata[3] = '.'; computerdata[4] = '1';
          Wire.beginTransmission(addrs);  
          Wire.write(computerdata); 
          Wire.endTransmission(); 
          delay(delay_time);
        Serial.println("Done."); 
    //lee water quality Sensor!                              
        ii = 0; 
        do{
            for (int clx = 0; clx <= 45; clx++) {ec_data[clx] = ' ';}
            for (int cli = 0; cli <= 15; cli++) {computerdata[cli] = ' ';}
            computerdata[0] = 'r';
            Wire.beginTransmission(addrs);  
            Wire.write(computerdata);          
              Wire.endTransmission();           //end the I2C data transmission.
              delay(delay_time); 
              Wire.requestFrom(addrs, 48, 1); 
              code = Wire.read(); 
                while (Wire.available()) {
                    in_char = Wire.read();
                    ec_data[ii] = in_char;
                    ii += 1;
                    if (in_char == 0) {
                        ii = 0;
                        Wire.endTransmission();
                        break;
                    }
                }
              delay(500);
        }while(code != 1);
        Serial.println(ec_data);
            ec = strtok(ec_data, ","); Serial.println(ec);
            tds = strtok(NULL, ",");   Serial.println(tds);
            sal = strtok(NULL, ",");   Serial.println(sal);
            sg = strtok(NULL, ",");    Serial.println(sg);   
        return tds;       
} 
//--------------------------------------------------------------------------------------------