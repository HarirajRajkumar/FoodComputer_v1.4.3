unsigned long humidifierMillis = 0;
boolean humidifierState = 0;

void humidifierControl(float humidity)
{
 if ( humidity <= humidifierControlPerc )
 {
  if ( myMillis - humidifierMillis >= humidifierTimer)
  { 
    humidifierMillis = myMillis;
    humidifierState =! humidifierState;
  } // close millis if
  digitalWrite(humidifierPin , humidifierState);
 }// close if
 else digitalWrite(humidifierPin , LOW);
 
}

