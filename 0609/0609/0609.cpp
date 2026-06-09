// 0609.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <Windows.h>

/// 스레드 함수 원형 (고정되어 있음)
/// DWORD WINAPI 함수이름(LPVOID 인수)
DWORD WINAPI pig(LPVOID param)
{
    int cnt = (int)param;

    for (int i = 0; i < 100; i++)
    {
        printf("%d - %d\n", cnt, i);
        /// 밀리 세컨 단위로 휴식할 시간을 제공
        Sleep(100);
    }

    /// 스레드 스스로 종료를 요청하는 API
    ExitThread(0);      /// 0번은 정상 종료
    return 0;
}


int main()
{
    //pig(NULL); // 일반 함수처럼 호출 가능!
    HANDLE hThread[5] = { INVALID_HANDLE_VALUE, };

    for (int i = 0; i < 5; i++)
    {
        /// 스레드 생성 API
        hThread[i] = CreateThread(
            NULL,       /// 보안 속성 -> NULL 이면 현재 프로세스와 동일한 권한
            0,          /// 스택 크기 -> 0이면 기본 값 1MB로 설정
            pig,        /// 스레드 함수 이름
            (LPVOID)i,       /// 인수
            0,          /// 시작 시 상태 -> 0이면 즉시 동작
            NULL        /// Thread의 ID 값을 반환 받는 변수
        );
    }

    Sleep(3000);
    printf("일시 중단\n");
    /// 스레드를 일시 중단 시키는 API
    for(int i = 0; i < 5; i++)
        SuspendThread(hThread[i]);

    Sleep(2000);
    printf("작업 재개\n");
    /// 스레드의 작업을 재개 시키는 API
    for (int i = 0; i < 5; i++)
        ResumeThread(hThread[i]);

    Sleep(3000);

    /// 스레드 대기 API
    for (int i = 0; i < 5; i++)
        WaitForSingleObject(hThread[i], INFINITE);

    /// 핸들 닫기
    for (int i = 0; i < 5; i++)
        CloseHandle(hThread[i]);

    std::cout << "Hello World!\n";
}
