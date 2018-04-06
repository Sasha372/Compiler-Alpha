#include "stdafx.h"
#include <fstream>
#include "Code.h"
#include "str.h"
using namespace std;

Code::Code(string file, string strCom, string beginCom, string endCom, bool ShowCode)
{
	if (!isInit) {
		filename = file;
		strComm = strCom;
		beginComm = beginCom;
		endComm = endCom;
		symbol = 0;

		ifstream input(file);
		string in;
		code temp;
		while (getline(input, in))
		{
			cutStringComm(in);	
			temp.push_back(in + "\n");
		}
		input.close();
		isInit = true;
		size_t s = file.rfind("\\");
		path = file.substr(0, s) + "\\";
		cout << file << endl;

		code toOne;
		cutBlockComm(temp, toOne);

		for (auto i = toOne.begin(); i != toOne.end(); i++) {
			before.push_back(start.size());
			start += *i;
		}

		if (ShowCode) {
			cout << "============" << endl;
			cout << start << endl;
			cout << "============" << endl;
		}
	}
}

string Code::nextWord(bool viewmode)
{
	string word;
	bool inQuotes = false;
	for (int j = symbol; j < start.size(); j++) {
		char crChar = start[j];
		if (!inQuotes) {
			if ((crChar == '"') || (crChar == '\'')) {
				if (returnWord(word, j, viewmode)) return word;
				word += crChar;
				inQuotes = true;
			}
			else if (str::isChrBeStr(crChar, str::letters + str::digits)) 
				word += crChar;
			else if (returnWord(word, j, viewmode)) return word;
		}
		else {
			if ((crChar == '"') || (crChar == '\'')) {
				returnWord(word, j + 1, viewmode);
				return word + crChar;
			}
			else if (!str::isChrBeStr(crChar, "\n\r"))
				word += crChar;
			else if (returnWord(word, j, viewmode)) {
				//TODO: Ошибка не закрытой кавычки
				return word;
			}
		}
	}
}

char Code::nextSymbol(bool viewmode)
{
	for (int j = symbol; j < start.size(); j++) {
		if (!str::isChrBeStr(start[j], " \t\r\n")) {
			if (!viewmode) {
				symbol = j + 1;
			}
			return start[j];
		}
	}
	return 0;
}

char Code::nextChar(bool viewmode)
{
	//cout << "L" << symbol << endl;
	for (int j = symbol; j < start.size(); j++) {
		if (!str::isChrBeStr(start[j], "\r\n")) {
			if (!viewmode) {
				//cout << "G" << j << endl;
				symbol = j + 1;
			}
			return start[j];
		}
	}
	//cout << "M" << symbol << endl;
}

dInt Code::one2two(int x)
{
	for (int i = 0; i < before.size() - 1; i++) {
		if (before[i + 1] > x) {
			if (before[i] <= x) {
				return { i, x - before[i] };
			}
		}
	}
}

int Code::two2one(int x, int y)
{
	if ((x >= 0) && (x < before.size())) {
		if (y < (before[x] - before[x - 1])) {
			return before[x] + y;
		}
	}
}

string Code::getLine(int line)
{
	return string();
}

string Code::getPath()
{
	return path;
}

bool Code::isEnd()
{
	char nS = nextSymbol(true);
	if (symbol > start.size() + 1)return true;
	if (str::isChrBeStr(nS, "" + '\0' + ' '))return true;
	else return false;
}

void Code::error(int id,string s)
{
	error_t t { Err, "", id, one2two(symbol).one, s };
	cout << "Error " << t.id << " in line " << t.line << " : " << s << " : " << one2two(symbol).two  << endl;
	errors.push_back(t);
}

bool Code::returnWord(string word, int j, bool view)
{
	if (!word.empty()) {
		if (!view)symbol = j; //view = false
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
