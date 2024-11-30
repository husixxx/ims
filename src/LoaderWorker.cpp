#include "LoaderWorker.h"

void LoaderWorker::Behavior()
{
    while (true)
    {
        std::cout << "Skladník čeká na balík ve frontě pro nakládku" << std::endl;

        // Zkontrolujeme, zda je fronta prázdná
        if (loadQueue.Empty())
        {
            Wait(1); // Pokud je fronta prázdná, skladník čeká
            continue;
        }

        // Vezmeme první balík z fronty


        if(vehicleQueue.Empty())
        {
            std::cout << "Žádné vozidlo není k dispozici. Čekám na další volné vozidlo.\n";
            Wait(1);
            continue;
        }
        Package *p = (Package *)loadQueue.GetFirst();
        std::cout << "Skladník připravuje balík " << p->id << " k nakládce." << std::endl;
        Vehicle* v = (Vehicle*)vehicleQueue.GetFirst();  // Vezmeme první dostupné vozidlo
        
        if (v->currentLoad >= v->maxCapacity) {
            std::cout << "Vozidlo je plné. Čekám na další volné vozidlo.\n";
            Wait(1);
            continue;
        }

        // Najdeme volné místo pro nakládku (facility)
        int slot = -1;
        while (slot == -1)
        {
            for (int i = 0; i < NUM_LOADING_SLOTS; i++)
            {
                if (!loadingFacility[i].Busy())
                {
                    slot = i;
                    break;
                }
            }

            // Pokud není žádné volné místo, skladník čeká
            if (slot == -1)
            {
                std::cout << "Všechna nakládací místa jsou obsazená. Čekám..." << std::endl;
                Wait(1);
            }
        }

        // Zabíráme volné místo (facility) pro nakládku
        Seize(loadingFacility[slot]);
        std::cout << "Skladník nakládá balík " << p->id << " na místo " << slot << std::endl;

        // Simulace času potřebného k nakládce
        Wait(Exponential(1)); // 3 minuty na nakládku

        // Uvolňujeme místo pro další pracovníky
        Release(loadingFacility[slot]);
        std::cout << "Skladník dokončil nakládku balíku " << p->id << std::endl;
        v->LoadPackage(p);
        if(v->currentLoad < v->maxCapacity)
        {
            v->Into(vehicleQueue);
        }
        p->Activate(); // Aktivujeme balík pro kontrolu

        // Pokud je vozidlo plné, aktivujeme ho pro rozvoz
    }
}
