#include"FileReader.h"
#include<sstream>
#include<fstream>
#include<iostream>
#include<algorithm>
#include <cstring>  
FileReader::FileReader() :
	indexLine(0), tookenType(TookenType::NONE)
{
	ss = new std::stringstream[(int)(TookenType::TOOKENSIZE)];
}
FileReader::~FileReader()
{

}

std::string FileReader::paresFile(const std::string& path)
{
	std::string line;
	std::ifstream stream(path);
	std::string string;
	tookenType = (TookenType::NEW);
	while (std::getline(stream, line))
	{
		indexLine++;

		while (line.find("\"") != std::string::npos)
		{
			int location = line.find("\"");
			int prev = location;
			//line.erase(location, location + 1);
			if (line.find("\"", location + 1) != std::string::npos)
			{
				tookenType = TookenType::STRINGLTIRAL;
				int i = location;
				location = line.find("\"", location + 1);
				std::string charTakn = "";
				while (i < location + 1)
				{
					charTakn += line[i];

					i++;
				}
				ss[(int)tookenType] << "LINE " << indexLine << " " << charTakn << std::endl;
				std::cout << ss[(int)tookenType].str();
				ss[(int)tookenType].str("");
				line.erase(prev, location + 1);
			}
			else {
				ss[(int)tookenType] << "LINE " << indexLine << " invalid Tooken (\") is missing to form a String." << std::endl;
				std::cout << ss[(int)tookenType].str();
				ss[(int)tookenType].str("");
				line = "";
			}

		}
		std::string s = "";
		int i = 0;
		bool fat = false;
		for (char x; i < line.length();)
		{

			x = line[i];
			if (x == '=' || x == '[' || x == '!' || x == '&' || x == '|')
				if (i + 1 < line.length() && (line[i + 1] == '=' || line[i + 1] == ']' || line[i + 1] == '&' || x == '|'))
				{
					if (line[i + 1] == '=' || line[i + 1] == '&' || line[i + 1] == '|') {
						checkTook(s);
						s = "";
					}


					s = s + x;
					i += 1;
					x = line[i];

					s += x;
					checkTook(s);
					s = "";
					fat = true;



				}
			if (x == ' ' || x == '(' || x == ')' || x == '*' || x == '-' || x == '/' || x == '+' || (!fat && x == '='))
			{

				if (s != "")
					checkTook(s);
				if (x != ' ')
				{
					s = x;
					checkTook(s);
				}
				s = "";
			}
			else {
				if (!fat)
					s = s + x;
			}
			i++;
			fat = false;

		}
		if (s != "")
		{
			checkTook(s);
			s = "";
		}

	}

	return ss[0].str();
}



void FileReader::checkTook(std::string  tstring)
{
	tstring.erase(std::remove(tstring.begin(), tstring.end(), '\t'), tstring.end());
	std::string string;
	if (tstring == "if") {
		tookenType = TookenType::IF;

		string = "KEYWORD (if)";
	}
	else if (tstring == ("int")) {
		tookenType = TookenType::INT;
		string = "KEYWORD (int)";
	}
	else if (tstring == ("double")) {
		tookenType = TookenType::DOUBLE;
		string = "KEYWORD (double)";
	}
	else if (tstring == ("null")) {
		tookenType = TookenType::IF;
		string = "KEYWORD (null)";
	}
	else if (tstring == ("void")) {
		tookenType = TookenType::VOID;

		string = "KEYWORD  (void)";
	}
	else if (tstring == ("class")) {
		tookenType = TookenType::CLASS;

		string = "KEYWORD  (class)";
	}
	else if (tstring == ("extends")) {
		tookenType = TookenType::EXTENDS;

		string = "KEYWORD (extends)";
	}
	else if (tstring == ("interface")) {
		tookenType = TookenType::INTERFACE;

		string = "KEYWORD (interface)";
	}
	else if (tstring == ("this")) {
		tookenType = TookenType::THIS;
		string = "KEYWORD (this)";
	}
	else if (tstring == ("retrun")) {
		tookenType = TookenType::RETURN;

		string = "KEYWORD (retrun)";
	}
	else if (tstring == ("break")) {
		tookenType = TookenType::BREAK;

		string = "KEYWORD (break)";
	}
	else if (tstring == "new") {
		tookenType = TookenType::NEW;

		string = "KEYWORD (new)";
	}
	else if (tstring == "!=") {
		tookenType = TookenType::NOTEQ;
		string = "TOOKEN (!=)";
	}
	else if (tstring == ("print")) {
		tookenType = TookenType::PRINT;

		string = "KEYWORD (print)";
	}
	else if (tstring == ("ReadInt")) {
		tookenType = TookenType::READINT;

		string = "KEYWORD (readint)";
	}
	else if (tstring == ("ReadLine")) {
		tookenType = TookenType::READLINE;

		string = "KEYWORD (readLine)";
	}
	else if (tstring == ("NewArray")) {
		tookenType = TookenType::NEWPOINTER;
		string = "KEYWORD (NewArray)";
	}

	else if (tstring == ("while")) {
		tookenType = TookenType::WHILE;
		string = "KEYWORD (while)";

	}
	else if (tstring == ("for")) {
		tookenType = TookenType::FOR;
		string = "KEYWORD (for)";

	}
	else if (tstring == ("do")) {
		tookenType = TookenType::DO;
		string = "KEYWORD (do)";
	}
	else if (tstring == ("(")) {
		tookenType = TookenType::QPRIGHT;
		string = "TOOKEN ( ( )";

	}
	else if (tstring == (")")) {
		tookenType = TookenType::QPLEFT;
		string = "TOOKEN ( ) )";

	}
	else if (tstring == ("==")) {
		tookenType = TookenType::EQUAL;
		string = "TOOKEN ( == )";

	}
	else if (tstring == ("string")) {
	tookenType = TookenType::STRING;
	string = "TOOKEN ( string )";

	}
	else if (tstring == ("[]")) {
		tookenType = TookenType::ParRIGHT;
		string = "TOOKEN ( [] )";

	}
	else if (tstring == ("[")) {
		tookenType = TookenType::ParRIGHT;
		string = "TOOKEN ( [ )";

	}
	else if (tstring == ("]")) {
		tookenType = TookenType::PARLEFT;
		string = "TOOKEN ( ] )";

	}
	else if (tstring == ("{")) {
		tookenType = TookenType::LEFTBRACKET;
		string = "TOOKEN ({) ";
	}
	else if (tstring == ("}")) {
		tookenType = TookenType::RIGHTBRACKET;
		string = "TOOKEN (}) ";
	}
	else if (tstring == ("{}")) {
		tookenType = TookenType::BOTHBRACKETS;
		string = "TOOKEN ({}) ";
	}
	else if (tstring == ("+")) {
		tookenType = TookenType::PLUS;
		string = "OPERATION (+) ";
	}
	else if (tstring == "-") {
		tookenType = TookenType::MINS;
		string = "OPERATION (-) ";

	}
	else if (tstring == ("*")) {
		tookenType = TookenType::MLTI;
		string = "OPERATION (*) ";

	}
	else if (tstring == ("/")) {
		tookenType = TookenType::DIV;
		string = "OPERATION (/) ";

	}
	else if (tstring == ("<")) {
		tookenType = TookenType::MORETHAN;
		string = "OPERATION (<) ";

	}
	else if (tstring == (">")) {
		tookenType = TookenType::LESSTHAN;
		string = "OPERATION (>) ";

	}
	else if (tstring == ("<=")) {
		tookenType = TookenType::MORETHANOREQ;
		string = "OPERATION (<=) ";

	}
	else if (tstring == (">=")) {
		tookenType = TookenType::LESSTHANOREQ;
		string = "OPERATION (>=) ";
	}
	else if (tstring == ("=")) {
		tookenType = TookenType::EQULONE;
		string = "OPERATION (=) ";
	}
	else if (tstring == ("%")) {
		tookenType = TookenType::PER;
		string = "OPERATION (%) ";
	}
	else if (tstring == ("^")) {
		tookenType = TookenType::POWER;
		string = "OPERATION (^) ";
	}
	else if (tstring == ("&&")) {
		tookenType = TookenType::ANDAND;
		string = "OPERATION (&&) ";
	}
	else if (tstring == ("||")) {
		tookenType = TookenType::OR;
		string = "OPERATION (||) ";
	}
	else if (tstring == ("!")) {
		tookenType = TookenType::NOT;
		string = "OPERATION (NOT) ";
	}

	else
	{
		bool numberPrev = false;
		bool charPrev = false;
		string = tstring;
		for (auto x : tstring)
		{
			if (tstring.size())
			{
				if (!(x == '[' || x == ']' || x == '.' || x == '+' || x == '-' || (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z')))
				{
					if (!(x >= '0' && x <= '9')) {
						string = "Invalid Tooken ( " + tstring + ")";
					}
					else {
						if (!charPrev)
							numberPrev = true;
						if (tookenType != TookenType::DOUBLE && tookenType != TookenType::IDENT) {
							tookenType = TookenType::NUMBER;
							string = "INT (" + tstring + ")";
						}
					}
				}
				else
				{
					if (tookenType != TookenType::DOUBLE) {
						tookenType = TookenType::IDENT;
						string = "ID (" + tstring + " )";

						charPrev = true;
					}
					if (numberPrev)
					{
						if (x == '.')
						{
							tookenType = TookenType::DOUBLE;
							string = "DOUBLE (" + tstring + ")";
						}
						else if (x == '+' || x == '-')
						{
							//if (tookenType == TookenType::EXP) {
							tookenType = TookenType::DOUBLE;
							string = "DOUBLE (" + tstring + ")";
							//}
						}
						else if (x == 'E')
						{
							tookenType = TookenType::EXP;
						}
						else {
							if (numberPrev)
								string = "Invalid Tooken ( " + tstring + " )";
							tstring.clear();
						}
					}
					else {
						if (x == '.')
						{
							string = "Invalid Tooken ( " + tstring + " )";
							tstring = "";
						}
					}
				}
			}
		}
	}
	ss[(int)tookenType] << "LINE " << indexLine << " " << string << "\n";
	std::cout << ss[(int)tookenType].str();
	ss[(int)tookenType].str("");
	tookenType = TookenType::NONE;
}