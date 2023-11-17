#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct RoutePoint
{
    double xKm;
    double yKm;
    string name;
};

class IVehicle
{
public:
    virtual bool drive(int kilometrs) = 0;
    virtual void refuel() = 0;
    virtual void printStatus() = 0;
};

class AbstractCar : public IVehicle
{
protected:
    double totalDistance;
    double fuelLevel;
    double fuelConsumption;
    double maxFuel;

public:
    AbstractCar(double fuelConsumption, double maxFuel)
        : totalDistance(0), fuelLevel(0), fuelConsumption(fuelConsumption), maxFuel(maxFuel) {}

    bool drive(int kilometers) override {
        double requiredFuel = (kilometers * fuelConsumption) / 100;
        if (fuelLevel < requiredFuel) {
            std::cout << "Недостаточно топлива для прохождения дистанции." << std::endl;
            return false;
        }
        else {
            totalDistance += kilometers;
            fuelLevel -= requiredFuel;
            return true;
        }

    }

    void refuel() override {
        fuelLevel = maxFuel;
        std::cout << "Бак заполнен" << std::endl;
    }

    void printStatus() override {
        std::cout << "Общий пробег: " << totalDistance << " км" << std::endl;
        std::cout << "Остаток топлива в баке: " << fuelLevel << " литров" << std::endl;
    }
};

class Sedan : public AbstractCar
{
public:
    Sedan()
        : AbstractCar(8, 60)
    {}
};

class SUV : public AbstractCar
{
public:
    SUV()
        : AbstractCar(10, 70)
    {}
};

class Bus : public AbstractCar
{
public:
    Bus()
        : AbstractCar(15, 150)
    {}
};

class Bicycle : public IVehicle
{
private:
    int totalDistance = 0;
public:
    int get_totalDistance()
    {
        return totalDistance;
    }

    bool drive(int kilometrs) override
    {
        totalDistance += kilometrs;
        return true;
    }

    void refuel() override {};

    void printStatus()
    {
        cout << "Общий пробег: " << get_totalDistance() << "km" << endl;
    }
};

class Route
{
private:
    vector<RoutePoint> points;
public:
    void addPoint(const RoutePoint& point)
    {
        points.push_back(point);
    }
    void run(IVehicle* vehicle) {
        if (points.size() < 2)
        {
            cout << "there is less than 2 points";
        }
        else
        {
            for (int i = 1; i < points.size(); i++)
            {
                int distance = round(sqrt(pow(points[i - 1].xKm - points[i].xKm, 2) + pow(points[i - 1].yKm - points[i].yKm, 2)));
                bool driveSuccess = vehicle->drive(distance);
                if (!driveSuccess)
                {
                    vehicle->refuel();
                    vehicle->drive(distance);
                }
                vehicle->printStatus();
            }
        }
    }
};

int main()
{
    setlocale(LC_ALL, "RUS");
    Route routes[2];
    routes[0].addPoint({ 0, 0, "Point 1" });
    routes[0].addPoint({ 100, 0, "Point 2" });
    routes[0].addPoint({ 200, 100, "Point 3" });
    routes[0].addPoint({ 300, 300, "Point 4" });
    routes[0].addPoint({ 100, 400, "Point 5" });
    routes[0].addPoint({ 0, 450, "Point 6" });


    routes[1].addPoint({ 0, 0, "Moscow" });
    routes[1].addPoint({ 0, 540, "Voronezh" });
    routes[1].addPoint({ 420, 540, "Saratov" });

    IVehicle* vehicles[4] = { new Bus, new SUV, new Sedan, new Bicycle };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            routes[j].run(vehicles[i]);
            cout << "\n\n";
        }
    }
    return 0;
}