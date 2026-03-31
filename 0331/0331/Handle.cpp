#include "Handle.h"

/// default 생성자. 인수 없이 이름만 사용하는 경우.
Handle::Handle()
{
	m_handle = INVALID_HANDLE_VALUE;
}


/// 멤버 변수인 HANDLE을 자동으로 해제하는 소멸자 선언
Handle::~Handle()
{
	/// 여기도 중복 체크~~~
	CloseHandle(m_handle);
}


/// 내부에서 핸들 값이 정상 값인지 확인하는 메서드.
void Handle::handleCheck(HANDLE handle__)
{
	/// 혹시나 개발자가 실수로 전달하는 경우 방지를 위한 점검
	if (NULL == handle__)
		return;
	/// 개발자가 값을 확인하지 않고 전달하는 경우 방지를 위한 점검
	if (INVALID_HANDLE_VALUE == handle__)
		return;
	/// 문제가 없는 핸들이면 멤버 변수에 할당!
	m_handle = handle__;
}

/// HANDLE을 초기화 인수로 받는 생성자.
Handle::Handle(HANDLE handle__)
{
	handleCheck(handle__);
}


/// =(대입 연산자)를 통해 핸들 값을 초기화하는 연산자 오버로딩.
void Handle::operator=(HANDLE handle__)
{
	handleCheck(handle__);
}


/// 핸들이 정상적인 값을 가지고 있는지 여부를 반환하는 메서드
BOOL Handle::isSetHandle()
{
	///
	/// checkHandle( ) 중복된 코드가 발생합니다!!!!!
	/// 어떻게 코드를 수정하면 중복 없이 모두 동작할 수 있을까요?
	/// 
	/// 혹시나 개발자가 실수로 전달하는 경우 방지를 위한 점검
	if (NULL == m_handle)
		return FALSE;
	/// 개발자가 값을 확인하지 않고 전달하는 경우 방지를 위한 점검
	if (INVALID_HANDLE_VALUE == m_handle)
		return FALSE;
	/// 정상 핸들 값을 보관하고 있음을 알림
	return TRUE;
}


/// 핸들 값이 별도로 사용되어야 하는 경우 핸들을 반환하는 메서드
HANDLE Handle::getHandle()
{
	return m_handle;
}

/// 핸들을 닫고 초기화하는 메서드
void Handle::closeHandle()
{
	/// 중복 체크 필요
	///
	CloseHandle(m_handle);
	m_handle = INVALID_HANDLE_VALUE;
}
