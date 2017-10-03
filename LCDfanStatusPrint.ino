void LCDfanStatusPrint(byte xPos, byte yPos)
{
  myLCD.setCursor(xPos,yPos);
  
  myLCD.print(htr[0].fanStatus);
}

