#pragma once
#include "otherstuff.h"
#include "department.h"
#include "doctor.h"
#include "patient.h"
struct hospital 
{
	char HospName[NMSZ]{};//Название больницы
	department *dp;//Массив отделений в больнице
	int dpnum = 0;//Количество отделений в больнице

	//Начальное считывание всей больницы из базы данных(Папки Hospital) в программу - возвращает true при успешном считывании
	bool read()
	{
		char *path = new char[10]{ "Hospital\\" };
		char namehospdef[] = { "HOSPITAL" };
		//Создаём Хэндлер и Файнд дата для папки Hospital
		WIN32_FIND_DATA FindFileData;
		HANDLE hf;
		char *pathfind = pathToFind(path);
		char Doc[] = { "Doctors" }, Pat[] = { "Patients" }, inf[] = { "departinfo.txt" }, name[] = {"nameinfo.txt"};//Постоянные папки и файлы, на которые ссылаемся
		hf = FindFirstFile(pathfind, &FindFileData);
		if (hf != INVALID_HANDLE_VALUE)
		{
			//Пропуск точек с начала
			FindNextFile(hf, &FindFileData);
			while (FindNextFile(hf, &FindFileData)) dpnum++;//Количество всех файлов
			//Определяем потенциальное(неточное) количество отделений
			dpnum--;
			//выделяем память  под отделение
			dp = new department[dpnum];
			//считываем файл с именем
			char *namefile = unite(path, name, 'f');
			FILE *namei = fopen(namefile, "r");
			if ((namei != nullptr))
			{
				readstring(HospName, namei);
				HospName[strlen(HospName)] = '\0';
				fclose(namei);
			}
			//если такового нет - просто пишем Хоспитал Намбер Ван
			else
			{
				strcpy(HospName, namehospdef);
			}
			hf = FindFirstFile(pathfind, &FindFileData);
			FindNextFile(hf, &FindFileData);
			int i = 0;//Отвечает за номер считываемого отделения в массив
			//Начинаем считывать отделения
			while (i < dpnum && FindNextFile(hf, &FindFileData))
			{
				//Чекаем, не файл txt с именем ли это
				bool isnminf = true;
				for (int check = 0; FindFileData.cFileName[check] != '\0' && name[check] != '\0';check++)
				{
					if (FindFileData.cFileName[check] != name[check]) {
						isnminf = false;
						break;
					}
				}
				if (isnminf) continue;
				//Копируем название папки отделения в само название отделения
				strcpy(dp[i].name, FindFileData.cFileName);
				//Создаём Хэндлер и Файнд дата для папки отделения
				WIN32_FIND_DATA FindFileDataD;
				HANDLE hfD;
				//Путь для поиска файлов отделения и взаимодействия с файлами в папке отделения
				char *Dpath = unite(path, FindFileData.cFileName);
				char *Dpathfind = pathToFind(Dpath);
				hfD = FindFirstFile(Dpathfind, &FindFileDataD);
				if (hfD != INVALID_HANDLE_VALUE)
				{
					//считывание файла с инфой про отделение
					char *InfPath = unite(Dpath, inf, 'f');
					FILE *inffile;
					if ((inffile = fopen(InfPath, "r")) != nullptr)
					{
						char nul;//Чтобы можно проследить пропуск "неинформативной" строки
						while ((nul = fgetc(inffile)) != '\n');
						fscanf(inffile, "%d", &dp[i].ptnsnum);
						fgetc(inffile);
						while ((nul = fgetc(inffile)) != '\n');//Пропуск "неинформативной" строки
						fscanf(inffile, "%d", &dp[i].docsnum);
						fgetc(inffile);
						while ((nul = fgetc(inffile)) != '\n');
						fscanf(inffile, "%d", &dp[i].frsrom);
						fgetc(inffile);
						fclose(inffile);
					}
					//нет файла инфы про отделение - уменьшаем общее кол-во отделений, переписываем предыдущие и переходим к следующей, ведь эта папка не полноценное отделение
					else
					{

						dpnum--;
						department *temp = new department[dpnum];
						for (int copydep = 0; copydep < i; copydep++)
						{
							dp[copydep].copyto(temp[copydep]);
						}
						for (int dep = 0; dep < dpnum+1; dep++)
						{

							delete[] dp[dep].ptns;
							dp[dep].ptns = nullptr;
							delete[] dp[dep].docs;
							dp[dep].docs = nullptr;

						} 
						delete[] dp;
						dp = nullptr;
						dp = new department[dpnum];
						for (int copydep = 0; copydep < i; copydep++)
						{
							temp[copydep].copyto(dp[copydep]);
						}
						delete[] temp;
						temp = nullptr;
						continue;
					}
					//Создаём Хэндлер и Файнд дата для папки Доктора
					WIN32_FIND_DATA FindFileDataDo;
					HANDLE hfDo;
					//Путь для поиска файлов отделения и взаимодействия с файлами в папке Доктора
					char *Dopath = unite(Dpath, Doc);
					char *Dopathfind = pathToFind(Dopath);
					hfDo = FindFirstFile(Dopathfind, &FindFileDataDo);
					//Если есть папка Доктора - считываем инфу далее
					if (hfDo != INVALID_HANDLE_VALUE) 
					{
						int k = 0;//здесь отвечает за докторов
						//Пропуск точек с начала
						FindNextFile(hfDo, &FindFileDataDo);
						FindNextFile(hfDo, &FindFileDataDo);
						//Если докторов больше нуля в данных - записываем(докторов не может быть ноль, потому что смысла тогда в отделении будет тоже 0, 
						// следовательно, его просто лучше не добавлять, ведь его всё равно не существует)
						if (dp[i].docsnum > 0)
						{
							//Выделение памяти на докторов
							dp[i].docs = new doctor[dp[i].docsnum];
							do
							{
								//Путь для чтения файла доктора
								char* fileDopath = unite(Dopath, FindFileDataDo.cFileName, 'f');
								//Запись имени доктора без txt и разделение его на три графы Ф.И.О
								dp[i].docs[k].flname = new char[strlen(FindFileDataDo.cFileName) - 3]{};
								for (int l = 0; l < strlen(FindFileDataDo.cFileName) - 4; l++)
								{
									dp[i].docs[k].flname[l] = FindFileDataDo.cFileName[l];
								}
								separatename(dp[i].docs[k].flname, dp[i].docs[k].ltname, dp[i].docs[k].ftname, dp[i].docs[k].pt);
								FILE *fileDo;
								//Если файл доктора открывается - считываем инфу
								if ((fileDo = fopen(fileDopath, "r")) != nullptr)
								{
									char nul;
									while ((nul = fgetc(fileDo)) != '\n');
									fscanf(fileDo, "%d", &dp[i].docs[k].bday[0]);
									fgetc(fileDo);
									fscanf(fileDo, "%d", &dp[i].docs[k].bday[1]);
									fgetc(fileDo);
									fscanf(fileDo, "%d", &dp[i].docs[k].bday[2]);
									fgetc(fileDo);
									while ((nul = fgetc(fileDo)) != '\n');
									readstring(dp[i].docs[k].position, fileDo);
									fgetc(fileDo);
									while ((nul = fgetc(fileDo)) != '\n');
									readstring(dp[i].docs[k].category, fileDo);
									fgetc(fileDo);
									while ((nul = fgetc(fileDo)) != '\n');
									fscanf(fileDo, "%f", &dp[i].docs[k].exp);
									fgetc(fileDo);
									while ((nul = fgetc(fileDo)) != '\n');
									readstring(dp[i].docs[k].cnmb, fileDo);
									fclose(fileDo);
								}
								k++;//Передвигаем номер позиции записи доктора в массив на 1 вперёд, чтобы записать следующего доктора
							} while (FindNextFile(hfDo, &FindFileDataDo));//Делаем, пока остаются файлы
						}
						//Если докторов 0 или меньше в данных - Не считаем это за отделение, пропускаем его, переписывая все предыдущие
						else
						{
							dpnum--;
							department *temp = new department[dpnum];
							for (int copydep = 0; copydep < i; copydep++)
							{
								dp[copydep].copyto(temp[copydep]);
							}
							for (int dep = 0; dep < dpnum + 1; dep++)
							{

								delete[] dp[dep].ptns;
								dp[dep].ptns = nullptr;
								delete[] dp[dep].docs;
								dp[dep].docs = nullptr;

							}
							delete[] dp;
							dp = nullptr;
							dp = new department[dpnum];
							for (int copydep = 0; copydep < i; copydep++)
							{
								temp[copydep].copyto(dp[copydep]);
							}
							delete[] temp;
							temp = nullptr;
							continue;
						}
					}
					//Если нет папки доктора - Не считаем это за отделение, пропускаем его, переписывая все предыдущие
					else
					{
						dpnum--;
						department *temp = new department[dpnum];
						for (int copydep = 0; copydep < i; copydep++)
						{
							dp[copydep].copyto(temp[copydep]);
						}
						for (int dep = 0; dep < dpnum + 1; dep++)
						{

							delete[] dp[dep].ptns;
							dp[dep].ptns = nullptr;
							delete[] dp[dep].docs;
							dp[dep].docs = nullptr;

						}
						delete[] dp;
						dp = nullptr;
						dp = new department[dpnum];
						for (int copydep = 0; copydep < i; copydep++)
						{
							temp[copydep].copyto(dp[copydep]);
						}
						delete[] temp;
						temp = nullptr;
						continue;
					}
					//Создаём Хэндлер и Файнд дата для папки Пациенты
					WIN32_FIND_DATA FindFileDataPa;
					HANDLE hfPa;
					//Путь для поиска файлов отделения и взаимодействия с файлами в папке Пациенты
					char *Papath = unite(Dpath, Pat);
					char *Papathfind = pathToFind(Papath);
					//Если есть папка Доктора - считываем инфу далее
					hfPa = FindFirstFile(Papathfind, &FindFileDataPa);
					if (hfPa != INVALID_HANDLE_VALUE)
					{
						int k = 0;//здесь отвечает за пациентов
						//Пропуск точек с начала
						FindNextFile(hfPa, &FindFileDataPa);
						FindNextFile(hfPa, &FindFileDataPa);
						//Если пациентов больше нуля , то идём далее
						if (dp[i].ptnsnum > 0)
						{
							//Выделяем память для пациентов
							dp[i].ptns = new patient[dp[i].ptnsnum];
							do
							{
								//Путь для чтения файла пациента
								char* filePapath = unite(Papath, FindFileDataPa.cFileName, 'f');
								//Запись имени пациента без txt и разделение его на три графы Ф.И.О
								dp[i].ptns[k].flname = new char[strlen(FindFileDataPa.cFileName) - 3]{};
								for (int z = 0; z < strlen(FindFileDataPa.cFileName) - 4; z++)
								{
									dp[i].ptns[k].flname[z] = FindFileDataPa.cFileName[z];
								}
								separatename(dp[i].ptns[k].flname, dp[i].ptns[k].ltname, dp[i].ptns[k].ftname, dp[i].ptns[k].pt);
								FILE *filePa;
								//Если файл открылся - считываем инфу пациента
								if ((filePa = fopen(filePapath, "r")) != nullptr)
								{
									char nul;
									while ((nul = fgetc(filePa)) != '\n');
									fscanf(filePa, "%d", &dp[i].ptns[k].bday[0]);
									fgetc(filePa);
									fscanf(filePa, "%d", &dp[i].ptns[k].bday[1]);
									fgetc(filePa);
									fscanf(filePa, "%d", &dp[i].ptns[k].bday[2]);
									fgetc(filePa);
									while ((nul = fgetc(filePa)) != '\n');
									fscanf(filePa, "%d", &dp[i].ptns[k].datein[0]);
									fgetc(filePa);
									fscanf(filePa, "%d", &dp[i].ptns[k].datein[1]);
									fgetc(filePa);
									fscanf(filePa, "%d", &dp[i].ptns[k].datein[2]);
									fgetc(filePa);
									fscanf(filePa, "%d", &dp[i].ptns[k].datein[3]);
									fgetc(filePa);
									fscanf(filePa, "%d", &dp[i].ptns[k].datein[4]);
									fgetc(filePa);
									while ((nul = fgetc(filePa)) != '\n');
									readstring(dp[i].ptns[k].ftdigns, filePa);
									fgetc(filePa);
									while ((nul = fgetc(filePa)) != '\n');
									readstring(dp[i].ptns[k].anls, filePa);
									fgetc(filePa);
									while ((nul = fgetc(filePa)) != '\n');
									readstring(dp[i].ptns[k].cnslt, filePa);
									fgetc(filePa);
									while ((nul = fgetc(filePa)) != '\n');
									readstring(dp[i].ptns[k].drgs, filePa);
									fgetc(filePa);
									while ((nul = fgetc(filePa)) != '\n');
									readstring(dp[i].ptns[k].dctname, filePa);
									fgetc(filePa);
									while ((nul = fgetc(filePa)) != '\n');
									fscanf(filePa, "%d", &dp[i].ptns[k].rmnum);
									fgetc(filePa);
									while ((nul = fgetc(filePa)) != '\n');
									fscanf(filePa, "%d", &dp[i].ptns[k].isout);
									//Если выписан - считываем инфу про дату выписки
									if (dp[i].ptns[k].isout)
									{
										fgetc(filePa);
										while ((nul = fgetc(filePa)) != '\n');
										fscanf(filePa, "%d", &dp[i].ptns[k].dateout[0]);
										fgetc(filePa);
										fscanf(filePa, "%d", &dp[i].ptns[k].dateout[1]);
										fgetc(filePa);
										fscanf(filePa, "%d", &dp[i].ptns[k].dateout[2]);
										fgetc(filePa);
										fscanf(filePa, "%d", &dp[i].ptns[k].dateout[3]);
										fgetc(filePa);
										fscanf(filePa, "%d", &dp[i].ptns[k].dateout[4]);
									}
									fclose(filePa);
								}
								k++;//Передвигаем номер позиции записи пациента в массив на 1 вперёд, чтобы записать следующего пациента
							} while (FindNextFile(hfPa, &FindFileDataPa));//Делаем, пока остаются файлы
						}
						//В данном случае, если пациентов == 0 считаем это за отделение(потому что пациентов может и не быть при открытии отделения)
						//Если пациентов записано меньше нуля - пропускаем
						if (dp[i].ptnsnum < 0)
						{
							dpnum--;
							department *temp = new department[dpnum];
							for (int copydep = 0; copydep < i; copydep++)
							{
								dp[copydep].copyto(temp[copydep]);
							}
							for (int dep = 0; dep < dpnum + 1; dep++)
							{

								delete[] dp[dep].ptns;
								dp[dep].ptns = nullptr;
								delete[] dp[dep].docs;
								dp[dep].docs = nullptr;

							}
							delete[] dp;
							dp = nullptr;
							dp = new department[dpnum];
							for (int copydep = 0; copydep < i; copydep++)
							{
								temp[copydep].copyto(dp[copydep]);
							}
							delete[] temp;
							temp = nullptr;
							continue;
						}
					}
					//Нет папки Пациенты - не нужно отделение, его пропускаем
					else
					{
						dpnum--;
						department *temp = new department[dpnum];
						for (int copydep = 0; copydep < i; copydep++)
						{
							dp[copydep].copyto(temp[copydep]);
						}
						for (int dep = 0; dep < dpnum + 1; dep++)
						{

							delete[] dp[dep].ptns;
							dp[dep].ptns = nullptr;
							delete[] dp[dep].docs;
							dp[dep].docs = nullptr;

						}
						delete[] dp;
						dp = nullptr;
						dp = new department[dpnum];
						for (int copydep = 0; copydep < i; copydep++)
						{
							temp[copydep].copyto(dp[copydep]);
						}
						delete[] temp;
						temp = nullptr;
						continue;
					}
					i++;////Передвигаем номер позиции записи отделения в массив на 1 вперёд, чтобы записать следующее отделение
				}
			}
			//если совсем нет информативных папок отделений - возвращаем false
			if (dpnum == 0) return false;
		}
		//Если не открыло папку hospital - возвращаем false
		else return false;
		//Если не было ошибок - возвращаем true
		return true;
		
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// Таким образом, программа устойчива к негативным значениям кол-ва людей в файле информации	 //
		// Устойчива к отсутствию папки базы данных														 //
		// Выделяет правильные папки-отделения по факторам:												 //
		//       - Наличие файла информации об отделении												 //
		//       - Наличие папки Докторов + кол-ва докторов хотя бы 1шт.								 //
		//       - Наличие папки Пациенты																 //
		///////////////////////////////////////////////////////////////////////////////////////////////////
	}

	//Запись больницы в базу данных (в папку Hospital)
	void write() 
	{
		//Создаём Хэндлер и Файнд дата для папки Hospital
		WIN32_FIND_DATA FindFileData;
		HANDLE hf;
		//создаём константные массивы для взаимодействия с пакой базы данных(папкой Hospital)
		char name[] = { "nameinfo.txt" };
		char *path = new char[10]{ "Hospital\\" };
		char *Dir = new char[9]{ "Hospital" };
		char *pathfind = pathToFind(path);
		hf = FindFirstFile(pathfind, &FindFileData);
		//Если папки Hospital не существует, создаём её
		if (hf == INVALID_HANDLE_VALUE)
		{
			CreateDirectory(Dir, NULL);
		}
		char *filename = unite(path, name, 'f');
		FILE *fname = fopen(filename, "w+");
		if (fname != nullptr)
		{
			fwrite(HospName, sizeof(char), strlen(HospName), fname);
			fputc('\n', fname);
			fclose(fname);
		}
		for (int i = 0; i < dpnum; i++)
		{
			dp[i].write();
		}
	}
};