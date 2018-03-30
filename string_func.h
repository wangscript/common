
/******************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017
See the license in LICENSE
******************************************************/

#ifndef STRING_FUNC_H
#define STRING_FUNC_H

#include "string.h"
#include "array.h"
#include <stdarg.h>
#include <iostream>

//! разделяет строку szStr на подстроки на основании разделителя szDelimiter
Array<String> StrExplode(const char *szStr, const char *szDelimiter, bool isAllowEmpty = true);

//! соединение всех строк, между строками вставить szDelimiter
String StrWeld(const char *szDelimiter, const char *szStr1, ...);


//! удаляет в строке szStr (пробельные) символы указанные в szSyms
String StrTrim(const char *szStr, const char *szSyms = " \t\n\r");

//! удаляет в начале строки szStr (пробельные) символы указанные в szSyms
String StrTrimL(const char *szStr, const char *szSyms = " \t\n\r");

//! удаляем в конце строки szStr (пробельные) символы указанные в szSyms
String StrTrimR(const char *szStr, const char *szSyms = " \t\n\r");

//##########################################################################

//! поиск в szStr подстроки szFinder с позиции iPos
int StrFind(const char *szStr, const char *szFinder, int iPos = 0);

//! поиск последнего вхождения строки szFinder в szStr
int StrFindLast(const char *szStr, const char *szFinder);

//! поиск в szStr подстроки szFinder с позиции iPos, без учета регистра
int StrFindI(const char *szStr, const char *szFinder, int iPos = 0);

//! поиск последнего вхождения строки szFinder в szStr, без учета регистра
int StrFindILast(const char *szStr, const char *szFinder);


//! вырезает из строки szStr подстроку начиная с iStart и размером iLen, если iLen < 0 вырезает в обратном направлении, если iLen == 0 вырезает до конца строки
String StrSubstr(const char *szStr, int iStart, int iLen=0);

//! возвращает количество вхождений строки szFinder в строку szStr
int StrSubstrCount(const char *szStr, const char *szFinder);

//! возвращает количество вхождений строки szFinder в строку szStr, без учета регистра
int StrSubstrICount(const char *szStr, const char *szFinder);





//! преобразует строку в нижний регистр
String StrToLower(const char *szStr);

//! преобразует строку в верхний регистр
String StrToUpper(const char *szStr);


#endif