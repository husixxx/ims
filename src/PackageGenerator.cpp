#include "PackageGenerator.h"
#include "Package.h"
#include "globals.h"

// Globální proměnná pro počítání generovaných balíků
extern int i;

void PackageGenerator::Behavior()
{

    std::string size = (rand() % 2 == 0) ? "Malý" : "Velký";

    // Generování vzdálenosti pro město Bratislava (1-15 km)
    double distance;
    double prob = Random();

    
    if (prob < 0.7)
    {
        distance = 5 + Exponential(1); 
    }
    
    else if (prob < 0.9)
    {
        distance = 10 + Exponential(2); 
    }
    
    else
    {
        distance = 15 + Exponential(3); 
    }

    
    std::string priority = (rand() % 2 == 0) ? "Expresní" : "Standardní";

    
    Package *p = new Package("PKG_" + std::to_string(i), size, priority, distance);

    
    p->Activate();
    i++; // Zvyšujeme index pro balíky

    std::cout << "Generován balík " << p->id << " (Velikost: " << size << ", Priorita: " << priority
              << ", Vzdálenost: " << distance << " km)\n";

    
    Activate(Time + Exponential(10)); // Počkej náhodně mezi generováním balíků (průměrně 10 minut)
}