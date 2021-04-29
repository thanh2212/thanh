#include <iostream>
#include <SDL.h>
#include <ctime>
#include "my_library.h"

using namespace std;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Game 2048";

bool kiem_tra_thang(int p[4][4]);
bool kiem_tra_thua(int p[4][4]);
int num_ran();
void  box_ran(int &hang,int &cot,int p[4][4]);
void in_ra_1(SDL_Renderer* renderer,SDL_Texture *nen2048,SDL_Texture *batdau,SDL_Texture *huongdan,SDL_Texture *thoat,int x);
void in_ra_2(SDL_Renderer* renderer,SDL_Texture *huongdanchitiet,SDL_Texture *quaylai);
void in_ra_3(SDL_Renderer* renderer,int p[4][4],SDL_Texture *quaylai,SDL_Texture *pic2,SDL_Texture *pic4,SDL_Texture *pic8,SDL_Texture *pic16,SDL_Texture *pic32,SDL_Texture *pic64,SDL_Texture *pic128,SDL_Texture *pic256,SDL_Texture *pic512,SDL_Texture *pic1024,SDL_Texture *pic2048);
bool hai_o_bang_nhau(int p[4][4]);
bool hai_o_bang_nhau_trai_phai(int p[4][4]);
bool hai_o_bang_nhau_tren_duoi(int p[4][4]);
bool day_so(int p[4][4]);

int main(int argc,char* argv[])
{
    srand(time(NULL));
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    SDL_Texture *nen2048 = loadTexture("nen2048.bmp", renderer);
    SDL_Texture *batdau = loadTexture("batdau.bmp", renderer);
    SDL_Texture *huongdan = loadTexture("huongdan.bmp", renderer);
    SDL_Texture *huongdanchitiet = loadTexture("huongdanchitiet.bmp", renderer);
    SDL_Texture *thoat = loadTexture("thoat.bmp", renderer);
    SDL_Texture *quaylai = loadTexture("quaylai.bmp", renderer);
    SDL_Texture *picwin = loadTexture("win.bmp", renderer);
    SDL_Texture *picgv = loadTexture("gameover.bmp", renderer);
    SDL_Texture *pic2 = loadTexture("a2.bmp", renderer);
    SDL_Texture *pic4 = loadTexture("a4.bmp", renderer);
    SDL_Texture *pic8 = loadTexture("a8.bmp", renderer);
    SDL_Texture *pic16 = loadTexture("a16.bmp", renderer);
    SDL_Texture *pic32 = loadTexture("a32.bmp", renderer);
    SDL_Texture *pic64 = loadTexture("a64.bmp", renderer);
    SDL_Texture *pic128 = loadTexture("a128.bmp", renderer);
    SDL_Texture *pic256 = loadTexture("a256.bmp", renderer);
    SDL_Texture *pic512 = loadTexture("a512.bmp", renderer);
    SDL_Texture *pic1024 = loadTexture("a1024.bmp", renderer);
    SDL_Texture *pic2048 = loadTexture("a2048.bmp", renderer);
    if (quaylai==nullptr||thoat==nullptr||huongdanchitiet==nullptr||huongdan==nullptr||batdau==nullptr||nen2048==nullptr||picwin== nullptr||picgv== nullptr||pic2== nullptr||pic4== nullptr||pic8== nullptr||pic16== nullptr||pic32== nullptr||pic64== nullptr||pic128== nullptr||pic256== nullptr||pic512== nullptr||pic1024== nullptr||pic2048== nullptr){
        SDL_DestroyTexture(quaylai);
        SDL_DestroyTexture(thoat);
        SDL_DestroyTexture(huongdanchitiet);
        SDL_DestroyTexture(huongdan);
        SDL_DestroyTexture(batdau);
        SDL_DestroyTexture(nen2048);
        SDL_DestroyTexture(picwin);
        SDL_DestroyTexture(picgv);
        SDL_DestroyTexture(pic2);
        SDL_DestroyTexture(pic4);
        SDL_DestroyTexture(pic8);
        SDL_DestroyTexture(pic16);
        SDL_DestroyTexture(pic32);
        SDL_DestroyTexture(pic64);
        SDL_DestroyTexture(pic128);
        SDL_DestroyTexture(pic256);
        SDL_DestroyTexture(pic512);
        SDL_DestroyTexture(pic1024);
        SDL_DestroyTexture(pic2048);
        quitSDL(window, renderer);
    }
    SDL_Event e;

    int toa_do_2048=0;
    while (true) {
        if(toa_do_2048>1200)
        {
            toa_do_2048=-300;
        }
        in_ra_1(renderer,nen2048,batdau,huongdan,thoat,toa_do_2048);
        toa_do_2048++;
        while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) return 0;
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            if(e.button.x>=400&&e.button.x<=700)
            {
                if(e.button.y>=300&&e.button.y<=370)
                {
                    int p[4][4];
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            p[i][j]=0;
                        }
                    }

                    int hang1,cot1;
                    box_ran(hang1,cot1,p);
                    p[hang1][cot1]=num_ran();
                    box_ran(hang1,cot1,p);
                    p[hang1][cot1]=num_ran();
                    in_ra_3(renderer,p,quaylai,pic2,pic4,pic8,pic16,pic32,pic64,pic128,pic256,pic512,pic1024,pic2048);

                    for(int l=1;l>0;l++)
                    {
                        if (e.type == SDL_MOUSEBUTTONDOWN)
                        {
                            if(e.button.x>=500&&e.button.x<=700&&e.button.y>=520&&e.button.y<=590)
                            {
                                break;
                            }
                        }
                        SDL_Delay(100);
                        if ( SDL_WaitEvent(&e) == 0) continue;
                        if (e.type == SDL_QUIT) break;

                        if (e.type == SDL_KEYDOWN){
                            switch(e.key.keysym.sym){
                                case SDLK_ESCAPE: break;
                                case SDLK_LEFT:
                                    {
                                    bool khong_duoc=false;
                                    for(int h=0;h<4;h++)
                                    {
                                        int cot=0;
                                        for(int c=0;c<4;c++)
                                        {
                                            if(p[h][c]!=0)
                                            {
                                                if(cot!=c)
                                                {
                                                    khong_duoc=true;
                                                }
                                                int x=p[h][c];
                                                p[h][c]=0;
                                                p[h][cot]=x;
                                                cot++;
                                            }
                                        }
                                    }
                                    bool bang_nhau=hai_o_bang_nhau_trai_phai(p);
                                    if(khong_duoc==false&&bang_nhau==false)
                                    {
                                        break;
                                    }
                                    if(p[0][0]==p[0][1])
                                    {
                                        p[0][0]=2*p[0][0];
                                        p[0][1]=0;
                                    }
                                    if(p[0][1]==p[0][2])
                                    {
                                        p[0][1]=2*p[0][1];
                                        p[0][2]=0;
                                    }
                                    if(p[0][2]==p[0][3])
                                    {
                                        p[0][2]=2*p[0][2];
                                        p[0][3]=0;
                                    }

                                    if(p[1][0]==p[1][1])
                                    {
                                        p[1][0]=2*p[1][0];
                                        p[1][1]=0;
                                    }
                                    if(p[1][1]==p[1][2])
                                    {
                                        p[1][1]=2*p[1][1];
                                        p[1][2]=0;
                                    }
                                    if(p[1][2]==p[1][3])
                                    {
                                        p[1][2]=2*p[1][2];
                                        p[1][3]=0;
                                    }

                                    if(p[2][0]==p[2][1])
                                    {
                                        p[2][0]=2*p[2][0];
                                        p[2][1]=0;
                                    }
                                    if(p[2][1]==p[2][2])
                                    {
                                        p[2][1]=2*p[2][1];
                                        p[2][2]=0;
                                    }
                                    if(p[2][2]==p[2][3])
                                    {
                                        p[2][2]=2*p[2][2];
                                        p[2][3]=0;
                                    }

                                    if(p[3][0]==p[3][1])
                                    {
                                        p[3][0]=2*p[3][0];
                                        p[3][1]=0;
                                    }
                                    if(p[3][1]==p[3][2])
                                    {
                                        p[3][1]=2*p[3][1];
                                        p[3][2]=0;
                                    }
                                    if(p[3][2]==p[3][3])
                                    {
                                        p[3][2]=2*p[3][2];
                                        p[3][3]=0;
                                    }
                                    for(int h=0;h<4;h++)
                                    {
                                        int cot=0;
                                        for(int c=0;c<4;c++)
                                        {
                                            if(p[h][c]!=0)
                                            {
                                                int x=p[h][c];
                                                p[h][c]=0;
                                                p[h][cot]=x;
                                                cot++;
                                            }
                                        }
                                    }
                                    box_ran(hang1,cot1,p);
                                    p[hang1][cot1]=num_ran();
                                    in_ra_3(renderer,p,quaylai,pic2,pic4,pic8,pic16,pic32,pic64,pic128,pic256,pic512,pic1024,pic2048);
                                break;
                                }
                                case SDLK_RIGHT:
                                    {
                                    bool khong_duoc=false;
                                    for(int h=0;h<4;h++)
                                    {
                                        int cot=3;
                                        for(int c=3;c>=0;c--)
                                        {
                                            if(p[h][c]!=0)
                                            {
                                                if(cot!=c)
                                                {
                                                    khong_duoc=true;
                                                }
                                                int x=p[h][c];
                                                p[h][c]=0;
                                                p[h][cot]=x;
                                                cot--;
                                            }
                                        }
                                    }
                                    bool bang_nhau=hai_o_bang_nhau_trai_phai(p);
                                    if(khong_duoc==false&&bang_nhau==false)
                                    {
                                        break;
                                    }
                                    if(p[0][3]==p[0][2])
                                    {
                                        p[0][3]=2*p[0][3];
                                        p[0][2]=0;
                                    }
                                    if(p[0][2]==p[0][1])
                                    {
                                        p[0][2]=2*p[0][2];
                                        p[0][1]=0;
                                    }
                                    if(p[0][1]==p[0][0])
                                    {
                                        p[0][1]=2*p[0][1];
                                        p[0][0]=0;
                                    }

                                    if(p[1][3]==p[1][2])
                                    {
                                        p[1][3]=2*p[1][3];
                                        p[1][2]=0;
                                    }
                                    if(p[1][2]==p[1][1])
                                    {
                                        p[1][2]=2*p[1][2];
                                        p[1][1]=0;
                                    }
                                    if(p[1][1]==p[1][0])
                                    {
                                        p[1][1]=2*p[1][1];
                                        p[1][0]=0;
                                    }

                                    if(p[2][3]==p[2][2])
                                    {
                                        p[2][3]=2*p[2][3];
                                        p[2][2]=0;
                                    }
                                    if(p[2][2]==p[2][1])
                                    {
                                        p[2][2]=2*p[2][2];
                                        p[2][1]=0;
                                    }
                                    if(p[2][1]==p[2][0])
                                    {
                                        p[2][1]=2*p[2][1];
                                        p[2][0]=0;
                                    }

                                    if(p[3][3]==p[3][2])
                                    {
                                        p[3][3]=2*p[3][3];
                                        p[3][2]=0;
                                    }
                                    if(p[3][2]==p[3][1])
                                    {
                                        p[3][2]=2*p[3][2];
                                        p[3][1]=0;
                                    }
                                    if(p[3][1]==p[3][0])
                                    {
                                        p[3][1]=2*p[3][1];
                                        p[3][0]=0;
                                    }
                                    for(int h=0;h<4;h++)
                                    {
                                        int cot=3;
                                        for(int c=3;c>=0;c--)
                                        {
                                            if(p[h][c]!=0)
                                            {
                                                int x=p[h][c];
                                                p[h][c]=0;
                                                p[h][cot]=x;
                                                cot--;
                                            }
                                        }
                                    }
                                    box_ran(hang1,cot1,p);
                                    p[hang1][cot1]=num_ran();
                                    in_ra_3(renderer,p,quaylai,pic2,pic4,pic8,pic16,pic32,pic64,pic128,pic256,pic512,pic1024,pic2048);
                                break;
                                }
                                case SDLK_DOWN:
                                    {
                                    bool khong_duoc=false;
                                    for(int c=0;c<4;c++)
                                    {
                                        int hang=3;
                                        for(int h=3;h>=0;h--)
                                        {
                                            if(p[h][c]!=0)
                                            {
                                                if(hang!=h)
                                                {
                                                    khong_duoc=true;
                                                }
                                                int x=p[h][c];
                                                p[h][c]=0;
                                                p[hang][c]=x;
                                                hang--;
                                            }
                                        }
                                    }
                                    bool bang_nhau=hai_o_bang_nhau_tren_duoi(p);
                                    if(khong_duoc==false&&bang_nhau==false)
                                    {
                                        break;
                                    }
                                    if(p[3][0]==p[2][0])
                                    {
                                        p[3][0]=2*p[3][0];
                                        p[2][0]=0;
                                    }
                                    if(p[2][0]==p[1][0])
                                    {
                                        p[2][0]=2*p[2][0];
                                        p[1][0]=0;
                                    }
                                    if(p[1][0]==p[0][0])
                                    {
                                        p[1][0]=2*p[1][0];
                                        p[0][0]=0;
                                    }

                                    if(p[3][1]==p[2][1])
                                    {
                                        p[3][1]=2*p[3][1];
                                        p[2][1]=0;
                                    }
                                    if(p[2][1]==p[1][1])
                                    {
                                        p[2][1]=2*p[2][1];
                                        p[1][1]=0;
                                    }
                                    if(p[1][1]==p[0][1])
                                    {
                                        p[1][1]=2*p[1][1];
                                        p[0][1]=0;
                                    }

                                    if(p[3][2]==p[2][2])
                                    {
                                        p[3][2]=2*p[3][2];
                                        p[2][2]=0;
                                    }
                                    if(p[2][2]==p[1][2])
                                    {
                                        p[2][2]=2*p[2][2];
                                        p[1][2]=0;
                                    }
                                    if(p[1][2]==p[0][2])
                                    {
                                        p[1][2]=2*p[1][2];
                                        p[0][2]=0;
                                    }

                                    if(p[3][3]==p[2][3])
                                    {
                                        p[3][3]=2*p[3][3];
                                        p[2][3]=0;
                                    }
                                    if(p[2][3]==p[1][3])
                                    {
                                        p[2][3]=2*p[2][3];
                                        p[1][3]=0;
                                    }
                                    if(p[1][3]==p[0][3])
                                    {
                                        p[1][3]=2*p[1][3];
                                        p[0][3]=0;
                                    }
                                    for(int c=0;c<4;c++)
                                    {
                                        int hang=3;
                                        for(int h=3;h>=0;h--)
                                        {
                                            if(p[h][c]!=0)
                                            {
                                                int x=p[h][c];
                                                p[h][c]=0;
                                                p[hang][c]=x;
                                                hang--;
                                            }
                                        }
                                    }
                                    box_ran(hang1,cot1,p);
                                    p[hang1][cot1]=num_ran();
                                    in_ra_3(renderer,p,quaylai,pic2,pic4,pic8,pic16,pic32,pic64,pic128,pic256,pic512,pic1024,pic2048);
                                break;
                                }
                                case SDLK_UP:
                                    {
                                    bool khong_duoc=false;
                                    for(int c=0;c<4;c++)
                                    {
                                        int hang=0;
                                        for(int h=0;h<4;h++)
                                        {
                                            if(p[h][c]!=0)
                                            {
                                                if(hang!=h)
                                                {
                                                    khong_duoc=true;
                                                }
                                                int x=p[h][c];
                                                p[h][c]=0;
                                                p[hang][c]=x;
                                                hang++;
                                            }
                                        }
                                    }
                                    bool bang_nhau=hai_o_bang_nhau_tren_duoi(p);
                                    if(khong_duoc==false&&bang_nhau==false)
                                    {
                                        break;
                                    }
                                    if(p[0][0]==p[1][0])
                                    {
                                        p[0][0]=2*p[0][0];
                                        p[1][0]=0;
                                    }
                                    if(p[1][0]==p[2][0])
                                    {
                                        p[1][0]=2*p[1][0];
                                        p[2][0]=0;
                                    }
                                    if(p[2][0]==p[3][0])
                                    {
                                        p[2][0]=2*p[2][0];
                                        p[3][0]=0;
                                    }

                                    if(p[0][1]==p[1][1])
                                    {
                                        p[0][1]=2*p[0][1];
                                        p[1][1]=0;
                                    }
                                    if(p[1][1]==p[2][1])
                                    {
                                        p[1][1]=2*p[1][1];
                                        p[2][1]=0;
                                    }
                                    if(p[2][1]==p[3][1])
                                    {
                                        p[2][1]=2*p[2][1];
                                        p[3][1]=0;
                                    }

                                    if(p[0][2]==p[1][2])
                                    {
                                        p[0][2]=2*p[0][2];
                                        p[1][2]=0;
                                    }
                                    if(p[1][2]==p[2][2])
                                    {
                                        p[1][2]=2*p[1][2];
                                        p[2][2]=0;
                                    }
                                    if(p[2][2]==p[3][2])
                                    {
                                        p[2][2]=2*p[2][2];
                                        p[3][2]=0;
                                    }

                                    if(p[0][3]==p[1][3])
                                    {
                                        p[0][3]=2*p[0][3];
                                        p[1][3]=0;
                                    }
                                    if(p[1][3]==p[2][3])
                                    {
                                        p[1][3]=2*p[1][3];
                                        p[2][3]=0;
                                    }
                                    if(p[2][3]==p[3][3])
                                    {
                                        p[2][3]=2*p[2][3];
                                        p[3][3]=0;
                                    }
                                    for(int c=0;c<4;c++)
                                    {
                                        int hang=0;
                                        for(int h=0;h<4;h++)
                                        {
                                            if(p[h][c]!=0)
                                            {
                                                int x=p[h][c];
                                                p[h][c]=0;
                                                p[hang][c]=x;
                                                hang++;
                                            }
                                        }
                                    }
                                    box_ran(hang1,cot1,p);
                                    p[hang1][cot1]=num_ran();
                                    in_ra_3(renderer,p,quaylai,pic2,pic4,pic8,pic16,pic32,pic64,pic128,pic256,pic512,pic1024,pic2048);
                                break;
                                }
                                default: break;
                            }
                        }
                        bool ket_qua_thang=kiem_tra_thang(p);
                        if(ket_qua_thang==true)
                        {
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                            SDL_RenderClear(renderer);
                            renderTexture(picwin, renderer, 400, 100, 400, 400);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(3000);
                            break;
                        }
                        bool ket_qua_thua=kiem_tra_thua(p);
                        if(ket_qua_thua==true)
                        {
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                            SDL_RenderClear(renderer);
                            renderTexture(picgv, renderer, 400, 100, 400, 400);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(3000);
                            break;
                        }
                    }


                }
                else
                {
                    if(e.button.y>=400&&e.button.y<=470)
                    {
                        while(true)
                        {
                            in_ra_2(renderer,huongdanchitiet,quaylai);
                            SDL_Delay(10);
                            if ( SDL_WaitEvent(&e) == 0) continue;
                            if (e.type == SDL_QUIT) return 0;
                            if (e.type == SDL_MOUSEBUTTONDOWN)
                            {
                                if(e.button.x>=450&&e.button.x<=650&&e.button.y>=500&&e.button.y<=570)
                                {
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        if(e.button.y>=500&&e.button.y<=570)
                        {
                            return 0;
                        }
                    }
                }
            }
        }
    }
}

	waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}


int num_ran()
{
    int n=rand()%10;
    switch(n)
    {
        case 0:case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:
        {
            return 2;
        }
        default:
        {
            return 4;
        }
    }
}

void  box_ran(int &hang,int &cot,int p[4][4])
{
    do
    {
        hang=rand()%4;
        cot=rand()%4;
    }while(p[hang][cot]!=0);
}

void in_ra_1(SDL_Renderer* renderer,SDL_Texture *nen2048,SDL_Texture *batdau,SDL_Texture *huongdan,SDL_Texture *thoat,int x)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    renderTexture(nen2048, renderer, x, 0, 300, 300);
    renderTexture(batdau, renderer, 400, 300, 300, 70);
    renderTexture(huongdan, renderer, 400, 400, 300, 70);
    renderTexture(thoat, renderer, 400, 500, 300, 70);
    SDL_RenderPresent(renderer);
}

void in_ra_2(SDL_Renderer* renderer,SDL_Texture *huongdanchitiet,SDL_Texture *quaylai)
{
    renderTexture(huongdanchitiet, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    renderTexture(quaylai, renderer, 450, 500, 200, 70);
    SDL_RenderPresent(renderer);
}

void in_ra_3(SDL_Renderer* renderer,int p[4][4],SDL_Texture *quaylai,SDL_Texture *pic2,SDL_Texture *pic4,SDL_Texture *pic8,SDL_Texture *pic16,SDL_Texture *pic32,SDL_Texture *pic64,SDL_Texture *pic128,SDL_Texture *pic256,SDL_Texture *pic512,SDL_Texture *pic1024,SDL_Texture *pic2048)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    int toa_do_hang=100,toa_do_cot;
    for(int i=0;i<4;i++)
    {
        toa_do_cot=400;
        for(int j=0;j<4;j++)
        {
            SDL_Rect filled_rect;
            filled_rect.x = toa_do_cot;
            filled_rect.y = toa_do_hang;
            filled_rect.w = 100;
            filled_rect.h = 100;
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &filled_rect);

            if(p[i][j]==2)
                {
                    renderTexture(pic2, renderer, toa_do_cot, toa_do_hang, 100, 100);
                }
            if(p[i][j]==4)
                {
                    renderTexture(pic4, renderer, toa_do_cot, toa_do_hang, 100, 100);
                }
            if(p[i][j]==8)
                {
                    renderTexture(pic8, renderer, toa_do_cot, toa_do_hang, 100, 100);
                }
            if(p[i][j]==16)
                {
                    renderTexture(pic16, renderer, toa_do_cot, toa_do_hang, 100, 100);
                }
            if(p[i][j]==32)
                {
                    renderTexture(pic32, renderer, toa_do_cot, toa_do_hang, 100, 100);
                }
            if(p[i][j]==64)
                {
                    renderTexture(pic64, renderer, toa_do_cot, toa_do_hang, 100, 100);
                }
            if(p[i][j]==128)
                {
                    renderTexture(pic128, renderer, toa_do_cot, toa_do_hang, 100, 100);
                }
            if(p[i][j]==256)
                {
                    renderTexture(pic256, renderer, toa_do_cot, toa_do_hang, 100, 100);
                }
            if(p[i][j]==512)
                {
                    renderTexture(pic512, renderer, toa_do_cot, toa_do_hang, 100, 100);
                }
            if(p[i][j]==1024)
                {
                    renderTexture(pic1024, renderer, toa_do_cot, toa_do_hang, 100, 100);
                }
            if(p[i][j]==2048)
                {
                    renderTexture(pic2048, renderer, toa_do_cot, toa_do_hang, 100, 100);
                }
            toa_do_cot+=100;
        }
        toa_do_hang+=100;
        cout<<endl;
    }
    renderTexture(quaylai, renderer, 500, 520, 200, 70);
    SDL_RenderPresent(renderer);
}

bool kiem_tra_thang(int p[4][4])
{
    bool kt1=false;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(p[i][j]==2048)
            {
                kt1=true;break;
            }
        }
    }
    if(kt1==true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool kiem_tra_thua(int p[4][4])
{
    bool kt1=true;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(p[i][j]==0)
            {
                kt1=false;break;
            }
        }
    }
    if(kt1==false)
    {
        return false;
    }
    else
    {
        bool kt2=hai_o_bang_nhau(p);
        if(kt2==false)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool hai_o_bang_nhau(int p[4][4])
{
    if(p[0][0]==p[0][1])
    {
        return true;
    }
    else
    {
        if(p[0][1]==p[0][2])
        {
            return true;
        }
        else
        {
            if(p[0][2]==p[0][3])
            {
                return true;
            }
            else
            {
                if(p[1][0]==p[1][1])
                {
                    return true;
                }
                else
                {
                    if(p[1][1]==p[1][2])
                    {
                        return true;
                    }
                    else
                    {
                        if(p[1][2]==p[1][3])
                        {
                            return true;
                        }
                        else
                        {
                            if(p[2][0]==p[2][1])
                            {
                                return true;
                            }
                            else
                            {
                                if(p[2][1]==p[2][2])
                                {
                                    return true;
                                }
                                else
                                {
                                    if(p[2][2]==p[2][3])
                                    {
                                        return true;
                                    }
                                    else
                                    {
                                        if(p[3][0]==p[3][1])
                                        {
                                            return true;
                                        }
                                        else
                                        {
                                            if(p[3][1]==p[3][2])
                                            {
                                                return true;
                                            }
                                            else
                                            {
                                                if(p[3][2]==p[3][3])
                                                {
                                                    return true;
                                                }
                                                else
                                                {
                                                    if(p[0][0]==p[1][0])
                                                    {
                                                        return true;
                                                    }
                                                    else
                                                    {
                                                        if(p[1][0]==p[2][0])
                                                        {
                                                            return true;
                                                        }
                                                        else
                                                        {
                                                            if(p[2][0]==p[3][0])
                                                            {
                                                                return true;
                                                            }
                                                            else
                                                            {
                                                                if(p[0][1]==p[1][1])
                                                                {
                                                                    return true;
                                                                }
                                                                else
                                                                {
                                                                    if(p[1][1]==p[2][1])
                                                                    {
                                                                        return true;
                                                                    }
                                                                    else
                                                                    {
                                                                        if(p[2][1]==p[3][1])
                                                                        {
                                                                            return true;
                                                                        }
                                                                        else
                                                                        {
                                                                            if(p[0][2]==p[1][2])
                                                                            {
                                                                                return true;
                                                                            }
                                                                            else
                                                                            {
                                                                                if(p[1][2]==p[2][2])
                                                                                {
                                                                                    return true;
                                                                                }
                                                                                else
                                                                                {
                                                                                    if(p[2][2]==p[3][2])
                                                                                    {
                                                                                        return true;
                                                                                    }
                                                                                    else
                                                                                    {
                                                                                        if(p[0][3]==p[1][3])
                                                                                        {
                                                                                            return true;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            if(p[1][3]==p[2][3])
                                                                                            {
                                                                                                return true;
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                if(p[2][3]==p[3][3])
                                                                                                {
                                                                                                    return true;
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                    return false;
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

bool hai_o_bang_nhau_trai_phai(int p[4][4])
{
    if(p[0][0]==p[0][1]&&p[0][0]!=0)
    {
        return true;
    }
    else
    {
        if(p[0][1]==p[0][2]&&p[0][1]!=0)
        {
            return true;
        }
        else
        {
            if(p[0][2]==p[0][3]&&p[0][2]!=0)
            {
                return true;
            }
            else
            {
                if(p[1][0]==p[1][1]&&p[1][0]!=0)
                {
                    return true;
                }
                else
                {
                    if(p[1][1]==p[1][2]&&p[1][1]!=0)
                    {
                        return true;
                    }
                    else
                    {
                        if(p[1][2]==p[1][3]&&p[1][2]!=0)
                        {
                            return true;
                        }
                        else
                        {
                            if(p[2][0]==p[2][1]&&p[2][0]!=0)
                            {
                                return true;
                            }
                            else
                            {
                                if(p[2][1]==p[2][2]&&p[2][1]!=0)
                                {
                                    return true;
                                }
                                else
                                {
                                    if(p[2][2]==p[2][3]&&p[2][2]!=0)
                                    {
                                        return true;
                                    }
                                    else
                                    {
                                        if(p[3][0]==p[3][1]&&p[3][0]!=0)
                                        {
                                            return true;
                                        }
                                        else
                                        {
                                            if(p[3][1]==p[3][2]&&p[3][1]!=0)
                                            {
                                                return true;
                                            }
                                            else
                                            {
                                                if(p[3][2]==p[3][3]&&p[3][2]!=0)
                                                {
                                                    return true;
                                                }
                                                else
                                                {
                                                    return false;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

bool hai_o_bang_nhau_tren_duoi(int p[4][4])
{
    if(p[0][0]==p[1][0]&&p[0][0]!=0)
    {
        return true;
    }
    else
    {
        if(p[1][0]==p[2][0]&&p[1][0]!=0)
        {
            return true;
        }
        else
        {
            if(p[2][0]==p[3][0]&&p[2][0]!=0)
            {
                return true;
            }
            else
            {
                if(p[0][1]==p[1][1]&&p[0][1]!=0)
                {
                    return true;
                }
                else
                {
                    if(p[1][1]==p[2][1]&&p[1][1]!=0)
                    {
                        return true;
                    }
                    else
                    {
                        if(p[2][1]==p[3][1]&&p[2][1]!=0)
                        {
                            return true;
                        }
                        else
                        {
                            if(p[0][2]==p[1][2]&&p[0][2]!=0)
                            {
                                return true;
                            }
                            else
                            {
                                if(p[1][2]==p[2][2]&&p[1][2]!=0)
                                {
                                    return true;
                                }
                                else
                                {
                                    if(p[2][2]==p[3][2]&&p[2][2]!=0)
                                    {
                                        return true;
                                    }
                                    else
                                    {
                                        if(p[0][3]==p[1][3]&&p[0][3]!=0)
                                        {
                                            return true;
                                        }
                                        else
                                        {
                                            if(p[1][3]==p[2][3]&&p[1][3]!=0)
                                            {
                                                return true;
                                            }
                                            else
                                            {
                                                if(p[2][3]==p[3][3]&&p[2][3]!=0)
                                                {
                                                    return true;
                                                }
                                                else
                                                {
                                                    return false;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
