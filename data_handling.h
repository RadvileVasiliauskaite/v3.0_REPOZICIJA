#ifndef DATA_HANDLING_H
#define DATA_HANDLING_H

#include <vector>
#include "studentas.h"

char getInputChoice();
double getPositiveScore(const std::string& prompt);
void readFromFile(std::vector<Studentas>& studentai, std::vector<std::vector<double>>& nd_rezultatai, std::vector<double>& egzaminoBalai);
double generuotiAtsitiktiniBala();

#endif // DATA_HANDLING_H