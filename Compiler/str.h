#pragma once
#ifndef STR_H
#define STR_H

using namespace std;

namespace str {
	extern string letters; // = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" }; //54 символа
	extern string digits; // = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" }; //54 символа
	bool onlySpace(string str);
	string CharRand();
	bool isChrBeStr(char str, string chr);
	void split(string line, char split, vector<string> & part);
	vector<int> allCharPos(string s, char ch);
	bool isStrInStr(string s, int pos, string t);
}

#endif // !STR_H