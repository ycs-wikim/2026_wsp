// 0317.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

/// 클래스의 선언 : 예약어 클래스이름 { ... };
class testClass
{
/// 접근 권한 : 누구나 접근이 가능
public:
    /// const 멤버 함수는 인스턴스화 시점(생성자 호출 시점)에 초기화가 가능!!!
    const int m_value;
    int m_x;

    /// 생성자와 소멸자는 반드시 public 접근 권한을 가져야 한다.
    ///     ==> 외부에서 생/소멸자를 호출하기 때문에 외부 접근이 가능!

    /// 생성자 : 반환 값이 없고, 클래스 이름과 동일한 함수로 여러개 만들 수 있다.
    ///     함수의 오버로딩이 허용되기 때문에 생성자를 다수 개를 만들 수 있다.
    ///     => 함수의 인수에 따라 같은 이름의 생성자라도 다수 개를 만들 수 있다.
    testClass(int x) : m_value(x)
    {
        m_x = x;
    }

    testClass() : m_value(999)
    {
        /// 클래스의 초기화 내용
        m_x = 0;
    }

    /// 소멸자 : 반환 값이 없고, 인수도 받을 수 없는 함수, 시작을 ~로 한다.
    ///     소멸자는 클래스 내부에 단 하나만 존재할 수 있다.
    ~testClass()
    {
        printf("%s called\n", __FUNCTION__);
    }


/// 접근 권한 : 관계가 있는 클래스라면 누구나 접근이 가능
protected:

/// 접근 권한 : 오직 이 클래스(testClass)만 사용할 수 있는 정보와 기능
private:

};



int main()
{
    testClass t(3);
    /// const는 선언 즉시 초기화해야 한다.
    const int x = 9;
    std::cout << "Hello World!\n";
}
