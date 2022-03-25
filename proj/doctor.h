#pragma once
#include "otherstuff.h"
struct doctor
{
	char ftname[NMSZ]{};//��� �������
	char ltname[NMSZ]{};//������� �������
	char pt[NMSZ]{};//�������� �������
	char *flname;//������ ��� �������
	int bday[3]{};//���� �������� �������
	char position[NMSZ]{};//��������� �������
	char category[NMSZ]{};//��������� �������
	float exp;//���� ������� � �����
	char cnmb[NMSZ]{};//���������� ����� �������

	//�a������� ��������� doctor
	void fill()
	{
		//���� ���� ��������
		datefill(bday, 'd');
		//���� � �������� �� �����
		cout << "Last name of the doctor" << endl;
		cin.ignore();
		while (true)
		{
			cin.getline(ltname, NMSZ);
			if (checkname(ltname)) break;
		}
		cout << "First name of the doctor" << endl;
		while (true)
		{
			cin.getline(ftname, NMSZ);
			if (checkname(ftname)) break;
		}
		cout << "Patronymic of the doctor" << endl;
		while (true)

		{
			cin.getline(pt, NMSZ);
			if (checkname(pt)) break;
		}
		flname = fullname(ltname, ftname, pt);
		//���� � �������� �� ����
		cout << "Experience in years" << endl;
		while (true)
		{
			cin >> exp;
			if (exp >= 0) break;
		}
		//���� � �������� �� ��������� �������
		cout << "Doctor's rank" << endl;
		cin.ignore();
		while (true)
		{
			cin.getline(position, NMSZ);
			if (checkinput(position)) break;
		}
		//���� � �������� �� ��������� �������
		cout << "The category" << endl;
		while (true)
		{
			cin.getline(category, NMSZ);
			if (checkinput(category)) break;
		}
		//���� � �������� �� ����� �������� �������
		cout << "Cellphone number" << endl;
		while (true)
		{
			cin.getline(cnmb, NMSZ);
			if (checknumber(cnmb)) break;
		}
	}

	//������� ��������� doctor �� �����
	void print()
	{
		system("cls");
		cout << "======================================================================" << endl;
		cout << "Name: " << flname << endl;
		cout << "Birthday: ";
		dateprint(bday, 'b');
		cout << "Position: " << position << endl;
		cout << "Category: " << category << endl;
		cout << "Experience: " << exp << " year";
		if (exp != 1) cout << "s";
		cout << endl;
		cout << "Cellphone number: " << cnmb << endl;
		cout << "======================================================================" << endl;
	}

	//�������� ���� ��������� doctor � ���� � ������� path
	//� ������ ��������� 3 ������� ������: fwrite, fprintf, � fputc
	//(��� ������������ � fprintf, fscanf, ����, ��� ����� ������� ������ ���� %d, %s, %f)
	void write(char *path)
	{
		//��� �������� ��������� ������ .txt
		char Bday[] = { "Birthday:" }, Pos[] = { "Position:" }, Cat[] = { "Category:" }, Exp[] = { "Experience(in years) :" }, Celnmb[] = { "Cellphone Number:" };
		char *filename = totxt(flname);
		char *Docfolderfile = unite(path, filename, 'f');
		FILE *dc = fopen(Docfolderfile, "w");
		if(dc != nullptr)
		{
			//������ ��� ��������
			fwrite(Bday, sizeof(char), strlen(Bday), dc);
			fputc('\n', dc);
			fprintf(dc, "%d", bday[0]);
			fputc('\n', dc);
			fprintf(dc, "%d", bday[1]);
			fputc('\n', dc);
			fprintf(dc, "%d", bday[2]);
			fputc('\n', dc);
			//������ ���������
			fwrite(Pos, sizeof(char), strlen(Pos), dc);
			fputc('\n', dc);
			fwrite(position, sizeof(char), strlen(position), dc);
			fputc('\n', dc);
			//������ ���������
			fwrite(Cat, sizeof(char), strlen(Cat), dc);
			fputc('\n', dc);
			fwrite(category, sizeof(char), strlen(category), dc);
			fputc('\n', dc);
			//������ �����
			fwrite(Exp, sizeof(char), strlen(Exp), dc);
			fputc('\n', dc);
			fprintf(dc, "%f", exp);
			fputc('\n', dc);
			//������ ����������� ������
			fwrite(Celnmb, sizeof(char), strlen(Celnmb), dc);
			fputc('\n', dc);
			fwrite(cnmb, sizeof(char), strlen(cnmb), dc);
			fputc('\n', dc);
			fclose(dc);
		}
	}

	//����������� ��������� doctor
	void copyto(doctor &a) 
	{
		strcpy(a.ltname, ltname);
		strcpy(a.ftname, ftname);
		strcpy(a.pt, pt);
		if (a.flname != nullptr) a.flname = nullptr;
		a.flname = new char[3*NMSZ] {};
		strcpy(a.flname, flname);
		strcpy(a.position, position);
		strcpy(a.category, category);
		strcpy(a.cnmb, cnmb);
		a.bday[0] = bday[0];
		a.bday[1] = bday[1];
		a.bday[2] = bday[2];
		a.exp = exp;
	}

	//�������� ���� �������
	void changesomething()
	{
		cout << "What do you want to change?" << endl;
		cout << "1. Birhtday date" << endl;
		cout << "2. Position" << endl;
		cout << "3. Category" << endl;
		cout << "4. Experience" << endl;
		cout << "5. Cellphone number" << endl;
		cout << "0. Exit" << endl;
		int functchsn;
		while (true)
		{
			cin >> functchsn;
			if (functchsn >= 0 && functchsn <= 5) break;
		}
		switch (functchsn)
		{
		case 0:
			break;
		case 1:
			system("cls");
			datefill(bday, 'd');
			break;
		case 2:
			system("cls");
			cout << "Enter new position" << endl;
			cin.ignore();
			while (true)
			{
				cin.getline(position, INSZ);
				if (checkinput(position)) break;
			}
			break;
		case 3:
			system("cls");
			cout << "Enter new category" << endl;
			cin.ignore();
			while (true)
			{
				cin.getline(category, INSZ);
				if (checkinput(category)) break;
			}
			break;
		case 4:
			system("cls");
			cout << "Enter new experience in years" << endl;
			while (true)
			{
				cin >> exp;
				if (exp > 0) break;
			}
			break;
		case 5:
			system("cls");
			cout << "Enter new cellphone number" << endl;
			cin.ignore();
			while (true)
			{
				cin.getline(cnmb, INSZ);
				if (checknumber(cnmb)) break;
			}
			break;
		}
	}
};