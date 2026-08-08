#ifndef CERIUM_DOCUMENT_TEXT_HPP_
#define CERIUM_DOCUMENT_TEXT_HPP_

#include <vector>
#include <string>

struct Line {
	Line(std::string content, int countBefore);

	std::string content;
	int countBefore;
};

class Text {
private:
	std::vector<Line> text;
	int position;
	int currentColumn;
	int currentLine;
public:
	int getPosition();
	int characterCount();

	void allCountBefore(); // Temporary slow implementation

	void setLine(int line);
	void setColumn(int column);
	void setPosition(int line, int column);
	void setPosition(int pos);

	void pasteInNewLine(std::string newLine, int line);
	void paste(std::string substr); // Can be used for pasting OR typing
	void paste(std::string substr, int column, int line);

	void deleteLine(int line);
	void deleteLine();
	void remove();
	void remove(int line, int column);

	std::vector<Line> getText();
	std::string getLine(int line);

	void clear();
};

#endif //CERIUM_DOCUMENT_TEXT_HPP_