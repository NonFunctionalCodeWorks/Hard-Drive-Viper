//============ Hard Drive Viper ============\\
//					    \\
//		 Version 1.0		    \\
//          NonFunctionalCodeWorks          \\
//					    \\
//==========================================\\



//=============== ERROR CODES ==============\\
//	    1 = Error scanf drive	    \\
//	    2 = Error scanf driveart        \\
//	    3 = Filesize		    \\
//==========================================\\


#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <filesystem>

typedef BOOL(WINAPI* P_GDFSE)(LPCTSTR, PULARGE_INTEGER, PULARGE_INTEGER, PULARGE_INTEGER);

int main()
{
	int x[100000] = { INT_MAX };
	int y[100000] = { 0 };

	//Size of the file
	long FileSize = 1;

	char pathfix[] = ":\\tempfile";
	char type[] = ".bin";
	char pathtemp[1000] = { };
	char path[1000] = { };
	char charID[1000] = { };
	int length = 0;
	char drive[2] = { 'E' };
	LPCSTR L = "\\E";
	int Type = -1;
	int Iterations = 0;
	long RoundCounter = 0;


	int FCloseValid = 0;
	bool SizeValid = false;
	long CorruptedFiles = 0;
	int Mode = -1;
	long NumberFiles = 0;
		

	//drive selection with a C drive lock
	printf("drive letter: ");
	if (!scanf("%c", &drive[0]))
		return 1;

	if (drive[0] == 'C' || drive[0] == 'c')
	{
		printf("invalid drive!");
		return 0;
	}


	//select drive
	switch (drive[0])
	{
	case 'C':
		return 0;
		break;
	case 'c':
		return 0;
		break;
	case  'A':
		L = "A:";
		break;
	case  'B':
		L = "B:";
		break;
	case  'D':
		L = "D:";
		break;
	case  'E':
		L = "E:";
		break;
	case  'F':
		L = "F:";
		break;
	case  'G':
		L = "G:";
		break;
	case  'H':
		L = "H:";
		break;
	case  'I':
		L = "I:";
		break;
	case  'J':
		L = "J:";
		break;
	case  'K':
		L = "K:";
		break;
	case  'L':
		L = "L:";
		break;
	case  'M':
		L = "M:";
		break;
	case  'N':
		L = "N:";
		break;
	case  'O':
		L = "O:";
		break;
	case  'P':
		L = "P:";
		break;
	case  'Q':
		L = "Q:";
		break;
	case  'R':
		L = "R:";
		break;
	case  'S':
		L = "S:";
		break;
	case  'T':
		L = "T:";
		break;
	case  'U':
		L = "U:";
		break;
	case  'V':
		L = "V:";
		break;
	case  'W':
		L = "W:";
		break;
	case  'X':
		L = "X:";
		break;
	case  'Y':
		L = "Y:";
		break;
	case  'Z':
		L = "Z:";
		break;
	}

	//select the type of the drive
	printf("\nHDD = 0 \nSSD-USB = 1");
	printf("\ndrive type: ");
	if (!scanf("%d", &Type))
		return 2;

	if (Type == 0) //HDD -> overwrite 10 times
		Iterations = 10;
	else if (Type == 1) //SSD -> overwrite once
		Iterations = 1;
	else
	{
		printf("\ninvalid drive type!");
		return 0;
	}
	printf("\drive type selected\n\n");


	//Calibration
	strcat(pathtemp, drive);
	strcat(pathtemp, pathfix);
	strcat(pathtemp, type);
	printf("PATHTEMP: %s \n", pathtemp);

	length = strlen(pathtemp);
	for (int q = 0; q <= length; q++)
	{
		path[q] = pathtemp[q];
	}

	//Create calibration file
	printf("\n\ncalibration");
	FILE* fh = fopen(path, "wb");

	if (fh != nullptr)
	{
		FCloseValid = fclose(fh);
		for (int i = 0; i < Iterations; i++)
		{

			fh = fopen(path, "rb+");
			fwrite(y, sizeof(int), 100000, fh);
			FCloseValid = fclose(fh);

			fh = fopen(path, "rb+");
			fwrite(x, sizeof(int), 100000, fh);
			FCloseValid = fclose(fh);
		}
	}

	FileSize = std::filesystem::file_size(path);
	std::cout << std::endl << "file size: " << FileSize << std::endl;

	if (FileSize == 1)
	{
		printf("calibration failed");
		return 3;
	}


	std::filesystem::space_info Z = std::filesystem::space(L);
	NumberFiles = Z.available / FileSize;
	std::cout << "drive size: " << Z.available << std::endl;
	std::cout << "number of files:" << NumberFiles << std::endl;


	//Clear path
	pathtemp[0] = '\0';
	path[0] = '\0';
	length = 0;

	printf("calibration finished\n\n");
	
	//Create and write all the files
	for (long id = 0; id < NumberFiles; id++)
	{
		std::cout << "ID: " << id << std::endl;


		strcat(pathtemp, drive);
		strcat(pathtemp, pathfix);
		strcat(pathtemp, charID);
		strcat(pathtemp, type);
		printf("PATHTEMP: %s \n", pathtemp);

		length = strlen(pathtemp);
		for (int q = 0; q <= length; q++)
		{
			path[q] = pathtemp[q];
		}


		//open the file
		FILE* fh = fopen(path, "wb");

		//write in the file
		if (fh != nullptr)
		{
			FCloseValid = fclose(fh);
			for (int i = 0; i < Iterations; i++)
			{

				fh = fopen(path, "rb+");
				fwrite(y, sizeof(int), 100000, fh);
				FCloseValid = fclose(fh);

				fh = fopen(path, "rb+");
				fwrite(x, sizeof(int), 100000, fh);
				FCloseValid = fclose(fh);
			}
		}
		else {
			printf("\nPfad NULL");
			CorruptedFiles++;
		}

		//increment Counter and print the value
		RoundCounter++;
		std::cout << "\Round " << RoundCounter << " of " << NumberFiles << std::endl << std::endl;


		//Clear path
		pathtemp[0] = '\0';
		path[0] = '\0';
		length = 0;
	}

	std::cout << "Number of corrupted files: " << CorruptedFiles << std::endl;
	
	return 0;
}
