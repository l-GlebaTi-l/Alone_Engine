#include "global.h"
#include "structs.h"
#include "func_names.h"
#include "parametrs.h"
//#include "stndt_param.h"
#include "izi_math.h"
#include "stndt_param.h"
#include "matrix.h"
#include "bmp_reader.h"
#include "textes.h"
#include "options.h"
#include "vectors.h"
#include "optimization.h"
#include "light.h"
#include "objects.h"
/// Pack into .h
World_Objects *W__Objs = new World_Objects[MAX_OBJECTS];
World_Players *W__Players = new World_Players[MAX_PLAYERS];
World_Cars *W__Cars = new World_Cars[MAX_CARS];
/// end of this pack
#include "classes.h"
#include "loader.h"
#include "proection.h"
#include "paint.h"

#include "../Online/server_structs.h"
#include "../Online/Server.h"
#include "../Online/Client.h"

#include "drawer.h"
#include "window.h"
#include "menu.h"
