#ifndef STRUCTS_HPP
#define STRUCTS_HPP


struct SensorOutput
{
  float values[6];   // sensorArray sensor;
  uint32_t timestamp;   // timestamp packetTime;
};

struct SensorOutputLoadCell
{
  float values[4];   // sensorArray sensor;
  uint32_t timestamp;   // timestamp packetTime;
};

union PacketBuffer
{
  SensorOutput packet;
  uint8_t buffer[sizeof(SensorOutput)];
};

union PacketBufferLoadCell
{
  SensorOutputLoadCell packet;
  uint8_t buffer[sizeof(SensorOutputLoadCell)];
};

#endif