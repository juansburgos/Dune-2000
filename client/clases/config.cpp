#include <fstream>
#include <utility>
#include "config.h"
#include "yaml-cpp/yaml.h"

Config::Config() {
  this->assets = YAML::LoadFile("../assets.yaml");
}
