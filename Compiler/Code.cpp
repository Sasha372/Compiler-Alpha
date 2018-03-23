#include "stdafx.h"
#include <fstream>
#include "Code.h"
#include "Random.h"
using namespace std;

Code::Code(string file)
{
	if (!isInit) {
		filename = file;
		ifstream input(file);
		string in;
		while (getline(input, in))
		{
			start.push_back(in);
			//cout << in << endl;
		}
		input.close();
		line = 0;
		symbol = 0;
		isInit = true;
	}
}

string Code::nextWord()
{
	string word;
	for (int i = line; i < start.size(); i++) {
		bool inQuotes = false;
		int size = sizeWoCom(start[i]);
		for (int j = symbol; j < size; j++) {
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
	for (int i = line; i < start.size(); i++) 
		for (int j = symbol; j < start[i].size(); j++) 
			if (!str::isChrBeStr(start[i][j], "		\n\r")) {
				if (!viewmode) {
					line = i;
					symbol = j + 1;
				}
				return start[i][j];
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

bool Code::returnWord(string word, int i, int j)
{
	if (!word.empty()) {
		line = i;
		symbol = j;
		return true;
	}
	return false;
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

	for (int i = 0; i < strS; i++) {
		for (int j = 0; j < chrS; j++)
			if (str == chr[j])return true;
	}
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