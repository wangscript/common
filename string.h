
/******************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017
See the license in LICENSE
******************************************************/

#ifndef String_H
#define String_H

#include <string.h>
#define _NO_GTK

#if !defined(_WINNT_)
typedef wchar_t WCHAR;
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned int UINT;
#endif

#ifndef SAFE_DELETE_A
#define SAFE_DELETE_A(p) if(p)\
	{\
		delete [] (p);\
		(p) = NULL;\
	}
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) if(p)\
	{\
		delete (p);\
		(p) = NULL;\
	}
#endif

#define def_str_validate(str) (str && str[0]!=0 && str[0]!='0')

bool StrValidate(const char* str);

void StrCutMesh(const char* path, char* name);

void StrCutSound(const char* path, char* name);

void StrCutName(const char* path, char* name);

void StrCutNameNEx(const char* path, char* name);

//парсинг строки (имени файла) str на имя папки path и имя файла name
//str = test_file_1.ex - path = test, name = file_1.ex
bool StrParsePathName(const char* str, char* path, char* name);


class StringW;

class String
{
public:
	friend class StringW;
	String();
	String(const char *	str);
	String(const char		sym);
	String(const int		num);
	String(const unsigned short		num);
	String(const unsigned long	num);
	String(const long		num);
	String(const double	num);
	String(const bool		bf);
	String(const String & str);
	String(const String * str);

	String(String && other);

	~String();

	void Release();

	////////////////////////////////////
	//�������� �������� �����
	//������������ ���������� ����� ������ String 
	//������� � �������� ��������� �������� �����

	String operator+(const String & str) const;
	String operator+(const String * str);

	String operator+(const char *	str);
	String operator+(const char &	sym);
	String operator+(const int &	num);
	String operator+(const unsigned short &	num);
	String operator+(const unsigned long &num);
	String operator+(const long &	num);
	String operator+(const double &num);
	String operator+(const bool &	bf);

	////////////////////////////////////
	//�������� ����������

	String & operator=(const String & str);
	String & operator=(const String * str);

	String & operator=(const char *	str);
	String & operator=(const char &	sym);
	String & operator=(const int &	num);
	String & operator=(const unsigned short &	num);
	String & operator=(const unsigned long &	num);
	String & operator=(const long &	num);
	String & operator=(const double &	num);
	String & operator=(const bool &	bf);

	String & operator=(String && other);

	////////////////////////////////////
	//�������� �������� ����� ������� � �������� ����������� �������� � ����������
	String & operator+=(const String &str);
	String & operator+=(const String *str);

	String & operator+=(const char *	str);
	String & operator+=(const char &	sym);
	String & operator+=(const int &	num);
	String & operator+=(const unsigned short &	num);
	String & operator+=(const unsigned long &	num);
	String & operator+=(const long &	num);
	String & operator+=(const double &num);
	String & operator+=(const bool &	bf);

	////////////////////////////////////
	//��������� ������ ���������� �� ������
	//������������ ����� ������ String, ������� �������� ���������
	String operator-(const String & str);
	String operator-(const String * str);

	String operator-(const char *	str);
	String operator-(const char &	sym);
	String operator-(const int &	num);
	String operator-(const unsigned short &	num);
	String operator-(const unsigned long &	num);
	String operator-(const long &	num);
	String operator-(const double &	num);
	String operator-(const bool &	bf);

	////////////////////////////////////
	//��������� ������ ���������� �� ������� �������
	String & operator-=(const String &str);
	String & operator-=(const String *str);

	String & operator-=(const char *	str);
	String & operator-=(const char &	sym);
	String & operator-=(const int &	num);
	String & operator-=(const unsigned short &	num);
	String & operator-=(const unsigned long &	num);
	String & operator-=(const long &	num);
	String & operator-=(const double &num);
	String & operator-=(const bool &	bf);

	//////////////////////////////////////
	//��������� ��� ������� ����������
	//������������ ����� ������ String
	String operator / (const String &str);
	String operator / (const String *str);

	String operator/(const char *	str);
	String operator/(const char &	sym);
	String operator/(const int &	num);
	String operator/(const unsigned short &	num);
	String operator/(const unsigned long &	num);
	String operator/(const long &	num);
	String operator/(const double &	num);
	String operator/(const bool &	bf);

	////////////////////////////////////
	//��������� ��� ������� ����������
	String & operator/=(const String &str);
	String & operator/=(const String *str);

	String & operator/=(const char *	str);
	String & operator/=(const char &	sym);
	String & operator/=(const int &	num);
	String & operator/=(const unsigned short &	num);
	String & operator/=(const unsigned long &	num);
	String & operator/=(const long &	num);
	String & operator/=(const double &num);
	String & operator/=(const bool &	bf);

	////////////////////////////////////

	bool operator==(const String &str) const;
	bool operator==(const String *str) const;

	bool operator==(const char *	str) const;
	bool operator==(const char &	sym) const;
	bool operator==(const int &		num) const;
	bool operator==(const unsigned short &	num) const;
	bool operator==(const unsigned long &	num) const;
	bool operator==(const long &	num) const;
	bool operator==(const double &	num) const;
	bool operator==(const bool &	bf) const;

	//////////////////////////////////////

	bool operator!= (const String &str) const;
	bool operator!= (const String *str) const;

	bool operator!=(const char *	str) const;
	bool operator!=(const char &	sym) const;
	bool operator!=(const int &		num) const;
	bool operator!=(const unsigned short &	num) const;
	bool operator!=(const unsigned long &	num) const;
	bool operator!=(const long &	num) const;
	bool operator!=(const double &	num) const;
	bool operator!=(const bool &	bf) const;

	//////////////////////////////////////
	char & operator[](const unsigned long & num);
	const char & operator[](const unsigned long & num) const;
	//////////////////////////////////////

	unsigned long length() const;
	unsigned long find(const char & c, unsigned long pos = 0) const;
	unsigned long find(const char * str, unsigned long pos = 0) const;
	unsigned long find(const String & str, unsigned long pos = 0) const;

	unsigned long find_last_of(const char & c, unsigned long pos = 0) const;
	unsigned long find_last_of(const char * str, unsigned long pos = 0) const;
	unsigned long find_last_of(const String & str, unsigned long pos = 0) const;

	unsigned long Replace(const char * str, const char * replace, unsigned long pos);
	unsigned long Replace(const String & str, const String & replace, unsigned long pos);

	unsigned long ReplaceAll(const char * str, const char * replace);
	unsigned long ReplaceAll(const String & str, const String & replace);

	//char * SubStr(unsigned long pos, unsigned long lenght); // ��� ������ �� �����
	String substr(unsigned long pos, unsigned long lenght = 0) const;
	unsigned int Delete(unsigned long pos, unsigned long lenght);

	String trim();

	const char * c_str() const;

	void Reserve(int length);
	void AppendReserve(int length);

	int		ToInt() const;
	long	ToLongInt() const;
	unsigned long	ToUnsLongInt() const;
	double	ToDouble() const;
	bool	ToBool() const;

	operator StringW() const;

	bool operator<(const String & s) const;

protected:
	char * string;
};

//bool operator<(const String & a, const String & b);



class StringW
{
public:
	friend class String;
	StringW();
	StringW(const WCHAR *	str);
	StringW(const WCHAR		sym);
	StringW(const int		num);
	StringW(const unsigned short		num);
	StringW(const unsigned long	num);
	StringW(const long		num);
	StringW(const double	num);
	StringW(const bool		bf);
	StringW(const StringW & str);
	StringW(const StringW * str);

	StringW(StringW && other);

	~StringW();

	void Release();

	////////////////////////////////////
	//�������� �������� �����
	//������������ ���������� ����� ������ StringW 
	//������� � �������� ��������� �������� �����

	StringW operator+(const StringW & str) const;
	StringW operator+(const StringW * str);

	StringW operator+(const WCHAR *	str);
	StringW operator+(const WCHAR &	sym);
	StringW operator+(const int &	num);
	StringW operator+(const unsigned short &	num);
	StringW operator+(const unsigned long &num);
	StringW operator+(const long &	num);
	StringW operator+(const double &num);
	StringW operator+(const bool &	bf);

	////////////////////////////////////
	//�������� ����������

	StringW & operator=(const StringW & str);
	StringW & operator=(const StringW * str);

	StringW & operator=(const WCHAR *	str);
	StringW & operator=(const WCHAR &	sym);
	StringW & operator=(const int &	num);
	StringW & operator=(const unsigned short &	num);
	StringW & operator=(const unsigned long &	num);
	StringW & operator=(const long &	num);
	StringW & operator=(const double &	num);
	StringW & operator=(const bool &	bf);

	StringW & operator=(StringW && other);

	////////////////////////////////////
	//�������� �������� ����� ������� � �������� ����������� �������� � ����������
	StringW & operator+=(const StringW &str);
	StringW & operator+=(const StringW *str);

	StringW & operator+=(const WCHAR *	str);
	StringW & operator+=(const WCHAR &	sym);
	StringW & operator+=(const int &	num);
	StringW & operator+=(const unsigned short &	num);
	StringW & operator+=(const unsigned long &	num);
	StringW & operator+=(const long &	num);
	StringW & operator+=(const double &num);
	StringW & operator+=(const bool &	bf);

	////////////////////////////////////
	//��������� ������ ���������� �� ������
	//������������ ����� ������ StringW, ������� �������� ���������
	StringW operator-(const StringW & str);
	StringW operator-(const StringW * str);

	StringW operator-(const WCHAR *	str);
	StringW operator-(const WCHAR &	sym);
	StringW operator-(const int &	num);
	StringW operator-(const unsigned short &	num);
	StringW operator-(const unsigned long &	num);
	StringW operator-(const long &	num);
	StringW operator-(const double &	num);
	StringW operator-(const bool &	bf);

	////////////////////////////////////
	//��������� ������ ���������� �� ������� �������
	StringW & operator-=(const StringW &str);
	StringW & operator-=(const StringW *str);

	StringW & operator-=(const WCHAR *	str);
	StringW & operator-=(const WCHAR &	sym);
	StringW & operator-=(const int &	num);
	StringW & operator-=(const unsigned short &	num);
	StringW & operator-=(const unsigned long &	num);
	StringW & operator-=(const long &	num);
	StringW & operator-=(const double &num);
	StringW & operator-=(const bool &	bf);

	//////////////////////////////////////
	//��������� ��� ������� ����������
	//������������ ����� ������ StringW
	StringW operator / (const StringW &str);
	StringW operator / (const StringW *str);

	StringW operator/(const WCHAR *	str);
	StringW operator/(const WCHAR &	sym);
	StringW operator/(const int &	num);
	StringW operator/(const unsigned short &	num);
	StringW operator/(const unsigned long &	num);
	StringW operator/(const long &	num);
	StringW operator/(const double &	num);
	StringW operator/(const bool &	bf);

	////////////////////////////////////
	//��������� ��� ������� ����������
	StringW & operator/=(const StringW &str);
	StringW & operator/=(const StringW *str);

	StringW & operator/=(const WCHAR *	str);
	StringW & operator/=(const WCHAR &	sym);
	StringW & operator/=(const int &	num);
	StringW & operator/=(const unsigned short &	num);
	StringW & operator/=(const unsigned long &	num);
	StringW & operator/=(const long &	num);
	StringW & operator/=(const double &num);
	StringW & operator/=(const bool &	bf);

	////////////////////////////////////

	bool operator==(const StringW &str) const;
	bool operator==(const StringW *str) const;

	bool operator==(const WCHAR *	str) const;
	bool operator==(const WCHAR &	sym) const;
	bool operator==(const int &		num) const;
	bool operator==(const unsigned short &	num) const;
	bool operator==(const unsigned long &	num) const;
	bool operator==(const long &	num) const;
	bool operator==(const double &	num) const;
	bool operator==(const bool &	bf) const;

	//////////////////////////////////////

	bool operator!= (const StringW &str) const;
	bool operator!= (const StringW *str) const;

	bool operator!=(const WCHAR *	str) const;
	bool operator!=(const WCHAR &	sym) const;
	bool operator!=(const int &		num) const;
	bool operator!=(const unsigned short &	num) const;
	bool operator!=(const unsigned long &	num) const;
	bool operator!=(const long &	num) const;
	bool operator!=(const double &	num) const;
	bool operator!=(const bool &	bf) const;

	//////////////////////////////////////
	WCHAR & operator[](const unsigned long & num);
	const WCHAR & operator[](const unsigned long & num) const;
	//////////////////////////////////////

	void insert(unsigned int pos, const WCHAR * data);
	void insert(unsigned int pos, const StringW & data);

	unsigned long length() const;
	unsigned long find(const WCHAR & c, unsigned long pos = 0) const;
	unsigned long find(const WCHAR * str, unsigned long pos = 0) const;
	unsigned long find(const StringW & str, unsigned long pos = 0) const;

	unsigned long find_last_of(const WCHAR & c, unsigned long pos = 0) const;
	unsigned long find_last_of(const WCHAR * str, unsigned long pos = 0) const;
	unsigned long find_last_of(const StringW & str, unsigned long pos = 0) const;

	unsigned long Replace(const WCHAR * str, const WCHAR * replace, unsigned long pos);
	unsigned long Replace(const StringW & str, const StringW & replace, unsigned long pos);

	unsigned long ReplaceAll(const WCHAR * str, const WCHAR * replace);
	unsigned long ReplaceAll(const StringW & str, const StringW & replace);

	StringW substr(unsigned long pos, unsigned long lenght = 0) const;
	unsigned int Delete(unsigned long pos, unsigned long lenght);

	StringW trim();

	const WCHAR * c_str() const;

	void Reserve(int length);
	void AppendReserve(int length);

	int		ToInt() const;
	long	ToLongInt() const;
	unsigned long	ToUnsLongInt() const;
	double	ToDouble() const;
	bool	ToBool() const;

	operator String() const;

protected:
	WCHAR * string;
};

/*bool operator<(const StringW & a, const StringW & b);

StringW operator+(const WCHAR * a, const StringW & b);
StringW operator+(const StringW & a, const WCHAR * b);*/

#endif
