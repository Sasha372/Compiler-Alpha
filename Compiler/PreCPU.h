#ifndef PRECPU_H
#include <vector>
#define PRECPU_H
using namespace std;

namespace PreCPU {
	typedef vector<string> code;
	extern vector<string> listDef_from;
	extern vector<string> listDef_to;
	extern int countDef;

	//extern vector<string> listReq; //���� � require
	//extern vector<int> listReqPos; //���� ������� require

	int GetCountDef(); //���������� ������ ������� � def
	void GetListDef(int id, string & from, string & to); //���������� �������� �� ��������� id

	string direct[];

	void processCode(string & istr, code & ostr);

	string delStrComment(string & ist);
	void SpaceCut(string & istr, string & ostr); //������� ������ �������
	void delBlkComment(code & str, code & woCom); //������� ������� ������������
	void directPreCPU(code & istr, code & ostr); //������ � �������� �������� �������������

	void direct_def(code & str, int & id, int & dir_id); //��������� ��������� "def"
	void direct_req(code & str, int & id, int & dir_id, code & ostr); //��������� ��������� "req"
}

#endif // PRECPU_H
