
#ifndef Signal_h
#define Signal_h

#include <Servo.h>
#include <inttypes.h>
#include <arduino.h>

class Signal
{
  public:
    Signal(uint16_t minPos, uint16_t maxPos, uint8_t timeStep, uint8_t step, uint8_t pin);
    void update(uint64_t now);
    void toMaxPos();
    void toMinPos();
    void init();
    
  private:
    uint16_t minPos;
    uint16_t maxPos;
    uint8_t timeStep;
    uint16_t curPos;
    uint64_t nextUpdate;
    bool toMax;
    bool done;
    uint8_t pin;
    uint8_t step;
    Servo signalServo;
    void goToPos(uint16_t pos);
};

#endif
