#ifndef CERIUM_DOCUMENT_ROPE_ROPENODE_HPP_
#define CERIUM_DOCUMENT_ROPE_ROPENODE_HPP_

#include <cstddef>
#include <memory>
#include <string>

namespace cerium::document {

struct RopeNode {
    std::string leaf;
    std::unique_ptr<RopeNode> left;
    std::unique_ptr<RopeNode> right;
    std::size_t weight = 0;
    std::size_t lineWeight = 0;
    std::size_t height = 1;

    RopeNode() = default;
    explicit RopeNode(std::string text);

    bool isLeaf() const noexcept;

    static std::unique_ptr<RopeNode> makeLeaf(std::string text);
    static std::unique_ptr<RopeNode> makeInternal(std::unique_ptr<RopeNode> l,
                                                  std::unique_ptr<RopeNode> r);

    static std::size_t nodeLength(const RopeNode* node) noexcept;
    static std::size_t nodeNewlineCount(const RopeNode* node) noexcept;
    static std::size_t nodeHeight(const RopeNode* node) noexcept;
    static void update(RopeNode* node) noexcept;
};

}

#endif