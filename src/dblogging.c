/*
 * dblogging.cpp
 *
 *  Created on: Dec 13, 2019 at 10:28:31 PM
 *      Author: Dennnis Bonke
 */

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include "db_logging.h"

// Default log level
log_type_t log_level = DEBUGGING;

/*
 * Log levels for messages
 */
static char *c_messages[] = {
	" \033[1;32mDEBUG\033[0m:",
	" \033[1;34mINFO\033[0m:",
	" \033[1;35mNOTICE\033[0m:",
	" \033[1;33mWARNING\033[0m:",
	" \033[1;31mERROR\033[0m:",
	" \033[1;37;41mCRITICAL\033[0m:",
	" \033[1;31;44mINSANE\033[0m:"
};

char time_buf[26];

char *get_time(void) {
	int millisec;
	struct tm *tm_info;
	struct timeval tv;

	gettimeofday(&tv, NULL);

	millisec = lrint(tv.tv_usec / 1000.0); // Round to nearest millisec
	if(millisec >= 1000) { // Rounding up to nearest second
		millisec -= 1000;
		tv.tv_sec++;
	}

	tm_info = localtime(&tv.tv_sec);

	strftime(time_buf, 26, "%Y:%m:%d %H:%M:%S", tm_info);
	return time_buf;
}

void _log(char *title, int line_no, log_type_t level, char *fmt, ...) {
	if (level >= log_level) {
		char buffer[1024];
		va_list args;
		va_start(args, fmt);
		vsprintf(buffer, fmt, args);
		va_end(args);

		char *type;
		if (level > INSANE) {
			type = "";
		} else {
			type = c_messages[level];
		}

		if(level > WARNING) {
			fprintf(stderr, "[%s:%s:%d]%s %s\n", get_time()/*"nope"*/, title, line_no, type, buffer);
		} else {
			fprintf(stdout, "[%s:%s:%d]%s %s\n", get_time()/*"nope"*/, title, line_no, type, buffer);
		}

	}
	/* else ignore */
}

void set_log_level(log_type_t level) {
	log_level = level;
}
