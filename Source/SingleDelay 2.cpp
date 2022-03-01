/*
  ==============================================================================

    CircularBuffer.cpp
    Created: 28 Feb 2022 5:35:58pm
    Author:  Jackson Kaplan

  ==============================================================================
*/

#include "CircularBuffer.h"

CircularBuffer::CircularBuffer() : prepared(false), isPrepared(prepared)
{
  buffer = nullptr;
}
CircularBuffer::~CircularBuffer()
{
  if (buffer)
    delete[] buffer;
}
void CircularBuffer::prepare(size_t size)
{
  head = tail = payload = 0;
  capacity              = size;
  buffer                = new float[capacity];
  std::memset(buffer, 0, sizeof(float) * size);
  prepared = true;
}

float CircularBuffer::peek(int by = 0)
{
  if (by > 0) {
    int loc = (int)head + by;
    return buffer[loc];
  }
  return buffer[head];
};
void CircularBuffer::push(float sample)
{
  if (payload == capacity)
    std::cerr << "buffer at capacity.\n";

  buffer[tail++] = sample;
  tail           = tail < capacity ? tail : tail - capacity;
  payload++;
}
float CircularBuffer::pop()
{
  if (payload == 0)
    std::cerr << "tried to pop off an empty buffer.\n";
  float ret = buffer[head++];
  head      = head < capacity ? head : head - capacity;
  payload--;
  return ret;
}
