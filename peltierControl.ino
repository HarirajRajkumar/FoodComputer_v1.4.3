boolean flagState = 0;
boolean ventState = 0;

void peltierControl(unsigned long peltierMillis)
{
  byte internalTemp = getDallasTemperatureC();
  if(fan[0].PeltierOn == 1) // peltier on 
  {
    if(peltierMillis < 25000) ventState = 1;
      
  if((peltierMillis > 25000 )&&(internalTemp > setEnvTemp))
  {
    ventState = 0;
    fan[0].peltierRelayState = 1;  // peltier on
    fan[0].RPM = readRPM_1();  // readRPM using tacho output from the fan 1
    fan[1].RPM = readRPM_2();  // readRPM using tacho output from the fan 2
    flagState = 0;    
  }
  else if((peltierMillis > 25000) && ((internalTemp <= setEnvTemp+1)&&(internalTemp > setEnvTemp - 1)) && (flagState ==0))
  { 
    fan[0].peltierRelayState = 1;
    fan[0].RPM = readRPM_1();
    fan[1].RPM = readRPM_2();
  }
  else if((peltierMillis > 25000) && (internalTemp <= setEnvTemp-1) && (flagState==0))
  {
        fan[0].peltierRelayState = 0;
        fan[0].RPM = readRPM_1();
        fan[1].RPM = readRPM_2();
        flagState = 1;
  }
  else if((peltierMillis > 25000) && (internalTemp <= setEnvTemp+1) && ( flagState ==1))
  {
        fan[0].peltierRelayState = 0;
        fan[0].RPM = readRPM_1();
        fan[1].RPM = readRPM_2();
  }
  else if ((internalTemp > setEnvTemp) &&(flagState==1))
  flagState=0;
  }// close main if
  if( (fan[0].RPM<4000 || fan[1].RPM < 4000) &&(peltierMillis > 25000 ) )
  { 
    fan[0].fault =1;
    fan[1].fault =1;
  } 

  if(fan[0].fault == 1){
  fan[0].peltierRelayState = 0;
  digitalWrite(fanRelay,LOW);
  }
  else if(fan[1].fault  == 1)
  {
  fan[0].peltierRelayState = 0;
  digitalWrite(fanRelay,LOW); 
  } 

  //if(fan[0].fault == 1 || fan[1].fault == 1 ||  fan[0].peltierRelayState == 0 && peltierMillis > 15000)
  //LCDpeltierEmergenyPrint();
  
  digitalWrite(PeltierRelay ,  fan[0].peltierRelayState);
  myLCD.setCursor(3,3);
  myLCD.print(ventState);
  digitalWrite(ventControl , ventState);
  //Serial.print(peltierMillis);
  //Serial.print("\t");
  //Serial.print(fan[0].RPM);Serial.print("\t");
  //Serial.print(fan[1].RPM);Serial.print("\t");
  //Serial.print(fan[0].fault);Serial.print("\t");
  //Serial.print(fan[1].fault);Serial.print("\t");
  //Serial.println(fan[0].peltierRelayState);
  
}

unsigned long pulseDuration,pulseDuration_2;

int readRPM_1()
{
pulseDuration = pulseIn(Tacho_1, LOW);
int frequency = 1000000/pulseDuration;

return (frequency/2*60);
}
int readRPM_2()
{
pulseDuration_2 = pulseIn(Tacho_2, LOW);
int frequency = 1000000/pulseDuration_2;

return (frequency/2*60);
 
}

