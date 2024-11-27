#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <iostream>
#include <iomanip>

class Studentas {
private:
    std::string vardas;
    std::string pavarde;
    double galutinisBalas;
    double galutinisMediana;

public:
    
    Studentas() : galutinisBalas(0), galutinisMediana(0) {}
    Studentas(const std::string& v, const std::string& p, double gBalas, double gMediana)
        : vardas(v), pavarde(p), galutinisBalas(gBalas), galutinisMediana(gMediana) {}

    Studentas(const Studentas& other)
        : vardas(other.vardas),
        pavarde(other.pavarde),
        galutinisBalas(other.galutinisBalas),
        galutinisMediana(other.galutinisMediana) {}
    //priskyrimo operatorius
    Studentas& operator=(const Studentas& other) {
        if (this == &other) return *this; // Apsauga nuo saves priskyrimo
        vardas = other.vardas;
        pavarde = other.pavarde;
        galutinisBalas = other.galutinisBalas;
        galutinisMediana = other.galutinisMediana;
        return *this;
    }

    std::string getVardas() const { return vardas; }
    std::string getPavarde() const { return pavarde; }
    double getGalutinisBalas() const { return galutinisBalas; }
    double getGalutinisMediana() const { return galutinisMediana; }

    void setVardas(const std::string& v) { vardas = v; }
    void setPavarde(const std::string& p) { pavarde = p; }
    void setGalutinisBalas(double gBalas) { galutinisBalas = gBalas; }
    void setGalutinisMediana(double gMediana) { galutinisMediana = gMediana; }

    ~Studentas() {
        vardas.clear();
        pavarde.clear();
    }

    void printInfo() const;

    friend std::ostream& operator<<(std::ostream& os, const Studentas& studentas);
    friend std::istream& operator>>(std::istream& is, Studentas& studentas);
};

#endif // STUDENTAS_H
