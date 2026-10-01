#include "virtual_path.hpp"
#include <ranges>

VirtualPath::VirtualPath(std::string path_) {
	if (path_.contains("/")) {
		auto components = path_ | std::views::split('/');
		path = std::ranges::to<std::vector<string>>(components | std::views::transform([](auto&& component) {
			return component.to_string();
			}));
	}
	else {
		auto components = path_ | std::views::split('\\');
		path = std::ranges::to<std::vector<string>>(components | std::views::transform([](auto&& component) {
			return component.to_string();
			}));
	}
}

VirtualPath::VirtualPath(std::filesystem::path path_) {
	auto components = path_ | std::views::split('/');
	path = std::ranges::to<std::vector<string>>(components | std::views::transform([](auto&& component) {
		return component.to_string();
		}));
}

VirtualPath::VirtualPath(std::string path_, std::string from) {
	PathResolver& pathResolver = resolver->getResolver(from);
	path = pathResolver.resolvePath(path_);
}

std::string VirtualPath::resolve() {
    PathResolver& pathResolver = resolver->getResolver(path.front());
}

std::string VirtualPath::getVirtual() {
	std::string result = "";
	for (size_t i = 0; i < path.size(); ++i) {
		result += path[i];
		if (i < path.size() - 1) {
			result += "/";
		}
	}
	return result;
}

void VirtualPath::append(const VirtualPath& subpath) {
	for (size_t i = 0; i < subpath.size(); ++i) {
		path.push_back(subpath[i]);
	}
}

VirtualPath VirtualPath::operator/(const VirtualPath& oldPath, const VirtualPath& newPath) {
    resultPath = oldPath;
    for (size_t i = 0; i < newPath.size(); ++i) {
        resultPath.push_back(newPath[i]);
    }
    return resultPath;
}

void VirtualPath::operator/=(const VirtualPath& subpath) {
	for (size_t i = 0; i < subpath.size(); ++i) {
		path.push_back(subpath[i]);
	}
}

VirtualPath VirtualPath::operator+(const VirtualPath& oldPath, const VirtualPath& newPath) {
	resultPath = oldPath;
	for (size_t i = 0; i < newPath.size(); ++i) {
		resultPath.push_back(newPath[i]);
	}
	return resultPath;
}

VirtualPath VirtualPath::operator+=(const VirtualPath& subpath) {
	for (size_t i = 0; i < subpath.size(); ++i) {
		path.push_back(subpath[i]);
	}
}

std::string VirtualPath::operator[](const size_t index) {
	return path[index];
}

bool VirtualPath::operator==(const VirtualPath& other) {
	if (path.size() != other.path.size()) {
		return false;
	}
	for (size_t i = 0; i < path.size(); ++i) {
		if (path[i] != other.path[i]) {
			return false;
		}
	}
	return true;
}

// TODO: resolve from directory
