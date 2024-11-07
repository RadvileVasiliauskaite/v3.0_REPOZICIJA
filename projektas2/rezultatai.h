#ifndef REZULTATAI_H
#define REZULTATAI_H

#include <vector>
#include <vector>
#include "studentas.h"

double skaiciuotiVidurki(const std::vector<double>& nd_rezultatai);
double skaiciuotiMediana(const std::vector<double>& uzduotys);
void displayResults(const std::vector<Studentas>& studentai);
void skaiciavimai(std::list<Studentas>& studentai, const std::vector<std::vector<double>> nd_rezultatai, const std::vector<double>& egzaminoBalai);

#endif // REZULTATAI_H