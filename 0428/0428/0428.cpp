// 0428.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

#include <Windows.h>
#include "FileHandler.h"


int main()
{
    /// 파일 처리 객체 생성
    FileHandler fh;
    if (FALSE == fh.FileOpenNormal((WCHAR*)"test.txt"))
    {
        printf("파일 개방 실패~\n");
    }
    /// 읽기/쓰기....

    /// 닫기
    fh.CloseFile();
    std::cout << "Hello World!\n";
}
