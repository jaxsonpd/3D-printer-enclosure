#include <stdbool.h>
#include <stdint.h>

#include "fff.h"


#ifdef FFF_MOCK_IMPL
#define VOID_FUNC FAKE_VOID_FUNC
#define VALUE_FUNC FAKE_VALUE_FUNC
#else
#define VOID_FUNC DECLARE_FAKE_VOID_FUNC
#define VALUE_FUNC DECLARE_FAKE_VALUE_FUNC
#endif

#define FFF_CLEAR_FAKES_LIST(FUNC) \
    FUNC(example_func)

VALUE_FUNC(int32_t, example_func, uint16_t, char **)