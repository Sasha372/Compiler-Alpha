#ifndef PRECPU_H
#include <vector>
#define PRECPU_H
using namespace std;

namespace PreCPU {

	extern vector<string> listDef_from;
	extern vector<string> listDef_to;
	extern int countDef;

	//extern vector<string> listReq; //���� � require
	//extern vector<int> listReqPos; //���� ������� require

	int GetCountDef(); //���������� ������ ������� � def
	void GetListDef(int id, string & from, string & to); //���������� �������� �� ��������� id

	string direct[];

	void processCode(string & istr, string & ostr);

	string StrComment(string & ist);
	void SpaceCut(string & istr, string & ostr); //������� ������ �������
	void BlkComment(string & str, string & woCom); //������� ������� ������������
	void directPreCPU(string & istr, string & ostr); //������ � �������� �������� �������������

	void direct_def(string & str, int & id, int & dir_id); //��������� ��������� "def"
	void direct_req(string & str, int & id, int & dir_id, string & ostr); //��������� ��������� "req"
}

#endif // PRECPU_H
