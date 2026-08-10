#ifndef CERIUM_DOCUMENT_DOCUMENT_HPP_
#define CERIUM_DOCUMENT_DOCUMENT_HPP_

#include <string>
#include "text.hpp"
#include <filesystem>

#include "../debug/logging/ConsoleLoggerMiddleware.hpp"
#include "../debug/logging/FileLoggerMiddleware.hpp"
#include "../debug/logging/Logger.hpp"
#include "../debug/logging/LoggerConfig.hpp"
#include "../debug/logging/Logging.hpp"


class Document {
	friend class Project;
private:
	std::filesystem::path path;
	std::string language = "txt";
	Text text;
	bool edit = true;

	std::unique_ptr<Logger> logger;

	Document(Document&& other) noexcept;
	Document(std::filesystem::path path, Text text, std::string language = "txt", bool edit = true);
public:
	Document(const Document&) = delete;

	Document& operator=(const Document&) = delete;
	Document& operator=(Document&& other) noexcept;

	void setupLogger();

	~Document() = default;
};

#endif //CERIUM_DOCUMENT_DOCUMENT_HPP_
