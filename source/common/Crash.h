#ifndef COMMON_CRASH_H
#define COMMON_CRASH_H

#include <source_location>

#define ASSERT(expression)                   \
        do                                   \
        {                                    \
            if (!(expression))               \
            {                                \
                crash(1);                    \
            }                                \
        } while (false);

#define ASSERT_NOT_EQUAL(condition, fail_value) \
    do                                          \
    {                                           \
        if ((condition) == (fail_value))        \
        {                                       \
            crash(1);                           \
        }                                       \
    } while (0)

#define ASSERT_EQUAL(condition, fail_value) \
    do                                      \
    {                                       \
        if ((condition) != (fail_value))    \
        {                                   \
            crash(1);                       \
        }                                   \
    } while (0)

#define ASSERT_NOT_NULL(condition) ASSERT_NOT_EQUAL((condition), nullptr)

[[noreturn]] void crash(int exit_code, const std::source_location location = std::source_location::current());

#endif // COMMON_CRASH_H
