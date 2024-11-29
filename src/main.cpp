#include "Package.h"
#include "Vehicle.h"
#include "LoaderWorker.h"
#include "ControllerWorker.h"
#include "PackageGenerator.h"  // Zahrnutí pro generátor balíků

int main() {
    Init(0, 10000);  // Inicializace SIMLIB

    // Vytvoření generátoru balíků
    PackageGenerator* generator = new PackageGenerator();
    generator->Activate();  // Aktivace generátoru balíků

    // Vytvoření vozidel
    Vehicle* vehicle1 = new Vehicle(20);  // Vozidlo s kapacitou 20 balíků
    (vehicle1->Into(vehicleQueue));  // Přidání vozidla do fronty vozidel

    // Vytvoření pracovníků pro kontrolu
    ControllerWorker* controller = new ControllerWorker();
    controller->Activate();

    // Vytvoření pracovníků
    LoaderWorker* loader = new LoaderWorker();
    loader->Activate();


    // Spuštění simulace
    Run();
}
