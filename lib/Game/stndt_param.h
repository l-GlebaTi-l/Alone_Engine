
int Draw_Textured_Edge_int(XY a, XY b, XY c, XYZ ta, XYZ tb, XYZ tc, int *texture, int texture_shirina, int texture_vysota, double l)
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
    iXY itp;

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
    int ifd = fd*10000
    , ifb = fb*10000;
    XY ta_r;
    ta_r.x = ta.x * (texture_shirina);
    ta_r.y = ta.y * (texture_vysota);

    int nxl, nxr, nyv, nyn; /// nxleft, nxright, nxverh, nxniz
    int *temp_p;
//    int *temp_pp;
//                temp_pp = ipixels + resolution.shirina*nyv;
//                    temp_p = temp_pp + nxl;
//                    temp_pp -= resolution.shirina;
    double *temp_z;

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

                    itp.x = (ta_r.x + fx*(a.y - j) + fd*(tr - nxl))*10000;
                    itp.y = (ta_r.y + fy*(a.y - j) + fb*(tr - nxl))*10000;

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = *(texture + itp.y/10000*texture_shirina + itp.x/10000);
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        itp.x -= ifd;
                        itp.y -= ifb;
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

                    itp.x = (ta_r.x + fx*(a.y - j) + fd*(tr - nxl))*10000;
                    itp.y = (ta_r.y + fy*(a.y - j) + fb*(tr - nxl))*10000;

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = *(texture + itp.y/10000*texture_shirina + itp.x/10000);
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        itp.x -= ifd;
                        itp.y -= ifb;
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

                    itp.x = (ta_r.x + fx*(a.y - j) + fd*(tr - nxl))*10000;
                    itp.y = (ta_r.y + fy*(a.y - j) + fb*(tr - nxl))*10000;

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = *(texture + itp.y/10000*texture_shirina + itp.x/10000);
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        itp.x -= ifd;
                        itp.y -= ifb;
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

                    itp.x = (ta_r.x + fx*(a.y - j) + fd*(nxl - tl))*10000;
                    itp.y = (ta_r.y + fy*(a.y - j) + fb*(nxl - tl))*10000;

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = *(texture + itp.y/10000*texture_shirina + itp.x/10000);
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        itp.x += ifd;
                        itp.y += ifb;
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

                    itp.x = (ta_r.x + fx*(a.y - j) + fd*(nxl - tl))*10000;
                    itp.y = (ta_r.y + fy*(a.y - j) + fb*(nxl - tl))*10000;

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = *(texture + itp.y/10000*texture_shirina + itp.x/10000);
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        itp.x += ifd;
                        itp.y += ifb;
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

                    itp.x = (ta_r.x + fx*(a.y - j) + fd*(nxl - tl))*10000;
                    itp.y = (ta_r.y + fy*(a.y - j) + fb*(nxl - tl))*10000;

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            *temp_z++ = l;
                            *temp_p++ = *(texture + itp.y/10000*texture_shirina + itp.x/10000);
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        itp.x += ifd;
                        itp.y += ifb;
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

int Draw_Textured_Edge_Proz_int(XY a, XY b, XY c, XYZ ta, XYZ tb, XYZ tc, int *texture, int texture_shirina, int texture_vysota, double l)
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
    iXY itp;

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
    int ifd = fd*10000
    , ifb = fb*10000;
    XY ta_r;
    ta_r.x = ta.x * (texture_shirina);
    ta_r.y = ta.y * (texture_vysota);

    int nxl, nxr, nyv, nyn; /// nxleft, nxright, nxverh, nxniz
    int *temp_p;
    int *temp_t;
//    int *temp_pp;
//                temp_pp = ipixels + resolution.shirina*nyv;
//                    temp_p = temp_pp + nxl;
//                    temp_pp -= resolution.shirina;
    double *temp_z;

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

                    itp.x = (ta_r.x + fx*(a.y - j) + fd*(tr - nxl))*10000;
                    itp.y = (ta_r.y + fy*(a.y - j) + fb*(tr - nxl))*10000;

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            temp_t = (texture + itp.y/10000*texture_shirina + itp.x/10000);
                            if(*((unsigned char*)temp_t + 3) == 255){
                                *temp_z++ = l;
                                *temp_p++ = *temp_t;
                            }
                            else{
                                temp_z++;
                                temp_p++;
                            }
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        itp.x -= ifd;
                        itp.y -= ifb;
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

                    itp.x = (ta_r.x + fx*(a.y - j) + fd*(tr - nxl))*10000;
                    itp.y = (ta_r.y + fy*(a.y - j) + fb*(tr - nxl))*10000;

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            temp_t = (texture + itp.y/10000*texture_shirina + itp.x/10000);
                            if(*((unsigned char*)temp_t + 3) == 255){
                                *temp_z++ = l;
                                *temp_p++ = *temp_t;
                            }
                            else{
                                temp_z++;
                                temp_p++;
                            }
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        itp.x -= ifd;
                        itp.y -= ifb;
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

                    itp.x = (ta_r.x + fx*(a.y - j) + fd*(tr - nxl))*10000;
                    itp.y = (ta_r.y + fy*(a.y - j) + fb*(tr - nxl))*10000;

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            temp_t = (texture + itp.y/10000*texture_shirina + itp.x/10000);
                            if(*((unsigned char*)temp_t + 3) == 255){
                                *temp_z++ = l;
                                *temp_p++ = *temp_t;
                            }
                            else{
                                temp_z++;
                                temp_p++;
                            }
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        itp.x -= ifd;
                        itp.y -= ifb;
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

                    itp.x = (ta_r.x + fx*(a.y - j) + fd*(nxl - tl))*10000;
                    itp.y = (ta_r.y + fy*(a.y - j) + fb*(nxl - tl))*10000;

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            temp_t = (texture + itp.y/10000*texture_shirina + itp.x/10000);
                            if(*((unsigned char*)temp_t + 3) == 255){
                                *temp_z++ = l;
                                *temp_p++ = *temp_t;
                            }
                            else{
                                temp_z++;
                                temp_p++;
                            }
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        itp.x += ifd;
                        itp.y += ifb;
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

                    itp.x = (ta_r.x + fx*(a.y - j) + fd*(nxl - tl))*10000;
                    itp.y = (ta_r.y + fy*(a.y - j) + fb*(nxl - tl))*10000;

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            temp_t = (texture + itp.y/10000*texture_shirina + itp.x/10000);
                            if(*((unsigned char*)temp_t + 3) == 255){
                                *temp_z++ = l;
                                *temp_p++ = *temp_t;
                            }
                            else{
                                temp_z++;
                                temp_p++;
                            }
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        itp.x += ifd;
                        itp.y += ifb;
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

                    itp.x = (ta_r.x + fx*(a.y - j) + fd*(nxl - tl))*10000;
                    itp.y = (ta_r.y + fy*(a.y - j) + fb*(nxl - tl))*10000;

                    temp_z = z_buffer + resolution.shirina*j + nxl;
                    for(int i = nxl; i <= nxr; i++){
                        if(l < *temp_z){
                            temp_t = (texture + itp.y/10000*texture_shirina + itp.x/10000);
                            if(*((unsigned char*)temp_t + 3) == 255){
                                *temp_z++ = l;
                                *temp_p++ = *temp_t;
                            }
                            else{
                                temp_z++;
                                temp_p++;
                            }
                        }
                        else{
                            temp_z++;
                            temp_p++;
                        }
                        itp.x += ifd;
                        itp.y += ifb;
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
