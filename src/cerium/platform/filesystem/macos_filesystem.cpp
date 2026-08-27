#include "filesystem.hpp"

#include <algorithm>
#include <cctype>

std::string MacOSFilesystem::resolve(std::vector<std::string> path) {
	std::string result = "";
	for (size_t i = 0; i < path.size(); ++i) {
		result += path[i];
		if (i < path.size() - 1) {
			result += "/";
		}
	}

	std::range::transform(result, result.begin(), [](unsigned char c) {
		return std::tolower(c);
		});

	return result;
}
