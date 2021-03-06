// Part of Measurement Kit <https://measurement-kit.github.io/>.
// Measurement Kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions.
#ifndef SRC_LIBMEASUREMENT_KIT_NEUBOT_DASH_HPP
#define SRC_LIBMEASUREMENT_KIT_NEUBOT_DASH_HPP

#include <measurement_kit/common/settings.hpp>

#include "src/libmeasurement_kit/common/reactor.hpp"

namespace mk {
namespace neubot {
namespace dash {

MK_DEFINE_ERR(
        MK_ERR_NEUBOT(0), MiddleboxDetectedError, "middlebox_detected_error")

void run(
        std::string measurement_server_hostname,
        std::string auth_token,
        std::string real_address,
        SharedPtr<nlohmann::json> entry,
        Settings settings,
        SharedPtr<Reactor> reactor,
        SharedPtr<Logger> logger,
        Callback<Error> callback
);

void negotiate(
        SharedPtr<nlohmann::json> entry,
        Settings settings,
        SharedPtr<Reactor> reactor,
        SharedPtr<Logger> logger,
        Callback<Error> callback
);

} // namespace dash
} // namespace neubot
} // namespace mk
#endif
