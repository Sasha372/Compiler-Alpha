#ifndef CODE_H
#define CODE_H
#include <vector>
using namespace std;
typedef vector<string> code;

class Code {
public:
	Code(string file, string strCom, string beginCom, string endCom);
	string nextWord();
	char nextSymbol(bool viewmode);
	char nextChar(bool viewmode);
	void skipComment(string endComm);
private:
	string filename;
	code start;
	bool isInit = false;
	bool inComment = false;
	int line, symbol;
	string strComm, beginComm, endComm;

	bool returnWord(string word, int i, int j);
	void cutStringComm(string & str);
	void cutBlockComm(code & str, code & out);
	int sizeWoCom(string str);
};

#endif // !CODE_H

