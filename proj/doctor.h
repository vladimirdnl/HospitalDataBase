#pragma once
#include "otherstuff.h"
struct doctor
{
	char ftname[NMSZ]{};//Имя доктора
	char ltname[NMSZ]{};//Фамилия доктора
	char pt[NMSZ]{};//Отчество доктора
	char *flname;//Полное имя доктора
	int bday[3]{};//День рождения доктора
	char position[NMSZ]{};//Должность доктора
	char category[NMSZ]{};//Категория доктора
	float exp;//Стаж доктора в годах
	char cnmb[NMSZ]{};//Телефонный номер доктора

	//Зaполнить структуру doctor
	void fill()
	{
		//ввод даты рождения
		datefill(bday, 'd');
		//ввод и проверки на имена
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
		//Ввод и проверка на опыт
		cout << "Experience in years" << endl;
		while (true)
		{
			cin >> exp;
			if (exp >= 0) break;
		}
		//ввод и проверка на должность доктора
		cout << "Doctor's rank" << endl;
		cin.ignore();
		while (true)
		{
			cin.getline(position, NMSZ);
			if (checkinput(position)) break;
		}
		//ввод и проверка на категорию доктора
		cout << "The category" << endl;
		while (true)
		{
			cin.getline(category, NMSZ);
			if (checkinput(category)) break;
		}
		//ввод и проверка на номер телефона доктора
		cout << "Cellphone number" << endl;
		while (true)
		{
			cin.getline(cnmb, NMSZ);
			if (checknumber(cnmb)) break;
		}
	}

	//Вывести структуру doctor на экран
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

	//Записать инфу структуры doctor в файл с адресом path
	//В записи использую 3 функции записи: fwrite, fprintf, и fputc
	//(Сам познакомился с fprintf, fscanf, знаю, что такое форматы данных типа %d, %s, %f)
	void write(char *path)
	{
		//для удобства просмотра файлов .txt
		char Bday[] = { "Birthday:" }, Pos[] = { "Position:" }, Cat[] = { "Category:" }, Exp[] = { "Experience(in years) :" }, Celnmb[] = { "Cellphone Number:" };
		char *filename = totxt(flname);
		char *Docfolderfile = unite(path, filename, 'f');
		FILE *dc = fopen(Docfolderfile, "w");
		if(dc != nullptr)
		{
			//Запись дня рождения
			fwrite(Bday, sizeof(char), strlen(Bday), dc);
			fputc('\n', dc);
			fprintf(dc, "%d", bday[0]);
			fputc('\n', dc);
			fprintf(dc, "%d", bday[1]);
			fputc('\n', dc);
			fprintf(dc, "%d", bday[2]);
			fputc('\n', dc);
			//Запись должности
			fwrite(Pos, sizeof(char), strlen(Pos), dc);
			fputc('\n', dc);
			fwrite(position, sizeof(char), strlen(position), dc);
			fputc('\n', dc);
			//Запись категории
			fwrite(Cat, sizeof(char), strlen(Cat), dc);
			fputc('\n', dc);
			fwrite(category, sizeof(char), strlen(category), dc);
			fputc('\n', dc);
			//Запись опыта
			fwrite(Exp, sizeof(char), strlen(Exp), dc);
			fputc('\n', dc);
			fprintf(dc, "%f", exp);
			fputc('\n', dc);
			//Запись телефонного номера
			fwrite(Celnmb, sizeof(char), strlen(Celnmb), dc);
			fputc('\n', dc);
			fwrite(cnmb, sizeof(char), strlen(cnmb), dc);
			fputc('\n', dc);
			fclose(dc);
		}
	}

	//Копирование структуры doctor
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

	//Изменить инфу доктора
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