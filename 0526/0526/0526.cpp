// 0526.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
    setlocale(LC_ALL, "");

    /// 감시할 디렉터리의 핸들
    HANDLE hDir = INVALID_HANDLE_VALUE;
    /// 디렉터리 변경에 대한 이벤트를 받을 Actions 목록 설정
    DWORD flags =   FILE_NOTIFY_CHANGE_FILE_NAME |      /// 파일 이름 변경
                    FILE_NOTIFY_CHANGE_DIR_NAME |       /// 디렉터리 이름 변경
                    FILE_NOTIFY_CHANGE_ATTRIBUTES |     /// 파일 속성 변경
                    FILE_NOTIFY_CHANGE_SIZE |           /// 파일 크기 변경
                    FILE_NOTIFY_CHANGE_LAST_WRITE |     /// 마지막 수정 발생
                    FILE_NOTIFY_CHANGE_CREATION;        /// 파일 생성
    /// 변경 정보를 받을 버퍼 선언
    //alignas(DWORD) uint8_t c_buf[1024];     /// 교재
    BYTE bData[2048] = { 0, };
    /// 실제 반환된 정보의 길이
    DWORD len = 0;

    /// 디렉터리를 감시 형태로 개방
    hDir = CreateFile(  L"D:\\202507000",
                        FILE_LIST_DIRECTORY,
                        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                        NULL,
                        OPEN_EXISTING,
                        FILE_FLAG_BACKUP_SEMANTICS,
                        NULL
                        );

    /// 디렉터리 핸들 획득 여부 확인
    if (INVALID_HANDLE_VALUE == hDir)
    {
        printf("CreateFile : %d\n", GetLastError());
        return -9;
    }

    for (int i = 0; i < 10; i++)
    {
        /// ReadDirectoryChangesW( )는 현재 위치에서 Pending 상태로 변경
        /// ==> OS가 정보를 반환하기 전까지는 무한정 대기 상태
        if (FALSE == ReadDirectoryChangesW(hDir,    /// 감시 디렉터리 핸들
            bData,      /// 정보가 넘겨져 올 버퍼
            2048,       /// 버퍼의 크기
            TRUE,       /// 하위 디렉터리 감시 여부
            flags,      /// 감시 종류
            &len,       /// 사용한 버퍼의 길이
            NULL,       /// Overlapped 구조체 : 비동기
            NULL        /// APC 이름 : 비동기
        ))
        {
            printf("ReadDirectoryChagesW : %d\n", GetLastError());
            CloseHandle(hDir);
            return -9;
        }

        /// 변경된 정보가 정상적으로 도착했다.
        FILE_NOTIFY_INFORMATION* event = (FILE_NOTIFY_INFORMATION*)bData;

        while (TRUE)
        {
            printf("NEO[ %d ] Action[ %d ], FNL[ %d ] FN[ %ws ]\n",
                event->NextEntryOffset, event->Action, event->FileNameLength,
                event->FileName);

            switch (event->Action)
            {
            case FILE_ACTION_ADDED:     /// 새로운 파일이 생성
                printf("파일 추가: %ws\n", event->FileName);
                break;

            case FILE_ACTION_MODIFIED:  /// 존재하는 파일이 수정
                printf("파일 수정: %ws\n", event->FileName);
                break;

            case FILE_ACTION_REMOVED:   /// 존재하는 파일이 삭제
                printf("파일 삭제: %ws\n", event->FileName);
                break;

                /// 파일 이름이 변경된 경우
            case FILE_ACTION_RENAMED_NEW_NAME:  /// 새로운 파일 이름
                printf("파일 새 이름: %ws\n", event->FileName);
                break;

            case FILE_ACTION_RENAMED_OLD_NAME:  /// 이전 파일 이름
                printf("파일 이전 이름: %ws\n", event->FileName);
                break;
            }
            /// 1개의 데이터에 대한 정보 출력 완료

            /// 무한 반복을 종료시키는 위치
            /// NextEntryOffset이 0이면 뒤에 데이터가 없다라는 의미.
            if (0 == event->NextEntryOffset)
                break;
            /// NextEntryOffset이 0이 아니라는 의미 => 다음 데이터가 있다.
            event = (FILE_NOTIFY_INFORMATION*)((PBYTE)event + event->NextEntryOffset);

            printf("\n%d\n", i);
        }
    }

    std::cout << "Hello World!\n";
}
