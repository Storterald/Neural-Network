#pragma once

#include <type_traits>

#include "../math/Base.h"
#include "../math/Math.h"
#include "../math/CudaMath.h"

// Simple macro to avoid checks on math functions regarding which memory the
// data is on. This macro only works inside a class derived from Data.
#define _MATH(FOO_NAME, ...)                                                               \
        do {                                                                               \
                static_assert(std::is_base_of_v<Data, std::decay<decltype(*this)>::type>,  \
                        "_MATH macro must be called inside a function in a Data derived"   \
                        "class.");                                                         \
                if (m_size < CUDA_MINIMUM)                                                 \
                        Math::FOO_NAME(__VA_ARGS__);                                       \
                else                                                                       \
                        CudaMath::FOO_NAME(__VA_ARGS__);                                   \
        } while (false)
