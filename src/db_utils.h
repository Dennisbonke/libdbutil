/*
 * test.h
 *
 *  Created on: Dec 13, 2019 at 9:45:23 PM
 *      Author: Dennnis Bonke
 */

#ifdef __cplusplus
extern "C" {
#endif
#ifndef LIB_DBUTILS_H_
#define LIB_DBUTILS_H_

#include "dbutils_internal.h"
#include <stdlib.h>

/*
 * Version information
 */
extern void dbutils_version(void);
/*
 * About info
 */
extern void dbutils_about(void);
/*
 * Random with limits
 */
extern int lrandom(int min, int max);

extern char *get_date_time(void);
extern struct tm *get_time(void);

#define db_min(a,b)   ((a) < (b) ? (a) : (b))
#define db_max(a,b)   ((a) > (b) ? (a) : (b))

#if !defined(__cplusplus) && !defined(min) && !defined(max)
     #define min(x,y) db_min(x,y)
     #define max(x,y) db_max(x,y)
#endif

extern int db_is_prime(unsigned int m);

extern int db_is_pow2(size_t n);

#endif /* LIB_DBUTILS_H_ */
#ifdef __cplusplus
}
#endif
