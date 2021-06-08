#include <Arduino.h>
#include <Arduino_LSM9DS1.h>

// I am copying from arduino gesture to emoji to try understand how data collection work. 
const float accThreshold = 2.5;
const int numSamples = 119;

int sampleRead = numSamples;

void setup() {
  Serial.begin(9600);
  while(!Serial);
  if(!IMU.begin()) {
    Serial.println("Error setting up IMU");
    while(1);
  }
  Serial.println("aX,aY,aZ,gX,gY,gZ");
}

void loop() {
  float aX, aY, aZ, gX, gY, gZ;
  Serial.println("boom");
  while(sampleRead == numSamples){
    if(IMU.accelerationAvailable()){
      IMU.readAcceleration(aX, aY, aZ);
      float aSum = fabs(aX) + fabs(aY) + fabs(aZ);

      if (aSum >= accThreshold) {
        sampleRead = 0;
        break;
      }
    }
  }

  while(sampleRead < numSamples) {
    if(IMU.accelerationAvailable() && IMU.gyroscopeAvailable()){
      IMU.readAcceleration(aX, aY, aZ);
      IMU.readGyroscope(gX, gY, gZ);
      sampleRead++;
      Serial.print(aX, 3);
      Serial.print(','),
      Serial.print(aY, 3);
      Serial.print(',');
      Serial.print(aZ, 3);
      Serial.print(',');
      Serial.print(gX, 3);
      Serial.print(','),
      Serial.print(gY, 3);
      Serial.print(',');
      Serial.print(gZ, 3);
      Serial.println();
      if(sampleRead == numSamples){
        Serial.println();
      }
    }
  }
}