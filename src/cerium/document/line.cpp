#include "line.hpp"

Line::Line(std::string content, int countBefore)
    : content(content), countBefore(countBefore) {}

Line::Line(std::string content) : content(content), countBefore(0) {}

Line::Line(const Line& other)
    : content(other.content), countBefore(other.countBefore) {}

Line& Line::operator=(const Line& other) {
    content = other.content;
    countBefore = other.countBefore;
    return *this;
}