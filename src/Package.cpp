#include "Package.h"

void Package::Behavior()
{
    // std::cout << "Balík " << id << " čeká na kontrolu." << std::endl;

    Seize(controller); // Balík je vyzvednut pracovníkem
    Wait(Exponential(1));
    Release(controller); // Uvolnění pracovníka
    // std::cout << "Balík " << id << " zkontrolovan, čeká na nakládku." << std::endl;
    Into(loadQueue);
    Passivate();

    Terminate();
}