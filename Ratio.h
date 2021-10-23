#ifndef _RATIO_H_
#define _RATIO_H_

class Ratio
{
  public:
    Ratio(int numerator, int denominator);    
    virtual ~Ratio();

    int numerator;
    int denominator;
};

#endif
