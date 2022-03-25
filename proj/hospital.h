#pragma once
#include "otherstuff.h"
#include "department.h"
#include "doctor.h"
#include "patient.h"
struct hospital 
{
	char HospName[NMSZ]{};//�������� ��������
	department *dp;//������ ��������� � ��������
	int dpnum = 0;//���������� ��������� � ��������

	//��������� ���������� ���� �������� �� ���� ������(����� Hospital) � ��������� - ���������� true ��� �������� ����������
	bool read()
	{
		char *path = new char[10]{ "Hospital\\" };
		char namehospdef[] = { "HOSPITAL" };
		//������ ������� � ����� ���� ��� ����� Hospital
		WIN32_FIND_DATA FindFileData;
		HANDLE hf;
		char *pathfind = pathToFind(path);
		char Doc[] = { "Doctors" }, Pat[] = { "Patients" }, inf[] = { "departinfo.txt" }, name[] = {"nameinfo.txt"};//���������� ����� � �����, �� ������� ���������
		hf = FindFirstFile(pathfind, &FindFileData);
		if (hf != INVALID_HANDLE_VALUE)
		{
			//������� ����� � ������
			FindNextFile(hf, &FindFileData);
			while (FindNextFile(hf, &FindFileData)) dpnum++;//���������� ���� ������
			//���������� �������������(��������) ���������� ���������
			dpnum--;
			//�������� ������  ��� ���������
			dp = new department[dpnum];
			//��������� ���� � ������
			char *namefile = unite(path, name, 'f');
			FILE *namei = fopen(namefile, "r");
			if ((namei != nullptr))
			{
				readstring(HospName, namei);
				HospName[strlen(HospName)] = '\0';
				fclose(namei);
			}
			//���� �������� ��� - ������ ����� �������� ������ ���
			else
			{
				strcpy(HospName, namehospdef);
			}
			hf = FindFirstFile(pathfind, &FindFileData);
			FindNextFile(hf, &FindFileData);
			int i = 0;//�������� �� ����� ������������ ��������� � ������
			//�������� ��������� ���������
			while (i < dpnum && FindNextFile(hf, &FindFileData))
			{
				//������, �� ���� txt � ������ �� ���
				bool isnminf = true;
				for (int check = 0; FindFileData.cFileName[check] != '\0' && name[check] != '\0';check++)
				{
					if (FindFileData.cFileName[check] != name[check]) {
						isnminf = false;
						break;
					}
				}
				if (isnminf) continue;
				//�������� �������� ����� ��������� � ���� �������� ���������
				strcpy(dp[i].name, FindFileData.cFileName);
				//������ ������� � ����� ���� ��� ����� ���������
				WIN32_FIND_DATA FindFileDataD;
				HANDLE hfD;
				//���� ��� ������ ������ ��������� � �������������� � ������� � ����� ���������
				char *Dpath = unite(path, FindFileData.cFileName);
				char *Dpathfind = pathToFind(Dpath);
				hfD = FindFirstFile(Dpathfind, &FindFileDataD);
				if (hfD != INVALID_HANDLE_VALUE)
				{
					//���������� ����� � ����� ��� ���������
					char *InfPath = unite(Dpath, inf, 'f');
					FILE *inffile;
					if ((inffile = fopen(InfPath, "r")) != nullptr)
					{
						char nul;//����� ����� ���������� ������� "���������������" ������
						while ((nul = fgetc(inffile)) != '\n');
						fscanf(inffile, "%d", &dp[i].ptnsnum);
						fgetc(inffile);
						while ((nul = fgetc(inffile)) != '\n');//������� "���������������" ������
						fscanf(inffile, "%d", &dp[i].docsnum);
						fgetc(inffile);
						while ((nul = fgetc(inffile)) != '\n');
						fscanf(inffile, "%d", &dp[i].frsrom);
						fgetc(inffile);
						fclose(inffile);
					}
					//��� ����� ���� ��� ��������� - ��������� ����� ���-�� ���������, ������������ ���������� � ��������� � ���������, ���� ��� ����� �� ����������� ���������
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
					//������ ������� � ����� ���� ��� ����� �������
					WIN32_FIND_DATA FindFileDataDo;
					HANDLE hfDo;
					//���� ��� ������ ������ ��������� � �������������� � ������� � ����� �������
					char *Dopath = unite(Dpath, Doc);
					char *Dopathfind = pathToFind(Dopath);
					hfDo = FindFirstFile(Dopathfind, &FindFileDataDo);
					//���� ���� ����� ������� - ��������� ���� �����
					if (hfDo != INVALID_HANDLE_VALUE) 
					{
						int k = 0;//����� �������� �� ��������
						//������� ����� � ������
						FindNextFile(hfDo, &FindFileDataDo);
						FindNextFile(hfDo, &FindFileDataDo);
						//���� �������� ������ ���� � ������ - ����������(�������� �� ����� ���� ����, ������ ��� ������ ����� � ��������� ����� ���� 0, 
						// �������������, ��� ������ ����� �� ���������, ���� ��� �� ����� �� ����������)
						if (dp[i].docsnum > 0)
						{
							//��������� ������ �� ��������
							dp[i].docs = new doctor[dp[i].docsnum];
							do
							{
								//���� ��� ������ ����� �������
								char* fileDopath = unite(Dopath, FindFileDataDo.cFileName, 'f');
								//������ ����� ������� ��� txt � ���������� ��� �� ��� ����� �.�.�
								dp[i].docs[k].flname = new char[strlen(FindFileDataDo.cFileName) - 3]{};
								for (int l = 0; l < strlen(FindFileDataDo.cFileName) - 4; l++)
								{
									dp[i].docs[k].flname[l] = FindFileDataDo.cFileName[l];
								}
								separatename(dp[i].docs[k].flname, dp[i].docs[k].ltname, dp[i].docs[k].ftname, dp[i].docs[k].pt);
								FILE *fileDo;
								//���� ���� ������� ����������� - ��������� ����
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
								k++;//����������� ����� ������� ������ ������� � ������ �� 1 �����, ����� �������� ���������� �������
							} while (FindNextFile(hfDo, &FindFileDataDo));//������, ���� �������� �����
						}
						//���� �������� 0 ��� ������ � ������ - �� ������� ��� �� ���������, ���������� ���, ����������� ��� ����������
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
					//���� ��� ����� ������� - �� ������� ��� �� ���������, ���������� ���, ����������� ��� ����������
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
					//������ ������� � ����� ���� ��� ����� ��������
					WIN32_FIND_DATA FindFileDataPa;
					HANDLE hfPa;
					//���� ��� ������ ������ ��������� � �������������� � ������� � ����� ��������
					char *Papath = unite(Dpath, Pat);
					char *Papathfind = pathToFind(Papath);
					//���� ���� ����� ������� - ��������� ���� �����
					hfPa = FindFirstFile(Papathfind, &FindFileDataPa);
					if (hfPa != INVALID_HANDLE_VALUE)
					{
						int k = 0;//����� �������� �� ���������
						//������� ����� � ������
						FindNextFile(hfPa, &FindFileDataPa);
						FindNextFile(hfPa, &FindFileDataPa);
						//���� ��������� ������ ���� , �� ��� �����
						if (dp[i].ptnsnum > 0)
						{
							//�������� ������ ��� ���������
							dp[i].ptns = new patient[dp[i].ptnsnum];
							do
							{
								//���� ��� ������ ����� ��������
								char* filePapath = unite(Papath, FindFileDataPa.cFileName, 'f');
								//������ ����� �������� ��� txt � ���������� ��� �� ��� ����� �.�.�
								dp[i].ptns[k].flname = new char[strlen(FindFileDataPa.cFileName) - 3]{};
								for (int z = 0; z < strlen(FindFileDataPa.cFileName) - 4; z++)
								{
									dp[i].ptns[k].flname[z] = FindFileDataPa.cFileName[z];
								}
								separatename(dp[i].ptns[k].flname, dp[i].ptns[k].ltname, dp[i].ptns[k].ftname, dp[i].ptns[k].pt);
								FILE *filePa;
								//���� ���� �������� - ��������� ���� ��������
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
									//���� ������� - ��������� ���� ��� ���� �������
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
								k++;//����������� ����� ������� ������ �������� � ������ �� 1 �����, ����� �������� ���������� ��������
							} while (FindNextFile(hfPa, &FindFileDataPa));//������, ���� �������� �����
						}
						//� ������ ������, ���� ��������� == 0 ������� ��� �� ���������(������ ��� ��������� ����� � �� ���� ��� �������� ���������)
						//���� ��������� �������� ������ ���� - ����������
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
					//��� ����� �������� - �� ����� ���������, ��� ����������
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
					i++;////����������� ����� ������� ������ ��������� � ������ �� 1 �����, ����� �������� ��������� ���������
				}
			}
			//���� ������ ��� ������������� ����� ��������� - ���������� false
			if (dpnum == 0) return false;
		}
		//���� �� ������� ����� hospital - ���������� false
		else return false;
		//���� �� ���� ������ - ���������� true
		return true;
		
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// ����� �������, ��������� ��������� � ���������� ��������� ���-�� ����� � ����� ����������	 //
		// ��������� � ���������� ����� ���� ������														 //
		// �������� ���������� �����-��������� �� ��������:												 //
		//       - ������� ����� ���������� �� ���������												 //
		//       - ������� ����� �������� + ���-�� �������� ���� �� 1��.								 //
		//       - ������� ����� ��������																 //
		///////////////////////////////////////////////////////////////////////////////////////////////////
	}

	//������ �������� � ���� ������ (� ����� Hospital)
	void write() 
	{
		//������ ������� � ����� ���� ��� ����� Hospital
		WIN32_FIND_DATA FindFileData;
		HANDLE hf;
		//������ ����������� ������� ��� �������������� � ����� ���� ������(������ Hospital)
		char name[] = { "nameinfo.txt" };
		char *path = new char[10]{ "Hospital\\" };
		char *Dir = new char[9]{ "Hospital" };
		char *pathfind = pathToFind(path);
		hf = FindFirstFile(pathfind, &FindFileData);
		//���� ����� Hospital �� ����������, ������ �
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