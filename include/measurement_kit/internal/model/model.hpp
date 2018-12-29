// Part of Measurement Kit <https://measurement-kit.github.io/>.
// Measurement Kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions.
#ifndef MEASUREMENT_KIT_INTERNAL_MODEL_MODEL_HPP
#define MEASUREMENT_KIT_INTERNAL_MODEL_MODEL_HPP

#include <map>
#include <string>
#include <vector>

namespace mk {
namespace internal {
namespace model {

class StringMap {
 public:
  bool present = false;

  std::map<std::string, std::string> value;

  void check() {}
};

class StringVector {
 public:
  bool present = false;

  std::vector<std::string> value;

  void check() {}
};

class String {
 public:
  bool present = false;

  std::string value;

  void check() {}
};

class Int64 {
 public:
  bool present = false;

  int64_t value = 0;

  void check() {}
};

class Bool {
 public:
  bool present = false;

  bool value = 0;

  void check() {}
};

class Float64 {
 public:
  bool present = false;

  double value = 0.0;

  void check() {}
};

#define MK_INTERNAL_MODEL_ENUM_TASKS(XX) \
  XX(Dash)                               \
  XX(CaptivePortal)                      \
  XX(DnsInjection)                       \
  XX(FacebookMessenger)                  \
  XX(HttpHeaderFieldManipulation)        \
  XX(HttpInvalidRequestLine)             \
  XX(MeekFrontedRequests)                \
  XX(MultiNdt)                           \
  XX(Ndt)                                \
  XX(TcpConnect)                         \
  XX(Telegram)                           \
  XX(WebConnectivity)                    \
  XX(Whatsapp)

class TaskName : public String {
 public:
  void check();
};

#define MK_INTERNAL_MODEL_ENUM_LOG_LEVELS(XX) \
  XX(ERR)                                     \
  XX(WARNING)                                 \
  XX(INFO)                                    \
  XX(DEBUG)                                   \
  XX(DEBUG2)

class LogLevel : public String {
 public:
  void check();
};

#define MK_INTERNAL_MODEL_ENUM_SETTINGS(XX)          \
  XX(StringMap, false, "/", annotations)             \
  XX(StringVector, false, "/", disabled_events)      \
  XX(StringVector, false, "/", inputs)               \
  XX(LogLevel, false, "/", log_level)                \
  XX(TaskName, true, "/", name)                      \
  XX(Bool, false, "/options/", all_endpoints)        \
  XX(String, false, "/options/", ca_bundle_path)     \
  XX(String, false, "/options/", geoip_asn_path)     \
  XX(String, false, "/options/", geoip_country_path) \
  XX(Int64, false, "/options/", max_runtime)         \
  XX(Bool, false, "/options/", no_collector)         \
  XX(Int64, false, "/options/", port)                \
  XX(Bool, false, "/options/", save_real_probe_asn)  \
  XX(Bool, false, "/options/", save_real_probe_cc)   \
  XX(Bool, false, "/options/", save_real_probe_ip)   \
  XX(String, false, "/options/", server)             \
  XX(String, false, "/options/", software_name)      \
  XX(String, false, "/options/", software_version)

class Settings {
 public:
#define XX(Type, Mandatory, Prefix, Name) Type Name;
  MK_INTERNAL_MODEL_ENUM_SETTINGS(XX)
#undef XX

  bool loads(const std::string &str, std::string *logs);

  bool dumps(std::string *str, std::string *logs);
};

#define MK_INTERNAL_MODEL_ENUM_EVENT_FIELDS(XX)    \
  XX(String, true, "/", key)                       \
  XX(String, false, "/value/", direction)          \
  XX(Float64, false, "/value/", downloaded_kb)     \
  XX(Float64, false, "/value/", elapsed)           \
  XX(String, false, "/value/", failure)            \
  XX(Int64, false, "/value/", idx)                 \
  XX(String, false, "/value/", input)              \
  XX(String, false, "/value/", json_str)           \
  XX(String, false, "/value/", log_level)          \
  XX(String, false, "/value/", message)            \
  XX(Int64, false, "/value/", num_streams)         \
  XX(Float64, false, "/value/", uploaded_kb)       \
  XX(Float64, false, "/value/", percentage)        \
  XX(String, false, "/value/", probe_asn)          \
  XX(String, false, "/value/", probe_cc)           \
  XX(String, false, "/value/", probe_ip)           \
  XX(String, false, "/value/", probe_network_name) \
  XX(String, false, "/value/", report_id)          \
  XX(String, false, "/value/", resolver_ip)        \
  XX(Float64, false, "/value/", speed_kbps)        \
  XX(String, false, "/value/", status)             \
  XX(String, false, "/value/", url)

class Event {
 public:
#define XX(Type, Mandatory, Prefix, Name) Type Name;
  MK_INTERNAL_MODEL_ENUM_EVENT_FIELDS(XX)
#undef XX

  bool loads(const std::string &str, std::string *logs);

  bool dumps(std::string *str, std::string *logs);
};

}  // namespace model
}  // namespace internal
}  // namespace mk
#endif
