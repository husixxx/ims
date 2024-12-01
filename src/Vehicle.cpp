#include "Vehicle.h"
#include <iostream>

void Vehicle::Behavior()
{
    while (true)
    {

        if (currentLoad < maxCapacity)
        {
            std::cout << "Vozidlo " << id << " čeká na balíky.\n";
            Wait(1);
            continue;
        }

        std::cout << "Vozidlo " << id << " začíná rozvoz.\n";

        for (auto &package : packages)
        {
            // Simulace doručení balíku

            if (vehicleType == ELECTRIC)
            {
                if (!CanDeliver(package->distance))
                {                          // 20% kapacity baterie
                    double chargingDistance = Exponential(2); // Vzdálenost k nabíječce
                    stats.totalCo2Emitted += chargingDistance * 0.08 * 2.31; // Emise CO2 pro spalovací vozidlo
                    Wait(chargingDistance / speed * 60.0); // cesta na nabijecku
                    ChargeBattery();
                }
                
                batteryRemaining -= package->distance * 0.2;        // Spotřeba baterie pro e-auto (0.2 kWh/km)
                double emissions = package->distance * 0.2 * 0.233; // Emise CO2 pro e-auto (0.2 kWh/km * 0.233 kg CO2/kWh)
                stats.totalCo2Emitted += emissions;
            }
            else
            {
                if (!CanDeliver(package->distance))
                {
                    double pumpDistance = Exponential(5); // Vzdálenost k pumpě
                    stats.totalCo2Emitted += pumpDistance * 0.08 * 2.31; // Emise CO2 pro spalovací vozidlo
                    stats.totalFuelConsumed += pumpDistance * 0.08;  // Spotřeba paliva pro spalovací vozidlo (8 l/100 km)
                    Wait(pumpDistance / speed * 60.0); // cesta na pumpu
                    RefillFuel();
                }

                fuelRemaining -= package->distance * 0.08; // Spotřeba paliva pro spalovací vozidlo (8 l/100 km)
                stats.totalFuelConsumed += package->distance * 0.08;  // Spotřeba paliva pro spalovací vozidlo (8 l/100 km)
                stats.totalCo2Emitted += package->distance * 0.08 * 2.31; // Emise CO2 pro spalovací vozidlo
            }

            Wait(package->distance / speed * 60.0); // Čas doručení balíku na základě vzdálenosti

            std::cout << "Balík " << package->id << " doručen.\n";
            
            stats.totalPackagesDelivered++;
            stats.totalDistanceTravelled += package->distance;
            distanceToReturn = package->distance; // Nastavení vzdálenosti zpět (do depa)
        }

        packages.clear();
        currentLoad = 0;

        // Návrat do depa
        Wait(distanceToReturn / speed * 60.0);
        stats.totalDistanceTravelled += distanceToReturn;
        if (vehicleType == ELECTRIC)
        {
            stats.totalCo2Emitted += distanceToReturn * 0.08 * 2.31; // Emise CO2 pro spalovací vozidlo
            ChargeBattery();                                         // Nabíjení pro elektrické vozidlo
        }
        else
        {
            stats.totalCo2Emitted += distanceToReturn * 0.08 * 0.233; // Emise CO2 pro spalovací vozidlo
            stats.totalFuelConsumed += distanceToReturn * 0.08;
            RefillFuel(); // Tankování pro spalovací vozidlo
        }

        // Znovu zařazení do fronty
        if (vehicleType == ELECTRIC)
        {
            Into(eVehicleQueue);
        }
        else
        {
            Into(vehicleQueue);
        }
    }
}

void Vehicle::ChargeBattery()
{
    std::cout << "Vozidlo " << id << " se nabíjí.\n";
    Wait(Exponential(2 * 60));          // Simulace nabíjení (2 hodiny)
    batteryRemaining = batteryCapacity; // Naplnění baterie na plnou kapacitu
}

void Vehicle::RefillFuel()
{
    std::cout << "Vozidlo " << id << " se tankuje.\n";
    Wait(Exponential(15)); // Simulace tankování (30 minut)
    fuelRemaining = fuelCapacity;
}

bool Vehicle::CanDeliver(double distance)
{
    if (vehicleType == ELECTRIC)
    {
        return batteryRemaining >= distance * 0.2; // Pro e-auta: Zda je dostatek baterie na doručení
    }
    else
    {
        return fuelRemaining >= distance * 0.08; // Pro spalovací auta: Zda je dostatek paliva na doručení
    }

}

void Vehicle::LoadPackage(Package *p)
{
    currentLoad++;
    if (currentLoad > maxCapacity)
    {
        std::cerr << "Překročena kapacita vozidla " << id << "!\n";
        return;
    }
    packages.push_back(p);
    std::cout << "Balík " << p->id << " naložen do vozidla.\n";
}