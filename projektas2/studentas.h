#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>

class Studentas {
private:
    std::string vardas;
    std::string pavarde;
    double galutinisBalas;
    double galutinisMediana;
    std::vector<double> nd_rezultatai;
    double egzaminoBalai;

public:

    Studentas() : galutinisBalas(0), galutinisMediana(0) {}
    Studentas(const std::string& v, const std::string& p, double gBalas, double gMediana, const std::vector<double>& nd, double egz)
        : vardas(v), pavarde(p), galutinisBalas(gBalas), galutinisMediana(gMediana), nd_rezultatai(nd), egzaminoBalai(egz) {}

    // Kopijavimo konstruktorius
    Studentas(const Studentas& other)
        : vardas(other.vardas),
        pavarde(other.pavarde),
        galutinisBalas(other.galutinisBalas),
        galutinisMediana(other.galutinisMediana),
        nd_rezultatai(other.nd_rezultatai),
        egzaminoBalai(other.egzaminoBalai) {}

    //priskyrimo operatorius
    Studentas& operator=(const Studentas& other) {
        if (this == &other) return *this; // Apsauga nuo saves priskyrimo
        vardas = other.vardas;
        pavarde = other.pavarde;
        galutinisBalas = other.galutinisBalas;
        galutinisMediana = other.galutinisMediana;
        nd_rezultatai = other.nd_rezultatai;
        egzaminoBalai = other.egzaminoBalai;
        return *this;
    }

    std::string getVardas() const { return vardas; }
    std::string getPavarde() const { return pavarde; }
    double getGalutinisBalas() const { return galutinisBalas; }
    double getGalutinisMediana() const { return galutinisMediana; }
    std::vector<double> getNd_rezultatai() const { return nd_rezultatai; }
    double getEgzaminoBalai() const { return egzaminoBalai; }

    void setVardas(const std::string& v) { vardas = v; }
    void setPavarde(const std::string& p) { pavarde = p; }
    void setGalutinisBalas(double gBalas) { galutinisBalas = gBalas; }
    void setGalutinisMediana(double gMediana) { galutinisMediana = gMediana; }
    void setNd_Rezultatai(const std::vector<double>& nd) { nd_rezultatai = nd; }
    void setEgzaminoBalai(double egz) { egzaminoBalai = egz; }

    //destruktorius
    ~Studentas() {
        vardas.clear();
        pavarde.clear();
        nd_rezultatai.clear();
        galutinisBalas = 0.0;
        galutinisMediana = 0.0;
        egzaminoBalai = 0;
    }

    void printInfo() const;

    friend std::ostream& operator<<(std::ostream& os, const Studentas& studentas);
    friend std::istream& operator>>(std::istream& is, Studentas& studentas);

};

#endif // STUDENTAS_H