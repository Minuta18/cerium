#ifndef CERIUM_DOCUMENT_TEXT_HPP_
#define CERIUM_DOCUMENT_TEXT_HPP_

#include <vector>
#include <string>

class Text {
private:
	std::vector<std::string> text;
	int currentColumn;
	int currentLine;
public:
	void setLine(int line);
	void setPosition(int column);
	void setPosition(int line, int column);

	void insert(char symbol); // Can be used for typing
	void insert(char symbol, int column, int line);

	void pasteInNewLine(std::string newLine, int line);
	void paste(std::string substr);
	void paste(std::string substr, int column, int line);

	void delete_line();
	void remove();
	void remove(int line, int column);

	std::vector<std::string> getText();
	std::string getLine(int line);

	void clear();
};

#endif //CERIUM_DOCUMENT_TEXT_HPP_