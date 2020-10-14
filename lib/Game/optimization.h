int KvadroDerevo(int *num, int stepen)
{
    int dlina[stepen + 1];
    for(int i = 0; i <= stepen; i++){
        dlina[i] = fast_pow(2, i);
        cout << "2^" << i << " = " << dlina[i] << endl;
    }
    cout << endl;
    int pos = 0;
    int ypos = 0;
    int xpos = 0;
    for(int i = 0; i < stepen; i++){
        ypos += num[i]/2 * dlina[stepen - 1 - i];
        cout << "1) ypos = " << ypos << endl;
        if(num[i] == 1 || num[i] == 3){
            xpos += dlina[stepen - 1 - i];
            cout << "2) xpos = " << xpos << endl;
        }
    }
    pos = ypos * dlina[stepen] + xpos;
    cout << "pos = " << pos << endl;
    return pos;
}

/**
    while(1){
        int stepen;
        cin >> stepen;
        if(stepen < 0)
            return 0;
        int num[stepen];
        cout << "Enter num" << endl;
        for(int i = 0; i < stepen; i++)
            cin >> num[i];
        KvadroDerevo(num, stepen);
        cout << "----//----//----//----" << endl;
    }
    return 0;
**/
