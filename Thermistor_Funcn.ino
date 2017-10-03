
  
int thermistorTempC1( )
{ 
       
    previousthermMillis = myMillis;
  int rawvalue = analogRead(THERMISTOR_PIN_1);
  int celsius = read_temp(rawvalue); 
       htr[0].tempTEMP =celsius;
}// close thermistorTempC1

int thermistorTempC2()
{
  
    int rawValue = analogRead(THERMISTOR_PIN_2);
    int Celsius = read_temp(rawValue);
    htr[1].tempTEMP = Celsius;
    
}

/* FOR TESTING !!
  Serial.print("Current temp: ");
   Serial.print(celsius);
  // Serial.print(" ");
  // To convert obtained celsius value to fahrenheit use => fahrenheit = (((celsius * 9) / 5) + 32);
   //Serial.print("Fahrenheit :");
  // Serial.print(fahrenheit);
  // Serial.print("F");
  // Serial.print(" ");
   
   Serial.print("Raw value: ");
   Serial.print(rawvalue);
   Serial.print(" ");


   float Voltage = rawvalue*(4.43/1023.0);
   Serial.print("Voltage: ");
   Serial.print(Voltage);
   Serial.print(" ");


   float TherRes = (Voltage*4680) / (4.43 - Voltage);
   Serial.print("Thermal Resistance: ");
   Serial.print(TherRes);
   Serial.println(" ");
*/

