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

#endif /* LIB_DBUTILS_H_ */
#ifdef __cplusplus
}
#endif
