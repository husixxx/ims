#include "ControllerWorker.h"

void ControllerWorker::Behavior()
{
    while (true)
    {
        if (!checkQueue.Empty())
        {
            Package *p = (Package *)checkQueue.GetFirst();
            std::cout << "Pracovník zpracovává balík " << p->id << std::endl;
            Wait(Exponential(3));
            std::cout << "Pracovník zpracoval balík " << p->id << std::endl;
            p->Activate();
        }
    }
}
