class OBJECT_OBJ {
protected:
    short my_id = -1;
    char *Name = new char[128];
    char *Texture_Name = new char[128];
    int param_name_find = 0;

    XYZ EX = {1., 0., 0.};
    XYZ EY = {0., 1., 0.};
    XYZ EZ = {0., 0., 1.};
    double alpha = 0.;
    double beta = 0.;
    double *MatPer;
    double *dMat;

    XYZ pos = {0., 0., 0.};
    XYZ *v = new XYZ[0];
    int num_v = 0;
    XYZ *vt = new XYZ[0];
    int num_vt = 0;
    XYZ *vn = new XYZ[0];
    int num_vn = 0;
    XYZ *vp = new XYZ[0];
    int num_vp = 0;
    Pol_OBJ *f = new Pol_OBJ[0];
    int num_f = 0;

    void Update_Matrix(){
//        delete(MatPer);
//        MatPer = new double [9];
        MatPer[0] = EX.x;
        MatPer[1] = EY.x;
        MatPer[2] = EZ.x;
        MatPer[3] = EX.y;
        MatPer[4] = EY.y;
        MatPer[5] = EZ.y;
        MatPer[6] = EX.z;
        MatPer[7] = EY.z;
        MatPer[8] = EZ.z;
//        if(MatrixObratnaya(MatPer) != 1)
//            MessageBoxA(NULL, "Object Matrix error.", "ENGINE ERROR", MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
    }
public:
    double scale = 1.;
    void Update(World_Players Telo){
        pos = Telo.pos;
        EX = Telo.EX;
        EY = Telo.EY;
        EZ = Telo.EZ;
        Update_Matrix();
    }
    void Update(World_Objects Telo){
        pos = Telo.pos;
        EX = Telo.EX;
        EY = Telo.EY;
        EZ = Telo.EZ;
        Update_Matrix();
    }
    void Update(World_Cars Telo){
        pos = Telo.pos;
        EX = Telo.EX;
        EY = Telo.EY;
        EZ = Telo.EZ;
        Update_Matrix();
    }
    void Object_load_OBJ(char* file_name){
        FILE *file = fopen(file_name, "rb");

        char file_comments[512];
        char mysor[512];
        char a;
        int A;

        while(fscanf(file, "%c", &a) != EOF){
            if(a == 'v'){
                fscanf(file, "%c", &a);
                if(a == 't'){
                    fscanf(file, "%c", &a);
                    vt = (XYZ*)realloc(vt,(num_vt+1)*sizeof(XYZ));
                    fscanf(file, "%lf %lf", &vt[num_vt].x, &vt[num_vt].y);
//                    vt[num_vt].x = 1 - vt[num_vt].x;
//                    vt[num_vt].y = 1 - vt[num_vt].y;
                    fscanf(file, "%c", &a);
                    if(a == ' '){
                        fscanf(file, "%lf", &vt[num_vt].z);
                        fscanf(file, "%c", &a);
                    }
                    else{
                        vt[num_vt].z = 0.;
                    }
                    num_vt++;
                }
                else if(a == 'n'){
                    fscanf(file, "%c", &a);
                    vn = (XYZ*)realloc(vn,(num_vn+1)*sizeof(XYZ));
                    fscanf(file, "%lf %lf %lf", &vn[num_vn].x, &vn[num_vn].y, &vn[num_vn].z);
                    num_vn++;
                    fscanf(file, "%c", &a);
                }
                else if(a == 'p'){
                    fscanf(file, "%c", &a);
                    vp = (XYZ*)realloc(vp,(num_vp+1)*sizeof(XYZ));
                    fscanf(file, "%lf %lf %lf", &vp[num_vp].x, &vp[num_vp].y, &vp[num_vp].z);
                    num_vp++;
                    fscanf(file, "%c", &a);
                }
                else{
                    v = (XYZ*)realloc(v,(num_v+1)*sizeof(XYZ));
                    fscanf(file, "%lf %lf %lf", &v[num_v].x, &v[num_v].y, &v[num_v].z);
                    num_v++;
                    fscanf(file, "%c", &a);
                }
            }
            else if(a == 'f'){
                fscanf(file, "%c", &a);
                f = (Pol_OBJ*)realloc(f,(num_f+1)*sizeof(Pol_OBJ));
                Pol_OBJ tF;
                f[num_f] = tF;
                while(!feof(file)){
                    f[num_f].t = (Point_Param*)realloc(f[num_f].t,(f[num_f].Point_num + 1)*sizeof(Point_Param));
                    Point_Param tT;
                    f[num_f].t[f[num_f].Point_num] = tT;

                    fscanf(file, "%d", &A);
                    f[num_f].t[f[num_f].Point_num].v = A - 1;
                    fscanf(file, "%c", &a);

                    if(a == '/'){
                        fscanf(file, "%d", &A);
                        f[num_f].t[f[num_f].Point_num].vt = A - 1;
                        fscanf(file, "%c", &a);
                        if(a == '/'){
                            fscanf(file, "%d", &A);
                            f[num_f].t[f[num_f].Point_num].vn = A - 1;
                            fscanf(file, "%c", &a);
                            if(a == '\n' || a == '\r'){
                                f[num_f].Point_num++;
                                break;
                            }
                        }
                        else if(a == '\n' || a == '\r'){
                            f[num_f].Point_num++;
                            break;
                        }
                    }
                    else if(a == '\n' || a == '\r'){
                        f[num_f].Point_num++;
                        break;
                    }
                    long was = ftell(file);
                    f[num_f].Point_num++;

                    fscanf(file, "%c", &a);
                    if(a != '\n' && a != '\r'){
                        fseek(file, was, 0);
                        continue;
                    }
                    else
                        break;
                }
                num_f++;
            }
            else if(a == 'o'){
                fscanf(file, "%c", &a);
                if(a != '\n' && a != '\r'){
                    if(param_name_find == 0){
                        int i = 0;
                        fscanf(file, "%c", &a);
                        while(a != '\n' && a != '\r'){
                            Name[i] = a;
                            i++;
                            fscanf(file, "%c", &a);
                        }
                        Name[i] = {'\0'};
                        param_name_find = 1;
                    }
                    else{
                        while(a != '\n' && a != '\r')
                            fscanf(file, "%c", &a);
                    }
                }
            }
            else if(a == '#'){
                fgets(file_comments, 510, file);
            }
            else if(a == 't'){
                fscanf(file, "%c", &a);
                if(a != '\n' && a != '\r')
                    fscanf(file, "%c", &a);
                else
                    continue;
                int i = 0;
                while(a != '\n' && a != '\r'){
                    Texture_Name[i] = a;
                    i++;
                    fscanf(file, "%c", &a);
                }
                Texture_Name[i] = {'\0'};
                if(PARAM_Console_On == 1)
                    cout << "Texture name = " << Texture_Name << endl;
                char tName[100] = {"gamedata/Objects/"};
                if(param_name_find == 1){
                    char slash[2] = {"/"};
                    strcat(tName,Name);
                    strcat(tName,slash);
                }
                strcat(tName,Texture_Name);
                OemToChar(tName,Texture_Name);
                if(PARAM_Console_On == 1)
                    cout << "Texture adress: " << Texture_Name << endl;
            }
            else if(a != '\n' && a != '\r'){
                fgets(mysor, 510, file);
            }
        }

        fclose(file);
        if(param_name_find == 0){
            int tNameL = 7;
            char tName[tNameL] = {"NoName"};
            for(int i = 0; i < tNameL; i++)
                Name[i] = tName[i];
        }
        if(PARAM_Console_On == 1)
            cout << "GEOMETRY SCAN END" << endl;
        MatPer = new double[9];
        dMat = new double[9];
        Update_Matrix();
    }
    virtual void Change_Orientation(int orientation){
        double temp;
        if(orientation == 132){
            for(int i = 0; i < num_v; i++){
                temp = v[i].y;
                v[i].y = v[i].z;
                v[i].z = temp;
            }
            for(int i = 0; i < num_vn; i++){
                temp = vn[i].y;
                vn[i].y = vn[i].z;
                vn[i].z = temp;
            }
            for(int i = 0; i < num_vp; i++){
                temp = vp[i].y;
                vp[i].y = vp[i].z;
                vp[i].z = temp;
            }
        }
        else if(orientation == 213){
            for(int i = 0; i < num_v; i++){
                temp = v[i].y;
                v[i].y = v[i].x;
                v[i].x = temp;
            }
            for(int i = 0; i < num_vn; i++){
                temp = vn[i].y;
                vn[i].y = vn[i].x;
                vn[i].x = temp;
            }
            for(int i = 0; i < num_vp; i++){
                temp = vp[i].y;
                vp[i].y = vp[i].x;
                vp[i].x = temp;
            }
        }
        else if(orientation == 231){
            for(int i = 0; i < num_v; i++){
                temp = v[i].x;
                v[i].x = v[i].y;
                v[i].y = v[i].z;
                v[i].z = temp;
            }
            for(int i = 0; i < num_vn; i++){
                temp = vn[i].x;
                vn[i].x = vn[i].y;
                vn[i].y = vn[i].z;
                vn[i].z = temp;
            }
            for(int i = 0; i < num_vp; i++){
                temp = vp[i].x;
                vp[i].x = vp[i].y;
                vp[i].y = vp[i].z;
                vp[i].z = temp;
            }
        }
        else if(orientation == 321){
            for(int i = 0; i < num_v; i++){
                temp = v[i].x;
                v[i].x = v[i].z;
                v[i].z = temp;
            }
            for(int i = 0; i < num_vn; i++){
                temp = vn[i].x;
                vn[i].x = vn[i].z;
                vn[i].z = temp;
            }
            for(int i = 0; i < num_vp; i++){
                temp = vp[i].x;
                vp[i].x = vp[i].z;
                vp[i].z = temp;
            }
        }
        else if(orientation == 312){
            for(int i = 0; i < num_v; i++){
                temp = v[i].x;
                v[i].x = v[i].z;
                v[i].z = v[i].y;
                v[i].y = temp;
            }
            for(int i = 0; i < num_vn; i++){
                temp = vn[i].x;
                vn[i].x = vn[i].z;
                vn[i].z = vn[i].y;
                vn[i].y = temp;
            }
            for(int i = 0; i < num_vp; i++){
                temp = vp[i].x;
                vp[i].x = vp[i].z;
                vp[i].z = vp[i].y;
                vp[i].y = temp;
            }
        }
    }
    virtual void Move(XYZ dMove){
        pos.x += dMove.x;
        pos.y += dMove.y;
        pos.z += dMove.z;
    }
    virtual void Povorot(double dAlpha, double dBeta){
        alpha += dAlpha;
        beta += dBeta;
        EX.z = 1*sin(beta);
        double temp_proeczia;
        temp_proeczia = 1*cos(beta);
        EX.y = temp_proeczia*sin(alpha);
        EX.x = temp_proeczia*cos(alpha);

        EZ.z = 1*sin(beta + Pi/2);   /// +90 градусов, или + 1,5707963267948966192313216916398‬, или + Pi/2

        temp_proeczia = 1*cos(beta + Pi/2);
        EZ.y = temp_proeczia*sin(alpha);
        EZ.x = temp_proeczia*cos(alpha);

        EY = vct_perp(EZ, EX);
        Update_Matrix();
    }
    virtual void Povorot_Po_Osi(XYZ n, double teta){
//        XYZ n;
//        n.x = EX.x*tn.x + EY.x*tn.y + EZ.x*tn.z;
//        n.y = EX.y*tn.x + EY.y*tn.y + EZ.y*tn.z;
//        n.z = EX.z*tn.x + EY.z*tn.y + EZ.z*tn.z;
        double l;
        l = vct_dlina(n);
        if(l > -0.001 && l < 0.001)
            return;
        n = n / l;
        teta *= l;
        double* M = new double[9];
        double c = cos(teta);
        double s = sin(teta);

        M[0] = c + (1 - c)*n.x*n.x;
        M[1] = (1 - c)*n.x*n.y - s*n.z;
        M[2] = (1 - c)*n.x*n.z + s*n.y;
        M[3] = (1 - c)*n.y*n.x + s*n.z;
        M[4] = c + (1 - c)*n.y*n.y;
        M[5] = (1 - c)*n.y*n.z - s*n.x;
        M[6] = (1 - c)*n.z*n.x - s*n.y;
        M[7] = (1 - c)*n.z*n.y + s*n.x;
        M[8] = c + (1 - c)*n.z*n.z;

        XYZ gdO;
        gdO.x = M[0]*EX.x + M[1]*EX.y + M[2]*EX.z;
        gdO.y = M[3]*EX.x + M[4]*EX.y + M[5]*EX.z;
        gdO.z = M[6]*EX.x + M[7]*EX.y + M[8]*EX.z;
        EX = gdO;
        gdO.x = M[0]*EY.x + M[1]*EY.y + M[2]*EY.z;
        gdO.y = M[3]*EY.x + M[4]*EY.y + M[5]*EY.z;
        gdO.z = M[6]*EY.x + M[7]*EY.y + M[8]*EY.z;
        EY = gdO;
        gdO.x = M[0]*EZ.x + M[1]*EZ.y + M[2]*EZ.z;
        gdO.y = M[3]*EZ.x + M[4]*EZ.y + M[5]*EZ.z;
        gdO.z = M[6]*EZ.x + M[7]*EZ.y + M[8]*EZ.z;
        EZ = gdO;

        delete(M);

        Update_Matrix();
    }
    virtual void Povorot_Po_Osi(XYZ n, double teta, XYZ &EX, XYZ &EY, XYZ &EZ){
//        XYZ n;
//        n.x = EX.x*tn.x + EY.x*tn.y + EZ.x*tn.z;
//        n.y = EX.y*tn.x + EY.y*tn.y + EZ.y*tn.z;
//        n.z = EX.z*tn.x + EY.z*tn.y + EZ.z*tn.z;
        double l;
        l = vct_dlina(n);
        if(l > -0.001 && l < 0.001)
            return;
        n = n / l;
        teta *= l;
        double* M = new double[9];
        double c = cos(teta);
        double s = sin(teta);

        M[0] = c + (1 - c)*n.x*n.x;
        M[1] = (1 - c)*n.x*n.y - s*n.z;
        M[2] = (1 - c)*n.x*n.z + s*n.y;
        M[3] = (1 - c)*n.y*n.x + s*n.z;
        M[4] = c + (1 - c)*n.y*n.y;
        M[5] = (1 - c)*n.y*n.z - s*n.x;
        M[6] = (1 - c)*n.z*n.x - s*n.y;
        M[7] = (1 - c)*n.z*n.y + s*n.x;
        M[8] = c + (1 - c)*n.z*n.z;

        XYZ gdO;
        gdO.x = M[0]*EX.x + M[1]*EX.y + M[2]*EX.z;
        gdO.y = M[3]*EX.x + M[4]*EX.y + M[5]*EX.z;
        gdO.z = M[6]*EX.x + M[7]*EX.y + M[8]*EX.z;
        EX = gdO;
        gdO.x = M[0]*EY.x + M[1]*EY.y + M[2]*EY.z;
        gdO.y = M[3]*EY.x + M[4]*EY.y + M[5]*EY.z;
        gdO.z = M[6]*EY.x + M[7]*EY.y + M[8]*EY.z;
        EY = gdO;
        gdO.x = M[0]*EZ.x + M[1]*EZ.y + M[2]*EZ.z;
        gdO.y = M[3]*EZ.x + M[4]*EZ.y + M[5]*EZ.z;
        gdO.z = M[6]*EZ.x + M[7]*EZ.y + M[8]*EZ.z;
        EZ = gdO;

        delete(M);

        Update_Matrix();
    }
    virtual void Povorot_Po_Osi_Polzovatel(XYZ tn, double teta){
        XYZ n;
        n.x = -(EX.x*tn.x + EY.x*tn.y + EZ.x*tn.z);
        n.y = -(EX.y*tn.x + EY.y*tn.y + EZ.y*tn.z);
        n.z = -(EX.z*tn.x + EY.z*tn.y + EZ.z*tn.z);
        double l;
        l = vct_dlina(n);
        n = n / l;
        teta *= l;
        double* M = new double[9];
        double c = cos(teta);
        double s = sin(teta);

        M[0] = c + (1 - c)*n.x*n.x;
        M[1] = (1 - c)*n.x*n.y - s*n.z;
        M[2] = (1 - c)*n.x*n.z + s*n.y;
        M[3] = (1 - c)*n.y*n.x + s*n.z;
        M[4] = c + (1 - c)*n.y*n.y;
        M[5] = (1 - c)*n.y*n.z - s*n.x;
        M[6] = (1 - c)*n.z*n.x - s*n.y;
        M[7] = (1 - c)*n.z*n.y + s*n.x;
        M[8] = c + (1 - c)*n.z*n.z;

        XYZ gdO;
        gdO.x = M[0]*EX.x + M[1]*EX.y + M[2]*EX.z;
        gdO.y = M[3]*EX.x + M[4]*EX.y + M[5]*EX.z;
        gdO.z = M[6]*EX.x + M[7]*EX.y + M[8]*EX.z;
        EX = gdO;
        gdO.x = M[0]*EY.x + M[1]*EY.y + M[2]*EY.z;
        gdO.y = M[3]*EY.x + M[4]*EY.y + M[5]*EY.z;
        gdO.z = M[6]*EY.x + M[7]*EY.y + M[8]*EY.z;
        EY = gdO;
        gdO.x = M[0]*EZ.x + M[1]*EZ.y + M[2]*EZ.z;
        gdO.y = M[3]*EZ.x + M[4]*EZ.y + M[5]*EZ.z;
        gdO.z = M[6]*EZ.x + M[7]*EZ.y + M[8]*EZ.z;
        EZ = gdO;

        delete(M);

        Update_Matrix();
    }
    XYZ GetPos(){
        return pos;
    }
};

class Player;

class Terrain {
private:
    int razm_x = 0;
    int razm_y = 0;
    double scale = 1.;
    double scale_height = 0.1;
    XYZ *v = new XYZ[0];
    double u = 1.4;

    XY *projected_points = new XY[0];
    double *l = new double[0];
    bool* is_on_scene = new bool[0];
public:
    Terrain(){}
    void Load_Terrain(ifstream &filename);
    void Paint(Player& Vizor);
    double Is_On_Terrain(XYZ pos);
    double Where_On_Terrain(XYZ pos);
    XYZ Normal_Of_Terrain(XYZ pos);
    double Return_u();
    ~Terrain(){
        delete(v);
        delete(projected_points);
        delete(l);
        delete(is_on_scene);
        if(PARAM_Console_On == 1)
            cout << "Terrain deleted!" << endl;
    }
};

class Player {
private:
    short my_id = -1;
    short model_id = 0;
    short health = 100;
    short gun_id = -1;
    double Height_Player = 1.8;
    XYZ Legs = {0., 0., 0.};
    double head_alpha = 0., head_beta = 0.; //  beta - угол поднятия головы, от OX до EkX, alpha - угол поворота головы
    double head_kachanie = 0.;  //  Это угол поворота по оси EkX, осуществляет крен головы (к примеру, при выглядывании из-за стены
    XYZ EX = {1., 0., 0.};
    XYZ EY = {0., 1., 0.};
    XYZ EZ = {0., 0., 1.};
    XYZ O = {Legs.x, Legs.y, Legs.z + Height_Player};
    double legs_alpha = 0., legs_beta = 0.;
    XYZ Legs_Ploskost_X = {1., 0., 0.};         /// данные два вектора определяют плоскость, на которой стоит персонаж.
    XYZ Legs_Ploskost_Y = {0., 1., 0.};         /// обновляется в соответствии с касанием ног к чему-либо. Если касаний нет - все
                                                /// параметры равны нулю - тогда объект не сможет двигаться благодаря вводу геймера
                                                /// Для случая особенного окружения (вода, лава и т.д.) параметры могут быть больше
                                                /// или меньше единицы, но всегда больше нуля (для состояний головокружения или
                                                /// пьянства - и отрицательными :) )
                                                /// P.S. - они сонаправленны с векторами EkX и EkY соответственно
                                                /// ВРЕМЕННЫЕ ПАРАМЕТРЫ, с добавлением анимации каждая нога будет иметь свою коллизию
    double param_max_speed_hodby = 4.;
    double param_max_speed_beg = 15.;
    double param_yskorenie_hodby = 4.;
    double param_yskorenie_beg = 3.;
    double param_yskorenie = 4.;
    double param_soprotivlenie = 3.;
    double param_jump_speed = 10.;

    AnimPlayer Animation = PLSTAY_;
    int CarNum = -1;

    double* MatPer;
    double* MatPerEd;

    XYZ vec_gamer_vvod = {0., 0., 0.};
    XYZ vec_soprotivleniya = {0., 0., 0.};

    bool param_is_on_territory = 0;
    bool param_falling = 0;
    double fall_speed = 0.;

    XYZ vec_out = {0., 0., 0.};

    steady_clock::time_point tstart_Car;// = steady_clock::now();      //  time start Car
    steady_clock::time_point tend_Car = steady_clock::now();      //  time end Car
//    auto tspend_Car = duration_cast<seconds>(tend_Car - tstart_Car);       //  time spend Car

    void Update_MatrixEd(){
        delete(MatPerEd);
        MatPerEd = new double [9];
        MatPerEd[0] = EX.x;
        MatPerEd[1] = EY.x;
        MatPerEd[2] = EZ.x;
        MatPerEd[3] = EX.y;
        MatPerEd[4] = EY.y;
        MatPerEd[5] = EZ.y;
        MatPerEd[6] = EX.z;
        MatPerEd[7] = EY.z;
        MatPerEd[8] = EZ.z;
        if(MatrixObratnaya(MatPerEd) != 1)
            MessageBoxA(NULL, "Person MatrixEd error.", "ENGINE ERROR", MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
    }
public:
    XYZ Eye_pos = O;
    XYZ Eye_pos_minus = vct_YnC(O, -1);
    XYZ pEX = EX;
    Player(){
        Height_Player = 1.8;
        Legs = {0., 0., 0.};
        O = {0., 0., 1.8};    /// z + Height
//        EO = {0.1, -0.683, -0.384};  /// z + Height, правая нижняя точка плоскости обзора
        EX = {1., 0., 0.};
        EY = {0., 1.366, 0.};
        EZ = {0., 0., 0.768};
    }
    Player(double dHeight, XYZ dLegs, XYZ dO, XYZ dEX, XYZ dEY, XYZ dEZ, double dhead_alpha, double dhead_beta){
        Height_Player = dHeight;
        Legs = dLegs;
        O = dO;
        EX = dEX;
        EY = dEY;
        EZ = dEZ;
        head_alpha = dhead_alpha;
        head_beta = dhead_beta;
    }
    void SitInCar(int num){
        tstart_Car = steady_clock::now();
        CarNum = num;
        PARAM_SEND_CAR = num;
        Animation = PLINCAR_;
    }
    void LeftCar(){
        tstart_Car = steady_clock::now();
        PARAM_SEND_CAR = -1;
        CarNum = -1;
        Animation = PLSTAY_;
    }
    const AnimPlayer GetAnim(){
        return Animation;
    }
    int GetCarNum(){
        return CarNum;
    }
    const bool IsInCar(){
        if(CarNum > -1)
            return 1;
        return 0;
    }
    bool is_DoSomething(){
        tend_Car = steady_clock::now();
        auto tspend_Car = duration_cast<seconds>(tend_Car - tstart_Car);
        cout << "Time spend: " << (int)tspend_Car.count() << endl;
        if((int)tspend_Car.count() >= 1)
            return 0;
        return 1;
    }
    void Update(double dtime, double dAlpha, double dBeta, Terrain& terrain, World_Players &Telo){  /// Update(time dms)
        my_id = Telo.g_id;
        Update(dtime, dAlpha, dBeta, terrain);
        Telo = {my_id, model_id, health, gun_id, Legs, EX, EY, EZ, Animation};
//        return Telo;
    }
    void Update(double dtime, double dAlpha, double dBeta, Terrain& terrain){  /// Update(time dms)
        if(IsInCar() == 1){
            if(PARAM_CAMERA_TYPE == 0)
                return Update_Sitting(dtime, terrain);
            else if(PARAM_CAMERA_TYPE == 1)
                return Update_Slezenie(dtime, terrain);
        }
        ///
        param_is_on_territory = terrain.Is_On_Terrain(Legs);
        double temp_h_was = terrain.Where_On_Terrain(Legs);
        {
            double h_under_terrain = terrain.Where_On_Terrain(Legs);
            if(h_under_terrain != 0){
                param_falling = 1;
                fall_speed = fall_speed + G*dtime*dtime;
            }
            else{
                param_falling = 0;
                fall_speed = 0.;
            }
        }

        Legs.x += vec_out.x;
        Legs.y += vec_out.y;
        Legs.z += vec_out.z - fall_speed;

        ///
//        cout << "Real = " << terrain.Where_On_Terrain(Legs) << endl;
//        cout << "Fake = " << terrain.Is_On_Terrain(Legs) << endl << endl;
        {/*
        double h_under_terrain = terrain.Is_On_Terrain(Legs);
        if(h_under_terrain == 0){
            fall_speed = 0.;
            param_falling = 0;
        }
        else if(h_under_terrain > -2 && h_under_terrain < 0){
            Legs.z -= h_under_terrain;
            fall_speed = 0;
            param_falling = 0;
        }
        else if(h_under_terrain > 0.){
            param_falling = 1;
            fall_speed = fall_speed + G*dtime*dtime;
            Legs.z -= fall_speed;
            h_under_terrain = terrain.Is_On_Terrain(Legs);
            if(h_under_terrain <= 0){
                Legs.z -= h_under_terrain;
                fall_speed = 0.;
                param_falling = 0;
            }
        }*/
        }
        vec_soprotivleniya = vct_YnC(vec_gamer_vvod, dtime*param_soprotivlenie);
        vec_gamer_vvod.x -= vec_soprotivleniya.x;
        vec_gamer_vvod.y -= vec_soprotivleniya.y;
        vec_gamer_vvod.z -= vec_soprotivleniya.z;
        if(vct_SP(vec_gamer_vvod, vec_soprotivleniya) < 0){
            vec_gamer_vvod = {0., 0., 0.};
        }
        param_yskorenie = param_yskorenie_hodby;
        double param_max_speed;
        if(PARAM_BUTTON_SHIFT == 1){
            param_yskorenie *= param_yskorenie_beg;
            param_max_speed = param_max_speed_beg;
        }
        else
            param_max_speed = param_max_speed_hodby;
        if(PARAM_BUTTON_W == 1){
            vec_gamer_vvod += Legs_Ploskost_X * dtime * param_yskorenie;
        }
        if(PARAM_BUTTON_A == 1){
            vec_gamer_vvod += Legs_Ploskost_Y * dtime * param_yskorenie;
        }
        if(PARAM_BUTTON_S == 1){
            vec_gamer_vvod -= Legs_Ploskost_X * dtime * param_yskorenie;
        }
        if(PARAM_BUTTON_D == 1){
            vec_gamer_vvod -= Legs_Ploskost_Y * dtime * param_yskorenie;
        }
        if(vct_dlina(vec_gamer_vvod) > param_max_speed)
            vec_gamer_vvod = vct_ration(vec_gamer_vvod);
        if(PARAM_CAR_NABLUDENIE != 1){
            Legs += vec_gamer_vvod * dtime;
            if(PARAM_BUTTON_SPACE == 1){
                Legs.z += param_jump_speed * dtime;
            }
        }

        double temp_h_will = terrain.Where_On_Terrain(Legs);
        if((temp_h_was != 0 && temp_h_was*temp_h_will <= 0) || (temp_h_will < 0 && temp_h_was == 0)){
            Legs.z -= temp_h_will;
            fall_speed = 0;
            param_falling = 0;
        }

        double Height = Height_Player;
        if(PARAM_BUTTON_CTRL == 1){
            Height /= 3;
            if(param_is_on_territory == 0)
                Legs.z -= param_jump_speed * dtime;
        }
        O.x = Legs.x;
        O.y = Legs.y;
        O.z = Legs.z + Height;
        //  Здесь - поворот головы
        head_alpha += dAlpha;
        head_beta += dBeta;
        legs_alpha += dAlpha;
        legs_beta += dBeta;
        EX.z = 1*sin(head_beta);
        double temp_proeczia;
        temp_proeczia = 1*cos(head_beta);
        EX.y = temp_proeczia*sin(head_alpha);
        EX.x = temp_proeczia*cos(head_alpha);

        EZ.z = 1*sin(head_beta + Pi/2);   /// +90 градусов, или + 1,5707963267948966192313216916398‬, или + Pi/2
        temp_proeczia = 1*cos(head_beta + Pi/2);
        EZ.y = temp_proeczia*sin(head_alpha);
        EZ.x = temp_proeczia*cos(head_alpha);

        EY = vct_perp(EZ, EX);
        ///
        //  Все о ногах здесь
        Legs_Ploskost_X.x = cos(legs_alpha);
        Legs_Ploskost_X.y = sin(legs_alpha);
        Legs_Ploskost_X.z = 0.;             // находится из проверки, стоит ли персонаж на чём-то
        Legs_Ploskost_Y.x = cos(legs_alpha + Pi/2);
        Legs_Ploskost_Y.y = sin(legs_alpha + Pi/2);
        Legs_Ploskost_Y.z = 0.;             // находится из проверки, стоит ли персонаж на чём-то
        ///
        /// осуществить здесь перемещение персонажа по вектору его передвижения и поворот, связать с прошедшим временем
        Update_MatrixEd();

        Eye_pos = O;
        Eye_pos_minus = O;
        Eye_pos_minus.x *= -1;
        Eye_pos_minus.y *= -1;
        Eye_pos_minus.z *= -1;
        pEX = EX;
    }
    void Update_Slezenie(double dtime, double* MatPerIn, double Obj_Speed, double Obj_Povorot, Terrain& terrain){
        //  Здесь - поворот головы
        EX.x = MatPerIn[0];
        EY.x = MatPerIn[1];
        EZ.x = MatPerIn[2];
        EX.y = MatPerIn[3];
        EY.y = MatPerIn[4];
        EZ.y = MatPerIn[5];
        EX.z = MatPerIn[6];
        EY.z = MatPerIn[7];
        EZ.z = MatPerIn[8];
        ///
        O.x = Legs.x - EX.x*5 - EX.x*Obj_Speed/60;
        O.x += EZ.x*2;
        O.y = Legs.y - EX.y*5 - EX.y*Obj_Speed/60;
        O.y += EZ.y*2;
        O.z = Legs.z - EX.z*5 - EX.z*Obj_Speed/60;
        O.z += EZ.z*2;
        if(Obj_Speed >= 0)
            O += EY*Obj_Povorot * (Obj_Speed / 10) / (1 + Obj_Speed/10);
        else{
            O += EY*Obj_Povorot * (Obj_Speed / 10) / (1.5 + Obj_Speed/10);
            O += EX*10;
            EX = -EX;
            EY = -EY;
        }
        double temp_h_was = terrain.Where_On_Terrain(O);
        if(temp_h_was < 0.5)
            O.z -= temp_h_was - 0.5;
        //  Все о ногах здесь         // находится из проверки, стоит ли персонаж на чём-то
        ///
        /// осуществить здесь перемещение персонажа по вектору его передвижения и поворот, связать с прошедшим временем
        Update_MatrixEd();

        Eye_pos = O;
        Eye_pos_minus = O;
        Eye_pos_minus.x *= -1;
        Eye_pos_minus.y *= -1;
        Eye_pos_minus.z *= -1;
        pEX = EX;
    }
    void Update_Sitting(double dtime, double* MatPerIn, Terrain& terrain){
        //  Здесь - поворот головы
        EX.x = MatPerIn[0];
        EY.x = MatPerIn[1];
        EZ.x = MatPerIn[2];
        EX.y = MatPerIn[3];
        EY.y = MatPerIn[4];
        EZ.y = MatPerIn[5];
        EX.z = MatPerIn[6];
        EY.z = MatPerIn[7];
        EZ.z = MatPerIn[8];
        ///
        O.x = Legs.x;
        O.x += EZ.x*0.85 + EY.x*0.3;
        O.y = Legs.y;
        O.y += EZ.y*0.85 + EY.y*0.3;
        O.z = Legs.z;
        O.z += EZ.z*0.85 + EY.z*0.3;
//        double temp_h_was = terrain.Where_On_Terrain(O);
//        if(temp_h_was < 0.5)
//            O.z -= temp_h_was - 0.5;
        //  Все о ногах здесь         // находится из проверки, стоит ли персонаж на чём-то
        ///
        /// осуществить здесь перемещение персонажа по вектору его передвижения и поворот, связать с прошедшим временем
        Update_MatrixEd();

        Eye_pos = O;
        Eye_pos_minus = O;
        Eye_pos_minus.x *= -1;
        Eye_pos_minus.y *= -1;
        Eye_pos_minus.z *= -1;
        pEX = EX;
    }
    void Update_Slezenie(double dtime, Terrain& terrain){
     ///   W__Cars[Bob.GetCarNum()].EX
     ///   XYZ tEX, XYZ tEY, XYZ tEZ, double Obj_Speed, double Obj_Povorot,
        Teleport(W__Cars[CarNum].pos);
        XYZ tEX = W__Cars[CarNum].EX
        , tEY = W__Cars[CarNum].EY
        , tEZ = W__Cars[CarNum].EZ
        ;
        double Obj_Speed = W__Cars[CarNum].skorost
        , Obj_Povorot = W__Cars[CarNum].povorot
        ;
        //  Здесь - поворот головы
        EX.x = tEX.x;
        EY.x = tEY.x;
        EZ.x = tEZ.x;
        EX.y = tEX.y;
        EY.y = tEY.y;
        EZ.y = tEZ.y;
        EX.z = tEX.z;
        EY.z = tEY.z;
        EZ.z = tEZ.z;
        ///
        O.x = Legs.x - EX.x*5 - EX.x*Obj_Speed/60;
        O.x += EZ.x*2;
        O.y = Legs.y - EX.y*5 - EX.y*Obj_Speed/60;
        O.y += EZ.y*2;
        O.z = Legs.z - EX.z*5 - EX.z*Obj_Speed/60;
        O.z += EZ.z*2;
        if(Obj_Speed >= 0)
            O += EY*Obj_Povorot * (Obj_Speed / 10) / (1 + Obj_Speed/10);
        else{
            O += EY*Obj_Povorot * (Obj_Speed / 10) / (1.5 + Obj_Speed/10);
            O += EX*10;
            EX = -EX;
            EY = -EY;
        }
        double temp_h_was = terrain.Where_On_Terrain(O);
        if(temp_h_was < 0.5)
            O.z -= temp_h_was - 0.5;
        //  Все о ногах здесь         // находится из проверки, стоит ли персонаж на чём-то
        ///
        /// осуществить здесь перемещение персонажа по вектору его передвижения и поворот, связать с прошедшим временем
        Update_MatrixEd();

        Eye_pos = O;
        Eye_pos_minus = O;
        Eye_pos_minus.x *= -1;
        Eye_pos_minus.y *= -1;
        Eye_pos_minus.z *= -1;
        pEX = EX;
    }
    void Update_Sitting(double dtime, Terrain& terrain){
        Teleport(W__Cars[CarNum].pos);
        XYZ tEX = W__Cars[CarNum].EX
        , tEY = W__Cars[CarNum].EY
        , tEZ = W__Cars[CarNum].EZ
        ;
        //  Здесь - поворот головы
        EX.x = tEX.x;
        EY.x = tEY.x;
        EZ.x = tEZ.x;
        EX.y = tEX.y;
        EY.y = tEY.y;
        EZ.y = tEZ.y;
        EX.z = tEX.z;
        EY.z = tEY.z;
        EZ.z = tEZ.z;
        ///
        O.x = Legs.x;
        O.x += EZ.x*0.85 + EY.x*0.3;
        O.y = Legs.y;
        O.y += EZ.y*0.85 + EY.y*0.3;
        O.z = Legs.z;
        O.z += EZ.z*0.85 + EY.z*0.3;
//        double temp_h_was = terrain.Where_On_Terrain(O);
//        if(temp_h_was < 0.5)
//            O.z -= temp_h_was - 0.5;
        //  Все о ногах здесь         // находится из проверки, стоит ли персонаж на чём-то
        ///
        /// осуществить здесь перемещение персонажа по вектору его передвижения и поворот, связать с прошедшим временем
        Update_MatrixEd();

        Eye_pos = O;
        Eye_pos_minus = O;
        Eye_pos_minus.x *= -1;
        Eye_pos_minus.y *= -1;
        Eye_pos_minus.z *= -1;
        pEX = EX;
    }
    XYZ Go_To_Object__NOW(XYZ T){   /// Здесь бы осуществить ещё поворот на обратные углы поворота объекта.....
        T.x -= O.x;
        T.y -= O.y;
        T.z -= O.z;
        return T;
    }
    void add_sily(XYZ sila){
        vec_out.x += sila.x;
        vec_out.y += sila.y;
        vec_out.z += sila.z;
    }
    void Teleport(XYZ coord){
        Legs = coord;
    }
    XY Where_I_See_Point_If_I_Sphere_Hacker_Edition(XYZ T, XYZ dPOS){
        XYZ gOT;    /// координаты OT в базисе глаза
        XYZ OT;
        OT.x = T.x + dPOS.x;  /// dPOS.x - O.x вычислять до этой функции один раз на объект и этот вектор и передавать
        OT.y = T.y + dPOS.y;
        OT.z = T.z + dPOS.z;

//        OT = vct_ration(OT);
        gOT.x = MatPerEd[0]*OT.x + MatPerEd[1]*OT.y + MatPerEd[2]*OT.z;
        gOT.y = MatPerEd[3]*OT.x + MatPerEd[4]*OT.y + MatPerEd[5]*OT.z;
        gOT.z = MatPerEd[6]*OT.x + MatPerEd[7]*OT.y + MatPerEd[8]*OT.z;
        gOT = vct_ration(gOT);

        int param_see = 0;
        if(param_see == 1){
            cout << " x: " << gOT.x << " y: " << gOT.y << " z: " << gOT.z << endl;
        }
//        XYZ temp_EZ = {0., 0., 1.};
//        XYZ temp_EY = {0., 1., 0.};
//        double SP;
//        SP = vct_SP(gOT, temp_EZ);
//        SP = SqrtInv((1 - SP*SP));
//        SP = 1 / SP;

//        i need:
//            gOT.x*gOT.x + gOT.y*gOT.y = 1;
//        and
//            gOT.x*gOT.x + gOT.z*gOT.z = 1;

        XY P;
        P.x = gOT.y * SqrtInvE(gOT.x*gOT.x + gOT.y*gOT.y);
        if(P.x > 1)
            P.x = 1;
        else if(P.x < -1)
            P.x = -1;
        P.x = acos(P.x);
        if(gOT.x < 0){
            if(gOT.y < 0){
                P.x = 2*Pi - P.x;
            }
            else{
                P.x = -P.x;
            }
        }
        P.x -= ((Pi - AlphaOBZ) / 2);
        P.x /= AlphaOBZ;

//        SP = vct_SP(gOT, temp_EY);
//        SP = SqrtInv((1 - SP*SP));
//        SP = 1 / SP;
        P.y = gOT.z;
        P.y *= -1;
        if(P.y > 1)
            P.y = 1;
        else if(P.y < -1)
            P.y = -1;
        P.y = acos(P.y);
        if(gOT.x < 0){
            if(gOT.z < 0){
                P.y = -P.y;
            }
            else{
                P.y = 2*Pi - P.y;
            }
        }
        P.y -= ((Pi - AlphaOBZ / 1.7786) / 2);
        P.y /= AlphaOBZ / 1.7786;
        if(param_see == 1){
            cout << " x: " << gOT.x << " y: " << gOT.y << " z: " << gOT.z << endl;
            cout << " x: " << P.x << " y: " << P.y << endl << endl;
        }

        P.x *= resolution.shirina;
        P.y *= resolution.vysota;
        return P;
    }
    XY Where_I_See_Point_In_World(XYZ T){
        XYZ gOT;    /// координаты OT в базисе глаза
        XYZ OT;
        OT.x = T.x - O.x;  /// dPOS.x - O.x вычислять до этой функции один раз на объект и этот вектор и передавать
        OT.y = T.y - O.y;
        OT.z = T.z - O.z;

//        OT = vct_ration(OT);
        gOT.x = MatPerEd[0]*OT.x + MatPerEd[1]*OT.y + MatPerEd[2]*OT.z;
        gOT.y = MatPerEd[3]*OT.x + MatPerEd[4]*OT.y + MatPerEd[5]*OT.z;
        gOT.z = MatPerEd[6]*OT.x + MatPerEd[7]*OT.y + MatPerEd[8]*OT.z;
        gOT = vct_ration(gOT);

        int param_see = 0;
        if(param_see == 1){
            cout << " x: " << gOT.x << " y: " << gOT.y << " z: " << gOT.z << endl;
        }

        XY P;
        P.x = gOT.y * SqrtInvE(gOT.x*gOT.x + gOT.y*gOT.y);
        if(P.x > 1)
            P.x = 1;
        else if(P.x < -1)
            P.x = -1;
        P.x = acos(P.x);
        if(gOT.x < 0){
            if(gOT.y < 0){
                P.x = 2*Pi - P.x;
            }
            else{
                P.x = -P.x;
            }
        }
        P.x -= ((Pi - AlphaOBZ) / 2);
        P.x /= AlphaOBZ;

//        SP = vct_SP(gOT, temp_EY);
//        SP = SqrtInv((1 - SP*SP));
//        SP = 1 / SP;
        P.y = gOT.z;
        P.y *= -1;
        if(P.y > 1)
            P.y = 1;
        else if(P.y < -1)
            P.y = -1;
        P.y = acos(P.y);
        if(gOT.x < 0){
            if(gOT.z < 0){
                P.y = -P.y;
            }
            else{
                P.y = 2*Pi - P.y;
            }
        }
        P.y -= ((Pi - AlphaOBZ / 1.7786) / 2);
        P.y /= AlphaOBZ / 1.7786;
        if(param_see == 1){
            cout << " x: " << gOT.x << " y: " << gOT.y << " z: " << gOT.z << endl;
            cout << " x: " << P.x << " y: " << P.y << endl << endl;
        }

        P.x *= resolution.shirina;
        P.y *= resolution.vysota;
        return P;
    }
    XY Where_I_See_Point_If_I_Sphere_Fast(XYZ gOT){
        gOT = vct_ration(gOT);
        XY P;
        P.x = gOT.y * SqrtInvE(gOT.x*gOT.x + gOT.y*gOT.y);
        if(P.x > 1)
            P.x = 1;
        else if(P.x < -1)
            P.x = -1;
        P.x = acos(P.x);
        if(gOT.x < 0){
            if(gOT.y < 0){
                P.x = 2*Pi - P.x;
            }
            else{
                P.x = -P.x;
            }
        }
        P.x -= Obz_Fast_x;
        P.x /= AlphaOBZ;

        P.y = gOT.z;
        P.y *= -1;
        if(P.y > 1)
            P.y = 1;
        else if(P.y < -1)
            P.y = -1;
        P.y = acos(P.y);
        if(gOT.x < 0){
            if(gOT.z < 0){
                P.y = -P.y;
            }
            else{
                P.y = 2*Pi - P.y;
            }
        }
        P.y -= Obz_Fast_y;
        P.y /= AlphaOBZ_y;

        P.x *= resolution.shirina;
        P.y *= resolution.vysota;
        return P;
    }
    XY Where_I_See_Point_If_I_Sphere_Bad_Edition(XYZ T, XYZ dPOS){
        XYZ gOT;    /// координаты OT в базисе глаза
        XYZ OT;
        OT.x = T.x + dPOS.x;  /// dPOS.x - O.x вычислять до этой функции один раз на объект и этот вектор и передавать
        OT.y = T.y + dPOS.y;
        OT.z = T.z + dPOS.z;

        OT = vct_ration(OT);
        gOT.x = MatPerEd[0]*OT.x + MatPerEd[1]*OT.y + MatPerEd[2]*OT.z;
        gOT.y = MatPerEd[3]*OT.x + MatPerEd[4]*OT.y + MatPerEd[5]*OT.z;
        gOT.z = MatPerEd[6]*OT.x + MatPerEd[7]*OT.y + MatPerEd[8]*OT.z;

        XY P;

///        P.x = vct_SP(EX, gOT) = ( 1,0,0 ; x, y, z) = x + 0 + 0
//        if(gOT.x > -0.01 && gOT.x < 0.01)
//            gOT.x = 0.01;
        P.x = gOT.x * SqrtInvE(gOT.y*gOT.y + gOT.x*gOT.x);
        if(P.x > 1)
            P.x = 1;
        else if(P.x < -1)
            P.x = -1;
        P.x = acos(P.x);
        if(gOT.y >= 0){
            P.x = -P.x;
        }

        P.y = gOT.x * SqrtInvE(gOT.z*gOT.z + gOT.x*gOT.x);
        if(P.y > 1)
            P.y = 1;
        else if(P.y < -1)
            P.y = -1;
        P.y = acos(P.y);
        if(gOT.z < 0){
            P.y = -P.y;
        }

        P.x += 1.;
        P.x /= 2;
        P.x *= resolution.shirina;
        P.y += 1.;
        P.y /= 2;
        P.y *= resolution.vysota;
//        cout << P.x << " " << P.y << endl;

        return P;
    }
    XY Where_I_See_Point_Internet_Edition(XYZ T, XYZ dPOS){
        XY P;
        XYZ gOT;    /// координаты OT в базисе глаза
        T.x = T.x + dPOS.x;  /// dPOS.x - O.x вычислять до этой функции один раз на объект и этот вектор и передавать
        T.y = T.y + dPOS.y;
        T.z = T.z + dPOS.z;

        gOT.x = MatPerEd[0]*T.x + MatPerEd[1]*T.y + MatPerEd[2]*T.z;
        gOT.y = MatPerEd[3]*T.x + MatPerEd[4]*T.y + MatPerEd[5]*T.z;
        gOT.z = MatPerEd[6]*T.x + MatPerEd[7]*T.y + MatPerEd[8]*T.z;

        P.x = 0.5 * resolution.shirina - N_VISION * gOT.y / gOT.x;
        P.y = 0.5 * resolution.vysota + N_VISION * gOT.z / gOT.x;
//        cout << " x: " << P.x << " y: " << P.y << endl;
        return P;
    }
    XY Where_I_See_Point_Internet_Edition_Fast(XYZ gOT){
        XY P;
        P.x = 0.5 * resolution.shirina - N_VISION * gOT.y / gOT.x;
        P.y = 0.5 * resolution.vysota + N_VISION * gOT.z / gOT.x;
        return P;
    }
    XY Where_I_See_Point(XYZ T, XYZ OpOo){  //  OpOo - O-player to O-object
        XY P;
/*
        double mu;
        T.x = T.x + OpOo.x;
        T.y = T.y + OpOo.y;
        T.z = T.z + OpOo.z;
        mu = temp_param_d / -( EkX.x*T.x + EkX.y*T.y + EkX.z*T.z );
        T.x = temp_OO.x + T.x*mu;
        T.y = temp_OO.y + T.y*mu;
        T.z = temp_OO.z + T.z*mu;

        P.x = MatPer[0]*T.x + MatPer[1]*T.y + MatPer[2]*T.z;
        P.y = MatPer[3]*T.x + MatPer[4]*T.y + MatPer[5]*T.z;
        P.x = 1 - P.x;

        P.x *= resolution.shirina;
        P.y *= resolution.vysota;*/
        return P;
    }
    void Ymnoz_Mat(double *Matrix, double *outMat){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
//                cout << "= " << MatPer[i*3] << "!" << endl;
                outMat[i*3 + j] = MatPerEd[i*3]*Matrix[j] + MatPerEd[i*3 + 1]*Matrix[j + 3] + MatPerEd[i*3 + 2]*Matrix[j + 6];
//                cout << "Good " << i << " " << j << endl;
            }
        }
    }
    XYZ Matrix_na_Vct(XYZ tv){
        XYZ outv;
        outv.x = MatPerEd[0]*tv.x + MatPerEd[1]*tv.y + MatPerEd[2]*tv.z;
        outv.y = MatPerEd[3]*tv.x + MatPerEd[4]*tv.y + MatPerEd[5]*tv.z;
        outv.z = MatPerEd[6]*tv.x + MatPerEd[7]*tv.y + MatPerEd[8]*tv.z;
        return outv;
    }
    XYZ Get_Pos(){
        return Legs;
    }
    ~Player(){
        if(PARAM_Console_On == 1)
            cout << "Person deletet!" << endl;
    }
};

class OBJ_STRUCT : public OBJECT_OBJ {  /// Хит-бокс объекта
protected:
    XYZ *f_norm;
    XYZ *temp_v;
    double Health = 100;
    double Ray_Shoot(XYZ A, XYZ B, XYZ C, XYZ n, XYZ O, XYZ OV, XYZ& Popadanie)     /// Определение пересечения прямой и треугольника
    {
    //    Obj* D_Obj = (Obj*) pD_Obj;
        XYZ Peres;
        double D, mu;
        double alphaAB, alphaBC, alphaCA;
        double tL;
        XYZ PA, PB, PC;
        XYZ VO;
        int i = 0;
//        int PERESECH = -1;
        double L = -1;
        XYZ OS;

//        while(PERESECH!=1){
    ///                     Точка пересечения
    //        XYZ OV, VO;
    //        Person_dEYE.x = V.x - O.x;
            VO.x = -OV.x;
    //        OV.y = V.y - O.y;
            VO.y = -OV.y;
    //        OV.z = V.z - O.z;
            VO.z = -OV.z;

            PA = A;
            PB = n;
            D = PB.x*PA.x + PB.y*PA.y + PB.z*PA.z;
            D *= -1;
            mu = ( D + PB.x*O.x + PB.y*O.y + PB.z*O.z ) / ( PB.x*VO.x + PB.y*VO.y + PB.z*VO.z );
            Peres.x = O.x + OV.x*mu;
            Peres.y = O.y + OV.y*mu;
            Peres.z = O.z + OV.z*mu;
        //    vector_print(Peres);
        ///                     Проверка пересечения с треугольником

            PA.x = PA.x - Peres.x;
            PA.y = PA.y - Peres.y;
            PA.z = PA.z - Peres.z;

            PB.x = B.x - Peres.x;
            PB.y = B.y - Peres.y;
            PB.z = B.z - Peres.z;

            PC.x = C.x - Peres.x;
            PC.y = C.y - Peres.y;
            PC.z = C.z - Peres.z;

        //    PA = vector_ration(PA);
            tL = SqrtInv(PA.x*PA.x + PA.y*PA.y + PA.z*PA.z);
            PA.x = PA.x/tL;
            PA.y = PA.y/tL;
            PA.z = PA.z/tL;
        //    PB = vector_ration(PB);
            tL = SqrtInv(PB.x*PB.x + PB.y*PB.y + PB.z*PB.z);
            PB.x = PB.x/tL;
            PB.y = PB.y/tL;
            PB.z = PB.z/tL;
        //    PC = vector_ration(PC);
            tL = SqrtInv(PC.x*PC.x + PC.y*PC.y + PC.z*PC.z);
            PC.x = PC.x/tL;
            PC.y = PC.y/tL;
            PC.z = PC.z/tL;
            alphaAB = PA.x*PB.x + PA.y*PB.y + PA.z*PB.z;
            alphaBC = PB.x*PC.x + PB.y*PC.y + PB.z*PC.z;
            alphaCA = PC.x*PA.x + PC.y*PA.y + PC.z*PA.z;

    //        alphaAB = acos(alphaAB);
    //        alphaBC = acos(alphaBC);
    //        alphaCA = acos(alphaCA);
            tL = alphaAB + alphaBC + alphaCA;

            i++;

    //        if(tL <= (PiDva + 0.001) && tL >= (PiDva - 0.001)){
    //            PERESECH = 1;
    //            break;
    //        }
            if(tL <= -1){
                Popadanie = Peres;
                OS = vct_is_tocheck(O, Peres);
                L = vct_dlina(OS);
//                PERESECH = 1;
                return L;
//                break;
            }
            else
                return -1;
//            if(i == All_Obj[Obj_Num].num_meshs){
//                PERESECH = 0;
//                break;
//            }
//        }
//        return L; /// Так можно и так получится? Вопрос!                 !!!!!!!
    }
public:
    OBJ_STRUCT(){}
    void Update_Normals(XYZ* toch){
        for(int i = 0; i < num_f; i++){
            if(f[i].Point_num > 2)
                f_norm[i] = vct_perp(vct_is_tocheck(toch[f[i].t[0].v], toch[f[i].t[1].v]), vct_is_tocheck(toch[f[i].t[0].v], toch[f[i].t[2].v]));
            else
                f_norm[i] = {0, 0, 1};
        }
    }
    void Change_Orientation(int orientation){
        OBJECT_OBJ::Change_Orientation(orientation);
        Update_Normals(v);
    }
    void OBJ_STRUCT_(char* filename, double Health){
        Object_load_OBJ(filename);
        f_norm = new XYZ[num_f];
        for(int i = 0; i < num_f; i++){
            if(f[i].Point_num > 2)
                f_norm[i] = vct_perp(vct_is_tocheck(v[f[i].t[0].v], v[f[i].t[1].v]), vct_is_tocheck(v[f[i].t[0].v], v[f[i].t[2].v]));
            else
                f_norm[i] = {0, 0, 1};
        }
        temp_v = new XYZ[num_v];
        this -> Health = Health;
    }
    void Set_Health(double Health){
        this -> Health = Health;
    }
    double GetHealth(){
        return Health;
    }
    void Move(XYZ where){
        pos.x += where.x;
        pos.y += where.y;
        pos.z += where.z;
    }
    double Shoot(Player& Killer, XYZ& hitpoint){  /// С позиции posit выстрел направления vect
        double L;
        XYZ posit = Killer.Eye_pos - pos;
        XYZ EX = Killer.pEX;
        XYZ tpos;
        XYZ tEX;
        tpos.x = scale*(MatPer[0]*posit.x + MatPer[1]*posit.y + MatPer[2]*posit.z);
        tpos.y = scale*(MatPer[3]*posit.x + MatPer[4]*posit.y + MatPer[5]*posit.z);
        tpos.z = scale*(MatPer[6]*posit.x + MatPer[7]*posit.y + MatPer[8]*posit.z);

        tEX.x = scale*(MatPer[0]*EX.x + MatPer[1]*EX.y + MatPer[2]*EX.z);
        tEX.y = scale*(MatPer[3]*EX.x + MatPer[4]*EX.y + MatPer[5]*EX.z);
        tEX.z = scale*(MatPer[6]*EX.x + MatPer[7]*EX.y + MatPer[8]*EX.z);
        for(int i = 0; i < num_f; i++){
            for(int j = 0; j < f[i].Point_num - 2; j ++){
                if((L = Ray_Shoot(v[f[i].t[0].v], v[f[i].t[j+1].v], v[f[i].t[j+2].v], f_norm[i], tpos, tEX, hitpoint)) >= 0)
                    return L;
            }
        }
        return -1;
    }
    double* Get_MatPer(){
        return MatPer;
    }
    bool Hit(double damage){
//        if(PARAM_Console_On == 1)
            cout << Health;
        Health -= damage;
//        if(PARAM_Console_On == 1)
            cout << " " << Health << endl;
        if(Health <= 0)
            return 0;
        return 1;
    }
};

class Object {
public:
    int ObjType = 0;    /// 1 - only points, 2 - poligonal, 3 - full textured object, -1 - empty file, -2 - file not find
    XYZ pos = {0., 0., 0.};
    Point* points = new Point[0];   /// Always +1, cause of first-from initialization
    XYZ* normals = new XYZ[0];
    Pol* polygons = new Pol[0];
    int num_points = 0;
    int num_polygons = 0;
    int num_normals = 0;
    int num_texture_coord = 0;
    char* name = new char[1];
    bool *ScrPoints_is_proected;
    XY *ScrPoints;

    Object(ifstream file){
        if(file.is_open() != 1){
            ObjType = -2;
            return;
        }
        if(file.eof() == 1){
            ObjType = -1;
            return;
        }

        char a;

        file >> a;
        if(a == 'N'){
            int i = 0;
            file >> a;
            while(file.eof() != 1 && a != '#'){
                name = (char*)realloc(name,(i+2)*sizeof(char));
                name[i] = a;
                i++;
                file >> a;
            }
        }
        else{
            name = (char*)realloc(name,(20)*sizeof(char));
            char name1[20] = {'O','b','j','e','c','t',' ','w','i','t','h','o','u','t',' ','n','a','m','e'};
            for(int i = 0; i < 19; i++){
                name[i] = name1[i];
            }
            if(a == '#')
                file >> a;
        }

                            /// POINTS <------------------------------------------- NUMERATION FROM 1 (not 0) !!!!!!!!!!!!!!!!!!!!!!!
        while(file.eof() != 1 && a != '#'){
            if(a == 'v'){
                points = (Point*)realloc(points,(num_points+1)*sizeof(Point));
                file >> points[num_points].x;
                file >> points[num_points].y;
                file >> points[num_points].z;
                num_points++;
            }
            file >> a;
        }

        file >> a;          /// NORMALS <-------------------------------------------
        while(file.eof() != 1 && a != '#'){
            if(a == 'n'){
                normals = (XYZ*)realloc(normals,(num_normals+1)*sizeof(XYZ));
                file >> normals[num_normals].x;
                file >> normals[num_normals].y;
                file >> normals[num_normals].z;
                num_normals++;
            }
            file >> a;
        }

        file >> a;          /// POLYGONS <-------------------------------------------
        while(file.eof() != 1 && a != '#'){
            if(a == 'f'){
                polygons = (Pol*)realloc(polygons,(num_polygons+1)*sizeof(Pol));
                file >> polygons[num_polygons].a;
                file >> polygons[num_polygons].b;
                file >> polygons[num_polygons].c;
                num_polygons++;
            }
            file >> a;
        }

        if(num_points > 0){
            ObjType = 1;
            if(num_polygons > 0){
                ObjType = 2;
                if(num_texture_coord > 0)
                    ObjType = 3;
            }
        }
        ScrPoints_is_proected = new bool[num_points];
        ScrPoints = new XY[num_points];
    }
    Object_Treyg(){
        name = (char*)realloc(name,(11)*sizeof(char));
        char name1[11] = {'T','r','e','y','g','o','l','n','i','c'};
        for(int i = 0; i < 10; i++){
            name[i] = name1[i];
        }
        points = new Point[3];
        normals = new XYZ[1];
        polygons = new Pol[1];
        points[0] = {-0.5,-0.5,0.5};
        points[1] = {-0.5,0.5,0.5};
        points[2] = {0.5,0.5,0.5};
        num_points = 3;
        polygons[0] = {0,1,2};
        num_polygons = 1;
        normals[0] = {0,0,1};
        num_normals = 1;
        pos = {0., 0., 0.};
        ScrPoints_is_proected = new bool[num_points];
        ScrPoints = new XY[num_points];
    }
    Object(){
        name = (char*)realloc(name,(4)*sizeof(char));
        char name1[4] = {'B','o','x'};
        for(int i = 0; i < 3; i++){
            name[i] = name1[i];
        }
        points = new Point[8];
        normals = new XYZ[12];
        polygons = new Pol[12];
        points[0] = {-0.5,-0.5,-0.5};
        points[1] = {0.5,-0.5,-0.5};
        points[2] = {0.5,0.5,-0.5};
        points[3] = {-0.5,0.5,-0.5};
        points[4] = {-0.5,-0.5,0.5};
        points[5] = {0.5,-0.5,0.5};
        points[6] = {0.5,0.5,0.5};
        points[7] = {-0.5,0.5,0.5};
        num_points = 8;
        polygons[0] = {0,1,2};
        polygons[1] = {0,2,3};
        polygons[2] = {0,1,5};
        polygons[3] = {0,4,5};
        polygons[4] = {1,2,5};
        polygons[5] = {2,5,6};
        polygons[6] = {2,3,7};
        polygons[7] = {2,7,6};
        polygons[8] = {0,3,7};
        polygons[9] = {0,7,4};
        polygons[10] = {4,5,6};
        polygons[11] = {4,6,7};
        num_polygons = 12;
        normals[0] = {0,0,-1};
        normals[1] = {0,0,-1};
        normals[2] = {0,-1,0};
        normals[3] = {0,-1,0};
        normals[4] = {1,0,0};
        normals[5] = {1,0,0};
        normals[6] = {0,1,0};
        normals[7] = {0,1,0};
        normals[8] = {-1,0,0};
        normals[9] = {-1,0,0};
        normals[10] = {0,0,1};
        normals[11] = {0,0,1};
        num_normals = 12;
        pos = {0., 0., 0.};
        ScrPoints_is_proected = new bool[num_points];
        ScrPoints = new XY[num_points];
    }
    void Save(char* file_name){
        ofstream file(file_name);
        file << "o " << name << endl;
        file << endl;
        for(int i = 0; i < num_points; i++){
            file << "v " << points[i].x << " " << points[i].y << " " << points[i].z << endl;
        }
        file << endl;
        for(int i = 0; i < num_polygons; i++){
            file << "f " << polygons[i].a + 1 << " " << polygons[i].b + 1 << " " << polygons[i].c + 1 << endl;
        }
        file << endl;
        file.close();
    }
    void Move(XYZ dMove){
//        for(int i = 0; i < num_points; i++){
//            points[i].x += dMove.x;
//            points[i].y += dMove.y;
//            points[i].z += dMove.z;
//        }
        pos.x += dMove.x;
        pos.y += dMove.y;
        pos.z += dMove.z;
    }
    int Paint(Player& Bob){
        XYZ temp_OpOo;
        XYZ temp_OpOpolygon;

        temp_OpOo = Bob.Go_To_Object__NOW(pos);                          /// For every object on scene

        for(int i = 0; i < num_points; i++)
            ScrPoints_is_proected[i] = 0;

        for(int j = 0; j < num_polygons; j++){
            temp_OpOpolygon.x =  points[polygons[j].a].x + pos.x - Bob.Eye_pos.x;
            temp_OpOpolygon.y =  points[polygons[j].a].y + pos.y - Bob.Eye_pos.y;
            temp_OpOpolygon.z =  points[polygons[j].a].z + pos.z - Bob.Eye_pos.z;
            if(vct_SP(normals[j], temp_OpOpolygon) < 0){
                if(ScrPoints_is_proected[polygons[j].a] != 1){
                    ScrPoints[polygons[j].a] = Bob.Where_I_See_Point_Internet_Edition(points[polygons[j].a], temp_OpOo);
                    ScrPoints_is_proected[polygons[j].a] = 1;
                }
                if(ScrPoints_is_proected[polygons[j].b] != 1){
                    ScrPoints[polygons[j].b] = Bob.Where_I_See_Point_Internet_Edition(points[polygons[j].b], temp_OpOo);
                    ScrPoints_is_proected[polygons[j].b] = 1;
                }
                if(ScrPoints_is_proected[polygons[j].c] != 1){
                    ScrPoints[polygons[j].c] = Bob.Where_I_See_Point_Internet_Edition(points[polygons[j].c], temp_OpOo);
                    ScrPoints_is_proected[polygons[j].c] = 1;
                }
                Draw_Edge_Optimized(ScrPoints[polygons[j].a], ScrPoints[polygons[j].b], ScrPoints[polygons[j].c], 20*j, 200, 10);
            }
        }
        return 0;
    }
    ~Object(){
        if(PARAM_Console_On == 1)
            cout << "Object deleted!" << endl;
        delete(points);
        delete(normals);
        delete(polygons);
        delete(ScrPoints_is_proected);
        delete(ScrPoints);
        delete(name);
    }
};

class Object_OBJ : public OBJECT_OBJ{
protected:
    RGBF color = {10, 200, 30, 0};
    Texture texture;
    unsigned char *raw_bmp;

    XYZ *f_centers = new XYZ[0];
    XY *projected_points = new XY[0];
//    bool *point_is_on_scene = new bool[0];
    int texture_bits = 0;

    void Object_load_BMP(){
        raw_bmp = loadBMP(Texture_Name, texture.res.shirina, texture.res.vysota, texture_bits);
        if(raw_bmp != NULL){
            if(PARAM_Console_On == 1)
                cout << "TEXTURE LOADED " << texture.res.shirina << " " << texture.res.vysota << endl;
//            /**
            texture.texture = new RGBF*[texture.res.vysota];
            for(int i = 0; i < texture.res.vysota; i++)
                texture.texture[i] = new RGBF[texture.res.shirina];
            if(PARAM_Console_On == 1)
                cout << "MEMORY ADDED" << endl;
            for(int i = 0; i < texture.res.vysota; i++){
                for(int j = 0; j < texture.res.shirina; j++){
                    texture.texture[i][j].r = raw_bmp[i*texture.res.shirina*4 + j*4];
                    texture.texture[i][j].g = raw_bmp[i*texture.res.shirina*4 + j*4 + 1];
                    texture.texture[i][j].b = raw_bmp[i*texture.res.shirina*4 + j*4 + 2];
                    texture.texture[i][j].f = raw_bmp[i*texture.res.shirina*4 + j*4 + 3];   /// от 0 до 255
                }
            }
            if(PARAM_Console_On == 1)
                cout << "CONVERSATION SUCCSESFULL" << endl;//*/
            param_have_texture = 1;
        }
        else{
            if(PARAM_Console_On == 1)
                cout << "TEXTURE NOT LOADED" << endl;
            param_have_texture = 0;
        }
    }
public:
    bool param_have_texture = 0;
    Object_OBJ(){}
    void Object_OBJ_(char* file_name){
        Object_load_OBJ(file_name);
        Object_load_BMP();

        f_centers = new XYZ[num_f];
        for(int i = 0; i < num_f; i++){
            f_centers[i].x = 0;
            f_centers[i].y = 0;
            f_centers[i].z = 0;
            for(int j = 0; j < f[i].Point_num; j++){
                f_centers[i].x += v[f[i].t[j].v].x;
                f_centers[i].y += v[f[i].t[j].v].y;
                f_centers[i].z += v[f[i].t[j].v].z;
            }
            f_centers[i].x /= f[i].Point_num;
            f_centers[i].y /= f[i].Point_num;
            f_centers[i].z /= f[i].Point_num;
        }
        projected_points = new XY[num_v];
//        point_is_on_scene = new bool[num_v];
    }
    void Console_Print(){
        cout << Name << endl;
        cout << endl << "num_v = " << num_v << endl;
        for(int i = 0; i < num_v; i++)
            cout << "v " << i << " " << v[i].x << " " << v[i].y << " " << v[i].z << endl;
//            cout << "v " << i << endl;
        cout << endl << "num_vt = " << num_vt << endl;
        for(int i = 0; i < num_vt; i++)
            cout << "vt " << i << " " << vt[i].x << " " << vt[i].y << " " << vt[i].z << endl;
//            cout << "vt " << i << endl;
        cout << endl << "num_vn = " << num_vn << endl;
        for(int i = 0; i < num_vn; i++)
            cout << "vn " << i << " " << vn[i].x << " " << vn[i].y << " " << vn[i].z << endl;
//            cout << "vn " << i << endl;
        cout << endl << "num_vp = " << num_vp << endl;
        for(int i = 0; i < num_vp; i++)
            cout << "vp " << i << " " << vp[i].x << " " << vp[i].y << " " << vp[i].z << endl;
//            cout << "vp " << i << endl;
        cout << endl << "num_f = " << num_f << endl;
        for(int i = 0; i < num_f; i++){
    //        cout << "pn = " << f[i].Point_num << endl;
            cout << "f " << i << " ";
            for(int j = 0; j < f[i].Point_num; j++){
                cout << f[i].t[j].v + 1 << "/" << f[i].t[j].vt + 1 << "/" << f[i].t[j].vn + 1 << " ";
            }
            cout << endl;
        }
        cout << endl << "End!" << endl;
    }
    virtual void Change_Orientation(int orientation){
        double temp;
        if(orientation == 132){
            for(int i = 0; i < num_v; i++){
                temp = v[i].y;
                v[i].y = v[i].z;
                v[i].z = temp;
            }
            for(int i = 0; i < num_vn; i++){
                temp = vn[i].y;
                vn[i].y = vn[i].z;
                vn[i].z = temp;
            }
            for(int i = 0; i < num_vp; i++){
                temp = vp[i].y;
                vp[i].y = vp[i].z;
                vp[i].z = temp;
            }
            for(int i = 0; i < num_f; i++){
                temp = f_centers[i].y;
                f_centers[i].y = f_centers[i].z;
                f_centers[i].z = temp;
            }
        }
        else if(orientation == 213){
            for(int i = 0; i < num_v; i++){
                temp = v[i].y;
                v[i].y = v[i].x;
                v[i].x = temp;
            }
            for(int i = 0; i < num_vn; i++){
                temp = vn[i].y;
                vn[i].y = vn[i].x;
                vn[i].x = temp;
            }
            for(int i = 0; i < num_vp; i++){
                temp = vp[i].y;
                vp[i].y = vp[i].x;
                vp[i].x = temp;
            }
            for(int i = 0; i < num_f; i++){
                temp = f_centers[i].y;
                f_centers[i].y = f_centers[i].x;
                f_centers[i].x = temp;
            }
        }
        else if(orientation == 231){
            for(int i = 0; i < num_v; i++){
                temp = v[i].x;
                v[i].x = v[i].y;
                v[i].y = v[i].z;
                v[i].z = temp;
            }
            for(int i = 0; i < num_vn; i++){
                temp = vn[i].x;
                vn[i].x = vn[i].y;
                vn[i].y = vn[i].z;
                vn[i].z = temp;
            }
            for(int i = 0; i < num_vp; i++){
                temp = vp[i].x;
                vp[i].x = vp[i].y;
                vp[i].y = vp[i].z;
                vp[i].z = temp;
            }
            for(int i = 0; i < num_f; i++){
                temp = f_centers[i].x;
                f_centers[i].x = f_centers[i].y;
                f_centers[i].y = f_centers[i].z;
                f_centers[i].z = temp;
            }
        }
        else if(orientation == 321){
            for(int i = 0; i < num_v; i++){
                temp = v[i].x;
                v[i].x = v[i].z;
                v[i].z = temp;
            }
            for(int i = 0; i < num_vn; i++){
                temp = vn[i].x;
                vn[i].x = vn[i].z;
                vn[i].z = temp;
            }
            for(int i = 0; i < num_vp; i++){
                temp = vp[i].x;
                vp[i].x = vp[i].z;
                vp[i].z = temp;
            }
            for(int i = 0; i < num_f; i++){
                temp = f_centers[i].x;
                f_centers[i].x = f_centers[i].z;
                f_centers[i].z = temp;
            }
        }
        else if(orientation == 312){
            for(int i = 0; i < num_v; i++){
                temp = v[i].x;
                v[i].x = v[i].z;
                v[i].z = v[i].y;
                v[i].y = temp;
            }
            for(int i = 0; i < num_vn; i++){
                temp = vn[i].x;
                vn[i].x = vn[i].z;
                vn[i].z = vn[i].y;
                vn[i].y = temp;
            }
            for(int i = 0; i < num_vp; i++){
                temp = vp[i].x;
                vp[i].x = vp[i].z;
                vp[i].z = vp[i].y;
                vp[i].y = temp;
            }
            for(int i = 0; i < num_f; i++){
                temp = f_centers[i].x;
                f_centers[i].x = f_centers[i].z;
                f_centers[i].z = f_centers[i].y;
                f_centers[i].y = temp;
            }
        }
    }
    int Paint(Player& Vizor){
        XYZ dO = Vizor.Go_To_Object__NOW(pos);
        for(int i = 0; i < num_v; i++){
            XYZ paint;
            paint.x = v[i].x*scale;
            paint.y = v[i].y*scale;
            paint.z = v[i].z*scale;
            projected_points[i] = Vizor.Where_I_See_Point_If_I_Sphere_Hacker_Edition(paint, dO);
        }
        XYZ OT;
        double l;
        for(int i = 0; i < num_f; i++){
            for(int j = 0; j < f[i].Point_num - 2; j++){
                XYZ f_centers_scaled = f_centers[i];
                f_centers_scaled.x *= scale;
                f_centers_scaled.y *= scale;
                f_centers_scaled.z *= scale;
                OT.x = f_centers_scaled.x + pos.x;
                OT.y = f_centers_scaled.y + pos.y;
                OT.z = f_centers_scaled.z + pos.z;
                OT = vct_is_tocheck(Vizor.Eye_pos, OT);
//                l = OT.x*OT.x + OT.y*OT.y + OT.z*OT.z;
//                l = vct_dlina(OT);
                if(vct_SP(Vizor.pEX, OT) > 0)
                    l = vct_dlina(OT);
                else
                    l = -1;
                if(l > 0)
                    Draw_Edge_Optimized_ZBUFFER(projected_points[f[i].t[j].v], projected_points[f[i].t[j + 1].v], projected_points[f[i].t[f[i].Point_num - 1].v], l, i, i*2, i*3);
//                    Draw_Edge_Optimized_ZBUFFER(projected_points[f[i].t[j].v - 1], projected_points[f[i].t[j + 1].v - 1], projected_points[f[i].t[f[i].Point_num - 1].v - 1], l, 100 + (double)i/(double)num_f * 30, 100 + (double)i/(double)num_f * 30, 0 + (double)i/(double)num_f * 30);
            }
        }
//        cout << "Drawed" << endl;
        return 0;
    }
    int Paint__(Player& Vizor){
        XYZ dO = Vizor.Go_To_Object__NOW(pos);
        for(int i = 0; i < num_v; i++){
            XYZ paint;
            paint.x = scale*(MatPer[0]*v[i].x + MatPer[1]*v[i].y + MatPer[2]*v[i].z);
            paint.y = scale*(MatPer[3]*v[i].x + MatPer[4]*v[i].y + MatPer[5]*v[i].z);
            paint.z = scale*(MatPer[6]*v[i].x + MatPer[7]*v[i].y + MatPer[8]*v[i].z);
            projected_points[i] = Vizor.Where_I_See_Point_If_I_Sphere_Hacker_Edition(paint, dO);
        }
        XYZ OT;
        double l;
        for(int i = 0; i < num_f; i++){
            for(int j = 0; j < f[i].Point_num - 2; j++){
            OT.x = pos.x + scale*(MatPer[0]*f_centers[i].x + MatPer[1]*f_centers[i].y + MatPer[2]*f_centers[i].z);
            OT.y = pos.y + scale*(MatPer[3]*f_centers[i].x + MatPer[4]*f_centers[i].y + MatPer[5]*f_centers[i].z);
            OT.z = pos.z + scale*(MatPer[6]*f_centers[i].x + MatPer[7]*f_centers[i].y + MatPer[8]*f_centers[i].z);
                OT = vct_is_tocheck(Vizor.Eye_pos, OT);
                if(vct_SP(Vizor.pEX, OT) > 0)
                    l = vct_dlina(OT);
                else
                    l = -1;
                if(l > 0)
                    Draw_Edge_Optimized_ZBUFFER(projected_points[f[i].t[j].v], projected_points[f[i].t[j + 1].v], projected_points[f[i].t[f[i].Point_num - 1].v], l, i, i*2, i*3);
//                    Draw_Edge_Optimized_ZBUFFER(projected_points[f[i].t[j].v - 1], projected_points[f[i].t[j + 1].v - 1], projected_points[f[i].t[f[i].Point_num - 1].v - 1], l, 100 + (double)i/(double)num_f * 30, 100 + (double)i/(double)num_f * 30, 0 + (double)i/(double)num_f * 30);
            }
        }
        return 0;
    }
    template <typename T>
    int Paint_Fast(Player& Vizor, T Telo){
        Update(Telo);
        return Paint_Fast(Vizor);
    }
//    virtual int Paint_Fast(Player& Vizor, World_Objects Telo){
//        Update(Telo);
//        return Paint_Fast(Vizor);
//    }
//    virtual int Paint_Fast(Player& Vizor, World_Cars Telo){
//        Update(Telo);
//        return Paint_Fast(Vizor);
//    }
    virtual int Paint_Fast(Player& Vizor){
        XYZ dO = Vizor.Go_To_Object__NOW(pos);
        Vizor.Ymnoz_Mat(MatPer, dMat);
        dO = Vizor.Matrix_na_Vct(dO);
        for(int i = 0; i < num_v; i++){
            XYZ paint;
            paint.x = scale*(dMat[0]*v[i].x + dMat[1]*v[i].y + dMat[2]*v[i].z);
            paint.y = scale*(dMat[3]*v[i].x + dMat[4]*v[i].y + dMat[5]*v[i].z);
            paint.z = scale*(dMat[6]*v[i].x + dMat[7]*v[i].y + dMat[8]*v[i].z);

            paint.x += dO.x;
            paint.y += dO.y;
            paint.z += dO.z;
//            if(paint.x <= 0)
//                point_is_on_scene[i] = 0;
//            else{
//                point_is_on_scene[i] = 1;
                projected_points[i] = Vizor.Where_I_See_Point_If_I_Sphere_Fast(paint);
//            }
        }
        XYZ OT;
        double l;
//        HANDLE threads[4];
//        int num_th = 0;
        for(int i = 0; i < num_f; i++){
            for(int j = 0; j < f[i].Point_num - 2; j++){
//                if(point_is_on_scene[f[i].t[0].v] == 1 && point_is_on_scene[f[i].t[j + 1].v] == 1 && point_is_on_scene[f[i].t[j + 2].v] == 1){
                    OT.x = pos.x + scale*(MatPer[0]*f_centers[i].x + MatPer[1]*f_centers[i].y + MatPer[2]*f_centers[i].z);
                    OT.y = pos.y + scale*(MatPer[3]*f_centers[i].x + MatPer[4]*f_centers[i].y + MatPer[5]*f_centers[i].z);
                    OT.z = pos.z + scale*(MatPer[6]*f_centers[i].x + MatPer[7]*f_centers[i].y + MatPer[8]*f_centers[i].z);
                    OT = OT - Vizor.Eye_pos;
                    double SP;
                    if(vct_SP(Vizor.pEX, OT) > 0)
                        l = SP(OT,OT);
                    else
                        l = -1;
                    if(l > 0){
                        if(num_vn > 0){
                            SP = (vct_SP(vct_ration(vn[f[i].t[0].vn]), GLOBAL_LIGHT) + vct_SP(vct_ration(vn[f[i].t[j + 1].vn]), GLOBAL_LIGHT) + vct_SP(vct_ration(vn[f[i].t[j + 2].vn]), GLOBAL_LIGHT)) / 6;
                            SP += 0.5;
                        }
                        if(param_have_texture == 0){
                            if(num_vn > 0)
                                Draw_Edge_Optimized_ZBUFFER_FAST(projected_points[f[i].t[0].v], projected_points[f[i].t[j + 1].v], projected_points[f[i].t[j + 2].v], l, color.r*SP, color.g*SP, color.b*SP);
                            else
            //                    Draw_Edge_Optimized_ZBUFFER(projected_points[f[i].t[j].v - 1], projected_points[f[i].t[j + 1].v - 1], projected_points[f[i].t[f[i].Point_num - 1].v - 1], l, i, i*2, i*3);
                                Draw_Edge_Optimized_ZBUFFER_FAST(projected_points[f[i].t[0].v], projected_points[f[i].t[j + 1].v], projected_points[f[i].t[j + 2].v], l, i, i*2, i*3);
            //                    Draw_Edge_Optimized_ZBUFFER(projected_points[f[i].t[j].v - 1], projected_points[f[i].t[j + 1].v - 1], projected_points[f[i].t[f[i].Point_num - 1].v - 1], l, 100 + (double)i/(double)num_f * 30, 100 + (double)i/(double)num_f * 30, 0 + (double)i/(double)num_f * 30);
                        }
                        else{
    //                        if(num_vn > 0)
    //                            Draw_Edge_Optimized_ZBUFFER_textured_short_GLOBAL_LIGHT(
    //                                                             projected_points[f[i].t[0].v],
    //                                                             projected_points[f[i].t[j + 1].v],
    //                                                             projected_points[f[i].t[j + 2].v],
    //                                                             vt[f[i].t[0].vt],
    //                                                             vt[f[i].t[j + 1].vt],
    //                                                             vt[f[i].t[j + 2].vt],
    //                                                             texture,
    //                                                             l,
    //                                                             SP
    //                                                             );
    //                        else
//                            if(texture_bits == 24 || texture_bits == 32)
//                                Draw_Edge_Optimized_ZBUFFER_textured(
//                                                                 projected_points[f[i].t[0].v],
//                                                                 projected_points[f[i].t[j + 1].v],
//                                                                 projected_points[f[i].t[j + 2].v],
//                                                                 vt[f[i].t[0].vt],
//                                                                 vt[f[i].t[j + 1].vt],
//                                                                 vt[f[i].t[j + 2].vt],
//                                                                 texture,
//                                                                 l
//                                                                 );
                            if(texture_bits == 24)
                                Draw_Textured_Edge_int(
                                                                 projected_points[f[i].t[0].v],
                                                                 projected_points[f[i].t[j + 1].v],
                                                                 projected_points[f[i].t[j + 2].v],
                                                                 vt[f[i].t[0].vt],
                                                                 vt[f[i].t[j + 1].vt],
                                                                 vt[f[i].t[j + 2].vt],
                                                                 (int*)raw_bmp,
                                                                 texture.res.shirina,
                                                                 texture.res.vysota,
                                                                 l
                                                                 );
                            else if(texture_bits == 32)
                                Draw_Textured_Edge_Proz_int(
                                                                 projected_points[f[i].t[0].v],
                                                                 projected_points[f[i].t[j + 1].v],
                                                                 projected_points[f[i].t[j + 2].v],
                                                                 vt[f[i].t[0].vt],
                                                                 vt[f[i].t[j + 1].vt],
                                                                 vt[f[i].t[j + 2].vt],
                                                                 (int*)raw_bmp,
                                                                 texture.res.shirina,
                                                                 texture.res.vysota,
                                                                 l
                                                                 );
                        }
                    }
//                }
            }
        }
//        WaitForMultipleObjects(num_th, threads, TRUE, INFINITE);
        return 0;
    }
    void Paint_Name(Player& Vizor){
        XY start_text;

        XYZ dO = Vizor.Go_To_Object__NOW(pos);
        dO = Vizor.Matrix_na_Vct(dO);

        XYZ paint;

        paint.x = scale*dO.x;
        paint.y = scale*dO.y;
        paint.z = scale*dO.z;
        start_text = Vizor.Where_I_See_Point_If_I_Sphere_Fast(paint);
        double rast;
        rast = vct_dlina(pos - Vizor.Get_Pos());
        eng.say(start_text.x, start_text.y, 16, rast, Name);
    }
    void Show_Texture_On_Ekran(){
        for(int i = 0; i < texture.res.vysota; i++){
            if(i >= resolution.vysota)
                break;
            for(int j = 0; j < texture.res.shirina; j++){
                if(j >= resolution.shirina)
                    break;
                pixels[i*resolution.shirina*4 + j*4] = texture.texture[i][j].b;
                pixels[i*resolution.shirina*4 + j*4 + 1] = texture.texture[i][j].g;
                pixels[i*resolution.shirina*4 + j*4 + 2] = texture.texture[i][j].r;
            }
        }
    }
    ~Object_OBJ(){
        delete(v);
        delete(vt);
        delete(vn);
        delete(vp);
        for(int i = 0; i < num_f; i++)
            delete(f[i].t);
        delete(f);
        delete(f_centers);
        delete(projected_points);
//        delete(point_is_on_scene);
        delete(MatPer);
        delete(dMat);
        delete(Texture_Name);
//        for(int i = 0; i < texture.res.vysota; i++)
//            delete(texture.texture[i]);
        delete(texture.texture);
        delete(Name);
        if(PARAM_Console_On == 1)
            cout << "Object_OBJ deleted!" << endl;
    }
};

class Alive_OBJ : public Object_OBJ {
private:
    bool Alive = 1;
public:
    OBJ_STRUCT HitBox;
    void Alive_OBJ_(char* Obj_filename, char* HitBox_filename, double Health){
        Object_OBJ_(Obj_filename);
        HitBox.OBJ_STRUCT_(HitBox_filename, Health);
    }
    void Move(XYZ dMove){
        pos.x += dMove.x;
        pos.y += dMove.y;
        pos.z += dMove.z;
        HitBox.Move(dMove);
    }
    void Change_Orientation(int orientation){
        Object_OBJ::Change_Orientation(orientation);
        HitBox.Change_Orientation(orientation);
    }
    template <typename T>
    int Paint_Fast(Player& Vizor, T Telo){
        return Object_OBJ::Paint_Fast(Vizor, Telo);
    }
    void Povorot(double dAlpha, double dBeta){
        Object_OBJ::Povorot(dAlpha, dBeta);
        MatrixObratnaya(MatPer, HitBox.Get_MatPer());
    }
    void Povorot_Po_Osi(XYZ n, double teta, XYZ &EX, XYZ &EY, XYZ &EZ){
        Object_OBJ::Povorot_Po_Osi(n, teta, EX, EY, EZ);
        MatrixObratnaya(MatPer, HitBox.Get_MatPer());
    }
    void Povorot_Po_Osi(XYZ n, double teta){
        Object_OBJ::Povorot_Po_Osi(n, teta);
        MatrixObratnaya(MatPer, HitBox.Get_MatPer());
    }
    void Povorot_Po_Osi_Polzovatel(XYZ tn, double teta){
        Object_OBJ::Povorot_Po_Osi_Polzovatel(tn, teta);
        MatrixObratnaya(MatPer, HitBox.Get_MatPer());
    }
    double Shoot(Player& Killer, double damage, XYZ& hitpoint){
        double L = HitBox.Shoot(Killer, hitpoint);
        if(L >= 0){
            Hit(damage);
            XYZ tpoint;
            tpoint.x = scale*(MatPer[0]*hitpoint.x + MatPer[1]*hitpoint.y + MatPer[2]*hitpoint.z);
            tpoint.y = scale*(MatPer[3]*hitpoint.x + MatPer[4]*hitpoint.y + MatPer[5]*hitpoint.z);
            tpoint.z = scale*(MatPer[6]*hitpoint.x + MatPer[7]*hitpoint.y + MatPer[8]*hitpoint.z);
            hitpoint = tpoint + pos;
        }
        return L;
    }
    bool Hit(double damage){
        Alive = HitBox.Hit(damage);
        return Alive;
    }
    bool Is_Alive(){
        return Alive;
    }
};

struct Objects{
    Object_OBJ obj;
    Objects *next;
};
/**
 y          Bz1
/|\    Az3
 |
 |
 |                oBz0
 0---->x     oAz2
**/
class AABB {
private:
public:
    XYZ A, B;
    AABB(XYZ tA, XYZ tB){
        A = tA;
        B = tB;
    }
    void Update(XYZ tA, XYZ tB){
        A = tA;
        B = tB;
    }
    int Collision(AABB o){
        if(A.x > o.B.x || o.A.x > B.x)
            return 0;
        if(A.y > o.B.y || o.A.y > B.y)
            return 0;
        if(A.z > o.B.z || o.A.z > B.z)
            return 0;
        return 1;
    }
};

class OBJ_Transport : public Alive_OBJ {
private:
    double povorot = 0.;
    double skorost = 0.;
    double max_speed = 240. / 3.6;  /// km/h
    double zadniy = 30. / 3.6;
    double tormoz = 300. / 3.6;
    double yskor = 50 / 3.6;
    double air_tormoz = 20 / 3.6;
    double amortization = 3.;
    AnimCar Animation = CARPARKED_;
public:
    void OBJ_Transport_(char* Obj_filename, char* HitBox_filename, double Health){
        povorot = 0.;
        skorost = 0.;
        max_speed = 240. / 3.6;  /// km/h
        zadniy = 30. / 3.6;
        tormoz = 300. / 3.6;
        yskor = 50 / 3.6;
        air_tormoz = 20 / 3.6;
        amortization = 3.;
        Animation = CARPARKED_;
        Alive_OBJ_(Obj_filename, HitBox_filename, Health);
    }
    double* GetMatPer(){
        return MatPer;
    }
    double GetSpeed(){
        return skorost;
    }
    double GetPovorot(){
        return povorot;
    }
    void Update(double dtime, Terrain &terrain, World_Cars &Info){
        my_id = Info.g_id;
        cout << "yskor " << yskor << endl;
        Update_With_Physics(dtime, terrain, Info);
//        Info = {my_id, Info.model_id, (short)HitBox.GetHealth(), pos, EX, EY, EZ, 0, skorost, povorot, Animation};
//struct World_Cars {
//    short g_id;
//    short model_id = -1;
//    short health = 100;
//    XYZ pos = {0., 0., 0.};
//    XYZ EX = {1., 0., 0.};
//    XYZ EY = {0., 1., 0.};
//    XYZ EZ = {0., 0., 1.};
//    double Wheel_Speed = 0;
//    double skorost = 0;
//    double povorot = 0;
//    AnimCar Animation = CARPARKED_;
//};

    }
    void Update_old(double dtime, Terrain &terrain){
        XYZ n;
        n = terrain.Normal_Of_Terrain(pos);
        n = vct_ration(n);
        if((n.x != 0 || n.y != 0 || n.z != 0) && (n.x - EZ.x > 0.01 || n.y - EZ.y > 0.01 || n.z - EZ.z > 0.01 || n.x - EZ.x < -0.01 || n.y - EZ.y < -0.01 || n.z - EZ.z < -0.01)){
            double teta;
            XYZ OSs = vct_perp(EZ, n);
            OSs = vct_ration(OSs);
            teta = vct_ygol(n, EZ);
            if(teta > 0.001){
                teta = acos(teta);
                Povorot_Po_Osi(OSs, teta);
            }
        }

        double a;
        double speed_lim = max_speed;

        if(PARAM_BUTTON_SHIFT == 1 && (PARAM_BUTTON_TAB == 1 || PARAM_CAR_NABLUDENIE == 1)){
            a = yskor * 3;
            speed_lim = max_speed;
        }
        else{
            a = yskor;
            speed_lim = max_speed / 4;
        }
        if(PARAM_BUTTON_W == 1 && (PARAM_BUTTON_TAB == 1 || PARAM_CAR_NABLUDENIE == 1)){
            skorost = skorost + a*dtime*dtime;
            if(skorost > speed_lim)
                skorost = speed_lim;
        }
        else{
            if(skorost > 0 && skorost - air_tormoz*air_tormoz*dtime*dtime > 0)
                skorost -= air_tormoz*air_tormoz*dtime*dtime;
            else if(skorost > 0)
                skorost = 0;
        }
        if(PARAM_BUTTON_S == 1 && (PARAM_BUTTON_TAB == 1 || PARAM_CAR_NABLUDENIE == 1)){
            if(skorost > 0){
                if(PARAM_BUTTON_SPACE == 0)
                    skorost -= tormoz*dtime*dtime;
            }
            else
                skorost -= zadniy*dtime*dtime;
            if(skorost < -zadniy)
                skorost = -zadniy;
        }
        else{
            if(skorost < 0 && skorost + air_tormoz*air_tormoz*dtime*dtime < 0)
                skorost += air_tormoz*air_tormoz*dtime*dtime;
            else if(skorost < 0)
                skorost = 0;
        }
        if(PARAM_BUTTON_SPACE == 1 && (PARAM_BUTTON_TAB == 1 || PARAM_CAR_NABLUDENIE == 1)){
            if(skorost > 0){
                if(skorost - tormoz*dtime*dtime > 0)
                    skorost -= tormoz*dtime*dtime;
                else
                    skorost = 0;
            }
            else if(skorost < 0){
                if(skorost + tormoz*dtime*dtime < 0)
                    skorost += tormoz*dtime*dtime;
                else
                    skorost = 0;
            }
        }
        if(PARAM_BUTTON_A == 1 && (PARAM_BUTTON_TAB == 1 || PARAM_CAR_NABLUDENIE == 1)){
            povorot += dtime;
            if(povorot > Pi/4)
                povorot = Pi/4;
        }
        else{
            static bool was = 0;
            if(povorot > 0){
                was = 1;
                povorot -= dtime;
            }
            else
                was = 0;
            if(was == 1){
                if(povorot <= 0){
                    povorot = 0;
                    was = 0;
                }
                else
                    was = 1;
            }
        }
        if(PARAM_BUTTON_D == 1 && (PARAM_BUTTON_TAB == 1 || PARAM_CAR_NABLUDENIE == 1)){
            povorot -= dtime;
            if(povorot < -Pi/4)
                povorot = -Pi/4;
        }
        else{
            static bool was = 0;
            if(povorot < 0){
                was = 1;
                povorot += dtime;
            }
            else
                was = 0;
            if(was == 1){
                if(povorot >= 0){
                    povorot = 0;
                    was = 0;
                }
                else
                    was = 1;
            }
        }
//        pos.x += EX.x*skorost*dtime;
//        pos.y += EX.y*skorost*dtime;
//        pos.z += EX.z*skorost*dtime;
        Move(EX*skorost*dtime);
        if(skorost > 0.)
            Povorot_Po_Osi(EZ, dtime*povorot*sqrt(skorost)/2);
        else if(skorost < 0.)
            Povorot_Po_Osi(EZ, -dtime*povorot*sqrt(-skorost)/2);
        double vys = terrain.Where_On_Terrain(pos);
        XYZ minvys = {0., 0., -vys};
        Move(minvys);
//        pos.z -= vys;
    }
    void Update_amortization(double dtime, Terrain &terrain){
        amortization = 5.;
        XYZ n;
        n = terrain.Normal_Of_Terrain(pos);
        n = vct_ration(n);
        if((n.x != 0 || n.y != 0 || n.z != 0) && (n.x - EZ.x > 0.01 || n.y - EZ.y > 0.01 || n.z - EZ.z > 0.01 || n.x - EZ.x < -0.01 || n.y - EZ.y < -0.01 || n.z - EZ.z < -0.01)){
            double teta;
            XYZ OSs = vct_perp(EZ, n);
            OSs = vct_ration(OSs);
            teta = vct_ygol(n, EZ);
            if(teta > 0.001){
                teta = acos(teta);
                Povorot_Po_Osi(OSs, teta*dtime*amortization);
            }
        }

        double a;
        double speed_lim = max_speed;

        if(PARAM_BUTTON_SHIFT == 1 && (PARAM_BUTTON_TAB == 1 || PARAM_CAR_NABLUDENIE == 1)){
            a = yskor * 3;
            speed_lim = max_speed;
        }
        else{
            a = yskor;
            speed_lim = max_speed / 4;
        }
        if(PARAM_BUTTON_W == 1 && (PARAM_BUTTON_TAB == 1 || PARAM_CAR_NABLUDENIE == 1)){
            skorost = skorost + a*dtime*dtime;
            if(skorost > speed_lim)
                skorost = speed_lim;
        }
        else{
            if(skorost > 0 && skorost - air_tormoz*air_tormoz*dtime*dtime > 0)
                skorost -= air_tormoz*air_tormoz*dtime*dtime;
            else if(skorost > 0)
                skorost = 0;
        }
        if(PARAM_BUTTON_S == 1 && (PARAM_BUTTON_TAB == 1 || PARAM_CAR_NABLUDENIE == 1)){
            if(skorost > 0){
                if(PARAM_BUTTON_SPACE == 0)
                    skorost -= tormoz*dtime*dtime;
            }
            else
                skorost -= zadniy*dtime*dtime;
            if(skorost < -zadniy)
                skorost = -zadniy;
        }
        else{
            if(skorost < 0 && skorost + air_tormoz*air_tormoz*dtime*dtime < 0)
                skorost += air_tormoz*air_tormoz*dtime*dtime;
            else if(skorost < 0)
                skorost = 0;
        }
        if(PARAM_BUTTON_SPACE == 1 && (PARAM_BUTTON_TAB == 1 || PARAM_CAR_NABLUDENIE == 1)){
            if(skorost > 0){
                if(skorost - tormoz*dtime*dtime > 0)
                    skorost -= tormoz*dtime*dtime;
                else
                    skorost = 0;
            }
            else if(skorost < 0){
                if(skorost + tormoz*dtime*dtime < 0)
                    skorost += tormoz*dtime*dtime;
                else
                    skorost = 0;
            }
        }
        if(PARAM_BUTTON_A == 1 && (PARAM_BUTTON_TAB == 1 || PARAM_CAR_NABLUDENIE == 1)){
            povorot += dtime;
            if(povorot > Pi/4)
                povorot = Pi/4;
        }
        else{
            static bool was = 0;
            if(povorot > 0){
                was = 1;
                povorot -= dtime;
            }
            else
                was = 0;
            if(was == 1){
                if(povorot <= 0){
                    povorot = 0;
                    was = 0;
                }
                else
                    was = 1;
            }
        }
        if(PARAM_BUTTON_D == 1 && (PARAM_BUTTON_TAB == 1 || PARAM_CAR_NABLUDENIE == 1)){
            povorot -= dtime;
            if(povorot < -Pi/4)
                povorot = -Pi/4;
        }
        else{
            static bool was = 0;
            if(povorot < 0){
                was = 1;
                povorot += dtime;
            }
            else
                was = 0;
            if(was == 1){
                if(povorot >= 0){
                    povorot = 0;
                    was = 0;
                }
                else
                    was = 1;
            }
        }
        Move(EX*skorost*dtime);
        if(skorost > 0.)
            Povorot_Po_Osi(EZ, dtime*povorot*sqrt(skorost)/2);
        else if(skorost < 0.)
            Povorot_Po_Osi(EZ, -dtime*povorot*sqrt(-skorost)/2);
        double vys = terrain.Where_On_Terrain(pos);
        XYZ minvys = {0., 0., -vys};
        Move(minvys);
    }
    void Update_With_Physics(double dtime, Terrain &terrain, World_Cars &Info){
        static double fall_speed = 0.;
        XYZ n;
        n = terrain.Normal_Of_Terrain(Info.pos);
        n = vct_ration(n);
        if((n.x != 0 || n.y != 0 || n.z != 0) && (n.x - Info.EZ.x > 0.01 || n.y - Info.EZ.y > 0.01 || n.z - Info.EZ.z > 0.01 || n.x - Info.EZ.x < -0.01 || n.y - Info.EZ.y < -0.01 || n.z - Info.EZ.z < -0.01)){
            static double teta = 0;
            static XYZ OSs;
            if(fall_speed == 0){
                OSs = vct_perp(Info.EZ, n);
                OSs = vct_ration(OSs);
                teta = vct_ygol(n, Info.EZ);
                teta = acos(teta);
            }
            if(teta > 0.001){
                Povorot_Po_Osi(OSs, teta*dtime*amortization, Info.EX, Info.EY, Info.EZ);
            }
        }

        double a;
        double speed_lim = max_speed;

        if(fall_speed == 0){
            if(PARAM_BUTTON_SHIFT == 1){
                a = yskor * 3;
                speed_lim = max_speed;
            }
            else{
                a = yskor;
                speed_lim = max_speed / 4;
            }
            if(PARAM_BUTTON_W == 1){
                Info.skorost = Info.skorost + a*dtime*dtime;
                if(Info.skorost > speed_lim)
                    Info.skorost = speed_lim;
            }
            else{
                if(Info.skorost > 0 && Info.skorost - air_tormoz*air_tormoz*dtime*dtime > 0)
                    Info.skorost -= air_tormoz*air_tormoz*dtime*dtime;
                else if(Info.skorost > 0)
                    Info.skorost = 0;
            }
            if(PARAM_BUTTON_S == 1){
                if(Info.skorost > 0){
                    if(PARAM_BUTTON_SPACE == 0)
                        Info.skorost -= tormoz*dtime*dtime;
                }
                else
                    Info.skorost -= zadniy*dtime*dtime;
                if(Info.skorost < -zadniy)
                    Info.skorost = -zadniy;
            }
            else{
                if(Info.skorost < 0 && Info.skorost + air_tormoz*air_tormoz*dtime*dtime < 0)
                    Info.skorost += air_tormoz*air_tormoz*dtime*dtime;
                else if(Info.skorost < 0)
                    Info.skorost = 0;
            }
            if(PARAM_BUTTON_SPACE == 1){
                if(Info.skorost > 0){
                    if(Info.skorost - tormoz*dtime*dtime > 0)
                        Info.skorost -= tormoz*dtime*dtime;
                    else
                        Info.skorost = 0;
                }
                else if(Info.skorost < 0){
                    if(Info.skorost + tormoz*dtime*dtime < 0)
                        Info.skorost += tormoz*dtime*dtime;
                    else
                        Info.skorost = 0;
                }
            }
            if(PARAM_BUTTON_A == 1){
                Info.povorot += dtime;
                if(Info.povorot > Pi/4)
                    Info.povorot = Pi/4;
            }
            else{
                static bool was = 0;
                if(Info.povorot > 0){
                    was = 1;
                    Info.povorot -= dtime;
                }
                else
                    was = 0;
                if(was == 1){
                    if(Info.povorot <= 0){
                        Info.povorot = 0;
                        was = 0;
                    }
                    else
                        was = 1;
                }
            }
            if(PARAM_BUTTON_D == 1){
                Info.povorot -= dtime;
                if(Info.povorot < -Pi/4)
                    Info.povorot = -Pi/4;
            }
            else{
                static bool was = 0;
                if(Info.povorot < 0){
                    was = 1;
                    Info.povorot += dtime;
                }
                else
                    was = 0;
                if(was == 1){
                    if(Info.povorot >= 0){
                        Info.povorot = 0;
                        was = 0;
                    }
                    else
                        was = 1;
                }
            }
        }
        static XYZ dviz;
        if(fall_speed == 0){
            dviz.x = Info.EX.x*Info.skorost*dtime;
            dviz.y = Info.EX.y*Info.skorost*dtime;
            dviz.z = Info.EX.z*Info.skorost*dtime;
        }
        else
            dviz.z -= G*dtime*dtime;
        Info.pos += dviz;
//        Move(dviz);
        if(fall_speed == 0){
            if(Info.skorost > 0.)
                Povorot_Po_Osi(Info.EZ, dtime*Info.povorot*sqrt(Info.skorost)/2, Info.EX, Info.EY, Info.EZ);
            else if(Info.skorost < 0.)
                Povorot_Po_Osi(Info.EZ, -dtime*Info.povorot*sqrt(-Info.skorost)/2, Info.EX, Info.EY, Info.EZ);
        }
        double vys = terrain.Where_On_Terrain(Info.pos);
        if(vys > 0.01){
            fall_speed -= G*dtime*dtime;
        }
        else{
//            Info.pos.z -= vys;
            XYZ minvys = {0., 0., -vys};
//            Move(minvys);
            Info.pos += minvys;
            fall_speed = 0;
        }
    }
    void Update_With_Physics(double dtime, Terrain &terrain){
        static double fall_speed = 0.;
        XYZ n;
        n = terrain.Normal_Of_Terrain(pos);
        n = vct_ration(n);
        if((n.x != 0 || n.y != 0 || n.z != 0) && (n.x - EZ.x > 0.01 || n.y - EZ.y > 0.01 || n.z - EZ.z > 0.01 || n.x - EZ.x < -0.01 || n.y - EZ.y < -0.01 || n.z - EZ.z < -0.01)){
            static double teta = 0;
            static XYZ OSs;
            if(fall_speed == 0){
                OSs = vct_perp(EZ, n);
                OSs = vct_ration(OSs);
                teta = vct_ygol(n, EZ);
                teta = acos(teta);
            }
            if(teta > 0.001){
                Povorot_Po_Osi(OSs, teta*dtime*amortization);
            }
        }

        double a;
        double speed_lim = max_speed;

        if(fall_speed == 0){
            if(PARAM_BUTTON_SHIFT == 1 && (PARAM_BUTTON_TAB == 1 || PARAM_CAR_NABLUDENIE == 1)){
                a = yskor * 3;
                speed_lim = max_speed;
            }
            else{
                a = yskor;
                speed_lim = max_speed / 4;
            }
            if(PARAM_BUTTON_W == 1 && (PARAM_BUTTON_TAB == 1 || PARAM_CAR_NABLUDENIE == 1)){
                skorost = skorost + a*dtime*dtime;
                if(skorost > speed_lim)
                    skorost = speed_lim;
            }
            else{
                if(skorost > 0 && skorost - air_tormoz*air_tormoz*dtime*dtime > 0)
                    skorost -= air_tormoz*air_tormoz*dtime*dtime;
                else if(skorost > 0)
                    skorost = 0;
            }
            if(PARAM_BUTTON_S == 1 && (PARAM_BUTTON_TAB == 1 || PARAM_CAR_NABLUDENIE == 1)){
                if(skorost > 0){
                    if(PARAM_BUTTON_SPACE == 0)
                        skorost -= tormoz*dtime*dtime;
                }
                else
                    skorost -= zadniy*dtime*dtime;
                if(skorost < -zadniy)
                    skorost = -zadniy;
            }
            else{
                if(skorost < 0 && skorost + air_tormoz*air_tormoz*dtime*dtime < 0)
                    skorost += air_tormoz*air_tormoz*dtime*dtime;
                else if(skorost < 0)
                    skorost = 0;
            }
            if(PARAM_BUTTON_SPACE == 1 && (PARAM_BUTTON_TAB == 1 || PARAM_CAR_NABLUDENIE == 1)){
                if(skorost > 0){
                    if(skorost - tormoz*dtime*dtime > 0)
                        skorost -= tormoz*dtime*dtime;
                    else
                        skorost = 0;
                }
                else if(skorost < 0){
                    if(skorost + tormoz*dtime*dtime < 0)
                        skorost += tormoz*dtime*dtime;
                    else
                        skorost = 0;
                }
            }
            if(PARAM_BUTTON_A == 1 && (PARAM_BUTTON_TAB == 1 || PARAM_CAR_NABLUDENIE == 1)){
                povorot += dtime;
                if(povorot > Pi/4)
                    povorot = Pi/4;
            }
            else{
                static bool was = 0;
                if(povorot > 0){
                    was = 1;
                    povorot -= dtime;
                }
                else
                    was = 0;
                if(was == 1){
                    if(povorot <= 0){
                        povorot = 0;
                        was = 0;
                    }
                    else
                        was = 1;
                }
            }
            if(PARAM_BUTTON_D == 1 && (PARAM_BUTTON_TAB == 1 || PARAM_CAR_NABLUDENIE == 1)){
                povorot -= dtime;
                if(povorot < -Pi/4)
                    povorot = -Pi/4;
            }
            else{
                static bool was = 0;
                if(povorot < 0){
                    was = 1;
                    povorot += dtime;
                }
                else
                    was = 0;
                if(was == 1){
                    if(povorot >= 0){
                        povorot = 0;
                        was = 0;
                    }
                    else
                        was = 1;
                }
            }
        }
        static XYZ dviz;
        if(fall_speed == 0){
            dviz.x = EX.x*skorost*dtime;
            dviz.y = EX.y*skorost*dtime;
            dviz.z = EX.z*skorost*dtime;
        }
        else
            dviz.z -= G*dtime*dtime;
//        pos += dviz;
        Move(dviz);
        if(fall_speed == 0){
            if(skorost > 0.)
                Povorot_Po_Osi(EZ, dtime*povorot*sqrt(skorost)/2);
            else if(skorost < 0.)
                Povorot_Po_Osi(EZ, -dtime*povorot*sqrt(-skorost)/2);
        }
        double vys = terrain.Where_On_Terrain(pos);
        if(vys > 0.01){
            fall_speed -= G*dtime*dtime;
        }
        else{
//            pos.z -= vys;
            XYZ minvys = {0., 0., -vys};
            Move(minvys);
            fall_speed = 0;
        }
    }
};

class Dynamic_OBJ_1 : public Object_OBJ {
private:
    XYZ Out_Sily = {0.,0.,0.};
    XYZ impulse = {0.,0.,0.};
    XYZ* tochki;    //  С массами m и расстояниями до них от оси вращения r (до центра масс)
    int t_num = 0;
    double Ze = 0.; //  Момент инерции тела относительно оси вращения
    double *m;
    double *r;
    double M;
    double R;
public:
    void Add_Sily(XYZ S){
        Out_Sily.x += S.x;
        Out_Sily.y += S.y;
        Out_Sily.z += S.z;
    }
    void Find_Ze(){
        Ze = 0;
        for(int i = 0; i < t_num; i++)
            Ze += m[i]*r[i]*r[i];
    }
    void Find_Ze_Any_OSs(XYZ pOSs, XYZ OSs){    //  pOSs - место оси вращения (её координаты), OSs - вектор оси вращения (сама ось)
        Ze = 0;
        Find_Ze();
        Ze += M*R*R;    //  Масса тела M и расстояние от оси вращения до центра масс R
    }
};

struct Dyn_Point{
    XYZ V;  /// координаты точки
    XYZ dv = {0., 0., 0.}; /// вектор скорости точки (нужен?)
    XYZ di = {0., 0., 0.}; /// вектор импульса точки
    double m;  /// масса точки
    double r;   /// расстояние до центра
    double r2;
    int sostoyanie = 0;
    XYZ OV;
    XYZ oss;    /// создаваемая ось вращения, = vct_perp(OV, di), где OV - вектор от центра масс до V
};

struct Dyn_Box{
    int num_V;
    XYZ V[8];
    bool y[8];
//    XYZ n[6];
};

struct OBB{
    int num_V;
    XYZ *V;
    bool *y;
//    XYZ n[6];
};

struct Sily{
    XYZ F;
    XYZ P;
};

class Dynamic_OBJ_2_1 : public Object_OBJ {
private:
    XYZ Cm;  /// координаты центра масс
    XYZ DI = {0., 0., 0.}; /// вектор импульса точки
    XYZ sDI = {0., 0., 0.};
    double M;
    Dyn_Box Obol;
//    double r;
//    double r2;
    int sostoyanie = 1;
    double koef_ypryg = 2.; /// от 1 до inf
//    XYZ OV;
    XYZ OSS = {0., 0., 0.};
public:
    void Create(double t_M, double t_koef_ypryg){
        Cm = {0., 0., 0.};
        DI = {0., 0., 0.};
        sDI = {0., 0., 0.};
        OSS = {0., 0., 0.};
        M = t_M;
        sostoyanie = 1;
        koef_ypryg = t_koef_ypryg;
        Obol.V[0] = {-0.5, -0.5, -0.5};
        Obol.V[1] = {0.5, -0.5, -0.5};
        Obol.V[2] = {0.5, 0.5, -0.5};
        Obol.V[3] = {-0.5, 0.5, -0.5};
        Obol.V[4] = {-0.5, -0.5, 0.5};
        Obol.V[5] = {0.5, -0.5, 0.5};
        Obol.V[6] = {0.5, 0.5, 0.5};
        Obol.V[7] = {-0.5, 0.5, 0.5};
        for(int i = 0; i < 8; i++)
            Obol.y[i] = 0;
    }
    XYZ Ydar(XYZ P, double sila, XYZ n_poverhnosti){
//        XYZ P;  /// точка удара
//        double sila;    /// сила удара
//        XYZ vP = vct_ration(DI) * (-sila);
        XYZ pvP;
        XYZ rychag;
        double plosh;
        double l_ydara;
        XYZ oss;

        XYZ CmP = P;
//        XYZ PCm = Cm - P;
        pvP = DI ^ CmP;
        plosh = sqrt(pvP*pvP);/*vct_dlina(pvP);*/
//        cout << "plosh = " << plosh << endl;
        rychag = DI ^ pvP;
//        cout << "RYCHAG = ";
//        vct_print(rychag);
        rychag = vct_ration(rychag);
//        cout << "RYCHAG = ";
//        vct_print(rychag);
        if(sqrt(DI*DI) > 0.01)
            l_ydara = (plosh / sqrt(DI*DI));
        else
            l_ydara = 0;
//        cout << "l_ydara = " << l_ydara << endl;
        rychag = rychag * l_ydara;
//        cout << "RYCHAG = ";
//        vct_print(rychag);

        oss = pvP;/* / (1 + l_ydara); / plosh;
        oss = oss * l_ydara;*/
//        vct_print(oss);
//        XYZ vP; /*= DI * (-1); /// вектор удара, обратен вектору импульса (движения лучше)*/
//        vP.x = -DI.x;
//        vP.y = -DI.y;
//        vP.z = -DI.z;
//        tDI = DI + vP * vct_SP(DI, CmP) * koef_ypryg;

        etx << "x = ";
        etx << oss.x;
        etx << " y = ";
        etx << oss.y;
        etx << " z = ";
        etx << oss.z;
        etx << "\n";
        OSS = OSS + oss/8;
//        vct_print(OSS);
//        return = vct_ration(n_poverhnosti) * sqrt(DI*DI)
        n_poverhnosti = vct_ration(n_poverhnosti);
        return (n_poverhnosti * vct_dlina(DI))*(-vct_SP(vct_ration(DI), n_poverhnosti)/**vct_SP(vct_ration(DI), vct_ration(CmP))*/*koef_ypryg);
//        return vP * vct_SP(DI, CmP) * koef_ypryg / 8;
//        if(sostoyanie != 0){
//            DI = DI - FV*dtime*dtime*M;
//        }
    }
    void Dynamic_Povorot_Po_Osi(XYZ n, double teta){
        double l;
        l = vct_dlina(n);
        if(l < 0.01)
            return;
        n = n / l;
        n = n;
        teta *= l;
        double* M = new double[9];
        double c = cos(teta);
        double s = sin(teta);

        M[0] = c + (1 - c)*n.x*n.x;
        M[1] = (1 - c)*n.x*n.y - s*n.z;
        M[2] = (1 - c)*n.x*n.z + s*n.y;
        M[3] = (1 - c)*n.y*n.x + s*n.z;
        M[4] = c + (1 - c)*n.y*n.y;
        M[5] = (1 - c)*n.y*n.z - s*n.x;
        M[6] = (1 - c)*n.z*n.x - s*n.y;
        M[7] = (1 - c)*n.z*n.y + s*n.x;
        M[8] = c + (1 - c)*n.z*n.z;

        XYZ gdO;
        gdO.x = M[0]*EX.x + M[1]*EX.y + M[2]*EX.z;
        gdO.y = M[3]*EX.x + M[4]*EX.y + M[5]*EX.z;
        gdO.z = M[6]*EX.x + M[7]*EX.y + M[8]*EX.z;
        EX = gdO;
        gdO.x = M[0]*EY.x + M[1]*EY.y + M[2]*EY.z;
        gdO.y = M[3]*EY.x + M[4]*EY.y + M[5]*EY.z;
        gdO.z = M[6]*EY.x + M[7]*EY.y + M[8]*EY.z;
        EY = gdO;
        gdO.x = M[0]*EZ.x + M[1]*EZ.y + M[2]*EZ.z;
        gdO.y = M[3]*EZ.x + M[4]*EZ.y + M[5]*EZ.z;
        gdO.z = M[6]*EZ.x + M[7]*EZ.y + M[8]*EZ.z;
        EZ = gdO;

        for(int i = 0; i < 8; i++){
            XYZ gdO;
            gdO.x = M[0]*Obol.V[i].x + M[1]*Obol.V[i].y + M[2]*Obol.V[i].z;
            gdO.y = M[3]*Obol.V[i].x + M[4]*Obol.V[i].y + M[5]*Obol.V[i].z;
            gdO.z = M[6]*Obol.V[i].x + M[7]*Obol.V[i].y + M[8]*Obol.V[i].z;
            Obol.V[i] = gdO;
        }
        delete(M);

        Update_Matrix();
    }
    void Update(double dtime, Terrain& terrain){
        etx << "x = ";
        etx << OSS.x;
        etx << "\ny = ";
        etx << OSS.y;
        etx << "\nz = ";
        etx << OSS.z;
        etx << "\n";
//        vct_print(sDI);
//        sDI = sDI - sDI*0.02;
//        OSS = OSS - OSS*0.03;
        pos = pos + sDI*dtime;
//        cout << "sDI = ";
//        vct_print(sDI);
        DI = sDI;
//        cout << "DI = ";
//        vct_print(DI);
        XYZ ydar = {0., 0., 0.};
        double h;
        XYZ reac;
        int k = 0;
        if(DI.x != 0 || DI.y != 0 || DI.z != 0){
            for(int i = 0; i < 8; i++){
                if((h = terrain.Where_On_Terrain(Obol.V[i] + pos)) < 0){
                    if(Obol.y[i] == 0){
//                        cout << "DI = ";
//                        vct_print(DI);
                        reac = terrain.Normal_Of_Terrain(Obol.V[i] + pos);
                        k++;
        //                DI = tDI;

                        ydar = ydar + Ydar(Obol.V[i], 1, reac);
//                        cout << "YDAR " << i << endl << endl;
                    }
                    Obol.y[i] = 1;
                }
                else{
//                    cout << "h = " << h << endl;
                    Obol.y[i] = 0;
                }
            }
        }
//        cout << "YDAR END" << endl;
//        cout << "ydar = ";
//        vct_print(ydar);
//        cout << "ydar = ";
//        vct_print(ydar);
        if(k > 0){
            ydar = ydar / k;
            sDI = sDI + ydar*2;
        }
//        vct_print(sDI);
//        for(int i = 0; i < 8; i++)
//            if((h = terrain.Where_On_Terrain(Obol.V[i] + pos)) < 0){
////                cout << "h = " << h << endl;
////                cout << "Cheat))) " << i << endl;
//                pos.z -= h;
//            }
//        Dynamic_Povorot_Po_Osi(OSS, dtime);
//        etx.Start_Dialog();
//        static const char text[64] = ("это полный пиздец так то");
//        otl << text;
//        for(int i = 0; i < 8; i++)
//            if(terrain.Where_On_Terrain(Obol.V[i] + pos) > 0)
                sDI = sDI + FV*G*dtime;
//        for(int i = 0; i < 8; i++){
//            Obol.V[i] = Obol.V[i] + (DI / M);
//        }
//        Cm = pos;
//        for(int i = 0; i < 8; i++)
////            vct_print(Obol.V[i]);
//            cout << vct_dlina(Obol.V[i]) << endl;
//        cout << endl << endl << endl;
    }
    void teleport(XYZ ppp){
        pos = pos + ppp;
//        Cm = pos;
//        for(int i = 0; i < 8; i++){
//            Obol.V[i] = Obol.V[i] + ppp;
//        }
    }
};

class Dynamic_OBJ_5 : public Object_OBJ {
private:
    XYZ O;
    OBB box;
    double M;

//    XYZ sily;
    XYZ P;  /// impulse
    XYZ V;  /// скорость
    XYZ a;  /// ускорение
    XYZ *F; /// прикладываемые силы
    int N_F;
//    XYZ *rF;  /// результирующие силы
    Sily *rF;
    XYZ resF;
    int num_F = 0;  /// их количество
public:
    void Create(double tM){
        box.V = new XYZ[num_v];
        for(int i = 0; i < num_v; i++){
            box.V[i] = v[i];
            box.y[i] = 0;
        }
        box.num_V = num_v;
        N_F = 0;
        rF = new Sily[0];
    }
    void Add_Sily(XYZ P, XYZ F){    //  вектор силы F в точке P (P - точка тела)
        rF = (Sily*)realloc(rF, (num_F + 1)*sizeof(Sily));
        rF[num_F].F = F;
        rF[num_F].P = P;
        num_F += 1;
    }
    void test(double dtime, Terrain& terrain, double u, XYZ N){    /// u - коеффициент трения поверхности
        --resF;   /// обнуление вектора (см. оператор --XYZ)
        resF += M*vG; /// сила притяжения

        /// НЕОБХОДИМО НАЙТИ ВЕКТОР N ИЗ (ВСЕХ?) ТОЧЕК СОПРИКОСНОВЕНИЯ
        // в конце
        XYZ n_terr = {0., 0., 0.};
        int n_t = 0;
        for(int i = 0; i < 8; i++){
            if((terrain.Where_On_Terrain(box.V[i] + O)) < 0.01){
                n_terr += terrain.Normal_Of_Terrain(box.V[i] + O);
                n_t++;
            }
        }
        if(n_t > 0)
            n_terr /= n_t;

//        if(fabs(rF.x) < 0.001 || fabs(rF.y) < 0.001 || fabs(rF.z) < 0.001){}
        if(n_t > 0){
            XYZ v_dviz = vct_perp(n_terr, resF);
            v_dviz = vct_perp(v_dviz, n_terr);
            v_dviz = vct_ration(v_dviz);

            N = resF * vct_ygol(resF, n_terr);
            N *= -1;
            resF += N;
            double u = terrain.Return_u();
            resF += u*vct_dlina(N) * v_dviz; //(а вектор какой?);  /// N - реакция опоры (сила трения)
        }
//        if(param_in_water == 1)
//            rF += po*g*V(узнать о векторе действия);
    }
    void Update(double dtime, Terrain& terrain){
//        P = V*M;
//        a = sum(F,num_F)/M; /// 2-й Закон Ньютона, F = ma;

    }
};

class Dynamic_OBJ_4 : public Object_OBJ {
private:
    XYZ O;
    Dyn_Box box;
    double M;

    XYZ sily;
    XYZ P;  /// impulse
    XYZ V;  /// скорость
    XYZ a;  /// ускорение
    XYZ *F; /// прикладываемые силы
    XYZ rF = {0., 0., 0.};  /// результирующие силы
    int num_F = 0;  /// их количество
public:
    void Create(double tM){
        box.num_V = 8;
        box.V[0] = {-0.5, -0.5, -0.5};
        box.V[1] = {0.5, -0.5, -0.5};
        box.V[2] = {0.5, 0.5, -0.5};
        box.V[3] = {-0.5, 0.5, -0.5};
        box.V[4] = {-0.5, -0.5, 0.5};
        box.V[5] = {0.5, -0.5, 0.5};
        box.V[6] = {0.5, 0.5, 0.5};
        box.V[7] = {-0.5, 0.5, 0.5};
        for(int i = 0; i < box.num_V; i++)
            box.y[i] = 0;
        M = tM;
    }
    void test(double dtime, Terrain& terrain, double u, XYZ N){    /// u - коеффициент трения поверхности
        --rF;   /// обнуление вектора (см. оператор --XYZ)
        rF += M*vG; /// сила притяжения


        // в конце
        XYZ n_terr = {0., 0., 0.};
        int n_t = 0;
        for(int i = 0; i < 8; i++){
            if((terrain.Where_On_Terrain(box.V[i] + O)) < 0.01){
                n_terr += terrain.Normal_Of_Terrain(box.V[i] + O);
                n_t++;
            }
        }
        if(n_t > 0)
            n_terr /= n_t;

//        if(fabs(rF.x) < 0.001 || fabs(rF.y) < 0.001 || fabs(rF.z) < 0.001){}
        if(n_t > 0){
            XYZ v_dviz = vct_perp(n_terr, rF);
            v_dviz = vct_perp(v_dviz, n_terr);
            v_dviz = vct_ration(v_dviz);

            N = rF * vct_ygol(rF, n_terr);
            N *= -1;
            rF += N;
            double u = terrain.Return_u();
            rF += u*vct_dlina(N) * v_dviz; //(а вектор какой?);  /// N - реакция опоры (сила трения)
        }
//        if(param_in_water == 1)
//            rF += po*g*V(узнать о векторе действия);
    }
    void Update(double dtime, Terrain& terrain){
//        P = V*M;
//        a = sum(F,num_F)/M; /// 2-й Закон Ньютона, F = ma;

    }
};
//*/
class Dynamic_OBJ_3 : public Object_OBJ {
private:
    XYZ Cm;  /// координаты центра масс
    XYZ DI = {0., 0., 0.}; /// вектор импульса точки
    XYZ sDI = {0., 0., 0.};
    double M;
    Dyn_Box Obol;
//    double r;
//    double r2;
    int sostoyanie = 1;
    double koef_ypryg = 2.; /// от 1 до inf
//    XYZ OV;
    XYZ OSS = {0., 0., 0.};
public:
    void Create(double t_M, double t_koef_ypryg){
        Cm = {0., 0., 0.};
        DI = {0., 0., 0.};
        sDI = {0., 0., 0.};
        OSS = {0., 0., 0.};
        M = t_M;
        sostoyanie = 1;
        koef_ypryg = t_koef_ypryg;
        Obol.V[0] = {-0.5, -0.5, -0.5};
        Obol.V[1] = {0.5, -0.5, -0.5};
        Obol.V[2] = {0.5, 0.5, -0.5};
        Obol.V[3] = {-0.5, 0.5, -0.5};
        Obol.V[4] = {-0.5, -0.5, 0.5};
        Obol.V[5] = {0.5, -0.5, 0.5};
        Obol.V[6] = {0.5, 0.5, 0.5};
        Obol.V[7] = {-0.5, 0.5, 0.5};
        for(int i = 0; i < 8; i++)
            Obol.y[i] = 0;
//        n[0] = {}
//        n[1] = {}
//        n[2] = {}
//        n[3] = {}
//        n[4] = {}
//        n[5] = {}

//        f 1 2 3
//        f 1 3 4
//        f 1 2 6
//        f 1 5 6
//        f 2 3 6
//        f 3 6 7
//        f 3 4 8
//        f 3 8 7
//        f 1 4 8
//        f 1 8 5
//        f 5 6 7
//        f 5 7 8
    }
    XYZ Ydar(XYZ P, double sila, XYZ n_poverhnosti){
//        XYZ P;  /// точка удара
//        double sila;    /// сила удара
//        XYZ vP = vct_ration(DI) * (-sila);
        XYZ pvP;
        XYZ rychag;
        double plosh;
        double l_ydara;
        XYZ oss;

        XYZ CmP = P;
//        XYZ PCm = Cm - P;
        pvP = DI ^ CmP;
        plosh = sqrt(pvP*pvP);/*vct_dlina(pvP);*/
//        cout << "plosh = " << plosh << endl;
        rychag = DI ^ pvP;
//        cout << "RYCHAG = ";
//        vct_print(rychag);
        rychag = vct_ration(rychag);
//        cout << "RYCHAG = ";
//        vct_print(rychag);
        if(sqrt(DI*DI) > 0.01)
            l_ydara = (plosh / sqrt(DI*DI));
        else
            l_ydara = 0;
//        cout << "l_ydara = " << l_ydara << endl;
        rychag = rychag * l_ydara;
//        cout << "RYCHAG = ";
//        vct_print(rychag);

        oss = pvP;/* / (1 + l_ydara); / plosh;
        oss = oss * l_ydara;*/
//        vct_print(oss);
//        XYZ vP; /*= DI * (-1); /// вектор удара, обратен вектору импульса (движения лучше)*/
//        vP.x = -DI.x;
//        vP.y = -DI.y;
//        vP.z = -DI.z;
//        tDI = DI + vP * vct_SP(DI, CmP) * koef_ypryg;

        etx << "x = ";
        etx << oss.x;
        etx << " y = ";
        etx << oss.y;
        etx << " z = ";
        etx << oss.z;
        etx << "\n";
        OSS = OSS + oss/8;
//        vct_print(OSS);
//        return = vct_ration(n_poverhnosti) * sqrt(DI*DI)
        n_poverhnosti = vct_ration(n_poverhnosti);
        return (n_poverhnosti * vct_dlina(DI))*(-vct_SP(vct_ration(DI), n_poverhnosti)/**vct_SP(vct_ration(DI), vct_ration(CmP))*/*koef_ypryg);
//        return vP * vct_SP(DI, CmP) * koef_ypryg / 8;
//        if(sostoyanie != 0){
//            DI = DI - FV*dtime*dtime*M;
//        }
    }
    void Dynamic_Povorot_Po_Osi(XYZ n, double teta){
        double l;
        l = vct_dlina(n);
        if(l < 0.01)
            return;
        n = n / l;
        n = n;
        teta *= l;
        double* M = new double[9];
        double c = cos(teta);
        double s = sin(teta);

        M[0] = c + (1 - c)*n.x*n.x;
        M[1] = (1 - c)*n.x*n.y - s*n.z;
        M[2] = (1 - c)*n.x*n.z + s*n.y;
        M[3] = (1 - c)*n.y*n.x + s*n.z;
        M[4] = c + (1 - c)*n.y*n.y;
        M[5] = (1 - c)*n.y*n.z - s*n.x;
        M[6] = (1 - c)*n.z*n.x - s*n.y;
        M[7] = (1 - c)*n.z*n.y + s*n.x;
        M[8] = c + (1 - c)*n.z*n.z;

        XYZ gdO;
        gdO.x = M[0]*EX.x + M[1]*EX.y + M[2]*EX.z;
        gdO.y = M[3]*EX.x + M[4]*EX.y + M[5]*EX.z;
        gdO.z = M[6]*EX.x + M[7]*EX.y + M[8]*EX.z;
        EX = gdO;
        gdO.x = M[0]*EY.x + M[1]*EY.y + M[2]*EY.z;
        gdO.y = M[3]*EY.x + M[4]*EY.y + M[5]*EY.z;
        gdO.z = M[6]*EY.x + M[7]*EY.y + M[8]*EY.z;
        EY = gdO;
        gdO.x = M[0]*EZ.x + M[1]*EZ.y + M[2]*EZ.z;
        gdO.y = M[3]*EZ.x + M[4]*EZ.y + M[5]*EZ.z;
        gdO.z = M[6]*EZ.x + M[7]*EZ.y + M[8]*EZ.z;
        EZ = gdO;

        for(int i = 0; i < 8; i++){
            XYZ gdO;
            gdO.x = M[0]*Obol.V[i].x + M[1]*Obol.V[i].y + M[2]*Obol.V[i].z;
            gdO.y = M[3]*Obol.V[i].x + M[4]*Obol.V[i].y + M[5]*Obol.V[i].z;
            gdO.z = M[6]*Obol.V[i].x + M[7]*Obol.V[i].y + M[8]*Obol.V[i].z;
            Obol.V[i] = gdO;
        }
        delete(M);

        Update_Matrix();
    }
    void Update(double dtime, Terrain& terrain){
        etx << "x = ";
        etx << OSS.x;
        etx << "\ny = ";
        etx << OSS.y;
        etx << "\nz = ";
        etx << OSS.z;
        etx << "\n";
//        vct_print(sDI);
//        sDI = sDI - sDI*0.02;
//        OSS = OSS - OSS*0.03;
        pos = pos + sDI*dtime;
//        cout << "sDI = ";
//        vct_print(sDI);
        DI = sDI;
//        cout << "DI = ";
//        vct_print(DI);
        XYZ ydar = {0., 0., 0.};
        double h;
        XYZ reac;
        int k = 0;
        if(DI.x != 0 || DI.y != 0 || DI.z != 0){
            for(int i = 0; i < 8; i++){
                if((h = terrain.Where_On_Terrain(Obol.V[i] + pos)) < 0){
                    if(Obol.y[i] == 0){
//                        cout << "DI = ";
//                        vct_print(DI);
                        reac = terrain.Normal_Of_Terrain(Obol.V[i] + pos);
                        k++;
        //                DI = tDI;

                        ydar = ydar + Ydar(Obol.V[i], 1, reac);
//                        cout << "YDAR " << i << endl << endl;
                    }
                    Obol.y[i] = 1;
                }
                else{
//                    cout << "h = " << h << endl;
                    Obol.y[i] = 0;
                }
            }
        }
//        cout << "YDAR END" << endl;
//        cout << "ydar = ";
//        vct_print(ydar);
//        cout << "ydar = ";
//        vct_print(ydar);
        if(k > 0){
            ydar = ydar / k;
            sDI = sDI + ydar*2;
        }
//        vct_print(sDI);
        for(int i = 0; i < 8; i++)
            if((h = terrain.Where_On_Terrain(Obol.V[i] + pos)) < 0){
//                cout << "h = " << h << endl;
//                cout << "Cheat))) " << i << endl;
                pos.z -= h;
            }
//        Dynamic_Povorot_Po_Osi(OSS, dtime);
//        etx.Start_Dialog();
//        static const char text[64] = ("это полный пиздец так то");
//        otl << text;
//        for(int i = 0; i < 8; i++)
//            if(terrain.Where_On_Terrain(Obol.V[i] + pos) > 0)
                sDI = sDI + FV*G*dtime;
//        for(int i = 0; i < 8; i++){
//            Obol.V[i] = Obol.V[i] + (DI / M);
//        }
//        Cm = pos;
//        for(int i = 0; i < 8; i++)
////            vct_print(Obol.V[i]);
//            cout << vct_dlina(Obol.V[i]) << endl;
//        cout << endl << endl << endl;
    }
    void teleport(XYZ ppp){
        pos = pos + ppp;
//        Cm = pos;
//        for(int i = 0; i < 8; i++){
//            Obol.V[i] = Obol.V[i] + ppp;
//        }
    }
};

class Dynamic_OBJ_2 : public Object_OBJ {
private:
    double M = 1.;
    XYZ O;
    Dyn_Point *V;
    int num_V = 0;
    double koef_ypryg = 0.7; /// от 0 до 1

    XYZ OSS = {0., 0., 0.};
    XYZ DI = {0., 0., 0.};
public:
    void Create(XYZ *t_V, int t_num_V, XYZ t_O, double t_M){
        M = t_M;
        num_V = t_num_V;
        O = t_O;
        V = new Dyn_Point[num_V];
        for(int i = 0; i < num_V; i++){
            V[i].V = t_V[i];
            V[i].di = {0., 0., 0.};
            V[i].OV = V[i].V - O;
            V[i].oss = {0., 0., 0.};
            V[i].r = vct_dlina(V[i].OV);
            V[i].m = M/num_V;               /// пробная версия, после изменить
            V[i].r2 = V[i].r*V[i].r;                  /// квадрат расстояния
        }
    }
    void Dynamic_Povorot_Po_Osi(XYZ n, double teta){
        double l;
        l = vct_dlina(n);
        n = n / l;
        teta *= l;
        double* M = new double[9];
        double c = cos(teta);
        double s = sin(teta);

        M[0] = c + (1 - c)*n.x*n.x;
        M[1] = (1 - c)*n.x*n.y - s*n.z;
        M[2] = (1 - c)*n.x*n.z + s*n.y;
        M[3] = (1 - c)*n.y*n.x + s*n.z;
        M[4] = c + (1 - c)*n.y*n.y;
        M[5] = (1 - c)*n.y*n.z - s*n.x;
        M[6] = (1 - c)*n.z*n.x - s*n.y;
        M[7] = (1 - c)*n.z*n.y + s*n.x;
        M[8] = c + (1 - c)*n.z*n.z;

        XYZ gdO;
        gdO.x = M[0]*EX.x + M[1]*EX.y + M[2]*EX.z;
        gdO.y = M[3]*EX.x + M[4]*EX.y + M[5]*EX.z;
        gdO.z = M[6]*EX.x + M[7]*EX.y + M[8]*EX.z;
        EX = gdO;
        gdO.x = M[0]*EY.x + M[1]*EY.y + M[2]*EY.z;
        gdO.y = M[3]*EY.x + M[4]*EY.y + M[5]*EY.z;
        gdO.z = M[6]*EY.x + M[7]*EY.y + M[8]*EY.z;
        EY = gdO;
        gdO.x = M[0]*EZ.x + M[1]*EZ.y + M[2]*EZ.z;
        gdO.y = M[3]*EZ.x + M[4]*EZ.y + M[5]*EZ.z;
        gdO.z = M[6]*EZ.x + M[7]*EZ.y + M[8]*EZ.z;
        EZ = gdO;

        for(int i = 0; i < num_V; i++){
            XYZ gdO;
            gdO.x = M[0]*V[i].V.x + M[1]*V[i].V.y + M[2]*V[i].V.z;
            gdO.y = M[3]*V[i].V.x + M[4]*V[i].V.y + M[5]*V[i].V.z;
            gdO.z = M[6]*V[i].V.x + M[7]*V[i].V.y + M[8]*V[i].V.z;
            V[i].V = gdO;
//            gdO.x = M[0]*V[i].V.x + M[1]*V[i].V.y + M[2]*V[i].V.z;
//            gdO.y = M[3]*V[i].V.x + M[4]*V[i].V.y + M[5]*V[i].V.z;
//            gdO.z = M[6]*V[i].V.x + M[7]*V[i].V.y + M[8]*V[i].V.z;
//            V[i].V = gdO;
            gdO.x = M[0]*V[i].OV.x + M[1]*V[i].OV.y + M[2]*V[i].OV.z;
            gdO.y = M[3]*V[i].OV.x + M[4]*V[i].OV.y + M[5]*V[i].OV.z;
            gdO.z = M[6]*V[i].OV.x + M[7]*V[i].OV.y + M[8]*V[i].OV.z;
            V[i].OV = gdO;
        }
        delete(M);

        Update_Matrix();
    }
    void Update(double dtime, Terrain& terrain){
        XYZ tDI = {0., 0., 0.};
        XYZ tOSS = {0., 0., 0.};
        for(int i = 0; i < num_V; i++){
            if(terrain.Where_On_Terrain(V[i].V) >= 0){
                V[i].di = V[i].di + FV*dtime*dtime*V[i].m;
                V[i].sostoyanie = 0;
            }
            else if(V[i].sostoyanie == 0 && terrain.Where_On_Terrain(V[i].V) < 0){
                XYZ n;
                n = terrain.Normal_Of_Terrain(V[i].V);
                V[i].di = vct_otrazeniya(V[i].di, n);
                V[i].di = V[i].di*koef_ypryg;
                V[i].sostoyanie = 1;
            }
            if(V[i].di == 0){
                V[i].oss = {0., 0., 0.};
            }
            else{
                V[i].oss = V[i].OV ^ V[i].di;
            }
            tDI = tDI + V[i].di;
            tOSS = OSS + V[i].oss;
        }
        DI = tDI;
        OSS = tOSS;

        Dynamic_Povorot_Po_Osi(OSS, dtime);
        pos = pos + DI;
    }
    ~Dynamic_OBJ_2(){
        delete(V);
    }
};

class Button {
private:
    double tli = 0, tlj = 0;       //  ширина и высота текстуры
    int type = 0;
public:
    double posi = 0, posj = 0;     //  левая верхняя точка текстуры на экране
    double li = 0, lj = 0;         //  ширина и высота кнопки
    unsigned char *texture;
    Button(){}
//    void Button_load(){
//        li = resolution.shirina / 10;
//        lj = resolution.vysota / 10;
//        posi = (resolution.shirina / 2) - (li / 2);
//        posj = (resolution.vysota / 4) - (lj / 2);
//        delete(texture);
//        texture = new unsigned char[(int)(lj*li*4)];
//        for(int j = 0; j < lj; j++){
//            for(int i = 0; i < li*4; i++){
//                texture[(int)(j*li*4+i)] = 0;
//            }
//        }
//        type = 1;
//    }
    void Button_load(double t_li, double t_lj, double t_posi, double t_posj, char* texture_adress){
        li = t_li;
        lj = t_lj;
        posi = (int)(t_posi * resolution.shirina - t_li / 2);
        posj = (int)(t_posj * resolution.vysota - t_lj / 2);
        if(PARAM_Console_On == 1)
            cout << li << " " << lj << " " << posi << " " << posj << endl;
        int temp_i = 0, temp_j = 0;
//        delete(texture);
        texture = new unsigned char[0];
        texture = loadBMP(texture_adress, temp_i, temp_j);
        if(texture == NULL){
            temp_i = t_li;
            temp_j = t_lj;
            delete(texture);
            texture = new unsigned char[temp_i*temp_j*4];
            for(int j = 0; j < temp_j; j++){
                for(int i = 0; i < temp_i; i++){
                    texture[j*temp_i*4 + i*4] = 30;
                    texture[j*temp_i*4 + i*4 + 1] = 30;
                    texture[j*temp_i*4 + i*4 + 2] = 5;
                    texture[j*temp_i*4 + i*4 + 3] = 1;
                }
            }
            tli = temp_i;
            tlj = temp_j;
            type = 1;
        }
        else{
            tli = temp_i;
            tlj = temp_j;
            type = 3;
        }
    }
    void Paint(){
        if(type == 1){
            for(int j = 0; j < lj; j++){
                for(int i = 0; i < li*4; i++){
                    if((i + posi)*4 > 0 && (i + posi)*4 < resolution.shirina && j > 0 && j < resolution.vysota)
                        pixels[(int)((j+posj)*resolution.shirina*4 + i + (posi*4))] = texture[(int)(j*li*4 + i)];
                }
            }
        }
        else if(type == 3){
            for(int j = 0; j < lj; j++){
                for(int i = 0; i < li; i++){
                    if(i + posi > 0 && i + posi < resolution.shirina && j + posj > 0 && j + posj < resolution.vysota){
                        *(ipixels + (int)((resolution.vysota - (j+posj))*resolution.shirina + (i+posi))) = *((int*)texture + (int)((lj - 1 - j)*(tlj/lj)*tli + i*(tli/li)));
//                        pixels[(int)((resolution.vysota - (j+posj))*resolution.shirina*4 + (i+posi)*4)] = texture[(int)(j*(tlj/lj)*tli*4 + i*(tli/li)*4)];
//                        pixels[(int)((resolution.vysota - (j+posj))*resolution.shirina*4 + (i+posi)*4 + 1)] = texture[(int)(j*(tlj/lj)*tli*4 + i*(tli/li)*4 + 1)];
//                        pixels[(int)((resolution.vysota - (j+posj))*resolution.shirina*4 + (i+posi)*4 + 2)] = texture[(int)(j*(tlj/lj)*tli*4 + i*(tli/li)*4 + 2)];
//                        pixels[(int)((resolution.vysota - (j+posj))*resolution.shirina*4 + (i+posi)*4 + 3)] = texture[(int)(j*(tlj/lj)*tli*4 + i*(tli/li)*4 + 3)];
                    }
                }
            }
        }
    }
    bool is_there(POINT cursor){
        if(cursor.x > posi && cursor.x < (posi + li) && cursor.y > posj && cursor.y < (posj + lj))
            return 1;
        return 0;
    }
};


void Terrain::Load_Terrain(ifstream &filename){
    filename >> razm_y;
    filename >> razm_x;

    v = new XYZ[razm_y*razm_x];

    for(int i = 0; i < razm_y; i++){
        for(int j = 0; j < razm_x; j++){
            filename >> v[i*razm_x + j].z;
            v[i*razm_x + j].x = (j - razm_x/2)*scale;
            v[i*razm_x + j].y = (i - razm_y/2)*scale;
            v[i*razm_x + j].z *= scale * scale_height;
        }
    }

    projected_points = new XY[razm_y*razm_x];
    l = new double[razm_y*razm_x];
    is_on_scene = new bool[razm_y*razm_x];
}
void Terrain::Paint(Player& Vizor){
    XYZ temp_rast;
    int temp_i;
    int temp_ip1;
    for(int i = 0; i < razm_y; i++){
        for(int j = 0; j < razm_x; j++){
            temp_i = i*razm_x + j;
            projected_points[temp_i] = Vizor.Where_I_See_Point_If_I_Sphere_Hacker_Edition(v[temp_i],Vizor.Eye_pos_minus);
            temp_rast = Vizor.Eye_pos - v[temp_i];
            l[temp_i] = SP(temp_rast,temp_rast);
            if(vct_SP(temp_rast, Vizor.pEX) > 0)
                is_on_scene[temp_i] = 0;
            else
                is_on_scene[temp_i] = 1;
        }
    }
    double tl;
    for(int i = 0; i < razm_y - 1; i++){
        for(int j = 0; j < razm_x - 1; j++){
            temp_i = i*razm_x + j;
            temp_ip1 = temp_i + razm_x;
            if(is_on_scene[temp_i] == 1 || is_on_scene[temp_i + 1] == 1 || is_on_scene[temp_ip1] == 1){
                tl = (l[temp_i] + l[temp_i + 1] + l[temp_ip1]) / 3;
                Draw_Edge_Optimized_ZBUFFER_FAST(projected_points[temp_i], projected_points[temp_i + 1], projected_points[temp_ip1], tl, v[temp_i].z, 255, v[temp_i].z);
            }
            if(is_on_scene[temp_i + 1] == 1 || is_on_scene[temp_ip1] == 1 || is_on_scene[temp_ip1 + 1] == 1){
                tl = (l[temp_i + 1] + l[temp_ip1] + l[temp_ip1 + 1]) / 3;
                Draw_Edge_Optimized_ZBUFFER_FAST(projected_points[temp_i + 1], projected_points[temp_ip1], projected_points[temp_ip1 + 1], tl, 255 - v[temp_ip1].z, 255, 255 - v[temp_ip1].z);
            }
        }
    }
}
double Terrain::Is_On_Terrain(XYZ pos){
    if(pos.x > razm_x/2 || pos.x < -razm_x/2 || pos.y > razm_y/2 || pos.y < -razm_y/2)
        return 0;  /// объект вне территории
//    double height_stand = v[(((int)pos.y + razm_y/2)*razm_x + (int)(pos.x + razm_x/2))].z;
//    return pos.z - height_stand;
    return 1;
}
double Terrain::Where_On_Terrain(XYZ pos){
    if(pos.x > razm_x/2 || pos.x < -razm_x/2 || pos.y > razm_y/2 || pos.y < -razm_y/2)
        return 0;  /// объект вне территории
    else{
        XYZ v1, v2, v3;
        v1 = v[(((int)pos.y + razm_y/2)*razm_x + (int)(pos.x + razm_x/2))];
        v2 = v[(((int)pos.y + razm_y/2)*razm_x + (int)(pos.x + razm_x/2)) + 1];
        v3 = v[(((int)pos.y + razm_y/2 + 1)*razm_x + (int)(pos.x + razm_x/2))];

        double Peres;
        double D, mu;
        double alphaAB, alphaBC, alphaCA;
        double tL;
        XYZ PA, PB, PC;
        XYZ n;
        XYZ OV = {0,0,-1};

        for(int i = 0; i < 2; i++){
            if(i == 0){
                if(pos.y < 0){
                    v1 = v[(((int)pos.y - 1 + razm_y/2)*razm_x + (int)(pos.x + razm_x/2))];
                    v2 = v[(((int)pos.y - 1 + razm_y/2 + 1)*razm_x + (int)(pos.x + razm_x/2))];
                    v3 = v[(((int)pos.y - 1 + razm_y/2)*razm_x + (int)(pos.x + razm_x/2 + 1))];
                }
                else{
                    v1 = v[(((int)pos.y + razm_y/2)*razm_x + (int)(pos.x + razm_x/2))];
                    v2 = v[(((int)pos.y + razm_y/2 + 1)*razm_x + (int)(pos.x + razm_x/2))];
                    v3 = v[(((int)pos.y + razm_y/2)*razm_x + (int)(pos.x + razm_x/2 + 1))];
                }
            }
            else if(i == 1){
                if(pos.y < 0){
                    v1 = v[(((int)pos.y - 1 + razm_y/2 + 1)*razm_x + (int)(pos.x + razm_x/2 + 1))];
                    v2 = v[(((int)pos.y - 1 + razm_y/2)*razm_x + (int)(pos.x + razm_x/2 + 1))];
                    v3 = v[(((int)pos.y - 1 + razm_y/2 + 1)*razm_x + (int)(pos.x + razm_x/2))];
                }
                else{
                    v1 = v[(((int)pos.y + razm_y/2 + 1)*razm_x + (int)(pos.x + razm_x/2 + 1))];
                    v2 = v[(((int)pos.y + razm_y/2)*razm_x + (int)(pos.x + razm_x/2 + 1))];
                    v3 = v[(((int)pos.y + razm_y/2 + 1)*razm_x + (int)(pos.x + razm_x/2))];
                }
            }
    ///                     Точка пересечения
            PA = v1;
            n = vct_perp(vct_is_tocheck(v1, v2),vct_is_tocheck(v1, v3));
            D = n.x*PA.x + n.y*PA.y + n.z*PA.z;
            D *= -1;
            mu = ( D + n.x*pos.x + n.y*pos.y + n.z*pos.z ) / ( n.z );
            Peres = pos.z + OV.z*mu;
        ///                     Проверка пересечения с треугольником

            PA.x = PA.x - pos.x;
            PA.y = PA.y - pos.y;
            PA.z = PA.z - Peres;

            PB.x = v2.x - pos.x;
            PB.y = v2.y - pos.y;
            PB.z = v2.z - Peres;

            PC.x = v3.x - pos.x;
            PC.y = v3.y - pos.y;
            PC.z = v3.z - Peres;

            tL = SqrtInv(PA.x*PA.x + PA.y*PA.y + PA.z*PA.z);
            PA.x = PA.x/tL;
            PA.y = PA.y/tL;
            PA.z = PA.z/tL;

            tL = SqrtInv(PB.x*PB.x + PB.y*PB.y + PB.z*PB.z);
            PB.x = PB.x/tL;
            PB.y = PB.y/tL;
            PB.z = PB.z/tL;

            tL = SqrtInv(PC.x*PC.x + PC.y*PC.y + PC.z*PC.z);
            PC.x = PC.x/tL;
            PC.y = PC.y/tL;
            PC.z = PC.z/tL;
            alphaAB = PA.x*PB.x + PA.y*PB.y + PA.z*PB.z;
            alphaBC = PB.x*PC.x + PB.y*PC.y + PB.z*PC.z;
            alphaCA = PC.x*PA.x + PC.y*PA.y + PC.z*PA.z;

            tL = alphaAB + alphaBC + alphaCA;

            if(tL <= -1){
                return pos.z - Peres;
            }
        }
        return 0;
    }
}
XYZ Terrain::Normal_Of_Terrain(XYZ pos){
    XYZ zero = {0., 0., 0.};
    if(pos.x > razm_x/2 || pos.x < -razm_x/2 || pos.y > razm_y/2 || pos.y < -razm_y/2)
        return zero;  /// объект вне территории
    else{
        XYZ v1, v2, v3;
//        v1 = v[(((int)pos.y + razm_y/2)*razm_x + (int)(pos.x + razm_x/2))];
//        v2 = v[(((int)pos.y + razm_y/2)*razm_x + (int)(pos.x + razm_x/2)) + 1];
//        v3 = v[(((int)pos.y + razm_y/2 + 1)*razm_x + (int)(pos.x + razm_x/2))];

        double Peres;
        double D, mu;
        double alphaAB, alphaBC, alphaCA;
        double tL;
        XYZ PA, PB, PC;
        XYZ n;
        XYZ OV = {0,0,-1};

        for(int i = 0; i < 2; i++){
            if(i == 0){
                if(pos.y < 0){
                    v1 = v[(((int)pos.y - 1 + razm_y/2)*razm_x + (int)(pos.x + razm_x/2))];
                    v2 = v[(((int)pos.y - 1 + razm_y/2 + 1)*razm_x + (int)(pos.x + razm_x/2))];
                    v3 = v[(((int)pos.y - 1 + razm_y/2)*razm_x + (int)(pos.x + razm_x/2 + 1))];
                }
                else{
                    v1 = v[(((int)pos.y + razm_y/2)*razm_x + (int)(pos.x + razm_x/2))];
                    v2 = v[(((int)pos.y + razm_y/2 + 1)*razm_x + (int)(pos.x + razm_x/2))];
                    v3 = v[(((int)pos.y + razm_y/2)*razm_x + (int)(pos.x + razm_x/2 + 1))];
                }
            }
            else if(i == 1){
                if(pos.y < 0){
                    v1 = v[(((int)pos.y - 1 + razm_y/2 + 1)*razm_x + (int)(pos.x + razm_x/2 + 1))];
                    v2 = v[(((int)pos.y - 1 + razm_y/2)*razm_x + (int)(pos.x + razm_x/2 + 1))];
                    v3 = v[(((int)pos.y - 1 + razm_y/2 + 1)*razm_x + (int)(pos.x + razm_x/2))];
                }
                else{
                    v1 = v[(((int)pos.y + razm_y/2 + 1)*razm_x + (int)(pos.x + razm_x/2 + 1))];
                    v2 = v[(((int)pos.y + razm_y/2)*razm_x + (int)(pos.x + razm_x/2 + 1))];
                    v3 = v[(((int)pos.y + razm_y/2 + 1)*razm_x + (int)(pos.x + razm_x/2))];
                }
            }
    ///                     Точка пересечения
            PA = v1;
            n = vct_perp(vct_is_tocheck(v1, v2),vct_is_tocheck(v1, v3));
            D = n.x*PA.x + n.y*PA.y + n.z*PA.z;
            D *= -1;
            mu = ( D + n.x*pos.x + n.y*pos.y + n.z*pos.z ) / ( n.z );
            Peres = pos.z + OV.z*mu;
        ///                     Проверка пересечения с треугольником

            PA.x = PA.x - pos.x;
            PA.y = PA.y - pos.y;
            PA.z = PA.z - Peres;

            PB.x = v2.x - pos.x;
            PB.y = v2.y - pos.y;
            PB.z = v2.z - Peres;

            PC.x = v3.x - pos.x;
            PC.y = v3.y - pos.y;
            PC.z = v3.z - Peres;

            tL = SqrtInv(PA.x*PA.x + PA.y*PA.y + PA.z*PA.z);
            PA.x = PA.x/tL;
            PA.y = PA.y/tL;
            PA.z = PA.z/tL;

            tL = SqrtInv(PB.x*PB.x + PB.y*PB.y + PB.z*PB.z);
            PB.x = PB.x/tL;
            PB.y = PB.y/tL;
            PB.z = PB.z/tL;

            tL = SqrtInv(PC.x*PC.x + PC.y*PC.y + PC.z*PC.z);
            PC.x = PC.x/tL;
            PC.y = PC.y/tL;
            PC.z = PC.z/tL;
            alphaAB = PA.x*PB.x + PA.y*PB.y + PA.z*PB.z;
            alphaBC = PB.x*PC.x + PB.y*PC.y + PB.z*PC.z;
            alphaCA = PC.x*PA.x + PC.y*PA.y + PC.z*PA.z;

            tL = alphaAB + alphaBC + alphaCA;

            if(tL <= -1){
//                if(i == 1){
                    n = vct_YnC(n, -1);
//                }
                return n;
            }
        }
        return zero;
    }
}
double Terrain::Return_u(){
    return u;
}

/// Способ нахождения точки пересечения прямой и треугольника
void text_point_peresecheniya(){
/*
double Terrain::Where_On_Terrain(XYZ pos){
    if(pos.x > razm_x/2 || pos.x < -razm_x/2 || pos.y > razm_y/2 || pos.y < -razm_y/2)
        return 0;  /// объект вне территории
    else{
        XYZ v1, v2, v3;
        v1 = v[(((int)pos.y + razm_y/2)*razm_x + (int)(pos.x + razm_x/2))];
        v2 = v[(((int)pos.y + razm_y/2)*razm_x + (int)(pos.x + razm_x/2)) + 1];
        v3 = v[(((int)pos.y + razm_y/2 + 1)*razm_x + (int)(pos.x + razm_x/2))];

        XYZ Peres;
        double D, mu;
        double alphaAB, alphaBC, alphaCA;
        double tL;
        XYZ PA, PB, PC;
        XYZ VO;
        XYZ n;
        XYZ OV = {0,0,-1};

        for(int i = 0; i < 2; i++){
            if(i == 0){
                if(pos.y < 0){
                    v1 = v[(((int)pos.y - 1 + razm_y/2)*razm_x + (int)(pos.x + razm_x/2))];
                    v2 = v[(((int)pos.y - 1 + razm_y/2 + 1)*razm_x + (int)(pos.x + razm_x/2))];
                    v3 = v[(((int)pos.y - 1 + razm_y/2)*razm_x + (int)(pos.x + razm_x/2 + 1))];
                }
                else{
                    v1 = v[(((int)pos.y + razm_y/2)*razm_x + (int)(pos.x + razm_x/2))];
                    v2 = v[(((int)pos.y + razm_y/2 + 1)*razm_x + (int)(pos.x + razm_x/2))];
                    v3 = v[(((int)pos.y + razm_y/2)*razm_x + (int)(pos.x + razm_x/2 + 1))];
                }
            }
            else if(i == 1){
                if(pos.y < 0){
                    v1 = v[(((int)pos.y - 1 + razm_y/2 + 1)*razm_x + (int)(pos.x + razm_x/2 + 1))];
                    v2 = v[(((int)pos.y - 1 + razm_y/2)*razm_x + (int)(pos.x + razm_x/2 + 1))];
                    v3 = v[(((int)pos.y - 1 + razm_y/2 + 1)*razm_x + (int)(pos.x + razm_x/2))];
                }
                else{
                    v1 = v[(((int)pos.y + razm_y/2 + 1)*razm_x + (int)(pos.x + razm_x/2 + 1))];
                    v2 = v[(((int)pos.y + razm_y/2)*razm_x + (int)(pos.x + razm_x/2 + 1))];
                    v3 = v[(((int)pos.y + razm_y/2 + 1)*razm_x + (int)(pos.x + razm_x/2))];
                }
            }
    ///                     Точка пересечения
            VO.x = -OV.x;
            VO.y = -OV.y;
            VO.z = -OV.z;

            PA = v1;
            n = vct_perp(vct_is_tocheck(v1, v2),vct_is_tocheck(v1, v3));
            D = n.x*PA.x + n.y*PA.y + n.z*PA.z;
            D *= -1;
            mu = ( D + n.x*pos.x + n.y*pos.y + n.z*pos.z ) / ( n.x*VO.x + n.y*VO.y + n.z*VO.z );
            Peres.x = pos.x + OV.x*mu;
            Peres.y = pos.y + OV.y*mu;
            Peres.z = pos.z + OV.z*mu;
        ///                     Проверка пересечения с треугольником

            PA.x = PA.x - Peres.x;
            PA.y = PA.y - Peres.y;
            PA.z = PA.z - Peres.z;

            PB.x = v2.x - Peres.x;
            PB.y = v2.y - Peres.y;
            PB.z = v2.z - Peres.z;

            PC.x = v3.x - Peres.x;
            PC.y = v3.y - Peres.y;
            PC.z = v3.z - Peres.z;

            tL = SqrtInv(PA.x*PA.x + PA.y*PA.y + PA.z*PA.z);
            PA.x = PA.x/tL;
            PA.y = PA.y/tL;
            PA.z = PA.z/tL;

            tL = SqrtInv(PB.x*PB.x + PB.y*PB.y + PB.z*PB.z);
            PB.x = PB.x/tL;
            PB.y = PB.y/tL;
            PB.z = PB.z/tL;

            tL = SqrtInv(PC.x*PC.x + PC.y*PC.y + PC.z*PC.z);
            PC.x = PC.x/tL;
            PC.y = PC.y/tL;
            PC.z = PC.z/tL;
            alphaAB = PA.x*PB.x + PA.y*PB.y + PA.z*PB.z;
            alphaBC = PB.x*PC.x + PB.y*PC.y + PB.z*PC.z;
            alphaCA = PC.x*PA.x + PC.y*PA.y + PC.z*PA.z;

            tL = alphaAB + alphaBC + alphaCA;


    //        if(tL <= (PiDva + 0.001) && tL >= (PiDva - 0.001)){
    //            PERESECH = 1;
    //            break;
    //        }
            if(tL <= -1){
                return pos.z - Peres.z;
            }
        }
        return 0;
    }
}
//*/
}

/**


class Clock {   // abstract class - теперь он абстрактный класс
public:
    virtual void ShowTime() = 0 const;  // pure virtual function - чисто виртуальная функиця
};

class Wallclock : public Clock {
public:
    void ShowTime() const;
};



class Clock {   // abstract class - теперь он абстрактный класс
public:
    virtual void ShowTime() const;  // pure virtual function - чисто виртуальная функиця
    virtual void Func(long arg);

    Clock& operator=(const Clock& other);

    virtual ~Clock();
};

class Wallclock : public Clock {
public:
    //using Clock::operator=;
    WallClock& operator=(const WristWatch& other) :
        Clock::operator=(other);
    void ShowTime() const override final; //  C++11
    void Func(long arg) override;
};

class SmartWallClock : public WallClock {
public:
    void ShowTime();  // нельзя, т.к. есть final
};

int main() {
    Clock* public = new WallClock;
    pClock1->ShowTime();
    return 0;
}

**/
