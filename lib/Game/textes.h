#define START 0
#define CENTER 1
#define END 2

class GAME_TEXT {
protected:
    int img_x = 0;
    int img_y = 0;
    int bx;     //  ширина картинки буквы
    int by;     //  высота картинки буквы
    int* shr;   //  shrifty - изображение шрифтов
    iXY cp;
public:
    virtual int Convert(char a) = 0;
    virtual void say(int x, int y, double razm, double rast, const char* text){  //  int w_type, w_type = write type
        double r_x, r_y;
        int tbx, tby;
        r_x = bx/razm;
        r_y = by/razm;
        tbx = bx * razm/by;
        tby = by * razm/by;
        if(rast >= 0)
            rast = rast*rast;
        else
            rast = -rast*rast;
        int k = 0;
        cp.x = x;
        cp.y = y;
        int* image;
        image = ipixels;
        int n = 0;
        while(text[k] != '\0'){
            if(text[k] != '\n' && text[k] != '\r'){
                n = Convert(text[k]);
                int* temp_t;
                double* temp_z;
                int temp;
                if(n != -1)
                    for(int j = 0; j < tby; j++){
                        for(int i = 0; i < tbx; i++){
                            temp_t = shr + (int)(j*r_y*img_x + bx*n + i*r_x);
                            if(cp.y + j >= 0 && cp.y + j < resolution.vysota && cp.x + i >= 0 && cp.x + i < resolution.shirina){
                                temp = (cp.y + j)*resolution.shirina + cp.x + i;
                                temp_z = z_buffer + temp;
                                if(*((unsigned char*)temp_t + 3) != 0) //  *((unsigned char*)temp_t + 3) == 255
                                    if(rast <= *temp_z){
                                        *temp_z = rast;
                                        image[temp] = *temp_t;
                                    }
                            }
                            else if(cp.x + i >= resolution.shirina && cp.y + j >= 0){
                                cp.y -= tby;
                                cp.x = x;
                            }
                            else break;
                        }
                    }
                cp.x += tbx;
            }
            else{
                cp.y -= tby;
                cp.x = x;
            }
            k++;
        }
    }
    virtual void say(int x, int y, double razm, unsigned char r, unsigned char g, unsigned char b, double rast, const char* text){
        int color;
        int* ad_c = &color;
        *((unsigned char*)ad_c) = b;
        *((unsigned char*)ad_c + 1) = g;
        *((unsigned char*)ad_c + 2) = r;
        *((unsigned char*)ad_c + 3) = 0;
        double r_x, r_y;
        int tbx, tby;
        r_x = bx/razm;
        r_y = by/razm;
        tbx = bx * razm/by;
        tby = by * razm/by;
        if(rast >= 0)
            rast = rast*rast;
        else
            rast = -rast*rast;
        int k = 0;
        cp.x = x;
        cp.y = y;
        int* image;
        image = ipixels;
        int n = 0;
        while(text[k] != '\0'){
            if(text[k] != '\n' && text[k] != '\r'){
                n = Convert(text[k]);
                int* temp_t;
                double* temp_z;
                int temp;
                if(n != -1)
                    for(int j = 0; j < tby; j++){
                        for(int i = 0; i < tbx; i++){
                            temp_t = shr + (int)(j*r_y*img_x + bx*n + i*r_x);
                            if(cp.y + j >= 0 && cp.y + j < resolution.vysota && cp.x + i >= 0 && cp.x + i < resolution.shirina){
                                temp = (cp.y + j)*resolution.shirina + cp.x + i;
                                temp_z = z_buffer + temp;
                                if(*((unsigned char*)temp_t + 3) != 0) //  *((unsigned char*)temp_t + 3) == 255
                                    if(rast <= *temp_z){
                                        *temp_z = rast;
                                        image[temp] = *temp_t + color;
                                    }
                            }
                            else if(cp.x + i >= resolution.shirina && cp.y + j >= 0){
                                cp.y -= tby;
                                cp.x = x;
                            }
                            else break;
                        }
                    }
                cp.x += tbx;
            }
            else{
                cp.y -= tby;
                cp.x = x;
            }
            k++;
        }
    }
    virtual void say(int x, int y, double razm, unsigned char r, unsigned char g, unsigned char b, unsigned char f, double rast, const char* text){
        int color;
        int* ad_c = &color;
        *((unsigned char*)ad_c) = b;
        *((unsigned char*)ad_c + 1) = g;
        *((unsigned char*)ad_c + 2) = r;
        *((unsigned char*)ad_c + 3) = f;
        double r_x, r_y;
        int tbx, tby;
        r_x = bx/razm;
        r_y = by/razm;
        tbx = bx * razm/by;
        tby = by * razm/by;
        if(rast >= 0)
            rast = rast*rast;
        else
            rast = -rast*rast;
        int k = 0;
        cp.x = x;
        cp.y = y;
        int* image;
        image = ipixels;
        int n = 0;
        while(text[k] != '\0'){
            if(text[k] != '\n' && text[k] != '\r'){
                n = Convert(text[k]);
                int* temp_t;
                double* temp_z;
                int temp;
                if(n != -1)
                    for(int j = 0; j < tby; j++){
                        for(int i = 0; i < tbx; i++){
                            temp_t = shr + (int)(j*r_y*img_x + bx*n + i*r_x);
                            if(cp.y + j >= 0 && cp.y + j < resolution.vysota && cp.x + i >= 0 && cp.x + i < resolution.shirina){
                                temp = (cp.y + j)*resolution.shirina + cp.x + i;
                                temp_z = z_buffer + temp;
                                if(*((unsigned char*)temp_t + 3) != 0) //  *((unsigned char*)temp_t + 3) == 255
                                    if(rast <= *temp_z){
                                        *temp_z = rast;
                                        image[temp] = *temp_t + color;
                                    }
                            }
                            else if(cp.x + i >= resolution.shirina && cp.y + j >= 0){
                                cp.y -= tby;
                                cp.x = x;
                            }
                            else break;
                        }
                    }
                cp.x += tbx;
            }
            else{
                cp.y -= tby;
                cp.x = x;
            }
            k++;
        }
    }
    virtual void say(int x, int y, double razm, const char* text){  //  важность = -100
        double r_x, r_y;
        int tbx, tby;
        r_x = bx/razm;
        r_y = by/razm;
        tbx = bx * razm/by;
        tby = by * razm/by;
        int k = 0;
        cp.x = x;
        cp.y = y;
        int* image;
        image = ipixels;
        int n = 0;
        while(text[k] != '\0'){
            if(text[k] != '\n' && text[k] != '\r'){
                n = Convert(text[k]);
                int* temp_t;
                double* temp_z;
                int temp;
                if(n != -1)
                    for(int j = 0; j < tby; j++){
                        for(int i = 0; i < tbx; i++){
                            temp_t = shr + (int)(j*r_y*img_x + bx*n + i*r_x);
                            if(cp.y + j >= 0 && cp.y + j < resolution.vysota && cp.x + i >= 0 && cp.x + i < resolution.shirina){
                                temp = (cp.y + j)*resolution.shirina + cp.x + i;
                                temp_z = z_buffer + temp;
                                if(*((unsigned char*)temp_t + 3) != 0) //  *((unsigned char*)temp_t + 3) == 255
                                    if(-100 <= *temp_z){
                                        *temp_z = -100;
                                        image[temp] = *temp_t;
                                    }
                            }
                            else if(cp.x + i >= resolution.shirina && cp.y + j >= 0){
                                cp.y -= tby;
                                cp.x = x;
                            }
                            else break;
                        }
                    }
                cp.x += tbx;
            }
            else{
                cp.y -= tby;
                cp.x = x;
            }
            k++;
        }
    }
    void operator <<(const char text){
        pixels[resolution.vysota/2*resolution.shirina*4 + resolution.shirina*2] = text;
        pixels[resolution.vysota/2*resolution.shirina*4 + resolution.shirina*2 + 1] = text;
        pixels[resolution.vysota/2*resolution.shirina*4 + resolution.shirina*2 + 2] = text;
    }
};

class TEXT_Eng : public GAME_TEXT {
public:
    TEXT_Eng(){
        unsigned char* t_shr;
        t_shr = loadBMP("data/shrifty/english2.bmp", img_x, img_y);
        shr = (int*)t_shr;
        by = img_y;
        bx = by;    //  img_x / 32
    }
    int Convert(char a){
        switch(a){
            case 'A':
            case 'a':
                return 0;
            case 'B':
            case 'b':
                return 1;
            case 'C':
            case 'c':
                return 2;
            case 'D':
            case 'd':
                return 3;
            case 'E':
            case 'e':
                return 4;
            case 'F':
            case 'f':
                return 5;
            case 'G':
            case 'g':
                return 6;
            case 'H':
            case 'h':
                return 7;
            case 'I':
            case 'i':
                return 8;
            case 'J':
            case 'j':
                return 9;
            case 'K':
            case 'k':
                return 10;
            case 'L':
            case 'l':
                return 11;
            case 'M':
            case 'm':
                return 12;
            case 'N':
            case 'n':
                return 13;
            case 'O':
            case 'o':
                return 14;
            case 'P':
            case 'p':
                return 15;
            case 'Q':
            case 'q':
                return 16;
            case 'R':
            case 'r':
                return 17;
            case 'S':
            case 's':
                return 18;
            case 'T':
            case 't':
                return 19;
            case 'U':
            case 'u':
                return 20;
            case 'V':
            case 'v':
                return 21;
            case 'W':
            case 'w':
                return 22;
            case 'X':
            case 'x':
                return 23;
            case 'Y':
            case 'y':
                return 24;
            case 'Z':
            case 'z':
                return 25;
            case '-':
                return 26;
            case '!':
                return 27;
            case '?':
                return 28;
            case '.':
                return 29;
            case ',':
                return 30;
            case ':':
                return 31;
            default:
                return -1;
        }
    }
};

class TEXT_Rus : public GAME_TEXT {
public:
    TEXT_Rus(){
        unsigned char* t_shr;
        t_shr = loadBMP("data/shrifty/russian.bmp", img_x, img_y);
        shr = (int*)t_shr;
        by = img_y;
        bx = by;
    }
    int Convert(char a){
        switch(a){
            case '0':
                return 0;
            case '1':
                return 1;
            case '2':
                return 2;
            case '3':
                return 3;
            case '4':
                return 4;
            case '5':
                return 5;
            case '6':
                return 6;
            case '7':
                return 7;
            case '8':
                return 8;
            case '9':
                return 9;
            case 'А':
            case 'а':
                return 10;
            case 'Б':
            case 'б':
                return 11;
            case 'В':
            case 'в':
                return 12;
            case 'Г':
            case 'г':
                return 13;
            case 'Д':
            case 'д':
                return 14;
            case 'Е':
            case 'е':
                return 15;
            case 'Ё':
            case 'ё':
                return 16;
            case 'Ж':
            case 'ж':
                return 17;
            case 'З':
            case 'з':
                return 18;
            case 'И':
            case 'и':
                return 19;
            case 'Й':
            case 'й':
                return 20;
            case 'К':
            case 'к':
                return 21;
            case 'Л':
            case 'л':
                return 22;
            case 'М':
            case 'м':
                return 23;
            case 'Н':
            case 'н':
                return 24;
            case 'О':
            case 'о':
                return 25;
            case 'П':
            case 'п':
                return 26;
            case 'Р':
            case 'р':
                return 27;
            case 'С':
            case 'с':
                return 28;
            case 'Т':
            case 'т':
                return 29;
            case 'У':
            case 'у':
                return 30;
            case 'Ф':
            case 'ф':
                return 31;
            case 'Х':
            case 'х':
                return 32;
            case 'Ц':
            case 'ц':
                return 33;
            case 'Ч':
            case 'ч':
                return 34;
            case 'Ш':
            case 'ш':
                return 35;
            case 'Щ':
            case 'щ':
                return 36;
            case 'Ъ':
            case 'ъ':
                return 37;
            case 'Ы':
            case 'ы':
                return 38;
            case 'Ь':
            case 'ь':
                return 39;
            case 'Э':
            case 'э':
                return 40;
            case 'Ю':
            case 'ю':
                return 41;
            case 'Я':
            case 'я':
                return 42;
            case '-':
                return 43;
            case '!':
                return 44;
            case '?':
                return 45;
            case '.':
                return 46;
            case ',':
                return 47;
            case ':':
                return 48;
            case ';':
                return 49;
            case '(':
                return 50;
            case ')':
                return 51;
            case '_':
                return 52;
            case '=':
                return 53;
            case '+':
                return 54;
            case '*':
                return 55;
            case '<':
                return 56;
            case '>':
                return 57;
            case '@':
                return 58;
            case '%':
                return 59;
            case '\'':
                return 60;
            case '"':
                return 61;
            default:
                return -1;
        }
    }
};

class TEXT_BOX : public GAME_TEXT {
private:
    int lx, ly, rx, ry;
    double r_x, r_y;
    int tbx, tby;
    double razm;
    int color;
    int box_color;
    double priority = -100;
    iXY caretka;
    void text_char(const char* text){
        int k = 0;
        int* image;
        image = ipixels;
        int n = 0;
        while(text[k] != '\0'){
            if(text[k] != '\n' && text[k] != '\r'){
                n = Convert(text[k]);
                int* temp_t;
                double* temp_z;
                int temp;
                if(n != -1)
                    for(int j = 0; j < tby; j++){
                        for(int i = 0; i < tbx; i++){
                            temp_t = shr + (int)(j*r_y*img_x + bx*n + i*r_x);
                            if(caretka.y + j >= ry && caretka.y + j < ly && caretka.x + i >= lx && caretka.x + i < rx){
                                temp = (caretka.y + j)*resolution.shirina + caretka.x + i;
                                temp_z = z_buffer + temp;
                                if(*((unsigned char*)temp_t + 3) != 0) //  *((unsigned char*)temp_t + 3) == 255
                                    if(priority <= *temp_z){
                                        *temp_z = priority;
                                        image[temp] = *temp_t + color;
                                    }
                            }
                            else if(caretka.x + i >= lx && caretka.y + j >= ry){
                                caretka.y -= tby;
                                caretka.x = lx;
                            }
                            else break;
                        }
                    }
                caretka.x += tbx;
            }
            else{
                caretka.y -= tby;
                caretka.x = lx;
            }
            k++;
        }
    }
public:
    void TEXT_BOX_init(int lx, int ly, int rx, int ry, double razm, unsigned char r, unsigned char g, unsigned char b, unsigned char f, double priority){
        this -> lx = lx;
        this -> ly = ly;
        this -> rx = rx;
        this -> ry = ry;
        this -> razm = razm;
        int* tcolor = &color;
        *((unsigned char*)tcolor) = b;
        *((unsigned char*)tcolor + 1) = g;
        *((unsigned char*)tcolor + 2) = r;
        *((unsigned char*)tcolor + 3) = f;
        if(priority < 0)
            this -> priority = priority*priority;
        else
            this -> priority = -priority;
        caretka.x = lx;
        caretka.y = ly;
        r_x = bx/razm;
        r_y = by/razm;
        tbx = bx * razm/by;
        tby = by * razm/by;
    }
    void TEXT_BOX_init(int lx, int ly, int rx, int ry, double razm, unsigned char r, unsigned char g, unsigned char b, unsigned char f, unsigned char box_r, unsigned char box_g, unsigned char box_b, unsigned char box_f, double priority){
        this -> lx = lx;
        this -> ly = ly;
        this -> rx = rx;
        this -> ry = ry;
        this -> razm = razm;
        int* tcolor = &color;
        *((unsigned char*)tcolor) = b;
        *((unsigned char*)tcolor + 1) = g;
        *((unsigned char*)tcolor + 2) = r;
        *((unsigned char*)tcolor + 3) = f;
        tcolor = &box_color;
        *((unsigned char*)tcolor) = box_b;
        *((unsigned char*)tcolor + 1) = box_g;
        *((unsigned char*)tcolor + 2) = box_r;
        *((unsigned char*)tcolor + 3) = box_f;
        if(priority < 0)
            this -> priority = priority*priority;
        else
            this -> priority = -priority;
        caretka.x = lx;
        caretka.y = ly;
        r_x = bx/razm;
        r_y = by/razm;
        tbx = bx * razm/by;
        tby = by * razm/by;
    }
    virtual int Convert(char a) = 0;
    void Start_Dialog(){
        caretka.x = lx;
        caretka.y = ly;
    }
    void say(const char* text){
        int k = 0;
        int* image;
        image = ipixels;
        int n = 0;
        while(text[k] != '\0'){
            if(text[k] != '\n' && text[k] != '\r'){
                n = Convert(text[k]);
                int* temp_t;
                double* temp_z;
                int temp;
                if(n != -1)
                    for(int j = 0; j < tby; j++){
                        for(int i = 0; i < tbx; i++){
                            temp_t = shr + (int)(j*r_y*img_x + bx*n + i*r_x);
                            if(caretka.y + j >= ry && caretka.y + j < ly && caretka.x + i >= lx && caretka.x + i < rx){
                                temp = (caretka.y + j)*resolution.shirina + caretka.x + i;
                                temp_z = z_buffer + temp;
                                if(*((unsigned char*)temp_t + 3) != 0) //  *((unsigned char*)temp_t + 3) == 255
                                    if(priority <= *temp_z){
                                        *temp_z = priority;
                                        image[temp] = *temp_t + color;
                                    }
                            }
                            else if(caretka.x + i >= lx && caretka.y + j >= ry){
                                caretka.y -= tby;
                                caretka.x = lx;
                            }
                            else break;
                        }
                    }
                caretka.x += tbx;
            }
            else{
                caretka.y -= tby;
                caretka.x = lx;
            }
            k++;
        }
    }
    void operator <<(double x){
        int k;
        double param = 1000000;
        bool is_first = 1;
        bool was_p = 0;
        char text[64];
        text[0] = 'н';
        text[1] = 'у';
        text[2] = 'л';
        text[3] = 'л';
        text[4] = '\0';
        int i = 0;
        if(x == 0){
            text[0] = '0';
            text[1] = '\0';
        }
        else{
            if(x < 0){
                text[i] = '-';
                i++;
                text[i] = '\0';
                x = -x;
            }
            while(param > 0.000001){
                k = x/param;
                x -= k*param;
                param /= 10;
                if(is_first == 1 && k == 0){
                    if(param < 1 && was_p == 0){
                        if(x - (int)x >= 0.000001){
                            text[i] = '0';
                            i++;
                            text[i] = '.';
                            i++;
                            text[i] = '\0';
                            is_first = 0;
                            was_p = 1;
                        }
                        else
                            break;
                    }
                    continue;
                }
                else
                    is_first = 0;
                text[i] = (char)k + 48;
                i++;
                text[i] = '\0';
                if(param == 0.1 && was_p == 0 && x >= 0.000001){
                    text[i] = '.';
                    i++;
                    text[i] = '\0';
                    was_p = 1;
                }
                else if(x < 0.000001)
                    break;
            }
        }
        text_char(text);
    }
    void operator <<(const char* text){
        int k = 0;
        int* image;
        image = ipixels;
        int n = 0;
        while(text[k] != '\0'){
            if(text[k] != '\n' && text[k] != '\r'){
                n = Convert(text[k]);
                int* temp_t;
                double* temp_z;
                int temp;
                if(n != -1)
                    for(int j = 0; j < tby; j++){
                        for(int i = 0; i < tbx; i++){
                            temp_t = shr + (int)(j*r_y*img_x + bx*n + i*r_x);
                            if(caretka.y + j >= ry && caretka.y + j < ly && caretka.x + i >= lx && caretka.x + i < rx){
                                temp = (caretka.y + j)*resolution.shirina + caretka.x + i;
                                temp_z = z_buffer + temp;
                                if(*((unsigned char*)temp_t + 3) != 0) //  *((unsigned char*)temp_t + 3) == 255
                                    if(priority <= *temp_z){
                                        *temp_z = priority;
                                        image[temp] = *temp_t + color;
                                    }
                            }
                            else if(caretka.x + i >= lx && caretka.y + j >= ry){
                                caretka.y -= tby;
                                caretka.x = lx;
                            }
                            else break;
                        }
                    }
                caretka.x += tbx;
            }
            else{
                caretka.y -= tby;
                caretka.x = lx;
            }
            k++;
        }
    }
    void say_in_box(const char* text){      /// вывести текст в данном боксе
        unsigned char br, bg, bb, bf;
        double f, of;
        int* tcolor = &box_color;
        bb = *((unsigned char*)tcolor);
        bg = *((unsigned char*)tcolor + 1);
        br = *((unsigned char*)tcolor + 2);
        bf = *((unsigned char*)tcolor + 3);
        f = (double)bf/255;
        of = 1 - f;
        for(int j = ry; j < ly; j++){
            for(int i = lx; i < rx; i++){
                pixels[j*resolution.shirina*4 + i*4] = pixels[j*resolution.shirina*4 + i*4]*of + bb*f;
                pixels[j*resolution.shirina*4 + i*4 + 1] = pixels[j*resolution.shirina*4 + i*4 + 1]*of + bg*f;
                pixels[j*resolution.shirina*4 + i*4 + 2] = pixels[j*resolution.shirina*4 + i*4 + 2]*of + br*f;
            }
        }
        say(text);
    }
    void operator ==(const double invizible_param){     /// ортисовать диалоговый бокс с прозрачностью от 0 до 1
        unsigned char br, bg, bb;
        double of;
        int* tcolor = &box_color;
        bb = *((unsigned char*)tcolor);
        bg = *((unsigned char*)tcolor + 1);
        br = *((unsigned char*)tcolor + 2);
        of = 1 - invizible_param;
        for(int j = ry; j < ly; j++){
            for(int i = lx; i < rx; i++){
                pixels[j*resolution.shirina*4 + i*4] = pixels[j*resolution.shirina*4 + i*4]*of + bb*invizible_param;
                pixels[j*resolution.shirina*4 + i*4 + 1] = pixels[j*resolution.shirina*4 + i*4 + 1]*of + bg*invizible_param;
                pixels[j*resolution.shirina*4 + i*4 + 2] = pixels[j*resolution.shirina*4 + i*4 + 2]*of + br*invizible_param;
            }
        }
    }
};

class TEXT_BOX_Eng : public TEXT_BOX {
public:
    TEXT_BOX_Eng(int lx, int ly, int rx, int ry, double razm, unsigned char r, unsigned char g, unsigned char b, unsigned char f, double priority){
        unsigned char* t_shr;
        t_shr = loadBMP("data/shrifty/english3.bmp", img_x, img_y);
        shr = (int*)t_shr;
        by = img_y;
        bx = by;    //  img_x / 32
        TEXT_BOX_init(lx, ly, rx, ry, razm, r, g, b, f, priority);
    }
    TEXT_BOX_Eng(int lx, int ly, int rx, int ry, double razm, unsigned char r, unsigned char g, unsigned char b, unsigned char f, unsigned char box_r, unsigned char box_g, unsigned char box_b, unsigned char box_f, double priority){
        unsigned char* t_shr;
        t_shr = loadBMP("data/shrifty/english3.bmp", img_x, img_y);
        shr = (int*)t_shr;
        by = img_y;
        bx = by;    //  img_x / 32
        TEXT_BOX_init(lx, ly, rx, ry, razm, r, g, b, f, box_r, box_g, box_b, box_f, priority);
    }
    int Convert(char a){
        switch(a){
            case '0':
                return 0;
            case '1':
                return 1;
            case '2':
                return 2;
            case '3':
                return 3;
            case '4':
                return 4;
            case '5':
                return 5;
            case '6':
                return 6;
            case '7':
                return 7;
            case '8':
                return 8;
            case '9':
                return 9;
            case 'A':
            case 'a':
                return 10;
            case 'B':
            case 'b':
                return 11;
            case 'C':
            case 'c':
                return 12;
            case 'D':
            case 'd':
                return 13;
            case 'E':
            case 'e':
                return 14;
            case 'F':
            case 'f':
                return 15;
            case 'G':
            case 'g':
                return 16;
            case 'H':
            case 'h':
                return 17;
            case 'I':
            case 'i':
                return 18;
            case 'J':
            case 'j':
                return 19;
            case 'K':
            case 'k':
                return 20;
            case 'L':
            case 'l':
                return 21;
            case 'M':
            case 'm':
                return 22;
            case 'N':
            case 'n':
                return 23;
            case 'O':
            case 'o':
                return 24;
            case 'P':
            case 'p':
                return 25;
            case 'Q':
            case 'q':
                return 26;
            case 'R':
            case 'r':
                return 27;
            case 'S':
            case 's':
                return 28;
            case 'T':
            case 't':
                return 29;
            case 'U':
            case 'u':
                return 30;
            case 'V':
            case 'v':
                return 31;
            case 'W':
            case 'w':
                return 32;
            case 'X':
            case 'x':
                return 33;
            case 'Y':
            case 'y':
                return 34;
            case 'Z':
            case 'z':
                return 35;
            case '-':
                return 36;
            case '!':
                return 37;
            case '?':
                return 38;
            case '.':
                return 39;
            case ',':
                return 40;
            case ':':
                return 41;
            case ';':
                return 42;
            case '(':
                return 43;
            case ')':
                return 44;
            case '_':
                return 45;
            case '=':
                return 46;
            case '+':
                return 47;
            case '*':
                return 48;
            case '<':
                return 49;
            case '>':
                return 50;
            case '@':
                return 51;
            case '%':
                return 52;
            case '\'':
                return 53;
            case '"':
                return 54;
            default:
                return -1;
        }
    }
};

class TEXT_BOX_Rus : public TEXT_BOX {
public:
    TEXT_BOX_Rus(int lx, int ly, int rx, int ry, double razm, unsigned char r, unsigned char g, unsigned char b, unsigned char f, double priority){
        unsigned char* t_shr;
        t_shr = loadBMP("data/shrifty/russian.bmp", img_x, img_y);
        shr = (int*)t_shr;
        by = img_y;
        bx = by;
        TEXT_BOX_init(lx, ly, rx, ry, razm, r, g, b, f, priority);
    }
    TEXT_BOX_Rus(int lx, int ly, int rx, int ry, double razm, unsigned char r, unsigned char g, unsigned char b, unsigned char f, unsigned char box_r, unsigned char box_g, unsigned char box_b, unsigned char box_f, double priority){
        unsigned char* t_shr;
        t_shr = loadBMP("data/shrifty/russian.bmp", img_x, img_y);
        shr = (int*)t_shr;
        by = img_y;
        bx = by;
        TEXT_BOX_init(lx, ly, rx, ry, razm, r, g, b, f, box_r, box_g, box_b, box_f, priority);
    }
    int Convert(char a){
        switch(a){
            case '0':
                return 0;
            case '1':
                return 1;
            case '2':
                return 2;
            case '3':
                return 3;
            case '4':
                return 4;
            case '5':
                return 5;
            case '6':
                return 6;
            case '7':
                return 7;
            case '8':
                return 8;
            case '9':
                return 9;
            case 'А':
            case 'а':
                return 10;
            case 'Б':
            case 'б':
                return 11;
            case 'В':
            case 'в':
                return 12;
            case 'Г':
            case 'г':
                return 13;
            case 'Д':
            case 'д':
                return 14;
            case 'Е':
            case 'е':
                return 15;
            case 'Ё':
            case 'ё':
                return 16;
            case 'Ж':
            case 'ж':
                return 17;
            case 'З':
            case 'з':
                return 18;
            case 'И':
            case 'и':
                return 19;
            case 'Й':
            case 'й':
                return 20;
            case 'К':
            case 'к':
                return 21;
            case 'Л':
            case 'л':
                return 22;
            case 'М':
            case 'м':
                return 23;
            case 'Н':
            case 'н':
                return 24;
            case 'О':
            case 'о':
                return 25;
            case 'П':
            case 'п':
                return 26;
            case 'Р':
            case 'р':
                return 27;
            case 'С':
            case 'с':
                return 28;
            case 'Т':
            case 'т':
                return 29;
            case 'У':
            case 'у':
                return 30;
            case 'Ф':
            case 'ф':
                return 31;
            case 'Х':
            case 'х':
                return 32;
            case 'Ц':
            case 'ц':
                return 33;
            case 'Ч':
            case 'ч':
                return 34;
            case 'Ш':
            case 'ш':
                return 35;
            case 'Щ':
            case 'щ':
                return 36;
            case 'Ъ':
            case 'ъ':
                return 37;
            case 'Ы':
            case 'ы':
                return 38;
            case 'Ь':
            case 'ь':
                return 39;
            case 'Э':
            case 'э':
                return 40;
            case 'Ю':
            case 'ю':
                return 41;
            case 'Я':
            case 'я':
                return 42;
            case '-':
                return 43;
            case '!':
                return 44;
            case '?':
                return 45;
            case '.':
                return 46;
            case ',':
                return 47;
            case ':':
                return 48;
            case ';':
                return 49;
            case '(':
                return 50;
            case ')':
                return 51;
            case '_':
                return 52;
            case '=':
                return 53;
            case '+':
                return 54;
            case '*':
                return 55;
            case '<':
                return 56;
            case '>':
                return 57;
            case '@':
                return 58;
            case '%':
                return 59;
            case '\'':
                return 60;
            case '"':
                return 61;
            default:
                return -1;
        }
    }
};

TEXT_Eng eng;
TEXT_Rus rus;
TEXT_BOX_Rus rtx(30, 758, 330, 458, 16, 255, 0, 0, 0, 30, 100, 10, 100, 10);
TEXT_BOX_Eng etx(30, 758, 1330, 458, 16, 255, 0, 0, 0, 30, 100, 10, 100, 10);
