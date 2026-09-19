#ifndef CERIUM_DOCUMENT_STORAGE_VECTORSTORAGE_HPP_
#define CERIUM_DOCUMENT_STORAGE_VECTORSTORAGE_HPP_

#include "ITextStorage.hpp"
#include "../line.hpp"

#include <cstddef>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace cerium::document {

class VectorStorage : public ITextStorage {
public:
    VectorStorage();
    explicit VectorStorage(std::string_view content);

    std::size_t length() const override;
    char charAt(std::size_t pos) const override;
    std::string substring(std::size_t begin, std::size_t end) const override;

    void insert(std::size_t pos, std::string_view text) override;
    void erase(std::size_t begin, std::size_t end) override;
    void clear() override;

    std::size_t lineCount() const override;
    std::string lineAt(std::size_t lineIndex) const override;
    std::size_t lineLength(std::size_t lineIndex) const override;

    std::pair<std::size_t, std::size_t> posToLineColumn(std::size_t pos) const override;
    std::size_t lineColumnToPos(std::size_t line, std::size_t column) const override;

    std::string toString() const override;

private:
    std::vector<Line> text;
    std::size_t totalLength = 0;

    void rebuildCountBefore();
    void rebuildTotalLength();
};

}

#endif