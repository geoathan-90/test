/*
------------------------------------------------------------

198?,1989,?,€“‚Ž“‘’Ž‘
ALFA/NUMBER INPUT
------------------------------------------------------------
*/
# include "src\tans5.h"

input(r,c,prmt,rr,ne,nm,mi,ma,prt,ty,format)

char    *prmt,          /* prompt */
	ty,             /* input type */
	*format;
unsigned char   *rr,            /* inserted value */
        	*mi, *ma;       /* min/max value */
int     r, c,           /* row, colummn */
        ne, nm,         /* min/max char number */
        prt;            /* protected input */
{
        unsigned char	r0[81]={0},	/* original value */
			s[81]={0};	/* bohuhtikos buffer */
	char    *cline();	/* line of n chars */
        int     alfa,   /* 'a' or 'm' input type */
                nx=0,   /* inserted char number */
                n,      /* left cursor char no. */
                ins,    /* insert mode */
                cmnd,   /* command mode */
                exitfl,   /* exit input flag */
                check,  /* logical var */
                err,    /* error no. */
                perr=0, /*  previour error no. */
                cc='#'; /* inserted char */
        double  atof();

    alfa = ty == 'a' || ty == 'm';
    if(strcmp(rr," ") < 0 || prt)       rr[0] = '\0';
    else if((nx=strlen(rr)) > nm)       rr[nm] = '\0';
    gotoxy(c-strlen(prmt),r);
    printf("%s%s%s", HI, prmt, FI);
    cursor(1);
    scpy(r0,rr);

    do  {
        if(cc == '#')   {
                ins = cmnd = n = exitfl = err = 0;
                nx=scpy(rr,r0);
		gotoxy(c,r);
                printf("%s%s", rr, cline(nm-nx,KENO));
		gotoxy(c,r);
        }

/*

	cc = bioskey(0);
	if((cc & 0xff) != 0) cc &= 0xff;
*/
	switch(cc=gchar()) {
	case F1:
	case HELP:
	    help();
	    break;
        case ESC:
            if(n == nx)
		    cc='#';
            else
	    {
                    rr[n] = '\0';
                    nx=n;
                    printf("%s", cline(nm-n,KENO));		/*18/8/89*/
		    exitfl = 1;
            }
        case '#':
            break;
        case LEFT_ARROW:
            if(!cmnd)   {
                exitfl = 1;
                break;
            }
        case '<':
            if(prt)             err = 10;
            else if(n == 0)     err = 9;
            else        {
                printf(LEFT);
                n--;
                if(ins) printf(" %c%s%s", rr[n], LEFT, LEFT);
            }
            break;
        case RIGHT_ARROW:
        case RETURN:
            if(cmnd == 0)
	    {
                exitfl = 1;
                break;
            }
        case '>':
            if(prt)             err = 10;
            else if(n == nx)    err = 9;
            else        {
                if(ins) printf("%c %s", rr[n], LEFT);
                else printf(RIGHT);
                n++;    }
            break;
        case END:                       /* TELOS KATAXVRISEVS */
            if(prt)     err = 10;
            else        {
                ins=0;
                printf("%s%c%s", rr+n, KENO, LEFT);  	         /*18/8/89*/
                n=nx;
            }
            break;
        case HOME:
            if(prt)     err = 10;
            else if(n)  {
                n=0;
                gotoxy(c,r);
                if(ins)
		{
		    printf(" %s", rr);
	            gotoxy(c,r);
                }
            }
            else exitfl = 1;
            break;
        case INS:
            if(prt)             err = 10;
            else if(ins)
	    {
		ins=0;
		printf("%s%c",rr+n, KENO);
                gotoxy(c+n,r);
            }
	    else if(nx == nm)	err = 1;		/*18/8/89*/
            else
	    {
		ins=1;
		printf(" %s",rr+n);
		gotoxy(c+n,r);
	    }
            break;
        case '\\':              /* allagh command mode */
            cmnd=1-cmnd;
            break;
        case BACKSPACE:               /* backspace */
            if(n)  {
                sprintf(rr+n-1, "%s", rr+n);
                n--;    nx--;
                if(! prt)       {
                    printf(LEFT);
                    if(ins) putchar(' ');
                    printf("%s%c", rr+n, KENO);
		    gotoxy(c+n,r);
                }
            }
	    else	err = 9;
            break;
        case DEL:               /* delete */
            if(n < nx)  {
                sprintf(rr+n, "%s", rr+n+1);
                nx--;
                if(! prt)       {
                    if(ins) putchar(' ');
                    printf("%s%c", rr+n, KENO);
		    gotoxy(c+n,r);
                }
            }
            break;
	case '-':
	    if(!alfa)
	    {
		if(rr[0] == '-')
		{
		    sprintf(rr, "%s", rr+1);
		    n--;	nx--;
		}
	        else if(nx < nm)
		{
    		    sprintf(s, "-%s", rr);
            	    scpy(rr, s);
                    n++;    nx++;
		}
		else
		{
		    err = 1;
		    break;
		}
		gotoxy(c, r);
	    	if(!prt)
	    	{
		    printf("%s", rr);
		    gotoxy(c+n, r);
		    if(ins)	putchar(' ');
		    if(rr[0] == '-')	    printf("%s", rr+n);
		    else                    printf("%s%c", rr+n, KENO);
	        }
	    	gotoxy(c+n, r);
	    	break;
	    }
        default:
            if(cc >= ' ' && cc < 256)
	    {
/*18/8/89*/     if(n == nm)			             err = 1;
                else if(ty == 'a' && isdigit(cc))            err = 3;
                else if(!alfa)
		{
                        if(ins && n == 0  && rr[0] == '-')   err = 6;
                        else if(cc == '.')
			{
                                if(ty == 'n')                err = 7;
                        }
                        else if(!isdigit(cc))		     err = 2;
                }
                if(!err)
		{
                        if(ins)
			{
			    sprintf(s, "%c%s", cc, rr+n);
                            scpy(rr+n,s);
                            n++;    nx++;
			    if(nx == nm)			/*18/8/89*/
			    {
                                printf("%c%s", cc, rr+n);
				ins = 0;	err = 1;
			    }
			    else
                                printf("%c %s", cc, rr+n);
			    gotoxy(c+n,r);
                        }
                        else
			{
                                rr[n] = cc;
                                if(n == nx)     n++, nx++, rr[n] = '\0';
                                else            n++;
                                if(!prt)        putchar(cc);
                        }
                }
            }                           /* TELOS TOY: if(cc >= ' ') */
            else        exitfl = 1;
            break;
        }                               /* TELOS TOY: switch(cc=getch()) */

/*
EXIT:
prepei na feygei xvris elegxo otan den ginetai allagh.
tote h eyuynh toy elegxoy afinetai sto kaloyn progr poy mporei na exei
eidikoys logoys afoy dinei mh epitrepth arxikh timh
(p.x. akyrvsh teleytaias (kenhs) eggrafhs sta arxeia, otan den ginei katax,
xvris thn eidikh epembas toy xrhsth.)

gotoxy(57,24); printf("33.[%5s] %+05X ", rr, rr); getch();
*/
        if(exitfl)
	{
            if(strcmp(rr,r0) == 0)      nx = 0;
            else if(nx < ne)                           err = 4;
            else
	    {
                if(alfa)
		{
/* if(strcmp(mi,rr) > 0 || strcmp(rr,ma) > 0)          err = 5; */
                    if(checkrange(mi,rr,ma) == -1)     err = 5;
		}
                else
		{
                    check=dpoint(rr) > 1;
                    check =
			check || strcmp(rr,".") == 0 || strcmp(rr,"-.") == 0;
                    check = ty == 'f' && check || strcmp(rr,"-") == 0;
                    if(check)                         err = 8;
                    else if(atof(rr) < atof(mi) || atof(rr) > atof(ma))
						      err = 5;
                }
            }
        }                                       /* TELOS TOY: if(exitfl) */
        if(err || perr)
	{
                error(err);
                if(prt) gotoxy(c,r);
                else    gotoxy(c+n,r);
                perr = err;
                if(err) err = exitfl = 0;
        }
    } while(! exitfl);

    cursor(0);
    gotoxy(c,r);
    printf("%s%*s", HI, nm, " ");       			/*18/8/89*/
    if(!prt)
    {
            gotoxy(c,r);
	switch(ty)
	{
	case 'a':
	case 'm':
	    printf(format, rr);
	    return(cc);
	case 'n':
	    printf(format, atoi(rr));
	    return(cc);
	case 'f':
	    printf(format, atof(rr));
	    return(cc);
	}
    }
    return(cc);
}                               /* -------------INPUT END--------------- */
/*
------------------------------------------------------------

-------------------------------------------------------------------- */
