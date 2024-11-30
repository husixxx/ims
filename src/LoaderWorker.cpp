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
        Package *p = (Package *)loadQueue.GetFirst();
        std::cout << "Skladník připravuje balík " << p->id << " k nakládce." << std::endl;

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
        Wait(Exponential(3)); // 3 minuty na nakládku

        // Uvolňujeme místo pro další pracovníky
        Release(loadingFacility[slot]);
        std::cout << "Skladník dokončil nakládku balíku " << p->id << std::endl;

        // Aktivujeme balík pro další krok (rozvoz)
        p->Activate();
    }
}
