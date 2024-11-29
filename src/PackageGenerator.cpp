#include "PackageGenerator.h"
// Propojení s globálními frontami

void PackageGenerator::Behavior() {
    // Generujeme balíky v náhodných intervalech
    for (int i = 0; i < 20; i++) {  // Například generujeme 20 balíků
        // Generujeme náhodně velikost a prioritu balíku
        std::string size = (i % 2 == 0) ? "Malý" : "Velký";  // Alternující velikost
        std::string priority = (i % 3 == 0) ? "Expresní" : "Standardní";  // Alternující priorita

        // Vytvoříme nový balík s ID, velikostí a prioritou
        Package* p = new Package("PKG_" + std::to_string(i), size, priority);
        p->Activate();  // Aktivujeme balík, aby šel do procesu nakládky

        std::cout << "Generován balík " << p->id << " (Velikost: " << size << ", Priorita: " << priority << ")\n";

        // Čekání mezi generováním balíků
        Wait(Exponential(1));  // Počkej náhodně mezi generováním balíků
    }
}
