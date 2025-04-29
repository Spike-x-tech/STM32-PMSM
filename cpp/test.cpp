#include<iostream>
#include<string>
#include<math.h>
using namespace std;

void swap(int &x, int &y){
    int z;
    z = x;
    x = y;
    y = z;
};

class Car
{
    public:
    int speed(int maxSpeed);
    void myMethod(){
        cout << "Hello World" << endl;
    }
    string brand;
    string model;
    int year;
    Car(string x, string y, int z);
};

int Car::speed(int maxSpeed){
    return maxSpeed;
}

Car::Car(string x, string y, int z){
    brand = x;
    model = y;
    year = z;
}
int main()
{
    int x= 5, y = 4;
    swap(x, y);
    cout << x << y << endl;

    Car carObj1("BMW", "X5", 2001);
    cout << carObj1.speed(200) << endl;
    carObj1.myMethod();
    return 0;
}