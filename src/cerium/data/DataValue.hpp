#ifndef CERIUM_DATA_DATAVALUE_HPP_
#define CERIUM_DATA_DATAVALUE_HPP_

#include <variant>
#include <string>
#include <cstdint>

class DataValue {
private:
    using Value = std::variant<std::nullptr_t, bool, int64_t, double, std::string>;

    Value value;

public:
    DataValue();

    DataValue(bool value);
    DataValue(int value);
    DataValue(int64_t value);
    DataValue(double value);
    DataValue(std::string value);

    template <typename T> T get() const {
        return std::get<T>(value);
    }

    template <typename T> bool is() const {
        return std::holds_alternative<T>(value);
    }
};

#endif // CERIUM_DATA_DATAVALUE_HPP_
