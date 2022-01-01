#include "Arduino.h"





class TTScoreCounter
{

    
    double score;
    double lastScore;
    uint16_t TimeThreshold;
    bool prevBallRecvStatus;
    uint32_t prevBallRecvTime;
    uint32_t consecutiveBalls;
    double freqWeight, countWeight;
    double updateScore(uint32_t timeDelay);
    uint32_t millisValue;
    
    public:
    TTScoreCounter(uint8_t pin);
    TTScoreCounter(uint8_t pin, double timeWeight,double freqWeight, uint16_t timeThreshold );
    bool run();
    double getScore() { return score;}
    uint32_t getConsecutiveBalls() { return consecutiveBalls;}


  




};
