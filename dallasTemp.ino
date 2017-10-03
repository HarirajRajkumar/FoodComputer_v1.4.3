int getDallasTemperatureC()
{   
     mySensor.requestTemperatures(); // send command to recieve temperature 
     byte dsTemperature = mySensor.getTempCByIndex(0);
     return dsTemperature; 
}

