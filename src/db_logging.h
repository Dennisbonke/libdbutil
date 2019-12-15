/*
 * db_logging.h
 *
 *  Created on: Dec 13, 2019 at 10:41:33 PM
 *      Author: Dennnis Bonke
 */

#ifdef __cplusplus
extern "C" {
#endif
#ifndef LIB_DBUTILS_LOGGING_H_
#define LIB_DBUTILS_LOGGING_H_

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {
	DEBUGGING = 0, /* Debug only */
	INFO, 	 	   /* Unimportant */
	NOTICE,    	   /* Important, but not bad */
	WARNING,	   /* Not what was expected, but still okay */
	ERROR,	       /* This is bad... */
	CRITICAL,	   /* Shit */
	INSANE		   /* We're dead */
} log_type_t;

extern log_type_t log_level;
extern void _log(char *title, int line_no, log_type_t level, const char *fmt, ...);
extern void set_log_level(log_type_t level);
extern log_type_t get_log_level(void);

#define debug_log(level, ...) _log(__FILE__, __LINE__, level, __VA_ARGS__)

#endif /* LIB_DBUTILS_LOGGING_H_ */

#ifdef __cplusplus
}
#endif
