/*
 * dblogging.cpp
 *
 *  Created on: Dec 13, 2019 at 10:28:31 PM
 *      Author: Dennnis Bonke
 */

#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include "db_logging.h"

static void print_dec(unsigned int value, unsigned int width, char * buf, int * ptr ) {
	unsigned int n_width = 1;
	unsigned int i = 9;
	while (value > i && i < UINT32_MAX) {
		n_width += 1;
		i *= 10;
		i += 9;
	}

	int printed = 0;
	while (n_width + printed < width) {
		buf[*ptr] = '0';
		*ptr += 1;
		printed += 1;
	}

	i = n_width;
	while (i > 0) {
		unsigned int n = value / 10;
		int r = value % 10;
		buf[*ptr + i - 1] = r + '0';
		i--;
		value = n;
	}
	*ptr += n_width;
}

/*
 * Hexadecimal to string
 */
static void print_hex(unsigned int value, unsigned int width, char * buf, int * ptr) {
	int i = width;

	if (i == 0) i = 8;

	unsigned int n_width = 1;
	unsigned int j = 0x0F;
	while (value > j && j < UINT32_MAX) {
		n_width += 1;
		j *= 0x10;
		j += 0x0F;
	}

	while (i > (int)n_width) {
		buf[*ptr] = '0';
		*ptr += 1;
		i--;
	}

	i = (int)n_width;
	while (i-- > 0) {
		buf[*ptr] = "0123456789abcdef"[(value>>(i*4))&0xF];
		*ptr += + 1;
	}
}

/*
 * vasprintf()
 */
static size_t xvasprintf(char * buf, const char * fmt, va_list args) {
	int i = 0;
	char * s;
	char * b = buf;
	for (const char *f = fmt; *f; f++) {
		if (*f != '%') {
			*b++ = *f;
			continue;
		}
		++f;
		unsigned int arg_width = 0;
		while (*f >= '0' && *f <= '9') {
			arg_width *= 10;
			arg_width += *f - '0';
			++f;
		}
		/* fmt[i] == '%' */
		switch (*f) {
			case 's': /* String pointer -> String */
				s = (char *)va_arg(args, char *);
				if (s == NULL) {
					s = "(null)";
				}
				while (*s) {
					*b++ = *s++;
				}
				break;
			case 'c': /* Single character */
				*b++ = (char)va_arg(args, int);
				break;
			case 'x': /* Hexadecimal number */
				i = b - buf;
				print_hex((unsigned long)va_arg(args, unsigned long), arg_width, buf, &i);
				b = buf + i;
				break;
			case 'd': /* Decimal number */
				i = b - buf;
				print_dec((unsigned long)va_arg(args, unsigned long), arg_width, buf, &i);
				b = buf + i;
				break;
			case '%': /* Escape */
				*b++ = '%';
				break;
			default: /* Nothing at all, just dump it */
				*b++ = *f;
				break;
		}
	}
	/* Ensure the buffer ends in a null */
	*b = '\0';
	return b - buf;

}

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

char date_time_buf[26];
char time_buf[26];

char *get_date_time(void) {
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

	strftime(date_time_buf, 26, "%d:%m:%Y %H:%M:%S", tm_info);
	return date_time_buf;
}

struct tm *get_time(void) {
	int millisec;
	struct tm *tm_info;
	struct timeval tv;

	gettimeofday(&tv, NULL);

	millisec = lrint(tv.tv_usec / 1000.0); // Round to nearest millisec
	if(millisec >= 1000) { // Rounding up to nearest second
		millisec -= 1000;
		tv.tv_sec++;
	}

	return tm_info = localtime(&tv.tv_sec);

	//strftime(time_buf, 26, "%Y:%m:%d %H:%M:%S", tm_info);
	//return time_buf;
}

void _log(char *title, int line_no, log_type_t level, const char *fmt, ...) {
	if (level >= log_level) {
		int last_errno = errno;
		char buffer[1024];
		char *err_text = NULL;
		va_list args;
		va_start(args, fmt);
		xvasprintf(buffer, fmt, args);
		va_end(args);

		char *type;
		if (level > INSANE) {
			type = "";
		} else {
			type = c_messages[level];
		}

		if(last_errno) {
			err_text = strerror(last_errno);
		}

		if(level > WARNING) {
			if(last_errno) {
				fprintf(stderr, "[%s:%s:%d]%s %s, errno: %d - %s", get_date_time(), title, line_no, type, (char *)buffer, last_errno, err_text);
			} else {
				fprintf(stderr, "[%s:%s:%d]%s %s", get_date_time(), title, line_no, type, (char *)buffer);
			}
		} else {
			if(last_errno) {
				fprintf(stdout, "[%s:%s:%d]%s %s, errno: %d - %s", get_date_time(), title, line_no, type, (char *)buffer, last_errno, err_text);
			} else {
				fprintf(stdout, "[%s:%s:%d]%s %s", get_date_time(), title, line_no, type, (char *)buffer);
			}
		}

		errno = last_errno = 0;

	}
	/* else ignore */
}

void set_log_level(log_type_t level) {
	log_level = level;
}

log_type_t get_log_level(void) {
	return log_level;
}
