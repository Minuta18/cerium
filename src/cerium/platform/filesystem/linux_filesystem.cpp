#include "filesystem.hpp"

#include <fstream>

std::string LinuxFilesystem::resolve(std::vector<std::string> path) {
	std::string result = "";
	for (size_t i = 0; i < path.size(); ++i) {
		result += path[i];
		if (i < path.size() - 1) {
			result += "/";
		}
	}
	return result;
}

VirtualPath LinuxFilesystem::parsePath(const std::string& path) {
	return VirtualPath(path);
}

void LinuxFilesystem::writeFile(const VirtualPath& path) {
	std::string resolvedPath = resolve(path.getVirtual());
	std::ofstream file(resolvedPath);
	if (!file) {
		throw std::runtime_error("Failed to write into file: " + resolvedPath);
	}
	file.close();
}

std::string LinuxFilesystem::readFile(const VirtualPath& path, std::optional<int> readLength) {
	std::string resolvedPath = resolve(path.getVirtual());
	std::ifstream file(resolvedPath);
	if (!file) {
		throw std::runtime_error("Failed to read file: " + resolvedPath);
	}
	std::string content;
	if (readLength.has_value()) {
		content.resize(readLength.value());
		file.read(&content[0], readLength.value());
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