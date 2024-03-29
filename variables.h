







//-----------------------------------------------------------------------------
        //peripherals devices defs
            #define OFF HIGH
            #define ON  LOW
            #define addrs 100                   // TDS Sensor Address
            Servo valvula;           // Create object for servo motor
              #define SIM800L_RX     27
              #define SIM800L_TX     26
              #define SIM800L_PWRKEY 4
              #define SIM800L_RST    5
              #define SIM800L_POWER  23
              #define LED_BLUE  13
            #define nutre  34  //NT
            #define mezcla 35  //MZ
            #define riego  32  //RG
            #define water  33  //WT

        //vars
                long looptime = 0;

        //WDT WATCHdog
            hw_timer_t *watchdogTimer = NULL;
            byte myTimer = 1; //0 | 1 | 2 |3
        //LEDstate
            long prevMillis = 0;
            int interval = 1000;
            boolean ledState = false;        
        //GPRS Module init    
            HardwareSerial *sim800lSerial = &Serial1;
            Adafruit_FONA sim800l = Adafruit_FONA(SIM800L_PWRKEY);
            uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0);
        // Time&Date Vars
            String at = ""; String Date; 
            int Sec; int Min; int Hr; int Year; int Month; int Day;
        // Nivel de Agua del tanque de riego
            int nivelAgua ;  char waterResult[6];
        // DS18B20 Temperature Sensor
            float tempAguaTanque ;
        //Water Quality Sensor
            byte code = 0;      //used to hold the I2C response code.
            char ec_data[48];   //
            byte in_char = 0;   //
            byte ii = 0;        //counter used for ec_data array.
            int delay_time = 4000;
            char computerdata[20];
            char *ec; char *tds;  
            char *sal; char *sg;   
            char charTDS[]="";
                String stringEC = ""; String stringTDS = ""; 
                String stringSAL = ""; String stringSG = "";
            char ecTEXT[]="EC:"; char tdsTEXT[]=" - TDS:";  
            char salTEXT[]=" - SAL:";  char sgTEXT[]=" - SG:";
        //ServoValvula
            static const int servoPin = 2;  // defines pin number for PWM

//-----------------------------------------------------------------------------