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
std::istream& operator>>(std::istream& is, Studentas& studentas) {
    std::string vardas, pavarde;
    double galutinisBalas, galutinisMediana;

    is >> vardas >> pavarde >> galutinisBalas;
    studentas.setVardas(vardas);
    studentas.setPavarde(pavarde);
    studentas.setGalutinisBalas(galutinisBalas);
    studentas.setGalutinisMediana(galutinisMediana);

    return is;
}

std::ostream& operator<<(std::ostream& os, const Studentas& studentas) {
    os << std::left << std::setw(15) << studentas.getVardas()
        << std::setw(15) << studentas.getPavarde()
        << std::setw(10) << std::fixed << std::setprecision(2) << studentas.getGalutinisBalas()
        << std::setw(40) << std::fixed << std::setprecision(2) << studentas.getGalutinisMediana();
    return os;
}
