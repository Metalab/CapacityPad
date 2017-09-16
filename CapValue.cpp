#include "CapValue.h"
#include "Arduino.h"

CapValue::CapValue() : peak(6000.0), bottom(3000.0), hysteresis(3000.0), readbufferindex(0), average(0) {
  
  for (int i = 0; i < _BUFFER_LENGTH; i++) {
      readbuffer[i] = 0;
  }
}

void CapValue::calculate() {
  long sum = 0;
  long last = readbuffer[0];
  long diff = 0;
  long totalDiff = 0;
  
  for (int i = 0; i < _BUFFER_LENGTH; i++) {
    diff = last - readbuffer[i];
    sum += (last = readbuffer[i]);
    totalDiff += diff;
  }

  average =  sum / _BUFFER_LENGTH;
  
  if (bottom + 15 <= peak) {
    peak -= 5;
    bottom += 5;
  }
  
  if (average > peak) {
    peak += 5.0;
  }
  if (average < bottom) {
    bottom -= 5.0;
  }

  hysteresis = abs(peak - bottom);
}

void CapValue::set(int v) {
  readbuffer[readbufferindex] = v;
  ++readbufferindex;
  if (readbufferindex == _BUFFER_LENGTH) {
    readbufferindex = 0;
  }

  calculate();
}

bool CapValue::isUp() {
  return average > (peak - hysteresis) - 100;
}

bool CapValue::isDown() {
  return average < (bottom + hysteresis) + 100;
}

