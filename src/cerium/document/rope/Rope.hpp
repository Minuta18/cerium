#ifndef CERIUM_DOCUMENT_ROPE_ROPE_HPP_
#define CERIUM_DOCUMENT_ROPE_ROPE_HPP_

#include "RopeNode.hpp"

#include <cstddef>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

namespace cerium::document {

class Rope {
public:
    Rope();
    explicit Rope(std::string_view content);

    Rope(const Rope& other);
    Rope& operator=(const Rope& other);
    Rope(Rope&& other) noexcept = default;
    Rope& operator=(Rope&& other) noexcept = default;
    ~Rope() = default;

    std::size_t length() const;
    char charAt(std::size_t pos) const;
    std::string substring(std::size_t begin, std::size_t end) const;

    void insert(std::size_t pos, std::string_view text);
    void erase(std::size_t begin, std::size_t end);
    void clear();

    std::string toString() const;

    std::optional<std::size_t> findChar(char c, std::size_t from = 0) const;

    std::size_t lineCount() const;
    std::string lineAt(std::size_t lineIndex) const;
    std::size_t lineLength(std::size_t lineIndex) const;
    std::pair<std::size_t, std::size_t> posToLineColumn(std::size_t pos) const;
    std::size_t lineColumnToPos(std::size_t line, std::size_t column) const;

private:
    std::unique_ptr<RopeNode> root;

    Rope(std::unique_ptr<RopeNode> r);

    static std::unique_ptr<RopeNode> buildFromString(std::string_view content);
    static std::unique_ptr<RopeNode> concat(std::unique_ptr<RopeNode> a,
                                            std::unique_ptr<RopeNode> b);
    static std::pair<std::unique_ptr<RopeNode>, std::unique_ptr<RopeNode>>
        splitNode(std::unique_ptr<RopeNode> node, std::size_t pos);

    std::size_t lineStartPos(std::size_t line) const;
};

}

#endif