#ifndef		__USERINFO_HEAD_FILE_3X58R46__
#define		__USERINFO_HEAD_FILE_3X58R46__

#define MAX_USERNAME_LEN	(20)
#define MAX_PASSWORD_LEN	(20)

typedef	enum
{
	USER_AUTH_NULL = -1,
	USER_AUTH_SYSTEM_SETUP = 0,
	USER_AUTH_SYSTEM_UPGRADE,
	USER_AUTH_HDD_FORMAT,
	USER_AUTH_FACTORY_SETTING,
	USER_AUTH_ENCODE_SETUP,
	USER_AUTH_MOTION_SETUP,
	USER_AUTH_PTZ_SETUP,
	USER_AUTH_VIDEO_SEARCH,
	USER_AUTH_RECORD_SCHEDULE,
	USER_AUTH_SENSOR_SETUP,
	USER_AUTH_SCREEN_SETUP,
	USER_AUTH_NETWORK_SETUP,
	USER_AUTH_NETWORK_VIEW,
	USER_AUTH_CNT,
}USER_AUTH_TYPE;

#define CHANNEL1_BIT	0x1
#define CHANNEL2_BIT	0x2
#define CHANNEL3_BIT	0x4
#define CHANNEL4_BIT	0x8
#define CHANNEL5_BIT	0x10
#define CHANNEL6_BIT	0x20
#define CHANNEL7_BIT	0x40
#define CHANNEL8_BIT	0x80
#define CHANNEL9_BIT	0x100
#define CHANNEL10_BIT	0x200
#define CHANNEL11_BIT	0x400
#define CHANNEL12_BIT	0x800
#define CHANNEL13_BIT	0x1000
#define CHANNEL14_BIT	0x2000
#define CHANNEL15_BIT	0x4000
#define CHANNEL16_BIT	0x8000

#define IS_CHANNEL_SET(x,chl)		((x) & (1 << (chl)))
#define SET_CHANNEL(x,chl)			((x) | (1 << (chl)))
#define CLR_CHANNEL(x,chl)			((x) & (~(1 << (chl))))


enum{
	CMDPAC_TYPE_USERVRF = 0,
	CMDPAC_TYPE_CHLREQ,
	CMDPAC_TYPE_PTZ,
	CMDPAC_TYPE_USERVRF_B,
	CMDPAC_TYPE_CHLREQ_B,
	CMDPAC_TYPE_SYSFILEREQ,
	CMDPAC_TYPE_SYSFILEPOST,

	CMDPAC_TYPE_REQTIMELIST,
	CMDPAC_TYPE_RECPLAY,
	CMDPAC_TYPE_RECPAUSE,
	CMDPAC_TYPE_RECCONTINUE,
	CMDPAC_TYPE_RECSTOP,
	CMDPAC_TYPE_POSTRECLIST,
	CMDPAC_TYPE_POSTRECDATA,

	CMDPAC_TYPE_CNT,
};

#define INITCMDPACK(pac,type)	{\
		memset(&(pac),0,sizeof((pac)));\
		(pac).cHead[0]=(type);\
	}

#define CMDPAC_SIZE_USERVRF			(4 + sizeof(UserVerify))
#define CMDPAC_SIZE_CHLREQ			(4)
#define CMDPAC_SIZE_PTZ				(4 + sizeof(PtzCmd))
#define CMDPAC_SIZE_USERVRF_B		(4 + sizeof(UserVerifyRst))
#define CMDPAC_SIZE_CHLREQ_B		(4 + sizeof(ChlReqRst))
#define CMDPAC_SIZE_SYSFILEREQ		(4)
#define CMDPAC_SIZE_SYSFILEPOST		(4 + sizeof(SysfilePost))

typedef enum{
	CMD_PTZ_UP = 0,
	CMD_PTZ_DOWN,
	CMD_PTZ_LEFT,
	CMD_PTZ_RIGHT,
	CMD_PTZ_AUTO,
	CMD_PTZ_FOCUSFAR,
	CMD_PTZ_FOCUSNEAR,
	CMD_PTZ_ZOOMOUT,
	CMD_PTZ_ZOOMIN,
	CMD_PTZ_IRISOPEN,
	CMD_PTZ_IRISCLOSE,
	CMD_PTZ_AUX1,
	CMD_PTZ_AUX2,

	CMD_PTZ_CNT,
}REMOTE_PTZ_CMD;

#define CMD_REMOTE_SYSFILE		254

typedef struct _tagFileSendHead{
	unsigned int		nFileTicket;
	unsigned int		nEof;
	unsigned int		MD;
	unsigned char		pData[1];
}FileSendHead,*lpFileSendHead;


typedef struct _tagUserVerify{
	unsigned char cUserName[MAX_USERNAME_LEN];
	unsigned char cPassWord[MAX_PASSWORD_LEN];
}UserVerify,*lpUserVerify;

typedef struct _tagUserVerifyRst{
	bool	bVerify;
	unsigned char Reverse[3];
	bool	Auth[USER_AUTH_CNT];
}UserVerifyRst,*lpUserVerifyRst;

typedef struct _tagChlReqRst{
	int		nChannelNum;
}ChlReqRst,*lpChlReqRst;

typedef struct _tagPtzCmd{
	int		nChannel:8;
	int		nCmd:8;
	int		bStop:8;
	int		nParam2:8;
}PtzCmd,*lpPtzCmd;

typedef struct _tagSysfilePost{
	int		nFileLen;
	char	FileData[1];
}SysfilePost,*lpSysfilePost;

typedef struct _tagReqTimeList{
	unsigned int nChls;
	unsigned int nTypes;
	struct	_tagTime{
		unsigned int nHour:8;
		unsigned int nMinute:8;
		unsigned int nSecond:8;
		unsigned int Reserved:8;
	}starttime,endtime;
	struct _tagDate{
		unsigned int nYear:16;
		unsigned int nMonth:8;
		unsigned int nDay:8;
	}SearchDate;
}ReqTimeList,*lpReqTimeList;

typedef struct _tagTimeListNode{
	int nChl;
	int nType;
	struct	_tagTime{
		unsigned int nHour:8;
		unsigned int nMinute:8;
		unsigned int nSecond:8;
		unsigned int Reserved:8;
	}starttime,endtime;
}TimeListNode,*lpTimeListNode;

typedef struct _tagPostTimeList{
	unsigned int	nSegNum;
	TimeListNode TimeNode[1];
}PostTimeList,*lpPostTimeList;

typedef struct _tagStartPlayRec{
	unsigned int nChls;
	unsigned int nTypes;
	unsigned int ClientId;
	struct	_tagTime{
		unsigned int nHour:8;
		unsigned int nMinute:8;
		unsigned int nSecond:8;
		unsigned int Reserved:8;
	}starttime;
}StartPlayRec,*lpStartPlayRec;

typedef struct _tagCmdFormakt{
	char	cHead[4];
	union{
		UserVerifyRst	userverifyrst;
		UserVerify		userverifyinfo;
		ChlReqRst		channelrequire;
		PtzCmd			ptzcommand;
		SysfilePost		sysfilepost;
		ReqTimeList		reqtimelist;
		PostTimeList	posttimelist;
		StartPlayRec	startplayrec;
	};
}CmdFormat,*lpCmdFormat;

#endif
