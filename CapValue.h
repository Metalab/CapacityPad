#ifndef __CAP_VALUE_H__

#define _BUFFER_LENGTH 10

#include <stdbool.h>

struct CapValue {
  float peak;
  float bottom;
  float hysteresis;
  int readbufferindex;
  long readbuffer[_BUFFER_LENGTH];
  long average;

  CapValue();
  void calculate();
  void set(int v);
  bool isUp();
  bool isDown();
};

#endif __CAP_VALUE_H__
