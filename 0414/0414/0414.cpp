// 0414.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <windows.h>

using namespace std;

/**
* LARGE_INTEGER 관련 내용 확인 함수
*/
void lit()
{
    /// 잘못된 초기화 방법
    //LARGE_INTEGER litest = 0;
    /// LARGE_INTEGER의 정식 초기화 방법
    LARGE_INTEGER litest = { 0, };
    /// 32비트씩 별도 초기화
    litest.LowPart = 199;
    litest.HighPart = 2000;
    /// 메모리를 구분해서 32비트씩 정확하게 따로 사용된다.
    /// 32비트와 64비트 형식으로 위의 값을 출력한 경우
    printf("LOW[ %d ] HI[ %d ]\n", litest.LowPart, litest.HighPart);
    /// QuadPart 출력시 예상하지 못한 값이 출력
    printf("QUAD[ %lld ]\n", litest.QuadPart);
    /// 64비트 값으로 초기화
    litest.QuadPart = 2199;
    printf("LOW[ %d ] HI[ %d ]\n", litest.LowPart, litest.HighPart);
    printf("QUAD[ %lld ]\n", litest.QuadPart);
    /// 64비트 값으로 초기화
    litest.QuadPart = 8589934592199;
    printf("LOW[ %d ] HI[ %d ]\n", litest.LowPart, litest.HighPart);
    printf("QUAD[ %lld ]\n", litest.QuadPart);
    /// int 형식의 32bit 시스템에서는 하위 값만 보관(오버플로우)
    int va = 8589934592199;
    printf("int: %d\n", va);
}


int main()
{
    //lit();
    //return 0;

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
    LARGE_INTEGER liSize = { 0, };

    /// 파일 크기 획득
    if (FALSE == GetFileSizeEx(h, &liSize))
    {
        printf("파일 크기 획득 실패: %d\n", GetLastError());
        CloseHandle(h);
        return -9;
    }
    /// 파일 크기를 획득한 상태
    printf("파일 크기: %lld\n", liSize.QuadPart);

    /// 파일 포인터 이동
    char buffer[128] = { 0, };
    LARGE_INTEGER liMove = { 0, };      /// 이동할 변위
    LARGE_INTEGER liAfter = { 0, };     /// 이동한 후의 포인터 위치

    for (int i = 0; i < 20; i++)
    {
        liMove.QuadPart = i;
        /// 파일의 시작 위치로 파일 포인터를 이동시켜라.
        if (FALSE == SetFilePointerEx(h, liMove, &liAfter, FILE_BEGIN))
        {
            printf("파일 포인터 이동 실패: %d\n", GetLastError());
            CloseHandle(h);
            return -9;
        }

        if (FALSE == ReadFile(h, buffer, 128, &len, NULL))
        {
            printf("파일 읽기 실패: %d\n", GetLastError());
            CloseHandle(h);
            return -9;
        }

        printf("파일의 내용: %s\n", buffer);
        memset(buffer, 0x00, 128);
    }

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
