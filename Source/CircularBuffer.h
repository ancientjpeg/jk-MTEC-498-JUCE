/*
  ==============================================================================

    CircularBuffer.h
    Created: 28 Feb 2022 2:10:08pm
    Author:  Jackson Kaplan

  ==============================================================================
*/

#pragma once

class CircularBuffer {
  unsigned int head, tail, payload, capacity;
  float       *buffer;

public:
  CircularBuffer(unsigned int size)
      : head(0), tail(0), payload(0), capacity(size), buffer(new float[size])
  {
  }
  ~CircularBuffer() { delete[] buffer; }
  void  readTo(float *dest, unsigned int num) {}
  void  push() {}
  float pop() {}
};