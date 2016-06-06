/************************************************************

	 Created By Dongho Lim, korea.devsec@gmail.com

*************************************************************/
#pragma once
#include <stdio.h>

class MyFileProcess {

protected:
	char *rawdata;
	int nFileSize;

public:
	MyFileProcess();	
	MyFileProcess(char* szFilePath);
	~MyFileProcess();
	int GetFileSize();
	char GetDataAtIndex(int nIndex);
	void SetDataAtIndex(int nIndex, char newData);

};