DWORD WINAPI WinMain_GameScreen (LPVOID param);
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
DWORD WINAPI Player_Vision(LPVOID param);



DWORD WINAPI WinMain_GameScreen (LPVOID param)
{
    HINSTANCE hInst;
    hInst = NULL;
    char Class [] = "Alone_Engine";          // HackClipboard_Class - название программы, которая и дала мне
                                                    // вывод изображения, только там он был с обычного буфера обмена...)
    WNDCLASS wc      = {0};
    ZeroMemory (&wc, sizeof (wc) );

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WindowProcedure;
    wc.hInstance     = hInst;
    wc.hIcon         = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor (NULL, IDC_ARROW);
//    wc.hbrBackground = CreateSolidBrush (RGB (150, 150, 150));
    wc.hbrBackground = NULL;
    wc.lpszClassName = Class;
    wc.lpszMenuName  = NULL;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;

    if (!RegisterClass (&wc))
    {
        if(PARAM_Console_On == 1)
            cout << "Fuck" << endl;
        else
            MessageBox (NULL, "Window Registration Failed!", "Error!", MB_OK | MB_ICONERROR);
        return 0;
    }

    HWND hwnd = CreateWindow (Class, "Engine", /*WS_OVERLAPPEDWINDOW*/ WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, resolution.shirina, resolution.vysota, NULL, NULL, hInst, NULL);
    if (!hwnd)
    {
        if(PARAM_Console_On == 1)
            cout << "Fuck dwa" << endl;
        else
            MessageBox (NULL, "Window Creation Failed!", "Error!", MB_OK | MB_ICONERROR);
        return 0;
    }

    ShowWindow (hwnd, SW_SHOW);
    InvalidateRect(hwnd, 0, 0);         /// 3-ье значение было NULL
    UpdateWindow (hwnd);

    MSG msg;
    while (f_exit != 27)
    {
//        PeekMessageA (&msg, NULL, 0, 0, PM_REMOVE);
        GetMessageA(&msg, NULL, 0, 0);
        TranslateMessage (&msg);
        DispatchMessageA(&msg);
    }
    UnregisterClass (Class, hInst);
    return (int) msg.wParam;
}

DWORD WINAPI TEN_TIMER(LPVOID param)
{
    HWND hwnd = (HWND) param;
    Sleep(10000);
    if(PARAM_Console_On == 1)
        cout << "Cadrs = " << IAI << endl;
    PostMessageA(hwnd, WM_STOP, 0, 0);
    ExitThread(0);
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HBITMAP hImg;
    static BITMAPINFO dbmi;
    static BITMAPINFOHEADER bmih;
    static HDC hdc;
    static HDC hMemDC;
    static PAINTSTRUCT ps;
    static BITMAP bm;
    static double wheelDelta = 0;

    static auto Tm_Start = steady_clock::now();
    static auto Tm_End = steady_clock::now();
    static auto TM_Spend = duration_cast<microseconds>(Tm_End - Tm_Start);
    static WORD FPS;
    static TCHAR FPS_Buf[80];
    Tm_End = steady_clock::now();
    TM_Spend = duration_cast<microseconds>(Tm_End - Tm_Start);
    Tm_Start = Tm_End;
    if(PARAM_InGame_Work == 1){
        switch(msg)
        {
            case WM_CURSOR_CHANGE:
                {
                    if(PARAM_Console_On == 1)
                        cout << "Cursor W1: " << ShowCursor(0) << endl;
                    else
                        ShowCursor(0);
                }
                break;
            case WM_CREATE:
                {
        //            SetTimer (hwnd, 1, 1, NULL);
                    CreateThread(NULL, 0, Player_Vision, hwnd, 0, 0);
                    bmih.biSize     = sizeof(BITMAPINFOHEADER);
                    bmih.biWidth    = resolution.shirina;
                    bmih.biHeight   = resolution.vysota;
                    bmih.biPlanes   = 1;
                    bmih.biBitCount = 32;
                    bmih.biCompression  = BI_RGB;
                    bmih.biSizeImage    = 0;
                    bmih.biXPelsPerMeter    =   10;
                    bmih.biYPelsPerMeter    =   10;
                    bmih.biClrUsed      = 0;
                    bmih.biClrImportant = 0;

                    ZeroMemory(&dbmi, sizeof(dbmi));
                    dbmi.bmiHeader = bmih;
                    dbmi.bmiColors->rgbBlue = 0;
                    dbmi.bmiColors->rgbGreen = 0;
                    dbmi.bmiColors->rgbRed = 0;
                    dbmi.bmiColors->rgbReserved = 0;
        //            CreateThread(NULL, 0, TEN_TIMER, hwnd, 0, 0);
                    PostMessageA(hwnd, WM_CURSOR_CHANGE, 0, 0);
                }
                break;
            case WM_KEYDOWN:
                {
                    if( wParam == ( VkKeyScan('W') & 0xFF )){
                        PARAM_BUTTON_W = 1;
                    }
                    if( wParam == ( VkKeyScan('S') & 0xFF )){
                        PARAM_BUTTON_S = 1;
                    }
                    if( wParam == ( VkKeyScan('A') & 0xFF )){
                        PARAM_BUTTON_A = 1;
                    }
                    if( wParam == ( VkKeyScan('D') & 0xFF )){
                        PARAM_BUTTON_D = 1;
                    }
                    if( wParam == VK_SPACE ){
                        PARAM_BUTTON_SPACE = 1;
                    }
                    if( wParam == VK_CONTROL ){
                        PARAM_BUTTON_CTRL = 1;
                    }
                    if( wParam == VK_SHIFT ){
                        PARAM_BUTTON_SHIFT = 1;
                    }
                    if( wParam == VK_SPACE ){
                        PARAM_BUTTON_SPACE = 1;
                    }
                    if( wParam == VK_PAUSE ){
                        if(PARAM_SLEEP == 0)
                            PARAM_SLEEP = 1;
                        else
                            PARAM_SLEEP = 0;
                    }
                    if( wParam == VK_TAB ){
                        PARAM_BUTTON_TAB = 1;
                    }
                    if( wParam == VK_NUMPAD2 ){
                        d_Arrors.y = -(double)TM_Spend.count()/1000000;
                    }
                    if( wParam == VK_NUMPAD4 ){
                        d_Arrors.x = (double)TM_Spend.count()/1000000;
                    }
                    if( wParam == VK_NUMPAD6 ){
                        d_Arrors.x = -(double)TM_Spend.count()/1000000;
                    }
                    if( wParam == VK_NUMPAD8 ){
                        d_Arrors.y = (double)TM_Spend.count()/1000000;
                    }
                    if( wParam == VK_DOWN ){
                        PARAM_Os.y = -1.;
                        PARAM_Beta = -0.05;
                    }
                    if( wParam == VK_LEFT ){
                        PARAM_Os.z = -1.;
                        PARAM_Alpha = 0.05;
                    }
                    if( wParam == VK_RIGHT ){
                        PARAM_Os.z = 1.;
                        PARAM_Alpha = -0.05;
                    }
                    if( wParam == VK_UP ){
                        PARAM_Os.y = 1.;
                        PARAM_Beta = 0.05;
                    }
                    if( wParam == ( VkKeyScan('Q') & 0xFF )){
                        PARAM_Os.x = 1.;
                    }
                    if( wParam == ( VkKeyScan('E') & 0xFF )){
                        PARAM_Os.x = -1.;
                    }
                    if( wParam == VK_F9 ){
                        if(PARAM_Console_On == 1)
                            cout << "PICK F9" << endl;
                        PARAM_DO_SCREENSHOT = 1;
                    }
                }
                break;
            case WM_MOUSEWHEEL:
                {
                    wheelDelta += GET_WHEEL_DELTA_WPARAM(wParam);
                    for(; wheelDelta > WHEEL_DELTA; wheelDelta -= WHEEL_DELTA){
                        PARAM_Scale -= 0.05;
                    }
                    for(; wheelDelta < 0; wheelDelta += WHEEL_DELTA){
                        PARAM_Scale += 0.05;
                    }
                }
                break;
            case WM_KEYUP:
                {
                    if( wParam == ( VkKeyScan('W') & 0xFF )){
                        PARAM_BUTTON_W = 0;
                    }
                    if( wParam == ( VkKeyScan('S') & 0xFF )){
                        PARAM_BUTTON_S = 0;
                    }
                    if( wParam == ( VkKeyScan('A') & 0xFF )){
                        PARAM_BUTTON_A = 0;
                    }
                    if( wParam == ( VkKeyScan('D') & 0xFF )){
                        PARAM_BUTTON_D = 0;
                    }
                    if( wParam == VK_SPACE ){
                        PARAM_BUTTON_SPACE = 0;
                    }
                    if( wParam == VK_CONTROL ){
                        PARAM_BUTTON_CTRL = 0;
                    }
                    if( wParam == VK_SHIFT ){
                        PARAM_BUTTON_SHIFT = 0;
                    }
                    if( wParam == VK_SPACE ){
                        PARAM_BUTTON_SPACE = 0;
                    }
                    if( wParam == VK_TAB ){
                        PARAM_BUTTON_TAB = 0;
                    }
                    if( wParam == VK_NUMPAD2 ){
                        d_Arrors.y = 0;
                    }
                    if( wParam == VK_NUMPAD4 ){
                        d_Arrors.x = 0;
                    }
                    if( wParam == VK_NUMPAD6 ){
                        d_Arrors.x = 0;
                    }
                    if( wParam == VK_NUMPAD8 ){
                        d_Arrors.y = 0;
                    }
                    if( wParam == VK_DOWN ){
                        PARAM_Os.y = 0.;
                        PARAM_Beta = 0.;
                    }
                    if( wParam == VK_LEFT ){
                        PARAM_Os.z = 0.;
                        PARAM_Alpha = 0.;
                    }
                    if( wParam == VK_RIGHT ){
                        PARAM_Os.z = 0.;
                        PARAM_Alpha = 0.;
                    }
                    if( wParam == VK_UP ){
                        PARAM_Os.y = 0.;
                        PARAM_Beta = 0.;
                    }
                    if( wParam == ( VkKeyScan('Q') & 0xFF )){
                        PARAM_Os.x = 0.;
                    }
                    if( wParam == ( VkKeyScan('E') & 0xFF )){
                        PARAM_Os.x = 0.;
                    }
                }
                break;
            case WM_LBUTTONDOWN:
                PARAM_BUTTON_LKM = 1;
                break;
            case WM_LBUTTONUP:
                PARAM_BUTTON_LKM = 0;
                break;
            case WM_CHAR:
                {
                    switch (wParam)
                    {
                        case 27:    /// Esc
                            {
                                PARAM_InGame_Work = -1;
        //                        f_exit = 27;
                            }
                            break;
                        case 'O':{}
                        case 'o':
                            {
                                if(PARAM_CAR_NABLUDENIE != 0)
                                    PARAM_CAR_NABLUDENIE = 0;
                                else
                                    PARAM_CAR_NABLUDENIE = 1;
                            }
                            break;
                        case 'V':{}
                        case 'v':
                            {
                                if(PARAM_CAMERA_TYPE > 0)
                                    PARAM_CAMERA_TYPE = 0;
                                else
                                    PARAM_CAMERA_TYPE++;
                            }
                            break;
                        case 'K':{}
                        case 'k':
                            {
                                short ttt = time(0);
                                W__Cars[NUM_CARS] = {ttt, 0, 500, {0., 5., 0.}, {1., 0., 0.}, {0., 1., 0.}, {0., 0., 1.}, 0, 0, 0, CARPARKED_};
                                NUM_CARS++;
                            }
                            break;
                        case '`':
                        case 'ё':
                        case 'Ё':
                            {
                                PARAM_IMAGE_TYPE++;
                                if(PARAM_IMAGE_TYPE > 1)
                                    PARAM_IMAGE_TYPE = 0;
                            }
                            break;
                    }
                    if(wParam > 47 && wParam < 58)  /// от 0 до 9
                        PARAM_Object_Choose = wParam - 48;
                }
                break;
            case WM_COMPLETE:
                {
                    static auto FPS_Start = steady_clock::now();
                    static auto FPS_End = steady_clock::now();
                    static auto FPS_Spend = duration_cast<microseconds>(FPS_End - FPS_Start);
                    static int FPS_Time[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                    static int FPS_TenTime;
                    FPS_End = steady_clock::now();
                    FPS_Spend = duration_cast<microseconds>(FPS_End - FPS_Start);
                    FPS_Start = FPS_End;
                    for(int i = 9; i > 0; i--)
                        FPS_Time[i] = FPS_Time[i - 1];
                    FPS_Time[0] = FPS_Spend.count();
                    FPS_TenTime = 0;
                    for(int i = 0; i < 10; i++)
                        FPS_TenTime += FPS_Time[i];

                    if(PARAM_DO_SCREENSHOT == 1){
                        PARAM_DO_SCREENSHOT = 0;
                        char tName[100] = {"screenshots/"}, NameSuffics[] = {".bmp"}, TempName[100];

                        time_t seconds = time(NULL);
                        tm* timeinfo = localtime(&seconds);

                        char format[18] = "%Y.%m.%d %H-%M-%S";
                        strftime(TempName, 100, format, timeinfo);
                        delete(timeinfo);

                        strcat(tName,TempName);
                        strcat(tName,NameSuffics);
                        cout << "Screenshot saved: " << tName << endl;
                        saveBMP(tName, pixels, resolution.shirina, resolution.vysota);
                    }
                    hdc = ::GetDC(NULL);

                    if(PARAM_IMAGE_TYPE == 1){
                        for(int i = 0; i < resolution.vysota*resolution.shirina; i++){
                            z_buffer_char[i*4] = (1 / (sqrt(sqrt(z_buffer[i]) + 1)))*255;
                            z_buffer_char[i*4 + 1] = z_buffer_char[i*4];
                            z_buffer_char[i*4 + 2] = z_buffer_char[i*4];
                        }
                        hImg = CreateDIBitmap(hdc, &bmih, CBM_INIT, z_buffer_char, &dbmi, DIB_RGB_COLORS);
                    }
                    else
                        hImg = CreateDIBitmap(hdc, &bmih, CBM_INIT, pixels, &dbmi, DIB_RGB_COLORS);
                    PARAM_Vyvod = 1;
                    if (hImg == NULL) {
                        if(PARAM_Console_On == 1)
                            cout << "Could not load the desired image image" << endl;
                        return 0;
                    }

                    ::ReleaseDC(NULL, hdc);

                    if (hImg)
                        InvalidateRect(hwnd, NULL, TRUE);
                    hdc = BeginPaint (hwnd, &ps);
                    hMemDC = CreateCompatibleDC(hdc);

                    SelectBitmap(hMemDC, hImg);
                    GetObject (hImg, sizeof (BITMAP), &bm);
                    BitBlt (hdc, 0, 0, bm.bmWidth, bm.bmHeight, hMemDC, 0, 0, SRCCOPY);

                    if(FPS_TenTime > 0){
                        FPS = wsprintf(FPS_Buf, TEXT("%d"), (10000000 / FPS_TenTime));
                        TextOut(hdc, 10, 10, FPS_Buf, FPS);

                    }


                    DeleteDC (hMemDC);
                    EndPaint (hwnd, &ps);
                    DeleteObject(hImg);
                }
                break;
            case WM_DESTROY:
                {
                    f_exit = 27;
                    DeleteObject(hImg);
                    KillTimer (hwnd, 1);
                    PostQuitMessage (0);
                }
                break;
            case WM_SETFOCUS:
                if(PARAM_Console_On == 1)
                    cout << "Focus on!" << endl;
                PARAM_SLEEP = 0;
                break;
            case WM_KILLFOCUS:
                if(PARAM_Console_On == 1)
                    cout << "Kill focus!" << endl;
                PARAM_SLEEP = 1;
                break;
            case WM_STOP:
                {
                    Sleep(5000);
                }
                break;
            case WM_ON_FOCUS:
                {
//                    SetFocus(hwnd);
                    SetForegroundWindow(hwnd);
                }
                break;
    //        default:
    //            return DefWindowProc (hwnd, msg, wParam, lParam);

        }
    }
    else if(PARAM_InGame_Work == -1){
        static bool Is_Picked = 0;
        static bool is_first = 1;
        static bool is_opened = 0;
        static int But_N = 0;
        static Button *Buttons;
        if(is_opened == 0){
            if(PARAM_Console_On == 1)
                cout << "Cursor: " << ShowCursor(1) << endl;
            else
                ShowCursor(1);
            SetTimer(hwnd, 1, 100, NULL);
            is_opened = 1;
        }
        if(is_first == 1){
            ifstream buttons_adresses("gamedata/menu/Menu.menu");
            Buttons = new Button[0];
            if(buttons_adresses.is_open())
                while(!buttons_adresses.eof()){
                    Buttons = (Button*)realloc(Buttons, (But_N + 1)*sizeof(Button));
                    char button_texture_adress[128];
                    double li, lj, posi, posj;
                    buttons_adresses >> li >> lj >> posi >> posj >> button_texture_adress;
                    Buttons[But_N].Button_load(li, lj, posi, posj, button_texture_adress);
                    But_N++;
                    if(PARAM_Console_On == 1)
                        cout << "BUTTONS CREATED" << endl;
                }
            is_first = 0;
            if(PARAM_Console_On == 1)
                cout << is_first << endl;
        }

        switch(msg)
        {
        case WM_TIMER:
            {
                image_defolt_F(100,100,100);
                for(int i = 0; i < But_N; i++)
                    Buttons[i].Paint();
                hdc = ::GetDC(NULL);
                hImg = CreateDIBitmap(hdc, &bmih, CBM_INIT, pixels, &dbmi, DIB_RGB_COLORS);
                PARAM_Vyvod = 1;
                if (hImg == NULL) {
                    if(PARAM_Console_On == 1)
                        cout << "Could not load the desired image image" << endl;
                    return 0;
                }

                ::ReleaseDC(NULL, hdc);

                if (hImg)
                    InvalidateRect(hwnd, NULL, TRUE);
                hdc = BeginPaint (hwnd, &ps);
                hMemDC = CreateCompatibleDC(hdc);

                SelectBitmap(hMemDC, hImg);
                GetObject (hImg, sizeof (BITMAP), &bm);
                BitBlt (hdc, 0, 0, bm.bmWidth, bm.bmHeight, hMemDC, 0, 0, SRCCOPY);
                DeleteObject(hImg);

                DeleteDC (hMemDC);
                EndPaint (hwnd, &ps);
            }
            break;
        case WM_LBUTTONDOWN:
            {
                Is_Picked = 1;
            }
            break;
        case WM_LBUTTONUP:
            {
                if(Is_Picked == 1){
                    POINT Menu_Cursor;
                    GetCursorPos(&Menu_Cursor);
                    if(PARAM_Console_On == 1)
                        cout << "Here!" << endl;
                    for(int i = 0; i < But_N; i++)
                        if(Buttons[i].is_there(Menu_Cursor) == 1){
                            if(Menu_Options(i, hwnd) == 0){
                                is_opened = 0;
                                KillTimer(hwnd, 1);
                            }
                            break;
                        }
                    Is_Picked = 0;
                }
            }
            break;
        case WM_CHAR:
            {
                switch (wParam)
                {
                    case 27:    /// Esc
                        {
                            if(PARAM_Console_On == 1)
                                cout << "EXIT FROM MENU" << endl;
                            PARAM_InGame_Work = 1;
                            PostMessageA(hwnd, WM_CURSOR_CHANGE, 0, 0);
                            is_opened = 0;
                            KillTimer(hwnd, 1);
                            CreateThread(NULL, 0, Player_Vision, hwnd, 0, 0);
                        }
                        break;
                }
                if((int)wParam > 48 && (int)wParam < (49 + But_N))
                    if(Menu_Options(wParam - 49, hwnd) == 0){
                        is_opened = 0;
                        KillTimer(hwnd, 1);
                    }
            }
            break;
        }
    }
    else if(PARAM_InGame_Work == 2){
        switch(msg){
        case WM_LBUTTONDOWN:
            PARAM_Height = 1.;
            break;
        case WM_LBUTTONUP:
            PARAM_Height = 0.;
            break;
        case WM_RBUTTONDOWN:
            PARAM_Height = -1.;
            break;
        case WM_RBUTTONUP:
            PARAM_Height = 0.;
            break;
        case WM_MOUSEWHEEL:
            {
                wheelDelta += GET_WHEEL_DELTA_WPARAM(wParam);
                for(; wheelDelta > WHEEL_DELTA; wheelDelta -= WHEEL_DELTA){
                    PARAM_Paint_L -= 0.05;
                }
                for(; wheelDelta < 0; wheelDelta += WHEEL_DELTA){
                    PARAM_Paint_L += 0.05;
                }
            }
            break;
        case WM_COMPLETE:
            {
    //            fixEnd = steady_clock::now();
    //            fixRez = duration_cast<milliseconds>(fixEnd - fixStt);
    //            cout << "M" << fixRez.count() << endl;
    //            fixStt = steady_clock::now();
                hdc = ::GetDC(NULL);
                hImg = CreateDIBitmap(hdc, &bmih, CBM_INIT, pixels, &dbmi, DIB_RGB_COLORS);
                PARAM_Vyvod = 1;
                if (hImg == NULL) {
                    cout << "Could not load the desired image image" << endl;
                    return 0;
                }

                ::ReleaseDC(NULL, hdc);

                if (hImg)
                    InvalidateRect(hwnd, NULL, TRUE);
                hdc = BeginPaint (hwnd, &ps);
                hMemDC = CreateCompatibleDC(hdc);

                SelectBitmap(hMemDC, hImg);
                GetObject (hImg, sizeof (BITMAP), &bm);
                BitBlt (hdc, 0, 0, bm.bmWidth, bm.bmHeight, hMemDC, 0, 0, SRCCOPY);
                DeleteObject(hImg);

                DeleteDC (hMemDC);
                EndPaint (hwnd, &ps);
            }
            break;
        case WM_CHAR:
            {
                switch (wParam)
                {
                    case 27:    /// Esc
                        {
                            PARAM_InGame_Work = -1;
    //                        f_exit = 27;
                        }
                        break;
                }
            }
            break;
        }
    }
    return DefWindowProc (hwnd, msg, wParam, lParam);
}

DWORD WINAPI Player_Vision(LPVOID param)
{
    HWND hwnd = (HWND) param;
    auto Tm_Start = steady_clock::now();
    auto Tm_End = steady_clock::now();
    auto TM_Spend = duration_cast<microseconds>(Tm_End - Tm_Start);

//
//    static char Car_Name[128] = {"gamedata/Objects/Camero_Proz/camero32.obj"};
//    static OBJ_Transport Car;
//    static bool car_load = 0;
//    if(car_load == 0){
//        Car.Alive_OBJ_(Car_Name, Car_Name, 100);
//        Car.Change_Orientation(312);
//        XYZ dMove = {0., 2., 0.};
//        Car.Move(dMove);
//        car_load = 1;
//    }

    Terrain terrain;
    ifstream terrain_adress("gamedata/terrain.txt");
    if(terrain_adress.is_open())
        terrain.Load_Terrain(terrain_adress);
    terrain_adress.close();

    if(PARAM_Console_On == 1)
        cout << "Created" << endl;
    XY AlpBet;

    PostMessageA(hwnd, WM_ON_FOCUS, 0, 0);

    while(PARAM_InGame_Work == 1){
        if(PARAM_Vyvod == 1){
            while(PARAM_SLEEP == 1)
                Sleep(1);
            image_defolt_F(10, 30, 150);

            Tm_End = steady_clock::now();
            TM_Spend = duration_cast<microseconds>(Tm_End - Tm_Start);
            Tm_Start = Tm_End;

            if(PARAM_BUTTON_TAB == 1){
                if(Bob.IsInCar() == 0 && Bob.is_DoSomething() != 1){
                    for(int i = 0; i < NUM_CARS; i++){
                        if(vct_dlina(vct_is_tocheck(Bob.Get_Pos(), W__Cars[i].pos)) < 2){
                            cout << "Sit in " << i << endl;
                            Bob.SitInCar(i);
                        }
                    }
                    if(Bob.IsInCar() == 0){
                        PARAM_BUTTON_TAB = 0;
                    }
                }
                else if (Bob.is_DoSomething() != 1){
                    Bob.LeftCar();
                }
            }

            AlpBet = D_Alpha_Beta();

//            if(Bob.GetAnim() == PLINCAR_){
//                Bob.Teleport(W__Cars[Bob.GetCarNum()].pos);
//                if(PARAM_CAMERA_TYPE == 0)
//                    Bob.Update_Sitting((double)TM_Spend.count()/1000000, W__Cars[Bob.GetCarNum()].EX, W__Cars[Bob.GetCarNum()].EY, W__Cars[Bob.GetCarNum()].EZ, terrain);
//                else if(PARAM_CAMERA_TYPE == 1)
//                    Bob.Update_Slezenie((double)TM_Spend.count()/1000000, W__Cars[Bob.GetCarNum()].EX, W__Cars[Bob.GetCarNum()].EY, W__Cars[Bob.GetCarNum()].EZ, W__Cars[Bob.GetCarNum()].skorost, W__Cars[Bob.GetCarNum()].povorot, terrain);
//            }
//            else{
//                Bob.Update((double)TM_Spend.count()/1000000, AlpBet.x, AlpBet.y, terrain, W__Players[0]);    /// For every new picture
//            }

            Bob.Update((double)TM_Spend.count()/1000000, AlpBet.x, AlpBet.y, terrain, W__Players[0]);    /// For every new picture
            int i;
            if((i = Bob.GetCarNum()) != -1){
                ID_Car[W__Cars[i].model_id].Update((double)TM_Spend.count()/1000000, terrain, W__Cars[i]);
            }

            Draw_Objects();









            terrain.Paint(Bob);

            IAI++;
            if(PARAM_InGame_Work == 1)
                PostMessageA(hwnd, WM_COMPLETE, 0, 0);
            PARAM_Vyvod = 0;
            GLOBAL_LIGHT = Rotate_Light(GLOBAL_LIGHT, EARTH_NORMAL, SPEED_SUN*(double)TM_Spend.count()/1000000);
            int color;
            *((unsigned char*)&color) = 100;
            *((unsigned char*)&color + 1) = 100;
            *((unsigned char*)&color + 2) = 255;
            int* image = ipixels;
            image[resolution.vysota/2*resolution.shirina + resolution.shirina/2] = color;
            for(int i = 1; i < 4; i++){
                image[(resolution.vysota/2 - i)*resolution.shirina + resolution.shirina/2] = color;
                image[(resolution.vysota/2 + i)*resolution.shirina + resolution.shirina/2] = color;
                image[resolution.vysota/2*resolution.shirina + resolution.shirina/2 + i] = color;
                image[resolution.vysota/2*resolution.shirina + resolution.shirina/2 - i] = color;
            }

            /**
            etx.Start_Dialog();
            while(PARAM_SLEEP == 1)
                Sleep(1);
            image_defolt_F(10, 30, 150);

            Tm_End = steady_clock::now();
            TM_Spend = duration_cast<microseconds>(Tm_End - Tm_Start);
//            cout << "time = " << (double)TM_Spend.count()/1000000 << endl;
            Tm_Start = Tm_End;

            Car.Update_With_Physics((double)TM_Spend.count()/1000000, terrain);

            AlpBet = D_Alpha_Beta();
            if(PARAM_BUTTON_TAB == 1){
                Bob.Teleport(Car.GetPos());
                if(PARAM_CAMERA_TYPE == 0)
                    Bob.Update_Sitting((double)TM_Spend.count()/1000000, Car.GetMatPer(), terrain);
                else if(PARAM_CAMERA_TYPE == 1)
                    Bob.Update_Slezenie((double)TM_Spend.count()/1000000, Car.GetMatPer(), Car.GetSpeed(), Car.GetPovorot(), terrain);
            }
            else
                Bob.Update((double)TM_Spend.count()/1000000, AlpBet.x, AlpBet.y, terrain);    /// For every new picture

            terrain.Paint(Bob);

            Objs_new = Objs;
            Work_Obj = Objs;

            if(PARAM_Object_Choose > -1 && PARAM_Object_Choose < obj_num){
                for(int i = 0; i < PARAM_Object_Choose; i++)
                    Work_Obj = Work_Obj -> next;

                Work_Obj -> obj.scale *= PARAM_Scale;
//                if(PARAM_Alpha != 0 || PARAM_Beta != 0)
//                    Work_Obj -> obj.Povorot(PARAM_Alpha, PARAM_Beta);
                if(PARAM_Os.x != 0 || PARAM_Os.y != 0 || PARAM_Os.z != 0){
                    Work_Obj -> obj.Povorot_Po_Osi_Polzovatel(PARAM_Os, PARAM_Teta);
                }
//                if(PARAM_DO_SCREENSHOT == 1){
//                    PARAM_DO_SCREENSHOT = 0;
//                    if(Work_Obj ->obj.param_have_texture == 1){
//                        Work_Obj ->obj.Show_Texture_On_Ekran();
//                        Sleep(300);
//                    }
//                }
            }
            PARAM_Scale = 1.;

            while(Objs_new != NULL){
                Objs_new -> obj.Paint_Fast(Bob);
//                Objs_new -> obj.Paint_Name(Bob);
                Objs_new = Objs_new -> next;
            }
            if(Car.Is_Alive() == 1){
                Car.Paint_Fast(Bob);
                if(PARAM_BUTTON_LKM == 1){
                    XYZ hitpoint;
                    if(Car.Shoot(Bob, 10, hitpoint) >= 0){
                        XY hitp;
                        hitp = Bob.Where_I_See_Point_In_World(hitpoint);
                        eng.say(hitp.x, hitp.y, 32, "HIT");
                    }
                }
            }

            IAI++;
            if(PARAM_InGame_Work == 1)
                PostMessageA(hwnd, WM_COMPLETE, 0, 0);
                PARAM_Vyvod = 0;
            GLOBAL_LIGHT = Rotate_Light(GLOBAL_LIGHT, EARTH_NORMAL, SPEED_SUN*(double)TM_Spend.count()/1000000);
            int color;
            *((unsigned char*)&color) = 100;
            *((unsigned char*)&color + 1) = 100;
            *((unsigned char*)&color + 2) = 255;
            int* image = ipixels;
            image[resolution.vysota/2*resolution.shirina + resolution.shirina/2] = color;
            for(int i = 1; i < 4; i++){
                image[(resolution.vysota/2 - i)*resolution.shirina + resolution.shirina/2] = color;
                image[(resolution.vysota/2 + i)*resolution.shirina + resolution.shirina/2] = color;
                image[resolution.vysota/2*resolution.shirina + resolution.shirina/2 + i] = color;
                image[resolution.vysota/2*resolution.shirina + resolution.shirina/2 - i] = color;
            }
            //*/
        }
    }
    return 0;
}

//DWORD WINAPI Player_Shooting(LPVOID param)
//{
//    if(Car.Is_Alive() == 1){
//        Car.Paint_Fast(Bob);
//        if(PARAM_BUTTON_LKM == 1){
//            XYZ hitpoint;
//            if(Car.Shoot(Bob, 10, hitpoint) >= 0){
//                XY hitp;
//                hitp = Bob.Where_I_See_Point_In_World(hitpoint);
//                eng.say(hitp.x, hitp.y, 32, "HIT");
//            }
//        }
//    }
//}

DWORD WINAPI Terrain_Painter(LPVOID param)
{
    HWND hwnd = (HWND) param;
    double **terrain;
    int razm_x, razm_y;

    ifstream file_terrain_in("gamedata/terrain.txt");
    if(file_terrain_in.is_open() == 1){
        if(MessageBoxA(NULL, "Create new map?", "Map editing", MB_YESNO | MB_ICONQUESTION | MB_SETFOREGROUND) == IDNO){
            file_terrain_in >> razm_y;
            file_terrain_in >> razm_x;
            terrain = new double*[razm_y];
            for(int i = 0; i < razm_y; i++)
                terrain[i] = new double[razm_x];
            for(int i = 0; i < razm_y; i++)
                for(int j = 0; j < razm_x; j++){
                    file_terrain_in >> terrain[i][j];
                }
        }
        else{
            razm_x = DEFOLT_TERRAIN_X;
            razm_y = DEFOLT_TERRAIN_Y;
            terrain = new double*[razm_y];
            for(int i = 0; i < razm_y; i++)
                terrain[i] = new double[razm_x];
            for(int i = 0; i < DEFOLT_TERRAIN_Y; i++)
                for(int j = 0; j < DEFOLT_TERRAIN_X; j++){
                    terrain[i][j] = 0.;
                }
        }
    }
    else{
        razm_x = DEFOLT_TERRAIN_X;
        razm_y = DEFOLT_TERRAIN_Y;
        terrain = new double*[razm_y];
        for(int i = 0; i < razm_y; i++)
            terrain[i] = new double[razm_x];
        for(int i = 0; i < DEFOLT_TERRAIN_Y; i++)
            for(int j = 0; j < DEFOLT_TERRAIN_X; j++){
                terrain[i][j] = 0.;
            }
    }
    file_terrain_in.close();

    image_defolt(3,10,30);
    POINT Cursor;
    double height;
    static int razm;
    while(PARAM_InGame_Work == 2){
//        if(PARAM_Vyvod == 1){
            razm = PARAM_Paint_L;
            if(PARAM_Height != 0){
                GetCursorPos(&Cursor);
                if(PARAM_Console_On == 1)
                    cout << "1 " << Cursor.x << " " << Cursor.y << endl;
                Cursor.x -= resolution.shirina/2 - razm_x/2;
                Cursor.y -= resolution.vysota/2 - razm_y/2;
                if(PARAM_Console_On == 1)
                    cout << "2 " << Cursor.x << " " << Cursor.y << endl;
//                if(Cursor.y < TR && Cursor.y >= 0 && Cursor.x < TR && Cursor.x >= 0)
//                    terrain[Cursor.y][Cursor.x] += PARAM_Height;
                height = PARAM_Height;
                for(double i = -razm; i <= razm; i++){
                    for(double j = -razm; j <= razm; j++){
                        if(sqrt(i*i + j*j) <= razm){
                            if(Cursor.y + i < razm_y && Cursor.y + i >= 0 && Cursor.x + j < razm_x && Cursor.x + j >= 0)
                                terrain[razm_y - 1 - (Cursor.y + (int)i)][Cursor.x + (int)j] += 2*height - height*sqrt(i*i + j*j)/razm;
                        }
                    }
                }
            }

            image_defolt(3,10,30);
            for(int i = 0; i < razm_y; i++)
                for(int j = 0; j < razm_x; j++){
                    pixels[resolution.shirina*(resolution.vysota - 1 - (resolution.vysota/2 - razm_y/2 + i))*4 + (resolution.shirina/2 - razm_x/2 + j)*4] = terrain[razm_y - 1 - i][j];
                    pixels[resolution.shirina*(resolution.vysota - 1 - (resolution.vysota/2 - razm_y/2 + i))*4 + (resolution.shirina/2 - razm_x/2 + j)*4 + 1] = terrain[razm_y - 1 - i][j];
                    pixels[resolution.shirina*(resolution.vysota - 1 - (resolution.vysota/2 - razm_y/2 + i))*4 + (resolution.shirina/2 - razm_x/2 + j)*4 + 2] = terrain[razm_y - 1 - i][j];
                }

            PostMessageA(hwnd, WM_COMPLETE, 0, 0);
            PARAM_Vyvod = 0;
//        }
    }

    ofstream file_terrain_out("gamedata/terrain.txt");
    file_terrain_out << razm_y << " " << razm_x << endl;
    for(int i = 0; i < razm_y; i++){
        for(int j = 0; j < razm_x; j++){
            file_terrain_out << terrain[i][j];
            if(j < razm_x - 1)
                file_terrain_out << " ";    /// или "\t"
        }
        if(i < razm_y - 1)
            file_terrain_out << endl;
    }
    file_terrain_out.close();
    for(int i = 0; i < razm_y; i++)
        delete(terrain[i]);
    delete(terrain);
    return 0;
}

