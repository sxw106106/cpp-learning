#ifndef __UTIL_H
#define __UTIL_H
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

void UTIL_LogPrint( const char *format, ... );

bool UTIL_CheckFile( const char *szFile );
void UTIL_MakeFile( const char *szFile, string strContents );
void UTIL_MakeFile( const char *szFile, string strContents, bool Cover );
void UTIL_DeleteFile( const char *szFile );
void UTIL_MoveFile( const char *szFile, const char *szDest ,bool Cover = false );
void UTIL_CopyFile( const char *szFile, const char *szDest ,bool Cover = false);
string UTIL_ReadFile( const char *szFile );

string UTIL_GetLocalTimeString();
void CreateDir(const char *DirPath);

string UTIL_GetFilePathFromPath(const char *szFilePath);
string UTIL_GetFileNameFromPath(const char *szFilePath);
int  splitString(const string & strSrc, const std::string& strDelims, vector<string>& strDest) ;
string TrimString(string StrToTrim , string StrSplit=" ");
															//截取字符串前后的空格

#endif