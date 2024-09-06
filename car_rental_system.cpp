#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <thread>
#include <chrono>
#include <limits>  // for numeric_limits

using namespace std;

class Car {
public:
    Car(string mark, string model, string color, string max_speed, int price, int date)
        : mark(mark), model(model), color(color), max_speed(max_speed), price(price), date(date) {}

    string get_mark() const { return mark; }
    string get_model() const { return model; }
    string get_color() const { return color; }
    string get_max_speed() const { return max_speed; }
    int get_price() const { return price; }
    int get_date() const { return date; }

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
    string get_address() const { return address; }
    string get_phone() const { return phone; }
    string get_id() const { return id; }
    string get_license() const { return license; }

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
    void displayCarDetails(const string& filename);

    Car car;
    int days;
    int total_rent;
    unordered_map<int, int> carPrices = {
        {1, 50}, {2, 40}, {3, 45}, {4, 35}, {5, 55},
        {6, 60}, {7, 30}, {8, 25}, {9, 20}, {10, 40}
    };
};

void Rent::selectCar() {
    int carIndex = 0;
    while (true) {
        cout << "\t\t\t\tPlease Select a Car" << endl;
        cout << "\t\t\t\t1. Tesla 2011" << endl;
        cout << "\t\t\t\t2. Hyundai 2015" << endl;
        cout << "\t\t\t\t3. Ford 2017" << endl;
        cout << "\t\t\t\t4. Kia 2018" << endl;
        cout << "\t\t\t\t5. BMW 2019" << endl;
        cout << "\t\t\t\t6. Mercedes 2012" << endl;
        cout << "\t\t\t\t7. TOYOTA 2013" << endl;
        cout << "\t\t\t\t8. FIAT 2016" << endl;
        cout << "\t\t\t\t9. SUZUKI 2020" << endl;
        cout << "\t\t\t\t10. SKODA 2014" << endl;
        cout << "\t\t\t\tChoose one of the Cars from these above options: ";
        cin >> carIndex;

        if (cin.fail() || carIndex < 1 || carIndex > 10) {
            cout << "Invalid Car Model. Please try again!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            displayCarDetails(to_string(carIndex) + ".txt");
            break;
        }
    }
    cout << "--------------------------------------------------------------------------" << endl;
}

void Rent::inputRentDays() {
    cout << "Number of days you wish to rent the car: ";
    while (true) {
        cin >> days;
        if (cin.fail() || days <= 0) {
            cout << "Invalid number of days. Please enter a positive integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    cout << endl;
}

void Rent::calculateRent() {
    cout << "Calculating rent. Please wait..." << endl;
    this_thread::sleep_for(chrono::seconds(1)); // Simulate processing delay

    total_rent = days * carPrices[stoi(car.get_model())];
}

Lessee Rent::inputLesseeInfo() {
    string name, address, phone, id, license;

    cout << "\t\t\t\tPlease enter your name: ";
    cin.ignore();
    getline(cin, name);
    cout << "\t\t\t\tPlease enter your address: ";
    getline(cin, address);
    cout << "\t\t\t\tPlease enter your phone: ";
    getline(cin, phone);
    cout << "\t\t\t\tPlease enter your id: ";
    getline(cin, id);
    cout << "\t\t\t\tPlease enter your license: ";
    getline(cin, license);
    cout << endl;

    return Lessee(name, address, phone, id, license);
}

void Rent::displayRentInfo(const Lessee& lessee) {
    cout << "\n\t\t                     Your Information                 " << endl;
    cout << "\t\t\t\tCustomer Name: " << lessee.get_name() << endl;
    cout << "\t\t\t\tCar Model: " << car.get_model() << endl;
    cout << "\t\t\t\tCar No.: " << car.get_date() << endl;
    cout << "\t\t\t\tNumber of days: " << days << endl;
    cout << "\t\t\t\tYour Rental Amount is: $" << total_rent << endl;
}

void Rent::run() {
    Lessee lessee = inputLesseeInfo();
    selectCar();
    inputRentDays();
    calculateRent();
    displayRentInfo(lessee);
}

void Rent::displayCarDetails(const string& filename) {
    cout << "You have chosen car from file: " << filename << endl;
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file: " << filename << endl;
        return;
    }
    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }
}

class Welcome {
public:
    Welcome() {
        ifstream in("welcome.txt");
        if (!in) {
            cout << "Cannot open input file." << endl;
            return;
        }
        string line;
        while (getline(in, line)) {
            cout << line << endl;
        }
        in.close();
        this_thread::sleep_for(chrono::seconds(1));
        cout << "\nStarting the program please wait..." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "\nLoading up files..." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        system("CLS");
    }
};

int main() {
    Welcome welcome;
    Car car("Tesla", "1", "Red", "200", 100, 2011); // Model index passed as string "1"
    Rent rent(car);
    rent.run();
    return 0;
}

