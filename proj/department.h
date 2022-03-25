#pragma once
#include "otherstuff.h"
#include "doctor.h"
#include "patient.h"
struct department
{
	char name[NMSZ]{};//��� ���������
	int rmnb = 150; //������������� ��� ������ ��������� ���-�� ������
	int frsrom;//����� ������ �������
	doctor *docs;//������ �������� � ���������
	int docsnum;//���������� �������� � ���������
	patient *ptns;//������ ��������� � ���������
	int ptnsnum;//���������� ��������� � ���������

	//����������� ��������� ���������
	void copyto(department &a)
	{
		strcpy(a.name, name);
		a.rmnb = 150;
		a.frsrom = frsrom;
		a.docs = new doctor[docsnum];
		a.docsnum = docsnum;
		for (int i = 0; i < docsnum; i++)
		{
			docs[i].copyto(a.docs[i]);
		}
		a.ptns = new patient[ptnsnum];
		a.ptnsnum = ptnsnum;
		for (int i = 0; i < ptnsnum; i++)
		{
			ptns[i].copyto(a.ptns[i]);
		}
	}

	//���������� ��������� ���������
	void fill()
	{
		int	ptnsnumin;//������� ��������� � �� ������ ������ � ���������
		int	ptnsnumout;//���������� �� ���������
		//��� ���������
		cout << "Name of the department" << endl;
		cin.ignore();
		while (true)
		{
			cin.getline(name, NMSZ);
			if (checkname(name)) break;
		}
		system("cls");
		//���������� �������� - ���� 0, �� �� ������ ���������
		cout << "Doctors number at the departure currently" << endl;
		while (true)
		{
			cin >> docsnum;
			if (docsnum >= 0) break;
		}
		if (docsnum == 0) return;
		docs = nullptr;
		docs = new doctor[docsnum];
		cout << "Enter data" << endl;
		for (int i = 0; i < docsnum; i++)
		{
			docs[i].fill();
			system("cls");
		}
		//���������� ��������� - ����� ���� � 0, ��������� ������� ���, ��� ������� � ���������, ����� ���, ��� ��������
		cout << "Patients number at the department currently" << endl;
		while (true)
		{
			cin >> ptnsnumin;
			if (ptnsnumin <= rmnb && ptnsnumin >= 0) break;
		}
			cout << "Enter the data:" << endl;
			patient *p1 = new patient[ptnsnumin];
			if (ptnsnumin != 0) {
				for (int i = 0; i < ptnsnumin; i++)
				{
					cout << "Patient " << i + 1 << endl << endl;
					p1[i].fill('w');
					p1[i].isout = false;
					system("cls");
				}
			}
			else p1 = nullptr;
		system("cls");
		cout << "Discharged patients number" << endl;
		while (true)
		{
			cin >> ptnsnumout;
			if (ptnsnumout >= 0) break;
		}
		patient *p2 = new patient[ptnsnumout];
			if (ptnsnumout != 0) {
			cout << "Enter data" << endl;
			for (int i = 0; i < ptnsnumout; i++)
			{
				cout << "Patient " << i + 1 << endl << endl;
				p2[i].fill('w');
				p2[i].discharge();
				system("cls");
			}
			}
			else p2 = nullptr;
		ptnsnum = ptnsnumin + ptnsnumout;
		//���������� �� ���� ��������� ���� � ������ ������
		ptns = nullptr;
		ptns = new patient[ptnsnum];
		for (int i = 0; i < ptnsnum; i++)
		{
			if (i < ptnsnumin)
			{
				p1[i].copyto(ptns[i]);
			}
			else
			{
				p2[i].copyto(ptns[i - ptnsnumin]);
			}
		}
		delete[] p1, p2;
		p1 = nullptr;
		p2 = nullptr;
		char other[] = { "Other" };
		//�������� �������� �� ������(�������� ������� "������") ��� ���������
		for (int i = 0; i < ptnsnum; i++)
		{
			system("cls");
			cout << "Choose a Doctor for " << ptns[i].flname << ":" << endl;
			for (int z = 0; z < docsnum; z++)
			{
				cout << z + 1 << ". " << docs[z].flname << endl;
			}
			cout << docsnum + 1 << ". Other" << endl;
			int docchsn;
			while (true)
			{
				cin >> docchsn;
				if (docchsn >= 1 && docchsn <= docsnum + 1) break;
			}
			docchsn--;
			if (docchsn == docsnum) strcpy(ptns[i].dctname, other);
			else  strcpy(ptns[i].dctname, docs[docchsn].flname);
		}
	}

	//������ ��������� department � ����� hospital
	void write()
	{
		WIN32_FIND_DATA FindFileData;
		HANDLE hf;
		char *path = new char[10]{ "Hospital\\" };
		//��� �������� ��������� ����� departinfo.txt
		char  Doc[] = { "Doctors" }, Pat[] = { "Patients" }, inf[] = { "departinfo.txt" }, infpt[] = { "Patients number:" }, infdc[] = { "Doctors number:" }, inffrm[] = {"First room:"};
		char *pathfind = pathToFind(path);
		//���� ��� ����� hospital - �� ����������
		hf = FindFirstFile(pathfind, &FindFileData);
		if (hf != INVALID_HANDLE_VALUE)
		{
			bool isnew = false;
			char *createpath = unite(path, name, 'f');
			//������, ����� �� ���������, ������� �� ����������, ������ ��� ���� ����� - ������ ��������������� ����������
			hf = FindFirstFile(pathfind, &FindFileData);
			FindNextFile(hf, &FindFileData);
			while (FindNextFile(hf, &FindFileData))
			{
				for (int check = 0; FindFileData.cFileName[check] != '\0' && name[check] != '\0'; check++)
				{
					if (FindFileData.cFileName[check] != name[check]) {
						isnew = true;
						break;
					}
				}
			}
			if(isnew) CreateDirectory(createpath, NULL);
			//���������� ���� departinfo.txt - ���������� ��� ���������
			createpath = unite(path, name);
			char *fileinf = unite(createpath, inf, 'f');
			FILE *fb = fopen(fileinf, "w");
			fwrite(infpt, sizeof(char), strlen(infpt), fb);
			fputc('\n', fb);
			fprintf(fb, "%d", ptnsnum);
			fputc('\n', fb);
			fwrite(infdc, sizeof(char), strlen(infdc), fb);
			fputc('\n', fb);
			fprintf(fb, "%d", docsnum);
			fputc('\n', fb);
			fwrite(inffrm, sizeof(char), strlen(inffrm), fb);
			fputc('\n', fb);
			fprintf(fb, "%d", frsrom);
			fputc('\n', fb);
			fclose(fb);
			char *createDocpath = unite(createpath, Doc, 'f');
			if(isnew)CreateDirectory(createDocpath, NULL);
			createDocpath = unite(createpath, Doc);
			for (int i = 0; i < docsnum; i++)
			{
				docs[i].write(createDocpath);
			}
			char *createPatpath = unite(createpath, Pat, 'f');
			if(isnew)CreateDirectory(createPatpath, NULL);
			createPatpath = unite(createpath, Pat);
			for (int i = 0; i < ptnsnum; i++)
			{
				ptns[i].write(createPatpath);
			}
		}
	}
};