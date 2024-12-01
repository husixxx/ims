#include "Package.h"
#include "Vehicle.h"
#include "LoaderWorker.h"
#include "PackageGenerator.h" // Zahrnutí pro generátor balíků
// Facility loadingFacility[NUM_LOADING_SLOTS];  // Pole pro facilities
Facility controller("Controller worker facility"); // Facility pro kontrolu balíků
Queue loadQueue("Loading packages queue");         // Store pro čekající balíky
Queue checkQueue("Checking packages queue");       // Fronta pro balíky čekající na kontrolu
Queue eVehicleQueue("Fronta elektro vozidel pro město");
Queue vehicleQueue("Fronta dizlovych vozidel");
// Fronta pro vozidla čekající na nakládku
SimulationStats stats;

int main()
{
    // seed pro generování náhodných čísel
    RandomSeed(time(NULL));
    Init(0, 1080); // Inicializace SIMLIB

    // Vytvoření generátoru balíků
    PackageGenerator *generator = new PackageGenerator();
    generator->Activate(); // Aktivace generátoru balíků

    Vehicle *vehicle1 = new Vehicle("1", VehicleType::COMBUSTION, 8.0, 300.0, 25.0, 40.0, 55.0); // Vozidlo s kapacitou 20 balíků
    Vehicle *vehicle2 = new Vehicle("2", VehicleType::COMBUSTION, 8.0, 300.0, 25.0, 40.0, 55.0); // Vozidlo s kapacitou 20 balíků
    Vehicle *vehicle3 = new Vehicle("3", VehicleType::ELECTRIC, 0.0, 300.0, 20.0, 40.0, 0.0); // Vozidlo s kapacitou 20 balíků

    vehicle1->Activate();           // Aktivace vozidla
    vehicle2->Activate();           // Aktivace vozidla
    vehicle3->Activate();           // Aktivace vozidla
    (vehicle1->Into(vehicleQueue)); // Přidání vozidla do fronty vozidel
    (vehicle2->Into(vehicleQueue)); // Přidání vozidla do fronty vozidel
    (vehicle3->Into(vehicleQueue)); // Přidání vozidla do fronty vozidel

    // Vytvoření pracovníků
    LoaderWorker *loader = new LoaderWorker();
    loader->Activate();
    LoaderWorker *loader2 = new LoaderWorker();
    loader2->Activate();
    LoaderWorker *loader3 = new LoaderWorker();
    loader3->Activate();

    // Spuštění simulace
    Run();

    // loader->Output();  // Nastavení fronty pro pracovníka
    // loader2->Output();  // Nastavení fronty pro pracovníka

    // cityVehicleQueue.Output();  // Nastavení fronty pro vozidla čekající na nakládku
    // ruralVehicleQueue.Output();  // Nastavení fronty pro vozidla čekající na nakládku
    std::cout << "\n=== Statistika simulace ===\n";
    std::cout << "Celková spotřeba benzínu: " << stats.totalFuelConsumed << " litrů\n";
    std::cout << "Celkové emise CO2: " << stats.totalCo2Emitted << " kg\n";
    std::cout << "Celková projetá vzdálenost: " << stats.totalDistanceTravelled << " km\n";
    std::cout << "Celkový počet doručených balíků: " << stats.totalPackagesDelivered << "\n";
    std::cout << "===========================\n";

    controller.Output(); // Nastavení fronty pro kontrolu balíků
    checkQueue.Output(); // Nastavení fronty pro čekající balíky
    loadQueue.Output();  // Nastavení fronty pro čekající balíky
}
