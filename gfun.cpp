#include "stdafx.h"
#include "gfun.h"

LPDIRECTDRAW7			g_pDirectDraw7=NULL;				                       	//用于预览的DirectDraw对象
LPDIRECTDRAWSURFACE7	g_pPrimarySurface=NULL;	
LPDIRECTDRAWCLIPPER	    g_pClipper=NULL;
CRITICAL_SECTION		g_csClipper;

int g_nSysLang;

CRITICAL_SECTION g_csDecInit;

char *GetAppPath(char *AppPath,int nSize)
{
	int i;
	memset(AppPath,0,nSize);
	GetModuleFileName(NULL,AppPath,nSize);
	for (i = strlen(AppPath) + 1; i >= 0; i --)
	{
		if (AppPath[i] == '\\')
		{
			break;
		}
	}
	AppPath[i] = 0;
	return AppPath;
}

void AddSecondToTime(int nSecond,SYSTEMTIME const &TimeInput,SYSTEMTIME &TimeOutput)
{
	int nTimeCalculate;
	nTimeCalculate=TimeInput.wHour*3600+TimeInput.wMinute*60+TimeInput.wSecond;
	nTimeCalculate+=nSecond;
	TimeOutput.wHour=nTimeCalculate/3600;
	TimeOutput.wMinute=nTimeCalculate%3600/60;
	TimeOutput.wSecond=nTimeCalculate%60;
}

bool SearchByAttr_int(TiXmlElement * rootElement,char *sAttr,int nValue,TiXmlElement **ElementOut)
{
	TiXmlElement * ElementTemp = rootElement;
	TiXmlElement * ElementOld;
	TiXmlElement * childElement;
	do 
	{
		int nId ;
		char *s;
		s = NULL;
		s = (char *)ElementTemp->Attribute(sAttr,&nId);
		if (s)
		{
			if (nId == nValue)
			{
				*ElementOut = ElementTemp;
				return true;
			}
		}
		if ((childElement = ElementTemp->FirstChildElement()))
		{
			if (SearchByAttr_int(childElement,sAttr,nValue,ElementOut))
			{
				return true;
			}
		}
		ElementOld = ElementTemp;
		ElementTemp = ElementTemp->NextSiblingElement();
	} while (ElementTemp != ElementOld && ElementTemp != NULL);
	return false;
}

bool IsThereAttr(TiXmlElement * rootElement,char *sAttr,char *sValue)
{
	TiXmlElement * ElementTemp = rootElement;
	TiXmlElement * ElementOld;
	TiXmlElement * childElement;
	char *tmp;
	do 
	{
		tmp=(char *)ElementTemp->Attribute(sAttr);
		if (sValue!=NULL)
		{
			if (!strcmp(tmp,sValue))
			{
				return true;
			}
		}
		if ((childElement = ElementTemp->FirstChildElement()))
		{
			if (IsThereAttr(childElement,sAttr,sValue))
			{
				return true;
			}
		}
		ElementOld = ElementTemp;
		ElementTemp = ElementTemp->NextSiblingElement();
	} while (ElementTemp != ElementOld && ElementTemp != NULL);
	return false;
}

bool SearchByAttr_char(TiXmlElement * rootElement,char *sAttr,char *nValue,TiXmlElement **ElementOut)
{
	TiXmlElement * ElementTemp = rootElement;
	TiXmlElement * ElementOld;
	TiXmlElement * childElement;
	do 
	{
		char tmp[1024];
		memset(tmp, 0, sizeof(tmp));
		strcpy(tmp,ElementTemp->Attribute(sAttr));
		if (!strcmp(tmp,nValue))
		{
			*ElementOut = ElementTemp;
			return true;
		}
		if ((childElement = ElementTemp->FirstChildElement()))
		{
			if (SearchByAttr_char(childElement,sAttr,nValue,ElementOut))
			{
				return true;
			}
		}
		ElementOld = ElementTemp;
		ElementTemp = ElementTemp->NextSiblingElement();
	} while (ElementTemp != ElementOld && ElementTemp != NULL);
	return false;
}

bool SearchByAttr(TiXmlElement * RootElement, char *sAttr, TiXmlElement** XmlElementOut)
{	
	TiXmlElement * ElementTemp = RootElement;
	TiXmlElement * ElementOld;
	TiXmlElement * childElement;
	do 
	{
		//	AfxMessageBox(ElementTemp->Value());
		if (!strcmp(ElementTemp->Value() , sAttr))
		{
			*XmlElementOut = ElementTemp;
			return true;
		}	
		if ((childElement = ElementTemp->FirstChildElement()))
		{
			if (SearchByAttr(childElement,sAttr,XmlElementOut))
			{
				return true;
			}
		}
		ElementOld = ElementTemp;
		ElementTemp = ElementTemp->NextSiblingElement();
	}
	while (ElementTemp != ElementOld && ElementTemp != NULL);
	return false;
}

void GetLangText(char *sSeg,char *sKey,char *sBuffer,int nBufferSize)
{
	char sAppPath[1024] = {0};
	GetAppPath(sAppPath,sizeof(sAppPath));

	char sLangSeg[16] = {0};
	char sLang[16] = {0};
	sprintf(sLang,"lang%d",g_nSysLang);
	GetMainSetText("LANG",sLang,sLangSeg,sizeof(sLangSeg));

	char sDir[16] = {0};
	GetMainSetText(sLangSeg,"dir",sDir,sizeof(sDir));
	
	char sLangIniFile[1024];
	memset(sLangIniFile,0,sizeof(sLangIniFile));
	sprintf(sLangIniFile,"%s\\LANG\\%s\\LANG.INI",sAppPath,sDir);

	GetPrivateProfileString(sSeg,sKey,"",sBuffer,nBufferSize,sLangIniFile);
}

void GetMainSetText(char *sSeg,char *sKey,char *sBuffer,int nBufferSize)
{
	char sAppPath[1024] = {0};
	GetAppPath(sAppPath,sizeof(sAppPath));

	WCHAR wsAppPath[1024] = {0};
	MultiByteToWideChar(CP_ACP,0,sAppPath,-1,wsAppPath,1024);

	WCHAR wsSeg[1024] = {0};
	MultiByteToWideChar(CP_ACP,0,sSeg,-1,wsSeg,1024);

	WCHAR wsKey[1024] = {0};
	MultiByteToWideChar(CP_ACP,0,sKey,-1,wsKey,1024);
	
	WCHAR wsMainIniFile[1024] = {0};
	swprintf(wsMainIniFile,L"%s\\MAINSET.INI",wsAppPath);
			
	WCHAR wsBuffer[1024] = {0};
	GetPrivateProfileStringW(wsSeg,wsKey,L"",wsBuffer,1024,wsMainIniFile);

	WideCharToMultiByte(CP_ACP,0,wsBuffer,-1,sBuffer,nBufferSize,"",NULL);
}

bool Domain2Ip(char *DomainName,char *ip)
{
	WSADATA wsaData;
	int nRet = WSAStartup(MAKEWORD(2,2),&wsaData);
	if (nRet != 0)
	{
		return false;
	}
	
	HOSTENT *host_entry;
	host_entry = gethostbyname(DomainName);
	
	if (NULL != host_entry)
	{
		sprintf(ip,"%d.%d.%d.%d", 
			(host_entry->h_addr_list[0][0]&0xff), 
			(host_entry->h_addr_list[0][1]&0xff), 
			(host_entry->h_addr_list[0][2]&0xff), 
			(host_entry->h_addr_list[0][3]&0xff)); 
	}
	else
	{
		WSACleanup();
		return false;
	}
	
	WSACleanup();
	return true;
}

int Time2Second(SYSTEMTIME t)
{
	return (t.wHour * 3600 + t.wMinute * 60 + t.wSecond);
}

int CompairTime(SYSTEMTIME t1,SYSTEMTIME t2)
{
	return (Time2Second(t1) - Time2Second(t2));
}

void GetElement( TiXmlElement * rootElement, char *sDevName, char *sChlNum, CString &sOut ) 
{
	if ( rootElement )
	{
		CString dev = rootElement->Attribute("type");
		CString name = rootElement->Attribute("name");
		if (  "dev" == /*rootElement->Attribute("type")*/dev )
		{
			if ( sDevName == name )
			{
				CString sChannels = rootElement->Attribute("channels");
				CString sChl;
				TiXmlElement *child = rootElement->FirstChildElement();
				for ( int i=0; i< atoi(sChannels); i++ )
				{
					sChl = child->Attribute("chl");
					if ( sChlNum == sChl)
					{
						sOut = child->Attribute("name");
					}
					child = child->NextSiblingElement();
				}
			}
		}
	}

	TiXmlElement * FirstChild = rootElement->FirstChildElement();
	while ( FirstChild )
	{
		GetElement( FirstChild, sDevName, sChlNum, sOut );
		FirstChild = FirstChild->NextSiblingElement();
	}
}


CString GetChlName(char *sDevName /* = NULL */, int nChlNum)
{
	if ( nChlNum == -1 )
	{
		return "-1";	//Channel number input error.
	}

	if ( 0 == strlen(sDevName) )
	{
		return "-2";	//devname input error
	}
	else
	{
		//get channel name by ip & channel number
		//get channel name from area.xml
		char sAppPath[1024];
		memset(sAppPath,0,sizeof(sAppPath));
		GetAppPath(sAppPath,sizeof(sAppPath));
		
		CString sAreaXml;
		sAreaXml.Format("%s\\area.xml",sAppPath);
		char * sAppPath_area = sAreaXml.GetBuffer(0);
		
		TiXmlDocument m_areaDoc;
		m_areaDoc.LoadFile(sAppPath_area, TIXML_DEFAULT_ENCODING);
		
		char sChlNum[16];
		memset( sChlNum, 0, sizeof(sChlNum) );
//		char *sChlName;
		sprintf( sChlNum, "%d", nChlNum);

		TiXmlElement * rootElement = m_areaDoc.RootElement();
		TiXmlElement * Firstchild = rootElement->FirstChildElement();

//		char *strChlName;
		//memset(strChlName,0,sizeof(strChlName));
		CString reslut;
		GetElement(rootElement, sDevName, sChlNum, reslut);
		return reslut;
	}
}

TraversalTask * StartTask(TiXmlElement * root,char *sAttr,char* sValue)
{
	char *sAttrTemp = (char *)malloc(strlen(sAttr) + 1);
	char *sValueTemp = (char *)malloc(strlen(sValue) + 1);
	memset(sAttrTemp,0,strlen(sAttr) + 1);
	memset(sValueTemp,0,strlen(sValue) + 1);
	strcpy(sAttrTemp,sAttr);
	strcpy(sValueTemp,sValue);

	TraversalTask * newTask = (TraversalTask *)malloc(sizeof(TraversalTask));
	memset(newTask,0,sizeof(TraversalTask));

	newTask->rootElement = root;
	newTask->sAttr = sAttrTemp;
	newTask->sValue = sValueTemp;
	newTask->find = NULL;

	return newTask;

}

void CloseTask(TraversalTask * task)
{
	if (NULL == task)
	{
		return;
	}

	if (task->sValue != NULL)
	{
		free(task->sValue);
		task->sValue = NULL;
	}

	if (task->sAttr != NULL)
	{
		free(task->sAttr);
		task->sAttr = NULL;
	}

	free(task);
}

bool SearchT(TiXmlElement * root,TraversalTask * task)
{
	TiXmlElement * ElementTemp = root;
	TiXmlElement * ElementOld;
	TiXmlElement * childElement;
	do 
	{
		// ToDo: 这个节点应该做的事
		
		if (!strcmp(task->sValue,ElementTemp->Attribute(task->sAttr)))
		{
			if (ElementTemp != task->find)
			{
				task->find = ElementTemp;
				return true;
			}
		}
		
		if ((childElement = ElementTemp->FirstChildElement()))
		{
			if (SearchT(childElement,task))
			{
				return true;
			}
		}
		ElementOld = ElementTemp;
		ElementTemp = ElementTemp->NextSiblingElement();
	} while (ElementTemp != ElementOld && ElementTemp != NULL);
	return false;
}

TiXmlElement * FindNextElement(TraversalTask *task)
{
	if (SearchT(task->rootElement,task))
	{
		return task->find;
	}
	else
	{
		return NULL;
	}
}

SOCKET InitSocket()
{
	WSAData wsaData;
	int nRet = WSAStartup(MAKEWORD(2,2),&wsaData);
	if (0 != nRet)
	{
		return SOCKET_ERROR;
	}
	
	SOCKET s;
	s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (INVALID_SOCKET == s)
	{
		WSACleanup();
		return SOCKET_ERROR;
	}
	
	int nTimeOut = 12000;
	::setsockopt(s,SOL_SOCKET,SO_RCVTIMEO,(char *)&nTimeOut,sizeof(nTimeOut));
	nTimeOut = 12000;
	::setsockopt(s,SOL_SOCKET,SO_SNDTIMEO,(char *)&nTimeOut,sizeof(nTimeOut));
	
	return s;
}

int HttpConnet(SOCKET s,char *sAddress,unsigned short nPort,bool *bExitFlat,unsigned int nTimeOut)
{
	unsigned long ul = 1;
	ioctlsocket(s, FIONBIO, (unsigned long*)&ul);
	
	char sIp[32];
	memset(sIp,0,sizeof(sIp));
	Domain2Ip(sAddress,sIp);
	SOCKADDR_IN addrSev;
	addrSev.sin_family=AF_INET;
	addrSev.sin_addr.S_un.S_addr=inet_addr(sIp);
	addrSev.sin_port=htons(nPort);
	
	connect(s,(const struct sockaddr *)&addrSev,sizeof(addrSev));
	
	fd_set WriteSet;
	struct timeval to;
	
	bool bConnected = false;
	
	int nSelectCount = 0;
	while (nSelectCount < int(nTimeOut * 2) && !(*bExitFlat))
	{
		FD_ZERO(&WriteSet);
		FD_SET(s,&WriteSet);
		to.tv_sec = 0;
		to.tv_usec = 500000;
		if (select(0,NULL,&WriteSet,NULL,&to) > 0)
		{
			int nError;
			int nOptLen = sizeof(nError);
			getsockopt(s, SOL_SOCKET, SO_ERROR, (char *)&nError, &nOptLen);
			if (0 == nError)
			{// 已连接上
				bConnected = true;
				break;
			}
			else
			{// 尚未连接
				nSelectCount ++;
			}
		}
		else
		{
			nSelectCount ++;
		}
	}
	
	if (!bConnected)
	{
		closesocket(s);	
		WSACleanup();
		return -1;
	}
	
	ul= 0 ;
	ioctlsocket(s, FIONBIO, (unsigned long*)&ul);
	
	return 0;
	
}

int ParseSendData(char * sHostName,unsigned int nHostPort,
				  char *pSendData,int nCount,
				  char *pOutput,unsigned int nOutputBufferSize)
{
	
	int nHeadLen = 0;
	char sHead[10240] = {0};
	
	// Action ,Connection segment & Content-Length Segment
	char httpheader[] = {
		"GET /cgi-bin/gw2.cgi?f=j&xml="
	};

	char httpend[] = {
		" HTTP/1.1\r\n"
		"Connection:close\r\n"
		"\r\n"
	};

	sprintf(sHead,"%s%s%s",httpheader,pSendData,httpend);

	// Start to Output
	nHeadLen = strlen(sHead);
	
	// Output header
	if ((int)nOutputBufferSize < nHeadLen)
	{
		return -1;
	}
	strcpy(pOutput,sHead);
	
	return strlen(pOutput);
}

int HttpClose(SOCKET s)
{
	closesocket(s);
	WSACleanup();
	return 0;
}

int parseData(char str[])
{
	int i=0,j=0;
	if (str==NULL)
	{
		return 0;
	}
	while(str[i]!='\0')
	{
		if (str[i]=='<')
		{
			if (!strncmp(str + i + 1,"juan",strlen("juan")))
			{
				break;
			}
		}
		i++;
	}
	while (str[i]!='\0')
	{
		if (!strncmp(str + i,"\\\"",strlen("\\\"")))
		{
			str[j++] = '\"';
			i += 2;
		}
		else if (!strncmp(str + i,"</juan>",strlen("</juan>")))
		{
			strcpy(str + j,"</juan>");
			j += strlen("</juan>");
			break;
		}
		else
		{
			str[j++]=str[i];
			i++;
		}
	}
	str[j]='\0';
	return 0;
}

char * urlencode(char const *s)
{
	int nRetSize = strlen(s) * 3 + 1;
	char *pRet = (char *)malloc(nRetSize);
    unsigned char hexchars[] = "0123456789ABCDEF";

	int i = 0,j = 0;
	while (s[i] != '\0')
	{
		if (( s[i] >= 'A' && s[i] <= 'Z' ) ||
			( s[i] >= 'a' && s[i] <= 'z' ) ||
			( s[i] >= '0' && s[i] <= '9' ) ||
			'.' == s[i] ||
			'-' == s[i] ||
			'_' == s[i]
			)
		{
			pRet[j++] = s[i];
		}
		else
		{
			pRet[j++] = '%';
			pRet[j++] = hexchars[( s[i] >> 4 & 0x0f )];
			pRet[j++] = hexchars[ s[i] & 0x0f ];
		}
		i ++;
	}
	pRet[j] = '\0';

	return pRet;
	
}

int DdrawInit(HWND hWnd)
{   
	HRESULT hr;
	
	
	//创建DDraw对象
	hr = DirectDrawCreateEx(NULL,(LPVOID *)&g_pDirectDraw7,IID_IDirectDraw7,NULL);
	if (FAILED(hr))
	{
		g_pDirectDraw7 = NULL;
		return -1;
	}
	
	//设置协作等级，执行成功，返回DD_OK
	hr = g_pDirectDraw7->SetCooperativeLevel(NULL,DDSCL_NORMAL);
	if (FAILED(hr))
	{
		g_pDirectDraw7->Release();
		g_pDirectDraw7 = NULL;
		return -1;
	}
	
	//创建裁减器
	hr = g_pDirectDraw7->CreateClipper(0,&g_pClipper,NULL);
	if (FAILED(hr))
	{
		g_pDirectDraw7->Release();
		g_pDirectDraw7 = NULL;
		return -1;
	}
	
	InitializeCriticalSection(&g_csClipper);
	
	//创建主页面
	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd,sizeof(DDSURFACEDESC2));
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	
	hr = g_pDirectDraw7->CreateSurface(&ddsd,&g_pPrimarySurface,NULL);
	if (FAILED(hr))
	{
		g_pClipper->Release();
		g_pClipper = NULL;
		g_pDirectDraw7->Release();
		g_pDirectDraw7 = NULL;
		g_pPrimarySurface = NULL;
		return -1;
	}
	
	
	
	//加载裁剪器到主页面
	hr = g_pClipper->SetHWnd(NULL,hWnd);
	if (FAILED(hr))
	{
		g_pClipper->Release();
		g_pClipper = NULL;
		g_pPrimarySurface->Release();
		g_pPrimarySurface = NULL;
		g_pDirectDraw7->Release();
		g_pDirectDraw7 = NULL;
		return -1;
	}
	//将剪裁器对象连接到主表面 
	hr = g_pPrimarySurface->SetClipper(g_pClipper);
	if (FAILED(hr))
	{
		g_pClipper->Release();
		g_pClipper = NULL;
		g_pPrimarySurface->Release();
		g_pPrimarySurface = NULL;
		g_pDirectDraw7->Release();
		g_pDirectDraw7 = NULL;
		return -1;
	}
	
	
	
	return 0;
}

void DdrawDeinit()
{
	if (g_pClipper)
	{
		g_pClipper->Release();
		g_pClipper = NULL;
	}
	if (g_pPrimarySurface)
	{	
		g_pPrimarySurface->Release();
		g_pPrimarySurface = NULL;
	}
	if (g_pDirectDraw7)
	{
		g_pDirectDraw7->Release();
		g_pDirectDraw7 = NULL;
	}

}

CTime time_t_to_ctime(time_t _timet)
{
	TIME_ZONE_INFORMATION tzi;
	GetSystemTime(&tzi.StandardDate);
	GetTimeZoneInformation(&tzi);
	
	CTime time(_timet + (tzi.Bias * 60));
//	CTime time(_timet);	
	return time;
}