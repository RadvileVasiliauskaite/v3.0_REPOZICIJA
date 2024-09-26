#ifndef REZULTATAI_H
#define REZULTATAI_H

#include <vector>
#include "studentas.h"

double skaiciuotiVidurki(const std::vector<double>& nd_rezultatai);
double skaiciuotiMediana(std::vector<double> nd_rezultatai);
void displayResults(const std::vector<Studentas>& studentai);

#endif // REZULTATAI_H
