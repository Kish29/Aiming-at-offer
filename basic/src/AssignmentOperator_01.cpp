//
// Created by jar on 9/12/2020.
//

#include <new>
#include "cstring"
#include "cstdio"
#include "exception"

class CMyString {
public:
    explicit CMyString(char *pData = nullptr);

    explicit CMyString(const CMyString &str);

    // 赋值重载运算符
    CMyString &operator=(const CMyString &str);

    ~CMyString();

    void Print();

private:
    char *m_pData;
};

CMyString::CMyString(char *pData) {
    if (pData == nullptr) {
        m_pData = new char[1];
        m_pData[0] = '\0';
    } else {
        // 注意末尾的'\0'
        m_pData = new char[strlen(pData) + 1];
        strcpy(m_pData, pData);
    }
}

CMyString::CMyString(const CMyString &str) {
    // 深复制
    m_pData = new char[strlen(str.m_pData) + 1];
    strcpy(m_pData, str.m_pData);
}

CMyString::~CMyString() {
    delete[] m_pData;
    m_pData = nullptr;
}

// 空指针、内存泄漏
// CMyString &CMyString::operator=(const CMyString &str) {
//     if (&str == nullptr || &str == this)
//         return *this;
//     delete[] m_pData;
//     m_pData = nullptr;
//
//     m_pData = new char[strlen(str.m_pData) + 1];
//     strcpy(m_pData, str.m_pData);
//     return *this;
// }

// 加入异常安全
// CMyString &CMyString::operator=(const CMyString &str) {
//     if (&str != nullptr) {
//         if (&str != this) {
//             CMyString strTemp(str);
//
//             char *pTemp = strTemp.m_pData;
//             strTemp.m_pData = m_pData;
//             m_pData = pTemp;
//         }
//     }
//     return *this;
// }

// 版本2
CMyString &CMyString::operator=(const CMyString &str) {
    if (&str == nullptr || &str == this)
        return *this;

    char *tmp_str = nullptr;
    try {
        tmp_str = new char[strlen(str.m_pData) + 1];
        strcpy(tmp_str, str.m_pData);
    } catch (std::bad_alloc &e) {
        e.what();
    }

    delete[] m_pData;
    m_pData = nullptr;
    m_pData = tmp_str;

    return *this;
}

/************测试代码************/

// print
void CMyString::Print() {
    printf("%s", m_pData);
}

// 1 正常测试
void Test1() {
    printf("Test1 running...\n");

    char *text = (char *) "Hello World\n";

    CMyString str1(text);
    CMyString str2;
    str2 = str1;

    str1.Print();
    str2.Print();
}

// 2 传入空指针测试
void Test2() {
    printf("Test2 running...\n");

    CMyString *str1 = nullptr;
    CMyString str2;
    str2 = *str1;

    str2.Print();
}

// 3 传入自身测试
void Test3() {
    printf("Test3 running...\n");

    char *text = (char *) "Hello World\n";

    CMyString str1(text);
    str1 = str1;

    str1.Print();
}

// 4 连续赋值
void Test4() {
    printf("Test4 running...\n");

    char *text = (char *) "Hello World\n";

    CMyString str1(text);
    CMyString str2;
    CMyString str3;
    str3 = str2 = str1;

    str1.Print();
    str2.Print();
    str3.Print();
}

void TestAll() {
    Test1();
    Test2();
    Test3();
    Test4();
}

int main() {
    TestAll();
}
