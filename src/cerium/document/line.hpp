#ifndef CERIUM_DOCUMENT_LINE_HPP_
#define CERIUM_DOCUMENT_LINE_HPP_

#include <string>

struct Line {
    Line(std::string content, int countBefore);
    Line(std::string content);
    Line(const Line& other);

    Line& operator=(const Line& other);

    std::string content;
    int countBefore;
};

#endif