#pragma once

#include <windows.h>

/**
* 윈도우 OS와 정보 교환하는 가장 기초적인 자료형 HANDLE을
* 보관하고, 사용할 수 있도록 만들어 주는 클래스를 선언.
*/

class Handle
{
/// 접근 권한 설정
/// C++을 별도로 설정하지 않으면 private 권한
/// JAVA에서는 별도로 설정하지 않으면 public 권한
private:
	/// 내부에서 관리하는 실제 핸들 객체
	HANDLE m_handle;
	/// 내부에서 핸들 값이 정상 값인지 확인하는 메서드.
	void handleCheck(HANDLE);
public:
	/// default 생성자. 인수 없이 이름만 사용하는 경우.
	Handle();
	/// HANDLE을 초기화 인수로 받는 생성자.
	Handle(HANDLE);
	/// 멤버 변수인 HANDLE을 자동으로 해제하는 소멸자 선언
	~Handle();
	/// =(대입 연산자)를 통해 핸들 값을 초기화하는 연산자 오버로딩.
	void operator=(HANDLE);
	/// 핸들이 정상적인 값을 가지고 있는지 여부를 반환하는 메서드
	BOOL isSetHandle();
	/// 핸들 값이 별도로 사용되어야 하는 경우 핸들을 반환하는 메서드
	HANDLE getHandle();
	/// 핸들을 닫고 초기화하는 메서드
	void closeHandle();
};

