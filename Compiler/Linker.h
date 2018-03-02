#ifndef LINKER_H
#define LINKER_H

#include <vector>
using namespace std;

namespace Linker{
	void Process(vector<string> & istr, vector<string> & ostr);
	void Search(vector<string> & istr, vector<string>& ostr);
	void Apply(vector<string> & istr, vector<string> & ostr);

	int searchAdr(string & str);
	void readAdr(string & istr, string & ostr, int id_b, int id_e);
	void setAdr(string & istr, int id, int adr);
}

#endif // !LINKER_H

