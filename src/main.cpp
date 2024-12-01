#include "Package.h"
#include "Vehicle.h"
#include "LoaderWorker.h"
#include "PackageGenerator.h" // Zahrnutí pro generátor balíků
// Facility loadingFacility[NUM_LOADING_SLOTS];  // Pole pro facilities
Facility controller("Controller worker facility"); // Facility pro kontrolu balíků
Queue loadQueue("Loading packages queue");         // Store pro čekající balíky     // Fronta pro balíky čekající na kontrolu
Queue eVehicleQueue("Fronta elektro vozidel pro město");
Queue vehicleQueue("Fronta dizlovych vozidel");
Stat fuelStat("Spotřeba paliva pro jeden balík (l)");
Stat co2Stat("Emise CO2 pro jeden balík (kg)");
Stat distanceStat("Projetá vzdálenost (km) pro balík");
Stat packagesStat("Počet doručených balíků");
Stat packagesChargeStat("Počet doručených balíku na jedno nabití");
Stat packagesFuelStat("Počet doručených balíku na jedno natankování");

Stat energyStat("Spotřeba energie (kWh) pro jeden balík"); // Stat pro spotřebu energie
// Fronta pro vozidla čekající na nakládku

int main()
{
    // seed pro generování náhodných čísel
    RandomSeed(time(NULL));
    Init(0, 518400); // Inicializace SIMLIB

    // Vytvoření generátoru balíků
    PackageGenerator *generator = new PackageGenerator();
    generator->Activate(); // Aktivace generátoru balíků

    Vehicle *vehicle1 = new Vehicle("1", VehicleType::COMBUSTION, 8.0, 300.0, 25.0, 40.0, 55.0); // Vozidlo s kapacitou 20 balíků
    Vehicle *vehicle2 = new Vehicle("2", VehicleType::COMBUSTION, 8.0, 300.0, 25.0, 40.0, 55.0); // Vozidlo s kapacitou 20 balíků
    Vehicle *vehicle3 = new Vehicle("3", VehicleType::ELECTRIC, 0.0, 300.0, 20.0, 40.0, 0.0);    // Vozidlo s kapacitou 20 balíků

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

    // std::cout << "=== Statistika simulace ===\n";
    // std::cout << "Průměrná spotřeba paliva na balík: " << fuelStat.MeanValue() << " l/balík\n";
    // std::cout << "Průměrná spotřeba energie na balík: " << energyStat.MeanValue() << " kWh/balík\n";
    // std::cout << "Počet balíků doručených na jedno nabití: " << (distanceStat.MeanValue() / packagesStat.Sum()) << " balíků\n";
    // std::cout << "Počet balíků doručených na jedno natankování: " << (distanceStat.MeanValue() / vehicle1->fuelCapacity) << " balíků\n";
    // std::cout << "Celkové emise CO2 na jeden balík: " << (co2Stat.MeanValue()) << " kg CO2/balík\n";
    // std::cout << "Celkové emise CO2: " << co2Stat.Sum() << " kg CO2\n";
    // std::cout << "Celkové palivo spotřebované: " << fuelStat.Sum() << " l\n";
    // std::cout << "Celkový počet doručených balíků: " << packagesStat.Sum() << "\n";

    energyStat.Output();         // Nastavení statistiky pro spotřebu energie
    fuelStat.Output();           // Nastavení statistiky pro spotřebu paliva
    co2Stat.Output();            // Nastavení statistiky pro emise CO2
    distanceStat.Output();       // Nastavení statistiky pro projetou vzdálenost
    packagesStat.Output();       // Nastavení statistiky pro počet doručených balíků
    packagesChargeStat.Output(); // Nastavení statistiky pro počet doručených balíků na jedno nabití
    packagesFuelStat.Output();   // Nastavení statistiky pro počet doručených balíků na jedno natankování
    controller.Output();         // Nastavení fronty pro kontrolu balíků
    loadQueue.Output();          // Nastavení fronty pro čekající balíky
}
