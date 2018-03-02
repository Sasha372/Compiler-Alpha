#ifndef PRECPU_H
#include <vector>
#define PRECPU_H
using namespace std;

namespace PreCPU {

	extern vector<string> listDef_from;
	extern vector<string> listDef_to;
	extern int countDef;

	//extern vector<string> listReq; //Лист с require
	//extern vector<int> listReqPos; //лист позиций require

	int GetCountDef(); //Возвращает размер вектора с def
	void GetListDef(int id, string & from, string & to); //Возвращает значение по заданному id

	string direct[];

	void processCode(string & istr, string & ostr);

	string StrComment(string & ist);
	void SpaceCut(string & istr, string & ostr); //Удаляет лишние пробелы
	void BlkComment(string & str, string & woCom); //Удаляет блочные коммментарии
	void directPreCPU(string & istr, string & ostr); //Чтение и удаление директив препроцессора

	void direct_def(string & str, int & id, int & dir_id); //Обработка директивы "def"
	void direct_req(string & str, int & id, int & dir_id, string & ostr); //Обработка директивы "req"
}

#endif // PRECPU_H
