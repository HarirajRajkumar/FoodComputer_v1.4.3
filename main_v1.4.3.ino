// V1.4.3 FOR MEGA

#include <LiquidCrystal_I2C.h> // LCD_i2c library
#include <SparkFunTSL2561.h>  // For TSL2561 
#include <Wire.h> // I2C communication library for LCD

// Library used to read from DHT11
//#include <DHT.h>
//Libraries included to read data from DS18B20
#include <OneWire.h> // One wire communication  
#include <DallasTemperature.h> // Library used to read temperature from DS18B20
//Libraries included for PID control
#include<PID_v1.h>
//Lib used to read data from DHT11 and object 
#include"DHT.h"
// Lib used to read data from BMP280 ( Water level )
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_BME280.h>

//Wire Definitions
#define DHTPIN 13 
// DHT type Usage
#define DHTTYPE DHT22       
DHT dht(DHTPIN,DHTTYPE);
// humidifier control
const byte humidifierPin =26;
#define humidifierControlPerc 70 // in percentage 
#define humidifierTimer 3000 // in seconds

#define One_wire_pin 12 // FOR DS18B20 One wire communication

// Water level minimum and maximum control and pin declarations
#define minLevel 12
#define maxLevel 16

#define mistTimer 5000

const byte pumpPin = 11;
const byte mistPin[3] = { 22,23,10 };
const byte TrigPin= 24;
const byte EchoPin = 25;
// smoothing data
const int numReadings = 30;
int readings[numReadings];
// Variables used for PID control
double Kp=2,Ki=5,Kd=1;
double SetPoint,Input,Output; // FOR PID Control

// Vent Control
#define ventControl 28

// open door detection
#define openDoorBuzzer 27
#define opedDoorTime 5000
#define openDoorSwitch 29

// classes object
  LiquidCrystal_I2C myLCD(0x27,16,4);
// classes defined for reading temperature from ds 18b20
  OneWire myOneWire ( One_wire_pin );
  DallasTemperature mySensor(&myOneWire);
  PID myPID(&Input,&Output,&SetPoint,Kp,Ki,Kd,DIRECT);
// For TSL2561 ( LIGHT SENSOR )
SFE_TSL2561 light;
// for BMP280 
Adafruit_BME280 myBME_1;
Adafruit_BMP280 myBMP_2;

// Variable declarations for light
boolean gain;     // Gain setting, 0 = X1, 1 = X16;
unsigned int ms;  // Integration ("shutter") time in milliseconds

#define myFanPin 2

// For thermistor
const byte THERMISTOR_PIN_1 =A0;
const byte THERMISTOR_PIN_2 =A1;
#define NUMTEMPS 20

// For BMP280 
long Temperature = 0, Pressure = 0, Altitude = 0, Ambient = 0;  

// USER DEFINED FUNCTION Declarations

/* USER DEFINED FUNCTION 1
 *  Function Name : printHeaterPerValue();
 *  What does it do ?
 *      Prints Heater percentage data to the LCD
 *   
 *  Variables parsed : 
 *      xPos and yPos to print the data.
 * 
 */

void printHeaterPercValue(byte xPos , byte yPos,byte PIDoutput);

/* USER DEFINED FUNCTION 2
 *    Function Name : foodCompBegin();
 *     What does it do ?
 *        Initializes LCD by printing the version and
 *        specific data required.
 *    MUST BE CALLED IN SETUP function.
 */   

 void foodCompBegin(void);
 
/* UDF 2.1
 * foodCompBeginSke();
 */
 
 void foodCompBeginSke();
 /* USER DEFINED FUNCTION 3
 *    Function Name: LCDtempPrint();
 *    What does it do ?
 *      Prints Temperature Data in specified co-ordinates of LCD
 */
 void LCDtempPrint(byte xPos, byte yPos, byte temperature);

  /*
  * User Defined Function 4
  *     Function Name : fanStatus();
  *     What does it do ?
  *       Prints Fans status on provided LCD location.
  */
  void fanStatus(byte xPos, byte yPos, byte fanStatus, byte fanPin,byte thresholdForOFF,byte thresholdForON);

  /*
   * User Defined Function 5
   *      Funcn : getDallasTemperatureC();
   *      
   *      Reads Internal temperature 
   */

  int getDallasTemperatureC();

  /*
   *  User Defined Function 6
   *   thermistorTempC1();
   *  Returns Temperature of 1st Thermistor in Celsius .
   *   
   */

  int thermistorTempC1();

   /*
   *  User Defined Function 6.1
   *   thermistorTempC2();
   *  Returns Temperature of 2nd Thermistor in Celsius .
   *   
   */

  int thermistorTempC2();

  /*
   * User defined Function 7
   *  DHT11Temp();
   *  Used to read data from DHT11 and returns data in Celsius.
   */
   float DHT11Temp(); // not used 

   /* 
    *  User Defined Function 8
    *  DHT11Hum();
    *  Used to read humidity data from DHT11.
    */
    float DHT11Hum(); // to control humidifier 

    /*
     *  User Defined Function 9
     *  LCDfanStatusPrint();
     *  Prints Heater Fan's status at the given LCD's XY position
     */
     void LCDfanStatusPrint(byte xPos , byte yPos); 

    /*
     * User Defined Function 10
     * peltierControl();
     * returns both fan's RPM and turns ON peltier relay after 5 seconds
     */
     void peltierControl(unsigned long peltierMillis);

     /*
      * UDF 11
      * peltierBegin();
      * Pulls up tacho input pin ( for pulseIn funcn )
      * 
      * Reads a pulse (either HIGH or LOW) on a pin and returns number of milliseconds the pin was high or low based on the set value
      * 
      */
      void peltierBegin(); 

      /*
       * UDF 12.1
       * readRPM_1();
       *  Returns RPM of fan 1 ( cold side )
       *  
       *  pulseIn()
       *  Reads a pulse (either HIGH or LOW) on a pin and returns number of milliseconds the pin was high or low based on the set value
      * 
      * For example, if value is HIGH, pulseIn() waits for the pin to go HIGH, starts timing, then waits for the pin to go LOW and stops timing. Returns the length of the pulse in microseconds or 0 if no complete pulse was received within the timeout.
      *
      *
       */
        int readRPM_1();
        
       /*
        * UDF 12.2
        * readRPM_2();
        * Returns RPM of fan 2 ( hot side )
        */
        int readRPM_2();
        
      /*
       * UDF 13
       * LCDpeltierEmergenyPrint();
       * Executes in case the peltier fan on both side is off due to external disturbances 
       * and alerts user.
       * eg: karpamboochi.
       */
       void LCDpeltierEmergenyPrint();

       /*
        * UDF 14
        * getInternalLux();
        * Read internal lux value 
        * Used incase if one light fails
        */
      void getInternalLux(unsigned long LuxMillis);

        /*
         * UDF 15
         * readWaterLevel();
         * 
         * Reads water level data from ultrasonic sensor's output value
         */
        byte readWaterLevel();   

        /* 
         *  UDF 16
         *  WaterLevelBegin();
         *  Setups mistpin , pumpPin and trigPin as ouput 
         *  and echoPin as input
         *  
         */
        void WaterLevelBegin();

        /*
         * UDF 16.1
         * averageDepth();
         * Samples numReadings of data and returns the value in int
         */
         int averageDepth();

         /*
          * UDF 17 
          * controlWaterLevel();
          * 
          * Enables Motor , Mist control to work
          * 
          */
        void controlWaterLevel(int WaterData);


          /*
           * UDF 18
           * openDoorDetection();
           * 
           * detects open door and alerts the user after OpenDoorTimer
           */
        void openDoorDetection();
//Selected PWM pin for UNO
//Should change when comes to MEGA
const byte heater1PWM_pin = 3;
const byte heater2PWM_pin = 5;

// Structure
// at present pwm at pin 3 and 5 are controlled from data at pin A0 Returns RPM of fan 1 ( cold side )
// version 1.2
struct heaterPWM{
  //int heaterPWM_data; // takes PWM data varing from 0 to 255
  char printPIDoutputPerc_LCD[3];    // takes % of Heater's PWM data varying from 0 to 100%
  double PID_control_Input; //Input which must be DS's Temperature
  double PID_control_Output; // Output
  int tempTEMP; //Temperature temp variable
  byte fanStatus;
  boolean HeaterOn;
}htr[1]; // since 2 heaters are present htr[1] = htr[0] and htr[1] -- array of structures

// Structure to control Peltier and fan 
struct peltier{
  int RPM;
  boolean fault;
  boolean peltierRelayState;
  boolean PeltierOn;
}fan[1]; 


// Peltier Control Pins
#define Tacho_1 4
#define Tacho_2 8
#define PeltierRelay 7
#define fanRelay 9

const byte setEnvTemp = 23; // Max enviroment Temperature (inside box)
const int setHtrTemp = 200; // Max Heater Temperature 


void setup(void) {  
    Serial.begin(9600);
    
    foodCompBegin();// print the version 
    
    foodCompBeginSke(); // printing the data label
    
    pinMode(heater1PWM_pin,OUTPUT); // PWM adjustment (1st)
    pinMode(heater2PWM_pin,OUTPUT); // PWM adjustment (2nd)
    pinMode(myFanPin , OUTPUT);
    pinMode(ventControl ,OUTPUT);
    mySensor.begin();  // Dallas Temperature begin

   
    peltierBegin(); // pulls up tacho input pin

    WaterLevelBegin(); // Mist pin and pump pin set as output
    
  // TSL2561_ADDR_0 address with '0' shorted on board (0x29)
  // TSL2561_ADDR   default address (0x39)
  // TSL2561_ADDR_1 address with '1' shorted on board (0x49)

    light.begin(TSL2561_ADDR_1); // for tsl

    gain = 0;// for tsl
    unsigned char time = 2;// for tsl
    light.setTiming(gain,time,ms); // Set Timing..
    light.setPowerUp(); // Powerup..

    // Humidifier pin Configuration
    pinMode(humidifierPin,OUTPUT);

    // PID Control begin
    SetPoint=setEnvTemp; // User Variable
    myPID.SetMode(AUTOMATIC);
    pinMode(myFanPin,OUTPUT);

    dht.begin();
    digitalWrite(myFanPin , LOW);
    
    // open door detection setup
    pinMode(openDoorBuzzer,OUTPUT);
    pinMode(openDoorSwitch,INPUT);
    boolean openDoorSwitchData = digitalRead(openDoorSwitch);
    boolean openDoorSetup ;
    if(openDoorSwitchData == 1) // depends on the switch connections
    {
      while(openDoorSetup == 0)
        openDoorSetup = digitalRead(openDoorSwitch);
    }// close if
     for (int thisReading = 0; thisReading < numReadings; thisReading++) 
    readings[thisReading] = 0;
}//close setup

unsigned long previousMillis = 0;
unsigned long myMillis;

unsigned long previousthermMillis = 0;
unsigned long previousthermMillis_2 = 0;

void loop()   {

   myMillis= millis();


//int tempDHT = DHT11Temp(); // get data from DHT11 at pin 13

byte dallasTemp = getDallasTemperatureC();

  if(myMillis > 15000 && myMillis < 16000) // choose whether peltier should be on or heater should be on
  {
    if(dallasTemp <= setEnvTemp )//&&  mainHeaterTemp < setEnvTemp) // switches on heater
{
      htr[0].HeaterOn = 1;
      fan[0].PeltierOn = 0;
}
    else if ( dallasTemp > setEnvTemp)// && setEnvTemp <  // switches on peltier
 {     htr[0].HeaterOn = 0;
      fan[0].PeltierOn = 1;
 }
  }
  
  if ( htr[0].HeaterOn ==1 )
  htr[0].PID_control_Input =  getDallasTemperatureC();//+tempDHT)/2; // average data of both temperature from DS18B20 and DHT11
 else 
   htr[0].PID_control_Input =  getDallasTemperatureC()+100;
  
  Input = htr[0].PID_control_Input;// providing input to PID function
  
 // myPID.SetSampleTime();  
  myPID.Compute();
 
  
  htr[0].PID_control_Output = Output;// Output of PID function
  htr[1].PID_control_Output = htr[0].PID_control_Output ;
  boolean ledState = 0;
  
  // Initial Direct heat up till 153*C and do PID  ( PRE HEAT !!)
  if( htr[0].HeaterOn ==1 )
  {
  if ( (htr[0].PID_control_Output < 153 ) ) //htr[0].//&& htr[1].PID_control_Output < 153 )
  {
    if(myMillis - previousMillis >= 100 )
    {
      previousMillis = myMillis;
           if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
     
    }
         digitalWrite(heater1PWM_pin,ledState);
         digitalWrite(heater2PWM_pin,ledState);
         htr[0].fanStatus=0;
         digitalWrite(myFanPin , LOW);

  }
  else
  {
    analogWrite(heater1PWM_pin,htr[0].PID_control_Output); 
    analogWrite(heater2PWM_pin,htr[1].PID_control_Output);
    digitalWrite(myFanPin , HIGH);
             htr[0].fanStatus=1;
  }
  }
  
  int thermistorTemp_1;
  // Reading data from two Thermistor
  if(myMillis - previousthermMillis > 100) // first thermistor
  {
    previousthermMillis = myMillis;
   thermistorTemp_1= thermistorTempC1();  
  }

  if(myMillis - previousthermMillis_2 > 150) // second thermistor
  { 
    previousthermMillis_2 = myMillis;
  thermistorTempC2(); // directly prints temperature
  }

  peltierControl(myMillis);
   getInternalLux(myMillis); 
  humidifierControl(DHT11Hum()); // read humidity
  LCDfanStatusPrint(10,3); // print fan status
  //Serial.print(thermistorTemp_1);
  //Serial.print("\t");
  //Serial.println(htr[0].PID_control_Input);

  //Serial.print(myMillis); Serial.print("\t");
  //Serial.print( fan[0].peltierRelayState );Serial.print("\t");
  //Serial.print( dallasTemp ); Serial.print("\t");
  //Serial.print(fan[0].fault);
 // Serial.print(setEnvTemp);Serial.print("\t");
  //Serial.print(fan[0].fault);Serial.print("\t");Serial.println(htr[0].printPIDoutputPerc_LCD);

  // mist control
  int depthOfWater = readWaterLevel(); // read water level data from ultrasonic sensor hrc
  int AveragedDepth = averageDepth(depthOfWater); // average that data
    controlWaterLevel(AveragedDepth); // control the mist with the water data 
//made this on the day of mersal song release 
    

  printHeaterPercValue(2,2,htr[0].PID_control_Output);
  myLCD.setCursor(2,3);
  myLCD.print(fan[0].peltierRelayState);
  //printHeaterPercValue(2,3,fan[0].peltierRelayState);
  LCDtempPrint(10,2,getDallasTemperatureC());

  Serial.println(AveragedDepth);
}//close loop

