#include "Package.h"
#include "Vehicle.h"
#include "LoaderWorker.h"
#include "ControllerWorker.h"
#include "PackageGenerator.h"  // Zahrnutí pro generátor balíků
Facility loadingFacility[NUM_LOADING_SLOTS];  // Pole pro facilities
Queue loadQueue;                           // Store pro čekající balíky
Queue checkQueue;                             // Fronta pro balíky čekající na kontrolu
Queue vehicleQueue;                           // Fronta pro vozidla čekající na nakládku

int main() {
    Init(0, 100);  // Inicializace SIMLIB

    // Vytvoření generátoru balíků
    PackageGenerator* generator = new PackageGenerator();
    generator->Activate();  // Aktivace generátoru balíků


    // (new Package("1", "pico", "mrdko"))->Activate();
    ControllerWorker* controller = new ControllerWorker();
    controller->Activate();
    // // Vytvoření vozidel
    Vehicle* vehicle1 = new Vehicle(20);  // Vozidlo s kapacitou 20 balíků
    Vehicle* vehicle2 = new Vehicle(20);  // Vozidlo s kapacitou 20 balíků
    (vehicle1->Into(vehicleQueue));  // Přidání vozidla do fronty vozidel
    (vehicle2->Into(vehicleQueue));  // Přidání vozidla do fronty vozidel
    vehicle1->Activate();  // Aktivace vozidla
    vehicle2->Activate();  // Aktivace vozidla

    // // Vytvoření pracovníků pro kontrolu

    // // Vytvoření pracovníků
    LoaderWorker* loader = new LoaderWorker();
    loader->Activate();


    // Spuštění simulace
    Run();
}
