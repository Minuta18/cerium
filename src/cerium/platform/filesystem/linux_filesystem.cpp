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