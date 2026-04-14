// 0414.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <windows.h>

using namespace std;


int main()
{
    DWORD error = 0;
    HANDLE h = INVALID_HANDLE_VALUE;
    h = CreateFile(L"d:\\test.txt",
                GENERIC_READ | GENERIC_WRITE,
                0,
                NULL,
                CREATE_ALWAYS,
                FILE_ATTRIBUTE_NORMAL,
                NULL);
    if (INVALID_HANDLE_VALUE == h)
    {
        printf("파일 생성 실패 : %d\n", GetLastError());
        return -9;
    }

    /// 파일 기록 버퍼
    char buf[128] = "get file error Create File error GetlastError";
    DWORD len = 0;
    if (FALSE == WriteFile(h, buf, strlen(buf), &len, NULL))
    {
        printf("파일 기록 실패 : %d\n", GetLastError());
        CloseHandle(h);
        return -9;
    }
    
    /// 핸들이 아직 유효한 상태

    /// OS에게 서비스 요청 : 파일 삭제
    if (DeleteFile(L"d:\\test.txt"))
    {
        printf("파일 삭제 완료\n");
    }
    else
    {
        error = GetLastError();
        printf("파일 삭제 실패: %d\n", error);
    }
    CloseHandle(h);
    
    std::cout << "Hello World!\n";

}
