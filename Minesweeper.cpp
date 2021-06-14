#include <graphics.h>
#include <time.h>
#include <cstdio>

const int LATIME=20, INALTIME=20, DIMCASUTA=16, NRBOMBE=40, LEGENDA=52, FACEDIM=36, dirX[8]={0, 1, 1, 1, 0, -1, -1, -1}, dirY[8]={-1, -1, 0, 1, 1, 1, 0, -1};
int nrCasuteNeexplorate;

bool verifMat(int x, int y);

void lee(int mat[INALTIME][LATIME], int x, int y, bool matDescoperit[INALTIME][LATIME], bool matBombe[INALTIME][LATIME]);

void drawTime(int nrSec);

void drawBomb(int y, int x);

void drawFlag(int y, int x);

void numar(int x, int y, int nr);

void drawChecked(int x, int y);

void drawUnchecked(int x, int y);

bool playMinesweeper();

void *bomb_img=0, *flag_img=0, *normal_face_img=0, *win_face_img=0, *lose_face_img=0;

void preload();

void unload();

int main ()
{
    preload();
    bool x=playMinesweeper();
    while(x)
        x=playMinesweeper();
    unload();
    return 0;
}

inline int max(int a, int b) {return a+(b-a)*(b>a);}
inline int min(int a, int b) {return a+(b-a)*(b<a);}

void preload()
{
    int d=max(FACEDIM, DIMCASUTA), w=initwindow(d, d, "", -d, -d);
    setbkcolor(WHITE);
    cleardevice();
    readimagefile("normal_face.bmp", 0, 0, FACEDIM-1, FACEDIM-1);
    normal_face_img=malloc(imagesize(0, 0, FACEDIM-1, FACEDIM-1));
    getimage(0, 0, FACEDIM-1, FACEDIM-1, normal_face_img);
    cleardevice();
    readimagefile("lose_face.bmp", 0, 0, FACEDIM-1, FACEDIM-1);
    lose_face_img=malloc(imagesize(0, 0, FACEDIM-1, FACEDIM-1));
    getimage(0, 0, FACEDIM-1, FACEDIM-1, lose_face_img);
    cleardevice();
    readimagefile("win_face.bmp", 0, 0, FACEDIM-1, FACEDIM-1);
    win_face_img=malloc(imagesize(0, 0, FACEDIM-1, FACEDIM-1));
    getimage(0, 0, FACEDIM-1, FACEDIM-1, win_face_img);
    cleardevice();
    readimagefile("bomb.bmp", 0, 0, DIMCASUTA, DIMCASUTA);
    bomb_img=malloc(imagesize(0, 0, DIMCASUTA, DIMCASUTA));
    getimage(0, 0, DIMCASUTA, DIMCASUTA, bomb_img);
    cleardevice();
    readimagefile("flag.bmp", 0, 0, DIMCASUTA, DIMCASUTA);
    flag_img=malloc(imagesize(0, 0, DIMCASUTA, DIMCASUTA));
    getimage(0, 0, DIMCASUTA, DIMCASUTA, flag_img);
    closegraph(w);
}

void unload()
{
    free(normal_face_img);
    free(lose_face_img);
    free(win_face_img);
    free(flag_img);
    free(bomb_img);
}

bool verifMat(int x, int y) {return !(x<0 || x>=LATIME || y<0 || y>=INALTIME);}

void lee(int mat[INALTIME][LATIME], int x, int y, bool matDescoperit[INALTIME][LATIME], bool matBombe[INALTIME][LATIME])
{
    if(verifMat(x, y) && !matDescoperit[y][x] && !matBombe[y][x])
    {
        matDescoperit[y][x]=true;
        if(!mat[y][x])
        {
            --nrCasuteNeexplorate;
            for(int i=0;i<8;++i)
                lee(mat, x+dirX[i], y+dirY[i], matDescoperit, matBombe);
        }
        else
            --nrCasuteNeexplorate;
    }
}

void numar(int x, int y, int nr)
{
    x*=DIMCASUTA;
    y=y*DIMCASUTA+LEGENDA;
	static int cols[]={BLACK, BLUE, GREEN, COLOR(150, 50, 20), BLUE, RED, COLOR(150, 100, 40), COLOR(150, 150, 40)};
    setcolor(cols[nr]);
	setbkcolor(COLOR(192, 192, 192));
	char ch[2];
	sprintf(ch, "%d", nr);
	outtextxy(x+((DIMCASUTA-textwidth(ch))>>1), y+((DIMCASUTA-textheight(ch))>>1), ch);
	setcolor(BLACK);
	line(x, y, x+DIMCASUTA, y);
	line(x, y+DIMCASUTA, x+DIMCASUTA, y+DIMCASUTA);
}

void drawTime(int nrSec)
{
    int nrH=nrSec/3600, nrM=nrSec%3600/60, nrS=nrSec%60;
    char T[15];
    sprintf(T, "%02d:%02d:%02d", nrH, nrM, nrS);
    setcolor(COLOR(200, 20, 20));
    setbkcolor(COLOR(128, 128, 128));
    outtextxy(5, 20, T);
}

void drawBomb(int y, int x)
{
    x*=DIMCASUTA;
    y*=DIMCASUTA;
    y+=LEGENDA;
    readimagefile("bomb.bmp", x, y, x+DIMCASUTA-1, y+DIMCASUTA-1);
}

void drawFlag(int y, int x)
{
    x*=DIMCASUTA;
    y*=DIMCASUTA;
    y+=LEGENDA;
    readimagefile("flag.bmp", x, y, x+DIMCASUTA-1, y+DIMCASUTA-1);
}

void drawUnchecked(int x, int y)
{
    x*=DIMCASUTA;
    y=y*DIMCASUTA+LEGENDA;
    setfillstyle(1, COLOR(128, 128, 128));
    setlinestyle(0, 0, 1);
    setcolor(BLACK);
    bar(x, y, x+DIMCASUTA, y+DIMCASUTA);
    rectangle(x, y, x+DIMCASUTA, y+DIMCASUTA);
}

void drawChecked(int x, int y)
{
    x*=DIMCASUTA;
    y=y*DIMCASUTA+LEGENDA;
    setfillstyle(1, COLOR(194, 194, 194));
    setcolor(BLACK);
    setlinestyle(0, 0, 1);
    bar(x, y, x+DIMCASUTA, y+DIMCASUTA);
    rectangle(x, y, x+DIMCASUTA, y+DIMCASUTA);
}

void draw(int mat[INALTIME][LATIME], bool matDescoperit[INALTIME][LATIME], bool matBombe[INALTIME][LATIME], int timeElapsed=0, char gameState=0)
{
    setbkcolor(COLOR(128, 128, 128));
    cleardevice();
    int i, j;
    drawTime(timeElapsed);
    switch(gameState)
    {
    case 0://Not ended
        putimage((getwindowwidth()-FACEDIM)>>1, (LEGENDA-FACEDIM)>>1, normal_face_img, COPY_PUT);
        for(i=0;i<INALTIME;++i)
            for(j=0;j<LATIME;++j)
                if(matDescoperit[i][j])
                {
                    drawChecked(j, i);
                    if(mat[i][j])
                        numar(j, i, mat[i][j]);
                }
                else
                    drawUnchecked(j, i);
        break;
    case 1://Win
        putimage((getwindowwidth()-FACEDIM)>>1, (LEGENDA-FACEDIM)>>1, win_face_img, COPY_PUT);
        for(i=0;i<INALTIME;++i)
            for(j=0;j<LATIME;++j)
                if(matDescoperit[i][j])
                {
                    drawChecked(j, i);
                    if(mat[i][j])
                        numar(j, i, mat[i][j]);
                }
                else
                    drawFlag(i, j);
        break;
    case 2://Lose
        putimage((getwindowwidth()-FACEDIM)>>1, (LEGENDA-FACEDIM)>>1, lose_face_img, COPY_PUT);
        for(i=0;i<INALTIME;++i)
            for(j=0;j<LATIME;++j)
                if(matBombe[i][j])
                {
                    drawBomb(i, j);
                }
                else if(matDescoperit[i][j])
                {
                    drawChecked(j, i);
                    if(mat[i][j])
                        numar(j, i, mat[i][j]);
                }
                else
                    drawUnchecked(j, i);
        break;
    }
    setcolor(BLACK);
    rectangle(0, LEGENDA, LATIME*DIMCASUTA, INALTIME*DIMCASUTA+LEGENDA);
    swapbuffers();
}

bool playMinesweeper()
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
    initwindow(DIMCASUTA*LATIME+1, DIMCASUTA*INALTIME+LEGENDA+1, "Minesweeper v. 1.2", 100, 100, true);
    draw(mat, matDescoperit, matBombe);
    while(ok && nrCasuteNeexplorate>NRBOMBE)
    {
        while(!ismouseclick(WM_LBUTTONDOWN))
            if(!started)
                start=time(0);
            else
                draw(mat, matDescoperit, matBombe, time(0)-start);
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
    }
    int now=time(0);
    draw(mat, matDescoperit, matBombe, now-start, 2-ok);
    while(true)
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(x>=DIMCASUTA*LATIME/2-16 && x<=DIMCASUTA*LATIME/2+16 && y>=LEGENDA/2-16 && y<=LEGENDA/2+16)
        {
            closegraph();
            return 1;
        }
        if(y<=LEGENDA)
            return 0;
    }
}