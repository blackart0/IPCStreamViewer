#pragma once
#include <DDRAW.H>
#include "tinyxml/tinyxml.h"

#include <WINSOCK2.H>
#pragma comment(lib,"ws2_32.lib")

#include <Shlwapi.h>
#pragma comment(lib,"Shlwapi.lib")

typedef struct _tagTraversalTask{
	TiXmlElement * rootElement;
	char *sAttr;
	char *sValue;
	TiXmlElement * find;
}TraversalTask,*lpTraversalTask;

extern int g_nSysLang;

extern CRITICAL_SECTION g_csDecInit;

extern char *          GetAppPath(char *AppPath,int nSize);

extern bool            SearchByAttr_int(TiXmlElement * rootElement,char *sAttr,int nValue,TiXmlElement **ElementOut);

extern bool            IsThereAttr(TiXmlElement * rootElement,char *sAttr,char *sValue);

extern void            GetLangText(char *sSeg,char *sKey,char *sBuffer,int nBufferSize);

extern bool            Domain2Ip(char *DomainName,char *ip);

extern bool			   SearchByAttr(TiXmlElement * rootElement,char *sAttr,TiXmlElement **ElementOut);

extern bool            SearchByAttr_char(TiXmlElement * rootElement,char *sAttr,char *nValue,TiXmlElement **ElementOut);

extern void            GetMainSetText(char *sSeg,char *sKey,char *sBuffer,int nBufferSize);

extern int             Time2Second(SYSTEMTIME t);

extern int             CompairTime(SYSTEMTIME t1,SYSTEMTIME t2);

extern void            AddSecondToTime(int nSecond,SYSTEMTIME const &TimeInput,SYSTEMTIME &TimeOutput);

extern CString         GetChlName(char *sDevName = NULL, int nChlNum = -1); //yqw+£ºÎ´Íê³É

extern TraversalTask * StartTask(TiXmlElement * root,char *sAttr,char* sValue);

extern void            CloseTask(TraversalTask * task);

extern TiXmlElement *  FindNextElement(TraversalTask *task);

extern SOCKET          InitSocket();

extern int             HttpConnet(SOCKET s,char *sAddress,unsigned short nPort,bool *bExitFlat,unsigned int nTimeOut);

extern int             ParseSendData(char * sHostName,unsigned int nHostPort,char *pSendData,int nCount,char *pOutput,unsigned int nOutputBufferSize);

extern int             HttpClose(SOCKET s);

extern int             parseData(char str[]);

extern char *          urlencode(char const *s);

extern int             DdrawInit(HWND hWnd);

extern void			   DdrawDeinit();
extern CTime		   time_t_to_ctime(time_t _timet);





