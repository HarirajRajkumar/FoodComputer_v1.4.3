void WaterLevelBegin()
{
   for(int i =0; i<3 ; i++)
  pinMode(mistPin[i],OUTPUT);
  pinMode(pumpPin,OUTPUT);

  pinMode(TrigPin,OUTPUT);
  pinMode(EchoPin,INPUT);
}

