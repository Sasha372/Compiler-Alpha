#include "stdafx.h"
#include "Random.h"
#include "str.h"

string str::letters = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" }; //54 символа
string str::digits = { "0123456789" }; //10 символов

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

	//cout << "===========In iCBS: " << str << " : " << chr << endl;

	for (int i = 0; i < strS; i++) {
		for (int j = 0; j < chrS; j++) {
			//cout << "iCBS: " << chr[j] << " : " << (int)chr[j] << endl;
			if (str == chr[j])return true;
		}
	}
	//cout << "===========In iCBS: char not str" << endl;
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

vector<int> str::allCharPos(string s, char ch)
{
	vector<int> rezult;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == ch)rezult.push_back(i);
	}
	return rezult;
}

bool str::isStrInStr(string s, int pos, string t)
{
	//bool rez = true;
	for (int i = 0; i < t.size(); i++) {
		if (s[i + pos] != t[i]) return false;
	}
	return true;
}
