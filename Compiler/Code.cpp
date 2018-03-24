#include "stdafx.h"
#include <fstream>
#include "Code.h"
using namespace std;

Code::Code(string file, string strCom, string beginCom, string endCom)
{
	if (!isInit) {
		filename = file;
		strComm = strCom;
		beginComm = beginCom;
		endComm = endCom;

		cout << file << endl;
		ifstream input(file);
		string in;
		code temp;
		while (getline(input, in))
		{
			cutStringComm(in);
			temp.push_back(in);
			cout << in << endl;
		}
		input.close();
		line = 0;
		symbol = 0;

		isInit = true;
		cout << "Initialization finised" << endl;

		cutBlockComm(temp, start);
		for (auto i = start.begin(); i != start.end(); i++)
			cout << *i << endl;
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
			if (!str::isChrBeStr(start[i][j], " \t\r\n")) { //9 - '	', 32 - ' '; "" + (char)13 + (char)10 + (char)32 + (char)9
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
	for (int i = line; i < start.size(); i++) {
		int end = (int)start[i].find(endComm);
		if (end != string::npos) {
			line = i;
			symbol = end + endComm.size();
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

void Code::cutStringComm(string & str)
{
	if (strComm != "") {
		int comm = str.find(strComm);
		if (comm != string::npos)
		{
			string tmp = str.substr(0, comm);
			str = tmp;
		}
	}
}

void Code::cutBlockComm(code & str, code & out)
{
	bool inComm = false;
	for (auto i = str.begin(); i != str.end(); i++)
	{
		bool inQuot = false;
		string aaa = *i;
		if ((aaa.find(beginComm) != string::npos) || (aaa.find(endComm) != string::npos)) {
			string temp;
			for (int g = 0; g < aaa.size(); g++)
			{
				char* j = &aaa[g];
				if ((*j == '"') || (*j == '\'')) inQuot = !inQuot;
				if (!inQuot) {
					if (inComm) {
						if (str::isStrInStr(*i, g, endComm)) {
							inComm = false;
							g += endComm.size();
						}
					}
					else {
						if (str::isStrInStr(*i, g, beginComm)) {
							inComm = true;
							g += beginComm.size();
						}
						else temp += *j;
					}
					/*if (str::isStrInStr(*i, id, endComm)) {
						inComm = false;
						*j += endComm.size() + 1;
					}
					else if (str::isStrInStr(*i, id, beginComm)) {
						inComm = true;
						*j += beginComm.size();
					}
					else if (!inComm) {
						temp += *j;
					}*/
				}
				else temp += *j;
			}
			if (inComm) out.push_back("");
			else out.push_back(temp);
			//cout << "1: " << *(out.end() - 1) << endl;
		}
		else {
			if (inComm) out.push_back("");
			else out.push_back(*i);
			//cout << "2: " << *(out.end() - 1) << endl;
		}
	}
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
