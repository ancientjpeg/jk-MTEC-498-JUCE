/*
  ==============================================================================

    CircularBuffer.h
    Created: 28 Feb 2022 2:10:08pm
    Author:  Jackson Kaplan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class CircularBuffer {
  unsigned int head, tail, payload, capacity;
  float       *buffer;

public:
  CircularBuffer(unsigned int size)
      : head(0), tail(0), payload(0), capacity(size), buffer(new float[size])
  {
    std::memset(buffer, 0, sizeof(float) * size);
  }
  ~CircularBuffer() { delete[] buffer; }
  void readToNoPop(float *dest, unsigned int num) {}
  void push(float sample)
  {
    if (payload == capacity)
      std::cerr << "buffer at capacity.\n";

    buffer[tail] = sample;
    tail         = tail + 1 < capacity ? tail + 1 : tail + 1 - capacity;
    payload++;
  }
  float pop()
  {
    if (payload == 0) {
      std::cerr << "tried to pop off an empty buffer.\n";
      exit(1);
    }
    float ret = buffer[head];
    head      = head + 1 < capacity ? head + 1 : head + 1 - capacity;
    payload--;
    return ret;
  }
};