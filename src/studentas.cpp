#include "studentas.h"
#include <iostream>
#include <iomanip>

/**
 * @brief Iveda "Studentas" objekto duomenis is standartinio srauto.
 *
 * Si funkcija iraso studento varda, pavarde, namu darbu rezultatus ir egzamino bala i atitinkamas
 * objekto savybes. Vardas ir pavarde irasomi kaip tekstiniai duomenys, o namu darbu rezultatai
 * irasomi i vektoriu. Namu darbu rezultatai ivedami, kol ivedamas -1 (baigimo zenklas). Egzamino balas
 * irasomas po namu darbu rezultatu.
 *
 * @param is ivesties srautas, is kurio duomenys bus nuskaityti.
 * @param studentas "Studentas" objekto nuoroda, kuriame bus issaugoti ivesti duomenys.
 * @return Patobulintas ivesties srautas.
 */
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

/**
 * @brief Isveda "Studentas" objekto duomenis i standartini srauta.
 *
 * Si funkcija isveda studento varda, pavarde, namu darbu rezultatus ir egzamino bala i isvesties srauta.
 * Vardas ir pavarde yra isvedami kaip tekstas, o namu darbu rezultatai isvedami kaip atskiri skaiciai.
 * Paskutinis rezultatas yra egzamino balas.
 *
 * @param os Isvesties srautas, i kuri bus irasyti studento duomenys.
 * @param studentas "Studentas" objekto, kurio duomenys bus isvesti, nuoroda.
 * @return Patobulintas isvesties srautas.
 */
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
