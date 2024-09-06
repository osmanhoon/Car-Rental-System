#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Car {
public:
    Car(string mark, string model, string color, string max_speed, int price, int date)
        : mark(mark), model(model), color(color), max_speed(max_speed), price(price), date(date) {}

    string get_model() const { return model; }

private:
    string mark;
    string model;
    string color;
    string max_speed;
    int price;
    int date;
};

class Lessee {
public:
    Lessee(string name, string address, string phone, string id, string license)
        : name(name), address(address), phone(phone), id(id), license(license) {}

    string get_name() const { return name; }

private:
    string name;
    string address;
    string phone;
    string id;
    string license;
};

class Rent {
public:
    Rent(const Car& car)
        : car(car), days(0), total_rent(0) {}

    void run();

private:
    void selectCar();
    void inputRentDays();
    void calculateRent();
    Lessee inputLesseeInfo();
    void displayRentInfo(const Lessee& lessee);

    Car car;
    int days;
    int total_rent;
    unordered_map<int, int> carPrices = {
        {1, 50}, {2, 40}, {3, 45}, {4, 35}, {5, 55},
        {6, 60}, {7, 30}, {8, 25}, {9, 20}, {10, 40}
    };
};

void Rent::selectCar() {
    int carIndex;
    cout << "Please Select a Car: ";
    cin >> carIndex;
    cout << "You have chosen car " << carIndex << endl;
}

void Rent::inputRentDays() {
    cout << "Number of days you wish to rent the car: ";
    cin >> days;
}

void Rent::calculateRent() {
    total_rent = days * carPrices[stoi(car.get_model())];
}

Lessee Rent::inputLesseeInfo() {
    string name;
    cout << "Please enter your name: ";
    cin >> name;
    return Lessee(name, "", "", "", "");
}

void Rent::displayRentInfo(const Lessee& lessee) {
    cout << "Customer Name: " << lessee.get_name() << endl;
    cout << "Car Model: " << car.get_model() << endl;
    cout << "Number of days: " << days << endl;
    cout << "Your Rental Amount is: $" << total_rent << endl;
}

void Rent::run() {
    Lessee lessee = inputLesseeInfo();
    selectCar();
    inputRentDays();
    calculateRent();
    displayRentInfo(lessee);
}

int main() {
    Car car("Tesla", "1", "Red", "200", 100, 2011);
    Rent rent(car);
    rent.run();
    return 0;
}
