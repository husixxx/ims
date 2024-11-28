#include "simlib.h"
#include <iostream>

// Parametry simulace
const int NUM_VEHICLES = 1;  // Počet vozidel
const int NUM_LOADING_SLOTS = 2;  // Počet nakládacích míst (facility)

// Facility pro nakládání balíků
Facility loadingFacility[NUM_LOADING_SLOTS];  // Facility pro nakládku balíků

// Fronta pro čekající balíky
Queue Q;

// Třída pro balíky
class Package : public Process {
public:
    std::string id;
    std::string size;  // Malý, Střední, Velký
    std::string priority;
    
    Package(std::string _id, std::string _size, std::string _priority)
        : id(_id), size(_size), priority(_priority) {}

    void Behavior() override {
        // Proces kontroly balíku (simulace čekání)
        Wait(2); // Čas na kontrolu (např. 2 minuty)
        // Po kontrole balík je připraven na nakládku
        std::cout << "Balík " << id << " zkontrolován, připraven na nakládku." << std::endl;

        // Požádat o přístup k jednomu slotu facility pro nakládku
        int kt = -1;
        zpet:  // Pokud je všechno obsazené, čeká, dokud nebude nějaký slot volný
        for (int a = 0; a < NUM_LOADING_SLOTS; a++) {
            if (!loadingFacility[a].Busy()) {
                kt = a;
                break;
            }
        }
        if (kt == -1) {
            Into(Q);  // Pokud není volné místo, přidej balík do fronty
            Passivate();  // Čekání na uvolnění slotu
            goto zpet;
        }

        Seize(loadingFacility[kt]);  // Získání přístupu k nakládací facility
        Wait(Exponential(30));  // Simulace času na nakládku
        Release(loadingFacility[kt]);  // Uvolnění facility po nakládce

        // Pokud je nějaký další balík čekající ve frontě, aktivuj ho
        if (Q.Length() > 0) {
            (Q.GetFirst())->Activate();  // Aktivace dalšího balíku ve frontě
        }
    }
};

// Třída pro vozidla
class Vehicle : public Process {
public:
    void Behavior() override {
        while (true) {
            // Vozidlo čeká na přístup k facility
            Wait(2); // Simulace času, kdy vozidlo čeká na další balík

            // Pokud je facility k dispozici, vozidlo si vezme balík a začne nakládku
            std::cout << "Vozidlo připraveno k nakládce balíku." << std::endl;
            
            // Čekáme na přístup k facility (proces čekání na balík)
            int kt = -1;
            zpet:  // Pokud je všechno obsazené, čeká
            for (int a = 0; a < NUM_LOADING_SLOTS; a++) {
                if (!loadingFacility[a].Busy()) {
                    kt = a;
                    break;
                }
            }
            if (kt == -1) {
                Into(Q);  // Pokud není volné místo, vozidlo čeká ve frontě
                Passivate();  // Čekání na uvolnění facility
                goto zpet;
            }

            // Po získání přístupu k facility, vozidlo může začít nakládat balíky
            Seize(loadingFacility[kt]);  // Vozidlo požaduje přístup k facility
            std::cout << "Vozidlo nakládá balík." << std::endl;
            Wait(3); // Čas na nakládku balíku (simulace)
            std::cout << "Vozidlo doručuje balík." << std::endl;

            // Po dokončení nakládky vozidlo uvolní facility
            Release(loadingFacility[kt]);
        }
    }
};

// Generátor balíků
class PackageGenerator : public Event {
public:
    void Behavior() override {
        for (int i = 0; i < 10; i++) { // Generování 10 balíků
            std::string size = (i % 2 == 0) ? "Malý" : "Velký";  // Alternující velikost balíku
            std::string priority = (i % 3 == 0) ? "Expresní" : "Standardní";
            Package* p = new Package("PKG_" + std::to_string(i), size, priority);
            p->Activate(); // Aktivace procesu pro balík
            std::cout << "Generován balík PKG_" << i << std::endl;
        }
    }
};

// Hlavní funkce
int main() {
    printf("%s\n", "Hello, World!");    

    Init(0, 60 * 60 * 8); // Simulace 8 hodin (pracovní den)

    
    // Vytvoření generátoru balíků a aktivace procesu
    PackageGenerator* generator = new PackageGenerator();
    generator->Activate(); // Aktivace generátoru balíků
    
    // Vytvoření vozidel a aktivace procesu
    for (int i = 0; i < NUM_VEHICLES; i++) {
        Vehicle* vehicle = new Vehicle();
        vehicle->Activate(); // Aktivace vozidla
    }

    // Spuštění simulace
    Run();

    return 0;
}
