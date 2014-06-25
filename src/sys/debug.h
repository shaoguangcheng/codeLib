#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdio.h>
#include <stdlib.h>

namespace csg {
    void _debug_()
    {
        printf("compiled : ",__DATE__," at ", _TIME__,"\n");
        printf("this is line %d of file %s\n",__LINE__,__FILE__);
    }
}
#endif //_DEBUG_H_SS
