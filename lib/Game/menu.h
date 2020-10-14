int But_N = 4;
Button *Buttons;


int Menu_Options(int num, HWND hwnd)
{
//    PostMessageA(hwnd, WM_CURSOR_CHANGE, 0, 0);
    switch(num){
    case 0:
        {
            if(PARAM_Console_On == 1)
                cout << "BUTTON 0!" << endl;
            PARAM_InGame_Work = 1;
            PostMessageA(hwnd, WM_CURSOR_CHANGE, 0, 0);
            CreateThread(NULL, 0, Player_Vision, hwnd, 0, 0);
            return 0;
        }
        break;
    case 1:
        {
            if(PARAM_Console_On == 1)
                cout << "BUTTON 1!" << endl;
        }
        break;
    case 2:
        {
            if(PARAM_Console_On == 1)
                cout << "BUTTON 2!" << endl;
            PARAM_InGame_Work = 2;
            CreateThread(NULL, 0, Terrain_Painter, hwnd, 0, 0);
        }
        break;
    case 3:
        {
            if(PARAM_Console_On == 1)
                cout << "BUTTON 3!" << endl;
            W__Objs[0].g_id = 0;
            W__Objs[0].model_id = 2;
            W__Objs[0].pos = {5, 0, 0};
            NUM_OBJECTS++;

            W__Objs[1].g_id = 0;
            W__Objs[1].model_id = 3;
            W__Objs[1].pos = {5, 3, 0};
            NUM_OBJECTS++;

            W__Objs[2].g_id = 0;
            W__Objs[2].model_id = 7;
            W__Objs[2].pos = {-6, 0, 1};
            NUM_OBJECTS++;

            short ttt = time(0);
            W__Cars[NUM_CARS] = {ttt, 0, 500, {0., 5., 0.}, {1., 0., 0.}, {0., 1., 0.}, {0., 0., 1.}, 0, 0, 0, CARPARKED_};
            NUM_CARS++;
//struct World_Objects {
//    short g_id;
//    short model_id = -1;
//    XYZ pos = {0., 0., 0.};
//    XYZ EX = {1., 0., 0.};
//    XYZ EY = {0., 1., 0.};
//    XYZ EZ = {0., 0., 1.};
//    AnimObj Animation = OBJSTAY_;
//};
        }
        break;
    case 4:
        {
            if(PARAM_Console_On == 1)
                cout << "BUTTON 4!" << endl;
            if(PARAM_Console_On == 0)
                PARAM_Console_On = 1;
            else
                PARAM_Console_On = 0;
        }
        break;
    case 5:
        {
            if(PARAM_Console_On == 1)
                cout << "BUTTON 5!" << endl;
            f_exit = 27;
        }
        break;
    case 6:
        {
            if(MessageBoxA(NULL, "Create server?", "Local game", MB_YESNO | MB_ICONQUESTION | MB_SETFOREGROUND) == IDYES)
                CreateThread(NULL, 0, Server::SERVER_CREATE, NULL, 0, 0);
            else
                CreateThread(NULL, 0, Client::CLIENT_CONNECT, NULL, 0, 0);
//            cout << "6" << endl;
        }
        break;
    }
    return -1;
}
