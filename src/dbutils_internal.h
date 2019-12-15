/*
 * dbutils_internal.h
 *
 *  Created on: Dec 13, 2019 at 10:07:22 PM
 *      Author: Dennnis Bonke
 */

#ifndef LIB_DBUTILS_H_
#error "Don't include me directly!"
#endif
#ifdef __cplusplus
extern "C" {
#endif
#ifndef LIB_DBUTILS_INTERNAL_H_
#define LIB_DBUTILS_INTERNAL_H_

#define DBUTILS_VERSION "v1.1.0"
#define DBUTILS_BUILD_DATE __DATE__
#define DBUTILS_BUILD_TIME __TIME__
#define DBUTILS_SOURCE "https://github.com/Dennisbonke/libdbutil"
#define DBUTILS_LICENSE_URL "https://www.gnu.org/licenses/gpl-3.0.en.html"

#if (defined(__GNUC__) || defined(__GNUG__)) && !(defined(__clang__) || defined(__INTEL_COMPILER))
# define COMPILER_VERSION "gcc " __VERSION__
#elif (defined(__clang__))
# define COMPILER_VERSION "clang " __clang_version__
#else
# define COMPILER_VERSION "unknown-compiler how-did-you-do-that"
#endif
#define DBUTILS_COMPILER COMPILER_VERSION

#if defined(__i386__)
#define TARGET_ARCH "i386 - Intel / AMD 32-bit"
#elif defined(__amd64__)
#define TARGET_ARCH "AMD64 - Intel / AMD 64-bit"
#elif defined(__arm__)
#define TARGET_ARCH "ARM"
#else
#define TARGET_ARCH "How did you do that?"
#warning "Please add your architecture identification to the list"
#endif

#define DBUTILS_ARCH TARGET_ARCH

#endif /* LIB_DBUTILS_INTERNAL_H_ */
#ifdef __cplusplus
}
#endif
