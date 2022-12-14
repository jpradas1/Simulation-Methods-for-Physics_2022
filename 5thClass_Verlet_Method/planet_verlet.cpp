#include <iostream>
#include <cmath>

#include "./../Requirements/vector_old.h"

const double g = 9.8; // m/s²

const double GM = 1.0;

class Body{
    public:
        void init(double x0, double y0, double z0, double Vx0, 
                  double Vy0, double Vz0, double m0, double R0);
        void compute_Forces();
        void movement(double dt);
        void boot(double dt);

        double get_x(){return r.x();};
        double get_y(){return r.y();};
        double get_z(){return r.z();};
    private:
        vector3D r, r_old, V, F;
        double m, R;
};

void Body::init(double x0, double y0, double z0, double Vx0, 
                double Vy0, double Vz0, double m0, double R0){
    r.load(x0, y0, z0); V.load(Vx0, Vy0, Vz0);
    m= m0; R= R0;
}

void Body::compute_Forces(){
    double F_aux = GM * m/(pow(r.norm(), 3));
    F = (-F_aux) * r;
}

void Body::boot(double dt){
    r_old = r - V*dt + F * (pow(dt,2)/(2*m));
}

void Body::movement(double dt){
    vector3D r_new;
    r_new += 2*r - r_old + F* (pow(dt,2)/m);
    V = (r_new-r_old)/(2*dt);
    r_old = r; r = r_new;
}

int main(){
    double t, dt=0.1;
    double omega, T, V0, r0=100; 
    double m = 1;
    Body Planet;

    omega = sqrt(GM*pow(r0,-3));
    V0 = omega*r0;
    T = 2*M_PI / omega;

    // double x0, double y0, double z0, double Vx0, 
    // double Vy0, double Vz0, double m0, double R0

    Planet.init(r0, 0 , 0, 0, V0/2, 0, m, 0.15);
    Planet.compute_Forces();
    Planet.boot(dt);

    for(t=0; t<1.1*T; t+= dt){
        std::cout << Planet.get_x() << "\t" << Planet.get_y() << std::endl;
        Planet.compute_Forces();
        Planet.movement(dt);
    }

    return 0;
}