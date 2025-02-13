#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Car {
public:
    string brand;
    string model;
    double dailyRate;
    int quantity; // Number of available cars

    Car(const string& brand, const string& model, double dailyRate, int quantity)
        : brand(brand), model(model), dailyRate(dailyRate), quantity(quantity) {}
};

class CarRentalSystem {
private:
    vector<Car> cars;

public:
    CarRentalSystem() {
        initializeCars();
    }

    void initializeCars() {
        vector<string> brands = {"Toyota", "Honda", "Ford", "Suzuki", "Mahindra", "Tata", "Volvo", "Volkswagen", "MG"};
        vector<vector<string>> models = {
            {"Camry", "Corolla", "Rav4"},
            {"Accord", "Civic", "Pilot"},
            {"Mustang", "Fusion", "Explorer"},
            {"Swift", "Baleno", "Vitara"},
            {"Scorpio", "XUV500", "Thar"},
            {"Altroz", "Tiago", "Harrier"},
            {"XC90", "S60", "V60"},
            {"Golf", "Passat", "Tiguan"},
            {"Hector", "ZS EV", "Gloster"}
        };

        for (size_t i = 0; i < brands.size(); ++i) {
            for (const auto& model : models[i]) {
                cars.emplace_back(brands[i], model, 30.0 + i * 5.0, 5);
            }
        }
    }

    void displayAvailableCarBrands() const {
        cout << "Available Car Brands:" << endl;
        vector<string> uniqueBrands;
        for (const Car& car : cars) {
            if (find(uniqueBrands.begin(), uniqueBrands.end(), car.brand) == uniqueBrands.end()) {
                uniqueBrands.push_back(car.brand);
                cout << car.brand << endl;
            }
        }
        cout << endl;
    }

    void displayAvailableModelsForBrand(const string& brand) const {
        cout << "Available Models for " << brand << ":" << endl;
        for (const Car& car : cars) {
            if (car.brand == brand) {
                cout << car.model << endl;
            }
        }
        cout << endl;
    }

    void displayAvailableCars() const {
        cout << "Available Cars:" << endl;
        for (const Car& car : cars) {
            cout << car.brand << " " << car.model << " - ₹" << car.dailyRate << " per day | Available: " << car.quantity << endl;
        }
        cout << endl;
    }

    double rentCar(const string& brand, const string& model, int days) {
        for (Car& car : cars) {
            if (car.brand == brand && car.model == model && car.quantity > 0) {
                double totalRent = car.dailyRate * days;
                cout << "Cost per day for " << car.brand << " " << car.model << ": ₹" << car.dailyRate << endl;
                cout << "You have rented a " << car.brand << " " << car.model << " for " << days << " days." << endl;
                cout << "Total Rent: ₹" << totalRent << endl;

                car.quantity--; // Reduce the available quantity

                return totalRent;
            }
        }
        cout << "Car not available for rent or out of stock." << endl;
        return 0.0;
    }

    void returnCar(const string& brand, const string& model) {
        for (Car& car : cars) {
            if (car.brand == brand && car.model == model) {
                cout << "You have returned a " << car.brand << " " << car.model << "." << endl;

                car.quantity++; // Increase the available quantity

                return;
            }
        }
        cout << "Invalid return. Car not found or already returned." << endl;
    }

    const vector<Car>& getCars() const {
        return cars;
    }
};

int main() {
    CarRentalSystem rentalSystem;

    cout << "Welcome to Creative Car Rentals!" << endl;
    rentalSystem.displayAvailableCarBrands();

    string chosenBrand, chosenModel;
    int rentalDays;

    cout << "Enter the brand of the car you want to rent: ";
    cin >> chosenBrand;

    bool validBrand = false;
    for (const Car& car : rentalSystem.getCars()) {
        if (car.brand == chosenBrand) {
            validBrand = true;
            break;
        }
    }

    if (!validBrand) {
        cout << "Invalid brand. Please choose from the available brands." << endl;
        return 1;
    }

    rentalSystem.displayAvailableModelsForBrand(chosenBrand);

    cout << "Enter the model of the car you want to rent: ";
    cin >> chosenModel;

    cout << "Enter the number of days you want to rent the car (max 7 days): ";
    cin >> rentalDays;

    if (rentalDays <= 0 || rentalDays > 7) {
        cout << "Invalid number of days. Please enter a number between 1 and 7." << endl;
        return 1;
    }

    double totalRent = rentalSystem.rentCar(chosenBrand, chosenModel, rentalDays);

    cout << "Thank you for choosing Creative Car Rentals!" << endl;
    cout << "Your total rent is: ₹" << totalRent << endl;

    return 0;
}
