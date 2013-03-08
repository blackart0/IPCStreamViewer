#pragma once

#include "plot/clPlot.h"

typedef double (*BlurJudgeProc)(BYTE *Ydata,int w,int h);

class BlurJudge
{
private:
	BYTE *YData;
	int width;
	int height;

	clPlot *m_plot;
public:
	BlurJudgeProc proc;
	
	BlurJudge();
	~BlurJudge();
	
	void SetJudgeProc(BlurJudgeProc proc);
	void SetJudgeProc(int index);
	void SetJudgeProc(char *name);
	BlurJudgeProc GetJudgeProc();
	
	void SetData(BYTE *ydata,int w,int h);
	void SetPlot(clPlot *plot);
	
	double DoJudge();
};

///
double MeanSquareDeviation(BYTE *ydata,int w,int h);
