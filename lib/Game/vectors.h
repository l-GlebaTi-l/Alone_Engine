void vct_from_file(XYZ &A, ifstream& file);         // ббнд бейрнпю хг тюикю
void vct_to_file(XYZ &A, ofstream& file);           // бшбнд бейрнпю хг тюикю
XYZ vct_return_tochky(XYZ AB, XYZ A);               // йнмевмюъ рнвйю бейрнпю AB б опнярпюмярбе
XYZ vct_YnC(XYZ A, double k);                       // слмнфемхе мю яйюкъп
XYZ vct_sum(XYZ A, XYZ B);                          // ясллю бейрнпнб
double vct_SP(XYZ A, XYZ B);                        // яйюкъпмне опнхгбедемхе бейрнпнб
double vct_dlina(XYZ A);                            // дкхмю бейрнпю
void vct_enter(XYZ &A);                             // ббнд бейрнпю онкэгнбюрекел
void vct_enter(XYZ &A, double x, double y, double z); // ббнд дюммшу бейрнпю хг рпеу рнвей
void vct_print(XYZ A);                          // бшбнд бейрнпю б йнмянкэ
XYZ vct_is_tocheck(XYZ A, XYZ B);               // мюунфдемхе бейрнпю AB
XYZ vct_perp(XYZ a1, XYZ a2);                   // оепоемдхйскъп й бейрнпюл a1 Х a2    OX * OY = OZ
XYZ vct_ration(XYZ A);                          // мнплюкхгюжхъ бейрнпю
XYZ vct_normal(XYZ ab, XYZ ac);                 // мнплюкэ й бейрнпюл
XYZ vct_orientation(XYZ A);                     // хглемемхе нпхемрюжхх бейрнпю
double vct_ygol(XYZ AB, XYZ AC);                //  йняхмся лефдс бейрнпюлх


void operator--(XYZ &fir)
{
    fir.x = 0;
    fir.y = 0;
    fir.z = 0;
}
XYZ operator+(const XYZ &fir, const XYZ &sec)
{
    XYZ res;
    res.x = fir.x + sec.x;
    res.y = fir.y + sec.y;
    res.z = fir.z + sec.z;
    return res;
}
void operator+=(XYZ &fir, const XYZ &sec)
{
    fir.x += sec.x;
    fir.y += sec.y;
    fir.z += sec.z;
}
void operator-=(XYZ &fir, const XYZ &sec)
{
    fir.x -= sec.x;
    fir.y -= sec.y;
    fir.z -= sec.z;
}
XYZ operator-(const XYZ &fir, const XYZ &sec)
{
    XYZ res;
    res.x = fir.x - sec.x;
    res.y = fir.y - sec.y;
    res.z = fir.z - sec.z;
    return res;
}
XYZ operator-(const XYZ &fir)
{
    XYZ res;
    res.x = -fir.x;
    res.y = -fir.y;
    res.z = -fir.z;
    return res;
}
double operator*(const XYZ &fir, const XYZ &sec)
{
    return fir.x*sec.x + fir.y*sec.y + fir.z*sec.z;
}
XYZ operator*(const XYZ &fir, const double &sec)
{
    XYZ res;
    res.x = fir.x * sec;
    res.y = fir.y * sec;
    res.z = fir.z * sec;
    return res;
}
XYZ operator*(const double &fir, const XYZ &sec)
{
    XYZ res;
    res.x = sec.x * fir;
    res.y = sec.y * fir;
    res.z = sec.z * fir;
    return res;
}
XYZ operator/(const XYZ &fir, const double &sec)
{
    XYZ res;
    res.x = fir.x / sec;
    res.y = fir.y / sec;
    res.z = fir.z / sec;
    return res;
}
void operator/=(XYZ &fir, const double &sec)
{
    fir.x /= sec;
    fir.y /= sec;
    fir.z /= sec;
}
void operator*=(XYZ &fir, const double &sec)
{
    fir.x *= sec;
    fir.y *= sec;
    fir.z *= sec;
}
XYZ operator ^(const XYZ &a, const XYZ &b)
{
    XYZ p;
    p.x = a.y*b.z - a.z*b.y;
    p.y = a.z*b.x - a.x*b.z;
    p.z = a.x*b.y - a.y*b.x;
    return p;
}
bool operator ==(const XYZ &a, const double &k)
{
    if(a.x == k)
        if(a.y == k)
            if(a.z == k)
                return 1;
    return 0;
}
bool operator ==(const XYZ &a, const XYZ &b)
{
    if(a.x == b.x)
        if(a.y == b.y)
            if(a.z == b.z)
                return 1;
    return 0;
}
bool operator !=(const XYZ &a, const double &k)
{
    if(a.x != k)
        if(a.y != k)
            if(a.z != k)
                return 1;
    return 0;
}
bool operator !=(const XYZ &a, const XYZ &b)
{
    if(a.x != b.x)
        if(a.y != b.y)
            if(a.z != b.z)
                return 1;
    return 0;
}




void vct_from_file(XYZ &A, ifstream& file)          // ббнд бейрнпю хг тюикю
{
    file >> A.x;
    file >> A.y;
    file >> A.z;
}
void vct_to_file(XYZ &A, ofstream& file)            // бшбнд бейрнпю хг тюикю
{
    file << A.x << " " << A.y << " " << A.z;
}
XYZ vct_return_tochky(XYZ AB, XYZ A)                // йнмевмюъ рнвйю бейрнпю AB б опнярпюмярбе
{
    XYZ B;
    B.x = A.x + AB.x;
    B.y = A.y + AB.y;
    B.z = A.z + AB.z;
    return B;
}
XYZ vct_YnC(XYZ A, double k)                        // слмнфемхе мю яйюкъп
{
    A.x = A.x*k;
    A.y = A.y*k;
    A.z = A.z*k;
    return A;
}
XYZ vct_sum(XYZ A, XYZ B)                           // ясллю бейрнпнб
{
    XYZ C;
    C.x = A.x + B.x;
    C.y = A.y + B.y;
    C.z = A.z + B.z;
    return C;
}
double vct_SP(XYZ A, XYZ B)                         // яйюкъпмне опнхгбедемхе бейрнпнб
{
    return A.x*B.x + A.y*B.y + A.z*B.z;
}
double vct_dlinaF(XYZ A)                             // дкхмю бейрнпю
{
    return SqrtInv(A.x*A.x + A.y*A.y + A.z*A.z);
}
double vct_dlina(XYZ A)                             // дкхмю бейрнпю
{
    return SqrtInv(A.x*A.x + A.y*A.y + A.z*A.z);
}
void vct_enter(XYZ &A)                              // ббнд бейрнпю онкэгнбюрекел
{
    cout << "Enter vector:" << endl;
    cin >> A.x >> A.y >> A.z;
}
void vct_enter(XYZ &A, double x, double y, double z) // ббнд дюммшу бейрнпю хг рпеу рнвей
{
    A.x = x;
    A.y = y;
    A.z = z;
}
void vct_print(XYZ A)                           // бшбнд бейрнпю б йнмянкэ
{
    cout << A.x << " ";
    cout << A.y << " ";
    cout << A.z << endl;
}
XYZ vct_is_tocheck(XYZ A, XYZ B)                // мюунфдемхе бейрнпю AB
{
    XYZ ab;
    ab.x = B.x - A.x;
    ab.y = B.y - A.y;
    ab.z = B.z - A.z;
    return ab;
}
XYZ vct_perp(XYZ a1, XYZ a2)                    // оепоемдхйскъп й бейрнпюл a1 Х a2    OX * OY = OZ
{
    XYZ p;
    p.x = a1.y*a2.z - a1.z*a2.y;
    p.y = a1.z*a2.x - a1.x*a2.z;
    p.z = a1.x*a2.y - a1.y*a2.x;
    return p;
}
XYZ vct_rationF(XYZ A)                           // мнплюкхгюжхъ бейрнпю
{
    double l;
    l = A.x*A.x + A.y*A.y + A.z*A.z;
    l = SqrtInvE(l);
    A.x = A.x*l;
    A.y = A.y*l;
    A.z = A.z*l;
    return A;
}
XYZ vct_ration(XYZ A)                           // мнплюкхгюжхъ бейрнпю
{
    double l;
    l = A.x*A.x + A.y*A.y + A.z*A.z;
    l = sqrt(l);
    if(l == 0){
//        cout << "RATION ERROR. SOMETHING == 0" << endl;
        return A;
    }
    A.x = A.x/l;
    A.y = A.y/l;
    A.z = A.z/l;
    return A;
}
XYZ vct_normal(XYZ ab, XYZ ac)                  // мнплюкэ й бейрнпюл
{
    XYZ n;
    n = vct_perp(ab, ac);
    n = vct_ration(n);
    return n;
}
XYZ vct_orientation(XYZ A)                      // хглемемхе нпхемрюжхх бейрнпю
{
    A.x = -A.x;
    A.y = -A.y;
    A.z = -A.z;
    return A;
}
double vct_ygol(XYZ AB, XYZ AC)                 //  йняхмся лефдс бейрнпюлх
{
    double cosBAC;
    AB = vct_ration(AB);
    AC = vct_ration(AC);
    cosBAC = vct_SP(AB,AC);
    return cosBAC;
}
XYZ vct_otrazeniya(XYZ a, XYZ n)
{
    XYZ p;
    n = vct_ration(n);
    p = n * vct_SP(a,n);
    return a - (p*2);
}
