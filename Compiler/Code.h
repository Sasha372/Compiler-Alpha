#ifndef CODE_H
#define CODE_H

#define Err 1

#include <vector>
using namespace std;
typedef vector<string> code;

struct dInt {
	int one;
	int two;
};

struct error_t {
	int type; //Warring, error, critical error
	string name;
	int id;
	int line;
	string word;
};

class Code {
public:
	Code(string file, string strCom, string beginCom, string endCom, bool ShowCode = false);
	string nextWord(bool viewmode = false);
	char nextSymbol(bool viewmode = false);
	char nextChar(bool viewmode = false);

	dInt one2two(int x);
	int two2one(int x, int y);
	string getLine(int line);
	string getPath();
	bool isEnd();

	void error(int id, string s);
private:
	string filename;
	string path;

	string start;
	vector<int> before; //Begins of strings

	bool isInit = false;
	int line, symbol;
	string strComm, beginComm, endComm;
	vector<error_t> errors;

	bool returnWord(string word, int j, bool view);
	void cutStringComm(string & str);
	void cutBlockComm(code & str, code & out);
};

#endif // !CODE_H

