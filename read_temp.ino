// Thermistor lookup table for RepRap Temperature Sensor Boards (http://make.rrrf.org/ts)
// Made with createTemperatureLookup.py (http://svn.reprap.org/trunk/reprap/firmware/Arduino/utilities/createTemperatureLookup.py)
// To create a LUT provide your own value to the NTC-LUT-Generator 
// ./createTemperatureLookup.py --r0=100000 --t0=25 --r1=0 --r2=4700 --beta=4066 --max-adc=1023
// r0: 100000     ( we used 100k NTC thermistor )
// t0: 25         ( Room Temperature )
// r1: 0
// r2: 4700       ( R2 value 
// beta: 4066     (Constent)
// max adc: 1023 ( Here it's 1023 since Arduino Uno is 10 bit uc !)
short temptable[NUMTEMPS][2] = {
   {1, 841},
   {54, 255},
   {107, 209},
   {160, 184},
   {213, 166},
   {266, 153},
   {319, 142},
   {372, 132},
   {425, 124},
   {478, 116},
   {531, 108},
   {584, 101},
   {637, 93},
   {690, 86},
   {743, 78},
   {796, 70},
   {849, 61},
   {902, 50},
   {955, 34},
   {1008, 3}
};



/* Function name : read_temp
 * Function : Take raw data from A0 pin (0 to 1023) and returns temperature provided from TempTable [20]
 * Return data : celcius
 * Reference : TempTable of 20 elements.
 */

int read_temp(int rawVal) 
{
   int  rawtemp = rawVal;
   int current_celsius = 0;

   byte i;
   for (i=1; i<NUMTEMPS; i++)
   {
      if (temptable[i][0] > rawtemp)
      {
         int realtemp  = temptable[i-1][1] + (rawtemp - temptable[i-1][0]) * (temptable[i][1] - temptable[i-1][1]) / (temptable[i][0] - temptable[i-1][0]);

         if (realtemp > 255)
            realtemp = 255;

         current_celsius = realtemp;

         break;
      }
   }

   // Overflow: We just clamp to 0 degrees celsius
   if (i == NUMTEMPS)
   current_celsius = 0;

   return current_celsius;
}
