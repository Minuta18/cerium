#include "VectorStorage.hpp"

#include <ranges>
#include <stdexcept>

namespace cerium::document {

VectorStorage::VectorStorage() {
    text.emplace_back("");
    rebuildTotalLength();
}

VectorStorage::VectorStorage(std::string_view content) {
    if (content.empty()) {
        text.emplace_back("");
    } else {
        auto lines = content | std::views::split('\n');
        text = std::ranges::to<std::vector<Line>>(
            lines | std::views::transform([](auto&& line) {
                return Line(std::string(line.begin(), line.end()));
            }));
    }
    rebuildCountBefore();
    rebuildTotalLength();
}

std::size_t VectorStorage::length() const {
    return totalLength;
}

char VectorStorage::charAt(std::size_t pos) const {
    if (pos >= totalLength) {
        throw std::out_of_range("VectorStorage::charAt: pos out of range");
    }
    std::size_t offset = 0;
    for (const auto& line : text) {
        if (pos < offset + line.content.size()) {
            return line.content[pos - offset];
        }
        offset += line.content.size() + 1;
    }
    throw std::out_of_range("VectorStorage::charAt: pos out of range");
}

std::string VectorStorage::substring(std::size_t begin, std::size_t end) const {
    if (begin > end || end > totalLength) {
        throw std::out_of_range("VectorStorage::substring: invalid range");
    }
    std::string result;
    result.reserve(end - begin);

    std::size_t pos = 0;
    for (std::size_t i = 0; i < text.size(); ++i) {
        const auto& content = text[i].content;
        std::size_t lineStart = pos;
        std::size_t lineEnd = lineStart + content.size();

        if (lineEnd >= begin && lineStart < end) {
            std::size_t from = begin > lineStart ? begin - lineStart : 0;
            std::size_t to = end < lineEnd ? end - lineStart : content.size();
            result.append(content, from, to - from);
        }

        if (i + 1 < text.size() && lineEnd + 1 > begin && lineEnd < end) {
            result.push_back('\n');
        }

        pos = lineEnd + 1;
    }
    return result;
}

void VectorStorage::insert(std::size_t pos, std::string_view text_view) {
    if (pos > totalLength) {
        throw std::out_of_range("VectorStorage::insert: pos out of range");
    }
    if (text_view.empty()) {
        return;
    }

    auto [line, column] = posToLineColumn(pos);

    std::string buffer = text[line].content;
    buffer.insert(column, text_view);

    std::vector<Line> newLines;
    auto split = buffer | std::views::split('\n');
    newLines = std::ranges::to<std::vector<Line>>(
        split | std::views::transform([](auto&& part) {
            return Line(std::string(part.begin(), part.end()));
        }));

    text.erase(text.begin() + static_cast<std::ptrdiff_t>(line));
    text.insert(text.begin() + static_cast<std::ptrdiff_t>(line),
                newLines.begin(), newLines.end());

    rebuildCountBefore();
    rebuildTotalLength();
}

void VectorStorage::erase(std::size_t begin, std::size_t end) {
    if (begin > end || end > totalLength) {
        throw std::out_of_range("VectorStorage::erase: invalid range");
    }
    if (begin == end) {
        return;
    }

    std::string before = substring(0, begin);
    std::string after = substring(end, totalLength);
    std::string joined = before + after;

    text.clear();
    if (joined.empty()) {
        text.emplace_back("");
    } else {
        auto lines = joined | std::views::split('\n');
        text = std::ranges::to<std::vector<Line>>(
            lines | std::views::transform([](auto&& line) {
                return Line(std::string(line.begin(), line.end()));
            }));
    }

    rebuildCountBefore();
    rebuildTotalLength();
}

void VectorStorage::clear() {
    text.clear();
    text.emplace_back("");
    rebuildCountBefore();
    rebuildTotalLength();
}

std::size_t VectorStorage::lineCount() const {
    return text.size();
}

std::string VectorStorage::lineAt(std::size_t lineIndex) const {
    if (lineIndex >= text.size()) {
        throw std::out_of_range("VectorStorage::lineAt: index out of range");
    }
    return text[lineIndex].content;
}

std::size_t VectorStorage::lineLength(std::size_t lineIndex) const {
    if (lineIndex >= text.size()) {
        throw std::out_of_range("VectorStorage::lineLength: index out of range");
    }
    return text[lineIndex].content.size();
}

std::pair<std::size_t, std::size_t>
VectorStorage::posToLineColumn(std::size_t pos) const {
    if (pos > totalLength) {
        throw std::out_of_range("VectorStorage::posToLineColumn: pos out of range");
    }
    std::size_t offset = 0;
    for (std::size_t i = 0; i < text.size(); ++i) {
        std::size_t lineEnd = offset + text[i].content.size();
        if (pos <= lineEnd) {
            return {i, pos - offset};
        }
        offset = lineEnd + 1;
    }
    return {text.size() - 1, text.back().content.size()};
}

std::size_t VectorStorage::lineColumnToPos(std::size_t line, std::size_t column) const {
    if (line >= text.size()) {
        throw std::out_of_range("VectorStorage::lineColumnToPos: line out of range");
    }
    if (column > text[line].content.size()) {
        throw std::out_of_range("VectorStorage::lineColumnToPos: column out of range");
    }
    std::size_t pos = 0;
    for (std::size_t i = 0; i < line; ++i) {
        pos += text[i].content.size() + 1;
    }
    return pos + column;
}

std::string VectorStorage::toString() const {
    std::string result;
    result.reserve(totalLength);
    for (std::size_t i = 0; i < text.size(); ++i) {
        result += text[i].content;
        if (i + 1 < text.size()) {
            result += '\n';
        }
    }
    return result;
}

void VectorStorage::rebuildCountBefore() {
    std::size_t offset = 0;
    for (auto& line : text) {
        line.countBefore = static_cast<int>(offset);
        offset += line.content.size() + 1;
    }
}

void VectorStorage::rebuildTotalLength() {
    totalLength = 0;
    for (std::size_t i = 0; i < text.size(); ++i) {
        totalLength += text[i].content.size();
        if (i + 1 < text.size()) {
            totalLength += 1;
        }
    }
}

}