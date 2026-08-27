#include "filesystem.hpp"

#include <fstream>

void UnixFilesystem::writeFile(const VirtualPath& path) {
	std::string resolvedPath = resolve(path.getVirtual());
	std::ofstream file(resolvedPath);
	if (!file) {
		throw std::runtime_error("Failed to write into file: " + resolvedPath);
	}
	file.close();
}

std::string UnixFilesystem::readFile(const VirtualPath& path, std::optional<int> readLength) {
	std::string resolvedPath = resolve(path.getVirtual());
	std::ifstream file(resolvedPath);
	if (!file) {
		throw std::runtime_error("Failed to read file: " + resolvedPath);
	}
	std::string content;
	if (readLength.has_value()) {
		content.resize(readLength);
		file.read(&content[0], readLength);
		file.close();
	}
	else {
		std::stringstream buffer;
		buffer << file.rdbuf();
		content = buffer.str();
		file.close();
	}
	return content;
}