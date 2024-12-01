#include "Vehicle.h"
#include <iostream>

void Vehicle::Behavior()
{
    while (true)
    {

        if (currentLoad < maxCapacity) // wait till full
        {
            // std::cout << "Vozidlo " << id << " čeká na balíky.\n";
            Wait(1);
            continue;
        }

        // std::cout << "Vozidlo " << id << " začíná rozvoz.\n";

        for (auto &package : packages)
        {
            // Simulace doručení balíku

            if (vehicleType == ELECTRIC)
            {
                if (!CanDeliver(package->distance))
                {                                             // 20% kapacity baterie
                    double chargingDistance = Exponential(2); // Vzdálenost k nabíječce
                    co2Stat(chargingDistance * 0.08 * 2.31);  // Emise CO2 pro spalovací vozidlo
                    energyStat(chargingDistance * 0.2);       // Spotřeba energie pro e-auto (0.2 kWh/km)
                    Wait(chargingDistance / speed * 60.0);    // cesta na nabijecku
                    ChargeBattery();
                }

                energyStat(package->distance * 0.2);                // Spotřeba energie pro e-auto (0.2 kWh/km)
                batteryRemaining -= package->distance * 0.2;        // Spotřeba baterie pro e-auto (0.2 kWh/km)
                double emissions = package->distance * 0.2 * 0.233; // Emise CO2 pro e-auto (0.2 kWh/km * 0.233 kg CO2/kWh)
                co2Stat(emissions);
                packagesDeliveredElectric++;
            }
            else
            {
                if (!CanDeliver(package->distance))
                {
                    double pumpDistance = Exponential(5); // Vzdálenost k pumpě
                    co2Stat(pumpDistance * 0.08 * 2.31);  // Emise CO2 pro spalovací vozidlo
                    fuelStat(pumpDistance * 0.08);        // Spotřeba paliva pro spalovací vozidlo (8 l/100 km)
                    Wait(pumpDistance / speed * 60.0);    // cesta na pumpu
                    RefillFuel();
                }

                fuelRemaining -= package->distance * 0.08; // Spotřeba paliva pro spalovací vozidlo (8 l/100 km)
                fuelStat(package->distance * 0.08);        // Spotřeba paliva pro spalovací vozidlo (8 l/100 km)
                co2Stat(package->distance * 0.08 * 2.31);  // Emise CO2 pro spalovací vozidlo
                packagesDeliveredFuel++;
            }

            Wait(package->distance / speed * 60.0); // Čas doručení balíku na základě vzdálenosti

            // std::cout << "Balík " << package->id << " doručen.\n";

            packagesStat(1);
            distanceStat(package->distance);
            distanceToReturn = package->distance; // Nastavení vzdálenosti zpět (do depa)
            package->Activate();                  // Aktivace balíku
        }

        packages.clear();
        currentLoad = 0;

        // Návrat do depa
        Wait(distanceToReturn / speed * 60.0);
        distanceStat(distanceToReturn);
        if (vehicleType == ELECTRIC)
        {
            batteryRemaining -= distanceToReturn * 0.2; // Spotřeba baterie pro e-auto (0.2 kWh/km)
            energyStat(distanceToReturn * 0.2);         // Spotřeba energie pro e-auto (0.2 kWh/km)
            co2Stat(distanceToReturn * 0.08 * 2.31);    // Emise CO2 pro spalovací vozidlo
        }
        else
        {
            fuelRemaining -= distanceToReturn * 0.08; // Spotřeba paliva pro spalovací vozidlo (8 l/100 km)
            co2Stat(distanceToReturn * 0.08 * 0.233); // Emise CO2 pro spalovací vozidlo
            fuelStat(distanceToReturn * 0.08);
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
    // std::cout << "Vozidlo " << id << " se nabíjí.\n";
    Wait(Exponential(2 * 60)); // Simulace nabíjení (2 hodiny)
    packagesChargeStat(packagesDeliveredElectric);
    batteryRemaining = batteryCapacity; // Naplnění baterie na plnou kapacitu
    packagesDeliveredElectric = 0;
}

void Vehicle::RefillFuel()
{
    // std::cout << "Vozidlo " << id << " se tankuje.\n";
    Wait(Exponential(15)); // Simulace tankování (30 minut)
    fuelRemaining = fuelCapacity;
    packagesFuelStat(packagesDeliveredFuel);
    packagesDeliveredFuel = 0;
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

    if (p->size == "Velký")
    {
        currentLoad += 2;
    }
    else
    {
        currentLoad++;
    }
    if (currentLoad > maxCapacity)
    {
        // std::cerr << "Překročena kapacita vozidla " << id << "!\n";
        return;
    }
    packages.push_back(p);
    // std::cout << "Balík " << p->id << " naložen do vozidla.\n";
}