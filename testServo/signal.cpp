#include "signal.h"

Signal::Signal(uint16_t minPos, uint16_t maxPos, uint8_t timeStep, uint8_t step, uint8_t pin){
  Signal::minPos=minPos;
  Signal::maxPos=maxPos;
  Signal::curPos=minPos+1;
  Signal::done=false;
  Signal::toMax=false;
  Signal::signalServo.writeMicroseconds(Signal::minPos);
  Signal::timeStep=timeStep;
  Signal::nextUpdate=timeStep;
  Signal::step=step;
  Signal::pin=(pin);
  return;
}

void Signal::init(){
  Signal::signalServo.attach(pin);
}

void Signal::toMaxPos(){
  Signal::toMax=true;
  Signal::done=false;
  return;
}

void Signal::toMinPos(){
  Signal::toMax=false;
  Signal::done=false;
  return;
}

void Signal::update(uint64_t now){
  if(!Signal::done && Signal::nextUpdate<now){
    Signal::nextUpdate=now+timeStep;
    if(Signal::toMax)
    {
      if(Signal::curPos<Signal::maxPos)
      {
        Signal::goToPos(Signal::curPos+step);
        if(Signal::curPos>=Signal::maxPos)
        {
          Signal::goToPos(Signal::maxPos);
          Signal::toMinPos();//Signal::done=true;
        }
      }
    }
    else
    {
      if(Signal::curPos>Signal::minPos)
      {
        Signal::goToPos(Signal::curPos-step);
        if(Signal::curPos<=Signal::minPos)
        {
          Signal::goToPos(Signal::minPos);
          Signal::toMaxPos();//Signal::done=true;
        }
      }
    }
  }
  return;
}

void Signal::goToPos(uint16_t pos){
  Signal::signalServo.writeMicroseconds(pos);
  Signal::curPos=pos;
}
