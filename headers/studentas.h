#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <iostream>
#include <iomanip>
#include <vector> 

//Bazine klase "Zmogus", skirta bendroms zmogaus savybes ir funkcionalumui aprasyti
class Zmogus {
public:
    //Viesi atributai, apibudinantys asmens varda ir pavarde
    std::string vardas;
    std::string pavarde;

    //Konstruktorius su numatytomies reiksmemis vardui ir pavardei
    Zmogus(const std::string v = "", const std::string p = ""):
        vardas (v), pavarde(p) {}

    //Funkcijos grazinancios objekto varda ir pavarde
    std::string getVardas() const { return vardas; }
    std::string getPavarde() const { return pavarde; }

    //Grynai virtuali funkcija, kuri turi buti igyvendinta paveldetose klasese
    virtual void spausdintiInfo() const = 0;

    //Virtualus destruktorius, uztikrinantis teisinga istekliu atlaisvinima paveldetose klasese
    virtual ~Zmogus() = default;
};

//Klase "Studentas", paveldinti "Zmogus". Skiria studento informacijai ir funkcijoms apdoroti
class Studentas : public Zmogus {
private:
    //Privatus atributai, apibudinantys studento rezultatus
    double galutinisBalas;
    double galutinisMediana;
    std::vector<double> nd_rezultatai;
    double egzaminoBalai;

public:
    //Numatytojo kostruktoriaus aprasymas. Inicializuoja tuscia studenta
    Studentas() : Zmogus(), galutinisBalas(0), galutinisMediana(0), egzaminoBalai(0) {}

    //Pilnas konstruktorius. Inicializuoja visus studento atributus.
    Studentas(const std::string& v, const std::string& p, double gBalas, double gMediana, 
              const std::vector<double>& nd, double egz)
        : Zmogus(v, p), galutinisBalas(gBalas), galutinisMediana(gMediana), nd_rezultatai(nd), egzaminoBalai(egz) {}

    //Kopijavimo konstruktorius. Kuria nauja objekta kopijuojant kita "Studentas" objekta
    Studentas(const Studentas& other)
        : Zmogus(other.vardas, other.pavarde),
          galutinisBalas(other.galutinisBalas),
          galutinisMediana(other.galutinisMediana),
          nd_rezultatai(other.nd_rezultatai),
          egzaminoBalai(other.egzaminoBalai) {}

    //Perrasytas priskyrimo operatorius, skirtas kopijuoti vieno objekto reiksmes kitam
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

    //Viesos funkcijos, skirtos grazinti arba nustatyti objektu atributus
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

    //Destruktorius. Atlaisvina dinamiskai rezervuotus isteklius ir nustato reiksmes i numatytasias
    ~Studentas() {

        nd_rezultatai.clear();
        galutinisBalas = 0.0;       
        galutinisMediana = 0.0;    
        egzaminoBalai = 0;
    }

    //Virtualios funkcijos implementacija, skirta studento informacijos spausdinimui
    void spausdintiInfo() const override {
        std::cout << "Vardas: " << vardas << ", Pavarde: " << pavarde << std::endl;
    }

    //Draugiski operatoriai, leidziantys patogiai ivesti ir isvesti objektus
    friend std::ostream& operator<<(std::ostream& os, const Studentas& studentas);
    friend std::istream& operator>>(std::istream& is, Studentas& studentas);
};

#endif // STUDENTAS_H

