#ifndef PACKAGE_H
#define PACKAGE_H
#include <iostream>
#include <string>
#include "globals.h"

class Package : public Process
{
public:
    std::string id;
    std::string size; // Malý, Střední, Velký
    double distance;
    Package(std::string _id, std::string _size, double _distance)
        : id(_id), size(_size), distance(_distance) {};
    void Behavior() override; // Metoda pro chování balíku (čekání na nakládku)
};

#endif // PACKAGE_H
