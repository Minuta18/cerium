#include "DataValue.hpp"
#include <cstdint>

DataValue::DataValue() : value(nullptr) {}

DataValue::DataValue(bool value) : value(value) {}

DataValue::DataValue(int value) : value(static_cast<int64_t>(value)) {}

DataValue::DataValue(int64_t value) : value(value) {}

DataValue::DataValue(double value) : value(value) {}

DataValue::DataValue(std::string value) : value(std::move(value)) {}
