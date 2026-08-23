#include "filesystem.hpp"

#include <filesystem>
#include <fstream>

std::string WindowsFilesystem::resolve(std::vector<std::string> path) {
	std::string result = "";
	for (size_t i = 0; i < path.size(); ++i) {
		result += path[i];
		if (i < path.size() - 1) {
			result += "\\";
		}
	}
	return result;
}

VirtualPath WindowsFilesystem::parsePath(const std::string& path) {
	return VirtualPath(path);
}

void WindowsFilesystem::writeFile(const VirtualPath& path) {
	std::string resolvedPath = resolve(path.getVirtual());
	std::ofstream file(resolvedPath);
	if (!file)) {
		throw std::runtime_error("Failed to write into file: " + resolvedPath);
	}
	file.close();
}

std::string WindowsFilesystem::readFile(const VirtualPath& path, std::optional<int> readLength) {
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