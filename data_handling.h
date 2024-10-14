#ifndef DATA_HANDLING_H
#define DATA_HANDLING_H

#include <vector>
#include <string>
#include "studentas.h"

// Function declarations
void readFromFile(std::vector<Studentas>& studentai, std::vector<std::vector<double>>& nd_rezultatai, std::vector<double>& egzaminoBalai);
void writeToFile(const std::vector<Studentas>& studentai, const std::vector<std::vector<double>>& nd_rezultatai, const std::vector<double>& egzaminoBalai, const std::string& filename);
void generateStudents(int studentCount, std::vector<Studentas>& studentai, std::vector<std::vector<double>>& nd_rezultatai, std::vector<double>& egzaminoBalai);
void inputStudentData(int studentCount, std::vector<Studentas>& studentai, std::vector<std::vector<double>>& nd_rezultatai, std::vector<double>& egzaminoBalai);
double skaiciuotiVidurki(const std::vector<double>& uzduotys);
double skaiciuotiMediana(const std::vector<double>& uzduotys);
char getInputChoice();
double generuotiAtsitiktiniBala();
double getPositiveScore(const std::string& prompt);
std::string formatIndex(int index, int maxLength);
char getSortingChoice();
void categorizeStudents(const std::vector<Studentas>& studentai, std::vector<Studentas>& vargsiai, std::vector<Studentas>& kietiakiai);
void processAndWriteResults(std::vector<Studentas>& studentai, const std::string& category, char sortOrder);


#endif // DATA_HANDLING_H