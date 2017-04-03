#include "stdafx.h"
#include "GFP.h"
#include <iostream>

int main(void)
{
	
	size_t sPeriodSize = 91;
	size_t sNumberOfPeriods = 1000;
	const char* File_name = "728_gfp.bin";

	//GFP gfp(sNumberOfPeriods, sPeriodSize);

	GFP gfp;

	gfp.SetPeriod(sPeriodSize);
	gfp.SetNumPeriod(sNumberOfPeriods);

	FILE *fp;
	fopen_s(&fp, File_name, "rb");

	if (fp == NULL) 
	{
		printf("Error \n");
		exit(1);
	}

	uint8_t *Buffer = new uint8_t[sNumberOfPeriods * sPeriodSize];									
																		
	for (uint32_t i = 0; i < sNumberOfPeriods * sPeriodSize; i++)
	{																									
		fread(&Buffer[i], 1, 1, fp);																// считываем из файла.
	}	
	
	fclose(fp);

	gfp.GenStatistic(Buffer);
	gfp.GenMask();
	uint8_t* FlagLocation = new uint8_t[sPeriodSize];
	FlagLocation = gfp.GetMask();
	
	for (uint8_t i = 0; i < 91; i++)
	{
		std::cout << 0 + FlagLocation[i] << std::endl;
	}
	return 0;
}

