#ifndef _VENTO_H_
#define _VENTO_H_

#include "Ratio.h"
#include "Stela.h"

class Vento
{
  public:
    Vento();
    Vento(int du, int tri, int kvin, int sep);
    virtual ~Vento();

    int du;
    int tri;
    int kvin;
    int sep;

    Ratio getRatio();
    Stela getStela(Stela fundamental);
    Stela getRising(Stela fundamental, Stela reference);
    Stela getFalling(Stela fundamental, Stela reference);
    Stela getTone(Stela fundamental);

    void shiftTri(int shift);
    void shiftKvin(int shift);

    bool operator==(const Vento& rhs) const;
    bool operator!=(const Vento& rhs) const;

  private:
};

#endif
