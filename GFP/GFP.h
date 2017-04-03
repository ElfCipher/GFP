#ifndef GFP_H
#define GFP_H
#include <cstdint>

class GFP
{
	private:

		const uint8_t first_flag = 0xD5; //10101011
		//const uint8_t second_flag		 = 0x6D; //10110110							������-�� ���������� 0
		const uint8_t third_flag = 0x8C; //00110001
		const uint8_t fourth_flag = 0x07; //11100000
		size_t PeriodSize;
		size_t NumberOfPeriods;
		uint8_t *Mask; //periodSize/8
		uint32_t k;																	// ������� � ������ ������� ���������� ����, ���������� �������
		uint16_t *Statistic;														// ���������� ������� ����
		uint16_t min_stat_flag;														// ����������� ���������� gfp ������

	public:

		//GFP(size_t sNumberOfPeriods, size_t sPeriodSize)
		//{
			
		//}

		void SetPeriod(size_t sPeriodSize);
		void SetNumPeriod(size_t sNumberOfPeriod);

		//~GFP();

		void GenStatistic(const uint8_t* Buffer);

		void GenMask();
		uint8_t* GetMask();
};



#endif