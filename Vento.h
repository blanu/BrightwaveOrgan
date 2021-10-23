#ifndef _VENTO_H_
#define _VENTO_H_

#include "Ratio.h"
#include "Stela.h"

class Vento
{
  public:
    Vento(bool rising);
    Vento(bool rising, int tri, int kvin);
    virtual ~Vento();

    bool rising;
    int tri;
    int kvin;

    Ratio getRatio();
    Stela getStela(Stela fundamental);
    Stela getRising(Stela fundamental, Stela reference);
    Stela getFalling(Stela fundamental, Stela reference);
    Stela getTone(Stela fundamental, Stela reference);

    void shiftTri(int shift);
    void shiftKvin(int shift);

  private:
};

#endif
