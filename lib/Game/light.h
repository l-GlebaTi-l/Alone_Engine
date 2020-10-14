XYZ Rotate_Light(XYZ light, XYZ n, double teta)
{
    n = vct_ration(n);
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
    gdO.x = M[0]*light.x + M[1]*light.y + M[2]*light.z;
    gdO.y = M[3]*light.x + M[4]*light.y + M[5]*light.z;
    gdO.z = M[6]*light.x + M[7]*light.y + M[8]*light.z;
    light = gdO;

    delete(M);
    return light;
}
