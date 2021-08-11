// SPDX-License-Identifier: BSD-3-Clause

#ifndef SFCMM_COMMON_H
#define SFCMM_COMMON_H
namespace sfcmm {
static constexpr int MAX_DIM = 4;
}

#include "common/compiler_config.h"
#include "common/globalmpi.h"
#include "common/macros.h"
#include "common/log.h"
#include "common/sfcmm_types.h"

#include "common/util/backtrace.h"
#include "common/util/string_helper.h"
#include "common/util/sys.h"

#include "common/math/cartesian.h"
#include "common/math/hilbert.h"
#include "common/math/mathfunctions.h"

#endif //SFCMM_COMMON_H