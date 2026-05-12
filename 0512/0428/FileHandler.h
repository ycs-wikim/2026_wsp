#pragma once

/// Handle 클래스는 다른 프로젝트에서 이미 개발 완료.
/// 해당 클래스를 그대로 프로젝트에 포함만 시킨 상태!
/// 물리적인 파일 위치는 그대로이지만, 경로만 가지고 온 상태
/// 헤더 파일 추가 시에 전체 경로를 설정해야 참조 가능
#include "../../0331/0331/Handle.h"

/// Doxygen 스타일의 주석
/**
* @brief	파일 처리를 전담하는 클래스
* @author	wikim (unangel@yuhan.ac.kr)
* @date		2026.04.28.
* @copyright Yuhan.ac.kr
*/

/// 함수 또는 클래스/구조체 바로 위에서 "///" 연속으로 입력
/// Visual Studio에서는 MS 스타일의 주석 코드가 자동 생성
/// <summary>
/// 자동으로 생성되는 MS 스타일의 주석
/// Handle이 파일 처리에 필수이기 때문에 Handle 클래스 상속
/// </summary>
class FileHandler
{
private:
	DWORD FSR = FILE_SHARE_READ;
	/// 핸들 객체를 멤버로 선언하여 직접 사용 가능
	Handle m_handle;


	/// <summary>
	/// 실제로 CreateFile을 이용하여 개방하는 메서드
	/// </summary>
	/// <param name="path">경로</param>
	/// <param name="dAccess">개방 목적: GENERIC_READ, GENERIC_WRITE</param>
	/// <param name="sMode">공유 모드 : FILE_SHARE_READ, ...</param>
	/// <param name="fAttribte">파일 모드</param>
	/// <returns>개방 성공 true, 실패 false</returns>
	BOOL real_file_open(
		WCHAR* path,
		DWORD dAccess,
		DWORD sMode,
		DWORD fAttribte
	);

	/// <summary>
	/// 읽기/쓰기 메서드의 인수를 점검하는 함수
	/// </summary>
	/// <param name="buf">읽기/쓰기 버퍼</param>
	/// <param name="len">읽기/쓰기 요청 길이</param>
	/// <param name="length">읽기/쓰기 실제 결과 길이</param>
	/// <returns>인수의 문제가 있다면 FALSE, 문제 없다면 TRUE</returns>
	BOOL check_rdwr_param(
		void* buf,
		DWORD len,
		DWORD* length
	);

public:
	/// <summary>
	/// 기본 파일 열기 : 읽기/쓰기 모두 가능, 공유한다.
	/// </summary>
	/// <param name="path">파일의 경로</param>
	/// <returns>개방 성공 true, 실패 false</returns>
	BOOL FileOpenNormal(WCHAR* path);

	/// 아래 내용과 같이 wrapping 함수를 구성해보자

	/// 클래스의 선언부 : 함수의 원형만! 작성
	BOOL FileRead(void*, DWORD len, DWORD* rlen);
	BOOL FileWrite(void*, DWORD len, DWORD* wlen);

	/// 파일 포인터를 무조건, 현재 위치와 상관 없이 처음으로 보낸다.
	BOOL FilePointerBegin();
	/// 파일 포인터를 처음으로 보내면서, 마지막 위치를 얻는 메서드
	BOOL FilePointerBegin(LARGE_INTEGER *pos);
	/// 파일 포인터를 처음 위치로부터 지정된(pos) 위치로 보내는 메스드
	BOOL FilePointerBegin(LARGE_INTEGER pos);

	BOOL FilePointerBegin(LARGE_INTEGER pos, LARGE_INTEGER *prev);

	/// 파일 포인터를 무조건, 현재 위치와 상관 없이 마지막으로 보낸다.
	BOOL FilePointerEnd();
	/// 파일 포인터를 마지막으로 보내면서, 마지막 위치를 얻는 메서드
	BOOL FilePointerEnd(LARGE_INTEGER* pos);
	/// 추가적으로 다양한 형태의 함수 적용이 가능하다.



	void CloseFile();
};

