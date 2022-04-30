#ifndef _DEBUG_HH_
#define _DEBUG_HH_

#if PRINT_LOGS == 1
#define D(x) x;
#else
#define D(x) ;
#endif

#endif
