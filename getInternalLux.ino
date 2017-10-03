unsigned long previousLuxMillis;
void getInternalLux(unsigned long LuxMillis)
{
  if(LuxMillis - previousLuxMillis > ms)
  {
    unsigned int data0, data1;
    previousLuxMillis = LuxMillis ;
  if (light.getData(data0,data1))
  {
    // getData() returned true, communication was successful
    
    //Serial.print("data0: ");
    //Serial.print(data0);
    //Serial.print(" data1: ");
    //Serial.print(data1);
  
    // To calculate lux, pass all your settings and readings
    // to the getLux() function.
    
    // The getLux() function will return 1 if the calculation
    // was successful, or 0 if one or both of the sensors was
    // saturated (too much light). If this happens, you can
    // reduce the integration time and/or gain.
    // For more information see the hookup guide at: https://learn.sparkfun.com/tutorials/getting-started-with-the-tsl2561-luminosity-sensor
  
    double lux;    // Resulting lux value
    boolean good;  // True if neither sensor is saturated
    
    // Perform lux calculation:

    good = light.getLux(gain,ms,data0,data1,lux);
    
    // Print out the results:
  
    //Serial.print(" lux: ");
    //Serial.print(lux);
    //if (good) Serial.println(" (good)"); else Serial.println(" (BAD)");
  }
  }
}

