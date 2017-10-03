
boolean MistData = 0;
boolean PumpData = 0;
// flag variables
boolean PumpFlag = 0;
bool MistFlag = 0;
unsigned long previousMillisPump = 0;

void controlWaterLevel(int WaterData)
{
  if(WaterData <= minLevel)  // 12
  { PumpFlag = 1;
    PumpFlag==1 ? PumpData = 1 : PumpData = 0; // ternary operator
    noCode(); // mist off
  }
  else if(WaterData == minLevel+1)  // 13
  {
    PumpFlag==1 ? PumpData = 1 : PumpData = 0; // pump on
       mistControl();
  }
  else if(WaterData == minLevel+2) // 14
  {
    PumpFlag==1 ? PumpData = 1 : PumpData = 0;
    mistControl();
  }
  else if(WaterData == minLevel+3)  // 15
  {
    PumpFlag==1 ? PumpData = 1 : PumpData = 0;
    mistControl();
  }
  else if(WaterData >= maxLevel)  // 16
  {
    mistControl();
    PumpFlag==1 ? PumpData = 1 : PumpData = 0;
    PumpFlag = 0;
  }
  
  digitalWrite(pumpPin , PumpData);
   
}

void noCode()
{
  for(int b=0;b<3;b++)
  digitalWrite(mistPin[b] , LOW);  
}

int a=0;
byte number;
boolean STATE =1;

void mistControl()
{
  //myMillis = millis();
    if(myMillis - previousMillisPump > mistTimer)
    {
      previousMillisPump = myMillis;
      mistSwitch(a);
      a++;
    }// close if
    
    if (a==4) a=1;
}// close mistControl


void mistSwitch(byte number)
{
  switch(number) // mistControl
  {
    case 1 : 
    digitalWrite(mistPin[0],HIGH);
    digitalWrite(mistPin[1],LOW);
    digitalWrite(mistPin[2],LOW);
    break;
    
    case 2 : 
    digitalWrite(mistPin[0],LOW);
    digitalWrite(mistPin[1],HIGH);
    digitalWrite(mistPin[2],LOW);
    break;
    
    case 3 :
    digitalWrite(mistPin[0],LOW);
    digitalWrite(mistPin[1],LOW);
    digitalWrite(mistPin[2],HIGH);
    break;
    
    default :
    digitalWrite(mistPin[0],LOW);
    digitalWrite(mistPin[1],LOW);
    digitalWrite(mistPin[2],LOW);
    break;
  }
}

