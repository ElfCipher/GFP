#include "stdafx.h"
#include "findflags.h"
#include <iostream>

int main(void)
{
	//GFP f0(90, 1000);
	// обработать файл, выделить память
	findflags("720_gfp.bin", 1000, 90);
	
	return 0;
}

