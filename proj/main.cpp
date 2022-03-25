#include "hospital.h"
#include "department.h"
#include "doctor.h"
#include "patient.h"
#include "otherstuff.h"
//Выбрать номер отделения(позиция в массиве)
int chooseDep(hospital DanInc)
{
	system("cls");
	int depchsn;
	cout << "Choose a department" << endl;
	for (int i = 0; i < DanInc.dpnum; i++)
	{
		cout << i + 1 << ". " << DanInc.dp[i].name << endl;
	}
	cout << "0. Exit" << endl;
	while (true)
	{
		cin >> depchsn;
		if (depchsn >= 0 && depchsn <= DanInc.dpnum) break;
	}
	depchsn--;
	return depchsn;
}

//Выбрать номер пациента(позиция в массиве) в выбранном отделении
int choosePat(hospital DanInc, int depchsn)
{
	system("cls");
	int patchsn;
	cout << "Choose a patient" << endl;
	for (int pat = 0; pat < DanInc.dp[depchsn].ptnsnum; pat++)
	{
		cout << pat + 1 << ". " << DanInc.dp[depchsn].ptns[pat].flname << endl;
	}
	cout << "0. Exit" << endl;
	while (true)
	{
		cin >> patchsn;
		if (patchsn >= 0 && patchsn <= DanInc.dp[depchsn].ptnsnum) break;
	}
	patchsn--;
	return patchsn;
}

//Выбрать номер доктора(позиция в массиве) в выбранном отделении
int chooseDoc(hospital DanInc, int depchsn)
{
	system("cls");
	int docchsn;
	cout << "Choose a doctor" << endl;
	for (int doc = 0; doc < DanInc.dp[depchsn].docsnum; doc++)
	{
		cout << doc + 1 << ". " << DanInc.dp[depchsn].docs[doc].flname << endl;
	}
	cout << "0. Exit" << endl;
	while (true)
	{
		cin >> docchsn;
		if (docchsn >= 0 && docchsn <= DanInc.dp[depchsn].docsnum) break;
	}
	docchsn--;
	return docchsn;
}

//Проверить выход
bool chkexit()
{
	cout << "Continue? Yes - 1, No - 0" << endl;
	int chk;
	while (true)
	{
		cin >> chk;
		if (chk == 0 || chk == 1) break;
	}
	system("cls");
	if (chk == 0) return true;
	else return false;
}

int main() {
	int changedentity = 0;//Изменённые данные
	//Автосейв - через каждые 3 изменения
	//Сейв при выходе - если не происходил перед этим Автосейв и/или не были затронуты данные
	int mainmenu;//Отвечает за выбор функции
	hospital DanInc;
	//Если возникла ошибка в чтении - прекращаем работу
	if (!DanInc.read())
	{
		cout << "There is a problem reading the data base" << endl;
		system("pause");
		return 0;
	}
	do
	{
		system("cls");
		cout << "\tHospital name: " << DanInc.HospName << endl;
		//Показ меню и выбор функции
		showmainmenu();
		while (true)
		{
			cin >> mainmenu;
			if (mainmenu >= 0 && mainmenu <= 16) break;
		}
		//Активация функций
		switch (mainmenu)
		{
		case 1 :
		//Добавление пациента
		{
			char *other = new char[6]{ "Other" };
			int depchsn = chooseDep(DanInc);
			if (depchsn == -1) break;
			system("cls");
			patient *upddprt = new patient[DanInc.dp[depchsn].ptnsnum + 1];
			for (int i = 0; i < DanInc.dp[depchsn].ptnsnum; i++)
			{
				DanInc.dp[depchsn].ptns[i].copyto(upddprt[i]);
			}
			while (true)
			{
				upddprt[DanInc.dp[depchsn].ptnsnum].fill('a');
				bool tobreak = true;
				for (int i = 0; i < DanInc.dp[depchsn].ptnsnum; i++)
				{
					int c = 0;
					for (int z = 0; upddprt[DanInc.dp[depchsn].ptnsnum].flname[z] != '\0' || DanInc.dp[depchsn].ptns[i].flname[z] != '\0';z++)
					{
						if (upddprt[DanInc.dp[depchsn].ptnsnum].flname[z] == DanInc.dp[depchsn].ptns[i].flname[z]) c++;
					}
					if (c == strlen(DanInc.dp[depchsn].ptns[i].flname) && c == strlen(upddprt[DanInc.dp[depchsn].ptnsnum].flname))
					{
						tobreak = false;
						break;
					}
				}
				if (tobreak) break;
				else
				{
					cout << "There are problems with the name, try once again" << endl;
					system("pause");
				}
			}
			cout << "Patient's room number" << endl;
			while (true)
			{
				bool tobreak = true;
				cin >> upddprt[DanInc.dp[depchsn].ptnsnum].rmnum;
				if (upddprt[DanInc.dp[depchsn].ptnsnum].rmnum <= 0 || upddprt[DanInc.dp[depchsn].ptnsnum].rmnum > (DanInc.dp[depchsn].frsrom + 149) || upddprt[DanInc.dp[depchsn].ptnsnum].rmnum < DanInc.dp[depchsn].frsrom)
				{
					tobreak = false;
				}
				for (int i = 0; i < DanInc.dp[depchsn].ptnsnum; i++)
				{
					if (DanInc.dp[depchsn].ptns[i].rmnum == upddprt[DanInc.dp[depchsn].ptnsnum].rmnum && upddprt[DanInc.dp[depchsn].ptnsnum].isout == false && DanInc.dp[depchsn].ptns[i].isout == false)
					{
						tobreak = false;
						break;
					}
				}
				if (tobreak) break;
			}
			cout << "Choose a doctor" << endl;
			int last = 1;
			for (int i = 0; i < DanInc.dp[depchsn].docsnum; i++, last++)
			{
				cout << i + 1 << ". " << DanInc.dp[depchsn].docs[i].flname << endl;
			}
			cout << last << ". Other" << endl;
			int chsndoc;
			while (true)
			{
				cin >> chsndoc;
				if (chsndoc > 0 && chsndoc <= last) break;
			}
			chsndoc--;
			if (chsndoc != last - 1) 
			{
				strcpy(upddprt[DanInc.dp[depchsn].ptnsnum].dctname, DanInc.dp[depchsn].docs[chsndoc].flname);
			}
			else
			{
				strcpy(upddprt[DanInc.dp[depchsn].ptnsnum].dctname, other);
			}
			DanInc.dp[depchsn].ptnsnum++;
			delete[] DanInc.dp[depchsn].ptns;
			DanInc.dp[depchsn].ptns = nullptr;
			DanInc.dp[depchsn].ptns = new patient[DanInc.dp[depchsn].ptnsnum];
			for (int copy = 0; copy < DanInc.dp[depchsn].ptnsnum; copy++)
			{
				upddprt[copy].copyto(DanInc.dp[depchsn].ptns[copy]);
			}
			delete[] upddprt;
			upddprt = nullptr;
			changedentity++;
			break;
		} 
		case 2:
		//Удаление пациента
		{
			char path[] = { "Hospital\\" }, pat[] = {"Patients"};
			int depchsn = chooseDep(DanInc);
			if (depchsn == -1) break;
			if (DanInc.dp[depchsn].ptnsnum > 0)
			{
				int patchsn = choosePat(DanInc, depchsn);
				if (patchsn == -1) break;
				patient *wopat = new patient[DanInc.dp[depchsn].ptnsnum - 1];
				int copy1 = 0;
				for (int copy = 0; copy < DanInc.dp[depchsn].ptnsnum; copy++)
				{
					if (copy != patchsn)
					{
						DanInc.dp[depchsn].ptns[copy].copyto(wopat[copy1]);
						copy1++;
					}
				}
				char *pathpat = unite(path, DanInc.dp[depchsn].name);
				char *txtname = totxt(DanInc.dp[depchsn].ptns[patchsn].flname);
				pathpat = unite(pathpat, pat);
				pathpat = unite(pathpat, txtname, 'f');
				remove(pathpat);
				DanInc.dp[depchsn].ptnsnum--;
				delete[]DanInc.dp[depchsn].ptns;
				DanInc.dp[depchsn].ptns = nullptr;
				DanInc.dp[depchsn].ptns = new patient[DanInc.dp[depchsn].ptnsnum];
				for (int copy = 0; copy < DanInc.dp[depchsn].ptnsnum; copy++)
				{
					wopat[copy].copyto(DanInc.dp[depchsn].ptns[copy]);
				}
				delete[] wopat;
				wopat = nullptr;
			}
			else cout << "There are no patients in this department" << endl;
			changedentity++;
			break;
		}
		case 3:
		//Выписывание существующего пациента
		{
			int depchsn = chooseDep(DanInc);
			if (depchsn == -1) break;
			system("cls");
			if (DanInc.dp[depchsn].ptnsnum > 0) {
				int patchsn;
				cout << "Choose a patient" << endl;
				int count = 0;
				for (int pat = 0; pat < DanInc.dp[depchsn].ptnsnum; pat++)
				{
					if (!DanInc.dp[depchsn].ptns[pat].isout)
					{
						cout << count + 1 << ". " << DanInc.dp[depchsn].ptns[pat].flname << endl;
						count++;
					}
				}
				cout << "0. Exit" << endl;
				if (count == 0)
				{
					system("cls");
					cout << "There are no patients to discharge" << endl;
					break;
				}
				while (true)
				{
					cin >> patchsn;
					if (patchsn >= 0 && patchsn <= count)
					{
						for (int pat = 0, inp = 0; pat < DanInc.dp[depchsn].ptnsnum; pat++)
						{
							if (!DanInc.dp[depchsn].ptns[pat].isout)
							{
								inp++;
							}
							if (inp == patchsn)
							{
								patchsn = pat + 1; 
								break;
							}
						}
					}
					break;
				}
				if (patchsn == 0) break;
				patchsn--;
				DanInc.dp[depchsn].ptns[patchsn].discharge();
			}
			else cout << "There are no patients in this department" << endl;
			changedentity++;
			break;
		}
		case 4:
		//Запись существующего пациента в больницу на стационар
		{
			system("cls");
			int depchsn = chooseDep(DanInc);
			if (depchsn == -1) break;
			system("cls");
			if (DanInc.dp[depchsn].ptnsnum > 0) {
				int patchsn;
				cout << "Choose a patient" << endl;
				int count = 0;
				for (int pat = 0; pat < DanInc.dp[depchsn].ptnsnum; pat++)
				{
					if (DanInc.dp[depchsn].ptns[pat].isout)
					{
						cout << count + 1 << ". " << DanInc.dp[depchsn].ptns[pat].flname << endl;
						count++;
					}
				}
				cout << "0. Exit" << endl;
				if (count == 0)
				{
					system("cls");
					cout << "There are no patients to enroll" << endl;
					break;
				}
				while (true)
				{
					cin >> patchsn;
					if (patchsn >= 0 && patchsn <= count)
					{
						for (int pat = 0, inp = 0; pat < DanInc.dp[depchsn].ptnsnum; pat++)
						{
							if (DanInc.dp[depchsn].ptns[pat].isout)
							{
								inp++;
							}
							if (inp == patchsn)
							{
								patchsn = pat+1;
								break;
							}
						}
						break;
					}
				}
				if (patchsn == 0) break;
				patchsn--;
				system("cls");
				DanInc.dp[depchsn].ptns[patchsn].enroll();
				cout << "Patient's room number" << endl;
				while (true)
				{
					bool tobreak = true;
					cin >> DanInc.dp[depchsn].ptns[patchsn].rmnum;
					if (DanInc.dp[depchsn].ptns[patchsn].rmnum <= 0 || DanInc.dp[depchsn].ptns[patchsn].rmnum > (DanInc.dp[depchsn].frsrom + 149) || DanInc.dp[depchsn].ptns[patchsn].rmnum < DanInc.dp[depchsn].frsrom) tobreak = false;
					for (int i = 0; i < DanInc.dp[depchsn].ptnsnum; i++)
					{
						 if (DanInc.dp[depchsn].ptns[i].rmnum == DanInc.dp[depchsn].ptns[patchsn].rmnum && DanInc.dp[depchsn].ptns[i].isout == false && i != patchsn)tobreak = false;
					}
					if (tobreak) break;
				}
			}
			else cout << "There are no patients in this department" << endl;
			changedentity++;
			break;
		}
		case 5:
		//Получение информации о пациенте
		{
			int depchsn = chooseDep(DanInc);
			if (depchsn == -1) break;
			if (DanInc.dp[depchsn].ptnsnum > 0) 
			{
				int patchsn = choosePat(DanInc, depchsn);
				if (patchsn == -1) break;
				DanInc.dp[depchsn].ptns[patchsn].print();
			}
			else cout << "There are no patients in this department" << endl;
			break;
		}
		case 6:
		//Показать пациентов в отделении(всех)
		{
			system("cls");
			int depchsn = chooseDep(DanInc);
			if (depchsn == -1) break;
			system("cls");
			cout << "\tThose that are in the hospital:" << endl;
			int z = 1;
			for (int i = 0; i < DanInc.dp[depchsn].ptnsnum; i++)
			{
				if (!DanInc.dp[depchsn].ptns[i].isout)
				{
					cout << z << ". " << DanInc.dp[depchsn].ptns[i].flname << endl;
					z++;
				}
			}
			if (z == 1) cout << "There are no patients in the department" << endl;
			cout << endl;
			cout << "\tThose that are out:" << endl;
			int k = 1;
			for (int i = 0; i < DanInc.dp[depchsn].ptnsnum; i++)
			{
				if (DanInc.dp[depchsn].ptns[i].isout)
				{
					cout << k << ". " << DanInc.dp[depchsn].ptns[i].flname << endl;
					k++;
				}
			}
			if (k == 1) cout << "There are no patients out" << endl;
			break;
		}
		case 7:
		//Изменить информацию о пациенте(День рождения, записи, выписки из больницы + анализы, консультации специалистов и назначенные препараты)
		{
			system("cls");
			int depchsn = chooseDep(DanInc);
			if (depchsn == -1) break;
			if (DanInc.dp[depchsn].ptnsnum > 0)
			{
				int ptnchsn = choosePat(DanInc, depchsn);
				if (ptnchsn == -1) break;
				DanInc.dp[depchsn].ptns[ptnchsn].changesomething();
			} else cout << "There are no patients in this department" << endl;
			changedentity++;
			break;
		}
		case 8:
		//Изменить комнату пациента
		{
			system("cls");
			int depchsn = chooseDep(DanInc);
			if (depchsn == -1) break;
			if (DanInc.dp[depchsn].ptnsnum > 0)
			{
				int ptnchsn = choosePat(DanInc, depchsn);
				if (ptnchsn == -1) break;
				if (DanInc.dp[depchsn].ptns[ptnchsn].isout) 
				{
					cout << "You cannot change a room of a discharged patient" << endl;
					break;
				}
				cout << "Patient's new room number" << endl;
				while (true)
				{
					bool tobreak = true;
					cin >> DanInc.dp[depchsn].ptns[ptnchsn].rmnum;
					if (DanInc.dp[depchsn].ptns[ptnchsn].rmnum <= 0 || DanInc.dp[depchsn].ptns[ptnchsn].rmnum > (DanInc.dp[depchsn].frsrom + 149) || DanInc.dp[depchsn].ptns[ptnchsn].rmnum < DanInc.dp[depchsn].frsrom) {
						tobreak = false;
						continue;
					}
					for (int i = 0; i < DanInc.dp[depchsn].ptnsnum; i++)
					{
						if (DanInc.dp[depchsn].ptns[i].rmnum == DanInc.dp[depchsn].ptns[ptnchsn].rmnum && DanInc.dp[depchsn].ptns[i].isout == false && i!=ptnchsn) tobreak = false;
					}
					if (tobreak) break;
				}
			}
			changedentity++;
			break;
		}
		case 9:
		//Изменить доктора пациента
		{
			system("cls");
			char other[] = { "Other" };
			int depchsn = chooseDep(DanInc);
			if (depchsn == -1) break;
			if (DanInc.dp[depchsn].ptnsnum > 0)
			{
				int patchsn = choosePat(DanInc, depchsn);
				if (patchsn == -1) break;
				cout << "Choose a doctor" << endl;
				for (int i = 0; i < DanInc.dp[depchsn].docsnum; i++)
				{
					cout << i + 1 << ". " << DanInc.dp[depchsn].docs[i].flname << endl;
				}
				cout << DanInc.dp[depchsn].docsnum + 1<< ". Other" << endl;
				int docchsn;
				while (true)
				{
					cin >> docchsn;
					if (docchsn >= 1 && docchsn <= DanInc.dp[depchsn].docsnum+1) break;
				}
				docchsn--;
				if (docchsn != DanInc.dp[depchsn].docsnum)strcpy(DanInc.dp[depchsn].ptns[patchsn].dctname, DanInc.dp[depchsn].docs[docchsn].flname);
				else strcpy(DanInc.dp[depchsn].ptns[patchsn].dctname, other);
				changedentity++;
			}
			else cout << "There are no patients to choose from" << endl;
			break;
		}
		case 10:
		//Получение информации о докторе
		{
			system("cls");
			int depchsn = chooseDep(DanInc);
			if (depchsn == -1) break;
			int docchsn = chooseDoc(DanInc, depchsn);
			if (docchsn == -1) break;
			DanInc.dp[depchsn].docs[docchsn].print();
			break;
		}
		case 11:
		//Показать докторов в отделении(всех)
		{
			system("cls");
			int depchsn = chooseDep(DanInc);
			if (depchsn == -1) break;
			system("cls");
			cout << "Doctors in " << DanInc.dp[depchsn].name << endl;
			for (int i = 0; i < DanInc.dp[depchsn].docsnum; i++)
			{
				cout << i + 1 << ". " << DanInc.dp[depchsn].docs[i].flname << endl;
			}
			break;
		}
		case 12:
		//Добавление доктора
		{
			int depchsn = chooseDep(DanInc);
			if (depchsn == -1) break;
			system("cls");
			doctor *upddoc = new doctor[DanInc.dp[depchsn].docsnum + 1];
			for (int i = 0; i < DanInc.dp[depchsn].docsnum; i++)
			{
				DanInc.dp[depchsn].docs[i].copyto(upddoc[i]);
			}
			while (true)
			{
				upddoc[DanInc.dp[depchsn].docsnum].fill();
				bool tobreak = true;
				for (int i = 0; i < DanInc.dp[depchsn].docsnum; i++)
				{
					int c = 0;
					for (int z = 0; upddoc[DanInc.dp[depchsn].docsnum].flname[z] != '\0' || DanInc.dp[depchsn].docs[i].flname[z] != '\0'; z++)
					{
						if (upddoc[DanInc.dp[depchsn].docsnum].flname[z] == DanInc.dp[depchsn].docs[i].flname[z]) c++;
					}
					if (c == strlen(DanInc.dp[depchsn].docs[i].flname) && c == strlen(upddoc[DanInc.dp[depchsn].docsnum].flname))
					{
						tobreak = false;
						break;
					}
				}
				if (tobreak) break;
				else
				{
					cout << "There are problems with the name, try once again" << endl;
					system("pause");
				}
			}
			DanInc.dp[depchsn].docsnum++;
			delete[] DanInc.dp[depchsn].docs;
			DanInc.dp[depchsn].docs = nullptr;
			DanInc.dp[depchsn].docs = new doctor[DanInc.dp[depchsn].docsnum];
			for (int copy = 0; copy < DanInc.dp[depchsn].docsnum; copy++)
			{
				upddoc[copy].copyto(DanInc.dp[depchsn].docs[copy]);
			}
			delete[] upddoc;
			upddoc = nullptr;
			changedentity++;
			break;
		}
		case 13:
		//Удаление доктора
		{
			system("cls");
			char path[] = { "Hospital\\" }, doc[] = { "Doctors" }, other[] = { "Other" };
			int depchsn = chooseDep(DanInc);
			if (depchsn == -1) break;
			if (DanInc.dp[depchsn].docsnum >= 2)
			{
				int docchsn = chooseDoc(DanInc, depchsn);
				if (docchsn == -1) break;
				doctor *wodoc = new doctor[DanInc.dp[depchsn].docsnum - 1];
				int copy1 = 0;
				for (int copy = 0; copy < DanInc.dp[depchsn].docsnum; copy++)
				{
					if (copy != docchsn)
					{
						DanInc.dp[depchsn].docs[copy].copyto(wodoc[copy1]);
						copy1++;
					}
				}
				char *pathdoc = unite(path, DanInc.dp[depchsn].name);
				char *txtname = totxt(DanInc.dp[depchsn].docs[docchsn].flname);
				pathdoc = unite(pathdoc, doc);
				pathdoc = unite(pathdoc, txtname, 'f');
				remove(pathdoc);
				for (int i = 0; i < DanInc.dp[depchsn].ptnsnum;i++)
				{
					bool tochange = true;
					for (int z = 0; DanInc.dp[depchsn].ptns[i].dctname[z] != '\0' && DanInc.dp[depchsn].docs[docchsn].flname[z] != '\0';z++)
					{
						if (DanInc.dp[depchsn].ptns[i].dctname[z] != DanInc.dp[depchsn].docs[docchsn].flname[z])
						{
							tochange = false;
							break;
						}
					}
					if (tochange) strcpy(DanInc.dp[depchsn].ptns[i].dctname, other);
				}
				DanInc.dp[depchsn].docsnum--;
				delete[] DanInc.dp[depchsn].docs;
				DanInc.dp[depchsn].docs = nullptr;
				DanInc.dp[depchsn].docs = new doctor[DanInc.dp[depchsn].docsnum];
				for (int copy = 0; copy < DanInc.dp[depchsn].docsnum; copy++)
				{
					wodoc[copy].copyto(DanInc.dp[depchsn].docs[copy]);
				}
				delete[] wodoc;
				wodoc = nullptr;
				changedentity++;
			}
			else cout << "There is 1 doctor in the department, please add 1 to delete" << endl;
			break;
		}
		case 14:
		//Изменение информации о докторе
		{
			system("cls");
			int depchsn = chooseDep(DanInc);
			if (depchsn == -1) break;
			int docchsn = chooseDoc(DanInc, depchsn);
			if (docchsn == -1) break;
			DanInc.dp[depchsn].docs[docchsn].changesomething();
			changedentity++;
			break;
		}
		case 15:
		//Добавление отделения
		{
			system("cls");
			if (chkexit()) break;
			department *upddp = new department[DanInc.dpnum + 1];
			for (int i = 0; i < DanInc.dpnum; i++)
			{
				DanInc.dp[i].copyto(upddp[i]);
			}
			//заполняем новое отделение
			cout << "First room number" << endl;
			while (true)
			{
				bool tobreak = true;
				cin >> upddp[DanInc.dpnum].frsrom;
				for (int i = 0; i < DanInc.dpnum; i++)
				{
					//Номер первой комнаты - 1, 151, 301 и т.д, тогда если первая комната занимает место другого отделения или (номер первой комнаты - 1) не кратен 150, мы не принимаем значения комнаты
					if ((upddp[DanInc.dpnum].frsrom >= DanInc.dp[i].frsrom && upddp[DanInc.dpnum].frsrom <= DanInc.dp[i].frsrom + 149) || (upddp[DanInc.dpnum].frsrom - 1) % 150 != 0) tobreak = false;
				}
				if (tobreak) break;
			}
			upddp[DanInc.dpnum].fill();
			if (upddp[DanInc.dpnum].docsnum == 0) break;
			
			//перезаписываем массив с отделениями с уже добаленным новым отделением
			for (int dep = 0; dep < DanInc.dpnum; dep++)
			{
				delete[] DanInc.dp[dep].ptns;
				DanInc.dp[dep].ptns = nullptr;
				delete[] DanInc.dp[dep].docs;
				DanInc.dp[dep].docs = nullptr;

			}
			delete[] DanInc.dp;
			DanInc.dp = nullptr;
			DanInc.dp = new department[DanInc.dpnum + 1];
			DanInc.dpnum++;
			for (int i = 0; i < DanInc.dpnum; i++)
			{
				upddp[i].copyto(DanInc.dp[i]);
			}
			delete[] upddp;
			upddp = nullptr;
			changedentity++;
			break;
		}
		case 16:
		//Изменение имени больницы
		{
			system("cls");
			if (chkexit()) break;
			cout << "Enter the new Hospital name" << endl;
			cin.ignore();
			while (true)
			{
				cin.getline(DanInc.HospName, NMSZ);
				if (checkname(DanInc.HospName)) break;
			}
			changedentity++;
			break;
		}
		}
		if (mainmenu != 0) system("pause");
		//Автосейв
		if (changedentity >= 3) {
			DanInc.write();
			changedentity = 0;
		}
	} while (mainmenu != 0);
	//Сейв при выходе
	if(changedentity != 0) DanInc.write();
	return 0;
}