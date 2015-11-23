// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.

#ifndef MEASUREMENT_KIT_COMMON_LIBS_HPP
#define MEASUREMENT_KIT_COMMON_LIBS_HPP

namespace measurement_kit {
namespace common {

struct Libs;

} // namespace common

common::Libs *get_global_libs();  /// Access global libs object

} // namespace measurement_kit
#endif
