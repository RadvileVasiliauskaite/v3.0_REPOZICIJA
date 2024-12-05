#include "studentas.h"
#include <iostream>
#include <iomanip>


std::istream& operator>>(std::istream& is, Studentas& studentas) {
    std::string vardas, pavarde;
    double egzaminoBalai;
    std::vector<double> nd_rezultatai;

    is >> vardas >> pavarde;
    studentas.setVardas(vardas);
    studentas.setPavarde(pavarde);

    double nd;
    while (is >> nd) {
        if (nd == -1) break;
        nd_rezultatai.push_back(nd);
    }
    studentas.setNd_Rezultatai(nd_rezultatai);

    is >> egzaminoBalai;
    studentas.setEgzaminoBalai(egzaminoBalai);

    return is;

}

std::ostream& operator<<(std::ostream& os, const Studentas& studentas) {
    os << std::left << std::setw(20) << studentas.getVardas()
        << std::setw(20) << studentas.getPavarde()
        << "ND: ";

    for (const auto& nd : studentas.getNd_rezultatai()) {
        os << nd << " ";
    }

    os << "Egzaminas: " << studentas.getEgzaminoBalai() << std::endl;

    return os;
}