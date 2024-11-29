#ifndef DATA_HANDLING_H
#define DATA_HANDLING_H

#include <vector>
#include <string>
#include <list>
#include "studentas.h"

// Function declarations
void readFromFile(std::list<Studentas>& studentai, std::vector<std::vector<double>>& nd_rezultatai, std::vector<double>& egzaminoBalai, const std::string& filename);
void writeToFile(const std::list<Studentas>& studentai, const std::vector<std::vector<double>>& nd_rezultatai, const std::vector<double>& egzaminoBalai, const std::string& filename);
void generateStudents(int studentCount, std::list<Studentas>& studentai, std::vector<std::vector<double>>& nd_rezultatai, std::vector<double>& egzaminoBalai);
void inputStudentData(int studentCount, std::list<Studentas>& studentai, std::vector<std::vector<double>>& nd_rezultatai, std::vector<double>& egzaminoBalai);
double skaiciuotiVidurki(const std::vector<double>& uzduotys);
double skaiciuotiMediana(const std::vector<double>& uzduotys);
char getInputChoice();
double generuotiAtsitiktiniBala();
double getPositiveScore(const std::string& prompt);
std::string formatIndex(int index, int maxLength);
char getSortingChoice();
void categorizeStudents(const std::list<Studentas>& studentai, std::list<Studentas>& vargsiai, std::list<Studentas>& kietiakiai);
void processAndWriteResults(std::list<Studentas>& studentai, const std::string& category, char sortOrder);
void writeResultsToFile(const std::list<Studentas>& students, const std::string& filename);

void strategija1(const std::list<Studentas>& studentai, std::list<Studentas>& vargsiai, std::list<Studentas>& kietiakiai);
void strategija2(std::list<Studentas>& studentai, std::list<Studentas>& vargsiai);
void strategija3(std::list<Studentas>& studentai, std::list<Studentas>& vargsiai, std::list<Studentas>& kietiakiai);
int selectStrategyAndCategorizeStudents(std::list<Studentas>& studentai, std::list<Studentas>& vargsiai, std::list<Studentas>& kietiakiai);
void RuleOfThree();

#endif // DATA_HANDLING_H