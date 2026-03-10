// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>
#include <windows.h>
#include "dprint.h"

using namespace std;

int sum(int a, int b)
{
	/// GO
	return a, b, a + b;
}


int main(int argc, char ** argv)
{
	char buf[128] = "FTP has had a long evolution over the years.  Appendix III is a";

	dprint(buf, 128);

	/*
	int k = sum(3, 6);
	printf("return : %d\n", k);
	/// 일반 변수
	int b = 9;
	int* p1 = &b;
	/// 배열과 포인터
	/// 배열은 선언되자 마자 상수로 고정
	int a[5] = { 1, 2, 3, 4, 5 };
	const int* const p = a;		/// 이미 a는 주소 상태

	for (int i = 0; i < 5; i++)
	{
		printf("[%d] %d\n", i, a[i]);
		printf("p[%d] %d\n", i, *(p + i));
		printf("a[%d] %d\n", i, p[i]);
		printf("e[%d] %d\n", i, *(a+i));
	}




	/ *
	int x[5] = { 0, };

	/// 1이면 조건 완료 상태
	/// 0이면 조건 미완료 상태
	x[0] = 1;
	x[1] = 1;
	x[2] = 1;
	x[3] = 1;
	x[4] = 1;
	/// 5개의 이벤트를 모두 완료한 경우, 
	/// 해당 조건을 만족하는지 확인
	do
	{
		/// 조건 비교
		if (0 == x[0])
			break;
		if (0 == x[1])
			break;
		if (0 == x[2])
			break;
		if (0 == x[3])
			break;
		if (0 == x[4])
			break;
		/// 5가지 조건을 모두 만족했다.
		printf("옛다 전설 퀘스트~\n");
		return 0;

	} while (true);
	/// 아직 완료하지 않은 이벤트가 있다.
	printf("너는 아직 준비가 안됐다.\n");
	*/

	return 0;
}
