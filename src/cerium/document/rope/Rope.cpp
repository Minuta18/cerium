#include "Rope.hpp"

#include <cassert>
#include <stdexcept>
#include <utility>

namespace cerium::document {

namespace {

constexpr std::size_t LEAF_MAX_SIZE = 1024;

std::unique_ptr<RopeNode> cloneNode(const RopeNode* node) {
    assert(node != nullptr);
    if (node->isLeaf()) {
        return RopeNode::makeLeaf(node->leaf);
    }
    auto left = cloneNode(node->left.get());
    auto right = cloneNode(node->right.get());
    return RopeNode::makeInternal(std::move(left), std::move(right));
}

void collectRange(const RopeNode* node, std::size_t nodeStart,
                  std::size_t begin, std::size_t end, std::string& out) {
    assert(node != nullptr);
    std::size_t nodeLen = RopeNode::nodeLength(node);
    std::size_t nodeEnd = nodeStart + nodeLen;

    if (nodeEnd <= begin || nodeStart >= end) {
        return;
    }

    if (node->isLeaf()) {
        std::size_t from = begin > nodeStart ? begin - nodeStart : 0;
        std::size_t to = end < nodeEnd ? end - nodeStart : node->leaf.size();
        out.append(node->leaf, from, to - from);
        return;
    }

    std::size_t leftLen = node->weight;
    collectRange(node->left.get(), nodeStart, begin, end, out);
    collectRange(node->right.get(), nodeStart + leftLen, begin, end, out);
}

std::optional<std::size_t>
findCharInNode(const RopeNode* node, char c, std::size_t from) {
    assert(node != nullptr);

    if (node->isLeaf()) {
        auto pos = node->leaf.find(c, from);
        if (pos == std::string::npos) {
            return std::nullopt;
        }
        return pos;
    }

    std::size_t leftLen = node->weight;

    if (from < leftLen) {
        auto res = findCharInNode(node->left.get(), c, from);
        if (res.has_value()) {
            return res;
        }
        auto resRight = findCharInNode(node->right.get(), c, 0);
        if (resRight.has_value()) {
            return leftLen + resRight.value();
        }
        return std::nullopt;
    }

    auto res = findCharInNode(node->right.get(), c, from - leftLen);
    if (!res.has_value()) {
        return std::nullopt;
    }
    return leftLen + res.value();
}

}  // namespace

Rope::Rope() : root(RopeNode::makeLeaf("")) {}

Rope::Rope(std::string_view content)
    : root(buildFromString(content)) {}

Rope::Rope(std::unique_ptr<RopeNode> r) : root(std::move(r)) {
    assert(root != nullptr);
}

Rope::Rope(const Rope& other)
    : root(cloneNode(other.root.get())) {}

Rope& Rope::operator=(const Rope& other) {
    if (this != &other) {
        root = cloneNode(other.root.get());
    }
    return *this;
}

std::size_t Rope::length() const {
    return RopeNode::nodeLength(root.get());
}

char Rope::charAt(std::size_t pos) const {
    if (pos >= length()) {
        throw std::out_of_range("Rope::charAt: pos out of range");
    }
    const RopeNode* node = root.get();
    std::size_t p = pos;
    while (!node->isLeaf()) {
        if (p < node->weight) {
            node = node->left.get();
        } else {
            p -= node->weight;
            node = node->right.get();
        }
    }
    return node->leaf[p];
}

std::string Rope::substring(std::size_t begin, std::size_t end) const {
    if (begin > end || end > length()) {
        throw std::out_of_range("Rope::substring: invalid range");
    }
    std::string result;
    result.reserve(end - begin);
    collectRange(root.get(), 0, begin, end, result);
    return result;
}

void Rope::insert(std::size_t pos, std::string_view text) {
    if (pos > length()) {
        throw std::out_of_range("Rope::insert: pos out of range");
    }
    if (text.empty()) {
        return;
    }
    auto [left, right] = splitNode(std::move(root), pos);
    auto mid = buildFromString(text);
    root = concat(std::move(left), concat(std::move(mid), std::move(right)));
}

void Rope::erase(std::size_t begin, std::size_t end) {
    if (begin > end || end > length()) {
        throw std::out_of_range("Rope::erase: invalid range");
    }
    if (begin == end) {
        return;
    }
    auto [left, rest] = splitNode(std::move(root), begin);
    auto [mid, right] = splitNode(std::move(rest), end - begin);
    (void)mid;
    root = concat(std::move(left), std::move(right));
}

void Rope::clear() {
    root = RopeNode::makeLeaf("");
}

std::string Rope::toString() const {
    return substring(0, length());
}

std::optional<std::size_t> Rope::findChar(char c, std::size_t from) const {
    if (from > length()) {
        throw std::out_of_range("Rope::findChar: from out of range");
    }
    return findCharInNode(root.get(), c, from);
}

std::size_t Rope::lineCount() const {
    return RopeNode::nodeNewlineCount(root.get()) + 1;
}

std::size_t Rope::lineStartPos(std::size_t line) const {
    const RopeNode* node = root.get();
    std::size_t offset = 0;
    std::size_t remainingLine = line;

    while (!node->isLeaf()) {
        std::size_t leftNewlines = node->lineWeight;
        std::size_t leftLen = node->weight;

        if (remainingLine <= leftNewlines) {
            node = node->left.get();
        } else {
            remainingLine -= leftNewlines + 1;
            offset += leftLen + 1;
            node = node->right.get();
        }
    }

    std::size_t leafLine = 0;
    std::size_t leafPos = 0;
    while (leafPos < node->leaf.size() && leafLine < remainingLine) {
        if (node->leaf[leafPos] == '\n') {
            ++leafLine;
        }
        ++leafPos;
    }
    return offset + leafPos;
}

std::pair<std::size_t, std::size_t>
Rope::posToLineColumn(std::size_t pos) const {
    if (pos > length()) {
        throw std::out_of_range("Rope::posToLineColumn: pos out of range");
    }
    const RopeNode* node = root.get();
    std::size_t remaining = pos;
    std::size_t line = 0;

    while (!node->isLeaf()) {
        std::size_t leftLen = node->weight;
        if (remaining <= leftLen) {
            node = node->left.get();
        } else {
            line += node->lineWeight + 1;
            remaining -= leftLen + 1;
            node = node->right.get();
        }
    }

    std::size_t col = 0;
    for (std::size_t i = 0; i < remaining && i < node->leaf.size(); ++i) {
        if (node->leaf[i] == '\n') {
            ++line;
            col = 0;
        } else {
            ++col;
        }
    }

    return {line, col};
}

std::size_t Rope::lineColumnToPos(std::size_t line, std::size_t column) const {
    std::size_t lines = lineCount();
    if (line >= lines) {
        throw std::out_of_range("Rope::lineColumnToPos: line out of range");
    }

    std::size_t start = lineStartPos(line);
    std::size_t end = (line + 1 < lines)
                          ? lineStartPos(line + 1) - 1
                          : length();
    if (column > end - start) {
        throw std::out_of_range("Rope::lineColumnToPos: column out of range");
    }
    return start + column;
}

std::string Rope::lineAt(std::size_t lineIndex) const {
    std::size_t lines = lineCount();
    if (lineIndex >= lines) {
        throw std::out_of_range("Rope::lineAt: line out of range");
    }
    std::size_t start = lineStartPos(lineIndex);
    std::size_t end = (lineIndex + 1 < lines)
                          ? lineStartPos(lineIndex + 1) - 1
                          : length();
    return substring(start, end);
}

std::size_t Rope::lineLength(std::size_t lineIndex) const {
    std::size_t lines = lineCount();
    if (lineIndex >= lines) {
        throw std::out_of_range("Rope::lineLength: line out of range");
    }
    std::size_t start = lineStartPos(lineIndex);
    std::size_t end = (lineIndex + 1 < lines)
                          ? lineStartPos(lineIndex + 1) - 1
                          : length();
    return end - start;
}

std::unique_ptr<RopeNode> Rope::concat(std::unique_ptr<RopeNode> a,
                                        std::unique_ptr<RopeNode> b) {
    assert(a != nullptr);
    assert(b != nullptr);

    std::size_t ha = RopeNode::nodeHeight(a.get());
    std::size_t hb = RopeNode::nodeHeight(b.get());

    if (ha <= hb + 1 && hb <= ha + 1) {
        return RopeNode::makeInternal(std::move(a), std::move(b));
    }

    if (ha > hb) {
        if (a->isLeaf()) {
            return RopeNode::makeInternal(std::move(a), std::move(b));
        }
        auto newRight = concat(std::move(a->right), std::move(b));
        return RopeNode::makeInternal(std::move(a->left), std::move(newRight));
    }

    if (b->isLeaf()) {
        return RopeNode::makeInternal(std::move(a), std::move(b));
    }
    auto newLeft = concat(std::move(a), std::move(b->left));
    return RopeNode::makeInternal(std::move(newLeft), std::move(b->right));
}

std::pair<std::unique_ptr<RopeNode>, std::unique_ptr<RopeNode>>
Rope::splitNode(std::unique_ptr<RopeNode> node, std::size_t pos) {
    assert(node != nullptr);

    if (node->isLeaf()) {
        assert(pos <= node->leaf.size());
        std::string leftStr = node->leaf.substr(0, pos);
        std::string rightStr = node->leaf.substr(pos);
        return {RopeNode::makeLeaf(std::move(leftStr)),
                RopeNode::makeLeaf(std::move(rightStr))};
    }

    if (pos < node->weight) {
        auto [leftA, leftB] = splitNode(std::move(node->left), pos);
        auto right = concat(std::move(leftB), std::move(node->right));
        return {std::move(leftA), std::move(right)};
    }

    if (pos == node->weight) {
        return {std::move(node->left), std::move(node->right)};
    }

    auto [rightA, rightB] = splitNode(std::move(node->right), pos - node->weight);
    auto left = concat(std::move(node->left), std::move(rightA));
    return {std::move(left), std::move(rightB)};
}

std::unique_ptr<RopeNode> Rope::buildFromString(std::string_view content) {
    if (content.size() <= LEAF_MAX_SIZE) {
        return RopeNode::makeLeaf(std::string(content));
    }
    std::size_t mid = content.size() / 2;
    auto left = buildFromString(content.substr(0, mid));
    auto right = buildFromString(content.substr(mid));
    return RopeNode::makeInternal(std::move(left), std::move(right));
}

}