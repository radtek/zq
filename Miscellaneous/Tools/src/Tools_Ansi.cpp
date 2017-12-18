// Tools_Ansi.cpp: implementation of the CTools_Ansi class.
//
//	Description	:1. Defines tool functions 
//	Version		:1.0
//	Date		:2008-4-30
//	Author		:lzq
//				 Copyright (C), 2008-2028
//	
//	History		:
//
//////////////////////////////////////////////////////////////////////

#include "Tools_Ansi.h"
#include <winsock2.h>       
#include <sys/timeb.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <iostream>											//header file for iostream
using namespace std;										//using of std namespace


#pragma comment(lib, "ws2_32.lib")	


#ifdef WIN32
#pragma unmanaged
#endif 


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTools_Ansi::CTools_Ansi()
{

}

CTools_Ansi::~CTools_Ansi()
{

}




//function		:ReplaceStr
//description	:1. replace substring in string
//				 2. all other function can call this function
//				 3. It's possible that length of Str differ after replacement is finished, so caller must process this case, avoidance memory overflow
//parameters	:Str : pointer of string what is replace
//				 SubStr : pointer of substring that is replaced with
//				 NewSubStr : pointer of substring that is replaced to
void CTools_Ansi::ReplaceStr(char *Str,const char *SubStr,const char *NewSubStr)
{
	int				SubLen,NewSubLen,Len1,Len2;
	char			*pp;

	SubLen=(int)strlen(SubStr);
	NewSubLen=(int)strlen(NewSubStr);
	while(1)
	{
		pp=strstr(Str,SubStr);
		if(!pp) break;
		Len1=(int)strlen(Str);
		Len2=(int)strlen(pp);

		if(Len2>SubLen)
			memmove(pp+NewSubLen,pp+SubLen,Len2-SubLen);
		memcpy(pp,NewSubStr,NewSubLen);
		pp[NewSubLen+Len2-SubLen]=0;
	}
}


//function		:ReplaceStrOnce
//description	:1. replace substring in string
//				 2. only one substring will be replace if there are several substring match it
void CTools_Ansi::ReplaceStrOnce(char *Str,const char *SubStr,const char *NewSubStr)
{
	int				SubLen,NewSubLen,Len1,Len2;
	char			*pp;

	SubLen=(int)strlen(SubStr);
	NewSubLen=(int)strlen(NewSubStr);
	pp=strstr(Str,SubStr);
	if(pp)
	{
		Len1=(int)strlen(Str);
		Len2=(int)strlen(pp);

		if(Len2>SubLen)
			memmove(pp+NewSubLen,pp+SubLen,Len2-SubLen);
		memcpy(pp,NewSubStr,NewSubLen);
		pp[NewSubLen+Len2-SubLen]=0;
	}
}


//	ɾ�����ұߵĿո�
void CTools_Ansi::DeleteStrRightSpace(char *Str)
{
	int i;
	for(i=strlen(Str);i>0;i--)
	{
		if(Str[i-1]==' '||Str[i-1]=='\t') Str[i-1]=0;
		else break;
	}
}

//	ɾ�����ұߵĿո�\t��\r��\n
void CTools_Ansi::DeleteStrRightSpace_10_13(char *Str)
{
	int i;
	for(i=strlen(Str);i>0;i--)
	{
		if(Str[i-1]==' '||Str[i-1]=='\t'||Str[i-1]==10||Str[i-1]==13) Str[i-1]=0;
		else break;
	}
}

//	ɾ������ߵĿո�
void CTools_Ansi::DeleteStrLeftSpace(char *Str)
{
	int			i,iLeft,Len;
	Len=strlen(Str);
	for(iLeft=0;iLeft<Len;iLeft++) if(Str[iLeft]!=' '&&Str[iLeft]!='\t') break;
	if(iLeft>0) 
	{
		for(i=iLeft;i<Len;i++) Str[i-iLeft]=Str[i];
		memset(Str+Len-iLeft,0,iLeft);
	}
}

//	ɾ�����ұߵ�����
void CTools_Ansi::DeleteStrRightDigit(char *Str)
{
	int len=strlen(Str);
	while(len>0&&isdigit((int)Str[len-1])) Str[--len]=0;
}


//	ɾ�������ߵĿո�
void CTools_Ansi::DeleteStrLeftRightSpace(char *Str)
{
	int			i,iLeft,iRight,Len;
	Len=strlen(Str);
	for(iLeft=0;iLeft<Len;iLeft++) if(Str[iLeft]!=' '&&Str[iLeft]!='\t') break;
	for(iRight=Len;iRight>iLeft;iRight--) if(Str[iRight-1]!=' '&&Str[iRight-1]!='\t') break;
	if(iLeft>0) for(i=iLeft;i<iRight;i++) Str[i-iLeft]=Str[i];
	if(Len>iRight-iLeft)
		memset(Str+iRight-iLeft,0,Len-(iRight-iLeft));
}

//	ɾ�������ߵĿո�ͻس����з�
void CTools_Ansi::DeleteStrLeftRightSpace_10_13(char *Str)
{
	int			i,iLeft,iRight,Len;
	Len=strlen(Str);
	for(iLeft=0;iLeft<Len;iLeft++) if(Str[iLeft]!=' '&&Str[iLeft]!='\t'&&Str[iLeft]!=10&&Str[iLeft]!=13) break;
	for(iRight=Len;iRight>iLeft;iRight--) if(Str[iRight-1]!=' '&&Str[iRight-1]!='\t'&&Str[iRight-1]!=10&&Str[iRight-1]!=13) break;
	if(iLeft>0) for(i=iLeft;i<iRight;i++) Str[i-iLeft]=Str[i];
	if(Len>iRight-iLeft)
		memset(Str+iRight-iLeft,0,Len-(iRight-iLeft));
}
string CTools_Ansi::DeleteStrLeftRightSpace_10_13(const string& Str)
{
	int			iLeft,iRight,Len;
    Len=Str.length();
    const char* pStr=Str.c_str();
	for(iLeft=0;iLeft<Len;iLeft++) if(pStr[iLeft]!=' '&&pStr[iLeft]!='\t'&&pStr[iLeft]!=10&&pStr[iLeft]!=13) break;
	for(iRight=Len;iRight>iLeft;iRight--) if(pStr[iRight-1]!=' '&&pStr[iRight-1]!='\t'&&pStr[iRight-1]!=10&&pStr[iRight-1]!=13) break;
    return Str.substr(iLeft,iRight-iLeft);
}

//���˵�˫б����������ע�ͣ������˵���β�Ŀո�Tab���س����з�
string CTools_Ansi::FilterLineComment(const string& Str)
{
    string strRlt;

    //���ÿһ�н��д���
    int len=Str.length();
    const char* pStr=Str.c_str();
    int linestart=0,linelen;
    while(linestart<len)
    {
        linelen=0;
        while(linestart+linelen<len&&pStr[linestart+linelen]!=0x0d&&pStr[linestart+linelen]!=0x0a) linelen++;
        int lineend=0;
        for(;lineend<linelen;lineend++)
        {
            //���˵���ע������
            if(lineend<linelen-1&&pStr[linestart+lineend]=='/'&&pStr[linestart+lineend+1]=='/') break;
            //����˫���Ż����Ű�β�Ĳ���
            if(pStr[linestart+lineend]=='"'||pStr[linestart+lineend]=='\'')
            {
                int lineend2=lineend+1;
                while(lineend2<linelen&&pStr[linestart+lineend2]!=pStr[linestart+lineend]) lineend2++;
                if(lineend2<linelen)
                {
                    lineend=lineend2;
                    continue;
                }
            }
        }
        int off1=0;
        while(off1<linelen&&(pStr[linestart+off1]==' '||pStr[linestart+off1]=='\t')) off1++;
        while(lineend>off1&&(pStr[linestart+lineend-1]==' '||pStr[linestart+lineend-1]=='\t')) lineend--;
        strRlt+=Str.substr(linestart+off1,lineend-off1);
        linestart+=linelen;

        int CRLFCnt=0;
        while(linestart+CRLFCnt<len&&(pStr[linestart+CRLFCnt]==0x0a||pStr[linestart+CRLFCnt]==0x0d)) CRLFCnt++;
        strRlt+=Str.substr(linestart,CRLFCnt);
        linestart+=CRLFCnt;
    }

    return DeleteStrLeftRightSpace_10_13(strRlt);
}


//function		:GetNextDigitOff
//description	:look for offset of the next digit bytes��Len can be empty
int CTools_Ansi::GetNextDigitOff(const char *pStr,int Len,int StartOff)
{
	int				i;
	if(!Len) Len=strlen(pStr);
	i=StartOff;
	while(i<Len&&pStr[i]>='0'&&pStr[i]<='9') i++;
	while(i<Len&&(pStr[i]<'0'||pStr[i]>'9')) i++;
	return i;
}

//function		:GetNextCharOff
//description	:look for offset of the next character bytes, Len can be empty
int CTools_Ansi::GetNextCharOff(char Ch,const char *pStr,int Len,int StartOff)
{
	int				i;
	if(!Len) Len=strlen(pStr);
	for(i=StartOff;i<Len&&pStr[i]!=Ch;i++);
	return i;
}

//function		:GetNextCharOff2
//description	:look for offset of the next two character bytes, Len can be empty
int CTools_Ansi::GetNextCharOff2(char Ch1,char Ch2,const char *pStr,int Len,int StartOff)
{
	int				i;
	if(!Len) Len=strlen(pStr);
	for(i=StartOff;i<Len&&pStr[i]!=Ch1&&pStr[i]!=Ch2;i++);
	return i;
}

//function		:GetNextValidOff
//description	:look for offset of the next char that is't space��tab��\r��\n, Len can be empty
int CTools_Ansi::GetNextValidOff(const char *pStr,int Len,int StartOff)
{
	int				i;
	char			ich;
	if(!Len) Len=strlen(pStr);
	for(i=StartOff;i<Len;i++)
	{
		ich=pStr[i];
		if(ich!=' '&&ich!='\t'&&ich!=10&&ich!=13) return i;
	}
	return Len;
}


//function		:GetNextInvalidOff
//description	:look for offset of the next char that is space��tab��\r��\n, Len can be empty
int CTools_Ansi::GetNextInvalidOff(const char *pStr,int Len,int StartOff)
{
	int				i;
	char			ich;
	if(!Len) Len=strlen(pStr);
	for(i=StartOff;i<Len;i++)
	{
		ich=pStr[i];
		if(ich==' '||ich=='\t'||ich==10||ich==13) return i;
	}
	return Len;
}


//function		:GetPrevInvalidOff
//description	:��ǰ�������ҵ�һ����һ���ַ���Valid��λ��
int CTools_Ansi::GetPrevInvalidOff(const char *pStr,int StartOff,int MinOff)
{
	int				i;
	char			ich;
	for(i=StartOff;i>0&&i>MinOff;i--)
	{
		ich=pStr[i-1];
		if(ich!=' '&&ich!='\t'&&ich!=10&&ich!=13) return i;
	}
	return i;
}


//function		:GetNextCharOrInvalidOff
//description	:look for offset of the next char that is special character, or space��tab��\r��\n, Len can be empty
int CTools_Ansi::GetNextCharOrInvalidOff(char Ch,const char *pStr,int Len,int StartOff)
{
	int				i;
	char			ich;
	if(!Len) Len=strlen(pStr);
	for(i=StartOff;i<Len;i++)
	{
		ich=pStr[i];
		if(ich==Ch||ich==' '||ich=='\t'||ich==10||ich==13) return i;
	}
	return Len;
}


//function		:GetNextFieldOff
//description	:look for offset of the next field, seperated by Seperator��Len can be empty
int CTools_Ansi::GetNextFieldOff(const char *pStr,int Len,int StartOff,char Seperator1,char Seperator2,char Seperator3,char Seperator4)
{
	int				i;
	if(!Len) Len=strlen(pStr);
	i=StartOff;
	while(i<Len&&pStr[i]!=Seperator1&&pStr[i]!=Seperator2&&pStr[i]!=Seperator3&&pStr[i]!=Seperator4) i++;
	while(i<Len&&(pStr[i]==Seperator1||pStr[i]==Seperator2||pStr[i]==Seperator3||pStr[i]==Seperator4)) i++;
	return i;
}

//ȡָ��λ�ÿ�ʼ��ָ�������֮ǰ���ַ��������˵�ǰ�ĵĿո�tab�ͼ����
BOOL CTools_Ansi::GetCurField(const char *pStr,int Len,int StartOff,int *RltFieldStart,int *RltFieldEnd,char Seperator1,char Seperator2,char Seperator3,char Seperator4)
{
	int				i;
	*RltFieldStart=0;
	*RltFieldEnd=0;
	if(!Len) Len=strlen(pStr);
	i=StartOff;
	while(i<Len&&(pStr[i]==' '||pStr[i]=='\t'||pStr[i]==Seperator1||pStr[i]==Seperator2||pStr[i]==Seperator3||pStr[i]==Seperator4)) i++;
	*RltFieldStart=i;
	while(i<Len&&pStr[i]!=Seperator1&&pStr[i]!=Seperator2&&pStr[i]!=Seperator3&&pStr[i]!=Seperator4) i++;
	while(i>0&&(pStr[i-1]==' '||pStr[i-1]=='\t')) i--;
	if(i<(*RltFieldStart)) i=(*RltFieldStart);
	*RltFieldEnd=i;
	if((*RltFieldEnd)>(*RltFieldStart)) return TRUE;
	else return FALSE;
}
BOOL CTools_Ansi::GetCurField_putDest(char *pDest,int MaxDestLen,const char* pStr,int Len,int StartOff,int *RltFieldStart,int *RltFieldEnd,char Seperator1,char Seperator2,char Seperator3,char Seperator4)
{
	BOOL brlt=GetCurField(pStr,Len,StartOff,RltFieldStart,RltFieldEnd,Seperator1,Seperator2,Seperator3,Seperator4);
	if(brlt&&pDest&&MaxDestLen>0)
	{
		int len=(*RltFieldEnd)-(*RltFieldStart);
		int copylen= len>MaxDestLen-1 ? MaxDestLen-1 : len;
		memcpy(pDest,pStr+(*RltFieldStart),copylen);
		pDest[copylen]=0;
	}
	return brlt;
}
//ȡָ����Χ���ü�����������������
bool CTools_Ansi::GetCurField(const char *pStr,int StartOff,int EndOff,int& FieldStart,int& FieldEnd,char Seperator1,char Seperator2,char Seperator3,char Seperator4)
{
	FieldStart=StartOff;
	FieldEnd=0;
	while(FieldStart<EndOff&&
			((Seperator1!=0&&pStr[FieldStart]==Seperator1)||
			 (Seperator2!=0&&pStr[FieldStart]==Seperator2)||
			 (Seperator3!=0&&pStr[FieldStart]==Seperator3)||
			 (Seperator4!=0&&pStr[FieldStart]==Seperator4)))
		FieldStart++;
	FieldEnd=FieldStart;
	while(FieldEnd<EndOff&&
			((Seperator1==0||pStr[FieldEnd]!=Seperator1)&&
			 (Seperator2==0||pStr[FieldEnd]!=Seperator2)&&
			 (Seperator3==0||pStr[FieldEnd]!=Seperator3)&&
			 (Seperator4==0||pStr[FieldEnd]!=Seperator4)))
		FieldEnd++;
	if(FieldEnd>FieldStart) return true;
	else return false;
}
//ȡָ��λ�ÿ�ʼ��ָ�������֮ǰ���ַ����������˵�ǰ�ĵĿո�tab�ͼ���������س���
int CTools_Ansi::GetCurField2(const char *pStr,int Len,int StartOff,int& RltFieldStart,int& RltFieldEnd,char Seperator1,char Seperator2,char Seperator3,char Seperator4)
{
	int				i;
	if(!Len) Len=(int)strlen(pStr);
	i=StartOff;
	RltFieldStart=i;
	while(i<Len&&pStr[i]!=Seperator1&&pStr[i]!=Seperator2&&pStr[i]!=Seperator3&&pStr[i]!=Seperator4) i++;
	RltFieldEnd=i;
	return RltFieldEnd-RltFieldStart;
}
int CTools_Ansi::GetCurField2_putDest(char *pDest,int MaxDestLen,const char* pStr,int Len,int StartOff,int& RltFieldStart,int& RltFieldEnd,char Seperator1,char Seperator2,char Seperator3,char Seperator4)
{
	int rltlen=GetCurField2(pStr,Len,StartOff,RltFieldStart,RltFieldEnd,Seperator1,Seperator2,Seperator3,Seperator4);
	if(rltlen>=0&&pDest&&MaxDestLen>0)
	{
		int copylen= rltlen>MaxDestLen-1 ? MaxDestLen-1 : rltlen;
		if(copylen>0) memcpy(pDest,pStr+RltFieldStart,copylen);
		pDest[copylen]=0;
	}
	return rltlen;
}


int CTools_Ansi::GetFourField(const char *pStr,int Len,int StartOff,int *RltFieldStart1,int *RltFieldEnd1,int *RltFieldStart2,int *RltFieldEnd2,int *RltFieldStart3,int *RltFieldEnd3,int *RltFieldStart4,int *RltFieldEnd4,char Seperator1,char Seperator2,char Seperator3,char Seperator4)
{
	int				Count,iStart,iEnd;
	BOOL			bRlt;

	Count=0;
	if(!Len) Len=strlen(pStr);
	if(RltFieldStart1&&RltFieldEnd1) (*RltFieldStart1)=(*RltFieldEnd1)=0;
	if(RltFieldStart2&&RltFieldEnd2) (*RltFieldStart2)=(*RltFieldEnd2)=0;
	if(RltFieldStart3&&RltFieldEnd3) (*RltFieldStart3)=(*RltFieldEnd3)=0;
	if(RltFieldStart4&&RltFieldEnd4) (*RltFieldStart4)=(*RltFieldEnd4)=0;

	if(!RltFieldStart1||!RltFieldEnd1) return Count;
	bRlt=GetCurField(pStr,Len,StartOff,&iStart,&iEnd,Seperator1,Seperator2,Seperator3,Seperator4);
	if(!bRlt) return Count;
	*RltFieldStart1=iStart;
	*RltFieldEnd1=iEnd;
	Count++;

	if(!RltFieldStart2||!RltFieldEnd2) return Count;
	bRlt=GetCurField(pStr,Len,iEnd,&iStart,&iEnd,Seperator1,Seperator2,Seperator3,Seperator4);
	if(!bRlt) return Count;
	*RltFieldStart2=iStart;
	*RltFieldEnd2=iEnd;
	Count++;

	if(!RltFieldStart3||!RltFieldEnd3) return Count;
	bRlt=GetCurField(pStr,Len,iEnd,&iStart,&iEnd,Seperator1,Seperator2,Seperator3,Seperator4);
	if(!bRlt) return Count;
	*RltFieldStart3=iStart;
	*RltFieldEnd3=iEnd;
	Count++;

	if(!RltFieldStart4||!RltFieldEnd4) return Count;
	bRlt=GetCurField(pStr,Len,iEnd,&iStart,&iEnd,Seperator1,Seperator2,Seperator3,Seperator4);
	if(!bRlt) return Count;
	*RltFieldStart4=iStart;
	*RltFieldEnd4=iEnd;
	Count++;

	return Count;
}

int CTools_Ansi::GetFourFieldInt(const char *pStr,int Len,int StartOff,int *RltValue1,int *RltValue2,int *RltValue3,int *RltValue4,char Seperator1,char Seperator2,char Seperator3,char Seperator4)
{
    int FieldStart1,FieldEnd1,FieldStart2,FieldEnd2,FieldStart3,FieldEnd3,FieldStart4,FieldEnd4;

    int irlt=GetFourField(pStr,Len,StartOff,&FieldStart1,&FieldEnd1,&FieldStart2,&FieldEnd2,&FieldStart3,&FieldEnd3,&FieldStart4,&FieldEnd4,Seperator1,Seperator2,Seperator3,Seperator4);
    if(irlt>0&&RltValue1&&FieldStart1<Len) *RltValue1=atoi(pStr+FieldStart1);
    if(irlt>1&&RltValue2&&FieldStart2<Len) *RltValue2=atoi(pStr+FieldStart2);
    if(irlt>2&&RltValue3&&FieldStart3<Len) *RltValue3=atoi(pStr+FieldStart3);
    if(irlt>3&&RltValue4&&FieldStart4<Len) *RltValue4=atoi(pStr+FieldStart4);
    return irlt;
}

int CTools_Ansi::GetFourField(const char *pStr,int StartOff,int EndOff,
		int& FieldStart1,int& FieldEnd1,int& FieldStart2,int& FieldEnd2,int& FieldStart3,int& FieldEnd3,int& FieldStart4,int& FieldEnd4,
		char Seperator1,char Seperator2,char Seperator3,char Seperator4)
{
	int				Count,iStart,iEnd;
	bool			bRlt;

	Count=0;
	FieldStart1=FieldEnd1=0;
	FieldStart2=FieldEnd2=0;
	FieldStart3=FieldEnd3=0;
	FieldStart4=FieldEnd4=0;

	bRlt=GetCurField(pStr,StartOff,EndOff,iStart,iEnd,Seperator1,Seperator2,Seperator3,Seperator4);
	if(!bRlt) return Count;
	FieldStart1=iStart;
	FieldEnd1=iEnd;
	Count++;

	bRlt=GetCurField(pStr,iEnd,EndOff,iStart,iEnd,Seperator1,Seperator2,Seperator3,Seperator4);
	if(!bRlt) return Count;
	FieldStart2=iStart;
	FieldEnd2=iEnd;
	Count++;

	bRlt=GetCurField(pStr,iEnd,EndOff,iStart,iEnd,Seperator1,Seperator2,Seperator3,Seperator4);
	if(!bRlt) return Count;
	FieldStart3=iStart;
	FieldEnd3=iEnd;
	Count++;

	bRlt=GetCurField(pStr,iEnd,EndOff,iStart,iEnd,Seperator1,Seperator2,Seperator3,Seperator4);
	if(!bRlt) return Count;
	FieldStart4=iStart;
	FieldEnd4=iEnd;
	Count++;

	return Count;
}

//��Str��ȡ��LeadingStr����ֱ��EndingStr֮��Ĵ�
string CTools_Ansi::GetSubStr(const string& Str,const string& LeadingStr,const string& EndingStr)
{
    int pos=Str.find(LeadingStr);
    if(pos==string::npos) return string("");
    pos+=LeadingStr.length();
    int pos2=Str.find(EndingStr,pos);
    if(pos2!=string::npos) return Str.substr(pos,pos2-pos);
    else return Str.substr(pos);
}

//get content in a string that follow prefix.
bool CTools_Ansi::GetContentFollowPrefix(const char* pStr,int StartOff,int EndOff,const char* pPrefix,char* pContent,int ContentSize)
{
	int iStart,iEnd,PrefixLen;
	PrefixLen=strlen(pPrefix);
	if(EndOff-StartOff>=PrefixLen&&memicmp(pStr+StartOff,pPrefix,PrefixLen)==0)
	{
		iStart=StartOff+PrefixLen;
		while(iStart<EndOff&&pStr[iStart]==' ') iStart++;
		iEnd=EndOff;
		while(iEnd>iStart&&pStr[iEnd-1]==' ') iEnd--;
		if(iEnd-iStart<ContentSize)
		{
			memcpy(pContent,pStr+iStart,iEnd-iStart);
			pContent[iEnd-iStart]=0;
		}
		else
		{
			pContent[0]=0;
		}
		return true;
	}
	return false;
}
//get content in a string that follow prefix.
bool CTools_Ansi::GetContentFollowPrefix(const char* pStr,int StartOff,int EndOff,const char* pPrefix,string rltContent)
{
    char buf[1024]={0};
    bool brlt=GetContentFollowPrefix(pStr,StartOff,EndOff,pPrefix,buf,sizeof(buf));
    if(brlt) rltContent=string(buf);
    return brlt;
}

//function		:GetSubStrInYuankuohao
//description	:get sub string in Yuankuohao
BOOL CTools_Ansi::GetSubStrInYuankuohao(const char *pSour,char *pRlt,int RltSize)
{
	int				i,j,Len;
	pRlt[0]=0;
	Len=strlen(pSour);
	for(i=0;i<Len&&pSour[i]!='(';i++);
	if(pSour[i]=='(') i++;
	for(j=Len;j>i&&pSour[j-1]!=')';j--);
	if(pSour[j-1]==')') j--;
	if(j-i>=RltSize) return FALSE;
	memcpy(pRlt,pSour+i,j-i);
	pRlt[j-i]=0;
	return TRUE;
}
//����һ������ָ���ַ��ĸ���
int CTools_Ansi::GetCountOfCharInStr(const char* pStr,char Ch)
{
	if(!pStr) return 0;
	int Cnt=0,len=strlen(pStr);
	for(int i=0;i<len;i++)
		if(pStr[i]==Ch) Cnt++;
	return Cnt;
}
//ȡһ������ָ���ַ���λ��
std::vector<int> CTools_Ansi::GetCharPos(const char* pStr,char Ch)
{
	std::vector<int> pos;
	if(pStr)
	{
		for(int i=0,len=(int)strlen(pStr);i<len;i++)
			if(pStr[i]==Ch) pos.push_back(i);
	}
	return pos;
}

//��һ�������ָ������ֳɶ���Ӵ�
std::vector<std::string> CTools_Ansi::SplitString(const char* pStr,char splitchar1,char splitchar2)
{
	std::vector<std::string> substr;
	if(pStr)
	{
		int pos=0,len=strlen(pStr);
		if(splitchar2==0)
		{
			for(int i=0;i<len;i++)
			{
				if(pStr[i]==splitchar1) { substr.push_back(string(pStr+pos,i-pos));  pos=i+1; }
			}
		}
		else
		{
			for(int i=0;i<len-1;i++)
			{
				if(pStr[i]==splitchar1&&pStr[i+1]==splitchar2) { substr.push_back(string(pStr+pos,i-pos));  pos=i+2; }
			}
		}
		substr.push_back(string(pStr+pos,len-pos));
	}
	return substr;
}
//��һ�������ָ������ֳɶ���Ӵ�
void CTools_Ansi::SplitString(vector<int>& rltsubpos,vector<int>& rltsublen,const char* pStr,char splitchar1,char splitchar2)
{
    rltsubpos.clear();
    rltsublen.clear();
	if(pStr)
	{
		int pos=0,len=strlen(pStr);
		if(splitchar2==0)
		{
			for(int i=0;i<len;i++)
			{
				if(pStr[i]==splitchar1) 
                { 
                    rltsubpos.push_back(pos);
                    rltsublen.push_back(i-pos);
                    pos=i+1; 
                }
			}
		}
		else
		{
			for(int i=0;i<len-1;i++)
			{
				if(pStr[i]==splitchar1&&pStr[i+1]==splitchar2) 
                { 
                    rltsubpos.push_back(pos);
                    rltsublen.push_back(i-pos);
                    pos=i+2; 
                }
			}
		}
        rltsubpos.push_back(pos);
        rltsublen.push_back(len-pos);
	}
}
//��һ�������ָ������ֳɶ���Ӵ�
bool CTools_Ansi::SplitString(int* prltsubpos,int* prltsublen,int& rltsubcount,int maxsubcount,const char* pStr,char splitchar1,char splitchar2)
{
    rltsubcount=0;
	if(pStr)
	{
		int pos=0,len=strlen(pStr);
		if(splitchar2==0)
		{
			for(int i=0;i<len;i++)
			{
				if(pStr[i]==splitchar1) 
                { 
                    prltsubpos[rltsubcount]=pos;
                    prltsublen[rltsubcount++]=i-pos;
                    if(rltsubcount>=maxsubcount) return false;
                    pos=i+1; 
                }
			}
		}
		else
		{
			for(int i=0;i<len-1;i++)
			{
				if(pStr[i]==splitchar1&&pStr[i+1]==splitchar2) 
                { 
                    prltsubpos[rltsubcount]=pos;
                    prltsublen[rltsubcount++]=i-pos;
                    if(rltsubcount>=maxsubcount) return false;
                    pos=i+2; 
                }
			}
		}
        prltsubpos[rltsubcount]=pos;
        prltsublen[rltsubcount++]=len-pos;
        return true;
	}
    return false;
}
//�зִ�������ʽΪ��str11-str12;str21-str22;str31-str32������[;]Ϊsplitchar1��[-]Ϊsplitchar2�����˷ָ�����β�Ŀո�tab���س������У����˵��յ��Ӵ�
vector<pair<string,string>> CTools_Ansi::SplitString2(const char* pStr,char splitchar1,char splitchar2)
{
	vector<pair<string,string>> substr;
	if(pStr)
	{
		int off0=0,off1=0,off2=0,off=0;
		int len=strlen(pStr);
		while(off<len)
		{
			off0=off;
			off1=-1;
			while(off<len&&pStr[off]!=splitchar1)
			{
				if(pStr[off]==splitchar2&&off1==-1)  off1=off;
				off++;
			}
			if(off1==-1) off1=off;
			//now off0 is start offset, off1 is offset of splitchar2, off is offset of splitchar1 

			int i1=off0,i2=off1;
			while(i1<i2&&(pStr[i1]==' '||pStr[i1]=='\t'||pStr[i1]=='\r'||pStr[i1]=='\n')) i1++;
			while(i2>i1&&(pStr[i2-1]==' '||pStr[i2-1]=='\t'||pStr[i2-1]=='\r'||pStr[i2-1]=='\n')) i2--;

			int j1=off1+( off1<len&&(pStr[off1]==splitchar2||pStr[off1]==splitchar1) ? 1 : 0 );
			int j2=off;
			while(j1<j2&&(pStr[j1]==' '||pStr[j1]=='\t'||pStr[j1]=='\r'||pStr[j1]=='\n')) j1++;
			while(j2>j1&&(pStr[j2-1]==' '||pStr[j2-1]=='\t'||pStr[j2-1]=='\r'||pStr[j2-1]=='\n')) j2--;

			if(i2>i1||j2>j1)
				substr.push_back(make_pair(string(pStr+i1,i2-i1),string(pStr+j1,j2-j1)));

			if(off==len) break;
			off++;
		}
	}
	return substr;
}


//ִ��WSAStartup
void CTools_Ansi::PerformWSAStartup(void)
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,0),&wsaData);
}

//ִ��WSACleanup
void CTools_Ansi::PerformWSACleanup(void)
{
    WSACleanup();
}


//function		:GetLocalHostName_IP
//description	:1. get local host name and local ip
BOOL CTools_Ansi::GetLocalHostName_IP(char *pHostName,int cbHostName,DWORD *pLocalIP,int MaxIPCount)
{

	HOSTENT			*pHost;
	DWORD			**ppAddress;
	int				i;
	DWORD			LocalIP;
	char			LocalHostName[HOSTNAMELEN];

																			//ȡ������ַ
	if(pHostName) 
		memset(pHostName,0,cbHostName);
	if(pLocalIP!=NULL&&MaxIPCount>0)
		memset((char*)pLocalIP,0,sizeof(DWORD)*MaxIPCount);

	memset((char*)LocalHostName,0,sizeof(LocalHostName));
	LocalIP=0;

 	gethostname(LocalHostName,sizeof(LocalHostName)-1);
	if(!LocalHostName[0]) return FALSE;

	if(pHostName)
		strncpy(pHostName,LocalHostName,cbHostName-1);

	pHost=gethostbyname(LocalHostName);
	if(!pHost) return FALSE;
	if(pHost->h_length!=4||pHost->h_addrtype!=2) return FALSE;

	if(pLocalIP!=NULL&&MaxIPCount>0)
	{
		ppAddress=(DWORD**)(pHost->h_addr_list);
		for(i=0;i<MaxIPCount;i++)
		{
			if(!ppAddress[i]) 
				break;
			pLocalIP[i]=*(ppAddress[i]);
		}
	}
	return TRUE;
}


//function		:GetIPFromHostName
//description	:1. get local host name and local ip
//return		:IP number in result
int CTools_Ansi::GetIPFromHostName(const char *pHostName,DWORD *pHostIP,int MaxIPCount)
{
	HOSTENT			*pHost;
	DWORD			**ppAddress;
	int				i,Len,RltNum,DotNum;

	if(MaxIPCount<=0) return 0;
	if(!pHostName) return 0;
	if(!pHostIP) return 0; 

	for(i=0,Len=strlen(pHostName),DotNum=0;i<Len;i++)
	{
		if(pHostName[i]!=' '&&pHostName[i]!='\t'&&pHostName[i]!='.'&&(pHostName[i]<'0'||pHostName[i]>'9'))
			break;
		if(pHostName[i]=='.') DotNum++;
	}
	if(i>=Len&&DotNum==3)									//pHostName�����ֱ�ʾ��IP��ַ��ֱ��ת������
	{
		pHostIP[0]=ConvertStrIP(pHostName);
		return 1;
	}

	pHost=gethostbyname(pHostName);
	if(!pHost) return 0;
	if(pHost->h_length!=4||pHost->h_addrtype!=2) return 0;

	memset(pHostIP,0,sizeof(DWORD)*MaxIPCount);

	RltNum=0;
	ppAddress=(DWORD**)(pHost->h_addr_list);
	for(i=0;i<MaxIPCount;i++)
	{
		if(!ppAddress[i]) 
			break;
		pHostIP[i]=*(ppAddress[i]);
		RltNum++;
	}
	return RltNum;
}
bool CTools_Ansi::GetIPFromHostName2(const char *pHostName,unsigned int& HostIP)
{
    unsigned long dwHostIP;
    HostIP=0;
    if(GetIPFromHostName(pHostName,&dwHostIP,1)!=1) return false;
    HostIP=(unsigned int)dwHostIP;
    return true;
}



//	���ַ�����ʽ��IP��ַת����DWORD
DWORD CTools_Ansi::ConvertStrIP(const char *pIP)
{
	DWORD			dwIP;
	dwIP=inet_addr(pIP);
	return dwIP;
}

char* CTools_Ansi::ConvertdwIP(DWORD dwIP)
{
	struct in_addr in;
	in.S_un.S_addr=dwIP;
	return inet_ntoa(in);
}
char* CTools_Ansi::ConvertdwIP2(DWORD dwIP,char* buf,int bufsize)
{
	struct in_addr in;
	in.S_un.S_addr=dwIP;
	strncpy(buf,inet_ntoa(in),bufsize-1);
	buf[bufsize-1]=0;
	return buf;
}

//	�ж��ǲ���ͬһ������
BOOL CTools_Ansi::IsSameHost(DWORD* iHostIP,int IPCount,DWORD TargetIP)
{
	int				i;
	for(i=0;i<IPCount;i++)
		if(iHostIP[i]!=0&&iHostIP[i]!=0xffffffff&&iHostIP[i]==TargetIP) return TRUE;
	return FALSE;
}



//	���ݷָ��������ַ�����ȡ����N���ֶ�
BOOL CTools_Ansi::GetFieldFromStr(const char *pData,int FieldOrd,const char *pSeperator,char *RltBuf,int RltSize)
{
	int				iOrd,Off,Len,SeperatorLen,j;
	char			*pp;

	memset(RltBuf,0,RltSize);

	iOrd=0;
	Off=0;
	Len=strlen(pData);
	SeperatorLen=strlen(pSeperator);
	while(Off<Len)
	{
		if(iOrd==FieldOrd) break;
		pp=(char*)strstr(pData+Off,pSeperator);
		if(!pp) break;
		j=pp-(pData+Off);
		Off+=j+SeperatorLen;
		iOrd++;
	}

	if(iOrd==FieldOrd)
	{
		pp=(char*)strstr(pData+Off,pSeperator);
		if(!pp) pp=(char*)pData+Len;
		j=pp-(pData+Off);
		if(j>RltSize) j=RltSize;
		memcpy(RltBuf,pData+Off,j);
		return TRUE;
	}


	return FALSE;
}



//	�ж��ַ������ʱ���Ƿ������ǰʱ��
//	1. strDateTime���԰����������ʱ�䣬��ͬʱ�䲿���÷ֺŻ򶺺ŷָ�
//	2. ÿ��ʱ�����date���ֺ�time����
//	3. ���ÿ��ʱ����û��date����ʾdate�������Ϸ������û��time����ʾtime�������Ϸ�
//	3. date���ֿ��԰������ʱ�䣬�ո�ָ���ȡֵ��Χ��
//		�����ա���ĩ����1����2����3����4����5����6����7����0����1-��3
//		1�š�2�š�......31�š�1��-10��
//		1��1�ա�12��31�ա�1��1��-12��31��
//	4. time���ֿɰ������ʱ�䣬�ո�ָ�����ʽ��
//		hh:mm:ss
//		hh:mm:ss-hh:mm:ss
//		hh:mm
//		hh:mm-hh:mm
//	5. ʱ���ڲ����пո�
BOOL CTools_Ansi::IsNowValidDateTimeStr(const char *strDateTime)
{
	time_t			itime;
	struct tm		*ltime;
	BOOL			bValidDate,bValidTime,bRlt;
	int				Off,i,Len;
	char			Buf[512];


	if(strstr(strDateTime,",")!=0||strstr(strDateTime,";")!=0)
	{																			//********����������ʱ������********
		Len=strlen(strDateTime);
		Off=0;
		while(Off<Len)
		{
			for(;Off<Len&&(strDateTime[Off]==','||strDateTime[Off]==';'||strDateTime[Off]==' '||strDateTime[Off]=='\t');Off++);
			for(i=Off;i<Len&&i-Off<sizeof(Buf)-1&&strDateTime[i]!=','&&strDateTime[i]!=';';i++);
			if(i>Off)
			{
				memcpy(Buf,strDateTime+Off,i-Off);
				Buf[i-Off]=0;
				bRlt=IsNowValidDateTimeStr(Buf);
				if(bRlt) return TRUE;
				Off=i+1;
			}
		}
		return FALSE;
	}

																				//********���洦������ֻ����һ��ʱ������********
	time(&itime);
	ltime=localtime(&itime);
	bValidDate=FALSE;
	bValidTime=FALSE;

	if(	strstr(strDateTime,"������")==0&&strstr(strDateTime,"��")==0&&strstr(strDateTime,"��")==0&&
		strstr(strDateTime,"��")==0&&strstr(strDateTime,"��")==0&&
		strstr(strDateTime,":")==0) 
		return FALSE;															//��û�ж�������Ҳû�ж���ʱ�䣬����ʧ��
	else if(strstr(strDateTime,"������")==0&&strstr(strDateTime,"��")==0&&strstr(strDateTime,"��")==0&&
			strstr(strDateTime,"��")==0&&strstr(strDateTime,"��")==0)
		bValidDate=TRUE;														//û�ж������ڣ���Ϊ������Ч
	else if(strstr(strDateTime,":")==0)
		bValidTime=TRUE;														//û�ж���ʱ�䣬��Ϊʱ����Ч

	Len=strlen(strDateTime);
	Off=0;
	while(Off<Len)
	{																			//һ�����ֶν����ж�
		for(;Off<Len&&(strDateTime[Off]==' '||strDateTime[Off]=='\t');Off++);
		for(i=Off;i<Len&&i-Off<sizeof(Buf)-1&&strDateTime[i]!=' '&&strDateTime[i]!='\t';i++);
		memcpy(Buf,strDateTime+Off,i-Off);
		Buf[i-Off]=0;
		if(!bValidDate&&
			(strstr(Buf,"������")!=0||strstr(Buf,"��")!=0||strstr(Buf,"��")!=0||
			 strstr(strDateTime,"��")!=0||strstr(strDateTime,"��")!=0))
			bValidDate=IsNowValidDateStr(Buf);
		else if(!bValidTime&&strstr(Buf,":")!=0)
			bValidTime=IsNowValidTimeStr(Buf);

		if(bValidDate&&bValidTime) return TRUE;
		Off=i;
	}

	return FALSE;

}


//	�ж��ַ������ʱ���Ƿ������ǰʱ��
//	1. strDateȡֵ��Χ��
//		�����ա���ĩ����1����2����3����4����5����6����7����0����1-��3����һ���ܶ�......����
//		1�š�2�š�......31�š�1��-10��
//		1��1�ա�12��31�ա�1��1��-12��31�ա�һ��1��......ʮ����1��
BOOL CTools_Ansi::IsNowValidDateStr(const char *strDate)
{
	time_t			itime;
	struct tm		*ltime;
	BOOL			bValidData;
	int				i,j,m1,d1,m2,d2;
	char			*pEndDate,*pDate1,*pDate2;;
	char			*pMonth,*pMon1,*pMon2;


	time(&itime);
	ltime=localtime(&itime);
	bValidData=FALSE;

	if(strstr(strDate,"������")!=0&&ltime->tm_wday>=1&&ltime->tm_wday<=5) return TRUE;
	if(strstr(strDate,"��ĩ")!=0&&(ltime->tm_wday==0||ltime->tm_wday==6)) return TRUE;

	pEndDate=(char*)strstr(strDate,"-");
	if(!pEndDate)
	{																			//û�ж�����ʼʱ��
		if(memcmp(strDate,"��",2)==0)
		{
			if(memcmp(strDate,"��һ",4)==0) i=1;
			else if(memcmp(strDate,"�ܶ�",4)==0) i=2;
			else if(memcmp(strDate,"����",4)==0) i=3;
			else if(memcmp(strDate,"����",4)==0) i=4;
			else if(memcmp(strDate,"����",4)==0) i=5;
			else if(memcmp(strDate,"����",4)==0) i=6;
			else if(memcmp(strDate,"����",4)==0) i=0;
			else i=atoi(strDate+2);

			if(i==7) i=0;
			if(ltime->tm_wday==i) return TRUE;									//�������ڼ��Ķ���
		}
		else if(strstr(strDate,"��")!=0)
		{
			i=atoi(strDate);
			if(ltime->tm_mday==i) return TRUE;									//���ϼ��ŵĶ���
		}
		else if((pMonth=(char*)strstr(strDate,"��"))!=0)
		{
			if(memcmp(strDate,"һ��",4)==0) i=1;
			else if(memcmp(strDate,"����",4)==0) i=2;
			else if(memcmp(strDate,"����",4)==0) i=3;
			else if(memcmp(strDate,"����",4)==0) i=4;
			else if(memcmp(strDate,"����",4)==0) i=5;
			else if(memcmp(strDate,"����",4)==0) i=6;
			else if(memcmp(strDate,"����",4)==0) i=7;
			else if(memcmp(strDate,"����",4)==0) i=8;
			else if(memcmp(strDate,"����",4)==0) i=9;
			else if(memcmp(strDate,"ʮ��",4)==0) i=10;
			else if(memcmp(strDate,"ʮһ��",4)==0) i=11;
			else if(memcmp(strDate,"ʮ����",4)==0) i=12;
			else i=atoi(strDate);
			j=atoi(pMonth+2);
			if(ltime->tm_mon+1==i&&ltime->tm_mday==j) return TRUE;				//���ϼ��¼��յĶ���
		}
	}
	else
	{																			//������ʼʱ��
		pEndDate++;
		if(memcmp(strDate,"��",2)==0&&memcmp(pEndDate,"��",2)==0)
		{
			if(memcmp(strDate,"��һ",4)==0) i=1;
			else if(memcmp(strDate,"�ܶ�",4)==0) i=2;
			else if(memcmp(strDate,"����",4)==0) i=3;
			else if(memcmp(strDate,"����",4)==0) i=4;
			else if(memcmp(strDate,"����",4)==0) i=5;
			else if(memcmp(strDate,"����",4)==0) i=6;
			else if(memcmp(strDate,"����",4)==0) i=0;
			else i=atoi(strDate+2);
			if(i==7) i=0;

			if(memcmp(pEndDate,"��һ",4)==0) j=1;
			else if(memcmp(pEndDate,"�ܶ�",4)==0) j=2;
			else if(memcmp(pEndDate,"����",4)==0) j=3;
			else if(memcmp(pEndDate,"����",4)==0) j=4;
			else if(memcmp(pEndDate,"����",4)==0) j=5;
			else if(memcmp(pEndDate,"����",4)==0) j=6;
			else if(memcmp(pEndDate,"����",4)==0) j=0;
			else j=atoi(pEndDate+2);
			if(j==7) j=0;

			if(	i<=j&&ltime->tm_wday>=i&&ltime->tm_wday<=j||
				i>j&&(ltime->tm_wday>=i&&ltime->tm_wday<=6||ltime->tm_wday<=j))
				return TRUE;													//������x-��y�Ķ���
		}
		else if((pDate1=(char*)strstr(strDate,"��"))!=0&&pDate1<pEndDate&&(pDate2=(char*)strstr(pEndDate,"��"))!=0)
		{
			i=atoi(strDate);
			j=atoi(pEndDate);
			if(	i<=j&&ltime->tm_mday>=i&&ltime->tm_mday<=j||
				i>j&&(ltime->tm_mday>=i&&ltime->tm_mday<=31||ltime->tm_mday<=j))
				return TRUE;													//����x��-y�ŵĶ���
		}
		else if((pMon1=(char*)strstr(strDate,"��"))!=0&&(pDate1=(char*)strstr(strDate,"��"))!=0&&pDate1>pMon1&&pDate1<pEndDate&&
				(pMon2=(char*)strstr(pEndDate,"��"))!=0&&(pDate2=(char*)strstr(pEndDate,"��"))!=0&&pDate2>pMon2)
		{
			if(memcmp(strDate,"һ��",4)==0) m1=1;
			else if(memcmp(strDate,"����",4)==0) m1=2;
			else if(memcmp(strDate,"����",4)==0) m1=3;
			else if(memcmp(strDate,"����",4)==0) m1=4;
			else if(memcmp(strDate,"����",4)==0) m1=5;
			else if(memcmp(strDate,"����",4)==0) m1=6;
			else if(memcmp(strDate,"����",4)==0) m1=7;
			else if(memcmp(strDate,"����",4)==0) m1=8;
			else if(memcmp(strDate,"����",4)==0) m1=9;
			else if(memcmp(strDate,"ʮ��",4)==0) m1=10;
			else if(memcmp(strDate,"ʮһ��",4)==0) m1=11;
			else if(memcmp(strDate,"ʮ����",4)==0) m1=12;
			else m1=atoi(strDate);

			d1=atoi(pMon1+2);

			if(memcmp(pEndDate,"һ��",4)==0) m2=1;
			else if(memcmp(pEndDate,"����",4)==0) m2=2;
			else if(memcmp(pEndDate,"����",4)==0) m2=3;
			else if(memcmp(pEndDate,"����",4)==0) m2=4;
			else if(memcmp(pEndDate,"����",4)==0) m2=5;
			else if(memcmp(pEndDate,"����",4)==0) m2=6;
			else if(memcmp(pEndDate,"����",4)==0) m2=7;
			else if(memcmp(pEndDate,"����",4)==0) m2=8;
			else if(memcmp(pEndDate,"����",4)==0) m2=9;
			else if(memcmp(pEndDate,"ʮ��",4)==0) m2=10;
			else if(memcmp(pEndDate,"ʮһ��",4)==0) m2=11;
			else if(memcmp(pEndDate,"ʮ����",4)==0) m2=12;
			else m2=atoi(pEndDate);

			d2=atoi(pMon2+2);

			if(	(ltime->tm_mon+1>m1||ltime->tm_mon+1==m1&&ltime->tm_mday>=d1)&&
				(ltime->tm_mon+1<m2||ltime->tm_mon+1==m2&&ltime->tm_mday<=d2))
				return TRUE;													//����x��y��-a��b�յĶ���
		}

	}

	return FALSE;
}


//	�ж��ַ������ʱ���Ƿ������ǰʱ��
//	1. strTime��ʽ��
//		hh:mm
//		hh:mm:ss
//		hh:mm-hh:mm
//		hh:mm:ss-hh:mm:ss
//	2. �����÷���hh:02��ʾÿСʱ��02��
BOOL CTools_Ansi::IsNowValidTimeStr(const char *strTime)
{
	time_t			itime;
	struct tm		*ltime;
	BOOL			bValidData;
	int				Len;
	char			*pEndTime,*pp;
	int				h1,m1,s1,h2,m2,s2;
	int				EveryHour1ID,EveryHour2ID;


	time(&itime);
	ltime=localtime(&itime);
	bValidData=FALSE;

	Len=strlen(strTime);
	pEndTime=(char*)strstr(strTime,"-");
	h1=m1=s1=h2=m2=s2=-1;
	EveryHour1ID=EveryHour2ID=0;
	if(!pEndTime)
	{																			//û�ж�����ʼʱ��
		pp=(char*)strTime;
		while(pp[0]==' '||pp[0]=='\t') pp++;

		if(pp[0]=='h'&&pp[1]=='h')
		{
			EveryHour1ID=1;
			pp+=2;
		}
		else
		{
			h1=atoi(pp);
			while(pp[0]>='0'&&pp[0]<='9') pp++;
		}

		if(pp[0]==':')
		{
			pp++;
			while(pp[0]==' '||pp[0]=='\t') pp++;
			m1=atoi(pp);

			while(pp[0]>='0'&&pp[0]<='9') pp++;
			if(pp[0]==':')
			{
				pp++;
				while(pp[0]==' '||pp[0]=='\t') pp++;
				s1=atoi(pp);
			}
		}

		
		if(	h1>=0&&m1>=0&&s1<0&&ltime->tm_hour==h1&&ltime->tm_min==m1||
			EveryHour1ID&&m1>=0&&s1<0&&ltime->tm_min==m1||
			h1>=0&&m1>=0&&s1>=0&&ltime->tm_hour==h1&&ltime->tm_min==m1&&ltime->tm_sec==s1||
			EveryHour1ID&&m1>=0&&s1>=0&&ltime->tm_min==m1&&ltime->tm_sec==s1)
			return TRUE;														//����hh:mm��hh:mm:ss�Ķ���
	}
	else
	{																			//������ʼʱ��
		pEndTime++;

		pp=(char*)strTime;
		while(pp[0]==' '||pp[0]=='\t') pp++;

		if(pp[0]=='h'&&pp[1]=='h')
		{
			EveryHour1ID=1;
			pp+=2;
		}
		else
		{
			h1=atoi(pp);
			while(pp[0]>='0'&&pp[0]<='9') pp++;
		}

		if(pp[0]==':')
		{
			pp++;
			while(pp[0]==' '||pp[0]=='\t') pp++;
			m1=atoi(pp);

			while(pp[0]>='0'&&pp[0]<='9') pp++;
			if(pp[0]==':')
			{
				pp++;
				while(pp[0]==' '||pp[0]=='\t') pp++;
				s1=atoi(pp);
			}
		}



		pp=pEndTime;
		while(pp[0]==' '||pp[0]=='\t') pp++;

		if(pp[0]=='h'&&pp[1]=='h') 
		{
			EveryHour2ID=1;
			pp+=2;
		}
		else
		{
			h2=atoi(pp);
			while(pp[0]>='0'&&pp[0]<='9') pp++;
		}
		if(pp[0]==':')
		{
			pp++;
			while(pp[0]==' '||pp[0]=='\t') pp++;
			m2=atoi(pp);

			while(pp[0]>='0'&&pp[0]<='9') pp++;
			if(pp[0]==':')
			{
				pp++;
				while(pp[0]==' '||pp[0]=='\t') pp++;
				s2=atoi(pp);
			}
		}


		if(h1>=0&&m1>=0&&h2>=0&&m2>=0)
		{
			if(s1<0) s1=0;
			if(s2<0) s2=59;

			if(h2>h1||h2==h1&&m2>m1||h2==h1&&m2==m1&&s2>=s1)
			{
				if(	(ltime->tm_hour>h1||ltime->tm_hour==h1&&ltime->tm_min>m1||ltime->tm_hour==h1&&ltime->tm_min==m1&&ltime->tm_sec>=s1)&&
					(ltime->tm_hour<h2||ltime->tm_hour==h2&&ltime->tm_min<m2||ltime->tm_hour==h2&&ltime->tm_min==m2&&ltime->tm_sec<=s2))
					return TRUE;
			}
			else
			{
				if(	(ltime->tm_hour>h1||ltime->tm_hour==h1&&ltime->tm_min>m1||ltime->tm_hour==h1&&ltime->tm_min==m1&&ltime->tm_sec>=s1)||
					(ltime->tm_hour<h2||ltime->tm_hour==h2&&ltime->tm_min<m2||ltime->tm_hour==h2&&ltime->tm_min==m2&&ltime->tm_sec<=s2))
					return TRUE;
			}
		}
		else if(EveryHour1ID&&m1>=0&&EveryHour2ID&&m2>=0)
		{
			if(s1<0) s1=0;
			if(s2<0) s2=59;

			if(m2>m1||m2==m1&&s2>=s1)
			{
				if(	(ltime->tm_min>m1||ltime->tm_min==m1&&ltime->tm_sec>=s1)&&
					(ltime->tm_min<m2||ltime->tm_min==m2&&ltime->tm_sec<=s2))
					return TRUE;
			}
			else
			{
				if(	(ltime->tm_min>m1||ltime->tm_min==m1&&ltime->tm_sec>=s1)||
					(ltime->tm_min<m2||ltime->tm_min==m2&&ltime->tm_sec<=s2))
					return TRUE;
			}
		}
	}

	return FALSE;
}


//	��NewFileָ���wave�ļ��ϲ���TargetFileָ���wave�ļ���
//	NewFile��TargetFile�ļ��ĸ�ʽ����һ��
BOOL CTools_Ansi::AppendWaveFileToAnother(const char *TargetFile,const char *NewFile)
{
	FILE			*fTarget,*fNew;
	BOOL			bRlt;
	struct RIFF_HEADER
	{
		char		szRiffID[4];												// 'R','I','F','F'
		DWORD		dwRiffSize;
		char		szRiffFormat[4];											// 'W','A','V','E'
	}RiffHead_Target,RiffHead_New;
	struct FMT_BLOCK
	{
		char		szFmtID[4];													// 'f','m','t',' '
		DWORD		dwFmtSize;
		struct WAVE_FORMAT
		{
			WORD	wFormatTag;
			WORD	wChannels;
			DWORD	dwSamplesPerSec;
			DWORD	dwAvgBytesPerSec;
			WORD	wBlockAlign;
			WORD	wBitsPerSample;
		}WavFormat;
	}FormatHead_Target,FormatHead_New;
	char			ExtFormatInfo_Target[2];
	char			ExtFormatInfo_New[2];
	struct FACT_BLOCK
	{
		char		szFactID[4];												// 'f','a','c','t'
		DWORD		dwFactSize;
	}FactHead_Target,FactHead_New;
	struct DATA_BLOCK
	{
		char		szDataID[4];
		DWORD		dwDataSize;
	}DataHead_Target,DataHead_New;
	DWORD			RIFFHeadOff_Target,DataHeadOff_Target;
	char			Tmp[32768];
	int				i,j,TmpSize;



	fTarget=fopen(TargetFile,"rb+");
	if(!fTarget) return FALSE;

	fNew=fopen(NewFile,"rb");
	if(!fNew)
	{
		fclose(fTarget);
		return FALSE;
	}


	memset((char*)&RiffHead_Target,0,sizeof(RiffHead_Target));
	memset((char*)&RiffHead_New,0,sizeof(RiffHead_New));
	memset((char*)&FormatHead_Target,0,sizeof(FormatHead_Target));
	memset((char*)&FormatHead_New,0,sizeof(FormatHead_New));
	memset((char*)ExtFormatInfo_Target,0,sizeof(ExtFormatInfo_Target));
	memset((char*)ExtFormatInfo_New,0,sizeof(ExtFormatInfo_New));
	memset((char*)&FactHead_Target,0,sizeof(FactHead_Target));
	memset((char*)&FactHead_New,0,sizeof(FactHead_New));
	memset((char*)&DataHead_Target,0,sizeof(DataHead_Target));
	memset((char*)&DataHead_New,0,sizeof(DataHead_New));

																				//��ȡTargetFile���ļ�ͷ
	RIFFHeadOff_Target=0;
	fread((char*)&RiffHead_Target,1,sizeof(RiffHead_Target),fTarget);
	fread((char*)&FormatHead_Target,1,sizeof(FormatHead_Target),fTarget);
	if(FormatHead_Target.dwFmtSize==18)
		fread((char*)ExtFormatInfo_Target,1,sizeof(ExtFormatInfo_Target),fTarget);
	fread((char*)&FactHead_Target,1,sizeof(FactHead_Target),fTarget);
	if(memcmp(FactHead_Target.szFactID,"fact",4)==0)
	{
		fseek(fTarget,FactHead_Target.dwFactSize,1);
		fread((char*)&DataHead_Target,1,sizeof(DataHead_Target),fTarget);
	}
	else
	{
		memcpy((char*)&DataHead_Target,(char*)&FactHead_Target,sizeof(DataHead_Target));
		memset((char*)&FactHead_Target,0,sizeof(FactHead_Target));
	}
	DataHeadOff_Target=ftell(fTarget)-sizeof(DataHead_Target);

																				//��ȡNewFile���ļ�ͷ
	fread((char*)&RiffHead_New,1,sizeof(RiffHead_New),fNew);
	fread((char*)&FormatHead_New,1,sizeof(FormatHead_New),fNew);
	if(FormatHead_New.dwFmtSize==18)
		fread((char*)ExtFormatInfo_New,1,sizeof(ExtFormatInfo_New),fNew);
	fread((char*)&FactHead_New,1,sizeof(FactHead_New),fNew);
	if(memcmp(FactHead_New.szFactID,"fact",4)==0)
	{
		fseek(fNew,FactHead_Target.dwFactSize,1);
		fread((char*)&DataHead_New,1,sizeof(DataHead_New),fNew);
	}
	else
	{
		memcpy((char*)&DataHead_New,(char*)&FactHead_New,sizeof(DataHead_New));
		memset((char*)&FactHead_New,0,sizeof(FactHead_New));
	}

	if(	memcmp((char*)&FormatHead_Target,(char*)&FormatHead_New,sizeof(FormatHead_Target))==0)
	{																			//wave��ʽһ��
		fseek(fTarget,0,2);

		TmpSize=sizeof(Tmp);
		j=DataHead_New.dwDataSize/TmpSize;
		for(i=0;i<j;i++)
		{
			fread(Tmp,1,TmpSize,fNew);
			fwrite(Tmp,1,TmpSize,fTarget);
		}
		j=DataHead_New.dwDataSize%TmpSize;
		if(j>0)
		{
			fread(Tmp,1,j,fNew);
			fwrite(Tmp,1,j,fTarget);
		}

		RiffHead_Target.dwRiffSize+=DataHead_New.dwDataSize;
		DataHead_Target.dwDataSize+=DataHead_New.dwDataSize;
		fseek(fTarget,RIFFHeadOff_Target,0);
		fwrite((char*)&RiffHead_Target,1,sizeof(RiffHead_Target),fTarget);
		fseek(fTarget,DataHeadOff_Target,0);
		fwrite((char*)&DataHead_Target,1,sizeof(DataHead_Target),fTarget);
		
		bRlt=TRUE;
	}
	else 
		bRlt=FALSE;																//wave��ʽ��һ��



	fclose(fTarget);
	fclose(fNew);
	return bRlt;
}


//	��Wave�ļ��У�ɾ��ָ������
//	pContent�ĳ���Ӧ�ô���16
//	UnitBytesָһ������ȥ�����ֽڣ�16bits�������2�ֽ�
BOOL CTools_Ansi::RemoveContentFromWaveFile(const char *FileName,const char *pContent,int Len,int UnitBytes)
{
	FILE			*fp,*fpNew;
	char			NewFileName[256];
	char			*pHead;
	struct RIFF_HEADER
	{
		char		szRiffID[4];												// 'R','I','F','F'
		DWORD		dwRiffSize;
		char		szRiffFormat[4];											// 'W','A','V','E'
	}RiffHead;
	struct FMT_BLOCK
	{
		char		szFmtID[4];													// 'f','m','t',' '
		DWORD		dwFmtSize;
		struct WAVE_FORMAT
		{
			WORD	wFormatTag;
			WORD	wChannels;
			DWORD	dwSamplesPerSec;
			DWORD	dwAvgBytesPerSec;
			WORD	wBlockAlign;
			WORD	wBitsPerSample;
		}WavFormat;
	}FormatHead;
	char			ExtFormatInfo[2];
	struct FACT_BLOCK
	{
		char		szFactID[4];												// 'f','a','c','t'
		DWORD		dwFactSize;
	}FactHead;
	struct DATA_BLOCK
	{
		char		szDataID[4];
		DWORD		dwDataSize;
	}DataHead;
	DWORD			RIFFHeadOff,DataHeadOff,DataOff;
	char			*pTmp;
	DWORD			Off,LastOff,OldLen,NewLen;
	DWORD			CmpVal1,CmpVal2,CmpVal3,CmpVal4;


	if(Len<8) return FALSE;
	CmpVal1=*(DWORD*)pContent;
	CmpVal2=*(DWORD*)(pContent+4);
	CmpVal3=*(DWORD*)(pContent+8);
	CmpVal4=*(DWORD*)(pContent+12);

	fp=fopen(FileName,"rb+");
	if(!fp) return FALSE;

	sprintf(NewFileName,"%s_~",FileName);
	fpNew=fopen(NewFileName,"wb");
	if(!fpNew)
	{
		fclose(fp);
		return FALSE;
	}

	memset((char*)&RiffHead,0,sizeof(RiffHead));
	memset((char*)&FormatHead,0,sizeof(FormatHead));
	memset((char*)ExtFormatInfo,0,sizeof(ExtFormatInfo));
	memset((char*)&FactHead,0,sizeof(FactHead));
	memset((char*)&DataHead,0,sizeof(DataHead));

																				//��ȡWave���ļ�ͷ
	RIFFHeadOff=0;
	fread((char*)&RiffHead,1,sizeof(RiffHead),fp);
	fread((char*)&FormatHead,1,sizeof(FormatHead),fp);
	if(FormatHead.dwFmtSize==18)
		fread((char*)ExtFormatInfo,1,sizeof(ExtFormatInfo),fp);
	fread((char*)&FactHead,1,sizeof(FactHead),fp);
	if(memcmp(FactHead.szFactID,"fact",4)==0)
	{
		fseek(fp,FactHead.dwFactSize,1);
		fread((char*)&DataHead,1,sizeof(DataHead),fp);
	}
	else
	{
		memcpy((char*)&DataHead,(char*)&FactHead,sizeof(DataHead));
		memset((char*)&FactHead,0,sizeof(FactHead));
	}
	DataOff=ftell(fp);
	DataHeadOff=DataOff-sizeof(DataHead);



	pHead=(char*)malloc(DataOff);
	if(!pHead)
	{
		fclose(fp);
		fclose(fpNew);
		unlink(NewFileName);
		return FALSE;
	}
	fseek(fp,0,0);
	fread(pHead,1,DataOff,fp);
	fwrite(pHead,1,DataOff,fpNew);
	free(pHead);



	OldLen=DataHead.dwDataSize;
	pTmp=(char*)malloc(OldLen);
	if(!pTmp)
	{
		fclose(fp);
		fclose(fpNew);
		unlink(NewFileName);
		return FALSE;
	}
	fread(pTmp,1,OldLen,fp);
	fclose(fp);



	Off=0;
	LastOff=0;
	NewLen=OldLen;
	while((int)OldLen>=Len&&Off<=OldLen-Len)
	{
		if(	CmpVal1==*(DWORD*)(pTmp+Off)&&
			CmpVal2==*(DWORD*)(pTmp+Off+4)&&
			CmpVal3==*(DWORD*)(pTmp+Off+8)&&
			CmpVal4==*(DWORD*)(pTmp+Off+12)&&
			memcmp(pContent+16,pTmp+Off+16,Len-16)==0)
		{
			NewLen-=Len;
			if(Off>LastOff)
				fwrite(pTmp+LastOff,1,Off-LastOff,fpNew);
			Off+=Len;
			LastOff=Off;
			RiffHead.dwRiffSize-=Len;
			DataHead.dwDataSize-=Len;
			continue;
		}
		Off+=UnitBytes;
	}
	if(OldLen>LastOff)
		fwrite(pTmp+LastOff,1,OldLen-LastOff,fpNew);

	free(pTmp);

	if(NewLen!=OldLen)
	{
		fseek(fpNew,0,0);
		fwrite((char*)&RiffHead,1,sizeof(RiffHead),fpNew);
		fseek(fpNew,DataHeadOff,0);
		fwrite((char*)&DataHead,1,sizeof(DataHead),fpNew);
		fclose(fpNew);
		unlink(FileName);
		rename(NewFileName,FileName);
	}
	else 
	{
		fclose(fpNew);
		unlink(NewFileName);
	}

	return TRUE;
}


//	��Wave�ļ��У�ȡ��Ƶ����
//	���س��ȡ����iSize�����󣬻�pContentΪ�գ���������Ҫ�ĳ���
int CTools_Ansi::GetContentFromWaveFile(const char *FileName,char *pContent,DWORD iSize)
{
	FILE			*fp;
	struct RIFF_HEADER
	{
		char		szRiffID[4];												// 'R','I','F','F'
		DWORD		dwRiffSize;
		char		szRiffFormat[4];											// 'W','A','V','E'
	}RiffHead;
	struct FMT_BLOCK
	{
		char		szFmtID[4];													// 'f','m','t',' '
		DWORD		dwFmtSize;
		struct WAVE_FORMAT
		{
			WORD	wFormatTag;
			WORD	wChannels;
			DWORD	dwSamplesPerSec;
			DWORD	dwAvgBytesPerSec;
			WORD	wBlockAlign;
			WORD	wBitsPerSample;
		}WavFormat;
	}FormatHead;
	char			ExtFormatInfo[2];
	struct FACT_BLOCK
	{
		char		szFactID[4];												// 'f','a','c','t'
		DWORD		dwFactSize;
	}FactHead;
	struct DATA_BLOCK
	{
		char		szDataID[4];
		DWORD		dwDataSize;
	}DataHead;
	DWORD			RIFFHeadOff,DataHeadOff;


	fp=fopen(FileName,"rb");
	if(!fp) return 0;

	memset((char*)&RiffHead,0,sizeof(RiffHead));
	memset((char*)&FormatHead,0,sizeof(FormatHead));
	memset((char*)ExtFormatInfo,0,sizeof(ExtFormatInfo));
	memset((char*)&FactHead,0,sizeof(FactHead));
	memset((char*)&DataHead,0,sizeof(DataHead));

																				//��ȡWave���ļ�ͷ
	RIFFHeadOff=0;
	fread((char*)&RiffHead,1,sizeof(RiffHead),fp);
	fread((char*)&FormatHead,1,sizeof(FormatHead),fp);
	if(FormatHead.dwFmtSize==18)
		fread((char*)ExtFormatInfo,1,sizeof(ExtFormatInfo),fp);
	fread((char*)&FactHead,1,sizeof(FactHead),fp);
	if(memcmp(FactHead.szFactID,"fact",4)==0)
	{
		fseek(fp,FactHead.dwFactSize,1);
		fread((char*)&DataHead,1,sizeof(DataHead),fp);
	}
	else
	{
		memcpy((char*)&DataHead,(char*)&FactHead,sizeof(DataHead));
		memset((char*)&FactHead,0,sizeof(FactHead));
	}
	DataHeadOff=ftell(fp)-sizeof(DataHead);

	if(iSize>=DataHead.dwDataSize&&pContent)
		fread(pContent,1,DataHead.dwDataSize,fp);
	fclose(fp);
	return DataHead.dwDataSize;
}


//	�Ӵ�·�����ļ�����ȡ��������ļ���
//	PathFileName:��·�����ļ���
//	RltFileName:��������Ĳ���·�����ļ���
//	RltSize:���ߴ�
bool CTools_Ansi::GetPureFileName(const char* pFileNameWithPath,char* pRltFileName,int RltSize)
{
	int Len,Off;

	if(!pFileNameWithPath||!pRltFileName) return false;

	pRltFileName[0]=0;

	Len=strlen(pFileNameWithPath);
	Off=Len;
	while(Off>0&&pFileNameWithPath[Off-1]!='\\'&&pFileNameWithPath[Off-1]!=':') 
		Off--;

	if(RltSize>0&&Len-Off>=RltSize)
		return false;

	memcpy(pRltFileName,pFileNameWithPath+Off,Len-Off);
	pRltFileName[Len-Off]=0;

	return true;
}
string CTools_Ansi::GetPureFileName(const string& FileNameWithPath)
{
	char buf[1024]={0};
	if(!GetPureFileName(FileNameWithPath.c_str(),buf,sizeof(buf)-1)) return "";
	return string(buf);
}

//	��ȫ·���ļ�����ȡ���̷�����־��:
bool CTools_Ansi::GetDiskSymbol(const char* pFileName,char* pRltDiskSymbol,int RltSize)
{
	char *pTemp;
	int Len;

	if(!pFileName||!pRltDiskSymbol) return false;

	pRltDiskSymbol[0]=0;

	pTemp=(char*)strstr(pFileName,":");
	if(!pTemp) return false;

	Len=pTemp-pFileName+1;
	if(RltSize>0&&Len>=RltSize) return false;
	
	memcpy(pRltDiskSymbol,pFileName,Len);
	pRltDiskSymbol[Len]=0;

	return true;
}

//	��ȫ·���ļ�����ȡ��·���������̷�
bool CTools_Ansi::GetFilePathWithoutDiskSymbol(char* pFileName,char* pRltFilePath,int RltSize)
{
	char *pTempHead;
	int OffHead;
	int Len;

	if(!pFileName||!pRltFilePath) return false;

	pRltFilePath[0]=0;

	pTempHead=strstr(pFileName,":");
	OffHead=0;
	if(pTempHead!=NULL)
		OffHead=pTempHead-pFileName+1;
	

	Len=strlen(pFileName);
	while(Len>0&&pFileName[Len-1]!='\\'&&pFileName[Len-1]!=':') 
		Len--;

	if(RltSize>0&&Len-OffHead>=RltSize)
		return false;

	memcpy(pRltFilePath,pFileName+OffHead,Len-OffHead);
	pRltFilePath[Len-OffHead]=0;

	if(Len-OffHead>0&&pRltFilePath[Len-OffHead-1]!='\\'&&(RltSize<=0||Len-OffHead<RltSize-1))
	{
		pRltFilePath[Len-OffHead]='\\';
		pRltFilePath[Len-OffHead+1]=0;
	}

	return true;
}

//	��ȫ·���ļ�����ȡ��·�������̷�
bool CTools_Ansi::GetFilePathWithDiskSymbol(char* pFileName,char* pRltFilePath,int RltSize)
{
	int Len;

	if(!pFileName||!pRltFilePath) return false;

	pRltFilePath[0]=0;

	Len=strlen(pFileName);
	while(Len>0&&pFileName[Len-1]!='\\'&&pFileName[Len-1]!=':') 
		Len--;

	if(RltSize>0&&Len>=RltSize)
		return false;

	memcpy(pRltFilePath,pFileName,Len);
	pRltFilePath[Len]=0;

	if(pRltFilePath[Len-1]!='\\'&&(RltSize<=0||Len<RltSize-1))
	{
		pRltFilePath[Len]='\\';
		pRltFilePath[Len+1]=0;
	}

	return true;
}



//	����Startt2��Endms1�ļ��ʱ��
int CTools_Ansi::GetDeltaMS(time_t Endt1,int Endms1,time_t Startt2,int Startms2)
{
	DWORD			DeltaSec;
	int				iRlt;

	if(Endt1>Startt2||Endt1==Startt2&&Endms1>=Startms2)
	{
		DeltaSec=(DWORD)(Endt1-Startt2);
		if(DeltaSec>(0x7fffffff-1000)/1000) iRlt=0x7fffffff;
		else iRlt=(int)DeltaSec*1000+(Endms1-Startms2);
		return iRlt;
	}
	else
	{
		DeltaSec=(DWORD)(Startt2-Endt1);
		if(DeltaSec>(0x7fffffff-1000)/1000) iRlt=0x7fffffff;
		else iRlt=(int)DeltaSec*1000+(Startms2-Endms1);
		return (-1)*iRlt;
	}
}


void CTools_Ansi::MyTrim(char*pStr)
{
	int				i,j,Len;

	for(i=0,Len=strlen(pStr);i<Len&&pStr[i]==' ';i++);
	for(j=Len;j>i&&pStr[j-1]==' ';j--);

	if(i>0)
	{
		memmove(pStr,pStr+i,j-i);
		memset(pStr+j-i,0,Len-(j-i));
	}
	else if(j<Len)
	{
		memset(pStr+j,0,Len-j);
	}
}
void CTools_Ansi::mytrimleft(string& str)
{
    str.erase(0,str.find_first_not_of(" "));
}

//ɾ�����ұߵĿո�
void CTools_Ansi::mytrimright(string& str)
{
    str.erase(str.find_last_not_of(" ") + 1);
}
//ɾ�����ұߵĿո�tab��\r��\n
void CTools_Ansi::mytrimright2(string& str)
{
	int len=str.size();
	if(len==0) return;
	const char* pstr=str.c_str();
	while(len>0&&(pstr[len-1]==' '||pstr[len-1]=='\t'||pstr[len-1]=='\r'||pstr[len-1]=='\n')) len--;
	if(len<(int)str.size())
		str.erase(len);
}
//ɾ�����ұߵĿո�tab��\r��\n������
void CTools_Ansi::mytrimrightdight(std::string& str)
{
	int len=str.size();
	if(len==0) return;
	const char* pstr=str.c_str();
	while(len>0&&(pstr[len-1]==' '||pstr[len-1]=='\t'||pstr[len-1]=='\r'||pstr[len-1]=='\n'||isdigit(pstr[len-1]))) len--;
	if(len<(int)str.size())
		str.erase(len);
}

void CTools_Ansi::mytrim(string& str)
{
    str.erase(0,str.find_first_not_of(" "));
    str.erase(str.find_last_not_of(" ") + 1);
}

//��ȡһ���ַ���trim�����Ч��ʼλ�ú���Ч����
void CTools_Ansi::mygettrimpos(const char* pstr,int&off,int&len)
{
    if(!pstr) { off=len=0;  return; }

    len=strlen(pstr);
    while(len>0&&pstr[len-1]==' ') len--;
    off=0;
    while(off<len&&pstr[off]==' ') off++;
    len-=off;
}

void CTools_Ansi::mymemcpy_trim(char* prlt,int rltsize,const char* psrc)
{
    if(!prlt||rltsize<=0||!psrc)
        return;

    int len,off;
    mygettrimpos(psrc,off,len);
    if(len>=rltsize) len=rltsize-1;

    if(len>0)
        memcpy(prlt,psrc+off,len);
    prlt[len]=0;
}


//�Ƚ�������������1,0,-1��
int CTools_Ansi::mycompare_trynumeric(const char* str1,const char* str2)
{
    if(!str1||!str2) return -1;

    char *endptr1=NULL,*endptr2=NULL;

    //�ȳ���ת����double���бȽ�
    double d1=strtod(str1,&endptr1);
    double d2=strtod(str2,&endptr2);
    if((endptr1==NULL||endptr1[0]==0)&&(endptr2==NULL||endptr2[0]==0))
    {
        //��ʾת����double�ɹ�
        if(d1==d2) return 0;
        else return (d1>d2?1:-1);
    }

    //�ٳ���ת����long���бȽ�
    endptr1=endptr2=NULL;
    long l1=strtol(str1,&endptr1,0);
    long l2=strtol(str2,&endptr2,0);
    if((endptr1==NULL||endptr1[0]==0)&&(endptr2==NULL||endptr2[0]==0))
    {
        //��ʾת����long�ɹ�
        if(l1==l2) return 0;
        else return (l1>l2?1:-1);
    }

    //����ַ����Ƚ�
    int irlt=strcmp(str1,str2);
    if(irlt==0) return 0;
    else if(irlt>0) return 1;
    else return -1;
}



//�Ƚ�������������1,0,-1��
int CTools_Ansi::mycompare(const string& str1,const string& str2)
{
    int irlt=str1.compare(str2);
    if(irlt==0) return 0;
    else if(irlt>0) return 1;
    else return -1;
}

//�Ƚ�������������1,0,-1��
int CTools_Ansi::mycompare2(const char* str1,const char* str2)
{
    if(!str1||!str2) return -1;

    int irlt=strcmp(str1,str2);
    if(irlt==0) return 0;
    else if(irlt>0) return 1;
    else return -1;
}

//�жϴ��Ƿ�ȫ��������
bool CTools_Ansi::isdigitstring(const char* str,int len)
{
	if(len==0) len=strlen(str);
	for(int i=0;i<len;i++)
	{
		if(!isdigit((int)str[i])) return false;
	}
	return true;
}

//	ȡ��ǰ��ʱ�䣬����time_t��������int�ĺ�����
void CTools_Ansi::GetComplexAnsiTime(time_t *pRltSecs,int *pRltMS)
{
	if(pRltSecs&&!pRltMS)
		time(pRltSecs);
	else
	{
		struct _timeb	itime;
		_ftime(&itime);
		if(pRltSecs) *pRltSecs=itime.time;
		if(pRltMS) *pRltMS=itime.millitm;
	}
}





//	���ַ�����ȡ��time_tʱ��
//	���ڸ�ʽΪ��xxxx��xx��xx�գ� xxxx/xx/xx�� xxxx-xx-xx
//	ʱ���ʽΪ��xxʱxx��xx�룻 xx:xx:xx�� xx:xx
time_t	CTools_Ansi::GetAnsiTimeFromString(char *pBuf)
{
	struct tm		*ptm;
	time_t			itime;
	int				iYear,iMon,iDay,iHour,iMin,iSec;
	char			*pYear,*pMon,*pDay,*pHour,*pSec,*pp;

	time(&itime);
	ptm=localtime(&itime);

	iYear=ptm->tm_year+1900;
	iMon=ptm->tm_mon+1;
	iDay=ptm->tm_mday;
	iHour=ptm->tm_hour;
	iMin=ptm->tm_min;
	iSec=ptm->tm_sec;

	pYear=strstr(pBuf,"��");
	if(!pYear) pYear=strstr(pBuf,"/");
	if(!pYear) pYear=strstr(pBuf,"-");
	if(pYear)
	{
		pp=pYear;
		while(pp>pBuf&&*(pp-1)==' ') pp--;
		while(pp>pBuf&&*(pp-1)>='0'&&*(pp-1)<='9') pp--;
		iYear=atoi(pp);
	}

	pMon=strstr(pBuf,"��");
	if(!pMon&&pYear)
	{
		if(*pYear=='/') pMon=strstr(pYear+1,"/");
		else if(*pYear=='-') pMon=strstr(pYear+1,"-");
	}
	if(pMon)
	{
		pp=pMon;
		while(pp>pBuf&&*(pp-1)==' ') pp--;
		while(pp>pBuf&&*(pp-1)>='0'&&*(pp-1)<='9') pp--;
		iMon=atoi(pp);
	}

	pDay=strstr(pBuf,"��");
	if(pDay)
	{
		pp=pDay;
		while(pp>pBuf&&*(pp-1)==' ') pp--;
		while(pp>pBuf&&*(pp-1)>='0'&&*(pp-1)<='9') pp--;
		iDay=atoi(pp);
	}
	else if(pMon)
	{
		if(*pMon=='/') pp=pMon+1;
		if(*pMon=='-') pp=pMon+1;
		while(pp[0]!=0&&pp[0]==' ') pp++;
		iDay=atoi(pp);
	}

	pHour=strstr(pBuf,":");
	if(pHour)
	{
		pp=pHour;
		while(pp>pBuf&&*(pp-1)==' ') pp--;
		while(pp>pBuf&&*(pp-1)>='0'&&*(pp-1)<='9') pp--;
		iHour=atoi(pp);

		pp=pHour+1;
		while(pp[0]!=0&&pp[0]==' ') pp++;
		iMin=atoi(pp);

		pSec=strstr(pHour+1,":");
		if(pSec)
		{
			pp=pSec+1;
			while(pp[0]!=0&&pp[0]==' ') pp++;
			iSec=atoi(pp);
		}
	}

	return MakeAnsiTime(iYear,iMon,iDay,iHour,iMin,iSec);

	
}

//	����һ��time_tʱ��
time_t CTools_Ansi::MakeAnsiTime(int wYear,int wMon,int wDay,int wHour,int wMin,int wSec)
{
	struct tm		itm;

	if(wYear<1970) wYear=1970;
	if(wYear>2038) wYear=2038;
	if(wMon<1) wMon=1;
	if(wMon>12) wMon=12;
	if(wDay<1) wDay=1;
	if(wDay>31) wDay=31;
	if(wHour<0) wHour=0;
	if(wHour>23) wHour=23;
	if(wMin<0) wMin=0;
	if(wMin>59) wMin=59;
	if(wSec<0) wSec=0;
	if(wSec>59) wSec=59;

	memset(&itm,0,sizeof(itm));
	itm.tm_year=wYear-1900;
	itm.tm_mon=wMon-1;
	itm.tm_mday=wDay;
	itm.tm_hour=wHour;
	itm.tm_min=wMin;
	itm.tm_sec=wSec;

	return mktime(&itm);
}

//	��time_t��itimeMS��ʾ��ʱ��ת����yyyy-mm-dd hh:mm:ss.xxx���ַ���
//	GetPartMap:Ҫȡ��ʱ�䲿�֣���λ��ʾ���ӵ��ұ�0λ��ʼ��ʾ���ꡢ�¡��ա�ʱ���֡��롢����
char* CTools_Ansi::GetAnsiTimeString(char *pBuf,time_t itime,unsigned int itimeMS,unsigned int GetPartMap)
{
	struct tm		*ptm;
	int				Len;

	if(!pBuf) return NULL;
	pBuf[0]=0;

	if(itime==0)
		return pBuf;

	ptm=localtime(&itime);
	Len=0;
	if(ptm&&itime) 
	{
		if((GetPartMap&1)==1) { sprintf(pBuf+Len,"%04d-",ptm->tm_year+1900);  Len=strlen(pBuf); }
		if((GetPartMap&2)==2) { sprintf(pBuf+Len,"%02d-",ptm->tm_mon+1);  Len=strlen(pBuf); }
		if((GetPartMap&4)==4) { sprintf(pBuf+Len,"%02d",ptm->tm_mday);  Len=strlen(pBuf); }
		if(Len>0&&pBuf[Len-1]=='-') { pBuf[Len-1]=0; Len--; }
		if(Len>0) { strcat(pBuf," ");  Len++; }

		if((GetPartMap&8)==8) { sprintf(pBuf+Len,"%02d:",ptm->tm_hour);  Len=strlen(pBuf); }
		if((GetPartMap&16)==16) { sprintf(pBuf+Len,"%02d:",ptm->tm_min);  Len=strlen(pBuf); }
		if((GetPartMap&32)==32) { sprintf(pBuf+Len,"%02d",ptm->tm_sec);  Len=strlen(pBuf); }
		if((GetPartMap&64)==64) { sprintf(pBuf+Len,".%03d",itimeMS);  Len=strlen(pBuf); }
		if(Len>0&&pBuf[Len-1]==':') { pBuf[Len-1]=0; Len--; }
	}
	return pBuf;
}



//  ���ַ�����ʾ��ʱ��ת����utc��time_tʱ��
//  pDate:yyyymmdd
//  pTime:hh:mm:ss �� hhmmss
time_t CTools_Ansi::Get_time_t_utc_from_strTime(const char* pDate, const char* pTime)
{
    int iYear,iMon,iDay,iHour,iMin,iSec;
    struct tm itm;
    time_t itime;

    if(!pDate&&!pTime) return 0;

    if(!pDate||!pDate[0]) 
    {
        SYSTEMTIME CurTime;
        GetLocalTime(&CurTime);
        iYear=CurTime.wYear;
        iMon=CurTime.wMonth;
        iDay=CurTime.wDay;
    }
    else 
    {
        sscanf(pDate,"%04d%02d%02d",&iYear,&iMon,&iDay);
    }

    if(!pTime||!pTime[0]) 
        iHour=iMin=iSec=0;
    else if(pTime[2]==':'&&pTime[5]==':')
        sscanf(pTime,"%02d:%02d:%02d",&iHour,&iMin,&iSec);
    else
        sscanf(pTime,"%02d%02d%02d",&iHour,&iMin,&iSec);

    if(iYear<1970||iYear>2030||iMon<1||iMon>12||iDay<1||iDay>31||iHour<0||iHour>23||iMin<0||iMin>59||iSec<0||iSec>59) 
        return 0;

    memset(&itm,0,sizeof(itm));
    itm.tm_year=iYear-1900;
    itm.tm_mon=iMon-1;
    itm.tm_mday=iDay;
    itm.tm_hour=iHour;
    itm.tm_min=iMin;
    itm.tm_sec=iSec;

    itime=mktime(&itm);                                     //�õ�utcʱ��

    return itime;
}

/// ��ʱ���ַ���תΪ����
/// pTime:hhmmss �� hh:mm:ss
unsigned int CTools_Ansi::CalculateTotalSeconds(const char* pTime)
{
	if(pTime==NULL || pTime[0]=='\0')
		return 0;

	int iHour=0;
	int iMin=0;
	int iSec=0;
	unsigned int len=strlen(pTime);
	if(len==6)
	{
		sscanf(pTime,"%02d%02d%02d",&iHour,&iMin,&iSec);
	}
	else if(len==8 && pTime[2]==':'&&pTime[5]==':')
	{
		sscanf(pTime,"%02d:%02d:%02d",&iHour,&iMin,&iSec);
	}

	if(iHour<0||iHour>23||iMin<0||iMin>59||iSec<0||iSec>59)
		return 0;

	return (iHour*3600+iMin*60+iSec);

}


//  ��utc��time_tʱ��ת�����ַ�����ʾ��ʱ��
//  pRltDate:yyyymmdd��Ҫ��֤�㹻�Ŀռ�
//  pRltTime:hh:mm:ss��Ҫ��֤�㹻�Ŀռ�
void CTools_Ansi::Get_strTime_from_utc(time_t iTime,char* pRltDate,char* pRltTime)
{
    struct tm *ptm;
    ptm=localtime(&iTime);
    if(!ptm) return;

    if(pRltDate)
        sprintf(pRltDate,"%04d%02d%02d",ptm->tm_year+1900,ptm->tm_mon+1,ptm->tm_mday);
    if(pRltTime)
        sprintf(pRltTime,"%02d:%02d:%02d",ptm->tm_hour,ptm->tm_min,ptm->tm_sec);
}
//  utcת��Ϊhh:mm:ss
string CTools_Ansi::Get_strTime_from_utc2(time_t iTime)
{
    if(!iTime) return string("");
    struct tm *ptm;
    ptm=localtime(&iTime);
    if(!ptm) return string("");

    char buf[32]={0};
    sprintf(buf,"%02d:%02d:%02d",ptm->tm_hour,ptm->tm_min,ptm->tm_sec);
    return string(buf);
}
//  utcת��ΪSun, 5 Jan 2014 10:22:33 GMT
string CTools_Ansi::Get_strTime_from_utc3(time_t iTime)
{
    char buf[256]={0};
    struct tm igmt=*gmtime(&iTime);
	switch(igmt.tm_wday)
	{
		case 0:	strcat(buf,"Sun, ");  break;
		case 1:	strcat(buf,"Mon, ");  break;
		case 2:	strcat(buf,"Tue, ");  break;
		case 3:	strcat(buf,"Wed, ");  break;
		case 4:	strcat(buf,"Thu, ");  break;
		case 5:	strcat(buf,"Fri, ");  break;
		case 6:	strcat(buf,"Sat, ");  break;
	}
	sprintf(buf+strlen(buf),"%d ",igmt.tm_mday);
	switch(igmt.tm_mon+1)
	{
		case 1: strcat(buf,"Jan ");  break;
		case 2: strcat(buf,"Feb ");  break;
		case 3: strcat(buf,"Mar ");  break;
		case 4: strcat(buf,"Apr ");  break;
		case 5: strcat(buf,"May ");  break;
		case 6: strcat(buf,"Jun ");  break;
		case 7: strcat(buf,"Jul ");  break;
		case 8: strcat(buf,"Aug ");  break;
		case 9: strcat(buf,"Seq ");  break;
		case 10: strcat(buf,"Oct ");  break;
		case 11: strcat(buf,"Nov ");  break;
		case 12: strcat(buf,"Dec ");  break;
	}
	sprintf(buf+strlen(buf),"%d %02d:%02d:%02d GMT",igmt.tm_year+1900,igmt.tm_hour,igmt.tm_min,igmt.tm_sec);
    return string(buf);
}

//  ��utc��time_tʱ��ת�����ַ�����ʾ��ʱ��, ��ʽΪyyyy-mm-dd
void CTools_Ansi::Get_strDate_from_utc(time_t iTime,char* pRltDate)
{
    struct tm *ptm;
    ptm=localtime(&iTime);
    if(!ptm) return;

    if(pRltDate)
        sprintf(pRltDate,"%04d-%02d-%02d",ptm->tm_year+1900,ptm->tm_mon+1,ptm->tm_mday);
}
//	��utc��time_tʱ�������ת��Ϊ������, ��ʽΪyyyymmdd����20140511
int CTools_Ansi::Get_intDate_from_utc(time_t iTime)
{
    struct tm *ptm;
    ptm=localtime(&iTime);
    if(!ptm) return -1;

	return (ptm->tm_year+1900)*10000+(ptm->tm_mon+1)*100+ptm->tm_mday;
}


//  ��utc��time_tʱ��ת���ɱ���ʱ��
void CTools_Ansi::Get_DateTime_from_utc(time_t iTime,int* pRltYear,int* pRltMonth,int* pRltDay,int* pRltHour,int* pRltMinutes,int * pRltSecs,int* pRltWeekDay)
{
    struct tm *ptm;

    if(pRltYear) *pRltYear=0;
    if(pRltMonth) *pRltMonth=0;
    if(pRltDay) *pRltDay=0;
    if(pRltHour) *pRltHour=0;
    if(pRltMinutes) *pRltMinutes=0;
    if(pRltSecs) *pRltSecs=0;
    if(pRltWeekDay) *pRltWeekDay=0;

    ptm=localtime(&iTime);
    if(!ptm) return;

    if(pRltYear) *pRltYear=ptm->tm_year+1900;
    if(pRltMonth) *pRltMonth=ptm->tm_mon+1;
    if(pRltDay) *pRltDay=ptm->tm_mday;
    if(pRltHour) *pRltHour=ptm->tm_hour;
    if(pRltMinutes) *pRltMinutes=ptm->tm_min;
    if(pRltSecs) *pRltSecs=ptm->tm_sec;
    if(pRltWeekDay) *pRltWeekDay=ptm->tm_wday;
}
//  ������ʱ��ת����utcʱ��
time_t CTools_Ansi::Get_utc_from_DateTime(int year,int month,int day,int hour,int minutes,int secs)
{
    struct tm itm;

    memset(&itm,0,sizeof(itm));
    itm.tm_year=year-1900;
    itm.tm_mon=month-1;
    itm.tm_mday=day;
    itm.tm_hour=hour;
    itm.tm_min=minutes;
    itm.tm_sec=secs;

    return mktime(&itm);                                     //�õ�utcʱ��
}


//  ���ַ�����ʾ��ʱ��ת���ɵ���00:00:00��ʼ������
//  pTime:hhmmss �� hh:mm:ss ��hh:mm �� h:mm �� h:m �� hh:m
int CTools_Ansi::Get_TodaySecs_from_strTime(char* pTime)
{
    int iHour=0,iMin=0,iSec=0;

    if(!pTime) return 0;

    if(pTime[2]==':'&&pTime[5]==':')
        sscanf(pTime,"%02d:%02d:%02d",&iHour,&iMin,&iSec);
    else if(strlen(pTime)==6)
        sscanf(pTime,"%02d%02d%02d",&iHour,&iMin,&iSec);
    else if(strlen(pTime)==5&&pTime[2]==':')
        sscanf(pTime,"%02d:%02d",&iHour,&iMin);
    else if(strlen(pTime)==4&&pTime[1]==':')
        sscanf(pTime,"%01d:%02d",&iHour,&iMin);
    else if(strlen(pTime)==3&&pTime[1]==':')
        sscanf(pTime,"%01d:%01d",&iHour,&iMin);
    else if(strlen(pTime)==4&&pTime[2]==':')
        sscanf(pTime,"%02d:%01d",&iHour,&iMin);

    if(iHour<0||iHour>23||iMin<0||iMin>59||iSec<0||iSec>59) 
        return 0;

    return iHour*3600+iMin*60+iSec;
}


//	��һ����ֵת���ɶ����Ʊ�ʾ���ַ���
//	ת����������ҵ����˳�����У�bit0��pRlt[BitNum-1]
char* CTools_Ansi::GetBinFormatString(char *pRlt,unsigned int Val,unsigned int BitNum)
{
	unsigned int	i;

	if(!pRlt) return NULL;

	if(BitNum>32) BitNum=32;
	memset(pRlt,0,BitNum+1);
	for(i=0;i<BitNum;i++)
	{
		if( ( Val & ((unsigned int)1<<i) ) != 0 )
			pRlt[BitNum-1-i]='1';
		else 
			pRlt[BitNum-1-i]='0';
	}
	return pRlt;
}

//	��һ����ֵת���ɶ����Ʊ�ʾ���ַ���
//	ת������������ҵ�˳�����У�bit0��pRlt[0]
char* CTools_Ansi::GetBinFormatString2(char *pRlt,unsigned int Val,unsigned int BitNum)
{
	unsigned int	i;

	if(!pRlt) return NULL;

	if(BitNum>32) BitNum=32;
	memset(pRlt,0,BitNum+1);
	for(i=0;i<BitNum;i++)
	{
		if( ( Val & ((unsigned int)1<<i) ) != 0 )
			pRlt[i]='1';
		else 
			pRlt[i]='0';
	}
	return pRlt;
}

//  ��һ���ڴ�ת����Hex�ַ���
string CTools_Ansi::GetHexStringFromMem(const void* pMem,int MemLen)
{
    char buf[512];
    char *prlt=buf;
    if(MemLen*2+1>(int)sizeof(buf)) prlt=(char*)malloc(MemLen*2+1);
    if(!prlt) return std::string("");

    int i;
    for(i=0;i<MemLen;i++) sprintf(prlt+i*2,"%02x",((unsigned char*)pMem)[i]);
    prlt[i*2]=0;
    std::string strRlt=string(prlt);
    if(MemLen*2+1>(int)sizeof(buf)) free(prlt);

    return strRlt;
}

//  ��Hex�ַ���ת�ɳ��ڴ档���ؽ���ֽڳ���
int CTools_Ansi::GetMemFromHexString(void* pMem,int MemSize,const string& strHex)
{
    const char* pHex=(const char*)strHex.c_str();
    int i,j;
    for(i=0;i<(int)strHex.length()/2&&i<MemSize;i++)
    {
        sscanf(pHex+i*2,"%02x",&j);
        ((unsigned char*)pMem)[i]=(unsigned char)j;
    }
    return i;
}
int CTools_Ansi::GetMemFromHexString(void* pMem,int MemSize,const char* pszHex,int HexLen)
{
    int i,j;
    for(i=0;i<HexLen/2&&i<MemSize;i++)
    {
        sscanf(pszHex+i*2,"%02x",&j);
        ((unsigned char*)pMem)[i]=(unsigned char)j;
    }
    return i;
}
//  ��doubleת����Hex�ַ���
string CTools_Ansi::GetHexStringFromDouble(double Val)
{
    return GetHexStringFromMem(&Val,sizeof(Val));
}
//  ��Hex�ַ���ת��double�����ؽ���ֽڳ���
double CTools_Ansi::GetDoubleFromHexString(const string& strHex)
{
    double rlt=0;
    GetMemFromHexString(&rlt,sizeof(rlt),strHex);
    return rlt;
}
double CTools_Ansi::GetDoubleFromHexString(const char* pszHex,int HexLen)
{
    double rlt=0;
    GetMemFromHexString(&rlt,sizeof(rlt),pszHex,HexLen);
    return rlt;
}

//  ������ת����ʮ�����ַ���
string CTools_Ansi::GetStringFromInteger(int Val)
{
    char buf[256]={0};
    itoa(Val,buf,10);
    return string(buf);
}
//  ʮ�����ַ���ת��Ϊ����
int CTools_Ansi::GetIntegerFromString(const string& strVal)
{
    return atoi(strVal.c_str());
}
int CTools_Ansi::GetIntegerFromString(const char* pszVal)
{
    return atoi(pszVal);
}
//  ��λʮ�������ַ���ת��Ϊ����
unsigned char CTools_Ansi::GetByteFromHexString(const string& strHex)
{
	unsigned char rlt=0;
	CTools_Ansi::GetMemFromHexString(&rlt,1,strHex);
	return rlt;
}


//	����ĺ���InternalLookupInFieldIndex()��ʹ�ã����ڼ���iMid��iHead��iTail
//	ʹ�õ����±�־:
//	LookupMidCompleteID;					//���ַ���Mid���
//	LookupHeadID;							//���ַ���ͷ
//	LookupHeadCompleteID;					//��ͷ���
//	LookupHeadBackwardOneByOneID;			//��ǰһ��һ���ľ�ȷ���ҵ�һ��������Mid��mid
//	LookupHeadForwardOneByOneID;			//���һ��һ���ľ�ȷ���ҵ�һ������Mid��mid
//	LookupTailID;							//���ַ���β
//	LookupTailCompleteID;					//��β���
//	LookupTailBackwardOneByOneID;			//��ǰһ��һ���ľ�ȷ���ҵ�һ������Mid��mid
//	LookupTailForwardOneByOneID;			//���һ��һ���ľ�ȷ���ҵ�һ��������Mid��mid
//	����ĺ���InternalLookupInFieldIndex()��ʹ�ã����ڼ���Mid��Head��Tail���������CmpRlt��iHead��iTail��iMid��
#define CalculateMid_LookupInSequenceBuffer															\
{																									\
	if(LookupMidCompleteID==0)																		\
	{																								\
		Calculate_GetMid_LookupInSequenceBuffer;													\
	}																								\
	else																							\
	{																								\
		if(LookupHeadID==1&&LookupHeadCompleteID==0)												\
		{																							\
			Calculate_GetHead_LookupInSequenceBuffer;												\
		}																							\
		else if(LookupTailID==1&&LookupTailCompleteID==0)											\
		{																							\
			Calculate_GetTail_LookupInSequenceBuffer;												\
		}																							\
		if((LookupHeadID==0||LookupHeadCompleteID==1)&&(LookupTailID==0||LookupTailCompleteID==1))	\
		{																							\
			CmpRlt=0;																				\
			break;																					\
		}																							\
	}																								\
}



//	����ĺ���InternalLookupInFieldIndex()��ʹ�ã����ڼ���Mid��Head��Tail���������CmpRlt��iHead��iTail��iMid��
//	�˺����ڼ�����ַ���Mid���ڻ�ȡf(Mid)=pSour��Midʱ����
#define Calculate_GetMid_LookupInSequenceBuffer														\
{																									\
	if(CmpRlt>0&&Head!=Mid) { Head=Mid;  Mid=(Head+Tail)/2; }										\
	else if(CmpRlt>0&&Head==Mid)																	\
	{																								\
		CmpRlt=-1;  LookupMidCompleteID=1;															\
		iHead=Head;  iTail=Tail;  iMid=Mid;															\
		break;																						\
	}																								\
	else if(CmpRlt<0&&Tail!=Mid) { Tail=Mid;  Mid=(Head+Tail)/2; }									\
	else if(CmpRlt<0&&Tail==Mid)																	\
	{																								\
		Head--; CmpRlt=-1; LookupMidCompleteID=1;													\
		iHead=Head;  iTail=Tail;  iMid=Mid;															\
		break;																						\
	}																								\
	else																							\
	{																								\
		iHead=Head;																					\
		iTail=Tail;																					\
		iMid=Mid;																					\
		LookupMidCompleteID=1;																		\
		if(pLastHead) { LookupHeadID=1;  Head=iHead;  Tail=iMid;  Mid=(Head+Tail)/2; }				\
		else if(pLastTail) { LookupTailID=1;  Head=iMid;  Tail=iTail;  Mid=(Head+Tail)/2; }			\
		else break; 																				\
	}																								\
}



//	����ĺ���InternalLookupInFieldIndex()��ʹ�ã����ڼ���Mid��Head��Tail���������CmpRlt��iHead��iTail��iMid��
//	�˺����ھ�ȷ����f(iMid)==pSourʱ��Head���ڻ�ȡf(iMid)=pSour��iMid�����
#define Calculate_GetHead_LookupInSequenceBuffer													\
{																									\
	if(LookupHeadBackwardOneByOneID==0&&LookupHeadForwardOneByOneID==0)								\
	{																								\
		if(CmpRlt==0&&Tail!=Mid) { Tail=Mid;  Mid=(Head+Tail)/2;  }									\
		else if(CmpRlt==0&&Tail==Mid) { LookupHeadBackwardOneByOneID=1; }							\
		else if(CmpRlt!=0&&Head!=Mid) { Head=Mid;  Mid=(Head+Tail)/2; }								\
		else if(CmpRlt!=0&&Head==Mid) { LookupHeadBackwardOneByOneID=1; }							\
	}																								\
	if(LookupHeadBackwardOneByOneID==1&&LookupHeadForwardOneByOneID==0)								\
	{																								\
		if(Mid<=0) { Mid=0;  LookupHeadForwardOneByOneID=1; }										\
		else if(CmpRlt!=0) { LookupHeadForwardOneByOneID=1; }										\
		else																						\
		{																							\
			Mid--;																					\
			if(Mid<=0) { Mid=0;  LookupHeadForwardOneByOneID=1; }									\
		}																							\
	}																								\
	if(LookupHeadBackwardOneByOneID==1&&LookupHeadForwardOneByOneID==1)								\
	{																								\
		if(Mid>=iMid) { Mid=iMid;  LookupHeadCompleteID=1; }										\
		else if(CmpRlt==0) LookupHeadCompleteID=1;													\
		else																						\
		{																							\
			Mid++;																					\
			if(Mid>=iMid) { Mid=iMid;  LookupHeadCompleteID=1; }									\
		}																							\
																									\
		if(LookupHeadCompleteID)																	\
		{																							\
			if(Mid<0) Mid=0;																		\
			if(Mid>iMid) Mid=iMid;																	\
			iHead=Mid;																				\
																									\
			if(pLastTail) { LookupTailID=1;  Head=iMid;  Tail=iTail;  Mid=(Head+Tail)/2; }			\
			else { CmpRlt=0;  break; }																\
		}																							\
	}																								\
}


//	����ĺ���InternalLookupInFieldIndex()��ʹ�ã����ڼ���Mid��Head��Tail���������CmpRlt��iHead��iTail��iMid��
//	�˺����ھ�ȷ����f(iMid)==pSourʱ��Tail���ڻ�ȡf(iMid)=pSour��iMid�����
#define Calculate_GetTail_LookupInSequenceBuffer													\
{																									\
	if(LookupTailBackwardOneByOneID==0&&LookupTailForwardOneByOneID==0)								\
	{																								\
		if(CmpRlt==0&&Head!=Mid) { Head=Mid;  Mid=(Head+Tail)/2;  }									\
		else if(CmpRlt==0&&Head==Mid) { LookupTailBackwardOneByOneID=1; }							\
		else if(CmpRlt!=0&&Tail!=Mid) { Tail=Mid;  Mid=(Head+Tail)/2; }								\
		else if(CmpRlt!=0&&Tail==Mid) { LookupTailBackwardOneByOneID=1; }							\
	}																								\
	if(LookupTailBackwardOneByOneID==1&&LookupTailForwardOneByOneID==0)								\
	{																								\
		if(Mid<=iMid) { Mid=iMid;  LookupTailForwardOneByOneID=1; }									\
		else if(CmpRlt==0) { LookupTailForwardOneByOneID=1; }										\
		else																						\
		{																							\
			Mid--;																					\
			if(Mid<=iMid) { Mid=iMid;  LookupTailForwardOneByOneID=1; }								\
		}																							\
	}																								\
	if(LookupTailBackwardOneByOneID==1&&LookupTailForwardOneByOneID==1)								\
	{																								\
		if(Mid>=UnitNum) { Mid=UnitNum;  LookupTailCompleteID=1; }					\
		else if(CmpRlt!=0) LookupTailCompleteID=1;													\
		else																						\
		{																							\
			Mid++;																					\
			if(Mid>=UnitNum) { Mid=UnitNum;  LookupTailCompleteID=1; }				\
		}																							\
																									\
		if(LookupTailCompleteID)																	\
		{																							\
			if(Mid<=iMid) Mid=iMid+1;																\
			if(Mid>UnitNum) Mid=UnitNum;												\
			iTail=Mid;																				\
			CmpRlt=0;																				\
			break;																					\
		}																							\
	}																								\
}




//	�ö��ַ���һ������Ļ����������һ���ַ���
//	�����Ǵ�С����
//	��Сд�޹�
//	1. ���ҵ�����ֵ�����������������е���ţ�pLastHead�ǵ�һ������������λ�ã�pLastTail�ǵ�һ��������������λ�ã�pLastHead<=x<pLastTail����������
//	2. ���Ҳ���������-1��pLastHead��pLastTail�ǰ���ָ���ַ�����������ֵ *pLastHead=(-1 ~ Max-1) *pLastTail=(0 ~ Max)
int CTools_Ansi::LookupInSequenceBuffer_Mem(char *SeqBuf,int UnitNum,int UnitSize,char *Str,int Len,int *pLastHead,int *pLastTail)
{
	int				Head,Tail,Mid,iHead,iTail,iMid,CmpRlt;
	int				LookupMidCompleteID;					//���ַ���Mid���
	int				LookupHeadID;							//���ַ���ͷ
	int				LookupHeadCompleteID;					//��ͷ���
	int				LookupHeadBackwardOneByOneID;			//��ǰһ��һ���ľ�ȷ���ҵ�һ��������Mid��mid
	int				LookupHeadForwardOneByOneID;			//���һ��һ���ľ�ȷ���ҵ�һ������Mid��mid
	int				LookupTailID;							//���ַ���β
	int				LookupTailCompleteID;					//��β���
	int				LookupTailBackwardOneByOneID;			//��ǰһ��һ���ľ�ȷ���ҵ�һ������Mid��mid
	int				LookupTailForwardOneByOneID;			//���һ��һ���ľ�ȷ���ҵ�һ��������Mid��mid

	if(Len>UnitSize) return -1;

	Head=0;
	Tail=UnitNum;
	Mid=(Head+Tail)/2;

	LookupMidCompleteID=0;									//���ַ���Mid���
	LookupHeadID=0;											//���ַ���ͷ
	LookupHeadCompleteID=0;									//��ͷ���
	LookupHeadBackwardOneByOneID=0;							//��ǰһ��һ���ľ�ȷ���ҵ�һ��������Mid��mid
	LookupHeadForwardOneByOneID=0;							//���һ��һ���ľ�ȷ���ҵ�һ������Mid��mid
	LookupTailID=0;											//���ַ���β
	LookupTailCompleteID=0;									//��β���
	LookupTailBackwardOneByOneID=0;							//��ǰһ��һ���ľ�ȷ���ҵ�һ������Mid��mid
	LookupTailForwardOneByOneID=0;							//���һ��һ���ľ�ȷ���ҵ�һ��������Mid��mid
	
	while(1)
	{
		CmpRlt=_memicmp(Str,SeqBuf+Mid*UnitSize,Len);
		CalculateMid_LookupInSequenceBuffer;
	}
	if(pLastHead) *pLastHead=Head;
	if(pLastTail) *pLastTail=Tail;

	if(CmpRlt==0) return iMid;
	else return -1;
}

//	�ö��ַ���һ������Ļ����������һ��DWORD
//	���ҵ���DWORD���������ڻ����������ţ����򷵻�-1��pLastHead��pLastTail�ǰ���ָ���ַ�����������ֵ
//	�����Ǵ�С����
//	��Сд�޹�
int CTools_Ansi::LookupInSequenceBuffer_DWORD(char *SeqBuf,int UnitNum,int UnitSize,unsigned int dwID,int *pLastHead,int *pLastTail)
{
	int				Head,Tail,Mid,iHead,iTail,iMid,CmpRlt;
	int				LookupMidCompleteID;					//���ַ���Mid���
	int				LookupHeadID;							//���ַ���ͷ
	int				LookupHeadCompleteID;					//��ͷ���
	int				LookupHeadBackwardOneByOneID;			//��ǰһ��һ���ľ�ȷ���ҵ�һ��������Mid��mid
	int				LookupHeadForwardOneByOneID;			//���һ��һ���ľ�ȷ���ҵ�һ������Mid��mid
	int				LookupTailID;							//���ַ���β
	int				LookupTailCompleteID;					//��β���
	int				LookupTailBackwardOneByOneID;			//��ǰһ��һ���ľ�ȷ���ҵ�һ������Mid��mid
	int				LookupTailForwardOneByOneID;			//���һ��һ���ľ�ȷ���ҵ�һ��������Mid��mid

	Head=0;
	Tail=UnitNum;
	Mid=(Head+Tail)/2;

	LookupMidCompleteID=0;									//���ַ���Mid���
	LookupHeadID=0;											//���ַ���ͷ
	LookupHeadCompleteID=0;									//��ͷ���
	LookupHeadBackwardOneByOneID=0;							//��ǰһ��һ���ľ�ȷ���ҵ�һ��������Mid��mid
	LookupHeadForwardOneByOneID=0;							//���һ��һ���ľ�ȷ���ҵ�һ������Mid��mid
	LookupTailID=0;											//���ַ���β
	LookupTailCompleteID=0;									//��β���
	LookupTailBackwardOneByOneID=0;							//��ǰһ��һ���ľ�ȷ���ҵ�һ������Mid��mid
	LookupTailForwardOneByOneID=0;							//���һ��һ���ľ�ȷ���ҵ�һ��������Mid��mid
	
	while(1)
	{
		if(dwID>(*(unsigned int*)(SeqBuf+Mid*UnitSize))) CmpRlt=1;
		else if(dwID<(*(unsigned int*)(SeqBuf+Mid*UnitSize))) CmpRlt=-1;
		else CmpRlt=0;
		
		CalculateMid_LookupInSequenceBuffer;
	}
	if(pLastHead) *pLastHead=Head;
	if(pLastTail) *pLastTail=Tail;

	if(CmpRlt==0) return iMid;
	else return -1;
}
#undef	CalculateMid_LookupInSequenceBuffer
#undef	Calculate_GetMid_LookupInSequenceBuffer
#undef	Calculate_GetTail_LookupInSequenceBuffer
#undef	Calculate_GetHead_LookupInSequenceBuffer



//	�ö��ַ���һ������Ļ��������������
//	�����Ǵ�С����
//  �������RltBegin��RltEnd�У���ʾ��һ������������λ�ú͵�һ��������������λ�á�(������ȣ���ʾû�ҵ�)
void CTools_Ansi::LookupInSequenceBuffer(int& RltBegin,int& RltEnd,
                                         const void* pData,int UnitNum,int UnitSize,
                                         const void* pLookupContent,
                                         COMPARE_LookupInSequenceBuffer CompareMethod)
{
	int				Head,Tail,Mid,iHead,iTail,iMid,CmpRlt;

    if(UnitNum<=0)
    {
        RltBegin=RltEnd=0;
        return;
    }

    Head=0;
	Tail=UnitNum;         //����ʱ������Tail
	Mid=(Head+Tail)/2;

    //�Ȳ���ָ�����ݡ����ҹ����У�Head<=LookupContent<Tail
    while(1)
    {
        CmpRlt=CompareMethod(pLookupContent,(const char*)pData+Mid*UnitSize);

	    if(CmpRlt>0&&Mid!=Head) { Head=Mid;  Mid=(Head+Tail)/2; }
	    else if(CmpRlt<0&&Mid!=Tail) { Tail=Mid;  Mid=(Head+Tail)/2; }
	    else if(CmpRlt!=0)
	    {   
            //��ʾҪ���ҵ�������N��N+1֮��(Tail=Head+1)����С�ڵ�һ������(Tail==Head==0)��û�н��
            RltBegin=RltEnd=Tail;       
            return;
	    }
	    else 
	    {
            //�ҵ��˽��, CmpRlt==0��Ҫ���ҵ�������Mid(Head��Tail֮��)
            break;
	    }
    }

    //��ʱ��Head��Tail�ǿ��ܵ����޺�����
    iHead=Head;
    iTail=Tail;
    iMid=Mid;

    //�ö��ַ���ǰ���ҵ�һ������������ֵ(����)����Head-Mid֮�䡣���ҹ����У�Head!=LookupContent && Tail==LookupContent
    Head=iHead;
    Tail=iMid;
    Mid=(Head+Tail)/2;
    while(1)
    {
        CmpRlt=CompareMethod(pLookupContent,(const char*)pData+Mid*UnitSize);

	    if(CmpRlt==0&&Mid!=Tail) { Tail=Mid;  Mid=(Head+Tail)/2; }
	    else if(CmpRlt!=0&&Mid!=Head) { Head=Mid;  Mid=(Head+Tail)/2; }
	    else 
	    {   
            //��ʱ��Tail���ǵ�һ������������ֵ(����)
            RltBegin=Tail;       
            break;
	    }
    }

    //�ö��ַ������ҵ�һ��������������ֵ(����)����Mid-Tail֮�䡣���ҹ����У�Head==LookupContent && Tail!=LookupContent
    Head=iMid;
    Tail=iTail;
    Mid=(Head+Tail)/2;
    while(1)
    {
        CmpRlt=CompareMethod(pLookupContent,(const char*)pData+Mid*UnitSize);

	    if(CmpRlt!=0&&Mid!=Tail) { Tail=Mid;  Mid=(Head+Tail)/2; }
	    else if(CmpRlt==0&&Mid!=Head) { Head=Mid;  Mid=(Head+Tail)/2; }
	    else 
	    {   
            //��ʱ��Tail���ǵ�һ��������������ֵ(����)
            RltEnd=Tail;       
            break;
	    }
    }

    return;
}



//	��ð�ݷ��������������Ǵ�С����
//	Buf��Ҫ����Ļ���������������UnitNum����Ԫ��ɣ�ÿ����Ԫ�ĳ���ΪUnitSize
//	CmpOffΪҪ�ȽϵĴ��ڵ�Ԫ���λ�ã�CmpLenΪ�Ƚϵĳ���
//	��Сд�޹�
void CTools_Ansi::SetSequenceInBubble(char *Buf,int UnitNum,int UnitSize,int CmpOff,int CmpLen)
{
	int			i,j,AdjustNum,Rlt;
	char		Tmp[1024];

	if(UnitSize>1024) return;
	for(i=0;i<UnitNum-1;i++)
	{
		AdjustNum=0;
		for(j=UnitNum-1;j>i;j--)
		{
			Rlt=_memicmp(Buf+CmpOff+(j-1)*UnitSize,Buf+CmpOff+j*UnitSize,CmpLen);
			if(Rlt>0)
			{
				memcpy(Tmp,Buf+(j-1)*UnitSize,UnitSize);
				memcpy(Buf+(j-1)*UnitSize,Buf+j*UnitSize,UnitSize);
				memcpy(Buf+j*UnitSize,Tmp,UnitSize);
				AdjustNum++;
			}
		}
		if(!AdjustNum) break;								//û��Ҫ����������Ѿ��ź�����
	}
}


//	ȡָ����Χ�ڵ������
unsigned int CTools_Ansi::GetRandomValue(unsigned int MinVal,unsigned int MaxVal)
{
	unsigned int Val1,Val2,Val;
	struct _timeb	itime;

	_ftime(&itime);

	srand((unsigned int)itime.millitm);
	Val1=rand();
	if(MaxVal-MinVal>0&&MaxVal-MinVal<RAND_MAX)
		Val=Val1%(MaxVal-MinVal)+MinVal;
	else if(MaxVal-MinVal>0&&RAND_MAX>0&&MaxVal-MinVal>RAND_MAX)
	{
		Val2=rand();
		Val=(Val1*((MaxVal-MinVal)/RAND_MAX)+Val2)%(MaxVal-MinVal)+MinVal;
	}
	else Val=MinVal;
	return Val;
}

//  ȡ���ִ���ÿ�����ֵ�����ĸ��ɵĴ������ֱ�����GB2312����
string CTools_Ansi::GetFirstAlphasOfChineseStrGBK(const string& GBKStr)
{
    char buf[256]={0};
    int len=0;

    const unsigned char *p=(const unsigned char*)GBKStr.c_str();
    for(int i=0;i<(int)GBKStr.size()-1&&len<(int)sizeof(buf)-1;)
    {
        if(p[i]<0xA0) { i++;  continue; }
        else
        {
            unsigned short wd=*(const unsigned short*)(p+i);
            wd=(wd>>8)+(wd<<8);
            if(wd>=0xB0A1&&wd<=0xB0C4) buf[len++]='a';
            else if(wd>=0xB0C5&&wd<=0xB2C0) buf[len++]='b';
            else if(wd>=0xB2C1&&wd<=0xB4ED) buf[len++]='c';
            else if(wd>=0xB4EE&&wd<=0xB6E9) buf[len++]='d';
            else if(wd>=0xB6EA&&wd<=0xB7A1) buf[len++]='e';
            else if(wd>=0xB7A2&&wd<=0xB8c0) buf[len++]='f';
            else if(wd>=0xB8C1&&wd<=0xB9FD) buf[len++]='g';
            else if(wd>=0xB9FE&&wd<=0xBBF6) buf[len++]='h';
            else if(wd>=0xBBF7&&wd<=0xBFA5) buf[len++]='j';
            else if(wd>=0xBFA6&&wd<=0xC0AB) buf[len++]='k';
            else if(wd>=0xC0AC&&wd<=0xC2E7) buf[len++]='l';
            else if(wd>=0xC2E8&&wd<=0xC4C2) buf[len++]='m';
            else if(wd>=0xC4C3&&wd<=0xC5B5) buf[len++]='n';
            else if(wd>=0xC5B6&&wd<=0xC5BD) buf[len++]='o';
            else if(wd>=0xC5BE&&wd<=0xC6D9) buf[len++]='p';
            else if(wd>=0xC6DA&&wd<=0xC8BA) buf[len++]='q';
            else if(wd>=0xC8BB&&wd<=0xC8F5) buf[len++]='r';
            else if(wd>=0xC8F6&&wd<=0xCBF0) buf[len++]='s';
            else if(wd>=0xCBFA&&wd<=0xCDD9) buf[len++]='t';
            else if(wd>=0xCDDA&&wd<=0xCEF3) buf[len++]='w';
            else if(wd>=0xCEF4&&wd<=0xD188) buf[len++]='x';
            else if(wd>=0xD1B9&&wd<=0xD4D0) buf[len++]='y';
            else if(wd>=0xD4D1&&wd<=0xD7F9) buf[len++]='z';
            i+=2;
        }
    }

    return string(buf);
}