#ifndef COMMON_CRASH_H
#define COMMON_CRASH_H

#define CRASH(exit_code) \
    do                   \
    {                    \
        internal_crash(__FILE__, __LINE__, (exit_code)); \
    } while (0)

#define ASSERT(expression)                   \
        do                                   \
        {                                    \
            if (!(expression))               \
            {                                \
                CRASH(1);                    \
            }                                \
        } while (false);

#define ASSERT_NOT_EQUAL(condition, fail_value) \
    do                                          \
    {                                           \
        if ((condition) == (fail_value))        \
        {                                       \
            CRASH(1);                           \
        }                                       \
    } while (0)

#define ASSERT_EQUAL(condition, fail_value) \
    do                                      \
    {                                       \
        if ((condition) != (fail_value))    \
        {                                   \
            CRASH(1);                       \
        }                                   \
    } while (0)

#define ASSERT_NOT_NULL(condition) ASSERT_NOT_EQUAL((condition), nullptr)

// TODO: Noreturn attribute
void internal_crash(const char *file, int line, int exit_code);

#endif // COMMON_CRASH_H
