#include<string>
class FileReader {
private:
	int indexLine;
	enum class TookenType {
		NONE = -1, EXP, NOTEQ, NULLPTR, NUMBER, IDENT, EQUAL, QPRIGHT, QPLEFT, MORETHAN, LESSTHAN,STRING, MORETHANOREQ, LESSTHANOREQ, ANDAND, OR, EQULONE, PER, POWER, VOID, INT, TREU, FALSE, DOUBLE, BOOL, CLASS, INTERFACE, IMPLEMENETS, THIS, EXTENDS, RETURN, BREAK, NEW, NEWPOINTER, PRINT, READINT, READLINE, IF, ELSE, WHILE, FOR, DO, ParRIGHT, PARLEFT, PLUS, MINS, MLTI, DIV, STRINGLTIRAL, NOT, LEFTBRACKET, RIGHTBRACKET, BOTHBRACKETS, TOOKENSIZE
	};
	std::stringstream* ss;
	TookenType tookenType;

public:
	FileReader();
	~FileReader();

	std::string paresFile(const std::string& path);
	void checkTook(std::string  string);
};