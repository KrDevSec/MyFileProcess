/************************************************************

	 Created By Dongho Lim, korea.devsec@gmail.com

*************************************************************/

#include "MyFileProcess.h"

MyFileProcess::MyFileProcess()
{
	/* ������ ����� �߸��� ���(���ڸ� �ѱ��� ���� ���) */

	this->nFileSize = 0;
	this->rawdata = NULL;
	// printf(" [!] MyFileProcess() Constructor Syntax Error...\n");
}

MyFileProcess::MyFileProcess(char* szFilePath)
{
	/* ���� ������ �� �ʱ�ȭ �۾� */
	FILE *pFile = NULL;

	pFile = fopen(szFilePath, "r");					/* ������ �б���� ���� */

	if ( pFile == NULL )							/* ���� ���⿡ ������ ��� */
	{
		printf(" [!] MyFileProcess() File Open Failed...\n");		/* ������ �˸���. */
		return;
	}

	fseek(pFile, 0, SEEK_END);						/* ���� ���� ��ġ�� ������ �̵� */
	this->nFileSize = ftell(pFile);					/* �� ��ġ�� ��ȯ�ϸ�, ������ ũ�� */
	fseek(pFile, 0, SEEK_SET);						/* �ٽ� ������ ó�� ��ġ�� ������ �̵� */

	rawdata = new char[this->nFileSize];				/* ������ ũ�⸸ŭ �Ҵ� */
		
	if ( rawdata == NULL )								/* �Ҵ翡 ������ ��� */
	{
		printf(" [!] MyFileProcess() Data Allocate Failed...\n");	/* ������ �˸���. */
		return;
	}

	/* ������ �о� this->Data�� ���� */
	int nNullCnt = 0;
	char temp;
	int p=0;
	while( !feof(pFile)) {
		fscanf(pFile, "%c", &temp);
		if( temp == 0x0A )
			nNullCnt++;
		this->rawdata[p++] = temp;
	 //�� �پ� �дٰ� �������� ���� ������ ������ ������ ��������
	}
	
	for( --p ; p<=nFileSize; p++ )
		this->rawdata[p] = ' ';

	
	fclose(pFile);									/* ������ �ݴ´�. */
}

MyFileProcess::~MyFileProcess(){
	/* �Ҹ��� �κ� */
	delete this->rawdata;								/* �Ҵ� ���� */
}
int MyFileProcess::GetFileSize(){
	/* ������ ũ�⸦ ��ȯ���ִ� ���� �޼��� */
	return this->nFileSize;
}

char MyFileProcess::GetDataAtIndex(int nIndex)
{
	/* �ε����� �Է¹޾� �������� ���Ҹ� ��ȯ���ִ� ���� �޼��� */
	if( nIndex < this->nFileSize )
		return this->rawdata[nIndex];
	return NULL;
}
	
void MyFileProcess::SetDataAtIndex(int nIndex, char newData){
	/* �ε����� �Է¹ް�, ������ ���ҿ��� ���ο� ���ҷ� �������ִ� ���� �޼��� */
	this->rawdata[nIndex] = newData;
}