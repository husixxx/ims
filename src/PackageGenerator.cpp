#include "PackageGenerator.h"
// #include "Package.h"
// Propojení s globálními frontami

void PackageGenerator::Behavior()
{
    // Generujeme balíky v náhodných intervalech

    // Generujeme náhodně velikost a prioritu balíku
    std::string size = (rand() % 2 == 0) ? "Malý" : "Velký";              // Náhodná velikost
    std::string priority = (rand() % 3 == 0) ? "Expresní" : "Standardní"; // Náhodná priorita
    
    // Vytvoříme nový balík s ID, velikostí a prioritou
    Package *p = new Package("PKG_" + std::to_string(i), size, priority);
    // Aktivujeme balík, aby šel do procesu nakládky
    p->Activate();
    i++;
    std::cout << "Generován balík " << p->id << " (Velikost: " << size << ", Priorita: " << priority << ")\n";

    // Čekání mezi generováním balíků
    Activate(Time + Exponential(1)); // Počkej náhodně mezi generováním balíků
}
