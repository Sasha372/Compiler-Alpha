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
			cout << in << endl;
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
		for (int j = symbol; j < start[i].size(); j++) {
			if (!inQuotes) {
				if (!str::isChrBeStr(start[i][j], "	 \n\r")) {
					if (str::isChrBeStr(start[i][j], str::letters + str::digits)) {
						word += start[i][j];
					}
					else if (!word.empty()) {
						line = i;
						symbol = j;
						return word;
					}
				}
				else if (!word.empty()) {
					line = i;
					symbol = j;
					return word;
				}
			}
			else {

			}
		}
	}
}

void Code::print()
{
	//for (int i = 0; i < body[7].size(); i++)
		//cout << i << " : " << body[7][i] << endl;
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

//Вернет false если символ есть в строке
bool str::isChrBeStr(char str, string chr) {
	int strS = 1;// str.size();
	int chrS = chr.size();

	for (int i = 0; i < strS; i++) {
		for (int j = 0; j < chrS; j++)
			if (str == chr[j])return false;
	}
	return true;
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