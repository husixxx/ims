#include "PackageGenerator.h"
#include "Package.h"
#include "globals.h"

// counter
extern int i;

void PackageGenerator::Behavior()
{

    std::string size = (rand() % 2 == 0) ? "Malý" : "Velký";

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

    Package *p = new Package("PKG_" + std::to_string(i), size, distance);

    p->Activate();
    i++; // Zvyšujeme index pro balíky

    // std::cout << "Generován balík " << p->id << " (Velikost: " << size
    //   << ", Vzdálenost: " << distance << " km)\n";

    Activate(Time + Exponential(10)); // wait 10min
}