#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <iostream>
#include <iomanip>
#include <vector> 

class Zmogus {
public:
    std::string vardas;
    std::string pavarde;
    Zmogus(const std::string v = "", const std::string p = ""):
        vardas (v), pavarde(p) {}

    std::string getVardas() const { return vardas; }
    std::string getPavarde() const { return pavarde; }

    virtual void spausdintiInfo() const = 0;
    virtual ~Zmogus() = default;
};

class Studentas : public Zmogus {
private:
    double galutinisBalas;
    double galutinisMediana;
    std::vector<double> nd_rezultatai;
    double egzaminoBalai;

public:
    Studentas() : Zmogus(), galutinisBalas(0), galutinisMediana(0), egzaminoBalai(0) {}

    Studentas(const std::string& v, const std::string& p, double gBalas, double gMediana, 
              const std::vector<double>& nd, double egz)
        : Zmogus(v, p), galutinisBalas(gBalas), galutinisMediana(gMediana), nd_rezultatai(nd), egzaminoBalai(egz) {}

    Studentas(const Studentas& other)
        : Zmogus(other.vardas, other.pavarde),
          galutinisBalas(other.galutinisBalas),
          galutinisMediana(other.galutinisMediana),
          nd_rezultatai(other.nd_rezultatai),
          egzaminoBalai(other.egzaminoBalai) {}

    Studentas& operator=(const Studentas& other) {
        if (this == &other) return *this;
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


    ~Studentas() {

        nd_rezultatai.clear();
        galutinisBalas = 0.0;       
        galutinisMediana = 0.0;    
        egzaminoBalai = 0;
    }

    void spausdintiInfo() const override {
        std::cout << "Vardas: " << vardas << ", Pavarde: " << pavarde << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Studentas& studentas);
    friend std::istream& operator>>(std::istream& is, Studentas& studentas);
};

#endif // STUDENTAS_H

