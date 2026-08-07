#include "text.hpp"

void Text::setLine(int line) {
	currentLine = line;
}

void Text::setPosition(int column){
	currentColumn = column;
}
void Text::setPosition(int line, int column) {
	currentLine = line;
	currentColumn = column;
}

void Text::insert(char symbol) {
	text[currentLine].insert(currentColumn, 1, symbol);
}

void Text::insert(char symbol, int column, int line) {
	text[line].insert(column, 1, symbol);
}

void Text::pasteInNewLine(std::string newLine, int line) {
	text.insert(text.begin() + line, newLine);
}

void Text::paste(std::string substr) {
	text[currentLine].insert(currentColumn, substr);
}

void Text::paste(std::string substr, int column, int line) {
	text[line].insert(column, substr);
}

void Text::delete_line(int line) {
	text.erase(text.begin() + line);
}

void Text::remove() {
	text[currentLine].erase(currentColumn, 1);
}

void Text::remove(int line, int column) {
	text[line].erase(column, 1);
}

std::vector<std::string> Text::getText() {
	return text;
}

std::string Text::getLine(int line) {
	return text[line];
}

void clear() {
	text.clear();
	currentColumn = 0;
	currentLine = 0;
}