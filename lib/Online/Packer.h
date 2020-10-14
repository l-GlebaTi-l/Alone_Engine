//bool Pack(World_Players P, unsigned char* dat);
//bool Pack(World_Objects P, unsigned char* dat);
//bool Pack(World_Cars P, unsigned char* dat);
//bool PackAll(unsigned char* dat);
//bool unPack(unsigned char* dat);

void vct_print(XYZ A)                           // бшбнд бейрнпю б йнмянкэ
{
    cout << A.x << " ";
    cout << A.y << " ";
    cout << A.z << endl;
}

bool Pack(World_Players &P, unsigned char* &dat)
{
    if(PARAM_Console_On_Online == 1)
        cout << "\tPack about person..." << endl;
    char* s = (char*)dat;
    *(int*)s = 1;
     s += 4;         /// type
    *(World_Players*)s = P;
    s += sizeof(World_Players);
    dat = (unsigned char*)s;
    return 1;
}

bool Pack(World_Objects &P, unsigned char* &dat)
{
    if(PARAM_Console_On_Online == 1)
        cout << "\tPack about Objects" << endl;
    char* s = (char*)dat;
    *(int*)s = 2;
    s += 4;         /// type
    *(World_Objects*)s = P;
    s += sizeof(World_Objects);
    dat = (unsigned char*)s;
    return 1;
}

bool Pack(World_Cars &P, unsigned char* &dat)
{
    if(PARAM_Console_On_Online == 1)
        cout << "\tPack about Cars..." << endl;
    char* s = (char*)dat;
    *(int*)s = 3;
    s += 4;         /// type
    *(World_Cars*)s = P;
    s += sizeof(World_Cars);
    dat = (unsigned char*)s;
    return 1;
}

bool PackAll(unsigned char* &dat)
{
    if(PARAM_Console_On_Online == 1)
        cout << "START PACKING ALL..." << endl;
    for(int i = 0; i < NUM_PLAYERS; i++)
        Pack(W__Players[i], dat);
    for(int i = 0; i < NUM_OBJECTS; i++)
        Pack(W__Objs[i], dat);
    for(int i = 0; i < NUM_CARS; i++)
        Pack(W__Cars[i], dat);

    char* s = (char*)dat;
    *(int*)s = 373;
    s += 4;
    dat = (unsigned char*)s;

    return 1;
}

bool unPack(unsigned char* &dat)
{
    char* s = (char*)dat;
    if(PARAM_Console_On_Online == 1)
        cout << "Unpacking..." << endl;

    while(*(int*)s != 373){
        if(*(int*)s == 1){    /// W__Players
            s += 4;
            int t;
            World_Players P;
            P = *(World_Players*)s;
            s += sizeof(World_Players);

            if((t = IsLoaded_player(P.g_id, W__Players, NUM_PLAYERS)) != -1){
                if(PARAM_Console_On_Online == 1)
                    cout << "Player already here" << endl;
                if(t != 0)
                    W__Players[t] = P;
                else
                    if(PARAM_Console_On_Online == 1)
                        cout << "It about yourself" << endl;

            }
            else{
                if(PARAM_Console_On_Online == 1)
                    cout << "New player entered!" << endl;
                W__Players[NUM_PLAYERS] = P;
                NUM_PLAYERS++;
            }
        }
        else if(*(int*)s == 2){   /// W__Objects
            s += 4;
            int t;
            World_Objects P;
            P = *(World_Objects*)s;
            s += sizeof(World_Objects);

            if((t = IsLoaded_obj(P.g_id, W__Objs, NUM_OBJECTS)) != -1){
                if(PARAM_Console_On_Online == 1)
                    cout << "Object already here" << endl;
                W__Objs[t] = P;
            }
            else{
                if(PARAM_Console_On_Online == 1)
                    cout << "New object added!" << endl;
                W__Objs[NUM_OBJECTS] = P;
                NUM_OBJECTS++;
            }
        }
        else if(*(int*)s == 3){   /// W__Cars
            s += 4;
            int t;
            World_Cars P;
            P = *(World_Cars*)s;
            s += sizeof(World_Cars);

            if((t = IsLoaded_car(P.g_id, W__Cars, NUM_CARS)) != -1){
                if(PARAM_Console_On_Online == 1)
                    cout << "Car already here" << endl;
                if(t != PARAM_SEND_CAR)
                    W__Cars[t] = P;
            }
            else{
                if(PARAM_Console_On_Online == 1)
                    cout << "New car added!" << endl;
                W__Cars[NUM_CARS] = P;
                NUM_CARS++;
            }
        }
        else{
            if(PARAM_Console_On_Online == 1)
                cout << "ERROR PACKET: " << *(int*)s << endl;
            return 0;
        }
    }
    s += 4;

    dat = (unsigned char*)s;
    return 1;
}

bool readPacket(unsigned char* &dat)
{
    char* s = (char*)dat;
    cout << "READING TO YOU..." << endl;
    cout << "\tS = " << *(int*)s << endl;

    while(*(int*)s != 373){
        cout << " S = " << *(int*)s << endl;
        if(*(int*)s == 1){    /// W__Players
            s += 4;
            int t;
            World_Players P;
            P = *(World_Players*)s;
            s += sizeof(World_Players);
            cout << "g_id " << P.g_id << endl;
            cout << "model_id " << P.model_id << endl;
            cout << "health " << P.health << endl;
            cout << "gun_id " << P.gun_id << endl;
            cout << "vct pos: ";
            vct_print(P.pos);
            cout << "vct EX: ";
            vct_print(P.EX);
            cout << "vct EY: ";
            vct_print(P.EY);
            cout << "vct EZ: ";
            vct_print(P.EZ);
            cout << sizeof(AnimPlayer) << " " "Animation: " << P.Animation << endl;

            if((t = IsLoaded_player(P.g_id, W__Players, NUM_PLAYERS)) != -1){
                cout << "Player already here" << endl;
            }
            else{
                cout << "New player entered!" << endl;
            }
        }
        else if(*(int*)s == 2){   /// W__Objects
            s += 4;
            int t;
            World_Objects P;
            P = *(World_Objects*)s;
            s += sizeof(World_Objects);
            cout << "g_id " << P.g_id << endl;
            cout << "model_id " << P.model_id << endl;
            cout << "vct pos: ";
            vct_print(P.pos);
            cout << "vct EX: ";
            vct_print(P.EX);
            cout << "vct EY: ";
            vct_print(P.EY);
            cout << "vct EZ: ";
            vct_print(P.EZ);
            cout << sizeof(AnimPlayer) << " " "Animation: " << P.Animation << endl;

            if((t = IsLoaded_obj(P.g_id, W__Objs, NUM_OBJECTS)) != -1){
                cout << "Object already here" << endl;
            }
            else{
                cout << "New object added!" << endl;
            }
        }
        else if(*(int*)s == 3){   /// W__Cars
            s += 4;
            int t;
            World_Cars P;
            P = *(World_Cars*)s;
            s += sizeof(World_Cars);
            cout << "g_id " << P.g_id << endl;
            cout << "model_id " << P.model_id << endl;
            cout << "health " << P.health << endl;
            cout << "vct pos: ";
            vct_print(P.pos);
            cout << "vct EX: ";
            vct_print(P.EX);
            cout << "vct EY: ";
            vct_print(P.EY);
            cout << "vct EZ: ";
            vct_print(P.EZ);
            cout << "Wheel_Speed " << P.Wheel_Speed << endl;
            cout << "skorost " << P.skorost << endl;
            cout << "povorot " << P.povorot << endl;
            cout << sizeof(AnimPlayer) << " " "Animation: " << P.Animation << endl;

            if((t = IsLoaded_car(P.g_id, W__Cars, NUM_CARS)) != -1){
                cout << "Car already here" << endl;
            }
            else{
                cout << "New car added!" << endl;
            }
        }
        else{
            cout << "ERROR PACKET: " << *(int*)s << endl;
            return 0;
        }
    }
    s += 4;

    dat = (unsigned char*)s;
    return 1;
}
