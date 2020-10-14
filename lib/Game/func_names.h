int Draw_Edge_Optimized(XY a, XY b, XY c, unsigned char red, unsigned char green, unsigned char blue);
int Draw_Edge_Optimized_ZBUFFER(XY a, XY b, XY c, double l, unsigned char red, unsigned char green, unsigned char blue);
int Draw_Edge_Optimized_ZBUFFER_FAST(XY a, XY b, XY c, double l, unsigned char red, unsigned char green, unsigned char blue);
int Draw_Edge_Optimized_ZBUFFER_textured(XY a, XY b, XY c, XY ta, XY tb, XY tc, Texture& texture, double l);
int Draw_Edge_Optimized_ZBUFFER_textured(XY a, XY b, XY c, XYZ ta, XYZ tb, XYZ tc, Texture& texture, double l);
int Draw_Edge_Optimized_ZBUFFER_textured_short(XY a, XY b, XY c, XYZ ta, XYZ tb, XYZ tc, Texture& texture, double l);
int Draw_Edge_Optimized_ZBUFFER_textured_short_OLD(XY a, XY b, XY c, XYZ ta, XYZ tb, XYZ tc, Texture& texture, double l);
int Draw_Edge_Optimized_ZBUFFER_textured_short_FAST(XY a, XY b, XY c, XYZ ta, XYZ tb, XYZ tc, Texture& texture, double l);
int Draw_Edge_Optimized_ZBUFFER_textured_short_GLOBAL_LIGHT(XY a, XY b, XY c, XYZ ta, XYZ tb, XYZ tc, Texture& texture, double l, double light);
int Draw_Edge_Optimized_ZBUFFER_textured_short_GLOBAL_LIGHT_FAST(XY a, XY b, XY c, XYZ ta, XYZ tb, XYZ tc, Texture& texture, double l, double light);
int Draw_Edge_Optimized_ZBUFFER_textured_short_FAST_4byte(XY a, XY b, XY c, XYZ ta, XYZ tb, XYZ tc, int *texture, int texture_shirina, int texture_vysota, double l);
int Draw_Edge_Optimized_ZBUFFER_textured_short_FAST_4byte_Proz(XY a, XY b, XY c, XYZ ta, XYZ tb, XYZ tc, int *texture, int texture_shirina, int texture_vysota, double l);
int Menu_Options(int num, HWND hwnd);

DWORD WINAPI Draw_Textured_Edge(void* param);
