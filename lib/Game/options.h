/**
dCursor отслеживать по следующей схеме:
    get = getcursorpos();
    dCursor += get - set;
    setsursorpos(set);
    Sleep(1);
dCursor - глобальная переменная
    принимающая функция:
        DCursor = 0;
        tempCursor = &DCursor;
        DCursor = &dCursor;
        dCursor = &tempCursor;
В данном случе не будет потерь перемещения курсора и он будет вечно обновляться, не позволяя ограничиться размерами экрана
(за исключением совсем "дерганых" игроков, выводящих за миллисекунду курсор за пол экрана)))
**/

//    extern short PERSON_ID;
//    extern short PERSON_HP;
//    extern XYZf PERSON_POS;
//    extern XYZf PERSON_EYE;

short Game_Prereloading();
short _Game_Prereloading();
POINT DCursor();
XY D_Alpha_Beta();

POINT DCursor()
{
    POINT Cursor_dt;
    GetCursorPos(&Cursor_dt);
    SetCursorPos(resolution.shirina/2,resolution.vysota/2);
    Cursor_dt.x = resolution.shirina/2 - Cursor_dt.x;
    Cursor_dt.y = resolution.vysota/2 - Cursor_dt.y;
    return Cursor_dt;
}

XY D_Alpha_Beta()
{
    XY AlpBet;
    POINT Cursor_dt;
    GetCursorPos(&Cursor_dt);
    SetCursorPos(resolution.shirina/2,resolution.vysota/2);

    AlpBet.x = 0.5 - (double)Cursor_dt.x / resolution.shirina + d_Arrors.x;
    AlpBet.y = 0.5 - (double)Cursor_dt.y / resolution.vysota + d_Arrors.y;
    return AlpBet;
}

short Game_Prereloading()
{
//    PERSON_ID = rand()/65000;
//    PERSON_HP = 100;
//    PERSON_POS = {0., 0., 0.};
//    PERSON_EYE = {1., 0., 0.};
//    int answer;
    GOTO_RETRY:                               /// И единственный его вызов. Мне было лень писать цикл while...
    if(_Game_Prereloading() != 1){
        int answer = MessageBoxA(NULL, "Loading engine error.\nTry again?", "ENGINE ERROR", MB_RETRYCANCEL | MB_ICONWARNING | MB_SETFOREGROUND); // MB_TOPMOST
        switch(answer)
        {
        case IDCANCEL:
            return -1;
            break;
        case IDRETRY:
            goto GOTO_RETRY;              /// Единственное Goto в программе. Простите, программисты...
            break;
        }
    }
    return 1;
}

short _Game_Prereloading()
{
    if(CosFastInit() != 1){
        CosFastDelete();
        return -1;
    }
    return 1;
}
