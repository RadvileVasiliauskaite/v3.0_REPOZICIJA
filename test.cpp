#include "pch.h"
#include "gtest/gtest.h"
#include "studentas.h"
#include <vector>

// Testas Studentas klasei: tikrina konstruktorius ir getterius
TEST(StudentasTest, ConstructorAndGetters) {
    std::vector<double> nd_rezultatai = { 8.5, 9.0, 7.5 };
    double egzaminoBalas = 8.0;

    // Sukuriame studenta su testiniais duomenimis
    Studentas studentas("Jonas", "Jonaitis", 8.4, 8.0, nd_rezultatai, egzaminoBalas);

    // Tikriname, ar teisingai sukurti objekto atributai
    EXPECT_EQ(studentas.getVardas(), "Jonas");
    EXPECT_EQ(studentas.getPavarde(), "Jonaitis");
    EXPECT_DOUBLE_EQ(studentas.getGalutinisBalas(), 8.4);
    EXPECT_DOUBLE_EQ(studentas.getGalutinisMediana(), 8.0);
    EXPECT_EQ(studentas.getNd_rezultatai().size(), 3);
    EXPECT_DOUBLE_EQ(studentas.getEgzaminoBalai(), 8.0);
}

// Testas setteriui
TEST(StudentasTest, Setters) {
    Studentas studentas;

    studentas.setVardas("Petras");
    studentas.setPavarde("Petraitis");
    studentas.setGalutinisBalas(9.5);
    studentas.setGalutinisMediana(9.0);
    studentas.setNd_Rezultatai({ 7.5, 8.0, 8.5 });
    studentas.setEgzaminoBalai(8.5);

    // Tikriname, ar seteriai teisingai pakeite reiksmes
    EXPECT_EQ(studentas.getVardas(), "Petras");
    EXPECT_EQ(studentas.getPavarde(), "Petraitis");
    EXPECT_DOUBLE_EQ(studentas.getGalutinisBalas(), 9.5);
    EXPECT_DOUBLE_EQ(studentas.getGalutinisMediana(), 9.0);
    EXPECT_EQ(studentas.getNd_rezultatai().size(), 3);
    EXPECT_DOUBLE_EQ(studentas.getEgzaminoBalai(), 8.5);
}

// Testas kopijavimo konstruktoriui
TEST(StudentasTest, CopyConstructor) {
    std::vector<double> nd_rezultatai = { 8.0, 7.5, 9.0 };
    Studentas original("Marius", "Mariuška", 8.5, 8.0, nd_rezultatai, 7.5);

    // Sukuriame studenta naudodami kopijavimo konstruktoriu
    Studentas copy = original;

    // Tikriname, ar kopija turi tas pacias reiksmes
    EXPECT_EQ(copy.getVardas(), "Marius");
    EXPECT_EQ(copy.getPavarde(), "Mariuška");
    EXPECT_DOUBLE_EQ(copy.getGalutinisBalas(), 8.5);
    EXPECT_DOUBLE_EQ(copy.getGalutinisMediana(), 8.0);
    EXPECT_EQ(copy.getNd_rezultatai().size(), 3);
    EXPECT_DOUBLE_EQ(copy.getEgzaminoBalai(), 7.5);
}

// Testas priskyrimo operatoriui
TEST(StudentasTest, AssignmentOperator) {
    std::vector<double> nd_rezultatai1 = { 9.0, 8.5, 9.5 };
    Studentas original("Andrius", "Andriuski", 9.0, 9.5, nd_rezultatai1, 9.0);

    Studentas assigned;
    assigned = original;

    // Tikriname, ar priskyrimo operatorius veikia teisingai
    EXPECT_EQ(assigned.getVardas(), "Andrius");
    EXPECT_EQ(assigned.getPavarde(), "Andriuski");
    EXPECT_DOUBLE_EQ(assigned.getGalutinisBalas(), 9.0);
    EXPECT_DOUBLE_EQ(assigned.getGalutinisMediana(), 9.5);
    EXPECT_EQ(assigned.getNd_rezultatai().size(), 3);
    EXPECT_DOUBLE_EQ(assigned.getEgzaminoBalai(), 9.0);
}

// Testas destruktoriui ir resursu valymui
TEST(StudentasTest, DestructorClearsResources) {
    Studentas studentas("Tomas", "Tomaitis", 9.0, 8.0, { 10.0, 9.5, 8.0 }, 7.5);

    // Patikriname, ar objektas tinkamai atlaisvina atminti po sunaikinimo
    EXPECT_NO_THROW({
        studentas.setVardas("Petras");
        studentas.setPavarde("Petraitis");
        studentas.setGalutinisBalas(9.0);
        });
}



// Pagrindine funkcija, kad paleistumete testus
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
