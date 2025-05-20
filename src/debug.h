#pragma once

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/// ASSERT always complains about the failed assertion, regardless of the NDEBUG
/// macro

#undef ASSERT
#define ASSERT(x, ...)                                                         \
    ({                                                                         \
        if (unlikely(!(x))) {                                                  \
            fprintf(stderr,                                                    \
                    "Assertion failed: `%s`, at %s:%s:%d. " VA_ARGS_FIRST(     \
                        __VA_ARGS__) "\n",                                     \
                    #x, __FILE__, __func__,                                    \
                    __LINE__ VA_ARGS_EXCEPT_FIRST(__VA_ARGS__));               \
            abort();                                                           \
            UNREACHABLE;                                                       \
        }                                                                      \
    })

#undef PANIC
#define PANIC(...)                                                             \
    ({                                                                         \
        fprintf(stderr, "Panic at %s:%s:%d. " VA_ARGS_FIRST(__VA_ARGS__) "\n", \
                __FILE__, __func__,                                            \
                __LINE__ VA_ARGS_EXCEPT_FIRST(__VA_ARGS__));                   \
        abort();                                                               \
        UNREACHABLE;                                                           \
    })

#undef ASSERT_EQ
#define ASSERT_EQ(x, y, fmtid, ...)                                            \
    ({                                                                         \
        typeof(x) MPROT(ASSERT_EQ_X) = (x);                                    \
        typeof(y) MPROT(ASSERT_EQ_Y) = (y);                                    \
        if (unlikely(MPROT(ASSERT_EQ_X) != MPROT(ASSERT_EQ_Y))) {              \
            fprintf(stderr,                                                    \
                    "Assertion failed: `%s`=`" fmtid                           \
                    "` is not equal to `%s`=`" fmtid                           \
                    "`, at %s:%s:%d. " VA_ARGS_FIRST(__VA_ARGS__) "\n",        \
                    #x, MPROT(ASSERT_EQ_X), #y, MPROT(ASSERT_EQ_Y), __FILE__,  \
                    __func__, __LINE__ VA_ARGS_EXCEPT_FIRST(__VA_ARGS__));     \
            abort();                                                           \
            UNREACHABLE;                                                       \
        }                                                                      \
    })

#undef ASSERT_EQ_STR
#define ASSERT_EQ_STR(x, y, ...)                                               \
    ({                                                                         \
        const char *MPROT(ASSERT_EQ_X) = (x);                                  \
        const char *MPROT(ASSERT_EQ_Y) = (y);                                  \
        if (unlikely(strcmp(MPROT(ASSERT_EQ_X), MPROT(ASSERT_EQ_Y)) != 0)) {   \
            fprintf(stderr,                                                    \
                    "Assertion failed: `%s`=`%s` is not equal to `%s`=`%s`, "  \
                    "at %s:%s:%d. " VA_ARGS_FIRST(__VA_ARGS__) "\n",           \
                    #x, MPROT(ASSERT_EQ_X), #y, MPROT(ASSERT_EQ_Y), __FILE__,  \
                    __func__, __LINE__ VA_ARGS_EXCEPT_FIRST(__VA_ARGS__));     \
            abort();                                                           \
            UNREACHABLE;                                                       \
        }                                                                      \
    })
