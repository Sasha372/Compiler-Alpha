#ifndef STR_H
#define STR_H
#include <vector>
using namespace std;
typedef vector<string> code;

namespace str {
	extern string letters; // = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" }; //54 символа
	extern string digits; // = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" }; //54 символа
	bool onlySpace(string str);
	string CharRand();
	bool isChrBeStr(char str, string chr);
	void split(string line, char split, vector<string> & part);
}

class Code {
public:
	Code(string file);
	string nextWord();
	void print();
private:
	string filename;
	code start;
	bool isInit = false;
	int line, symbol;
	bool returnWord(string word, int i, int j);
	int sizeWoCom(string str);
};

#endif // !STR_H

