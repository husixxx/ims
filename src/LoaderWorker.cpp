#include "LoaderWorker.h"

void LoaderWorker::Behavior()
{
    while (true)
    {
        std::cout << "Skladník čeká na přístup k nakládacímu místu" << std::endl;
        Package *p = (Package *)checkQueue.GetFirst();
        int slot = -1;
    zpet:
        for (int i = 0; i < NUM_LOADING_SLOTS; i++)
        {
            if (!loadingFacility[i].Busy())
            {
                slot = i;
                break;
            }
        }
        if (slot == -1)
        {
            Passivate();
            goto zpet;
        }

        Seize(loadingFacility[slot]);
        std::cout << "Skladník nakládá balík " << p->id << std::endl;
        Wait(Exponential(3));
        std::cout << "Skladník naložil balík" << p->id << std::endl;
        Release(loadingFacility[slot]);

        p->Activate();
    }
}
