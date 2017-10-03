 void foodCompBegin(void)
  {
    
  myLCD.begin();
  myLCD.backlight();
  myLCD.setCursor(0,1);// next line
  myLCD.print("Food Computer");
  myLCD.setCursor(0,2);// next line
  myLCD.print("VERSION 1.4.3 \"MEGA\"");
   myLCD.setCursor(0,3);// next line
   myLCD.print("Open Door Detection");
  //Serial.println("Food Computer");
  //Serial.println("Data Print v1");
  //Serial.print("\n");
  //Serial.print("\n");
  delay(3500);
  myLCD.clear();

  //Serial.println("SETPOINT(*T)\tPID INPUT(*T)\tPID OUTPUT(*T)");
  }// close foodCompBegin

