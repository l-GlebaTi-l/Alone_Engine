Player Bob;

Object_OBJ *ID_Obj;
Alive_OBJ *ID_Gamer;
OBJ_Transport *ID_Car;

int NUM_OBJECTS = 0;
int NUM_PLAYERS = 0;
int NUM_CARS = 0;

//int IsLoaded_obj(short g_id);
//int IsLoaded_player(short g_id);
//int IsLoaded_car(short g_id);

bool Prereload_Objects(const char* file_objects, const char* file_human, const char* file_cars)
{
    static bool answer = 1;
    static int id_obj_num = 9;
    static int id_player_num = 1;
    static int id_car_num = 2;
    int obj_num = 0;
    int player_num = 0;
    int car_num = 0;

    ifstream mod_obj_adr(file_objects);
    if(mod_obj_adr.is_open() == 0){
        PARAM_OBJ_ADRESSES = 0;
    }
    else{
        PARAM_OBJ_ADRESSES = 1;
//        mod_obj_adr >> id_obj_num;
    }
    ID_Obj = new Object_OBJ[id_obj_num];

    if(PARAM_Console_On_loader == 1)
        cout << "LOADED Objects:" << endl;
    while(answer == 1){
        char tName[100] = {"gamedata/Objects/"}, Name[100], NameSuffics[] = {".obj"}, TempName[100];
        if(PARAM_OBJ_ADRESSES == 1)
            mod_obj_adr >> TempName;
        else
            break;
        strcat(tName,TempName);
        strcat(tName,NameSuffics);
        OemToChar(tName,Name);
        if(PARAM_Console_On_loader == 1)
            cout << "\t" << Name << endl;

        ID_Obj[obj_num].Object_OBJ_(Name);
        if(mod_obj_adr.eof() != 1){
            int orientation;
            mod_obj_adr >> orientation;
            if(orientation == 132 || orientation == 213 || orientation == 231 || orientation == 321 || orientation == 312){
                ID_Obj[obj_num].Change_Orientation(orientation);
            }
            mod_obj_adr >> ID_Obj[obj_num].scale;
        }
        obj_num++;

        if(mod_obj_adr.eof() == 1)
            answer = 0;
    }
    mod_obj_adr.close();

    ifstream mod_pl_adr(file_human);
    if(mod_pl_adr.is_open() == 0){
        PARAM_OBJ_ADRESSES = 0;
    }
    else{
        PARAM_OBJ_ADRESSES = 1;
//        mod_obj_adr >> id_player_num;
    }
    ID_Gamer = new Alive_OBJ[id_player_num];

    if(PARAM_Console_On_loader == 1)
        cout << "LOADED Player models:" << endl;
    while( PARAM_OBJ_ADRESSES == 1 ){
        char tName[100] = {"gamedata/PlayerModels/"}, Name[100], NameSuffics[] = {".obj"}, TempName[100];
        if(PARAM_OBJ_ADRESSES == 1)
            mod_pl_adr >> TempName;
        else
            break;
        strcat(tName,TempName);
        strcat(tName,NameSuffics);
        OemToChar(tName,Name);

        char HtName[100] = {"gamedata/PlayerModels/"}, HName[100], HNameSuffics[] = {".obj"}, HTempName[100];
        if(PARAM_OBJ_ADRESSES == 1)
            mod_pl_adr >> HTempName;
        else
            break;
        strcat(HtName,HTempName);
        strcat(HtName,HNameSuffics);
        OemToChar(HtName,HName);
        if(PARAM_Console_On_loader == 1)
            cout << "\t" << Name << endl;

        ID_Gamer[player_num].Alive_OBJ_(Name, HName, 100);
        if(mod_pl_adr.eof() != 1){
            int orientation;
            mod_pl_adr >> orientation;
            if(orientation == 132 || orientation == 213 || orientation == 231 || orientation == 321 || orientation == 312){
                ID_Gamer[player_num].Change_Orientation(orientation);
            }
//            mod_pl_adr >> ID_Gamer[player_num].scale;
        }
        player_num++;

        if(mod_pl_adr.eof() == 1)
            break;
    }
    mod_pl_adr.close();

    ifstream mod_car_adr(file_cars);
    if(mod_car_adr.is_open() == 0){
        PARAM_OBJ_ADRESSES = 0;
    }
    else{
        PARAM_OBJ_ADRESSES = 1;
//        mod_obj_adr >> id_car_num;
    }
    ID_Car = new OBJ_Transport[id_car_num];

    if(PARAM_Console_On_loader == 1)
        cout << "LOADED Cars:" << endl;
    while( PARAM_OBJ_ADRESSES == 1 ){
        char tName[100] = {"gamedata/Transport/"}, Name[100], NameSuffics[] = {".obj"}, TempName[100];
        if(PARAM_OBJ_ADRESSES == 1)
            mod_car_adr >> TempName;
        else
            break;
        strcat(tName,TempName);
        strcat(tName,NameSuffics);
        OemToChar(tName,Name);
        if(PARAM_Console_On_loader == 1)
            cout << "\t" << Name << endl;

        ID_Car[car_num].OBJ_Transport_(Name, Name, 500);
        if(mod_car_adr.eof() != 1){
            int orientation;
            mod_car_adr >> orientation;
            if(orientation == 132 || orientation == 213 || orientation == 231 || orientation == 321 || orientation == 312){
                ID_Car[car_num].Change_Orientation(orientation);
            }
//            mod_car_adr >> ID_Car[car_num].scale;
        }
        car_num++;

        if(mod_car_adr.eof() == 1)
            break;
    }
    mod_car_adr.close();

    short t = time(0)%10000;
    cout << "Your id is: " << t << endl;
    W__Players[0] = {t, 0, 100, -1, {0., 0., 0.,}, {1., 0., 0.}, {0., 1., 0.}, {0., 0., 1.}, PLSTAY_};
    NUM_PLAYERS++;
    return 1;
}
