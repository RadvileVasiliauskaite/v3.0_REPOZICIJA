#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>

class Studentas {
private:
    std::string vardas;
    std::string pavarde;
    double galutinisBalas;
    double galutinisMediana;

public:
    // Konstruktoriai
    Studentas() : galutinisBalas(0), galutinisMediana(0) {}
    Studentas(const std::string& v, const std::string& p, double gBalas, double gMediana)
        : vardas(v), pavarde(p), galutinisBalas(gBalas), galutinisMediana(gMediana) {}

    // Getteriai
    std::string getVardas() const { return vardas; }
    std::string getPavarde() const { return pavarde; }
    double getGalutinisBalas() const { return galutinisBalas; }
    double getGalutinisMediana() const { return galutinisMediana; }

    // Setteriai
    void setVardas(const std::string& v) { vardas = v; }
    void setPavarde(const std::string& p) { pavarde = p; }
    void setGalutinisBalas(double gBalas) { galutinisBalas = gBalas; }
    void setGalutinisMediana(double gMediana) { galutinisMediana = gMediana; }

    
    void printInfo() const;
};

#endif // STUDENTAS_H
