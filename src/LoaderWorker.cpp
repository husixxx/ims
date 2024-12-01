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
        // std::cout << "Skladník připravuje balík " << p->id << " k nakládce.\n";

        Vehicle *vehicle = nullptr;
        // random assignment of vehicle
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
            // std::cout << "Žádné dostupné vozidlo pro balík " << p->id << ". Čekám...\n";
            p->Into(loadQueue); // return to queue
            Wait(1);
            continue;
        }

        vehicle->LoadPackage(p);
        // load to car
        Wait(Exponential(4));

        if (vehicle->currentLoad < vehicle->maxCapacity)
        {
            vehicle->Into(vehicle->vehicleType == VehicleType::ELECTRIC ? eVehicleQueue : vehicleQueue); // back to vehicle queue
        }
    }
}
