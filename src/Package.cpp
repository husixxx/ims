#include "Package.h"
// Třída pro balíky



void Package::Behavior()
{
    // Proces kontroly balíku (simulace čekání)
    Wait(Exponential(2)); // Čas na kontrolu (např. 2 minuty)
    // Po kontrole balík je připraven na nakládku
    std::cout << "Balík " << id << " automaticky zkontrolovan, čeká na kontrolu." << std::endl;
    Into(checkQueue); // Balík čeká ve frontě na kontrolu
    Passivate();

    std::cout << "Balík " << id << " zkontrolovan, čeká na nakládku." << std::endl;
    Into(loadQueue);
    Passivate();
}