void peltierBegin()
{
  pinMode(Tacho_1,INPUT_PULLUP);
  pinMode(Tacho_2,INPUT_PULLUP);
  
  pinMode(PeltierRelay,OUTPUT);
  pinMode(fanRelay,OUTPUT);
  
  digitalWrite(PeltierRelay,LOW);
  digitalWrite(fanRelay,HIGH);
}

