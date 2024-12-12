#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include <iostream> 
#include <iomanip>

/**
 * @brief Bazine klase, aprasanti zmogu su bendromis savybemis ir funkcionalumu.
 */
class Zmogus {
public:
    /// Asmens vardas.
    std::string vardas;
    /// Asmens pavarde.
    std::string pavarde;

    /**
     * @brief Sukuria Zmogus objekta su numatytuoju arba nurodytu vardu ir pavarde.
     * @param v Vardas (numatytasis yra tuscias tekstas).
     * @param p Pavarde (numatytasis yra tuscias tekstas).
     */
    Zmogus(const std::string v = "", const std::string p = "") :
        vardas(v), pavarde(p) {}

    /**
     * @brief Grazina varda.
     * @return Asmens vardas.
     */
    std::string getVardas() const { return vardas; }

    /**
     * @brief Grazina pavarde.
     * @return Asmens pavarde.
     */
    std::string getPavarde() const { return pavarde; }

    /**
     * @brief Grynai virtuali funkcija, skirta asmens informacijai spausdinti. Turi buti igyvendinta paveldetose klasese.
     */
    virtual void spausdintiInfo() const = 0;

    /**
     * @brief Virtualus destruktorius, uztikrinantis teisinga resursu atlaisvinima paveldetose klasese.
     */
    virtual ~Zmogus() = default;
};

/**
 * @brief Klase, aprasanti studenta, paveldima is Zmogus.
 */
class Studentas : public Zmogus {
private:
    /// Studentu galutinis balas.
    double galutinisBalas;
    /// Studentu galutine mediana.
    double galutinisMediana;
    /// Namu darbu rezultatai.
    std::vector<double> nd_rezultatai;
    /// Egzamino balas.
    double egzaminoBalai;

public:
    /**
     * @brief Numatytojo konstruktoriaus aprasymas.
     */
    Studentas() : Zmogus(), galutinisBalas(0), galutinisMediana(0), egzaminoBalai(0) {}

    /**
     * @brief Sukuria Studentas objekta su nurodytais atributais.
     * @param v Studentu vardas.
     * @param p Studentu pavarde.
     * @param gBalas Galutinis balas.
     * @param gMediana Galutine mediana.
     * @param nd Namu darbu rezultatai.
     * @param egz Egzamino balas.
     */
    Studentas(const std::string& v, const std::string& p, double gBalas, double gMediana, const std::vector<double>& nd, double egz)
        : Zmogus(v, p), galutinisBalas(gBalas), galutinisMediana(gMediana), nd_rezultatai(nd), egzaminoBalai(egz) {}

    /**
     * @brief Kopijavimo konstruktorius, skirtas sukurti nauja objekta, nukopijuojant kita.
     * @param other Kitas Studentas objektas, is kurio kopijuojama.
     */
    Studentas(const Studentas& other)
        : Zmogus(other.vardas, other.pavarde),
        galutinisBalas(other.galutinisBalas),
        galutinisMediana(other.galutinisMediana),
        nd_rezultatai(other.nd_rezultatai),
        egzaminoBalai(other.egzaminoBalai) {}

    /**
     * @brief Priskyrimo operatorius, skirtas kopijuoti vieno Studentas objekto reiksmes kitam.
     * @param other Kitas Studentas objektas.
     * @return Nuoroda i priskirta objekta.
     */
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

    // Getteriai ir setteriai
    std::string getVardas() const { return vardas; }
    std::string getPavarde() const { return pavarde; }
    /// @brief Grazina galutini bala.
    double getGalutinisBalas() const { return galutinisBalas; }
    /// @brief Grazina galutine mediana.
    double getGalutinisMediana() const { return galutinisMediana; }
    /// @brief Grazina namu darbu rezultatus.
    std::vector<double> getNd_rezultatai() const { return nd_rezultatai; }
    /// @brief Grazina egzamino bala.
    double getEgzaminoBalai() const { return egzaminoBalai; }

    void setVardas(const std::string& v) { vardas = v; }
    void setPavarde(const std::string& p) { pavarde = p; }
    /// @brief Nustato galutini bala.
    void setGalutinisBalas(double gBalas) { galutinisBalas = gBalas; }
    /// @brief Nustato galutine mediana.
    void setGalutinisMediana(double gMediana) { galutinisMediana = gMediana; }
    /// @brief Nustato namu darbu rezultatus.
    void setNd_Rezultatai(const std::vector<double>& nd) { nd_rezultatai = nd; }
    /// @brief Nustato egzamino bala.
    void setEgzaminoBalai(double egz) { egzaminoBalai = egz; }

    /**
     * @brief Destruktorius, skirtas atlaisvinti resursus.
     */
    ~Studentas() {
        vardas.clear();
        pavarde.clear();
        nd_rezultatai.clear();
        galutinisBalas = 0.0;
        galutinisMediana = 0.0;
        egzaminoBalai = 0;
    }

    /**
     * @brief Spausdina studento informacija.
     */
    void spausdintiInfo() const override {
        std::cout << "Vardas: " << vardas << ", Pavarde: " << pavarde << std:: endl;
    }

    /**
     * @brief Perkrautas operatorius objektu spausdinimui.
     */
    friend std::ostream& operator<<(std::ostream& os, const Studentas& studentas);
    /**
     * @brief Perkrautas operatorius objektu nuskaitymui.
     */
    friend std::istream& operator>>(std::istream& is, Studentas& studentas);

};

#endif // STUDENTAS_H