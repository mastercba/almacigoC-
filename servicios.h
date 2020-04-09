//---------------------------------------------------------------------------------------
void svcRiego()
{
    timerWrite(watchdogTimer, 0);                                 // reset timer feed dog
    int tr = 0;
    // Riego!
    Serial.println("Riego en proceso...!");
    digitalWrite(riego,  ON); 
    do{
      delay(100);
      tr++;                  
    }while(tr <= 4000 );          //500 son 51seg (aprox 1')
    // Apago riego!
    digitalWrite(riego,  OFF);        
}
//---------------------------------------------------------------------------------------
void svcMezcla()
{
    timerWrite(watchdogTimer, 0);                                 // reset timer feed dog
    int tm = 0;
    Serial.println("Mezcla en proceso...!");
    // Mezcla ON!    
    digitalWrite(mezcla,  ON);
    do{
      delay(100); tm++;                  
    }while(tm <= 2000 );          //500 son 51seg (aprox 1')            
    // Apago mezcla!
    digitalWrite(mezcla,  OFF);     
}
//---------------------------------------------------------------------------------------
        void svcDosi()  
        {
            timerWrite(watchdogTimer, 0);                         // reset timer feed dog   
            int rd = 0;
            Serial.println("Dosificando A&B...!");
            // dosificadores ON!    
            digitalWrite(nutre,  ON);
            do{  
              delay(100); rd++;                  
            }while(rd <= 250 );           //500 son 51seg (aprox 1')           
            // dosificadores OFF! 
            digitalWrite(nutre,  OFF);    
        }
//---------------------------------------------------------------------------------------
void iniciaValvula(){
  valvula.attach(servoPin);                                          // start the library
  Serial.println("Valve CLOSE...!");
  valvula.write(0);
  Serial.println("Done!");           
  valvula.detach();                                           // disable servo connection
}
//---------------------------------------------------------------------------------------
void abrirValvula(){
    valvula.attach(servoPin);                                        // start the library
        Serial.println("Opening valve...!");
          for(int posDegrees = 0; posDegrees <= 100; posDegrees++) {
            valvula.write(posDegrees);
            //Serial.println(posDegrees);
            delay(40);
          }
        Serial.println("Done!");  
    valvula.detach();                                         // disable servo connection
}
//---------------------------------------------------------------------------------------
void cerrarValvula(){
    valvula.attach(servoPin);                                        // start the library
        Serial.println("Closing valve...!");
          for(int posDegrees = 90; posDegrees >= 0; posDegrees--) {
            valvula.write(posDegrees);
            //Serial.println(posDegrees);
            delay(40);
          }
        Serial.println("Done!");           
    valvula.detach();                                         // disable servo connection
}
//---------------------------------------------------------------------------------------


// WATER - fill water to the tank - agua : 1(cargo) - 0(nocargo) 
//--------------------------------------------------------------------------------------------
int srvWater()
{
  Serial.println("Iniciamos Carga de AGUA al TANQUE!");
  int espero = 1; int numeroIntentos = 0; int aguita = 0;//dTank = true;
  nivelAgua = waterLevelStatus();  delay(10);              //1:empty  0:full WaterLevel sensor              
  digitalWrite(mezcla,  ON);    //mezclar - ON!                
  do{ 
    timerWrite(watchdogTimer, 0);                                      // reset timer feed dog
    digitalWrite(water,  ON);  //agua - ON!
    espero = espero + 1;  delay(2000);       // enable watch DOG...... & wait a little longer!
    nivelAgua = waterLevelStatus();  delay(10);            //1:empty  0:full WaterLevel sensor    
    if(espero == 700){                                      // tiempo de espera del espero 700
        if(numeroIntentos==7){             //excede en numero de veces que intento cargar agua
          //Apagamos TODO! y salimos --> NO SE PUDO CARGAR AGUA!
              Serial.println("Apagamos todo!, salimos!, no se pudo cargar agua!"); 
              digitalWrite(water,  OFF); digitalWrite(mezcla,  OFF);
              //reporta
			      // Send SMS for status
			      if (!sim800l.sendSMS("+591 69496560", "Relay is activated.")) {
			        Serial.println(F("Failed"));
			      } else {
			        Serial.println(F("Sent!"));
			      }
              //espera 2-3 min que pase las 21:00am
                  int tEspera1 = 0;
                  do{
                    timerWrite(watchdogTimer, 0); // reset timer feed dog
                    delay(100); tEspera1++;
                  }while(tEspera1 <= 1500 );    //500 son 51seg (aprox 1') //1500
              aguita = 0;
              return aguita;                  
        }
        numeroIntentos = numeroIntentos + 1;      //no se pudo cargar agua volvemos a intentar
        //apagamos
        Serial.println("Apagamos todo!, no se pudo cargar agua!, otro intento!");
        digitalWrite(water,  OFF); digitalWrite(mezcla,  OFF);
        delay(1000); espero = 1;                // once again! , wait for a while, init wDog,
        //abrimos agua y mezcla para intentar nuevamente       
        digitalWrite(water,  ON); digitalWrite(mezcla,  ON);
    }    
  }while(nivelAgua == 1);
    // Apagamos TODO, tanque listo!
        Serial.println("Apagamos todo!, Tanque listo!"); 
        digitalWrite(mezcla,  OFF);   //mezclar - OFF!
        digitalWrite(water,  OFF);    //agua - OFF! 
              //espera 2-3 min que pase las 21:00am
                  int tEspera2 = 0;
                  do{
                    timerWrite(watchdogTimer, 0); // reset timer feed dog
                    delay(100); tEspera2++;
                  }while(tEspera2 <= 1500 );    //500 son 51seg (aprox 1')  //1500
        aguita = 1;
        return aguita;
}
//--------------------------------------------------------------------------------------------

