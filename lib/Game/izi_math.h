float SqrtInv(float x);
float SqrtInvE(float x);
float Q_rsqrt2E(float number);
float FastCos(float Alpha);
short CosFastInit();
void CosFastDelete();

float *cos_fast;

float SqrtInv(float x)             /// Практичная (точность sqrt, но быстрее в 2 раза) 41 ms
{
    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f375a86 - (i>>1);
    x = *(float*)&i;
    x = x*(1.5f - xhalf*x*x);
    x = x*(1.5f - xhalf*x*x);
    x = x*(1.5f - xhalf*x*x);
    x=1/x;
    return x;
}
float SqrtInvE(float x)             /// Полная точность, 1/корень 28 ms
{
    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f375a86 - (i>>1);
    x = *(float*)&i;
    x = x*(1.5f - xhalf*x*x);
    x = x*(1.5f - xhalf*x*x);
    x = x*(1.5f - xhalf*x*x);
    return x;
}
float Q_rsqrt2E(float number)     /// Очень практичная, 1/корень, быстрее в 2 раза корня, 15 ms
{
	const float x2 = number * 0.5F;
	const float threehalfs = 1.5F;

	union {
		float f;
		uint32_t i;
	} conv = {number}; // member 'f' set to value of 'number'.
	conv.i  = 0x5f3759df - ( conv.i >> 1 );
	conv.f  *= ( threehalfs - ( x2 * conv.f * conv.f ) );
	return conv.f;
}

float FastCos(float Alpha)
{
    if(Alpha >= 360. || Alpha < 0.)
        Alpha = (int)Alpha % 360;
    return cos_fast[(int)(Alpha*1000)];
}
short CosFastInit()
{
    cos_fast = new float[360000];
    for(int i = 0; i < 360; i++){
        for(int j = 0; j < 1000; j++){
            cos_fast[i*1000 + j] = cos((((i + ((float)j/1000)) * Pi) / 180));
        }
    }
    return 1;
}
void CosFastDelete()
{
    delete(cos_fast);
}

int fast_pow(int a, int b) {
  if(b == 0){
    return 1;
  }
  if(b % 2 == 0){
    return pow(a * a, b / 2);
  }
  return a * pow(a, b - 1);
}
