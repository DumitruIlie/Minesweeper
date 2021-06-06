#include <graphics.h>
#include <time.h>
#include <cstdio>

using namespace std;

const int LATIME=20,INALTIME=20,DIMCASUTA=16,NRBOMBE=40,LEGENDA=52;

int dirX[8]={0,1,1,1,0,-1,-1,-1}, dirY[8]={-1,-1,0,1,1,1,0,-1}, poligon[8], nrCasuteNeexplorate;

bool verifMat(int x, int y);

void lee(int mat[INALTIME][LATIME], int x, int y, bool matDescoperit[INALTIME][LATIME], bool matBombe[INALTIME][LATIME]);

void numar(int x, int y, int nr);

void drawWin(bool mat[INALTIME][LATIME]);

void drawLose(bool mat[INALTIME][LATIME]);

void drawTime(int nrSec);

void drawNormal();

void drawBomb(int y, int x);

void drawFlag(int y, int x);

int playMinesweeper();

int main ()
{
    int x=playMinesweeper();
    while(x)
        x=playMinesweeper();
    return 0;
}

bool verifMat(int x, int y)
{
    if(x<0||x>=LATIME||y<0||y>=INALTIME)
        return false;
    return true;
}

void lee(int mat[INALTIME][LATIME], int x, int y, bool matDescoperit[INALTIME][LATIME], bool matBombe[INALTIME][LATIME])
{
    if(verifMat(x, y)&&matDescoperit[y][x]==false&&!matBombe[y][x])
    {
        matDescoperit[y][x]=true;
        poligon[0]=x*DIMCASUTA;
        poligon[1]=y*DIMCASUTA+LEGENDA;
        poligon[2]=poligon[0]+DIMCASUTA;
        poligon[3]=poligon[1];
        poligon[4]=poligon[2];
        poligon[5]=poligon[3]+DIMCASUTA;
        poligon[6]=poligon[0];
        poligon[7]=poligon[5];
        setcolor(BLACK);
        setlinestyle(0, 0, 1);
        fillpoly(4, poligon);
        if(mat[y][x]==0)
        {
            --nrCasuteNeexplorate;
            for(int i=0;i<8;++i)
                lee(mat, x+dirX[i], y+dirY[i], matDescoperit, matBombe);
        }
        else
        {
            numar(x*DIMCASUTA, y*DIMCASUTA+LEGENDA, mat[y][x]);
            --nrCasuteNeexplorate;
        }
    }
}

void numar(int x, int y, int nr)
{
    switch(nr)
    {
    case(1):
        {
            setcolor(BLUE);
            setlinestyle(0, 0, 2);
            line(x+DIMCASUTA/2, y+2, x+DIMCASUTA/2, y+12);
            line(x+DIMCASUTA/2, y+2, x+3, y+6);
            setlinestyle(0, 0, 1);
        }
        break;
    case(2):
        {
            setcolor(GREEN);
            setlinestyle(0, 0, 2);
            ellipse(x+DIMCASUTA/2, y-2+DIMCASUTA/2, 330, 180, 4, 4);
            line(x+DIMCASUTA/2+3, y+1+DIMCASUTA/2, x+DIMCASUTA/2, y+13);
            line(x+DIMCASUTA/2, y+13, x+DIMCASUTA-3, y+13);
            setcolor(BLACK);
        }
        break;
    case(3):
        {
            setcolor(COLOR(150, 50, 20));
            setlinestyle(0, 0, 2);
            ellipse(x+DIMCASUTA/2, y+5, 270, 140, 3, 4);
            ellipse(x+DIMCASUTA/2, y+10, 225, 90, 4, 5);
            setcolor(BLACK);
        }
        break;
    case(4):
        {
            setcolor(BLUE);
            setlinestyle(0, 0, 2);
            line(x+8, y+4, x+2, y+DIMCASUTA/2+2);
            line(x+4, y+DIMCASUTA/2+2, x+10, y+DIMCASUTA/2+2);
            line(x+8, y+4, x+8, y+DIMCASUTA-2);
            setcolor(BLACK);
        }
        break;
    case(5):
        {
            setcolor(RED);
            setlinestyle(0, 0, 2);
            ellipse(x+DIMCASUTA/2, y+DIMCASUTA*2/3, 235, 135, 4, 4);
            line(x+6, y+4, x+6, y+6);
            line(x+6, y+4, x+12, y+4);
            setcolor(BLACK);
        }
        break;
    case(6):
        {
            setcolor(RED);
            setlinestyle(0, 0, 2);
            circle(x+DIMCASUTA/2, y+DIMCASUTA*3/4-2, 4);
            line(x+DIMCASUTA/2-4, y+DIMCASUTA*3/4-2, x+DIMCASUTA/2, y+2);
            setcolor(BLACK);
        }
        break;
    case(7):
        {
            setcolor(COLOR(150, 100, 40));
            setlinestyle(0, 0, 2);
            line(x+6, y+4, x+12, y+4);
            line(x+12, y+4, x+9, y+12);
            setcolor(BLACK);
        }
        break;
    case(8):
        {
            setcolor(COLOR(150, 150, 40));
            setlinestyle(0, 0, 2);
            circle(x+DIMCASUTA/2, y+6, 3);
            circle(x+DIMCASUTA/2, y+11, 4);
            setcolor(BLACK);
        }
    }
}

void drawWin(bool mat[INALTIME][LATIME])
{
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, YELLOW);
    setlinestyle(0, 0, 2);
    fillellipse(LATIME*DIMCASUTA/2, LEGENDA/2, 16, 16);
    line(LATIME*DIMCASUTA/2-14, LEGENDA/2-7, LATIME*DIMCASUTA/2+14, LEGENDA/2-7);
    line(LATIME*DIMCASUTA/2-14, LEGENDA/2-6, LATIME*DIMCASUTA/2+14, LEGENDA/2-6);
    setfillstyle(SOLID_FILL, BLACK);
    poligon[0]=LATIME*DIMCASUTA/2-8;
    poligon[1]=LEGENDA/2-6;
    poligon[2]=poligon[0];
    poligon[3]=poligon[1]+3;
    poligon[4]=poligon[0]+5;
    poligon[5]=poligon[3];
    poligon[6]=poligon[4];
    poligon[7]=poligon[1];
    fillpoly(4, poligon);
    poligon[0]=LATIME*DIMCASUTA/2+3;
    poligon[1]=LEGENDA/2-6;
    poligon[2]=poligon[0];
    poligon[3]=poligon[1]+3;
    poligon[4]=poligon[0]+5;
    poligon[5]=poligon[3];
    poligon[6]=poligon[4];
    poligon[7]=poligon[1];
    fillpoly(4, poligon);
    setlinestyle(SOLID_LINE, 0, 2);
    setcolor(RED);
    ellipse(LATIME*DIMCASUTA/2, LEGENDA/2+5, 180, 0, 10, 3);
    for(int i=0;i<INALTIME;++i)
        for(int j=0;j<LATIME;++j)
            if(mat[i][j])
                drawFlag(i, j);
}

void drawLose(bool mat[INALTIME][LATIME])
{
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, YELLOW);
    setlinestyle(0, 0, 2);
    fillellipse(LATIME*DIMCASUTA/2, LEGENDA/2, 16, 16);
    line(LATIME*DIMCASUTA/2-7, LEGENDA/2-7, LATIME*DIMCASUTA/2-2, LEGENDA/2-2);
    line(LATIME*DIMCASUTA/2-7, LEGENDA/2-2, LATIME*DIMCASUTA/2-2, LEGENDA/2-7);
    line(LATIME*DIMCASUTA/2+7, LEGENDA/2-7, LATIME*DIMCASUTA/2+2, LEGENDA/2-2);
    line(LATIME*DIMCASUTA/2+7, LEGENDA/2-2, LATIME*DIMCASUTA/2+2, LEGENDA/2-7);
    setlinestyle(SOLID_LINE, 0, 2);
    setcolor(RED);
    ellipse(LATIME*DIMCASUTA/2, LEGENDA/2+5, 0, 180, 10, 3);
    for(int i=0;i<INALTIME;++i)
        for(int j=0;j<LATIME;++j)
            if(mat[i][j])
                drawBomb(i, j);
}

void drawTime(int nrSec)
{
    int nrH=nrSec/3600, nrM=nrSec%3600/60, nrS=nrSec%60;
    char T[9];
    T[0]=char(nrH/10+'0');
    T[1]=char(nrH%10+'0');
    T[2]=':';
    T[3]=char(nrM/10+'0');
    T[4]=char(nrM%10+'0');
    T[5]=':';
    T[6]=char(nrS/10+'0');
    T[7]=char(nrS%10+'0');
    T[8]='\0';
    moveto(5, 20);
    setcolor(COLOR(200, 20, 20));
    outtext(T);
}

void drawNormal()
{
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, YELLOW);
    setlinestyle(0, 0, 2);
    fillellipse(LATIME*DIMCASUTA/2, LEGENDA/2, 16, 16);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(LATIME*DIMCASUTA/2-4, LEGENDA/2-3, 2, 2);
    fillellipse(LATIME*DIMCASUTA/2+4, LEGENDA/2-3, 2, 2);
    setlinestyle(SOLID_LINE, 0, 2);
    setcolor(RED);
    ellipse(LATIME*DIMCASUTA/2, LEGENDA/2+5, 180, 0, 9, 1);
}

void drawBomb(int y, int x)
{
    setfillstyle(SOLID_FILL, BLACK);
    x*=DIMCASUTA;
    y*=DIMCASUTA;
    y+=LEGENDA;
    setcolor(BLACK);
    fillellipse(x+DIMCASUTA/2, y+DIMCASUTA/2, 5, 5);
    putpixel(x+DIMCASUTA/2+1, y+DIMCASUTA/2-4, COLOR(194, 128, 20));
    putpixel(x+DIMCASUTA/2+1, y+DIMCASUTA/2-5, COLOR(194, 128, 20));
    putpixel(x+DIMCASUTA/2+1, y+DIMCASUTA/2-3, COLOR(194, 128, 20));
    putpixel(x+DIMCASUTA/2+2, y+DIMCASUTA/2-4, COLOR(194, 128, 20));
    putpixel(x+DIMCASUTA/2, y+DIMCASUTA/2-4, COLOR(194, 128, 20));
}

void drawFlag(int y, int x)
{
    setfillstyle(SOLID_FILL, BLACK);
    x*=DIMCASUTA;
    y*=DIMCASUTA;
    y+=LEGENDA;
    poligon[0]=x+DIMCASUTA-4;
    poligon[1]=y+DIMCASUTA-2;
    poligon[2]=x+4;
    poligon[3]=poligon[1];
    poligon[4]=poligon[2];
    poligon[5]=poligon[1]-5;
    poligon[6]=poligon[0];
    poligon[7]=poligon[5];
    setlinestyle(0, 0, 1);
    setcolor(BLACK);
    fillpoly(4, poligon);
    line(x+DIMCASUTA/2, poligon[1]-2, x+DIMCASUTA/2, y+2);
    poligon[0]=x+DIMCASUTA/2;
    poligon[2]=poligon[0];
    poligon[4]=poligon[0]+6;
    poligon[1]=y+2;
    poligon[3]=poligon[1]+6;
    poligon[5]=poligon[1]+3;
    setfillstyle(SOLID_FILL, COLOR(200, 40, 40));
    setlinestyle(0, 0, 1);
    setcolor(BLACK);
    fillpoly(3, poligon);
}

int playMinesweeper()
{
    nrCasuteNeexplorate=INALTIME*LATIME;
    int seed=time(NULL)%1000, mat[INALTIME][LATIME], x, y, start;
    bool matBombe[INALTIME][LATIME], matDescoperit[INALTIME][LATIME], ok=true, started=false;
    for(int i=0;i<seed;++i)
        srand(rand());
    for(int i=0;i<INALTIME;++i)
        for(int j=0;j<LATIME;++j)
        {
            mat[i][j]=0;
            matBombe[i][j]=false;
            matDescoperit[i][j]=false;
        }
    for(int i=0;i<NRBOMBE;++i)
    {
        x=rand()%LATIME, y=rand()%INALTIME;
        if(!matBombe[y][x])
            matBombe[y][x]=true;
        else
            --i;
    }
    for(int i=0;i<INALTIME;++i)
        for(int j=0;j<LATIME;++j)
            for(int k=0;k<8;++k)
            {
                if(verifMat(j+dirX[k], i+dirY[k])&&matBombe[i+dirY[k]][j+dirX[k]])
                    ++mat[i][j];
            }
    initwindow(DIMCASUTA*LATIME+1, DIMCASUTA*INALTIME+LEGENDA+1, "Minesweeper v. 1.1", 100, 100);
    setbkcolor(WHITE);
    cleardevice();
    setcolor(COLOR(0, 0, 0));
    setfillstyle(SOLID_FILL, COLOR(128, 128, 128));
    for(int i=0;i<INALTIME;++i)
    {
        for(int j=0;j<LATIME;++j)
        {
            poligon[0]=j*DIMCASUTA;
            poligon[1]=i*DIMCASUTA+LEGENDA;
            poligon[2]=poligon[0]+DIMCASUTA;
            poligon[3]=poligon[1];
            poligon[4]=poligon[2];
            poligon[5]=poligon[3]+DIMCASUTA;
            poligon[6]=poligon[0];
            poligon[7]=poligon[5];
            fillpoly(4, poligon);
        }
    }
    drawNormal();
    drawTime(0);
    while(ok&&nrCasuteNeexplorate>NRBOMBE)
    {
        while(!ismouseclick(WM_LBUTTONDOWN))
            if(!started)
                start=time(NULL);
            else
                drawTime(time(NULL)-start);
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(y>=LEGENDA)
        {
            started=true;
            x/=DIMCASUTA;
            y-=LEGENDA;
            y/=DIMCASUTA;
            setfillstyle(SOLID_FILL, COLOR(192, 192, 192));
            if(matBombe[y][x])
                ok=false;
            else
                lee(mat, x, y, matDescoperit, matBombe);
        }
        else
        {
            if(x>=DIMCASUTA*LATIME/2-16&&x<=DIMCASUTA*LATIME/2+16&&y>=LEGENDA/2-16&&y<=LEGENDA/2+16)
            {
                closegraph();
                return 1;
            }
            return 0;
        }
    }
    int now=time(NULL);
    drawTime(now-start);
    if(ok)
    {
        drawWin(matBombe);
        while(!ismouseclick(WM_LBUTTONDOWN));
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(x>=DIMCASUTA*LATIME/2-16&&x<=DIMCASUTA*LATIME/2+16&&y>=LEGENDA/2-16&&y<=LEGENDA/2+16)
        {
            closegraph();
            return 1;
        }
        return 0;
    }
    else
    {
        drawLose(matBombe);
        while(!ismouseclick(WM_LBUTTONDOWN));
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(x>=DIMCASUTA*LATIME/2-16&&x<=DIMCASUTA*LATIME/2+16&&y>=LEGENDA/2-16&&y<=LEGENDA/2+16)
        {
            closegraph();
            return 1;
        }
        return 0;
    }
}
