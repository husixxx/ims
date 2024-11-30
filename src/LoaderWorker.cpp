#include "LoaderWorker.h"

void LoaderWorker::Behavior()
{
    while (true)
    {
        if (loadQueue.Empty())
        {
            Wait(1);
            continue;
        }

        Package *p = (Package *)loadQueue.GetFirst();
        std::cout << "Skladník připravuje balík " << p->id << " k nakládce.\n";

        Vehicle *vehicle = nullptr;
        // Kontrola dostupnosti e-auta
        if (Random() < 0.5 && !eVehicleQueue.Empty())
        {
            vehicle = (Vehicle *)eVehicleQueue.GetFirst();
        }
        else if (!vehicleQueue.Empty())
        {
            vehicle = (Vehicle *)vehicleQueue.GetFirst();
        }

        if (!vehicle)
        {
            std::cout << "Žádné dostupné vozidlo pro balík " << p->id << ". Čekám...\n";
            p->Into(loadQueue);
            Wait(1);
            continue;
        }
        // Pokud žádné vozidlo není k dispozici
        vehicle->LoadPackage(p);

        Wait(Exponential(4)); // Simulace nakládky balíku (1 minuta)

        if (vehicle->currentLoad < vehicle->maxCapacity)
        {
            vehicle->Into(vehicle->vehicleType == VehicleType::ELECTRIC ? eVehicleQueue : vehicleQueue); // Vozidlo je plně naloženo, začne doručení
        }
    }
}
