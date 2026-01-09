/*
=========================================================================
LL 1989,ˆŽ“ŠˆŽ‘,24,
------------------------------------------------------------------------- */
#include "src\\tans5.h"

extern char	scr[4001];

get_from_user_filename(
char *pathname,
char *fext)
{
	int ier;
	FILE	*fp, *fopen();
	static char fname[13]={0};

	/* ---------------------------- DEFINE DATA FILE: */
	get_from_disk_screen(80,16,DFNAME);
	puttext(1,10,80,25,scr);
	cursor(1);
	do
	{
	    if((ier=input(14,35,"",fname,0,12,"!","zzzzzzzz",0,'m',"%-s"))
			== HOME || ier == ESC)
	    	return ier;
	    strcat(pathname, fname);
	    if(strchr(fname,'.') == NULL)	    strcat(pathname, fext);
	    if((fp = fopen(pathname, "ab")) == NULL)
	        error(11);
	    else
		fclose(fp);
	} while(fp == NULL);
	return ier;
}
/*
=========================================================================
------------------------------------------------------------------------- */

