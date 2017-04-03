#include "stdafx.h"
#include "GFP.h"
#include <iostream>
#include <cstdint>
#include <algorithm>

void GFP::SetPeriod(size_t sPeriodSize)
{
	PeriodSize = sPeriodSize;
}

void GFP::SetNumPeriod(size_t sNumberOfPeriod)
{
	NumberOfPeriods = sNumberOfPeriod;
}

void GFP::GenStatistic(const uint8_t* Buffer)
{
	uint16_t* Statistic = new uint16_t[256*PeriodSize];

	Statistic[256*PeriodSize] = { 0 };

	for (uint8_t j = 0; j < PeriodSize; j++)										
	{
		for (uint16_t i = 0; i < NumberOfPeriods; i++)								
		{																			
			Statistic[j * 256 + Buffer[i*PeriodSize + j]]++;							// статистика каждого байта			
		}
	}
}

void GFP::GenMask()
{

	for (uint8_t j = 0; j < PeriodSize; j++)
	{
		min_stat_flag = std::min(Statistic[j * 256 + first_flag], std::min(Statistic[j * 256 + third_flag], Statistic[j * 256 + fourth_flag])); 
		k = 0;

		for (uint8_t i = 0; i < 255; i++)												// проходим по статистике каждого байта.
		{
			if ((i == 0 + first_flag) || (i == 0 + third_flag) || (i == 0 + fourth_flag)) i++;				// не учитываем байты gfp.

			if (min_stat_flag > Statistic[j * 256 + i]) k++;							// если статистика min_stat_flag больше статистики i-го байта, то к++
		}

		if (k > 250) Mask[j] = 1;														// если min_stat_flag - макс. статистика среди не gfp байт, то это флаг
		else Mask[j] = 0;															    // иначе обычный байт
	}

}

uint8_t* GFP::GetMask()
{
	return Mask;
}