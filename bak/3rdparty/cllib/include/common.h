
#ifndef _COMMON_H
# define _COMMON_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# ifdef __cplusplus
#  define EXTERN_C_START extern "C" {
#  define EXTERN_C_END }
# else
#  define EXTERN_C_START /* empty */
#  define EXTERN_C_END /* empty */
#  if !defined(static_assert)
#   define static_assert _Static_assert
#  endif
# endif

# ifndef __always_inline
#  define __always_inline inline __attribute__((__always_inline__))
# endif
# ifndef __cold
#  define __cold __attribute__((__cold__))
# endif
# ifndef __noreturn
#  define __noreturn __attribute__((__noreturn__))
# endif
# ifndef __used
#  define __used __attribute__((__used__))
# endif

# define likely(expr) __builtin_expect(!!(expr), 1)
# define unlikely(expr) __builtin_expect(!!(expr), 0)

# define panic(msg) __panic(msg, __FILE__, __LINE__)
# define warn(msg) __warn(msg, __FILE__, __LINE__)
# define panic_on(expr, msg) do {	\
	if (unlikely(expr)) {		\
		panic(msg);		\
	}				\
} while (false)

EXTERN_C_START

__cold __noreturn void __panic(const char *msg, const char *file, unsigned long line);
__cold void __warn(const char *msg, const char *file, unsigned long line);

EXTERN_C_END

#endif /* _COMMON_H */
