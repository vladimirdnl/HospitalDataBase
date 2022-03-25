#define _CRT_SECURE_NO_WARNINGS
#pragma once
#define INSZ 2048 //���������������� ��������� ��� ������� ������ ���� ����� �������� � �.�.
#define NMSZ 181 //���������������� ��������� ��� ������� ������ ���
#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdio>
using namespace std;
//functions//

//��� ����������, ������ �� ���
bool isleap(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) return true;
	else return false;
}

//����� ��������� �������� ��� ����- ��� ����-����
bool checkname(char *name)
{
	int c = 0; //����������� ������� � ������
	char chkfrsmbl[] = { "ABCDEFGHIJKLMNOPRQSTUVWXYZabcdefghijklmnopqrstuvwxyz '" };//������ � ������������ ���������
	for (int i = 0; i < strlen(name); i++)
	{
		for (int j = 0; j < strlen(chkfrsmbl); j++)
		{
			if (name[i] == chkfrsmbl[j]) c++;//���� ����������� ������, +1 � ����������� � ������
		}
	}
	if (c == strlen(name)) return true;//��������� ����������� �������� � ����� ������, + �������
	else return false;
}

//����� ��������� ���� � ���� ������������, �������� � �.�.
bool checkinput(char *name)
{
	int c = 0;//����������� ������� � ������
	char chkfrsmbl[] = { "ABCDEFGHIJKLMNOPRQSTUVWXYZabcdefghijklmnopqrstuvwxyz ;',./!~#%*()+-=?><$" };//������ � ������������ ���������
	for (int i = 0; i < strlen(name); i++)
	{
		for (int j = 0; j < strlen(chkfrsmbl); j++)
		{
			if (name[i] == chkfrsmbl[j]) c++;//���� ����������� ������, +1 � ����������� � ������
		}
	}
	if (c == strlen(name)) return true;//��������� ����������� �������� � ����� ������, + �������
	else return false;
}

//����� ��������� ���� � ��������� �������
bool checknumber(char *name)
{
	int c = 0;//����������� ������� � ������
	char chkfrsmbl[] = { "+0123456789" };//������ � ������������ ���������
	for (int i = 0; i < strlen(name); i++)
	{
		for (int j = 0; j < strlen(chkfrsmbl); j++)
		{
			if (name[i] == chkfrsmbl[j]) c++;//���� ����������� ������, +1 � ����������� � ������
		}
	}
	if (c == strlen(name)) return true;//��������� ����������� �������� � ����� ������, + �������
	else return false;
}

//���������� ���
void datefill(int *date, char a) 
{
	//����� �� ����� "�������" �����, ������, ��� ������
	time_t start = time(0);
	tm* Now = localtime(&start);
	//p - ���� �������� ��������, d - �������, i - ���� ���������� ��������, o - �����������
	if (a == 'p' || a == 'd' || a == 'i' || a == 'o')
	{
		if (a == 'p') cout << "Enter the year of birthday of the patient" << endl;
		else if(a == 'd') cout << "Enter the year of birthday of the doctor" << endl;
		else if(a == 'i') 	cout << "Enter the year of entering" << endl;
		else cout << "Enter the year of discharging" << endl;
		//yearcheck
		while (true)
		{
			cin >> date[2];
			if (date[2] >= 1900 && (date[2] <= Now->tm_year + 1900)) break;//���� �� ��� ��������/ ����������� ����������, �.�. ������, ��� 1900 � ������, ��� ������
		}
		if (a == 'p') cout << "Enter the month of birthday of the patient" << endl;
		else if (a == 'd') cout << "Enter the month of birthday of the doctor" << endl;
		else if (a == 'i') 	cout << "Enter the month of entering" << endl;
		else cout << "Enter the month of discharging" << endl;
		//monthcheck
		while (true)
		{
			cin >> date[1];
			if (date[2] == Now->tm_year + 1900)
			{
				if (date[1] >= 1 && date[1] <= Now->tm_mon+1) break;
			}
			else if (date[1] >= 1 && date[1] <= 12) break;
			//���� �� ����� ��������/ ����������� ����������, �.�. ������, ��� 1 � ������, ��� 12
		}
		if (a == 'p') cout << "Enter the day of birthday of the patient" << endl;
		else if (a == 'd') cout << "Enter the day of birthday of the doctor" << endl;
		else if (a == 'i') 	cout << "Enter the day of entering" << endl;
		else cout << "Enter the day of discharging" << endl;
		//bdaycheck
		while (true)
		{
			cin >> date[0];
			if (date[0] >= 1 && date[0] <= 31)
			{
				if (date[2] == Now->tm_year + 1900 && date[1] == Now->tm_mon+1 && date[0] <= Now->tm_mday) break;
				if (date[1] == 2 && isleap(date[2]) && date[0] <= 29) break;
				else if (date[1] == 2 && !isleap(date[2]) && date[0] <= 28) break;
				else if (date[1] != 2 && date[1] <= 7 && date[1] % 2 != 0) break;
				else if (date[1] != 2 && date[1] <= 7 && date[1] % 2 == 0 && date[0] <= 30) break;
				else if (date[1] >= 8 && date[1] % 2 == 0) break;
				else if (date[1] >= 8 && date[1] % 2 != 0 && date[0] <= 30) break;
				//���� �� ���� ��������/ ����������� ����������
			}
		}
	}

	if (a == 'i' || a == 'o')
	{
		if(a == 'i') cout << "Enter the time of entering" << endl;
		else cout << "Enter the time of discharging" << endl;
		cout << "Hours: ";
		while (true)
		{
			//���� �� ����� � ����� ��������/ ����������� ����������
			cin >> date[3];
			if (date[2] == Now->tm_year + 1900 && date[1] == Now->tm_mon + 1 && date[0] == Now->tm_mday)
			{
				if (date[3] >= 0 && date[3] <= Now->tm_hour) break;
			}
			else if (date[3] >= 0 && date[3] <= 23) break;
		}
		cout << "Minutes: ";
		while (true)
		{
			//���� �� ����� � ������� ��������/ ����������� ����������
			cin >> date[4];
			if (date[2] == Now->tm_year + 1900 && date[1] == Now->tm_mon + 1 && date[0] == Now->tm_mday && date[3] == Now->tm_hour)
			{
				if (a == 'o') { if (date[4] >= 0 && date[4] <= 59) break; }
				else if (date[4] >= 0 && date[4] <= Now->tm_min) break;
			}
			else if (date[4] >= 0 && date[4] <= 59) break;
		}
	}
}

//�������� - ���������� ���� ������� � ����� �����������
bool dateoutcheck(int *dateout, int *datein)
{
	if (dateout[2] < datein[2]) return false;
	else if (dateout[2] > datein[2]) return true;
	else
	{
		if (dateout[1] < datein[1]) return false;
		else if (dateout[1] > datein[1]) return true;
		else
		{
			if (dateout[0] < datein[0]) return false;
			else if (dateout[0] > datein[0]) return true;
			else 
			{
				if (dateout[3] < datein[3]) return false;
				else if (dateout[3] > datein[3]) return true;
				else
				{
					if (dateout[4] > datein[4]) return true;
					else return false;
				}
			}
		}
	}
}

//�������� - ���������� ���� �������� � ����� �����������
bool bdatecheck(int *bdate, int *datein)
{
	if (datein[2] < bdate[2]) return false;
	else if (datein[2] > bdate[2]) return true;
	else
	{
		if (datein[1] < bdate[1]) return false;
		else if (datein[1] > bdate[1]) return true;
		else
		{
			if (datein[0] < bdate[0]) return false;
			else return true;
		}
	}
}

//������ ���� �� �����
void dateprint(int *date, char a)
{
	//���� <10, �� �������� 0, ����� ��������� 09, � �� 9
	if (date[0] >= 10)cout << date[0];
	else cout << "0" << date[0];
	cout << ".";
	if (date[1] >= 10) cout << date[1];
	else cout << "0" << date[1];
	cout << ".";
	cout << date[2];
	//���� ���� ����������� � �����������, �� ����������� ����� � ����� � �������
	if (a == 'i' || a == 'o')
	{
		cout << " ";
		if (date[3] >= 10) cout << date[3];
		else cout << "0" << date[3];
		cout << ":";
		if (date[4] >= 10) cout << date[4];
		else cout << "0" << date[4];
	}
	cout << endl;
}

//������ ������ ��� ������������� � FindFirstFile
char* pathToFind(char *path1) 
{
	char *a = new char[(strlen(path1) + 4)]{};
	for (int i = 0; i < strlen(path1); i++) {
		a[i] = path1[i];
	}
	a[strlen(path1)] = '*';
	a[strlen(path1) + 1] = '.';
	a[strlen(path1) + 2] = '*';
	return a;
}

//��� ���������� ������, ������ ������ ������ ������ � ����� \\, ��� �������� � �����,
// � ������, ���� ��������� f(�������� file ��� �� folder) �� ������ � ����� \\, �����
// ��������� �� ���������� ��� ����.
char* unite(char *path1, char *path2)
{
	//������ ����� ������, � ������� ��� ����������� ������, \\ � \0
	char *path3 = new char[strlen(path1) + strlen(path2) + 2]{};
	for (int i = 0; i < strlen(path1) + strlen(path2); i++)
	{
		if (i < strlen(path1))
		{
			path3[i] = path1[i];
		}
		else
		{
			path3[i] = path2[i - strlen(path1)];
		}
	}
	path3[strlen(path3)] = '\\';
	return path3;
}
char* unite(char *path1, char *path2, char a)
{
	//���� f - �� �� ����� \\ � �������� ������ ������ ��� \0
	char *path3;
	if(a!= 'f') path3 = new char[strlen(path1) + strlen(path2) + 2]{};
	else path3 = new char[strlen(path1) + strlen(path2) + 1]{};
	for (int i = 0; i < strlen(path1) + strlen(path2); i++)
	{
		if (i < strlen(path1))
		{
			path3[i] = path1[i];
		}
		else
		{
			path3[i] = path2[i - strlen(path1)];
		}
	}
	if (a != 'f') path3[strlen(path3)] = '\\';
	return path3;
}

//���������� ��� ������ �.�.� � ������ ���
char* fullname(char *lt, char *ft, char *pt)
{
	//������ ��� ���� �������� � 3 ������� �.�.�
	int sizef = strlen(lt) + 1 + strlen(ft) + 1 + strlen(pt);
	char *flln = new char[sizef + 1]{};
	for (int i = 0; i < sizef; i++)
	{
		if (i < strlen(lt))
		{
			flln[i] = lt[i];
		}
		else if (i == strlen(lt) || i == strlen(ft) + strlen(lt) + 1) flln[i] = ' ';
		else if (i < strlen(ft) + strlen(lt) + 1)
		{
			flln[i] = ft[i - strlen(lt) - 1];
		}
		else
		{
			flln[i] = pt[i - strlen(lt) - strlen(ft) - 2];
		}
	}
	return flln;
}

//��������� ������ ��� �� ��� ������ �.�.� 
void separatename(char *fl, char *lt, char *ft, char *pt)
{
	int space = 0;
	for (int i = 0; i < strlen(fl); i++) 
	{
		if (fl[i] == ' ') space++;
		else if (space == 0) lt[i] = fl[i];
		else if (space == 1) ft[i - strlen(lt) - 1] = fl[i];
		else pt[i - strlen(lt) - strlen(ft) - 2] = fl[i];
	}
}

//��������� ������ � ����� �� '\n'
void readstring(char *a, FILE *file)
{
	int num = 0;
	for (; fgetc(file) != '\n'; num++);
	fseek(file, -num - 2, SEEK_CUR);
	fread(a, sizeof(char), num, file);
}

//��������� � ������ .txt
char* totxt(char *a)
{
	char *z = new char[strlen(a) + 5]{};
	for (int i = 0; i < strlen(a); i++)
	{
		z[i] = a[i];
	}
	z[strlen(a)] = '.';
	z[strlen(a) + 1] = 't';
	z[strlen(a) + 2] = 'x';
	z[strlen(a) + 3] = 't';
	return z;
}

//���������� ������� ����
void showmainmenu() 
{
	cout << "You're in our hospital! " << endl;
	cout << "Choose a function:" << endl << endl;
	cout << "\tPatients" << endl;
	cout << "1. Add a patient" << endl;
	cout << "2. Delete a patient " << endl;
	cout << "3. Discharge an existing patient " << endl;
	cout << "4. Enroll an existing patient " << endl;
	cout << "5. Get info about a patient" << endl;
	cout << "6. Show patients in department" << endl;
	cout << "7. Change patient's info" << endl;
	cout << "8. Change patient's room" << endl;
	cout << "9. Change patient's doctor" << endl << endl;
	cout <<"\tDoctors"<< endl;
	cout << "10. Get info about a doctor" << endl;
	cout << "11. Show doctors in department" << endl;
	cout << "12. Add a doctor" << endl;
	cout << "13. Delete a doctor" << endl;
	cout << "14. Change doctor's info" << endl << endl;
	cout << "\tDepartments" << endl;
	cout << "15. Add a department" << endl;
	cout << "(Deletion of a department requires to be done manually)" << endl << endl;
	cout << "\tHospital" << endl;
	cout << "16. Change hospital name" << endl;
	cout << "0. Exit" << endl;
}