// 0602.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <Windows.h>


int main()
{
    /// 파일을 개방 -> 파일의 정보(타입, 시간정보)
    HANDLE hFile = CreateFile(L"D:\\test.txt",
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    /// 오류 체크
    if (INVALID_HANDLE_VALUE == hFile)
    {
        printf("error : %s - %d\n", __FUNCTION__, GetLastError());
        return -9;
    }

    /// 대상 커널 객체의 유형에 대해 확인하는 방법
    DWORD type = GetFileType(hFile);
    switch (type)
    {
        case FILE_TYPE_DISK:
            printf("Disk type\n");
            break;
        case FILE_TYPE_PIPE:
            printf("Pipe type\n");
            break;
        case FILE_TYPE_UNKNOWN:
            printf("Unknown type\n");
            break;
        default:
            printf("default type\n");
            break;
    }

    /// 파일의 시간 정보 획득
    /// FILETIME 구조체 형식으로 시간/날짜 정보가 반환됨
    /// FILEIMTE은 기록을 쉽게하기 위해서 작성된 구조체다.
    FILETIME createTime, accessTime, writeTime;
    if (FALSE == GetFileTime(hFile, &createTime, &accessTime, &writeTime))
    {
        printf("error : %s - %d\n", __FUNCTION__, GetLastError());
        CloseHandle(hFile);
        return -9;
    }
    
    /// DWORD 형식으로 시간/날짜를 그대로 출력한 결과
    printf("create time: %d - %d\n", createTime.dwLowDateTime, createTime.dwHighDateTime);
    printf("access time: %d - %d\n", accessTime.dwLowDateTime, accessTime.dwHighDateTime);
    printf("write time: %d - %d\n\n", writeTime.dwLowDateTime, writeTime.dwHighDateTime);

    /// 사람이 알아볼 수 있는 형태의 시간/날짜 정보 보관 구조체 선언
    SYSTEMTIME systime;
    /// 사람이 알아볼 수 있는 형식으로 파일 생성 시간을 변경
    if (FALSE != FileTimeToSystemTime(&createTime, &systime))
    {
        /// 변경이 성공하면 생성 시간 출력
        printf("create time : %d.%d.%d. %d:%d:%d\n",
            systime.wYear, systime.wMonth, systime.wDay,
            systime.wHour + 9, systime.wMinute, systime.wSecond);
    }
    /// 마지막 접근 시간 변경
    if (FALSE != FileTimeToSystemTime(&accessTime, &systime))
    {
        printf("access time : %d.%d.%d. %d:%d:%d\n",
            systime.wYear, systime.wMonth, systime.wDay,
            systime.wHour + 9, systime.wMinute, systime.wSecond);
    }
    /// 마지막 수정 시간 변경
    if (FALSE != FileTimeToSystemTime(&writeTime, &systime))
    {
        printf("write time : %d.%d.%d. %d:%d:%d\n",
            systime.wYear, systime.wMonth, systime.wDay,
            systime.wHour + 9, systime.wMinute, systime.wSecond);
    }

    /// 파일의 생성 시간을 변경
    /// 사람이 알아볼 수 있는 형태에서 기록 형태로 변경
    systime.wYear = 2030;
    systime.wMonth = 11;
    systime.wDay = 11;
    /// SYSTEMTIME을 FILETIME으로 변환
    if (FALSE != SystemTimeToFileTime(&systime, &createTime))
    {
        /// 변환 성공 시, 파일의 생성 시간을 변경
        if (FALSE == SetFileTime(hFile, &createTime, NULL, NULL))
        {
            /// 변경이 실패한 경우의 오류 출력
            printf("SetFileTime Error: %d\n", GetLastError());
        }
    }
    /// 시간 변경이 성공했다면, 탐색기의 파일 속성에서 확인

    /// 핸들 닫기
    CloseHandle(hFile);
    std::cout << "Hello World!\n";
}
