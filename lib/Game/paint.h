


/// ВСЕ ФУНКЦИИ ОТРИСОВКИ ОБЪЕКТОВ ХРАНЯТСЯ В stndt_param.h !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



int Draw_Edge_Optimized_ZBUFFER_FAST(XY a, XY b, XY c, double l, unsigned char red, unsigned char green, unsigned char blue)
{
    int color_int = 0;
//    int* t_color = *color_int;
    unsigned char* tc_color;
    tc_color = (unsigned char*)&color_int;
    *tc_color = blue;
    tc_color++;
    *tc_color = green;
    tc_color++;
    *tc_color = red;
    tc_color++;
    *tc_color = 0;

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

    if((int)a.y - (int)b.y < 1)
        abx = (b.x - a.x);
    else
        abx = (b.x - a.x) / (a.y - b.y);

    if((int)a.y - (int)c.y < 1)
        acx = (c.x - a.x);
    else
        acx = (c.x - a.x) / (a.y - c.y);

    if((int)b.y - (int)c.y < 1)
        bcx = (c.x - b.x);
    else
        bcx = (c.x - b.x) / (b.y - c.y);

    ost = a.y - (int)a.y;
    if(ost < 0)
        ost *= -1;

    int nxl, nxr, nyv, nyn; /// nxleft, nxright, nxverh, nxniz
    int *temp_p;
    double *temp_z;
//    cout << "b.x " << b.x << " b.y " << b.y << " c.x " << c.x << " c.y " << c.y << " a.x " << a.x << " a.y " << a.y << endl;
    if(((b.x - a.x)*(c.y - a.y) + (b.y - a.y)*(a.x - c.x)) >= 0){    /// левый случай (b слева от ac)
        if(a.y > 0){                            /// ПРОВЕРИТЬ, не будет ли ошибок при a.y >= 0, иначе теряются пиклеси в предельно редких случаях
            if(b.y < resolution.vysota - 1){
                tr = a.x + (acx*ost);
                tl = a.x + (abx*ost);
                if(a.y >= resolution.vysota){
                    tr += acx * ((int)a.y - resolution.vysota + 1);
                    tl += abx * ((int)a.y - resolution.vysota + 1);
                    nyv = resolution.vysota - 1;
                }
                else
                    nyv = a.y;
                if(b.y >= 0)
                    nyn = b.y + 1;
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
                    temp_p = ipixels + resolution.shirina*j + nxl;
                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = color_int;
                        }
                        else{
                            temp_p++;
                            temp_z++;
                        }
                    }
                    tr += acx;
                    tl += abx;
                }
                if(nyn == 0)
                    return 7;
                nyv = nyn - 1;
                if(c.y > 0)
                    nyn = c.y + 1;
                else
                    nyn = 0;
                ost = b.y - (int)b.y;
                if(ost < 0)
                    ost *= -1;
                tl = b.x + (bcx*ost);
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
                    temp_p = ipixels + resolution.shirina*j + nxl;
                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = color_int;
                        }
                        else{
                            temp_p++;
                            temp_z++;
                        }
                    }
                    tr += acx;
                    tl += bcx;
                }
                return 8;   /// - успешное завершение
            }
            else{
                if(c.y > resolution.vysota - 1)
                    return -1;          /// Треугольник вне кадра
                tr = a.x + (acx*ost);
                ost = b.y - (int)b.y;
                if(ost < 0)
                    ost *= -1;
                tl = b.x + (bcx*ost);

                tr += acx * ((int)a.y - resolution.vysota + 1);
                tl += bcx * ((int)b.y - resolution.vysota + 1);
                nyv = resolution.vysota - 1;

                if(c.y > 0)
                    nyn = c.y + 1;
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
                    temp_p = ipixels + resolution.shirina*j + nxl;
                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = color_int;
                        }
                        else{
                            temp_p++;
                            temp_z++;
                        }
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
        if(a.y > 0){                            /// ПРОВЕРИТЬ, не будет ли ошибок при a.y >= 0, иначе теряются пиклеси в предельно редких случаях
            if(b.y < resolution.vysota - 1){
                tl = a.x + (acx*ost);
                tr = a.x + (abx*ost);
                if(a.y >= resolution.vysota){
                    tl += acx * ((int)a.y - resolution.vysota + 1);
                    tr += abx * ((int)a.y - resolution.vysota + 1);
                    nyv = resolution.vysota - 1;
                }
                else
                    nyv = a.y;
                if(b.y >= 0)
                    nyn = b.y + 1;
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
                    temp_p = ipixels + resolution.shirina*j + nxl;
                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = color_int;
                        }
                        else{
                            temp_p++;
                            temp_z++;
                        }
                    }
                    tl += acx;
                    tr += abx;
                }
                if(nyn == 0)
                    return 9;
                nyv = nyn - 1;
                if(c.y > 0)
                    nyn = c.y + 1;
                else
                    nyn = 0;
                ost = b.y - (int)b.y;
                if(ost < 0)
                    ost *= -1;
                tr = b.x + (bcx*ost);
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
                    temp_p = ipixels + resolution.shirina*j + nxl;
                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = color_int;
                        }
                        else{
                            temp_p++;
                            temp_z++;
                        }
                    }
                    tl += acx;
                    tr += bcx;
                }
                return 2;   /// - успешное завершение
            }
            else{
                if(c.y > resolution.vysota - 1)
                    return -1;          /// Треугольник вне кадра
                tl = a.x + (acx*ost);
                ost = b.y - (int)b.y;
                if(ost < 0)
                    ost *= -1;
                tr = b.x + (bcx*ost);

                tl += acx * ((int)a.y - resolution.vysota + 1);
                tr += bcx * ((int)b.y - resolution.vysota + 1);
                nyv = resolution.vysota - 1;

                if(c.y > 0)
                    nyn = c.y + 1;
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
                    temp_p = ipixels + resolution.shirina*j + nxl;
                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = color_int;
                        }
                        else{
                            temp_p++;
                            temp_z++;
                        }
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

/// По аналогии с нахождением текстурных координат вычислять коэффициент света
int Draw_Edge_Optimized_ZBUFFER_textured_short_GLOBAL_LIGHT(XY a, XY b, XY c, XYZ ta, XYZ tb, XYZ tc, Texture& texture, double l, double light)
{
    if(a.y < b.y){          /// простая перестановка вершин в нужный порядок
        if(b.y < c.y){
            XY t;
            t = a;
            a = c;
            c = t;

            XYZ tt;
            tt = ta;
            ta = tc;
            tc = tt;
        }
        else{
            if(a.y < c.y){
                XY t;
                t = a;
                a = b;
                b = c;
                c = t;

                XYZ tt;
                tt = ta;
                ta = tb;
                tb = tc;
                tc = tt;
            }
            else{
                XY t;
                t = a;
                a = b;
                b = t;

                XYZ tt;
                tt = ta;
                ta = tb;
                tb = tt;
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

                XYZ tt;
                tt = tb;
                tb = tc;
                tc = tt;
            }
        }
        else{
            XY t;
            t = a;
            a = c;
            c = b;
            b = t;

            XYZ tt;
            tt = ta;
            ta = tc;
            tc = tb;
            tb = tt;
        }
    }

    double abx, acx, bcx;
    double tl, tr; // temp left, temp right, temp bc
    double ost;

    if((int)a.y - (int)b.y < 1)
        abx = (b.x - a.x);
    else
        abx = (b.x - a.x) / (a.y - b.y);

    if((int)a.y - (int)c.y < 1)
        acx = (c.x - a.x);
    else
        acx = (c.x - a.x) / (a.y - c.y);

    if((int)b.y - (int)c.y < 1)
        bcx = (c.x - b.x);
    else
        bcx = (c.x - b.x) / (b.y - c.y);

    ost = a.y - (int)a.y;
    if(ost < 0)
        ost *= -1;



    XY ad, tad, ab, tab, ac, tac, db, tdb;
    double oldb, olac_y;
    iXY tp;

//    ab = b - a;
    ab.x = b.x - a.x;
    ab.y = b.y - a.y;

//    ac = c - a;
    ac.x = c.x - a.x;
    ac.y = c.y - a.y;

//    tab = tb - ta;
    tab.x = tb.x - ta.x;
    tab.y = tb.y - ta.y;

//    tac = tc - ta;
    tac.x = tc.x - ta.x;
    tac.y = tc.y - ta.y;

//    ad = (ac/ac.y)*(ab.y)
    ad.x = (ac.x/ac.y)*(ab.y);
    ad.y = ab.y;

//    tad.x = (tac.x/tac.y)*(tab.y);
//    tad.y = (tac.y/tac.y)*(tab.y);
///    tad = (tac / |ac|) * |ad|
    double temp;
    temp = SqrtInvE(ac.x*ac.x + ac.y*ac.y) * SqrtInv(ad.x*ad.x + ad.y*ad.y);
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
{
////    tp = (ac/ac.y)*acy + (dk/ldk)*(tr - i);
//    tp.x = (ac.x/ac.y)*acy + (dk.x/ldk)*(tr - i);
//    tp.y = (ac.y/ac.y)*acy + (dk.y/ldk)*(tr - i);
//
////    tp = (tac/ac.y)*acy + (tdk/ldk)*(tr - i);
//    tp.x = (tac.x/ac.y)*acy + (tdk.x/ldk)*(tr - i);
//    tp.y = (tac.y/ac.y)*acy + (tdk.y/ldk)*(tr - i);

////    tp = (tac/ac.y)*acy + (tdb/ldb)*(tr - i);
//    tp.x = (tac.x/ac.y)*acy + (tdb.x/ldb)*(tr - i);
//    tp.y = (tac.y/ac.y)*acy + (tdb.y/ldb)*(tr - i);
}
                    /// для B-левого случая
//    tp.x = ta.x + (tac.x*olac_y)*(a.y - j) + (tdb.x*oldb)*(tr - i);
//    tp.y = ta.y + (tac.y*olac_y)*(a.y - j) + (tdb.y*oldb)*(tr - i);
                    /// для B-правого случая
//    tp.x = ta.x + (tac.x*olac_y)*(a.y - j) + (tdb.x*oldb)*(i - tl);
//    tp.y = ta.y + (tac.y*olac_y)*(a.y - j) + (tdb.y*oldb)*(i - tl);
    double tacxolacy = (tac.x*olac_y)
    , tacyolacy = (tac.y*olac_y)
    , tdbxoldb = (tdb.x*oldb)
    , tdbyoldb = (tdb.y*oldb);

    int nxl, nxr, nyv, nyn; /// nxleft, nxright, nxverh, nxniz
//    cout << "b.x " << b.x << " b.y " << b.y << " c.x " << c.x << " c.y " << c.y << " a.x " << a.x << " a.y " << a.y << endl;
    if(((b.x - a.x)*(c.y - a.y) + (b.y - a.y)*(a.x - c.x)) >= 0){    /// левый случай (b слева от ac)
        if(a.y > 0){                            /// ПРОВЕРИТЬ, не будет ли ошибок при a.y >= 0, иначе теряются пиклеси в предельно редких случаях
            if(b.y < resolution.vysota - 1){
                tr = a.x + (acx*ost);
                tl = a.x + (abx*ost);
                if(a.y >= resolution.vysota){
                    tr += acx * ((int)a.y - resolution.vysota + 1);
                    tl += abx * ((int)a.y - resolution.vysota + 1);
                    nyv = resolution.vysota - 1;
                }
                else
                    nyv = a.y;
                if(b.y >= 0)
                    nyn = b.y + 1;
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
                    for(int i = nxl; i <= nxr; i++){
                        if(l < z_buffer[resolution.shirina*j + i]){
                            z_buffer[resolution.shirina*j + i] = l;
                            tp.x = (ta.x + tacxolacy*(a.y - j) + tdbxoldb*(tr - i))*(texture.res.shirina);
                            tp.y = (ta.y + tacyolacy*(a.y - j) + tdbyoldb*(tr - i))*(texture.res.vysota);
                            pixels[resolution.shirina*j*4 + i*4] = texture.texture[tp.y][tp.x].b*light;
                            pixels[resolution.shirina*j*4 + i*4 + 1] = texture.texture[tp.y][tp.x].g*light;
                            pixels[resolution.shirina*j*4 + i*4 + 2] = texture.texture[tp.y][tp.x].r*light;
                            // pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 3] = texture.texture[tp.y][tp.x].f;
                        }
                    }
                    tr += acx;
                    tl += abx;
                }
                if(nyn == 0)
                    return 7;
                nyv = nyn - 1;
                if(c.y > 0)
                    nyn = c.y + 1;
                else
                    nyn = 0;
                ost = b.y - (int)b.y;
                if(ost < 0)
                    ost *= -1;
                tl = b.x + (bcx*ost);
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
                    for(int i = nxl; i <= nxr; i++){
                        if(l < z_buffer[resolution.shirina*j + i]){
                            z_buffer[resolution.shirina*j + i] = l;
                            tp.x = (ta.x + tacxolacy*(a.y - j) + tdbxoldb*(tr - i))*(texture.res.shirina);
                            tp.y = (ta.y + tacyolacy*(a.y - j) + tdbyoldb*(tr - i))*(texture.res.vysota);
                            pixels[resolution.shirina*j*4 + i*4] = texture.texture[tp.y][tp.x].b*light;
                            pixels[resolution.shirina*j*4 + i*4 + 1] = texture.texture[tp.y][tp.x].g*light;
                            pixels[resolution.shirina*j*4 + i*4 + 2] = texture.texture[tp.y][tp.x].r*light;
                            // pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 3] = texture.texture[tp.y][tp.x].f;
                        }
                    }
                    tr += acx;
                    tl += bcx;
                }
                return 8;   /// - успешное завершение
            }
            else{
                if(c.y > resolution.vysota - 1)
                    return -1;          /// Треугольник вне кадра
                tr = a.x + (acx*ost);
                ost = b.y - (int)b.y;
                if(ost < 0)
                    ost *= -1;
                tl = b.x + (bcx*ost);

                tr += acx * ((int)a.y - resolution.vysota + 1);
                tl += bcx * ((int)b.y - resolution.vysota + 1);
                nyv = resolution.vysota - 1;

                if(c.y > 0)
                    nyn = c.y + 1;
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
                    for(int i = nxl; i <= nxr; i++){
                        if(l < z_buffer[resolution.shirina*j + i]){
                            z_buffer[resolution.shirina*j + i] = l;
                            tp.x = (ta.x + tacxolacy*(a.y - j) + tdbxoldb*(tr - i))*(texture.res.shirina);
                            tp.y = (ta.y + tacyolacy*(a.y - j) + tdbyoldb*(tr - i))*(texture.res.vysota);
                            pixels[resolution.shirina*j*4 + i*4] = texture.texture[tp.y][tp.x].b*light;
                            pixels[resolution.shirina*j*4 + i*4 + 1] = texture.texture[tp.y][tp.x].g*light;
                            pixels[resolution.shirina*j*4 + i*4 + 2] = texture.texture[tp.y][tp.x].r*light;
                            // pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 3] = texture.texture[tp.y][tp.x].f;
                        }
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
        if(a.y > 0){                            /// ПРОВЕРИТЬ, не будет ли ошибок при a.y >= 0, иначе теряются пиклеси в предельно редких случаях
            if(b.y < resolution.vysota - 1){
                tl = a.x + (acx*ost);
                tr = a.x + (abx*ost);
                if(a.y >= resolution.vysota){
                    tl += acx * ((int)a.y - resolution.vysota + 1);
                    tr += abx * ((int)a.y - resolution.vysota + 1);
                    nyv = resolution.vysota - 1;
                }
                else
                    nyv = a.y;
                if(b.y >= 0)
                    nyn = b.y + 1;
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
                    for(int i = nxl; i <= nxr; i++){
                        if(l < z_buffer[resolution.shirina*j + i]){
                            z_buffer[resolution.shirina*j + i] = l;
                            tp.x = (ta.x + tacxolacy*(a.y - j) + tdbxoldb*(i - tl))*(texture.res.shirina);
                            tp.y = (ta.y + tacyolacy*(a.y - j) + tdbyoldb*(i - tl))*(texture.res.vysota);
                            pixels[resolution.shirina*j*4 + i*4] = texture.texture[tp.y][tp.x].b*light;
                            pixels[resolution.shirina*j*4 + i*4 + 1] = texture.texture[tp.y][tp.x].g*light;
                            pixels[resolution.shirina*j*4 + i*4 + 2] = texture.texture[tp.y][tp.x].r*light;
                            // pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 3] = texture.texture[tp.y][tp.x].f;
                        }
                    }
                    tl += acx;
                    tr += abx;
                }
                if(nyn == 0)
                    return 9;
                nyv = nyn - 1;
                if(c.y > 0)
                    nyn = c.y + 1;
                else
                    nyn = 0;
                ost = b.y - (int)b.y;
                if(ost < 0)
                    ost *= -1;
                tr = b.x + (bcx*ost);
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
                    for(int i = nxl; i <= nxr; i++){
                        if(l < z_buffer[resolution.shirina*j + i]){
                            z_buffer[resolution.shirina*j + i] = l;
                            tp.x = (ta.x + tacxolacy*(a.y - j) + tdbxoldb*(i - tl))*(texture.res.shirina);
                            tp.y = (ta.y + tacyolacy*(a.y - j) + tdbyoldb*(i - tl))*(texture.res.vysota);
                            pixels[resolution.shirina*j*4 + i*4] = texture.texture[tp.y][tp.x].b*light;
                            pixels[resolution.shirina*j*4 + i*4 + 1] = texture.texture[tp.y][tp.x].g*light;
                            pixels[resolution.shirina*j*4 + i*4 + 2] = texture.texture[tp.y][tp.x].r*light;
                            // pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 3] = texture.texture[tp.y][tp.x].f;
                        }
                    }
                    tl += acx;
                    tr += bcx;
                }
                return 2;   /// - успешное завершение
            }
            else{
                if(c.y > resolution.vysota - 1)
                    return -1;          /// Треугольник вне кадра
                tl = a.x + (acx*ost);
                ost = b.y - (int)b.y;
                if(ost < 0)
                    ost *= -1;
                tr = b.x + (bcx*ost);

                tl += acx * ((int)a.y - resolution.vysota + 1);
                tr += bcx * ((int)b.y - resolution.vysota + 1);
                nyv = resolution.vysota - 1;

                if(c.y > 0)
                    nyn = c.y + 1;
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
                    for(int i = nxl; i <= nxr; i++){
                        if(l < z_buffer[resolution.shirina*j + i]){
                            z_buffer[resolution.shirina*j + i] = l;
                            tp.x = (ta.x + tacxolacy*(a.y - j) + tdbxoldb*(i - tl))*(texture.res.shirina);
                            tp.y = (ta.y + tacyolacy*(a.y - j) + tdbyoldb*(i - tl))*(texture.res.vysota);
                            pixels[resolution.shirina*j*4 + i*4] = texture.texture[tp.y][tp.x].b*light;
                            pixels[resolution.shirina*j*4 + i*4 + 1] = texture.texture[tp.y][tp.x].g*light;
                            pixels[resolution.shirina*j*4 + i*4 + 2] = texture.texture[tp.y][tp.x].r*light;
                            // pixels[resolution.shirina*ipix.y*4 + ipix.x*4 + 3] = texture.texture[tp.y][tp.x].f;
                        }
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

int Draw_Edge_Optimized_ZBUFFER_textured_short_GLOBAL_LIGHT_FAST(XY a, XY b, XY c, XYZ ta, XYZ tb, XYZ tc, Texture& texture, double l, double light)
{
    if(a.y < b.y){          /// простая перестановка вершин в нужный порядок
        if(b.y < c.y){
            XY t;
            t = a;
            a = c;
            c = t;

            XYZ tt;
            tt = ta;
            ta = tc;
            tc = tt;
        }
        else{
            if(a.y < c.y){
                XY t;
                t = a;
                a = b;
                b = c;
                c = t;

                XYZ tt;
                tt = ta;
                ta = tb;
                tb = tc;
                tc = tt;
            }
            else{
                XY t;
                t = a;
                a = b;
                b = t;

                XYZ tt;
                tt = ta;
                ta = tb;
                tb = tt;
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

                XYZ tt;
                tt = tb;
                tb = tc;
                tc = tt;
            }
        }
        else{
            XY t;
            t = a;
            a = c;
            c = b;
            b = t;

            XYZ tt;
            tt = ta;
            ta = tc;
            tc = tb;
            tb = tt;
        }
    }

    double abx, acx, bcx;
    double tl, tr; // temp left, temp right, temp bc
    double ost;

    if((int)a.y - (int)b.y < 1)
        abx = (b.x - a.x);
    else
        abx = (b.x - a.x) / (a.y - b.y);

    if((int)a.y - (int)c.y < 1)
        acx = (c.x - a.x);
    else
        acx = (c.x - a.x) / (a.y - c.y);

    if((int)b.y - (int)c.y < 1)
        bcx = (c.x - b.x);
    else
        bcx = (c.x - b.x) / (b.y - c.y);

    ost = a.y - (int)a.y;
    if(ost < 0)
        ost *= -1;



    XY ad, tad, ab, tab, ac, tac, db, tdb;
    double oldb, olac_y;
    XY tp;

//    ab = b - a;
    ab.x = b.x - a.x;
    ab.y = b.y - a.y;

//    ac = c - a;
    ac.x = c.x - a.x;
    ac.y = c.y - a.y;

//    tab = tb - ta;
    tab.x = tb.x - ta.x;
    tab.y = tb.y - ta.y;

//    tac = tc - ta;
    tac.x = tc.x - ta.x;
    tac.y = tc.y - ta.y;

//    ad = (ac/ac.y)*(ab.y)
    ad.x = (ac.x/ac.y)*(ab.y);
    ad.y = ab.y;

//    tad.x = (tac.x/tac.y)*(tab.y);
//    tad.y = (tac.y/tac.y)*(tab.y);
///    tad = (tac / |ac|) * |ad|
    double temp;
    temp = SqrtInvE(ac.x*ac.x + ac.y*ac.y) * SqrtInv(ad.x*ad.x + ad.y*ad.y);
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
{
////    tp = (ac/ac.y)*acy + (dk/ldk)*(tr - i);
//    tp.x = (ac.x/ac.y)*acy + (dk.x/ldk)*(tr - i);
//    tp.y = (ac.y/ac.y)*acy + (dk.y/ldk)*(tr - i);
//
////    tp = (tac/ac.y)*acy + (tdk/ldk)*(tr - i);
//    tp.x = (tac.x/ac.y)*acy + (tdk.x/ldk)*(tr - i);
//    tp.y = (tac.y/ac.y)*acy + (tdk.y/ldk)*(tr - i);

////    tp = (tac/ac.y)*acy + (tdb/ldb)*(tr - i);
//    tp.x = (tac.x/ac.y)*acy + (tdb.x/ldb)*(tr - i);
//    tp.y = (tac.y/ac.y)*acy + (tdb.y/ldb)*(tr - i);
}
                    /// для B-левого случая
//    tp.x = ta.x + (tac.x*olac_y)*(a.y - j) + (tdb.x*oldb)*(tr - i);
//    tp.y = ta.y + (tac.y*olac_y)*(a.y - j) + (tdb.y*oldb)*(tr - i);
                    /// для B-правого случая
//    tp.x = ta.x + (tac.x*olac_y)*(a.y - j) + (tdb.x*oldb)*(i - tl);
//    tp.y = ta.y + (tac.y*olac_y)*(a.y - j) + (tdb.y*oldb)*(i - tl);
    double tacxolacy = (tac.x*olac_y)
    , tacyolacy = (tac.y*olac_y)
    , tdbxoldb = (tdb.x*oldb)
    , tdbxoldb_r = (tdb.x*oldb)*(texture.res.shirina)
    , tdbyoldb = (tdb.y*oldb)
    , tdbyoldb_r = (tdb.y*oldb)*(texture.res.vysota);

    int nxl, nxr, nyv, nyn; /// nxleft, nxright, nxverh, nxniz
    unsigned char *temp_p;
    double *temp_z;
    double temp_xx = 1.;
    double temp_yy = 1.;
    int tpx, tpy;
//    cout << "b.x " << b.x << " b.y " << b.y << " c.x " << c.x << " c.y " << c.y << " a.x " << a.x << " a.y " << a.y << endl;
    if(((b.x - a.x)*(c.y - a.y) + (b.y - a.y)*(a.x - c.x)) >= 0){    /// левый случай (b слева от ac)
        if(a.y > 0){                            /// ПРОВЕРИТЬ, не будет ли ошибок при a.y >= 0, иначе теряются пиклеси в предельно редких случаях
            if(b.y < resolution.vysota - 1){
                tr = a.x + (acx*ost);
                tl = a.x + (abx*ost);
                if(a.y >= resolution.vysota){
                    tr += acx * ((int)a.y - resolution.vysota + 1);
                    tl += abx * ((int)a.y - resolution.vysota + 1);
                    nyv = resolution.vysota - 1;
                }
                else
                    nyv = a.y;
                if(b.y >= 0)
                    nyn = b.y + 1;
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
                    temp_p = pixels + resolution.shirina*j*4 + nxl*4;

                    temp_xx = ta.x + tacxolacy*(a.y - j) + tdbxoldb*tr;
                    temp_yy = ta.y + tacyolacy*(a.y - j) + tdbyoldb*tr;

                    tp.x = (temp_xx - tdbxoldb*nxl)*(texture.res.shirina);
                    tp.y = (temp_yy - tdbyoldb*nxl)*(texture.res.vysota);

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < z_buffer[resolution.shirina*j + i]){
                            *temp_z = l;
                            temp_z++;
                            tpx = tp.x;
                            tpy = tp.y;
                            *temp_p = texture.texture[tpy][tpx].b*light;
                            temp_p++;
                            *temp_p = texture.texture[tpy][tpx].g*light;
                            temp_p++;
                            *temp_p = texture.texture[tpy][tpx].r*light;
                            temp_p++;
                            // temp_p = texture.texture[tpy][tpx].f;
                            temp_p++;
                            tp.x -= tdbxoldb_r;
                            tp.y -= tdbyoldb_r;
                        }
                        else{
                            temp_z++;
                            temp_p += 4;
                            tp.x -= tdbxoldb_r;
                            tp.y -= tdbyoldb_r;
                        }
                    }
                    tr += acx;
                    tl += abx;
                }
                if(nyn == 0)
                    return 7;
                nyv = nyn - 1;
                if(c.y > 0)
                    nyn = c.y + 1;
                else
                    nyn = 0;
                ost = b.y - (int)b.y;
                if(ost < 0)
                    ost *= -1;
                tl = b.x + (bcx*ost);
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
                    temp_p = pixels + resolution.shirina*j*4 + nxl*4;

                    temp_xx = ta.x + tacxolacy*(a.y - j) + tdbxoldb*tr;
                    temp_yy = ta.y + tacyolacy*(a.y - j) + tdbyoldb*tr;

                    tp.x = (temp_xx - tdbxoldb*nxl)*(texture.res.shirina);
                    tp.y = (temp_yy - tdbyoldb*nxl)*(texture.res.vysota);
                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < z_buffer[resolution.shirina*j + i]){
                            *temp_z = l;
                            temp_z++;
                            tpx = tp.x;
                            tpy = tp.y;
                            *temp_p = texture.texture[tpy][tpx].b*light;
                            temp_p++;
                            *temp_p = texture.texture[tpy][tpx].g*light;
                            temp_p++;
                            *temp_p = texture.texture[tpy][tpx].r*light;
                            temp_p++;
                            // temp_p = texture.texture[tpy][tpx].f;
                            temp_p++;
                            tp.x -= tdbxoldb_r;
                            tp.y -= tdbyoldb_r;
                        }
                        else{
                            temp_z++;
                            temp_p += 4;
                            tp.x -= tdbxoldb_r;
                            tp.y -= tdbyoldb_r;
                        }
                    }
                    tr += acx;
                    tl += bcx;
                }
                return 8;   /// - успешное завершение
            }
            else{
                if(c.y > resolution.vysota - 1)
                    return -1;          /// Треугольник вне кадра
                tr = a.x + (acx*ost);
                ost = b.y - (int)b.y;
                if(ost < 0)
                    ost *= -1;
                tl = b.x + (bcx*ost);

                tr += acx * ((int)a.y - resolution.vysota + 1);
                tl += bcx * ((int)b.y - resolution.vysota + 1);
                nyv = resolution.vysota - 1;

                if(c.y > 0)
                    nyn = c.y + 1;
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
                    temp_p = pixels + resolution.shirina*j*4 + nxl*4;

                    temp_xx = ta.x + tacxolacy*(a.y - j) + tdbxoldb*tr;
                    temp_yy = ta.y + tacyolacy*(a.y - j) + tdbyoldb*tr;

                    tp.x = (temp_xx - tdbxoldb*nxl)*(texture.res.shirina);
                    tp.y = (temp_yy - tdbyoldb*nxl)*(texture.res.vysota);
                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < z_buffer[resolution.shirina*j + i]){
                            *temp_z = l;
                            temp_z++;
                            tpx = tp.x;
                            tpy = tp.y;
                            *temp_p = texture.texture[tpy][tpx].b*light;
                            temp_p++;
                            *temp_p = texture.texture[tpy][tpx].g*light;
                            temp_p++;
                            *temp_p = texture.texture[tpy][tpx].r*light;
                            temp_p++;
                            // temp_p = texture.texture[tpy][tpx].f;
                            temp_p++;
                            tp.x -= tdbxoldb_r;
                            tp.y -= tdbyoldb_r;
                        }
                        else{
                            temp_z++;
                            temp_p += 4;
                            tp.x -= tdbxoldb_r;
                            tp.y -= tdbyoldb_r;
                        }
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
        if(a.y > 0){                            /// ПРОВЕРИТЬ, не будет ли ошибок при a.y >= 0, иначе теряются пиклеси в предельно редких случаях
            if(b.y < resolution.vysota - 1){
                tl = a.x + (acx*ost);
                tr = a.x + (abx*ost);
                if(a.y >= resolution.vysota){
                    tl += acx * ((int)a.y - resolution.vysota + 1);
                    tr += abx * ((int)a.y - resolution.vysota + 1);
                    nyv = resolution.vysota - 1;
                }
                else
                    nyv = a.y;
                if(b.y >= 0)
                    nyn = b.y + 1;
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
                    temp_p = pixels + resolution.shirina*j*4 + nxl*4;

                    temp_xx = ta.x + tacxolacy*(a.y - j) - tdbxoldb*tl;
                    temp_yy = ta.y + tacyolacy*(a.y - j) - tdbyoldb*tl;

                    tp.x = (temp_xx + tdbxoldb*nxl)*(texture.res.shirina);
                    tp.y = (temp_yy + tdbyoldb*nxl)*(texture.res.vysota);
                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < z_buffer[resolution.shirina*j + i]){
                            *temp_z = l;
                            temp_z++;
                            tpx = tp.x;
                            tpy = tp.y;
                            *temp_p = texture.texture[tpy][tpx].b*light;
                            temp_p++;
                            *temp_p = texture.texture[tpy][tpx].g*light;
                            temp_p++;
                            *temp_p = texture.texture[tpy][tpx].r*light;
                            temp_p++;
                            // temp_p = texture.texture[tpy][tpx].f;
                            temp_p++;
                            tp.x += tdbxoldb_r;
                            tp.y += tdbyoldb_r;
                        }
                        else{
                            temp_z++;
                            temp_p += 4;
                            tp.x += tdbxoldb_r;
                            tp.y += tdbyoldb_r;
                        }
                    }
                    tl += acx;
                    tr += abx;
                }
                if(nyn == 0)
                    return 9;
                nyv = nyn - 1;
                if(c.y > 0)
                    nyn = c.y + 1;
                else
                    nyn = 0;
                ost = b.y - (int)b.y;
                if(ost < 0)
                    ost *= -1;
                tr = b.x + (bcx*ost);
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
                    temp_p = pixels + resolution.shirina*j*4 + nxl*4;

                    temp_xx = ta.x + tacxolacy*(a.y - j) - tdbxoldb*tl;
                    temp_yy = ta.y + tacyolacy*(a.y - j) - tdbyoldb*tl;

                    tp.x = (temp_xx + tdbxoldb*nxl)*(texture.res.shirina);
                    tp.y = (temp_yy + tdbyoldb*nxl)*(texture.res.vysota);
                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < z_buffer[resolution.shirina*j + i]){
                            *temp_z = l;
                            temp_z++;
                            tpx = tp.x;
                            tpy = tp.y;
                            *temp_p = texture.texture[tpy][tpx].b*light;
                            temp_p++;
                            *temp_p = texture.texture[tpy][tpx].g*light;
                            temp_p++;
                            *temp_p = texture.texture[tpy][tpx].r*light;
                            temp_p++;
                            // temp_p = texture.texture[tpy][tpx].f;
                            temp_p++;
                            tp.x += tdbxoldb_r;
                            tp.y += tdbyoldb_r;
                        }
                        else{
                            temp_z++;
                            temp_p += 4;
                            tp.x += tdbxoldb_r;
                            tp.y += tdbyoldb_r;
                        }
                    }
                    tl += acx;
                    tr += bcx;
                }
                return 2;   /// - успешное завершение
            }
            else{
                if(c.y > resolution.vysota - 1)
                    return -1;          /// Треугольник вне кадра
                tl = a.x + (acx*ost);
                ost = b.y - (int)b.y;
                if(ost < 0)
                    ost *= -1;
                tr = b.x + (bcx*ost);

                tl += acx * ((int)a.y - resolution.vysota + 1);
                tr += bcx * ((int)b.y - resolution.vysota + 1);
                nyv = resolution.vysota - 1;

                if(c.y > 0)
                    nyn = c.y + 1;
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
                    temp_p = pixels + resolution.shirina*j*4 + nxl*4;

                    temp_xx = ta.x + tacxolacy*(a.y - j) - tdbxoldb*tl;
                    temp_yy = ta.y + tacyolacy*(a.y - j) - tdbyoldb*tl;

                    tp.x = (temp_xx + tdbxoldb*nxl)*(texture.res.shirina);
                    tp.y = (temp_yy + tdbyoldb*nxl)*(texture.res.vysota);
                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < z_buffer[resolution.shirina*j + i]){
                            *temp_z = l;
                            temp_z++;
                            tpx = tp.x;
                            tpy = tp.y;
                            *temp_p = texture.texture[tpy][tpx].b*light;
                            temp_p++;
                            *temp_p = texture.texture[tpy][tpx].g*light;
                            temp_p++;
                            *temp_p = texture.texture[tpy][tpx].r*light;
                            temp_p++;
                            // temp_p = texture.texture[tpy][tpx].f;
                            temp_p++;
                            tp.x += tdbxoldb_r;
                            tp.y += tdbyoldb_r;
                        }
                        else{
                            temp_z++;
                            temp_p += 4;
                            tp.x += tdbxoldb_r;
                            tp.y += tdbyoldb_r;
                        }
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

bool image_defolt(char color_R, char color_G, char color_B)
{
    for(int i = 0; i < resolution.vysota - 1; i++){
        for(int j = 0; j < resolution.shirina; j++){
            pixels[resolution.shirina*i*4 + j*4] = color_B;
            pixels[resolution.shirina*i*4 + j*4 + 1] = color_G;
            pixels[resolution.shirina*i*4 + j*4 + 2] = color_R;
            // pixels[resolution.shirina*i*4 + j*4 + 3] = 0;
        }
    }
//    memset(pixels, 0, sizeof(unsigned char)*resolution.vysota*resolution.shirina*4);
    return 0;
}

bool image_defolt_F(char color_R, char color_G, char color_B)
{
    int color;
    unsigned char* tc;
    tc = (unsigned char*)&color;
    *tc = color_B;
    tc++;
    *tc = color_G;
    tc++;
    *tc = color_R;
    tc++;
    *tc = 255;
    int* image;
    image = ipixels;
//    memset(z_buffer, 100, sizeof(double)*resolution.vysota*resolution.shirina);
    double *temp_z;
    temp_z = z_buffer;
    for(int i = 0; i < resolution.vysota; i++)
        for(int j = 0; j < resolution.shirina; j++){
            *temp_z++ = VIZION_FAR;
            *image++ = color;
        }
//            z_buffer[resolution.shirina*i + j] = 100000000;
    return 0;
}

/*
100 600.7
500 600.8
200 100
*/
//bool Draw_All_Objects()
//{
//    for(Objects_On_Scene){
//        //  упорядочивание по отдаленности объектов
//        for(All_Object_Edges){
//            //  if-отсечение нелицевых граней
//            //  если все три точки по одну сторону вне
//        }
//    }
//}
