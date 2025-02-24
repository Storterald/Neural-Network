#pragma once

#include <cstdint>

#include "../math/Base.h"
#include "../math/Math.h"
#include "../math/CudaMath.h"

// Logger included anyway since it's used for Logger::fatal_error.
#include "../utils/Logger.h"

// PPO related constants.
constexpr float CLIP_EPSILON { 2e-1f };
constexpr float GAMMA { 0.99f };
constexpr float LAMBDA { 0.95f };