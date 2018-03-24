#include "stdafx.h"
#include <fstream>
#include "Code.h"
#include "Random.h"
using namespace std;

Code::Code(string file)
{
	if (!isInit) {
		filename = file;
		cout << file << endl;
		ifstream input(file);
		string in;
		while (getline(input, in))
		{
			auto str = cutStringComm(in);
			start.push_back(str);
			cout << str << endl;
		}
		input.close();
		line = 0;
		symbol = 0;
		isInit = true;
		cout << "Initialization finised" << endl;
	}
}

string Code::nextWord()
{
	string word;
	for (int i = line; i < start.size(); i++) {
		bool inQuotes = false;
		//int size = sizeWoCom(start[i]);
		for (int j = symbol; j < start[i].size(); j++) {
			char crChar = start[i][j];
			if (!inQuotes) {
				if ((crChar == '"') || (crChar == '\'')) {
					if (returnWord(word, i, j)) return word;
					word += crChar;
					inQuotes = true;
				}
				else if (str::isChrBeStr(crChar, str::letters + str::digits)) 
					word += crChar;
				else if (returnWord(word, i, j)) return word;
			}
			else {
				if ((crChar == '"') || (crChar == '\'')) {
					returnWord(word, i , j + 1);
					return word + crChar;
				}
				else if (!str::isChrBeStr(crChar, "\n\r"))
					word += crChar;
				else if (returnWord(word, i, j)) {
					//TODO: Ошибка не закрытой кавычки
					return word;
				}
			}
		}
		symbol = 0;
	}
}

char Code::nextSymbol(bool viewmode = false)
{
	for (int i = line; i < start.size(); i++) {
		for (int j = symbol; j < start[i].size(); j++) {
			if (!str::isChrBeStr(start[i][j], "" + (char)13 + (char)10 + (char)32 + (char)9)) { //9 - '	', 32 - ' ';
				if (!viewmode) {
					cout << "NS: " << (int)start[i][j] << " : " << start[i][j] << endl;
					line = i;
					symbol = j + 1;
				}
				return start[i][j];
			}
		}
	}
}

char Code::nextChar(bool viewmode = false)
{
	for (int i = line; i < start.size(); i++)
		for (int j = symbol; j < start[i].size(); j++)
			if (!str::isChrBeStr(start[i][j], "\n\r")) {
				if(!viewmode) {
					line = i;
					symbol = j + 1;
				}
				return start[i][j];
			}
}

void Code::skipComment(string endComm)
{
	while (true) {
		if ((nextSymbol() == '*'))
		{
			if (nextChar() == '/')
			{
				cout << "End of comment was find" << endl;
			}
		}
	}
}

bool Code::returnWord(string word, int i, int j)
{
	if (!word.empty()) {
		line = i;
		symbol = j;
		return true;
	}
	return false;
}

string Code::cutStringComm(string str)
{
	//string rezult;
	int comm = str.find("//");
	if (comm != string::npos)
	{
		return str.substr(0, comm);
	}
	return str;
}

int Code::sizeWoCom(string str)
{
	int size = str.size();
	if (!inComment) {
		int open = str.find("/*");
		if (open < size) {
			if (str[open - 1] != '\\')size = open;
			inComment = size;
		}
	}
	else {
		if (str.find("* /") < size) {
			if (str[str.find("* /") - 1] != '\\')size = (int)str.find("* /");
			if (size >= symbol) {
				inComment = true;
				return -1;
			}
		}
	}
}

string str::letters = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" }; //54 символа
string str::digits  = { "0123456789" }; //10 символов

bool str::onlySpace(string str)
{
	size_t found = str.find_first_not_of("	 ");
	if (found != string::npos) {
		return false;
	}
	else {
		return true;
	}
}

string str::CharRand() {
	string st;
	int ti = letters.size() - 1;
	for (int i = 0; i < 10; i++)
		st += letters[random(0, ti)];
	return st;
}

//Вернет true если символ есть в строке
bool str::isChrBeStr(char str, string chr) {
	int strS = 1;// str.size();
	int chrS = chr.size();

	cout << "===========In iCBS: " << str << " : " << chr << endl;

	for (int i = 0; i < strS; i++) {
		for (int j = 0; j < chrS; j++) {
			cout << "iCBS: " << chr[j] << " : " << (int)chr[j] << endl;
			if (str == chr[j])return true;
		}
	}
	cout << "========== = In iCBS: char not str" << endl;
	return false;
}

void str::split(string line, char split, vector<string> & part) {
	string buffer = ""; //буфферная строка
	for (int i = 0; i < line.size(); i++) {
		if (line[i] != split)
			buffer += line[i];
		else {
			part.push_back(buffer);
			buffer = "";
		}
	}
	part.push_back(buffer);
}