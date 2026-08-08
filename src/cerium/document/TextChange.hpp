#ifndef CERIUM_TEXT_TEXTCHANGE_HPP_
#define CERIUM_TEXT_TEXTCHANGE_HPP_

#include <cstddef>
#include <string>

enum class ChangeType { Insert, Delete };

struct TextChange {
    ChangeType type;

    size_t line;
    size_t column;

    std::string text;
};

#endif // CERIUM_TEXT_TEXTCHANGE_HPP_
