void printHeaterPercValue(byte xPos , byte yPos, byte PIDoutput)
{
  byte constrainedPerc = constrain(map(PIDoutput,0,255,0,101),0,100);
  String PIDoutputPerc_output = String ( constrainedPerc );
  PIDoutputPerc_output.toCharArray(htr[0].printPIDoutputPerc_LCD,3);

  //PRINT FILTERINGS
  if(constrainedPerc < 10)
 {
  myLCD.setCursor(xPos,yPos); 
  myLCD.print("0");
  myLCD.setCursor(xPos+1,yPos);
  myLCD.print(htr[0].printPIDoutputPerc_LCD);
  myLCD.setCursor(xPos+2,yPos); 
  myLCD.print("%"); 
 }
 else if( constrainedPerc < 100)
 {
  myLCD.setCursor(xPos,yPos); 
  myLCD.print(htr[0].printPIDoutputPerc_LCD);
  myLCD.setCursor(xPos+2,yPos); 
  myLCD.print("%");
  myLCD.setCursor(xPos+3,yPos);
  myLCD.print(" ");
 }// close else
 else 
 {
  myLCD.setCursor(xPos,yPos); 
  myLCD.print(htr[0].printPIDoutputPerc_LCD);
  myLCD.setCursor(xPos+2,yPos);
  myLCD.print("0");
  myLCD.setCursor(xPos+3,yPos); 
  myLCD.print("%");
 }// close else
  
  
}// close HTRdataPrint();



