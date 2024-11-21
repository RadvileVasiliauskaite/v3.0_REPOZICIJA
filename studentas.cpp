#include "studentas.h"
#include <iostream>
#include <iomanip>

void Studentas::printInfo() const {
    std::cout << std::left << std::setw(20) << vardas
        << std::setw(20) << pavarde
        << std::fixed << std::setprecision(2)
        << std::setw(20) << galutinisBalas
        << std::setw(20) << galutinisMediana
        << std::endl;
}
