struct scr_resolution{
    int shirina;
    int vysota;
};
typedef struct XYZ {
    double x;
    double y;
    double z;
} XYZ, Point;
//typedef struct {
//    float x;
//    float y;
//    float z;
//} XYZf;
typedef struct XY {
    double x;
    double y;
} XY, Point2;
typedef struct iXY {
    int x;
    int y;
} iXY, iPoint2, ScreenPoint;
typedef struct Pol{
    int a;
    int b;
    int c;
} Pol, iXYZ;
struct Point_Param{
    int v = 0;
    int vt = 0;
    int vn = 0;
};
typedef struct Pol_OBJ{
    Point_Param *t = new Point_Param[0];
    int Point_num = 0;
} Pol_OBJ;
typedef struct RGBF{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char f;
} RGBF, Color;
typedef struct Texture{
    RGBF** texture;
    scr_resolution res;
} Texture, OBJ_Texture, RGBF_Texture;
struct params_paint{
    double p0;
    double p1;
    double p2;
    double p3;
    double p4;
    double p5;
    double p6;
    double p7;
    double p8;
    double p9;
    double p10;
    double p11;
    double p12;
    int* p13;
    int p14;
    int p15;
};


template <typename T>
T sum(T* m, int n)
{
    T r = 0;
    for(int i = 0; i < n; i++)
        r += m[i];
    return r;
}
//XYZ sum(XYZ* m, int n)
//{
//    XYZ r = {0, 0, 0};
//    for(int i = 0; i < n; i++){
//        r.x += m[i].x;
//        r.y += m[i].y;
//        r.z += m[i].z;
//    }
//    return r;
//}
