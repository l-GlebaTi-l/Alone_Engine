/// Po = Point, Pl = Ploskost`, Tr = Treygol`nik, Ob = Object

XYZ Proection_Po_Pl(XYZ O, XYZ T, XYZ P, XYZ n)   // O - точка глаза, T - точка для проекции, P - точка проецируемой плоскости, n - её нормаль
{
    double D, mu;
    T.x = T.x - O.x;
    T.y = T.y - O.y;
    T.z = T.z - O.z;
    D = n.x*P.x + n.y*P.y + n.z*P.z;
    D *= -1;
    mu = ( D + n.x*O.x + n.y*O.y + n.z*O.z ) / -( n.x*T.x + n.y*T.y + n.z*T.z );
    T.x = O.x + T.x*mu;
    T.y = O.y + T.y*mu;
    T.z = O.z + T.z*mu;
    return T;
}

//                 EP = EkP - точка на плоскости "глаза" смотрящего, возвращает вектор до неё
XYZ Proection_Find_EP(XYZ O, XYZ T, XYZ P, XYZ n)   // O - точка глаза, T - точка для проекции, P - точка проецируемой плоскости, n - её нормаль
{
    double D, mu;
    T.x = T.x - O.x;
    T.y = T.y - O.y;
    T.z = T.z - O.z;
    D = n.x*P.x + n.y*P.y + n.z*P.z;
    D *= -1;
    mu = ( D + n.x*O.x + n.y*O.y + n.z*O.z ) / -( n.x*T.x + n.y*T.y + n.z*T.z );
    T.x = O.x - P.x + T.x*mu;
    T.y = O.y - P.y + T.y*mu;
    T.z = O.z - P.z + T.z*mu;
    return T;
}

XYZ Proection_Coordinates(XYZ O, XYZ T, XYZ EO, XYZ EX, double *matrix)
{
    XYZ P;
    XYZ EP; /// YZ EP, x must be = 0!
    P = Proection_Find_EP(O, T, EO, EX);  //  1) + 2)
    EP.x = matrix[0]*P.x + matrix[1]*P.y + matrix[2]*P.z;
    EP.y = matrix[3]*P.x + matrix[4]*P.y + matrix[5]*P.z;
    EP.z = matrix[6]*P.x + matrix[7]*P.y + matrix[8]*P.z;
    return EP;
}

XY Proection_Coordinates_to_2d(XYZ O, XYZ T, XYZ EO, XYZ EX, double *matrix)
{
    XYZ P;
    XY EP; /// YZ EP, x must be = 0!
    P = Proection_Find_EP(O, T, EO, EX);  //  1) + 2)
    EP.x = matrix[0]*P.x + matrix[1]*P.y + matrix[2]*P.z;
    EP.y = matrix[3]*P.x + matrix[4]*P.y + matrix[5]*P.z;
    return EP;
}

void test(XYZ O, XYZ T, XYZ EO, XYZ EX, XYZ EY, XYZ EZ)
{
    double *matrix = new double [9];
    matrix[0] = EX.x;
    matrix[1] = EY.x;
    matrix[2] = EZ.x;
    matrix[3] = EX.y;
    matrix[4] = EY.y;
    matrix[5] = EZ.y;
    matrix[6] = EX.z;
    matrix[7] = EY.z;
    matrix[8] = EZ.z;
    MatrixObratnaya_3d_to_2d_no_mem_lost(matrix);

    XY P;
    P = Proection_Coordinates_to_2d(O, T, EO, EX, matrix);
    cout << "P.x = " << P.x << " P.y = " << P.y << endl;
}
