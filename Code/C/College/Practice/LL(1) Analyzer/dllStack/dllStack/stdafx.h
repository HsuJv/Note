// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�: 
#include <windows.h>



// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include    <cstdio>
#include    <ctype.h>
#include	<iostream>

using namespace std;


#ifdef DLLSTACK_EXPORTS
#define DLLSTACKAPI __declspec(dllexport)
#else
#define DLLSTACKAPI __declspec(dllimport)
#endif // PEVIEWER_EXPORT