#ifndef CERIUM_DOCUMENT_STORAGE_ITEXTSTORAGE_HPP_
#define CERIUM_DOCUMENT_STORAGE_ITEXTSTORAGE_HPP_

#include <cstddef>
#include <string>
#include <string_view>
#include <utility>

namespace cerium::document {

class ITextStorage {
public:
    virtual ~ITextStorage() = default;

    ITextStorage(const ITextStorage&) = delete;
    ITextStorage& operator=(const ITextStorage&) = delete;
    ITextStorage(ITextStorage&&) = delete;
    ITextStorage& operator=(ITextStorage&&) = delete;

    virtual std::size_t length() const = 0;
    virtual char charAt(std::size_t pos) const = 0;
    virtual std::string substring(std::size_t begin, std::size_t end) const = 0;

    virtual void insert(std::size_t pos, std::string_view text) = 0;
    virtual void erase(std::size_t begin, std::size_t end) = 0;
    virtual void clear() = 0;

    virtual std::size_t lineCount() const = 0;
    virtual std::string lineAt(std::size_t lineIndex) const = 0;
    virtual std::size_t lineLength(std::size_t lineIndex) const = 0;

    virtual std::pair<std::size_t, std::size_t> posToLineColumn(std::size_t pos) const = 0;
    virtual std::size_t lineColumnToPos(std::size_t line, std::size_t column) const = 0;

    virtual std::string toString() const = 0;

protected:
    ITextStorage() = default;
};

}

#endif