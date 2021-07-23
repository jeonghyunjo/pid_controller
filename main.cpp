#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
//fopen(file name, "mode string")

double constant = 1.0; //initial distance = 1m

struct result {
    double vel;
    double distance;
    int error;
};

class PID {
    double kp;
    double ki;
    double kd;

    double distance = 1.0; //m
    int error = 0; //m
    double time = 0.0; //sec
    double vel = 0.0; //m/s
public:
    PID(double a, double b, double c);
    result controller(int a);
};

//Set initial constants
PID::PID(double a, double b, double c) {
    kp = a;
    ki = b;
    kd = c;
}

//Main controller part
result PID::controller(int a) {
    double temp = error;
    error = a; //distance - constant (positive means the front vehicle is farther)
    std::cout << error << std::endl;
    vel = kp * error + ki * ((temp + error) * 0.1) / 2 + kd * ((error - temp) / 0.1);
    distance = distance + vel * 0.1;
    return { vel, distance, error };
}

/*----------------------------------------------------------------------------------------------*/
int main() {
    PID s1(.1, .1, .1);
    std::ofstream myfile;
    myfile.open("data.txt");

    std::srand(std::time(nullptr)); // use current time as seed for random generator
    int random_variable = std::rand();

    for (int i = 0; i < 10000; i++) {
        double time = i * 0.1;

        switch (i) {
        case 0:random_variable = (random_variable%11)%10;
        case 1000:random_variable = (random_variable % 12) % 10 ;
        case 2000:random_variable = (random_variable % 13) % 10 ;
        case 3000:random_variable = (random_variable % 14) % 10 ;
        case 4000:random_variable = (random_variable % 15) % 10 ; 
        case 5000:random_variable = (random_variable % 16) % 10 ;
        case 6000:random_variable = (random_variable % 17) % 10 - 5;
        case 7000:random_variable = (random_variable % 18) % 10 - 5;
        case 8000:random_variable = (random_variable % 19) % 10 - 5;
        case 9000:random_variable = (random_variable % 20) % 10 - 5;
        }

        result res = s1.controller(random_variable);
        myfile << time << " " << res.vel << " " << res.distance << " " << res.error << "\n";
    }

    myfile.close();
    return 0;
}


