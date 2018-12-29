// Part of Measurement Kit <https://measurement-kit.github.io/>.
// Measurement Kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions.

#include <measurement_kit/internal/model/model.hpp>
#include <measurement_kit/common/nlohmann/json.hpp>

#include <stdexcept>

namespace mk {
namespace internal {
namespace model {

void TaskName::check() {
#define XX(Name) \
  if (value == #Name) return;
  MK_INTERNAL_MODEL_ENUM_TASKS(XX)
#undef XX
  std::string reason = "invalid task name: '";
  reason += value;
  reason += "'. FYI valid task names are:";
#define XX(Name)     \
  do {               \
    reason += " ";   \
    reason += #Name; \
  } while (0);
  MK_INTERNAL_MODEL_ENUM_TASKS(XX)
#undef XX
  throw std::runtime_error(reason);
}

void LogLevel::check() {
#define XX(Name) \
  if (value == #Name) return;
  MK_INTERNAL_MODEL_ENUM_LOG_LEVELS(XX)
#undef XX
  std::string reason = "invalid log level name: '";
  reason += value;
  reason += "'. FYI valid log level names are:";
#define XX(Name)     \
  do {               \
    reason += " ";   \
    reason += #Name; \
  } while (0);
  MK_INTERNAL_MODEL_ENUM_LOG_LEVELS(XX)
#undef XX
  throw std::runtime_error(reason);
}

// LOAD parses the variable named @p Name with JSON prefix @p Prefix
// that may be @p Mandatory with C++ type @p Type into the current class
// assuming that the input nlohmann::json instance is named `doc`.
#define LOAD(Type, Mandatory, Prefix, Name)                      \
  do {                                                           \
    std::string path = Prefix;                                   \
    path += #Name;                                               \
    auto pointer = nlohmann::json::json_pointer{path};           \
    try {                                                        \
      auto entry = doc.at(pointer);                              \
      try {                                                      \
        entry.get_to(Name.value);                                \
        Name.check();                                            \
        Name.present = true;                                     \
      } catch (const std::exception &exc) {                      \
        *logs += "error: while reading key at JSON path '";      \
        *logs += path;                                           \
        *logs += "' this error occurred: ";                      \
        *logs += exc.what();                                     \
        *logs += ".\n";                                          \
        return false;                                            \
      }                                                          \
    } catch (const std::exception &) {                           \
      if (Mandatory) {                                           \
        *logs += "error: missing mandatory key at JSON path: '"; \
        *logs += path;                                           \
        *logs += "'.\n";                                         \
        return false;                                            \
      }                                                          \
    }                                                            \
  } while (0);

// DUMP dumps the variable named @p Name with JSON prefix @p Prefix
// that may be @p Mandatory with C++ type @p Type from the current class
// assuming that the output nlohmann::json instance is named `doc`.
#define DUMP(Type, Mandatory, Prefix, Name)                 \
  do {                                                      \
    if (Mandatory && !Name.present) {                       \
      *logs += "error: mandatory key: '";                   \
      *logs += #Name;                                       \
      *logs += "' is not set.\n";                           \
      return false;                                         \
    }                                                       \
    if (Name.present) {                                     \
      std::string path = Prefix;                            \
      path += #Name;                                        \
      try {                                                 \
        auto pointer = nlohmann::json::json_pointer{path};  \
        Name.check();                                       \
        doc[pointer] = Name.value;                          \
      } catch (const std::exception &exc) {                 \
        *logs += "error: while writing key at JSON path '"; \
        *logs += path;                                      \
        *logs += "' this error occurred: ";                 \
        *logs += exc.what();                                \
        *logs += ".\n";                                     \
        return false;                                       \
      }                                                     \
    }                                                       \
  } while (0);

// LOADS implements loads for @p ClassName using @p Macro as the
// XX-list of variables belonging to @p ClassName
#define LOADS(ClassName, Macro)                                      \
  bool ClassName::loads(const std::string &str, std::string *logs) { \
    if (logs == nullptr) return false;                               \
    *this = {}; /* start over */                                     \
    nlohmann::json doc;                                              \
    try {                                                            \
      doc = nlohmann::json::parse(str);                              \
    } catch (const std::exception &exc) {                            \
      *logs += "error: ";                                            \
      *logs += exc.what();                                           \
      *logs += ".\n";                                                \
      return false;                                                  \
    }                                                                \
    Macro(LOAD) return true;                                         \
  }

// DUMPS is like LOADS but dumps rather than loading.
#define DUMPS(ClassName, Macro)                                \
  bool ClassName::dumps(std::string *str, std::string *logs) { \
    if (str == nullptr || logs == nullptr) return false;       \
    nlohmann::json doc;                                        \
    Macro(DUMP) try {                                          \
      *str = doc.dump();                                       \
    } catch (const std::exception &exc) {                      \
      *logs += "error: ";                                      \
      *logs += exc.what();                                     \
      *logs += ".\n";                                          \
      return false;                                            \
    }                                                          \
    return true;                                               \
  }

LOADS(Settings, MK_INTERNAL_MODEL_ENUM_SETTINGS)

DUMPS(Settings, MK_INTERNAL_MODEL_ENUM_SETTINGS)

LOADS(Event, MK_INTERNAL_MODEL_ENUM_EVENT_FIELDS)

DUMPS(Event, MK_INTERNAL_MODEL_ENUM_EVENT_FIELDS)

}  // namespace model
}  // namespace internal
}  // namespace mk
