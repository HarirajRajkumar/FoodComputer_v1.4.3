


//unsigned long previousMillis = 0;
unsigned long previousMillis_LOW = 0;
unsigned long previousMillis_HIGH = 0;

// defines variables
int duration;
int distance;

byte readWaterLevel()
{
  
  digitalWrite(TrigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin,HIGH);
  delayMicroseconds(6);  
 digitalWrite(TrigPin , LOW);

 duration = pulseIn(EchoPin, HIGH);

 distance = duration * 0.034029/2;

 int depthofwater = 29.5 - distance ;

return depthofwater;
}// close 

