#include "TTScoreCounter.hpp"
#define debug false

volatile bool ballSignalStatus  = false;
using namespace std;

#define DefaultfreqWeight 50.0 // increase this if more importance to the speed of the ball is required
#define DefaultCountWeight 20.0 // increased this if more importance to the consecutive number of balls is required
#define DefaultTimeThreshold 1000 // in ms
#define debounceThreshold 200 // in ms

void pinChangeInterruptSetup(uint8_t pin);


void pinChangeInterruptSetup(uint8_t pin)
{
  cli();
  PCMSK1 = (1<<pin); // enabling only pin change interrupt on A0.
  PCICR = (1<<PCIE1); // enabling pin change interrupt on PCINT14..8 pins (A0 - A5)
  
  /* Insert nop for synchronization*/
 // __no_operation();
/* Read port pins */
  sei();
}


ISR(PCINT1_vect){
     ballSignalStatus = true;
}





TTScoreCounter::TTScoreCounter(uint8_t pin) // Interrupt pin options: A0 - A5
{

 if(pin > A5 || pin < A0)
 {
  if(debug)
  {
    Serial.println("interrupt pin should be in the range of A0 - A5");
  }
  
  while(1);
 }
 pinChangeInterruptSetup(pin - A0);
 this->countWeight = DefaultCountWeight;
 this->freqWeight = DefaultfreqWeight;
 this->TimeThreshold = DefaultTimeThreshold;
 this->lastScore = 0;
 this->score = 0;
 this->millisValue = 0;


  

}








TTScoreCounter::TTScoreCounter(uint8_t pin , double countWeight,double freqWeight, uint16_t timeThreshold )
{ 
    pinChangeInterruptSetup(pin);
    this->freqWeight = freqWeight;
    this->countWeight = countWeight;
    this->TimeThreshold = timeThreshold;
}

bool TTScoreCounter::run()
{
    if(ballSignalStatus == true)
    {
       
        ballSignalStatus = false;
    }
    else
    {
        return false;
    }

    unsigned long timeDiff;
    timeDiff = millis() - prevBallRecvTime;
    prevBallRecvTime = millis();

    if(timeDiff < TimeThreshold)
    {
        if(timeDiff > debounceThreshold)
        {
            consecutiveBalls++;
            score += updateScore((uint32_t)timeDiff);
            if(debug){
              Serial.println("ball heard within proper time diff");
            Serial.println("time diff = " + (String)timeDiff);
            Serial.println("score = " + (String) score);
            }
            
            return true;
        }
        else
        {
            score +=0;
            return false;
        }
    }
    else{
       
        score = 0;
        consecutiveBalls = 0;
        
        return false;

    }
    
    
    


}

double TTScoreCounter::updateScore(uint32_t timeDelay)
{
    return (  (double) countWeight + (double) (1000 / timeDelay  ) * freqWeight );
}
