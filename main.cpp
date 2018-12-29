#include "src/libmeasurement_kit/internal/model/model.cpp"

#include <iostream>

int main() {

#if 1
  auto input_settings = R"({
    "annotations": {"a": "b", "c": "17"},
    "name": "Ndt",
    "log_level": "WARNING"
  })";
  mk::internal::model::Settings settings;
  std::string logs;
  auto rv = settings.loads(input_settings, &logs);
  std::clog << std::boolalpha << rv << std::endl;
  std::clog << logs;

  settings.log_level.value = "ANTANI";

  std::string output_settings;
  logs = "";
  rv = settings.dumps(&output_settings, &logs);
  std::clog << std::boolalpha << rv << std::endl;
  std::clog << logs;
  std::clog << output_settings << std::endl;
#endif

#if 0
  auto input_settings = R"({
    "annotations": {"a": "b", "c": "17"},
    "key": "status.update.performance",
    "value": {
      "elapsed": 17
    }
  })";
  mk::internal::model::Event event;
  std::string logs;
  auto rv = event.loads(input_settings, &logs);
  std::clog << std::boolalpha << rv << std::endl;
  std::clog << logs;

  std::string output_settings;
  logs = "";
  rv = event.dumps(&output_settings, &logs);
  std::clog << std::boolalpha << rv << std::endl;
  std::clog << logs;
  std::clog << output_settings << std::endl;
#endif

}
