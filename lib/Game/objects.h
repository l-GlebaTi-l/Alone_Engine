enum AnimPlayer { PLSTAY_, PLRUN_, PLJUMP_, PLINCAR_, PLSWEEM_, };  /// what do Player (his animation)
enum AnimCar { CARPARKED_, CARDRIVE_, CARSMOKED_, CARFIRED_ };
enum AnimObj { OBJSTAY_, OBJFIRE_, OBJCRASH_ };

struct World_Objects {
    short g_id;
    short model_id = -1;
    XYZ pos = {0., 0., 0.};
    XYZ EX = {1., 0., 0.};
    XYZ EY = {0., 1., 0.};
    XYZ EZ = {0., 0., 1.};
    AnimObj Animation = OBJSTAY_;
};
struct World_Players {
    short g_id;
    short model_id = -1;
    short health = 100;
    short gun_id = -1;
    XYZ pos = {0., 0., 0.};
    XYZ EX = {1., 0., 0.};
    XYZ EY = {0., 1., 0.};
    XYZ EZ = {0., 0., 1.};
    AnimPlayer Animation = PLSTAY_;
};
struct World_Cars {
    short g_id;
    short model_id = -1;
    short health = 100;
    XYZ pos = {0., 0., 0.};
    XYZ EX = {1., 0., 0.};
    XYZ EY = {0., 1., 0.};
    XYZ EZ = {0., 0., 1.};
    double Wheel_Speed = 0.;
    double skorost = 0.;
    double povorot = 0.;
    AnimCar Animation = CARPARKED_;
};
