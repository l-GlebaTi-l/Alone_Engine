//struct info {
//    short id;
//    XYZ pos;
//    XYZ pEX;
//    XYZ pEY;
//};

bool Draw_Objects()
{
//    while(Object -> next != NULL){
//        Object = Object -> Next;
//        if(Object -> id > 0 && Object -> id < 10){
//            Object ->
//        }
//    }
    for(int i = 0; i < NUM_OBJECTS; i++){
        ID_Obj[W__Objs[i].model_id].Paint_Fast(Bob, W__Objs[i]);
    }
    for(int i = 1; i < NUM_PLAYERS; i++){
        ID_Gamer[W__Players[i].model_id].Paint_Fast(Bob, W__Players[i]);
    }
    for(int i = 0; i < NUM_CARS; i++){
        ID_Car[W__Cars[i].model_id].Paint_Fast(Bob, W__Cars[i]);
    }

    return 1;
}
