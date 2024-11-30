#include "Package.h"
// Třída pro balíky



void Package::Behavior()
{
    std::cout << "Balík " << id << " čeká na kontrolu." << std::endl;
    // Proces kontroly balíku (simulace čekání)
    Seize(controller); // Balík je vyzvednut pracovníkem
        Wait(Exponential(1)); // Čekání na kontrolu balíku
        std::cout << "Balík " << id << " zkontrolovan, čeká na naklad." << std::endl;
    Release(controller); // Uvolnění pracovníka

    std::cout << "Balík " << id << " zkontrolovan, čeká na nakládku." << std::endl;
    Into(loadQueue);
    Passivate();
    // Passivate();
}