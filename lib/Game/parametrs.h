#define FV FALL_VECTOR

int f_exit = 0;
scr_resolution resolution;
short PARAM_Vyvod = 1;
bool PARAM_OBJ_ADRESSES = 0;
double AlphaOBZ = Pi / 2;
double PARAM_Sootnoshenie_storon = 1.;
double PARAM_Scale = 1.;
double PARAM_Paint_L = 5.;
double PARAM_Alpha = 0., PARAM_Beta = 0.;
XYZ PARAM_Os = {0., 0., 0.};
double PARAM_Teta = 0.05;
int PARAM_Object_Choose = -1;
bool PARAM_SLEEP = 0;
int PARAM_InGame_Work = 1;
double PARAM_Height = 0.;
bool PARAM_CAR_NABLUDENIE = 0;
double N_VISION = 500;
XY d_Arrors;

double Obz_Fast_x = ((Pi - AlphaOBZ) / 2);
double Obz_Fast_y = ((Pi - AlphaOBZ / 1.7786) / 2);
double AlphaOBZ_y = AlphaOBZ / 1.7786;




XYZ GLOBAL_LIGHT = {0., 0., -1.};
XYZ EARTH_NORMAL = {1., 0., 0.};
XYZ FALL_VECTOR = {0., 0., -1.};
XYZ vG = {0., 0., G};
double SPEED_SUN = 0.3;

int PARAM_IMAGE_TYPE = 0;
bool PARAM_DO_SCREENSHOT = 0;

bool PARAM_BUTTON_W = 0;
bool PARAM_BUTTON_A = 0;
bool PARAM_BUTTON_S = 0;
bool PARAM_BUTTON_D = 0;
bool PARAM_BUTTON_SHIFT = 0;
bool PARAM_BUTTON_CTRL = 0;
bool PARAM_BUTTON_SPACE = 0;
bool PARAM_BUTTON_N_PLUS = 0;
bool PARAM_BUTTON_N_MINUS = 0;
bool PARAM_BUTTON_LKM = 0;
int PARAM_BUTTON_TAB = -1;
int PARAM_CAMERA_TYPE = 0;

/// ONLINE

int PARAM_SEND_CAR = -1;

/**
        Tm_End = steady_clock::now();
        TM_Spend = duration_cast<microseconds>(Tm_End - Tm_Start);
        cout << (double)TM_Spend.count()/1000000;
        Tm_Start = Tm_End;
    auto Tm_Start = steady_clock::now();
    auto Tm_End = steady_clock::now();
    auto TM_Spend = duration_cast<microseconds>(Tm_End - Tm_Start);
        Tm_Start = steady_clock::now();
        Tm_End = steady_clock::now();
        TM_Spend = duration_cast<microseconds>(Tm_End - Tm_Start);
        cout << (double)TM_Spend.count()/1000000;
**/
