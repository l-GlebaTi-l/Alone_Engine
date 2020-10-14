/**
int Draw_Edge(XY a, XY b, XY c)
{
    if(a.y < b.y){          /// простая перестановка вершин в нужный порядок
        if(b.y < c.y){
            XY t;
            t = a;
            a = c;
            c = t;
        }
        else{
            if(a.y < c.y){
                XY t;
                t = a;
                a = b;
                b = c;
                c = t;
            }
            else{
                XY t;
                t = a;
                a = b;
                b = t;
            }
        }
    }
    else{
        if(a.y > c.y){
            if(b.y < c.y){
                XY t;
                t = b;
                b = c;
                c = t;
            }
        }
        else{
            XY t;
            t = a;
            a = c;
            c = b;
            b = t;
        }
    }

    double abx, acx, bcx;
    double tl, tr; // temp left, temp right, temp bc
    double ost;
    iXY ipix;

    abx = (b.x - a.x) / (a.y - b.y);

    acx = (c.x - a.x) / (a.y - c.y);

    bcx = (c.x - b.x) / (b.y - c.y);

    ost = a.y - (int)a.y;
    if(ost < 0)
        ost *= -1;
    ipix.y = a.y;
//    tabx = a.x + (abx*ost);
//    tab.y = a.y + (ab.y*ost);
//    tacx = a.x + (acx*ost);
//    tac.y = a.y + (ac.y*ost);

    XY pac;
    pac.x = c.y - a.y;
    pac.y = a.x - c.x;

    if(ipix.y > c.y){
        while(ipix.y > resolution.vysota){
            ipix.y--;
            ipix.x += acx;
            tl += abx;
            tr += acx;
        }
        if(((b.x - a.x)*pac.x + (b.y - a.y)*pac.y) >= 0){  /// ЕСЛИ b СЛЕВА ОТ ac
            tl = a.x + (abx*ost);
            tr = a.x + (acx*ost);
            ipix.x = a.x + tl - 2;

            while(ipix.x < tl){
                ipix.x++;
            }
            while(ipix.x < tr){
                            if(ipix.x > resolution.shirina){
                                ipix.x = resolution.shirina;
                                break;
                            }
                pixels[resolution.shirina*ipix.y*4 + ipix.x*4] = 150;
                pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 1] = 0;
                pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 2] = 0;
                pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 3] = 0;
                ipix.x++;
            }
            ipix.x += acx + 2;
            if(ipix.x > resolution.shirina)
                ipix.x = resolution.shirina;
            if(ipix.x < 0)
                ipix.x = 0;
            ipix.y--;
            tl += abx;
            tr += acx;
            for(int i = 0; i < 2; i++){
                while(ipix.y > b.y && ipix.y > 0){
                    if(ipix.x > tr){
                        ipix.x--;
                        while(ipix.x > tr){
                            ipix.x--;
                        }
                        while(ipix.x > tl){
                            if(ipix.x < 0){
                                ipix.x = 0;
                                break;
                            }
    //                        cout << " x=" << ipix.x << " y=" << ipix.y;
                            pixels[resolution.shirina*ipix.y*4 + ipix.x*4] = 150;
                            pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 1] = 0;
                            pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 2] = 0;
                            pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 3] = 0;
                            ipix.x--;
                        }
                        ipix.x += abx - 2;
            if(ipix.x > resolution.shirina)
                ipix.x = resolution.shirina;
            if(ipix.x < 0)
                ipix.x = 0;
                        ipix.y--;
                        tl += abx;
                        tr += acx;
                    }
                    else if(ipix.x < tl){
                        ipix.x++;
                        while(ipix.x < tl){
                            ipix.x++;
                        }
                        while(ipix.x < tr){
                            if(ipix.x > resolution.shirina){
                                ipix.x = resolution.shirina;
                                break;
                            }
    //                        cout << " x=" << ipix.x << " y=" << ipix.y;
                            pixels[resolution.shirina*ipix.y*4 + ipix.x*4] = 150;
                            pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 1] = 0;
                            pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 2] = 0;
                            pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 3] = 0;
                            ipix.x++;
                        }
                        ipix.x += acx + 2;
            if(ipix.x > resolution.shirina)
                ipix.x = resolution.shirina;
            if(ipix.x < 0)
                ipix.x = 0;
                        ipix.y--;
                        tl += abx;
                        tr += acx;
                    }
                    else return 4;
                }
                if(ipix.y > c.y){
                    ost = b.y - (int)b.y;
                    if(ost < 0)
                        ost *= -1;
                    tl = b.x + (bcx*ost);
                    b.y = c.y;
                    abx = bcx;
                }
                else break;
            }
        }
        else{               /// ЕСЛИ b СПРАВА ОТ ac
            tr = a.x + (abx*ost);
            tl = a.x + (acx*ost);
            ipix.x = a.x + tl - 2;
            while(ipix.x < tl){
                ipix.x++;
            }
            while(ipix.x < tr){
                            if(ipix.x > resolution.shirina){
                                ipix.x = resolution.shirina;
                                break;
                            }
                pixels[resolution.shirina*ipix.y*4 + ipix.x*4] = 150;
                pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 1] = 0;
                pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 2] = 0;
                pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 3] = 0;
                ipix.x++;
            }
            ipix.x += abx + 2;
            ipix.y--;
            tr += abx;
            tl += acx;
            for(int i = 0; i < 2; i++){
                while(ipix.y > b.y && ipix.y > 0){
                    if(ipix.x > tr){
                        ipix.x--;
                        while(ipix.x > tr){
                            ipix.x--;
                        }
                        while(ipix.x > tl){
                            if(ipix.x < 0){
                                ipix.x = 0;
                                break;
                            }
    //                        cout << " x=" << ipix.x << " y=" << ipix.y;
                            pixels[resolution.shirina*ipix.y*4 + ipix.x*4] = 150;
                            pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 1] = 0;
                            pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 2] = 0;
                            pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 3] = 0;
                            ipix.x--;
                        }
                        ipix.x += acx - 2;
                        ipix.y--;
                        tr += abx;
                        tl += acx;
                    }
                    else if(ipix.x < tl){
                        ipix.x++;
                        while(ipix.x < tl){
                            ipix.x++;
                        }
                        while(ipix.x < tr){
                            if(ipix.x > resolution.shirina){
                                ipix.x = resolution.shirina;
                                break;
                            }
    //                        cout << " x=" << ipix.x << " y=" << ipix.y;
                            pixels[resolution.shirina*ipix.y*4 + ipix.x*4] = 150;
                            pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 1] = 0;
                            pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 2] = 0;
                            pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 3] = 0;
                            ipix.x++;
                        }
                        ipix.x += abx + 2;
                        ipix.y--;
                        tr += abx;
                        tl += acx;
                    }
                    else return 4;
                }
                if(ipix.y > c.y){
                    if(ipix.y < 0)
                        return 5;   // вышел за нижнюю границу экрана
                    ost = b.y - (int)b.y;
                    if(ost < 0)
                        ost *= -1;
                    tr = b.x + (bcx*ost);
                    b.y = c.y;
                    abx = bcx;
                }
                else break;
            }
        }
    }
    else return 2;  /// не рисовать (перенести проверку в начало функции либо вообще до её вызова)
    return 3;
}

bool image_defolt()
{
    for(int i = 0; i < resolution.vysota - 1; i++){
        for(int j = 0; j < resolution.shirina - 1; j++){
            pixels[resolution.shirina*i*4 + j*4] = 100;
            pixels[resolution.shirina*i*4 + j*4 + 1] = 100;
            pixels[resolution.shirina*i*4 + j*4 + 2] = 100;
            pixels[resolution.shirina*i*4 + j*4 + 3] = 0;
        }
    }
    return 0;
}

bool Povorot()
{
    image_defolt();
    XY Center;
    Center.x = resolution.shirina / 2;
    Center.y = resolution.vysota / 2;
    XY CA, CB, CC;
    XY RA, RB, RC;
    CA.x = A.x - Center.x;
    CA.y = A.y - Center.y;
    CB.x = B.x - Center.x;
    CB.y = B.y - Center.y;
    CC.x = C.x - Center.x;
    CC.y = C.y - Center.y;

    RA.x = -CA.y;
    RA.y = CA.x;
    double l = 40;
    l = 1 / l;
//    l = SqrtInvE(RA.x*RA.x + RA.y*RA.y);
    RA.x *= l;
    RA.y *= l;

    RB.x = -CB.y;
    RB.y = CB.x;
//    l = SqrtInvE(RB.x*RB.x + RB.y*RB.y);
    RB.x *= l;
    RB.y *= l;

    RC.x = -CC.y;
    RC.y = CC.x;
//    l = SqrtInvE(RC.x*RC.x + RC.y*RC.y);
    RC.x *= l;
    RC.y *= l;

    A.x += RA.x;
    A.y += RA.y;
    B.x += RB.x;
    B.y += RB.y;
    C.x += RC.x;
    C.y += RC.y;
    Draw_Edge(A, B, C);
    return 0;
}

**/
/*
int Draw_Edge(XY a, XY b, XY c)
{
    if(a.y < b.y){          /// простая перестановка вершин в нужный порядок
        if(b.y < c.y){
            XY t;
            t = a;
            a = c;
            c = t;
        }
        else{
            if(a.y < c.y){
                XY t;
                t = a;
                a = b;
                b = c;
                c = t;
            }
            else{
                XY t;
                t = a;
                a = b;
                b = t;
            }
        }
    }
    else{
        if(a.y > c.y){
            if(b.y < c.y){
                XY t;
                t = b;
                b = c;
                c = t;
            }
        }
        else{
            XY t;
            t = a;
            a = c;
            c = b;
            b = t;
        }
    }

    double abx, acx, bcx;
    double tl, tr; // temp left, temp right, temp bc
    double ost;
    iXY ipix;

    abx = (b.x - a.x) / (a.y - b.y);

    acx = (c.x - a.x) / (a.y - c.y);

    bcx = (c.x - b.x) / (b.y - c.y);

    ost = a.y - (int)a.y;
    if(ost < 0)
        ost *= -1;
    ipix.y = a.y;
//    tabx = a.x + (abx*ost);
//    tab.y = a.y + (ab.y*ost);
//    tacx = a.x + (acx*ost);
//    tac.y = a.y + (ac.y*ost);

    XY pac;
    pac.x = c.y - a.y;
    pac.y = a.x - c.x;

    if(ipix.y > c.y){
        if(((b.x - a.x)*pac.x + (b.y - a.y)*pac.y) >= 0){  /// ЕСЛИ b СЛЕВА ОТ ac
            tl = a.x + (abx*ost);
            tr = a.x + (acx*ost);
            ipix.x = a.x + tl - 2;

            while(ipix.x < tl){
                ipix.x++;
            }
            while(ipix.x < tr){
                if(ipix.x > 0 && ipix.x < resolution.shirina && ipix.y > 0 && ipix.y < resolution.vysota){
                    pixels[resolution.shirina*ipix.y*4 + ipix.x*4] = 150;
                    pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 1] = 0;
                    pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 2] = 0;
                    pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 3] = 0;
                }
                ipix.x++;
            }
            ipix.x += acx + 2;
            ipix.y--;
            tl += abx;
            tr += acx;
            for(int i = 0; i < 2; i++){
                while(ipix.y > b.y){
                    if(ipix.x > tr){
                        ipix.x--;
                        while(ipix.x > tr){
                            ipix.x--;
                        }
                        while(ipix.x > tl){
    //                        cout << " x=" << ipix.x << " y=" << ipix.y;
                            if(ipix.x > 0 && ipix.x < resolution.shirina && ipix.y > 0 && ipix.y < resolution.vysota){
                                pixels[resolution.shirina*ipix.y*4 + ipix.x*4] = 150;
                                pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 1] = 0;
                                pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 2] = 0;
                                pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 3] = 0;
                            }
                            ipix.x--;
                        }
                        ipix.x += abx - 2;
                        ipix.y--;
                        tl += abx;
                        tr += acx;
                    }
                    else if(ipix.x < tl){
                        ipix.x++;
                        while(ipix.x < tl){
                            ipix.x++;
                        }
                        while(ipix.x < tr){
    //                        cout << " x=" << ipix.x << " y=" << ipix.y;
                            if(ipix.x > 0 && ipix.x < resolution.shirina && ipix.y > 0 && ipix.y < resolution.vysota){
                                pixels[resolution.shirina*ipix.y*4 + ipix.x*4] = 150;
                                pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 1] = 0;
                                pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 2] = 0;
                                pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 3] = 0;
                            }
                            ipix.x++;
                        }
                        ipix.x += acx + 2;
                        ipix.y--;
                        tl += abx;
                        tr += acx;
                    }
                    else return 4;
                }
                if(ipix.y > c.y){
                    ost = b.y - (int)b.y;
                    if(ost < 0)
                        ost *= -1;
                    tl = b.x + (bcx*ost);
                    b.y = c.y;
                    abx = bcx;
                }
                else break;
            }
        }
        else{               /// ЕСЛИ b СПРАВА ОТ ac
            tr = a.x + (abx*ost);
            tl = a.x + (acx*ost);
            ipix.x = a.x + tl - 2;
            while(ipix.x < tl){
                ipix.x++;
            }
            while(ipix.x < tr){
                if(ipix.x > 0 && ipix.x < resolution.shirina && ipix.y > 0 && ipix.y < resolution.vysota){
                    pixels[resolution.shirina*ipix.y*4 + ipix.x*4] = 150;
                    pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 1] = 0;
                    pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 2] = 0;
                    pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 3] = 0;
                }
                ipix.x++;
            }
            ipix.x += abx + 2;
            ipix.y--;
            tr += abx;
            tl += acx;
            for(int i = 0; i < 2; i++){
                while(ipix.y > b.y){
                    if(ipix.x > tr){
                        ipix.x--;
                        while(ipix.x > tr){
                            ipix.x--;
                        }
                        while(ipix.x > tl){
    //                        cout << " x=" << ipix.x << " y=" << ipix.y;
                            if(ipix.x > 0 && ipix.x < resolution.shirina && ipix.y > 0 && ipix.y < resolution.vysota){
                                pixels[resolution.shirina*ipix.y*4 + ipix.x*4] = 150;
                                pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 1] = 0;
                                pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 2] = 0;
                                pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 3] = 0;
                            }
                            ipix.x--;
                        }
                        ipix.x += acx - 2;
                        ipix.y--;
                        tr += abx;
                        tl += acx;
                    }
                    else if(ipix.x < tl){
                        ipix.x++;
                        while(ipix.x < tl){
                            ipix.x++;
                        }
                        while(ipix.x < tr){
    //                        cout << " x=" << ipix.x << " y=" << ipix.y;
                            if(ipix.x > 0 && ipix.x < resolution.shirina && ipix.y > 0 && ipix.y < resolution.vysota){
                                pixels[resolution.shirina*ipix.y*4 + ipix.x*4] = 150;
                                pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 1] = 0;
                                pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 2] = 0;
                                pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 3] = 0;
                            }
                            ipix.x++;
                        }
                        ipix.x += abx + 2;
                        ipix.y--;
                        tr += abx;
                        tl += acx;
                    }
                    else return 4;
                }
                if(ipix.y > c.y){
                    ost = b.y - (int)b.y;
                    if(ost < 0)
                        ost *= -1;
                    tr = b.x + (bcx*ost);
                    b.y = c.y;
                    abx = bcx;
                }
                else break;
            }
        }
    }
    else return 2;  /// не рисовать (перенести проверку в начало функции либо вообще до её вызова)
    return 3;
}

bool image_defolt()
{
    for(int i = 0; i < resolution.vysota - 1; i++){
        for(int j = 0; j < resolution.shirina - 1; j++){
            pixels[resolution.shirina*i*4 + j*4] = 100;
            pixels[resolution.shirina*i*4 + j*4 + 1] = 100;
            pixels[resolution.shirina*i*4 + j*4 + 2] = 100;
            pixels[resolution.shirina*i*4 + j*4 + 3] = 0;
        }
    }
    return 0;
}

bool Povorot()
{
    image_defolt();
    XY Center;
    Center.x = resolution.shirina / 2;
    Center.y = resolution.vysota / 2;
    XY CA, CB, CC;
    XY RA, RB, RC;
    CA.x = A.x - Center.x;
    CA.y = A.y - Center.y;
    CB.x = B.x - Center.x;
    CB.y = B.y - Center.y;
    CC.x = C.x - Center.x;
    CC.y = C.y - Center.y;

    RA.x = -CA.y;
    RA.y = CA.x;
    double l = 40;
    l = 1 / l;
//    l = SqrtInvE(RA.x*RA.x + RA.y*RA.y);
    RA.x *= l;
    RA.y *= l;

    RB.x = -CB.y;
    RB.y = CB.x;
//    l = SqrtInvE(RB.x*RB.x + RB.y*RB.y);
    RB.x *= l;
    RB.y *= l;

    RC.x = -CC.y;
    RC.y = CC.x;
//    l = SqrtInvE(RC.x*RC.x + RC.y*RC.y);
    RC.x *= l;
    RC.y *= l;

    A.x += RA.x;
    A.y += RA.y;
    B.x += RB.x;
    B.y += RB.y;
    C.x += RC.x;
    C.y += RC.y;
    Draw_Edge(A, B, C);
    return 0;
}
*/
/**

int Draw_Textured_Edge(LPVOID param, int *texture, int texture_shirina, int texture_vysota, double l)
{
    double* P = (double*)param;
    double a_x = *P++
    , a_y = *P++
    , b_x = *P++
    , b_y = *P++
    , c_x = *P++
    , c_y = *P++
    , ta_x = *P++
    , ta_y = *P++
    , tb_x = *P++
    , tb_y = *P++
    , tc_x = *P++
    , tc_y = *P++
    ;
    if(a_y < b_y){          /// простая перестановка вершин в нужный порядок
        if(b_y < c_y){
            double t;
            t = a_x;
            a_x = c_x;
            c_x = t;
            t = a_y;
            a_y = c_y;
            c_y = t;

            t = ta_x;
            ta_x = tc_x;
            tc_x = t;
            t = ta_y;
            ta_y = tc_y;
            tc_y = t;
        }
        else{
            if(a_y < c_y){
                double t;
                t = a_x;
                a_x = b_x;
                b_x = c_x;
                c_x = t;

                t = a_y;
                a_y = b_y;
                b_y = c_y;
                c_y = t;

                t = ta_x;
                ta_x = tb_x;
                tb_x = tc_x;
                tc_x = t;

                t = ta_y;
                ta_y = tb_y;
                tb_y = tc_y;
                tc_y = t;
            }
            else{///
                double t;
                t = a_x;
                a_x = b_x;
                b_x = t;

                t = ta_x;
                ta_x = tb_x;
                tb_x = t;

                t = a_y;
                a_y = b_y;
                b_y = t;

                t = ta_y;
                ta_y = tb_y;
                tb_y = t;
            }
        }
    }
    else{
        if(a_y > c_y){
            if(b_y < c_y){
                double t;
                t = b_x;
                b_x = c_x;
                c_x = t;

                t = tb_x;
                tb_x = tc_x;
                tc_x = t;

                t = b_y;
                b_y = c_y;
                c_y = t;

                t = tb_y;
                tb_y = tc_y;
                tc_y = t;
            }
        }
        else{
            double t;
            t = a_x;
            a_x = c_x;
            c_x = b_x;
            b_x = t;

            t = ta_x;
            ta_x = tc_x;
            tc_x = tb_x;
            tb_x = t;

            t = a_y;
            a_y = c_y;
            c_y = b_y;
            b_y = t;

            t = ta_y;
            ta_y = tc_y;
            tc_y = tb_y;
            tb_y = t;
        }
    }

    double abx, acx, bcx;
    double tl, tr; // temp left, temp right, temp bc
    double ost;

    if((int)a_y - (int)b_y < 1)
        abx = (b_x - a_x);
    else
        abx = (b_x - a_x) / (a_y - b_y);

    if((int)a_y - (int)c_y < 1)
        acx = (c_x - a_x);
    else
        acx = (c_x - a_x) / (a_y - c_y);

    if((int)b_y - (int)c_y < 1)
        bcx = (c_x - b_x);
    else
        bcx = (c_x - b_x) / (b_y - c_y);

    ost = a_y - (int)a_y;
    if(ost < 0)
        ost *= -1;



    XY ad, tad, ab, tab, ac, tac, db, tdb;
    double oldb, olac_y;
    XY tp;

//    ab = b - a;
    ab.x = b_x - a_x;
    ab.y = b_y - a_y;

//    ac = c - a;
    ac.x = c_x - a_x;
    ac.y = c_y - a_y;

//    tab = tb - ta;
    tab.x = tb_x - ta_x;
    tab.y = tb_y - ta_y;

//    tac = tc - ta;
    tac.x = tc_x - ta_x;
    tac.y = tc_y - ta_y;

//    ad = (ac/ac.y)*(ab.y)
    ad.x = (ac.x/ac.y)*(ab.y);
    ad.y = ab.y;

//    tad.x = (tac.x/tac.y)*(tab.y);
//    tad.y = (tac.y/tac.y)*(tab.y);
///    tad = (tac / |ac|) * |ad|
    double temp;
    temp = SqrtInvE((ac.x*ac.x + ac.y*ac.y)/(ad.x*ad.x + ad.y*ad.y));
    tad.x = tac.x * temp;
    tad.y = tac.y * temp;

//    db = ab - ad;
    db.x = ab.x - ad.x;
//    db.y = ab.y - ad.y;

    tdb.x = tab.x - tad.x;
    tdb.y = tab.y - tad.y;

//////    ldb = |db|;
////    ldb = SqrtInv(db.x*db.x + db.y*db.y);
//    ldb = db.x;
//    oldb = 1/ldb;
    oldb = 1/db.x;
    if(oldb < 0)
        oldb = -oldb;

//    lac = SqrtInv(ac.x*ac.x + ac.y*ac.y);
//    olac = 1/lac;

    olac_y = 1/ac.y;
    if(olac_y < 0)
        olac_y = -olac_y;

    double fx = (tac.x*olac_y)*(texture_shirina)
    , fy = (tac.y*olac_y)*(texture_vysota)
    , fd = (tdb.x*oldb)*(texture_shirina)
    , fb = (tdb.y*oldb)*(texture_vysota);
    XY ta_r;
    ta_r.x = ta_x * (texture_shirina);
    ta_r.y = ta_y * (texture_vysota);

    int nxl, nxr, nyv, nyn; /// nxleft, nxright, nxverh, nxniz
    int *temp_p;
//    int *temp_pp;
//                temp_pp = (int*)pixels + resolution.shirina*nyv;
//                    temp_p = temp_pp + nxl;
//                    temp_pp -= resolution.shirina;
    double *temp_z;

    if(((b_x - a_x)*(c_y - a_y) + (b_y - a_y)*(a_x - c_x)) >= 0){    /// левый случай (b слева от ac)
        if(a_y > 0){                            /// ПРОВЕРИТЬ, не будет ли ошибок при a_y >= 0, иначе теряются пиклеси в предельно редких случаях
            if(b_y < resolution.vysota - 1){
                tr = a_x + (acx*ost);
                tl = a_x + (abx*ost);
                if(a_y >= resolution.vysota){
                    tr += acx * ((int)a_y - resolution.vysota + 1);
                    tl += abx * ((int)a_y - resolution.vysota + 1);
                    nyv = resolution.vysota - 1;
                }
                else
                    nyv = a_y;
                if(b_y >= 0)
                    nyn = b_y + 1;
                else
                    nyn = 0;
                for(int j = nyv; j >= nyn; j--){
                    if(tl <= 0)                         /// ЕСТЬ ШАНС ОШИБКИ, поставить tl < 0 в случае обнаружения проблем
                        nxl = 0;
                    else if(tl >= resolution.shirina - 1){
                        tr += acx;
                        tl += abx;
                        continue; // эту строчку
                    }
    //                else if(tl == resolution.shirina)
    //                    nxl = resolution.shirina - 1;
                    else
                        nxl = tl + 1;
                    if(tr >= resolution.shirina)
                        nxr = resolution.shirina - 1;
                    else if(tr < 0){
                        tr += acx;
                        tl += abx;
                        continue;
                    }
                    else
                        nxr = tr;
                    temp_p = (int*)pixels + resolution.shirina*j + nxl;

                    tp.x = ta_r.x + fx*(a_y - j) + fd*(tr - nxl);
                    tp.y = ta_r.y + fy*(a_y - j) + fb*(tr - nxl);

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = *(texture + ((int)tp.y)*texture_shirina + (int)tp.x);
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        tp.x -= fd;
                        tp.y -= fb;
                    }
                    tr += acx;
                    tl += abx;
                }
                if(nyn == 0)
                    return 7;
                nyv = nyn - 1;
                if(c_y > 0)
                    nyn = c_y + 1;
                else
                    nyn = 0;
                ost = b_y - (int)b_y;
                if(ost < 0)
                    ost *= -1;
                tl = b_x + (bcx*ost);
                for(int j = nyv; j >= nyn; j--){
                    if(tl <= 0)                         /// ЕСТЬ ШАНС ОШИБКИ, поставить tl < 0 в случае обнаружения проблем
                        nxl = 0;
                    else if(tl >= resolution.shirina - 1){
                        tr += acx;
                        tl += bcx;
                        continue; // эту строчку
                    }
    //                else if(tl == resolution.shirina)
    //                    nxl = resolution.shirina - 1;
                    else
                        nxl = tl + 1;
                    if(tr >= resolution.shirina)
                        nxr = resolution.shirina - 1;
                    else if(tr < 0){
                        tr += acx;
                        tl += bcx;
                        continue;
                    }
                    else
                        nxr = tr;
                    temp_p = (int*)pixels + resolution.shirina*j + nxl;

                    tp.x = ta_r.x + fx*(a_y - j) + fd*(tr - nxl);
                    tp.y = ta_r.y + fy*(a_y - j) + fb*(tr - nxl);

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = *(texture + ((int)tp.y)*texture_shirina + (int)tp.x);
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        tp.x -= fd;
                        tp.y -= fb;
                    }
                    tr += acx;
                    tl += bcx;
                }
                return 8;   /// - успешное завершение
            }
            else{
                if(c_y > resolution.vysota - 1)
                    return -1;          /// Треугольник вне кадра
                tr = a_x + (acx*ost);
                ost = b_y - (int)b_y;
                if(ost < 0)
                    ost *= -1;
                tl = b_x + (bcx*ost);

                tr += acx * ((int)a_y - resolution.vysota + 1);
                tl += bcx * ((int)b_y - resolution.vysota + 1);
                nyv = resolution.vysota - 1;

                if(c_y > 0)
                    nyn = c_y + 1;
                else
                    nyn = 0;

                for(int j = nyv; j >= nyn; j--){
                    if(tl <= 0)                         /// ЕСТЬ ШАНС ОШИБКИ, поставить tl < 0 в случае обнаружения проблем
                        nxl = 0;
                    else if(tl >= resolution.shirina - 1){
                        tr += acx;
                        tl += bcx;
                        continue; // эту строчку
                    }
    //                else if(tl == resolution.shirina)
    //                    nxl = resolution.shirina - 1;
                    else
                        nxl = tl + 1;
                    if(tr >= resolution.shirina)
                        nxr = resolution.shirina - 1;
                    else if(tr < 0){
                        tr += acx;
                        tl += bcx;
                        continue;
                    }
                    else
                        nxr = tr;
                    temp_p = (int*)pixels + resolution.shirina*j + nxl;

                    tp.x = ta_r.x + fx*(a_y - j) + fd*(tr - nxl);
                    tp.y = ta_r.y + fy*(a_y - j) + fb*(tr - nxl);

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = *(texture + ((int)tp.y)*texture_shirina + (int)tp.x);
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        tp.x -= fd;
                        tp.y -= fb;
                    }
                    tr += acx;
                    tl += bcx;
                }
                return 1;   /// успешное завершение
            }
        }
        else
            return -1;
    }
    else{    /// правый случай (b справа от ac)
        if(a_y > 0){                            /// ПРОВЕРИТЬ, не будет ли ошибок при a_y >= 0, иначе теряются пиклеси в предельно редких случаях
            if(b_y < resolution.vysota - 1){
                tl = a_x + (acx*ost);
                tr = a_x + (abx*ost);
                if(a_y >= resolution.vysota){
                    tl += acx * ((int)a_y - resolution.vysota + 1);
                    tr += abx * ((int)a_y - resolution.vysota + 1);
                    nyv = resolution.vysota - 1;
                }
                else
                    nyv = a_y;
                if(b_y >= 0)
                    nyn = b_y + 1;
                else
                    nyn = 0;
                for(int j = nyv; j >= nyn; j--){
                    if(tl <= 0)                         /// ЕСТЬ ШАНС ОШИБКИ, поставить tl < 0 в случае обнаружения проблем
                        nxl = 0;
                    else if(tl >= resolution.shirina - 1){
                        tl += acx;
                        tr += abx;
                        continue; // эту строчку
                    }
                    else
                        nxl = (int)tl + 1;
                    if(tr >= resolution.shirina)
                        nxr = resolution.shirina - 1;
                    else if(tr < 0){
                        tl += acx;
                        tr += abx;
                        continue; // эту строчку
                    }
                    else
                        nxr = tr;
                    temp_p = (int*)pixels + resolution.shirina*j + nxl;

                    tp.x = ta_r.x + fx*(a_y - j) + fd*(nxl - tl);
                    tp.y = ta_r.y + fy*(a_y - j) + fb*(nxl - tl);

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = *(texture + ((int)tp.y)*texture_shirina + (int)tp.x);
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        tp.x += fd;
                        tp.y += fb;
                    }
                    tl += acx;
                    tr += abx;
                }
                if(nyn == 0)
                    return 9;
                nyv = nyn - 1;
                if(c_y > 0)
                    nyn = c_y + 1;
                else
                    nyn = 0;
                ost = b_y - (int)b_y;
                if(ost < 0)
                    ost *= -1;
                tr = b_x + (bcx*ost);
                for(int j = nyv; j >= nyn; j--){
                    if(tl <= 0)                         /// ЕСТЬ ШАНС ОШИБКИ, поставить tl < 0 в случае обнаружения проблем
                        nxl = 0;
                    else if(tl >= resolution.shirina - 1){
                        tl += acx;
                        tr += bcx;
                        continue; // эту строчку
                    }
    //                else if(tl == resolution.shirina)
    //                    nxl = resolution.shirina - 1;
                    else
                        nxl = tl + 1;
                    if(tr >= resolution.shirina)
                        nxr = resolution.shirina - 1;
                    else if(tr < 0){
                        tl += acx;
                        tr += bcx;
                        continue; // эту строчку
                    }
                    else
                        nxr = tr;
                    temp_p = (int*)pixels + resolution.shirina*j + nxl;

                    tp.x = ta_r.x + fx*(a_y - j) + fd*(nxl - tl);
                    tp.y = ta_r.y + fy*(a_y - j) + fb*(nxl - tl);

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = *(texture + ((int)tp.y)*texture_shirina + (int)tp.x);
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        tp.x += fd;
                        tp.y += fb;
                    }
                    tl += acx;
                    tr += bcx;
                }
                return 2;   /// - успешное завершение
            }
            else{
                if(c_y > resolution.vysota - 1)
                    return -1;          /// Треугольник вне кадра
                tl = a_x + (acx*ost);
                ost = b_y - (int)b_y;
                if(ost < 0)
                    ost *= -1;
                tr = b_x + (bcx*ost);

                tl += acx * ((int)a_y - resolution.vysota + 1);
                tr += bcx * ((int)b_y - resolution.vysota + 1);
                nyv = resolution.vysota - 1;

                if(c_y > 0)
                    nyn = c_y + 1;
                else
                    nyn = 0;

                for(int j = nyv; j >= nyn; j--){
                    if(tl <= 0)                         /// ЕСТЬ ШАНС ОШИБКИ, поставить tl < 0 в случае обнаружения проблем
                        nxl = 0;
                    else if(tl >= resolution.shirina - 1){
                        tl += acx;
                        tr += bcx;
                        continue; // эту строчку
                    }
    //                else if(tl == resolution.shirina)
    //                    nxl = resolution.shirina - 1;
                    else
                        nxl = tl + 1;
                    if(tr >= resolution.shirina)
                        nxr = resolution.shirina - 1;
                    else if(tr < 0){
                        tl += acx;
                        tr += bcx;
                        continue;
                    }
                    else
                        nxr = tr;
                    temp_p = (int*)pixels + resolution.shirina*j + nxl;

                    tp.x = ta_r.x + fx*(a_y - j) + fd*(nxl - tl);
                    tp.y = ta_r.y + fy*(a_y - j) + fb*(nxl - tl);

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = *(texture + ((int)tp.y)*texture_shirina + (int)tp.x);
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        tp.x += fd;
                        tp.y += fb;
                    }
                    tl += acx;
                    tr += bcx;
                }
                return 3;   /// успешное завершение
            }
        }
        else
            return -1;
    }
    return -5;
}



















                               /// ////////////////////////////////////////////////// ///





int Draw_Textured_Edge(void* param)
{
    params_paint* params = (params_paint*)param;
    double a_x = params->p0
    , a_y = params->p1
    , b_x = params->p2
    , b_y = params->p3
    , c_x = params->p4
    , c_y = params->p5
    , ta_x = params->p6
    , ta_y = params->p7
    , tb_x = params->p8
    , tb_y = params->p9
    , tc_x = params->p10
    , tc_y = params->p11
    , l = params->p12;
    int *texture = params->p13;
    int texture_shirina = params->p14;
    int texture_vysota = params->p15;
    if(a_y < b_y){          /// простая перестановка вершин в нужный порядок
        if(b_y < c_y){
            double t;
            t = a_x;
            a_x = c_x;
            c_x = t;
            t = a_y;
            a_y = c_y;
            c_y = t;

            t = ta_x;
            ta_x = tc_x;
            tc_x = t;
            t = ta_y;
            ta_y = tc_y;
            tc_y = t;
        }
        else{
            if(a_y < c_y){
                double t;
                t = a_x;
                a_x = b_x;
                b_x = c_x;
                c_x = t;

                t = a_y;
                a_y = b_y;
                b_y = c_y;
                c_y = t;

                t = ta_x;
                ta_x = tb_x;
                tb_x = tc_x;
                tc_x = t;

                t = ta_y;
                ta_y = tb_y;
                tb_y = tc_y;
                tc_y = t;
            }
            else{///
                double t;
                t = a_x;
                a_x = b_x;
                b_x = t;

                t = ta_x;
                ta_x = tb_x;
                tb_x = t;

                t = a_y;
                a_y = b_y;
                b_y = t;

                t = ta_y;
                ta_y = tb_y;
                tb_y = t;
            }
        }
    }
    else{
        if(a_y > c_y){
            if(b_y < c_y){
                double t;
                t = b_x;
                b_x = c_x;
                c_x = t;

                t = tb_x;
                tb_x = tc_x;
                tc_x = t;

                t = b_y;
                b_y = c_y;
                c_y = t;

                t = tb_y;
                tb_y = tc_y;
                tc_y = t;
            }
        }
        else{
            double t;
            t = a_x;
            a_x = c_x;
            c_x = b_x;
            b_x = t;

            t = ta_x;
            ta_x = tc_x;
            tc_x = tb_x;
            tb_x = t;

            t = a_y;
            a_y = c_y;
            c_y = b_y;
            b_y = t;

            t = ta_y;
            ta_y = tc_y;
            tc_y = tb_y;
            tb_y = t;
        }
    }

    double abx, acx, bcx;
    double tl, tr; // temp left, temp right, temp bc
    double ost;

    if((int)a_y - (int)b_y < 1)
        abx = (b_x - a_x);
    else
        abx = (b_x - a_x) / (a_y - b_y);

    if((int)a_y - (int)c_y < 1)
        acx = (c_x - a_x);
    else
        acx = (c_x - a_x) / (a_y - c_y);

    if((int)b_y - (int)c_y < 1)
        bcx = (c_x - b_x);
    else
        bcx = (c_x - b_x) / (b_y - c_y);

    ost = a_y - (int)a_y;
    if(ost < 0)
        ost *= -1;



    XY ad, tad, ab, tab, ac, tac, db, tdb;
    double oldb, olac_y;
    XY tp;

//    ab = b - a;
    ab.x = b_x - a_x;
    ab.y = b_y - a_y;

//    ac = c - a;
    ac.x = c_x - a_x;
    ac.y = c_y - a_y;

//    tab = tb - ta;
    tab.x = tb_x - ta_x;
    tab.y = tb_y - ta_y;

//    tac = tc - ta;
    tac.x = tc_x - ta_x;
    tac.y = tc_y - ta_y;

//    ad = (ac/ac.y)*(ab.y)
    ad.x = (ac.x/ac.y)*(ab.y);
    ad.y = ab.y;

//    tad.x = (tac.x/tac.y)*(tab.y);
//    tad.y = (tac.y/tac.y)*(tab.y);
///    tad = (tac / |ac|) * |ad|
    double temp;
    temp = SqrtInvE((ac.x*ac.x + ac.y*ac.y)/(ad.x*ad.x + ad.y*ad.y));
    tad.x = tac.x * temp;
    tad.y = tac.y * temp;

//    db = ab - ad;
    db.x = ab.x - ad.x;
//    db.y = ab.y - ad.y;

    tdb.x = tab.x - tad.x;
    tdb.y = tab.y - tad.y;

//////    ldb = |db|;
////    ldb = SqrtInv(db.x*db.x + db.y*db.y);
//    ldb = db.x;
//    oldb = 1/ldb;
    oldb = 1/db.x;
    if(oldb < 0)
        oldb = -oldb;

//    lac = SqrtInv(ac.x*ac.x + ac.y*ac.y);
//    olac = 1/lac;

    olac_y = 1/ac.y;
    if(olac_y < 0)
        olac_y = -olac_y;

    double fx = (tac.x*olac_y)*(texture_shirina)
    , fy = (tac.y*olac_y)*(texture_vysota)
    , fd = (tdb.x*oldb)*(texture_shirina)
    , fb = (tdb.y*oldb)*(texture_vysota);
    XY ta_r;
    ta_r.x = ta_x * (texture_shirina);
    ta_r.y = ta_y * (texture_vysota);

    int nxl, nxr, nyv, nyn; /// nxleft, nxright, nxverh, nxniz
    int *temp_p;
//    int *temp_pp;
//                temp_pp = (int*)pixels + resolution.shirina*nyv;
//                    temp_p = temp_pp + nxl;
//                    temp_pp -= resolution.shirina;
    double *temp_z;

    if(((b_x - a_x)*(c_y - a_y) + (b_y - a_y)*(a_x - c_x)) >= 0){    /// левый случай (b слева от ac)
        if(a_y > 0){                            /// ПРОВЕРИТЬ, не будет ли ошибок при a_y >= 0, иначе теряются пиклеси в предельно редких случаях
            if(b_y < resolution.vysota - 1){
                tr = a_x + (acx*ost);
                tl = a_x + (abx*ost);
                if(a_y >= resolution.vysota){
                    tr += acx * ((int)a_y - resolution.vysota + 1);
                    tl += abx * ((int)a_y - resolution.vysota + 1);
                    nyv = resolution.vysota - 1;
                }
                else
                    nyv = a_y;
                if(b_y >= 0)
                    nyn = b_y + 1;
                else
                    nyn = 0;
                for(int j = nyv; j >= nyn; j--){
                    if(tl <= 0)                         /// ЕСТЬ ШАНС ОШИБКИ, поставить tl < 0 в случае обнаружения проблем
                        nxl = 0;
                    else if(tl >= resolution.shirina - 1){
                        tr += acx;
                        tl += abx;
                        continue; // эту строчку
                    }
    //                else if(tl == resolution.shirina)
    //                    nxl = resolution.shirina - 1;
                    else
                        nxl = tl + 1;
                    if(tr >= resolution.shirina)
                        nxr = resolution.shirina - 1;
                    else if(tr < 0){
                        tr += acx;
                        tl += abx;
                        continue;
                    }
                    else
                        nxr = tr;
                    temp_p = (int*)pixels + resolution.shirina*j + nxl;

                    tp.x = ta_r.x + fx*(a_y - j) + fd*(tr - nxl);
                    tp.y = ta_r.y + fy*(a_y - j) + fb*(tr - nxl);

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = *(texture + ((int)tp.y)*texture_shirina + (int)tp.x);
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        tp.x -= fd;
                        tp.y -= fb;
                    }
                    tr += acx;
                    tl += abx;
                }
                if(nyn == 0)
                    {
delete((double*)param);
return 0;
}
                nyv = nyn - 1;
                if(c_y > 0)
                    nyn = c_y + 1;
                else
                    nyn = 0;
                ost = b_y - (int)b_y;
                if(ost < 0)
                    ost *= -1;
                tl = b_x + (bcx*ost);
                for(int j = nyv; j >= nyn; j--){
                    if(tl <= 0)                         /// ЕСТЬ ШАНС ОШИБКИ, поставить tl < 0 в случае обнаружения проблем
                        nxl = 0;
                    else if(tl >= resolution.shirina - 1){
                        tr += acx;
                        tl += bcx;
                        continue; // эту строчку
                    }
    //                else if(tl == resolution.shirina)
    //                    nxl = resolution.shirina - 1;
                    else
                        nxl = tl + 1;
                    if(tr >= resolution.shirina)
                        nxr = resolution.shirina - 1;
                    else if(tr < 0){
                        tr += acx;
                        tl += bcx;
                        continue;
                    }
                    else
                        nxr = tr;
                    temp_p = (int*)pixels + resolution.shirina*j + nxl;

                    tp.x = ta_r.x + fx*(a_y - j) + fd*(tr - nxl);
                    tp.y = ta_r.y + fy*(a_y - j) + fb*(tr - nxl);

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = *(texture + ((int)tp.y)*texture_shirina + (int)tp.x);
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        tp.x -= fd;
                        tp.y -= fb;
                    }
                    tr += acx;
                    tl += bcx;
                }
                {
delete((double*)param);
return 0;
}
            }
            else{
                if(c_y > resolution.vysota - 1)
                    {
delete((double*)param);
return 0;
}
                tr = a_x + (acx*ost);
                ost = b_y - (int)b_y;
                if(ost < 0)
                    ost *= -1;
                tl = b_x + (bcx*ost);

                tr += acx * ((int)a_y - resolution.vysota + 1);
                tl += bcx * ((int)b_y - resolution.vysota + 1);
                nyv = resolution.vysota - 1;

                if(c_y > 0)
                    nyn = c_y + 1;
                else
                    nyn = 0;

                for(int j = nyv; j >= nyn; j--){
                    if(tl <= 0)                         /// ЕСТЬ ШАНС ОШИБКИ, поставить tl < 0 в случае обнаружения проблем
                        nxl = 0;
                    else if(tl >= resolution.shirina - 1){
                        tr += acx;
                        tl += bcx;
                        continue; // эту строчку
                    }
    //                else if(tl == resolution.shirina)
    //                    nxl = resolution.shirina - 1;
                    else
                        nxl = tl + 1;
                    if(tr >= resolution.shirina)
                        nxr = resolution.shirina - 1;
                    else if(tr < 0){
                        tr += acx;
                        tl += bcx;
                        continue;
                    }
                    else
                        nxr = tr;
                    temp_p = (int*)pixels + resolution.shirina*j + nxl;

                    tp.x = ta_r.x + fx*(a_y - j) + fd*(tr - nxl);
                    tp.y = ta_r.y + fy*(a_y - j) + fb*(tr - nxl);

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = *(texture + ((int)tp.y)*texture_shirina + (int)tp.x);
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        tp.x -= fd;
                        tp.y -= fb;
                    }
                    tr += acx;
                    tl += bcx;
                }
                {
delete((double*)param);
return 0;
}
            }
        }
        else
            {
delete((double*)param);
return 0;
}
    }
    else{    /// правый случай (b справа от ac)
        if(a_y > 0){                            /// ПРОВЕРИТЬ, не будет ли ошибок при a_y >= 0, иначе теряются пиклеси в предельно редких случаях
            if(b_y < resolution.vysota - 1){
                tl = a_x + (acx*ost);
                tr = a_x + (abx*ost);
                if(a_y >= resolution.vysota){
                    tl += acx * ((int)a_y - resolution.vysota + 1);
                    tr += abx * ((int)a_y - resolution.vysota + 1);
                    nyv = resolution.vysota - 1;
                }
                else
                    nyv = a_y;
                if(b_y >= 0)
                    nyn = b_y + 1;
                else
                    nyn = 0;
                for(int j = nyv; j >= nyn; j--){
                    if(tl <= 0)                         /// ЕСТЬ ШАНС ОШИБКИ, поставить tl < 0 в случае обнаружения проблем
                        nxl = 0;
                    else if(tl >= resolution.shirina - 1){
                        tl += acx;
                        tr += abx;
                        continue; // эту строчку
                    }
                    else
                        nxl = (int)tl + 1;
                    if(tr >= resolution.shirina)
                        nxr = resolution.shirina - 1;
                    else if(tr < 0){
                        tl += acx;
                        tr += abx;
                        continue; // эту строчку
                    }
                    else
                        nxr = tr;
                    temp_p = (int*)pixels + resolution.shirina*j + nxl;

                    tp.x = ta_r.x + fx*(a_y - j) + fd*(nxl - tl);
                    tp.y = ta_r.y + fy*(a_y - j) + fb*(nxl - tl);

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = *(texture + ((int)tp.y)*texture_shirina + (int)tp.x);
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        tp.x += fd;
                        tp.y += fb;
                    }
                    tl += acx;
                    tr += abx;
                }
                if(nyn == 0)
                    {
delete((double*)param);
return 0;
}
                nyv = nyn - 1;
                if(c_y > 0)
                    nyn = c_y + 1;
                else
                    nyn = 0;
                ost = b_y - (int)b_y;
                if(ost < 0)
                    ost *= -1;
                tr = b_x + (bcx*ost);
                for(int j = nyv; j >= nyn; j--){
                    if(tl <= 0)                         /// ЕСТЬ ШАНС ОШИБКИ, поставить tl < 0 в случае обнаружения проблем
                        nxl = 0;
                    else if(tl >= resolution.shirina - 1){
                        tl += acx;
                        tr += bcx;
                        continue; // эту строчку
                    }
    //                else if(tl == resolution.shirina)
    //                    nxl = resolution.shirina - 1;
                    else
                        nxl = tl + 1;
                    if(tr >= resolution.shirina)
                        nxr = resolution.shirina - 1;
                    else if(tr < 0){
                        tl += acx;
                        tr += bcx;
                        continue; // эту строчку
                    }
                    else
                        nxr = tr;
                    temp_p = (int*)pixels + resolution.shirina*j + nxl;

                    tp.x = ta_r.x + fx*(a_y - j) + fd*(nxl - tl);
                    tp.y = ta_r.y + fy*(a_y - j) + fb*(nxl - tl);

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = *(texture + ((int)tp.y)*texture_shirina + (int)tp.x);
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        tp.x += fd;
                        tp.y += fb;
                    }
                    tl += acx;
                    tr += bcx;
                }
                {
delete((double*)param);
return 0;
}
            }
            else{
                if(c_y > resolution.vysota - 1)
                    {
delete((double*)param);
return 0;
}
                tl = a_x + (acx*ost);
                ost = b_y - (int)b_y;
                if(ost < 0)
                    ost *= -1;
                tr = b_x + (bcx*ost);

                tl += acx * ((int)a_y - resolution.vysota + 1);
                tr += bcx * ((int)b_y - resolution.vysota + 1);
                nyv = resolution.vysota - 1;

                if(c_y > 0)
                    nyn = c_y + 1;
                else
                    nyn = 0;

                for(int j = nyv; j >= nyn; j--){
                    if(tl <= 0)                         /// ЕСТЬ ШАНС ОШИБКИ, поставить tl < 0 в случае обнаружения проблем
                        nxl = 0;
                    else if(tl >= resolution.shirina - 1){
                        tl += acx;
                        tr += bcx;
                        continue; // эту строчку
                    }
    //                else if(tl == resolution.shirina)
    //                    nxl = resolution.shirina - 1;
                    else
                        nxl = tl + 1;
                    if(tr >= resolution.shirina)
                        nxr = resolution.shirina - 1;
                    else if(tr < 0){
                        tl += acx;
                        tr += bcx;
                        continue;
                    }
                    else
                        nxr = tr;
                    temp_p = (int*)pixels + resolution.shirina*j + nxl;

                    tp.x = ta_r.x + fx*(a_y - j) + fd*(nxl - tl);
                    tp.y = ta_r.y + fy*(a_y - j) + fb*(nxl - tl);

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = *(texture + ((int)tp.y)*texture_shirina + (int)tp.x);
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        tp.x += fd;
                        tp.y += fb;
                    }
                    tl += acx;
                    tr += bcx;
                }
                {
delete((double*)param);
return 0;
}
            }
        }
        else
            {
delete((double*)param);
return 0;
}
    }
    {
delete((double*)param);
return 0;
}
}

**/
