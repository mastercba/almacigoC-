







//-----------------------------------------------------------------------------
        //peripherals devices defs
            #define OFF HIGH
            #define ON  LOW
            #define addrs 100                   // TDS Sensor Address
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
        

//-----------------------------------------------------------------------------