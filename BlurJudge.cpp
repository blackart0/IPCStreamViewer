#include "StdAfx.h"
#include <math.h>

#include "BlurJudge.h"
/***********************************************************************************
*** BlurJuge Algorithm
************************************************************************************/

// mean square deviation
double MeanSquareDeviation(BYTE *ydata,int w,int h)
{
	long n=w*h;
	long i;
	long mean=0,total=0;
	// caculate mean
	for(i=0;i<n;i++){
		total+=ydata[i];
	}
	mean=total/n;
	//
	double t=0.0;
	for(i=0;i<n;i++){
		double gap=ydata[i]-mean;
		t+=gap*gap*1.0/n;
	}
	double MSD=sqrt(total)/135;
	
	printf("MeanSquareDeviation mean:%d n:%d MSD:%lf\n",mean,n,MSD);
	return MSD;
}

double TenClarityEvaluation(BYTE *bpImg,int w,int h)
{//Tenengrad函数判别
	int Sx=0;
	int Sy=0;
	double Img=0;
	double T0=0;
	BYTE *A,*B,*C,*D,*E,*F,*G,*H,*R1,*R2,*R3;
	int x,y;
	for(y=1;y<h-1;y++)
    {  R1=bpImg+y*w;
	R2=bpImg+(y-1)*w;
	R3=bpImg+(y+1)*w;
	for(x=1;x<w-1;x++)
	{
        A=(BYTE*)(R2+(x+1)*3);
        B=(BYTE*)(R3+(x+1)*3);
        C=(BYTE*)(R2+(x-1)*3);
        D=(BYTE*)(R3+(x-1)*3);
        E=(BYTE*)(R1+(x+1)*3);
        F=(BYTE*)(R1+(x-1)*3);
        G=(BYTE*)(R3+x*3);
        H=(BYTE*)(R2+x*3);
        Sx=*A-*B-*C-*D+(*E+*E)-(*F+*F);
        Sy=*D+*B-*C-*A+(*G+*G)-(*H+*H);
        Img+=sqrt(Sx*Sx+Sy*Sy);
	}
    }
    T0=sqrt(Img);
	
	T0=(T0-15000);
	if(T0<0) T0=0;
	if(T0>3000) T0=3000;
	T0=(3000-T0)/30;
	
	printf("TenClarityEvaluation n:%d T:%lf\n",w*h,T0);
	return T0;
}


double  GradClarityEvaluation(BYTE *bpImg,int w,int h)
{
	//梯度向量模方和	// not bad
	double Gk=0;
	BYTE *bpImgPtr1,*bpImgPtr2,*bpImg1,*bpImg2;
	int A=0;
	int B=0;
	double Z0=0;
	int x,y;
	for(y=0;y<h-1;y++)
	{ 
		bpImg1=bpImg+y*w;
		bpImg2=bpImg+(y+1)*w;
		for(x=0;x<w-1;x++)
		{
			bpImgPtr1=(BYTE*)(bpImg1+x*3);
			//bpImgPtr2=(BYTE*)(bpImg1+(x+1)*3);
			bpImgPtr2=(BYTE*)(bpImg2+x*3);
			A=*bpImgPtr1-*(bpImgPtr1+3);
			B=*bpImgPtr1-*bpImgPtr2;
			Gk+=sqrt(A*A+B*B);
		}
	}
    Z0=sqrt(Gk);
	// judge to 0~ 100
	Z0=(Z0-1000)/20;
	if(Z0<0) Z0=0;
	else if(Z0>100) Z0=100;

	printf("GradClarityEvaluation n:%d Z:%lf\n",w*h,Z0);
	return Z0;
}


double LapClarityEvaluation(BYTE *bpImg,int w,int h) 
{//laplace函数判别 //not bad
    double L=0;
    //int MaxL=0;
    double Z0=0;
    BYTE *A,*B,*C,*D,*E,*R1,*R2,*R3;
	int x,y;
    for(y=1;y<h-1;y++)
	{ R1=bpImg+y*w;
	R2=bpImg+(y-1)*w;
	R3=bpImg+(y+1)*w;
	for(x=1;x<w-1;x++)
	{
		A=(BYTE*)(R1+x*3);
		B=(BYTE*)(R1+(x-1)*3);
		C=(BYTE*)(R1+(x+1)*3);
		D=(BYTE*)(R2+x*3);
		E=(BYTE*)(R3+x*3);
		L+=(abs(*A+*A-*B-*C)+abs(*A+*A-*D-*E));
		//if(L>MaxL) MaxL=L;
	}
	}
    Z0=sqrt(L);
	// fix to 0-100
	Z0=(Z0-1500)/22;
	if(Z0<0) Z0=0;
	else if(Z0>100) Z0=100;
	printf("LapClarityEvaluation n:%d T:%lf\n",w*h,Z0);
	return Z0;
}

double  SharpnessEvaluation(BYTE* bpImg ,int w,int h)
{//点锐度算法 // not bad
	int x,y;
    int Img=0;
    int Sum=0;      
    static int c[100]={0};
    double Z0=0;
    double g=0;
    BYTE *A,*B,*C,*D,*E,*F,*G,*H,*I,*J,*K,*L,*M,*R1,*R2,*R3;
    for(y=1;y<h-1;y++)
    {
		R1=bpImg+y*w;
		R2=bpImg+(y-1)*w;
		R3=bpImg+(y+1)*w;
		for(x=1;x<w-2;x++)
		{
			A=(BYTE*)(R1+x*3);
			B=(BYTE*)(R1+(x-1)*3);
			C=(BYTE*)(R1+(x+1)*3);
			D=(BYTE*)(R2+(x-1)*3);
			E=(BYTE*)(R2+x*3);
			F=(BYTE*)(R2+(x+1)*3);
			G=(BYTE*)(R3+(x-1)*3);
			H=(BYTE*)(R3+x*3);
			I=(BYTE*)(R3+(x+1)*3);
			J=(BYTE*)(R1+(x+2)*3);
			K=(BYTE*)(R2+(x+2)*3);
			L=(BYTE*)(R3+(x+2)*3);
			g=1/sqrt(2);
			Sum=abs(*A-*B)+abs(*J-*C)+abs(g*(*E-*D))+abs(g*(*F-*E))+abs(*K-*F)+abs(g*(*H-*G))+abs(g*(*I-*H))+abs(*L-*I);
			Img+=Sum;
		}
    }
	Z0=Img/(h*w);
	//fix to 0~100
	Z0=Z0*2.3;
	printf("SharpnessAlgorithm n:%d T:%lf\n",w*h,Z0);

	return Z0;
}

double EnergyEvaluation(BYTE*bpImg,int w,int h)
{//能量梯度函数
	int Img=0;
	double Z0=0;
	int x,y;
	BYTE *A,*B,*C,*R1,*R2,*R3;
	for(y=0;y<h-1;y++)
    {
		R1=bpImg+y*w;
		R2=bpImg+(y+1)*w;
		for(x=0;x<w-1;x++)
		{
			A=(BYTE*)(R1+x*3);
			B=(BYTE*)(R1+(x+1)*3);
			C=(BYTE*)(R2+x*3);
			Img+=(*B-*A)*(*B-*A)+(*C-*A)*(*C-*A);
		}
	}
	Z0=sqrt(Img);
	//fix to 0~100
	Z0=(Z0-12000)/100;
	printf("EnergyEvaluation n:%d T:%lf\n",w*h,Z0);

	return Z0;
}

/*************************************************************************************
*** class: BlurJuge Implement
*************************************************************************************/
BlurJudge::BlurJudge()
{
	proc=GradClarityEvaluation;
	m_plot=NULL;
}

BlurJudge::~BlurJudge()
{
	YData=NULL;
	this->proc=NULL;
}

void BlurJudge::SetData(BYTE *ydata,int w,int h)
{
	YData=ydata;
	width=w;
	height=h;
}

void BlurJudge::SetPlot(clPlot *plot)
{
	m_plot=plot;
}

void BlurJudge::SetJudgeProc(BlurJudgeProc proc)
{
	this->proc=proc;
}

void BlurJudge::SetJudgeProc(int index)
{
	BlurJudgeProc procs[]=
	{
		GradClarityEvaluation,
		LapClarityEvaluation,
		SharpnessEvaluation,
		EnergyEvaluation,
	};
	if (index >= 4)
	{
		index=0;
	}
	proc=procs[index];
}

BlurJudgeProc BlurJudge::GetJudgeProc()
{
	return this->proc;
}

double BlurJudge::DoJudge()
{
	double d=proc(YData,width,height);
	if(m_plot){
		m_plot->AddPoint(0,  CTime::GetCurrentTime(), d);
		m_plot->NewFloatValue(d);
	}
	return d;
}