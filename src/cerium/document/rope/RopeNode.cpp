#include "RopeNode.hpp"

#include <algorithm>
#include <cassert>
#include <utility>

namespace cerium::document {

RopeNode::RopeNode(std::string text) : leaf(std::move(text)) {
    weight = leaf.size();
    lineWeight = static_cast<std::size_t>(
        std::count(leaf.begin(), leaf.end(), '\n'));
    height = 1;
}

bool RopeNode::isLeaf() const noexcept {
    return !left && !right;
}

std::unique_ptr<RopeNode> RopeNode::makeLeaf(std::string text) {
    return std::make_unique<RopeNode>(std::move(text));
}

std::unique_ptr<RopeNode> RopeNode::makeInternal(std::unique_ptr<RopeNode> l,
                                                 std::unique_ptr<RopeNode> r) {
    assert(l != nullptr);
    assert(r != nullptr);

    auto node = std::make_unique<RopeNode>();
    node->left = std::move(l);
    node->right = std::move(r);
    update(node.get());
    return node;
}

std::size_t RopeNode::nodeLength(const RopeNode* node) noexcept {
    assert(node != nullptr);
    if (node->isLeaf()) {
        return node->leaf.size();
    }
    return node->weight + nodeLength(node->right.get());
}

std::size_t RopeNode::nodeNewlineCount(const RopeNode* node) noexcept {
    assert(node != nullptr);
    if (node->isLeaf()) {
        return node->lineWeight;
    }
    return node->lineWeight + nodeNewlineCount(node->right.get());
}

std::size_t RopeNode::nodeHeight(const RopeNode* node) noexcept {
    assert(node != nullptr);
    return node->height;
}

void RopeNode::update(RopeNode* node) noexcept {
    assert(node != nullptr);
    assert(!node->isLeaf());
    node->weight = nodeLength(node->left.get());
    node->lineWeight = nodeNewlineCount(node->left.get());
    node->height = 1 + std::max(nodeHeight(node->left.get()),
                                nodeHeight(node->right.get()));
}

}