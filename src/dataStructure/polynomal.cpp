#include "polynomal.h"

#include <math.h>

ostream& operator <<(ostream& out,const term& t)
{
    if(fabs(t.coef) < 1e-5)return out;
    if(t.exp == 0) out << t.coef;
    if(t.exp == 1) out << t.coef << "X";
    if(t.exp > 1)  out << t.coef << "X^" << t.exp;
    return out;
}

polynomal::polynomal()
{
}
