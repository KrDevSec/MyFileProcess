/************************************************************

	 Created By Dongho Lim, korea.devsec@gmail.com

*************************************************************/

#include "MyFileProcess.h"

MyFileProcess::MyFileProcess()
{
	/* 생성자 사용을 잘못한 경우(인자를 넘기지 않은 경우) */

	this->nFileSize = 0;
	this->rawdata = NULL;
	// printf(" [!] MyFileProcess() Constructor Syntax Error...\n");
}

MyFileProcess::MyFileProcess(char* szFilePath)
{
	/* 정상 생성자 및 초기화 작업 */
	FILE *pFile = NULL;

	pFile = fopen(szFilePath, "r");					/* 파일을 읽기모드로 열고 */

	if ( pFile == NULL )							/* 파일 열기에 실패한 경우 */
	{
		printf(" [!] MyFileProcess() File Open Failed...\n");		/* 오류를 알린다. */
		return;
	}

	fseek(pFile, 0, SEEK_END);						/* 파일 끝의 위치로 포인터 이동 */
	this->nFileSize = ftell(pFile);					/* 그 위치를 반환하면, 파일의 크기 */
	fseek(pFile, 0, SEEK_SET);						/* 다시 파일의 처음 위치로 포인터 이동 */

	rawdata = new char[this->nFileSize];				/* 파일의 크기만큼 할당 */
		
	if ( rawdata == NULL )								/* 할당에 실패한 경우 */
	{
		printf(" [!] MyFileProcess() Data Allocate Failed...\n");	/* 오류를 알린다. */
		return;
	}

	/* 파일을 읽어 this->Data에 저장 */
	int nNullCnt = 0;
	char temp;
	int p=0;
	while( !feof(pFile)) {
		fscanf(pFile, "%c", &temp);
		if( temp == 0x0A )
			nNullCnt++;
		this->rawdata[p++] = temp;
	 //한 줄씩 읽다가 마지막에 읽은 내용이 없으면 루프를 빠져나옴
	}
	
	for( --p ; p<=nFileSize; p++ )
		this->rawdata[p] = ' ';

	
	fclose(pFile);									/* 파일을 닫는다. */
}

MyFileProcess::~MyFileProcess(){
	/* 소멸자 부분 */
	delete this->rawdata;								/* 할당 해제 */
}
int MyFileProcess::GetFileSize(){
	/* 파일의 크기를 반환해주는 접근 메서드 */
	return this->nFileSize;
}

char MyFileProcess::GetDataAtIndex(int nIndex)
{
	/* 인덱스를 입력받아 데이터의 원소를 반환해주는 접근 메서드 */
	if( nIndex < this->nFileSize )
		return this->rawdata[nIndex];
	return NULL;
}
	
void MyFileProcess::SetDataAtIndex(int nIndex, char newData){
	/* 인덱스를 입력받고, 기존의 원소에서 새로운 원소로 수정해주는 설정 메서드 */
	this->rawdata[nIndex] = newData;
}