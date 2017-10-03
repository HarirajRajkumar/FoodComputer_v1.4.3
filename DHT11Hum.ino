unsigned long previousMillis_DHT_hum = 0;

float DHT11Hum()
{
  unsigned long myDHTMillis_hum = millis();
  if(myDHTMillis_hum - previousMillis_DHT_hum > 250)
  {
    previousMillis_DHT_hum = myDHTMillis_hum;
   float h = dht.readHumidity();
   myLCD.setCursor(14,3);
   myLCD.print(h);
   return h;
  }
  
}

