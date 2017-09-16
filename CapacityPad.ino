#include <CapacitiveSensor.h>
#include "CapValue.h"

#define NUM_SENSORS 10

CapacitiveSensor cs9 = CapacitiveSensor(17,32);
CapacitiveSensor cs0 = CapacitiveSensor(17,1);
CapacitiveSensor cs1 = CapacitiveSensor(17,2);
CapacitiveSensor cs2 = CapacitiveSensor(17,9);
CapacitiveSensor cs3 = CapacitiveSensor(17,10);
CapacitiveSensor cs4 = CapacitiveSensor(17,11);
CapacitiveSensor cs5 = CapacitiveSensor(17,12);
CapacitiveSensor cs6 = CapacitiveSensor(17,13);
CapacitiveSensor cs7 = CapacitiveSensor(17,14);
CapacitiveSensor cs8 = CapacitiveSensor(17,15);


CapacitiveSensor SENSORS[] = {cs0, cs1, cs2, cs3, cs4, cs5, cs6, cs7, cs8, cs9};
CapValue VALUES[] = {CapValue(), CapValue(), CapValue(), CapValue(), CapValue(), CapValue(), CapValue(), CapValue(), CapValue(), CapValue()};
bool LAST[] = {false, false, false, false, false, false, false, false, false, false};

void setup() {
  Serial.begin(9600);
}


bool checkCapValue(int i) {
  CapacitiveSensor sensor = SENSORS[i];
  CapValue& value = VALUES[i];
  int raw = sensor.capacitiveSensorRaw(300);
  value.set(raw);

  if (value.isDown())
    return false;
  else 
    return true;
}

void loop()                    
{
  for(int i = 0; i < NUM_SENSORS; ++i) {
    if(checkCapValue(i)) {
      if(!LAST[i])
        Serial.println(i);
      LAST[i] = true;
    } else {
        LAST[i] = false;
    }
  }
  delay(5);
}
