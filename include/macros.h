#ifndef __MACROS_H_
#define __MACROS_H_

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif

#define OK 0
#define FAIL -1

#ifndef DPSIZE              // Size of disk page
#define DPSIZE (1 << 12)    // 4 KiB
#endif

#ifndef CACHESIZE           // Size of the LRU cache
#define CACHESIZE (1 << 28) // 256 MiB
#endif

#ifndef CACHELENGTH          
#define CACHELENGTH (CACHESIZE/sizeof(diskPage))
#endif

#ifndef LOT                 // Length of transmition 
#define LOT (1 << 10)       // 1 KiB
#endif

#ifndef DATAFILE
#define DATAFILE "/mnt/garbage/garbage10"
#endif

#ifndef PORT 
#define PORT 19999
#endif

#ifndef NSERVERS
#define NSERVERS 39
#endif

#ifndef HOST
#define HOST "10.20.12.170"
#endif

#ifndef ALPHA
#define ALPHA 0.03f
#endif


#endif
