int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

int averageDepth(int depthOfWater)
{
  total = total - readings[readIndex];

readings[readIndex] = depthOfWater;

total = total + readings[readIndex];

readIndex++;

if(readIndex >= numReadings)
  readIndex = 0;

average = total / numReadings;

return average;
}

