unsigned char *loadBMP_32bit( const char *fname, int &mx, int &my );

unsigned char *loadBMP( const char *fname, int &mx, int &my )
{
    mx = my = -1;
    FILE *f = fopen( fname, "rb" );
    if( !f ) return NULL;
    BITMAPFILEHEADER bmpfhead;
    BITMAPINFOHEADER bmphead;

    size_t res;

    res = fread( &bmpfhead, 1, sizeof(BITMAPFILEHEADER), f );
    if(PARAM_Console_On == 1){
        cout << endl <<
        "bfType = " << bmpfhead.bfType << endl <<
        "bfSize = " << bmpfhead.bfSize << endl <<
        "bfReserved1 = " << bmpfhead.bfReserved1 << endl <<
        "bfReserved2 = " << bmpfhead.bfReserved2 << endl <<
        "bfOffBits = " << bmpfhead.bfOffBits << endl <<
        endl;
    }
    res += fread( &bmphead, 1, sizeof(BITMAPINFOHEADER), f );
    if( res != sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER) ){
        if(PARAM_Console_On == 1)
            cout << "File memory error" << endl;
        fclose(f);
        return NULL;
    }

    if(PARAM_Console_On == 1)
        cout << "opened" << endl;

    fseek( f, 0, SEEK_END);
    int filesize = ftell(f);

    fseek( f, bmpfhead.bfOffBits, SEEK_SET);

    if(PARAM_Console_On == 1){
        cout << endl <<
        "filesize = " << filesize << endl <<
        "biSize = " << bmphead.biSize << endl <<
        "biWidth = " << bmphead.biWidth << endl <<
        "biHeight = " << bmphead.biHeight << endl <<
        "biPlanes = " << bmphead.biPlanes << endl <<
        "biBitCount = " << bmphead.biBitCount << endl <<
        "biCompression = " << bmphead.biCompression << endl <<
        "biSizeImage = " << bmphead.biSizeImage << endl <<
        "biXPelsPerMeter = " << bmphead.biXPelsPerMeter << endl <<
        "biYPelsPerMeter = " << bmphead.biYPelsPerMeter << endl <<
        "biClrUsed = " << bmphead.biClrUsed << endl <<
        "biClrImportant = " << bmphead.biClrImportant << endl <<
        endl;
    }

    if(
//        bmphead.biSizeImage != filesize - 54 ||
        bmphead.biClrUsed != 0    ||
        bmphead.biPlanes   != 1    ||
       (bmphead.biSize!=40 && bmphead.biSize!=108 && bmphead.biSize!=124)||
        bmpfhead.bfOffBits != 14+bmphead.biSize ||

        bmphead.biWidth <1 || bmphead.biWidth >10000 ||
        bmphead.biHeight<1 || bmphead.biHeight>10000 ||
        bmphead.biBitCount    != 24 ||
        bmphead.biCompression !=  0
        )
    {
        if(bmphead.biBitCount == 32)
            return loadBMP_32bit(fname, mx, my);
        else{
            fclose(f);
            return NULL;
        }
    }
    mx = bmphead.biWidth;
    my = bmphead.biHeight;
    int mx3 = (3*mx+3) & (-4);
    unsigned char *tmp_buf = new unsigned  char[mx3*my];
    res = fread( tmp_buf, 1, mx3*my, f);
    if( (int)res != mx3*my ) { delete []tmp_buf; fclose(f); return NULL; }

    fclose(f);

    if(PARAM_Console_On == 1)
        cout << "mx = " << mx << " my = " << my << endl;
    unsigned char *v = new unsigned char[mx*my*4];

    unsigned char *ptr = v;
    unsigned char *pRow = tmp_buf;
    for(int y = 0; y < my; y++) {
        for(int x = 0; x < mx; x++) {
            *ptr++ = *pRow;
            *ptr++ = *(pRow + 1);
            *ptr++ = *(pRow + 2);
            *ptr++ = 255;
            pRow += 3;
        }
    }
    delete (tmp_buf);
    return v;
}

unsigned char *loadBMP_32bit( const char *fname, int &mx, int &my )
{
    mx = my = -1;
    FILE *f = fopen( fname, "rb" );
    if( !f ) return NULL;
    BITMAPFILEHEADER bmpfhead;
    BITMAPINFOHEADER bmphead;

    size_t res;

    res = fread( &bmpfhead, 1, sizeof(BITMAPFILEHEADER), f );
    if(PARAM_Console_On == 1){
        cout << endl <<
        "bfType = " << bmpfhead.bfType << endl <<
        "bfSize = " << bmpfhead.bfSize << endl <<
        "bfReserved1 = " << bmpfhead.bfReserved1 << endl <<
        "bfReserved2 = " << bmpfhead.bfReserved2 << endl <<
        "bfOffBits = " << bmpfhead.bfOffBits << endl <<
        endl;
    }
    res += fread( &bmphead, 1, sizeof(BITMAPINFOHEADER), f );
    if( res != sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER) ){
        if(PARAM_Console_On == 1)
            cout << "File memory error" << endl;
        fclose(f);
        return NULL;
    }

    if(PARAM_Console_On == 1)
        cout << "opened" << endl;

    fseek( f, 0, SEEK_END);
    int filesize = ftell(f);

    fseek( f, bmpfhead.bfOffBits, SEEK_SET);

    if(PARAM_Console_On == 1){
        cout << endl <<
        "filesize = " << filesize << endl <<
        "biSize = " << bmphead.biSize << endl <<
        "biWidth = " << bmphead.biWidth << endl <<
        "biHeight = " << bmphead.biHeight << endl <<
        "biPlanes = " << bmphead.biPlanes << endl <<
        "biBitCount = " << bmphead.biBitCount << endl <<
        "biCompression = " << bmphead.biCompression << endl <<
        "biSizeImage = " << bmphead.biSizeImage << endl <<
        "biXPelsPerMeter = " << bmphead.biXPelsPerMeter << endl <<
        "biYPelsPerMeter = " << bmphead.biYPelsPerMeter << endl <<
        "biClrUsed = " << bmphead.biClrUsed << endl <<
        "biClrImportant = " << bmphead.biClrImportant << endl <<
        endl;
    }

    if(
//        bmphead.biSizeImage != filesize - 54 ||
        bmphead.biClrUsed != 0    ||
        bmphead.biPlanes   != 1    ||
       (bmphead.biSize!=40 && bmphead.biSize!=108 && bmphead.biSize!=124)||
//        bmpfhead.bfOffBits != 14+bmphead.biSize ||

        bmphead.biWidth <1 || bmphead.biWidth >10000 ||
        bmphead.biHeight<1 || bmphead.biHeight>10000 ||
        bmphead.biBitCount    != 32/* ||
        bmphead.biCompression !=  0*/
        )
    {
            fclose(f);
            return NULL;
    }
    if(PARAM_Console_On == 1)
        cout << "texture is good" << endl;
    mx = bmphead.biWidth;
    my = bmphead.biHeight;
    int mx4 = 4*mx;
    unsigned char *tmp_buf = new unsigned  char[mx4*my];
    res = fread( tmp_buf, 1, mx4*my, f);
    if( (int)res != mx4*my ) { delete []tmp_buf; fclose(f); return NULL; }

    fclose(f);

    if(PARAM_Console_On == 1)
        cout << "mx = " << mx << " my = " << my << endl;
//    unsigned char *v = new unsigned char[mx*my*4];

//    v = tmp_buf;
//    unsigned char *ptr = v;
//    for(int y = my-1; y >= 0; y--) {
//        unsigned char *pRow = tmp_buf + mx4*y;
//        for(int x=0; x< mx; x++) {
//            *ptr++ = *pRow;
//            *ptr++ = *(pRow + 1);
//            *ptr++ = *(pRow + 2);
//            *ptr++ = *(pRow + 3);
//            pRow += 4;
//        }
//    }
//    delete []tmp_buf;
    return (tmp_buf);
}

unsigned char *loadBMP_32bit( const char *fname, int &mx, int &my, int& bittype );

unsigned char *loadBMP( const char *fname, int &mx, int &my, int& bittype )
{
    mx = my = -1;
    FILE *f = fopen( fname, "rb" );
    if( !f ) return NULL;
    BITMAPFILEHEADER bmpfhead;
    BITMAPINFOHEADER bmphead;

    size_t res;

    res = fread( &bmpfhead, 1, sizeof(BITMAPFILEHEADER), f );
    if(PARAM_Console_On == 1){
        cout << endl <<
        "bfType = " << bmpfhead.bfType << endl <<
        "bfSize = " << bmpfhead.bfSize << endl <<
        "bfReserved1 = " << bmpfhead.bfReserved1 << endl <<
        "bfReserved2 = " << bmpfhead.bfReserved2 << endl <<
        "bfOffBits = " << bmpfhead.bfOffBits << endl <<
        endl;
    }
    res += fread( &bmphead, 1, sizeof(BITMAPINFOHEADER), f );
    if( res != sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER) ){
        if(PARAM_Console_On == 1)
            cout << "File memory error" << endl;
        fclose(f);
        return NULL;
    }

    if(PARAM_Console_On == 1)
        cout << "opened" << endl;

    fseek( f, 0, SEEK_END);
    int filesize = ftell(f);

    fseek( f, bmpfhead.bfOffBits, SEEK_SET);

    if(PARAM_Console_On == 1){
        cout << endl <<
        "filesize = " << filesize << endl <<
        "biSize = " << bmphead.biSize << endl <<
        "biWidth = " << bmphead.biWidth << endl <<
        "biHeight = " << bmphead.biHeight << endl <<
        "biPlanes = " << bmphead.biPlanes << endl <<
        "biBitCount = " << bmphead.biBitCount << endl <<
        "biCompression = " << bmphead.biCompression << endl <<
        "biSizeImage = " << bmphead.biSizeImage << endl <<
        "biXPelsPerMeter = " << bmphead.biXPelsPerMeter << endl <<
        "biYPelsPerMeter = " << bmphead.biYPelsPerMeter << endl <<
        "biClrUsed = " << bmphead.biClrUsed << endl <<
        "biClrImportant = " << bmphead.biClrImportant << endl <<
        endl;
    }

    if(
//        bmphead.biSizeImage != filesize - 54 ||
        bmphead.biClrUsed != 0    ||
        bmphead.biPlanes   != 1    ||
       (bmphead.biSize!=40 && bmphead.biSize!=108 && bmphead.biSize!=124)||
        bmpfhead.bfOffBits != 14+bmphead.biSize ||

        bmphead.biWidth <1 || bmphead.biWidth >10000 ||
        bmphead.biHeight<1 || bmphead.biHeight>10000 ||
        bmphead.biBitCount    != 24 ||
        bmphead.biCompression !=  0
        )
    {
        if(bmphead.biBitCount == 32)
            return loadBMP_32bit(fname, mx, my, bittype);
        else{
            fclose(f);
            return NULL;
        }
    }
    mx = bmphead.biWidth;
    my = bmphead.biHeight;
    int mx3 = (3*mx+3) & (-4);
    unsigned char *tmp_buf = new unsigned  char[mx3*my];
    res = fread( tmp_buf, 1, mx3*my, f);
    if( (int)res != mx3*my ) { delete []tmp_buf; fclose(f); return NULL; }

    fclose(f);

    if(PARAM_Console_On == 1)
        cout << "mx = " << mx << " my = " << my << endl;
    unsigned char *v = new unsigned char[mx*my*4];

    unsigned char *ptr = v;
    unsigned char *pRow = tmp_buf;
    for(int y = 0; y < my; y++) {
        for(int x = 0; x < mx; x++) {
            *ptr++ = *pRow;
            *ptr++ = *(pRow + 1);
            *ptr++ = *(pRow + 2);
            *ptr++ = 255;
            pRow += 3;
        }
    }
    delete (tmp_buf);
    bittype = 24;
    return v;
}

unsigned char *loadBMP_32bit( const char *fname, int &mx, int &my, int& bittype )
{
    mx = my = -1;
    FILE *f = fopen( fname, "rb" );
    if( !f ) return NULL;
    BITMAPFILEHEADER bmpfhead;
    BITMAPINFOHEADER bmphead;

    size_t res;

    res = fread( &bmpfhead, 1, sizeof(BITMAPFILEHEADER), f );
    if(PARAM_Console_On == 1){
        cout << endl <<
        "bfType = " << bmpfhead.bfType << endl <<
        "bfSize = " << bmpfhead.bfSize << endl <<
        "bfReserved1 = " << bmpfhead.bfReserved1 << endl <<
        "bfReserved2 = " << bmpfhead.bfReserved2 << endl <<
        "bfOffBits = " << bmpfhead.bfOffBits << endl <<
        endl;
    }
    res += fread( &bmphead, 1, sizeof(BITMAPINFOHEADER), f );
    if( res != sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER) ){
        if(PARAM_Console_On == 1)
            cout << "File memory error" << endl;
        fclose(f);
        return NULL;
    }

    if(PARAM_Console_On == 1)
        cout << "opened" << endl;

    fseek( f, 0, SEEK_END);
    int filesize = ftell(f);

    fseek( f, bmpfhead.bfOffBits, SEEK_SET);

    if(PARAM_Console_On == 1){
        cout << endl <<
        "filesize = " << filesize << endl <<
        "biSize = " << bmphead.biSize << endl <<
        "biWidth = " << bmphead.biWidth << endl <<
        "biHeight = " << bmphead.biHeight << endl <<
        "biPlanes = " << bmphead.biPlanes << endl <<
        "biBitCount = " << bmphead.biBitCount << endl <<
        "biCompression = " << bmphead.biCompression << endl <<
        "biSizeImage = " << bmphead.biSizeImage << endl <<
        "biXPelsPerMeter = " << bmphead.biXPelsPerMeter << endl <<
        "biYPelsPerMeter = " << bmphead.biYPelsPerMeter << endl <<
        "biClrUsed = " << bmphead.biClrUsed << endl <<
        "biClrImportant = " << bmphead.biClrImportant << endl <<
        endl;
    }

    if(
//        bmphead.biSizeImage != filesize - 54 ||
        bmphead.biClrUsed != 0    ||
        bmphead.biPlanes   != 1    ||
       (bmphead.biSize!=40 && bmphead.biSize!=108 && bmphead.biSize!=124)||
//        bmpfhead.bfOffBits != 14+bmphead.biSize ||

        bmphead.biWidth <1 || bmphead.biWidth >10000 ||
        bmphead.biHeight<1 || bmphead.biHeight>10000 ||
        bmphead.biBitCount    != 32/* ||
        bmphead.biCompression !=  0*/
        )
    {
            fclose(f);
            return NULL;
    }
    if(PARAM_Console_On == 1)
        cout << "texture is good" << endl;
    mx = bmphead.biWidth;
    my = bmphead.biHeight;
    int mx4 = 4*mx;
    unsigned char *tmp_buf = new unsigned  char[mx4*my];
    res = fread( tmp_buf, 1, mx4*my, f);
    if( (int)res != mx4*my ) { delete []tmp_buf; fclose(f); return NULL; }

    fclose(f);

    if(PARAM_Console_On == 1)
        cout << "mx = " << mx << " my = " << my << endl;
//    unsigned char *v = new unsigned char[mx*my*4];

//    v = tmp_buf;
//    unsigned char *ptr = v;
//    for(int y = my-1; y >= 0; y--) {
//        unsigned char *pRow = tmp_buf + mx4*y;
//        for(int x=0; x< mx; x++) {
//            *ptr++ = *pRow;
//            *ptr++ = *(pRow + 1);
//            *ptr++ = *(pRow + 2);
//            *ptr++ = *(pRow + 3);
//            pRow += 4;
//        }
//    }
//    delete []tmp_buf;
    bittype = 32;
    return (tmp_buf);
}

int saveBMP( const char *fname, unsigned char *v, int mx, int my )	// В каждом элементе упаковано все три RGB-байта
{
    BITMAPFILEHEADER bmpfhead;
    BITMAPINFOHEADER bmphead;

//	memset( &bf, 0, sizeof(bmpfhead) );
//	memset( &bh, 0, sizeof(bmphead) );

    int mx3 = (3*mx+3) & (-4);
	int filesize = 54 + my*mx3;

    bmpfhead.bfType = 19778;
    bmpfhead.bfSize = filesize;
    bmpfhead.bfReserved1 = 0;
    bmpfhead.bfReserved2 = 0;
    bmpfhead.bfOffBits = 54;

    bmphead.biSize = 40;
    bmphead.biWidth = mx;
    bmphead.biHeight = my;
    bmphead.biPlanes = 1;
    bmphead.biBitCount = 24;
    bmphead.biCompression = 0;
    bmphead.biSizeImage = 0;
    bmphead.biXPelsPerMeter = 3780;
    bmphead.biYPelsPerMeter = 3780;
    bmphead.biClrUsed = 0;
    bmphead.biClrImportant = 0;

	FILE *f = fopen( fname, "wb" );
	if( !f ) return -1;
//	size_t res;

	// пишем заголовок
	fwrite( &bmpfhead, 1, sizeof(BITMAPFILEHEADER), f );
	fwrite( &bmphead, 1, sizeof(BITMAPINFOHEADER), f );
//	res = fwrite( &bh, 1, sizeof(BMPheader), f );
//	if( res != sizeof(BMPheader) ) { fclose(f); return -1; }

	// приготовим временный буфер
	unsigned char *tmp_buf = new unsigned char[mx3*my];
	// Перенос данных (не забудем про RGB->BGR)
	unsigned char *ptr = v;
	for(int y = 0; y < my; y++) {
		unsigned char *pRow = tmp_buf + mx3*y;
		for(int x = 0; x < mx; x++) {
			*pRow = *ptr++;
			*(pRow + 1) = *ptr++;
			*(pRow + 2) = *ptr++;
			pRow+=3;
			ptr++;
		}
	}
//    unsigned char temp_buf = new unsigned char[mx*my*3];

	fwrite( tmp_buf, 1, mx3*my, f );
	fclose(f);
	delete []tmp_buf;
	return 0;	// OK
}
