#include "stdafx.h"
#include "findflags.h"
#include <iostream>
#include <cstdint>
#include <algorithm>


	class GFP
	{

	private:

		const uint8_t first_flag = 0xD5; //10101011
		//const uint8_t second_flag		 = 0x6D; //10110110							������-�� ���������� 0
		const uint8_t third_flag = 0x8C; //00110001
		const uint8_t fourth_flag = 0x07; //11100000
		//size_t myPeriodSize;
		//size_t myNumberOfPeriods;
		//uint8_t *mask; //periodSize/8
		
	public:
	//	GFP(size_t period, size_t numPeriod)
	//	{

	//	}
		void read(const char* _Filegfp, const uint16_t NumberOfPeriods, const uint8_t PeriodSize)
		{
			FILE *fp;
			fopen_s(&fp, _Filegfp, "rb");

			if (fp == NULL) {
				printf("Error \n");
				exit(1);
			}

			uint8_t **x;																	// 
			x = new uint8_t*[NumberOfPeriods];												// ������������ ������ 1000�91.
			for (int i = 0; i < NumberOfPeriods; i++) x[i] = new uint8_t[PeriodSize];
			//x[j*periodSize + i]

			for (uint16_t i = 0; i < NumberOfPeriods; i++)									//
			{																				//
				for (uint16_t j = 0; j < PeriodSize; j++)									//
				{																			//
					fread(&x[i][j], 1, 1, fp);												// ��������� �� �����.
				}																			//
			}

			fclose(fp);

			uint8_t* mask = new uint8_t[PeriodSize];										// ����� �������� �����.

			//uint16_t **stat;																// ���������� ������� ����.
			//stat = new uint16_t*[256];
			//for (int i = 0; i < 256; i++) stat[i] = new uint16_t[PeriodSize];
			//stat[256][PeriodSize] = { 0 };
			uint16_t stat[256][90] = { 0 };

			uint16_t min_stat_flag = 0;														// ����������� ���������� gfp ������.

			for (uint8_t j = 0; j < PeriodSize; j++)										// ��������� �� ��������.
			{
				for (uint16_t i = 0; i < NumberOfPeriods; i++)								// 
				{																			// ���������� ������� �����.
					stat[0 + x[i][j]][j]++;													//
				}																			//

				min_stat_flag = std::min(stat[first_flag][j], std::min(stat[third_flag][j], stat[fourth_flag][j])); // ����������� ���������� gfp ������

				uint32_t k = 0;																// ������� � ������ ������� ���������� ����, ���������� �������
				// ������ min_stat_flag.

				for (uint8_t i = 0; i < 255; i++)											// �������� �� ���������� ������� �����.
				{
					if ((i == 0 + first_flag) || (i == 0 + third_flag) || (i == 0 + fourth_flag)) i++; // �� ��������� ����� gfp.

					if (min_stat_flag > stat[i][j]) k++;									// ���� ���������� min_stat_flag ������ ���������� i-�� �����, �� �++
				}

				if (k > 250) mask[j] = 1;													// ���� min_stat_flag - ����. ���������� ����� �� gfp ����, �� ��� ����
				else mask[j] = 0;														    // ����� ������� ����
				std::cout << 0 + mask[j];
			}
		}
	};

	void findflags(const char* _Filegfp, const uint16_t NumberOfPeriods, const uint8_t PeriodSize)
	{
		GFP gfp;
		gfp.read(_Filegfp, NumberOfPeriods, PeriodSize);
	}