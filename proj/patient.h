#pragma once
#include "otherstuff.h"
struct patient
{
	char ftname[NMSZ]{}; //��� ��������
	char ltname[NMSZ]{}; //������� ��������
	char pt[NMSZ]{}; //�������� ��������
	char *flname; //������ ��� ��������
	int bday[3]{}; //���� �������� ��������
	char ftdigns[INSZ]{}; //������ ������� ��������
	int datein[5]{}; //���� �����������
	char dctname[3*NMSZ]{}; //������ ��� �������� �������
	char anls[INSZ]{}; //������ ��������
	char cnslt[INSZ]{};//������ ������������ ������� ������������
	char drgs[INSZ]{};//������ ���������� ����������
	int dateout[5]{};//���� �������
	bool isout = false;//������� �� �������?
	int rmnum;//����� ������� ��������

	//����������� ��������� patient
	void copyto(patient &a) 
	{
		a.isout = isout;
		a.rmnum = rmnum;
		strcpy(a.ftname, ftname);
		strcpy(a.ltname, ltname);
		strcpy(a.pt, pt);
		strcpy(a.ftdigns, ftdigns);
		strcpy(a.dctname, dctname);
		if (a.flname != nullptr) a.flname = nullptr;
		a.flname = new char[3 * NMSZ] {};
		strcpy(a.flname, flname);
		strcpy(a.anls, anls);
		strcpy(a.cnslt, cnslt);
		strcpy(a.drgs, drgs);
		for (int i = 0; i < 3; i++) a.bday[i] = bday[i];
		for (int i = 0; i < 5; i++) a.datein[i] = datein[i];
		if(isout) for (int i = 0; i < 5; i++) a.dateout[i] = dateout[i];
	}

	//��������� ��������� patient
	void fill(char a)
	{
		//���� ���� �����������
		datefill(datein, 'i');
		//���� � �������� �� �����
		cout << "Last name of the patient" << endl;
		cin.ignore();
		while (true)
		{
			cin.getline(ltname, NMSZ);
			if (checkname(ltname)) break;
		}
		cout << "First name of the patient" << endl;
		while (true)
		{
			cin.getline(ftname, NMSZ);
			if (checkname(ftname)) break;
		}
		cout << "Patronymic of the patient" << endl;
		while (true) 
		{
			cin.getline(pt, NMSZ);
			if (checkname(pt)) break;
		}
		flname = fullname(ltname, ftname, pt);
		//���� ���� �������� � �������� �� ���� �����������
		while (true)
		{
			datefill(bday, 'p');
			if (bdatecheck(bday, datein)) break;
		}
		//���� � �������� �� ����(�������, �������, ������������, ���������)
		cout << "The first diagnosis" << endl;
		cin.ignore();
		while (true)
		{
			cin.getline(ftdigns, INSZ);
			if (checkinput(ftdigns)) break;
		}
		cout << "Check up data" << endl;
		while (true)
		{
			cin.getline(anls, INSZ);
			if (checkinput(anls)) break;
		}
		cout << "Consultations of related specialists" << endl;
		while (true)
		{
			cin.getline(cnslt, INSZ);
			if (checkinput(cnslt)) break;
		}
		cout << "Prescripted drugs" << endl;
		while (true)
		{
			cin.getline(drgs, INSZ);
			if (checkinput(drgs)) break;
		}
		//� ������ 'a' �� ����� �������, ����������� ������� ������� ��� �� ��� ��� � ��������
		if (a == 'a')
		{
			cout << "Is the patient discharged? 0 - No, 1 - Yes" << endl;
			int ans;
			while (true) 
			{
				cin >> ans;
				if (ans == 0 || ans == 1) break;
			}
			isout = ans;
		}
		if (isout)
		{
			discharge();
		}
	}

	//�������� �������� �� ��������
	void discharge() 
	{
		system("cls");
		isout = true;
		while (true)
		{
			datefill(dateout, 'o');
			if (dateoutcheck(dateout, datein)) break;
		}
	}

	//���� �������� �������, ������� ��� ��� � ��������, �� ����������� - ������� ��� �������
	void enroll()
	{
		system("cls");
		isout = false;
		while (true)
		{
			datefill(datein, 'i');
			if (bdatecheck(bday, datein) && dateoutcheck(datein, dateout)) break; //�������� �� ����
		}
		for (int i = 0; i < 5; i++)
		{
			dateout[i] = 0;
		}
	}

	//������� ���� �������� �� �����
	void print()
	{
		system("cls");
		cout << "======================================================================" << endl;
		cout << "Patient: " << flname << endl;
		cout << "Birthday: ";
		dateprint(bday, 'b');
		cout << "The first diagnosis: " << ftdigns << endl;
		cout << "Date & time of entering : ";
		dateprint(datein, 'i');
		cout << "Doctor: " << dctname << endl;
		cout << "Room Number: " << rmnum << endl;
		cout << "Analysis: " << anls << endl;
		cout << "Consultations of related specialists: " << cnslt << endl;
		cout << "Prescripted drugs: " << drgs << endl;
		cout << "Discharged: ";
		//���� ������� - ������� ���� �������

		if (isout) 
		{
			cout << "Yes" << endl;
			cout << "Discharge date: ";
			dateprint(dateout, 'o');
		}
		else cout << "No" << endl;
		cout << "======================================================================" << endl;
	}

	//�������� ���� �������� � ����, ������� ����� ����� path
	//� ������ ��������� 3 ������� ������: fwrite, fprintf, � fputc
	//(��� ������������ � fprintf, fscanf, ����, ��� ����� ������� ������ ���� %d, %s, %f)
	void write(char *path)
	{
		//��� �������� ��������� ������ .txt
		char Bday[] = { "Birthday:" }, Dtin[] = { "Datein:" }, Dtout[] = { "Dateout:" }, FtDiagn[] = { "First Diagnosis:" }, Chkp[] = { "Check up data(Analysis):" };
		char Cons[] = { "Consultation:" }, Drg[] = { "Drugs:" }, Doc[] = { "Doctor:" }, Iso[] = { "Isout:" }, Rmnb[] = {"Room number:"};
		char *filename = totxt(flname);
		char *Patfolderfile = unite(path, filename, 'f');
		FILE *pt = fopen(Patfolderfile, "w");
		if (pt != nullptr)
		{
			//������ ���� ��������
			fwrite(Bday, sizeof(char), strlen(Bday), pt);
			fputc('\n', pt);
			fprintf(pt, "%d", bday[0]);
			fputc('\n', pt);
			fprintf(pt, "%d", bday[1]);
			fputc('\n', pt);
			fprintf(pt, "%d", bday[2]);
			fputc('\n', pt);
			//������ ���� �����������
			fwrite(Dtin, sizeof(char), strlen(Dtin), pt);
			fputc('\n', pt);
			fprintf(pt, "%d", datein[0]);
			fputc('\n', pt);
			fprintf(pt, "%d", datein[1]);
			fputc('\n', pt);
			fprintf(pt, "%d", datein[2]);
			fputc('\n', pt);
			fprintf(pt, "%d", datein[3]);
			fputc('\n', pt);
			fprintf(pt, "%d", datein[4]);
			fputc('\n', pt);
			//������ ������� ��������
			fwrite(FtDiagn, sizeof(char), strlen(FtDiagn), pt);
			fputc('\n', pt);
			fwrite(ftdigns, sizeof(char), strlen(ftdigns), pt);
			fputc('\n', pt);
			//������ ��������
			fwrite(Chkp, sizeof(char), strlen(Chkp), pt);
			fputc('\n', pt);
			fwrite(anls, sizeof(char), strlen(anls), pt);
			fputc('\n', pt);
			//������ ������������
			fwrite(Cons, sizeof(char), strlen(Cons), pt);
			fputc('\n', pt);
			fwrite(cnslt, sizeof(char), strlen(cnslt), pt);
			fputc('\n', pt);
			//������ ����������
			fwrite(Drg, sizeof(char), strlen(Drg), pt);
			fputc('\n', pt);
			fwrite(drgs, sizeof(char), strlen(drgs), pt);
			fputc('\n', pt);
			//������ ����� �������
			fwrite(Doc, sizeof(char), strlen(Doc), pt);
			fputc('\n', pt);
			fwrite(dctname, sizeof(char), strlen(dctname), pt);
			fputc('\n', pt);
			//������ ������ �������
			fwrite(Rmnb, sizeof(char), strlen(Rmnb), pt);
			fputc('\n', pt);
			fprintf(pt, "%d", rmnum);
			fputc('\n', pt);
			//������ isout
			fwrite(Iso, sizeof(char), strlen(Iso), pt);
			fputc('\n', pt);
			fprintf(pt, "%d", isout);
			fputc('\n', pt);
			//������ ���� �������
			fwrite(Dtout, sizeof(char), strlen(Dtout), pt);
			fputc('\n', pt);
			if (isout)
			{
				fprintf(pt, "%d", dateout[0]);
				fputc('\n', pt);
				fprintf(pt, "%d", dateout[1]);
				fputc('\n', pt);
				fprintf(pt, "%d", dateout[2]);
				fputc('\n', pt);
				fprintf(pt, "%d", dateout[3]);
				fputc('\n', pt);
				fprintf(pt, "%d", dateout[4]);
				fputc('\n', pt);
			}
			fclose(pt);
		}
	}

	//��� ��������� ������ �� ������ ����
	//���� ������� ������� - +������� �������� ���� �������
	void changesomething()
	{
		cout << "What do you want to change?" << endl;
		cout << "1. Birhtday date" << endl;
		cout << "2. Date-in" << endl;
		cout << "3. Check-up data" << endl;
		cout << "4. Consultations data" << endl;
		cout << "5. Prescripted drugs data" << endl;
		if (isout) cout << "6. Discharge date" << endl;
		cout << "0. Exit" << endl;
		int functchsn;
		//�������� �� ���� ���������� �����
		while (true)
		{
			cin >> functchsn;
			if (functchsn >= 0)
			{
				if (isout && functchsn <= 6) break;
				if (!isout && functchsn <= 5) break;
			}
		}
		switch (functchsn)
		{
		case 0:
			break;
		case 1:
			system("cls");
			while (true)
			{
				datefill(bday, 'p');
				if (bdatecheck(bday, datein)) break;
			}
			break;
		case 2:
			system("cls");
			while (true)
			{
				datefill(datein, 'i');
				if (bdatecheck(bday, datein) && dateoutcheck(dateout, datein)) break;
			}
			break;
		case 3:
			system("cls");
			cout << "Enter new Check up data" << endl;
			cin.ignore();
			//���� ��������
			while (true)
			{
				cin.getline(anls, INSZ);
				if (checkinput(anls)) break;
			}
			break;
		case 4:
			system("cls");
			cout << "Enter new Consultations data" << endl;
			cin.ignore();
			//���� ������������
			while (true)
			{
				cin.getline(cnslt, INSZ);
				if (checkinput(cnslt)) break;
			}
			break;
		case 5:
			system("cls");
			cout << "Enter new Drugs data" << endl;
			cin.ignore();
			//���� ����������
			while (true)
			{
				cin.getline(drgs, INSZ);
				if (checkinput(drgs)) break;
			}
			break;
		case 6:
			system("cls");
			while (true)
			{
				datefill(dateout, 'o');
				if (dateoutcheck(dateout, datein)) break;
			}
			break;
		}
	}
};