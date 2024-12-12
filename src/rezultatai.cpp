#include "rezultatai.h"
#include "studentas.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>

/**
 * @brief Apskaiciuoja kiekvieno studento galutini bala ir mediana.
 *
 * Funkcija apskaiciuoja galutini bala ir mediana pagal pateiktus namu darbu rezultatus
 * bei egzamino balus. Galutinis balas apskaiciuojamas kaip 40% namu darbu vidurkio ir
 * 60% egzamino balo. Galutine mediana apskaiciuojama panasiai, tik naudojant mediana vietoj
 * vidurkio namu darbu rezultatuose.
 *
 * @param studentai Vektorius, kuriame saugomi studentu objektai, kuriems bus apskaiciuojami galutiniai balai ir medianos.
 * @param nd_rezultatai Dvimacio vektoriaus, kuriame saugomi kiekvieno studento namu darbu rezultatai.
 * @param egzaminoBalai Vektorius, kuriame saugomi studentu egzamino balai.
 */
void skaiciavimai(std::vector<Studentas>& studentai, const std::vector<std::vector<double>>& nd_rezultatai, const std::vector<double>& egzaminoBalai) {
    for (size_t i = 0; i < studentai.size(); ++i) {
        double egzaminoBalas = egzaminoBalai[i];
        studentai[i].setGalutinisBalas(0.4 * skaiciuotiVidurki(nd_rezultatai[i]) + 0.6 * egzaminoBalas);
        studentai[i].setGalutinisMediana(0.4 * skaiciuotiMediana(nd_rezultatai[i]) + 0.6 * egzaminoBalas);
    }
}

/**
 * @brief Apskaiciuoja pateikto rezultatu saraso vidurki.
 *
 * Funkcija suskaiciuoja pateikto vektoriaus vidurki. Jei vektorius tuscias, grazinama 0.
 *
 * @param nd_rezultatai Vektorius, kuriame saugomi namu darbu rezultatai, pagal kuriuos bus apskaiciuojamas vidurkis.
 *
 * @return Vidurkis, apskaiciuotas pagal pateiktus namu darbu rezultatus.
 */
double skaiciuotiVidurki(const std::vector<double>& nd_rezultatai) {
    if (nd_rezultatai.empty()) return 0.0;
    return std::accumulate(nd_rezultatai.begin(), nd_rezultatai.end(), 0.0) / nd_rezultatai.size();
}

/**
 * @brief Apskaiciuoja pateikto rezultatu saraso mediana.
 *
 * Funkcija apskaiciuoja pateikto vektoriaus mediana. Jei vektorius tuscias, grazinama 0.
 *
 * @param uzduotys Vektorius, kuriame saugomi namu darbu rezultatai, pagal kuriuos bus apskaiciuojama mediana.
 *
 * @return Mediana, apskaiciuota pagal pateiktus namu darbu rezultatus.
 */
double skaiciuotiMediana(const std::vector<double>& uzduotys) {
    if (uzduotys.empty()) return 0.0;
    std::vector<double> sortedUzduotys = uzduotys;
    std::sort(sortedUzduotys.begin(), sortedUzduotys.end());
    size_t size = sortedUzduotys.size();
    if (size % 2 == 0) {
        return (sortedUzduotys[size / 2 - 1] + sortedUzduotys[size / 2]) / 2;
    }
    else {
        return sortedUzduotys[size / 2];
    }
}

/**
 * @brief Isveda visu studentu informacija i standartini isvesties srauta.
 *
 * Funkcija isveda visu studentu vardus, pavardes ir ju galutinius balus, apskaiciuotus pagal
 * vidurki ir mediana. Rezultatai pateikiami su dviem skaitmenimis po kablelio.
 *
 * @param studentai Vektorius, kuriame saugomi studentu objektai, kuriu informacija bus isvedama.
 */
void displayResults(const std::vector<Studentas>& studentai) {
    std::cout << std::left << std::setw(20) << "Vardas"
        << std::setw(20) << "Pavarde"
        << std::setw(20) << "Galutinis (Vid.)"
        << std::setw(20) << "Galutinis (Med.)"
        << std::endl;
    

    for (const auto& studentas : studentai) {
        std::cout << std::left << std::setw(20) << studentas.getVardas()
            << std::setw(20) << studentas.getPavarde()
            << std::setw(20) << std::fixed << std::setprecision(2) << studentas.getGalutinisBalas()
            << std::setw(20) << std::fixed << std::setprecision(2) << studentas.getGalutinisMediana()
            << std::endl;
    }

}
