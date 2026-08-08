#include "text.hpp"
#include <ranges>

Line::Line(std::string content, int countBefore): content(content), countBefore(countBefore) {}

Line::Line(std::string content) : content(content), countBefore(0) {}

Line::Line(const Line& other) : content(other.content), countBefore(other.countBefore) {}

Line& Line::operator=(const Line& other) {
	content = other.content;
	countBefore = other.countBefore;
	return *this;
};

Text::Text(std::string content): currentColumn(0), currentLine(0), position(0) {
	auto lines = content | std::views::split('\n');
	text = std::ranges::to<std::vector<Line>>(lines | std::views::transform([](auto&& line) {
		return Line(std::string(line.begin(), line.end()));
		}));
}

Text::Text(std::vector<Line> content): text(content), currentColumn(0), currentLine(0), position(0) {}

int Text::getPosition() {
	return text[currentLine].countBefore + currentColumn;
}

int Text::characterCount() {
	return text.back().countBefore + static_cast<int>(text.back().content.size());
}

void Text::allCountBefore() {
	int currentCount = 0;
	for (int i = 0; i < text.size(); ++i) {
		text[i].countBefore = currentCount;
		currentCount += static_cast<int>(text[i].content.size());
	}
}

void Text::setLine(int line) {
	currentLine = line;
}

void Text::setColumn(int column){
	currentColumn = column;
}
void Text::setPosition(int line, int column) {
	currentLine = line;
	currentColumn = column;
}

void Text::setPosition(int pos) {
	position = pos;
}

void Text::pasteInNewLine(std::string newLine, int line) {
	text.insert(text.begin() + line, Line(newLine, 0));
	allCountBefore();
}

void Text::paste(std::string substr) {
	text[currentLine].content.insert(currentColumn, substr);
	allCountBefore();
}

void Text::paste(std::string substr, int column, int line) {
	text[line].content.insert(column, substr);
	allCountBefore();
}

void Text::deleteLine(int line) {
	text.erase(text.begin() + line);
	allCountBefore();
}

void Text::deleteLine() {
	text.erase(text.begin() + currentLine);
	allCountBefore();
}

void Text::deleteMultiple(int number) {
	text[currentLine].content.erase(currentColumn, number);
}

void Text::deleteMultiple(int number, int line, int column) {
	text[line].content.erase(column, number);
}

void Text::remove() {
	text[currentLine].content.erase(currentColumn, 1);
	allCountBefore();
}

void Text::remove(int line, int column) {
	text[line].content.erase(column, 1);
	allCountBefore();
}

std::vector<Line> Text::getText() {
	return text;
}

std::string Text::getLine(int line) {
	return text[line].content;
}

void Text::clear() {
	text.clear();
	currentColumn = 0;
	currentLine = 0;
	position = 0;
}