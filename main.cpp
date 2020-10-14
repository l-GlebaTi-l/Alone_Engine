            ///             распараллеливание распараллеливание РАСПАРАЛЛЕЛИВАНИЕ распараллеливание распараллеливание распараллеливание
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <clocale>
#include <windows.h>
#include <windowsx.h>
#include <math.h>
//#include <conio.h>
//#include <gl/gl.h>

#define Pi 3.1415926
#define G 9.8
#define DEFOLT_TERRAIN_X 60
#define DEFOLT_TERRAIN_Y 60
#define VIZION_FAR 10000000
#define MAX_OBJECTS 256
#define MAX_PLAYERS 32
#define MAX_CARS 64
#define SP(a,b) (a.x*b.x+a.y*b.y+a.z*b.z)
#define        WM_COMPLETE      (WM_USER + 10)
#define        WM_STOP          (WM_USER + 11)
#define        WM_ON_FOCUS      (WM_USER + 12)
#define        WM_CURSOR_CHANGE (WM_USER + 13)

using namespace std;
using namespace chrono;

bool PARAM_Console_On = 0;
bool PARAM_Console_On_loader = 0;

#include "lib/Game/libraries.h"

int main()
{
    if(Game_Prereloading() != 1)
        return -1;
    if(Prereload_Objects("gamedata/.object_adresses.txt", "gamedata/.player_models.txt", "gamedata/.transport_adresses.txt") != 1)
        return -2;
    resolution.shirina = GetSystemMetrics(SM_CXSCREEN);
    resolution.vysota = GetSystemMetrics(SM_CYSCREEN);
    PARAM_Sootnoshenie_storon = (double)resolution.shirina / (double)resolution.vysota;
    pixels = new unsigned char[resolution.shirina*resolution.vysota*4];
    ipixels = (int*)pixels;
    z_buffer = new double[resolution.shirina*resolution.vysota];
    z_buffer_char = new unsigned char[resolution.shirina*resolution.vysota*4];
    image_defolt_F(100,100,100);
    HANDLE Thread;
    Thread = CreateThread(NULL, 0, WinMain_GameScreen, NULL, 0, 0);
    cout << "Hello world!" << endl;
    WaitForSingleObject(Thread, INFINITE);
    cout << "Bye bye world!" << endl;
    f_exit = 27;
    CosFastDelete();
    delete(pixels);
    delete(z_buffer);
    cout << "Cadrs = " << IAI << endl;
    //*/
    return 0;
}




/**
    Миш, привет, С Днем Рождения! Прости дурака, за последнее время так заучился, что на каждом шагу туплю...
    Хочу пожелать тебе настоящего мужского счастья - чтобы с Женей всегда были теплые, приятные и желанные отношения,
    чтобы Паша всегда брал пример твоей заботы, чувства юмора и у него была бы такая же неотразимая улыбка и чтобы
    никакие карантины и прочие проблемы не были преградой для ваших путешествий! Оставайся таким же весёлым, добрым
    и нашим с Кристинкой лучшим другом!
**/
