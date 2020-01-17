/*
 * libdbutil.cpp
 *
 *  Created on: Dec 13, 2019 at 19:56:15 PM
 *      Author: Dennnis Bonke
 */

#include <stdio.h>
#include <stdlib.h>

#include "db_utils.h"

/*
 * Version information
 */
void dbutils_version(void) {
	fprintf(stdout, "This is 'dbutils' version %s, build on %s at %s, with %s for architecture %s.\n", DBUTILS_VERSION, DBUTILS_BUILD_DATE, DBUTILS_BUILD_TIME, DBUTILS_COMPILER, DBUTILS_ARCH);
}

/*
 * About info
 */
void dbutils_about(void) {
	dbutils_version();
	fprintf(stdout, "'dbutils' is a library with useful code snippets to use in open source projects.\n"
					"It was made for use in college, where there was a lot of code duplication.\n"
					"'dbutils' is made by Dennis Bonke.\n"
					"'dbutils' is licensed under the GNU GPLv3, which can be found here: %s.\n"
					"The source code of 'dbutils' can be found here: %s.\n"
					"Copyright (c) 2019 - 2020\n", DBUTILS_LICENSE_URL, DBUTILS_SOURCE);
}

/*
 * Random with limits
 */
int lrandom(int min, int max) {
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

int db_is_prime(unsigned int m) {
   unsigned int i, j;
   if(m < 2) return 0;
   if(m == 2) return 1;
   if(!(m & 1)) return 0;
   if(m % 3 == 0) return (m == 3);
   for(i = 5; (j = i * i), j <= m && j > i; i += 6) {
      if(m % i == 0) return 0;
      if(m % (i + 2) == 0) return 0;
   }
   return 1;
}

int db_is_pow2(size_t n) {
   return (n & (n - 1)) == 0;
}
