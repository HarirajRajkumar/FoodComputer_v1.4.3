 void LCDtempPrint(byte xPos, byte yPos ,byte temperature)
 {
  
  myLCD.setCursor(xPos,yPos); 
  myLCD.print(temperature);
  myLCD.setCursor(xPos+2,yPos); 
  myLCD.print("/"); 
  
   if(  htr[0].tempTEMP  < 10)
 {
  myLCD.setCursor(xPos+4,yPos);   
  myLCD.print(  htr[0].tempTEMP );
  myLCD.setCursor(xPos+6,yPos); 
  myLCD.print("/"); 
 }
 else if(   htr[0].tempTEMP < 100)
 {
  myLCD.setCursor(xPos+3,yPos); 
  myLCD.print(" ");
  myLCD.setCursor(xPos+4,yPos); 
  myLCD.print(  htr[0].tempTEMP );
  myLCD.setCursor(xPos+6,yPos); 
  myLCD.print("/");
 }// close else
 else if(   htr[0].tempTEMP  >= 100)
 {
  myLCD.setCursor(xPos+3,yPos); 
  myLCD.print(  htr[0].tempTEMP );
  myLCD.setCursor(xPos+6,yPos);
  myLCD.print("/");
 }// close else

// Printing next Thermistor Temperature Value
 if( htr[1].tempTEMP< 10)  // single digit
 {
  myLCD.setCursor(xPos+8,yPos);   
  myLCD.print( htr[1].tempTEMP);
 }
 else if(  htr[1].tempTEMP< 100) // double digit
 {
  myLCD.setCursor(xPos+7,yPos); 
  myLCD.print(" ");
  myLCD.setCursor(xPos+8,yPos); 
  myLCD.print( htr[1].tempTEMP);
 }// close else
 else if(  htr[1].tempTEMP >= 100)
{
  myLCD.setCursor(xPos+7,yPos); 
  myLCD.print( htr[1].tempTEMP);
 }// close else

  //Serial.print(  htr[0].tempTEMP );
  //Serial.print("\t");
  //Serial.println(htr[1].tempTEMP);
 }

