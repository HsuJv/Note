// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include	"targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�: 
#include	<windows.h>


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include    <cstdio>
#include    <ctype.h>
#include    <ctime>
#include	<iostream>

using namespace std;


#ifdef PEVIEWER_EXPORTS
#define PEVEIWER_API __declspec(dllexport)
#else
#define PEVIEWER_API __declspec(dllimport)
#endif // PEVIEWER_EXPORTS