#include "PackageGenerator.h"
#include "Package.h"
#include "globals.h"

// Globální proměnná pro počítání generovaných balíků
extern int i;

void PackageGenerator::Behavior() {
    // Generování balíků v náhodných intervalech
    
        // Generujeme náhodně velikost balíku (Malý nebo Velký)
        std::string size = (rand() % 2 == 0) ? "Malý" : "Velký"; 

        // Generování vzdálenosti pro město Bratislava (1-15 km)
        double distance;
        double prob = Random();
        
        // Krátká vzdálenost (např. 1-5 km do centra města)
        if (prob < 0.7) {
            distance = 5 + Exponential(1);  // 1–5 km (vzdálenost v centru)
        }
        // Střední vzdálenost (např. 5-10 km do okrajových částí města)
        else if (prob < 0.9) {
            distance = 10 + Exponential(2);  // 5–10 km (vzdálenost na předměstí)
        }
        // Velká vzdálenost (např. 10-15 km pro vzdálenější oblasti města)
        else {
            distance = 15 + Exponential(3);  // 10–15 km (vzdálenější oblasti)
        }

        // Generování priority balíku (Expresní nebo Standardní)
        std::string priority = (rand() % 2 == 0) ? "Expresní" : "Standardní";

        // Vytvoření balíku s ID, velikostí, prioritou a vzdáleností
        Package* p = new Package("PKG_" + std::to_string(i), size, priority, distance);

        // Aktivujeme balík, aby šel do procesu nakládky
        p->Activate();
        i++;  // Zvyšujeme index pro balíky

        std::cout << "Generován balík " << p->id << " (Velikost: " << size << ", Priorita: " << priority 
                  << ", Vzdálenost: " << distance << " km)\n";

        // Čekání mezi generováním balíků (náhodně)
        Activate(Time + Exponential(10));  // Počkej náhodně mezi generováním balíků (průměrně 30 minut)
    
}