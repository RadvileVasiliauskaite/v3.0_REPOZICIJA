<h1>Įdiegimas</h1>
Atsisiųskite diegimo failą pavadinimu setup.exe failą.
Dukart spustelėdami paleiskite įdiegimo programą t.y. setup.exe failą, kad pradėtumėte diegimo procesą.
Diegimo vedlys padės atlikti visus žingsnius. Jums reikės priimti licencijos sutartį ir paspausti "Next" (Kitas), kad tęstumėte diegimą.
Baigus diegimą, paspauskite "Finish" (Baigti), kad užbaigtumėte diegimo vedlį.
Viską užbaigę galite paleisti programą pasirinkdami ją iš pradžios meniu arba darbalaukio.

<h1>Naudojimo instrukcija</h1>
CMake: Įdiegta CMake (versija 3.25 ar vėlesnė)
Kompiliatorius: Turėti C++ kompiliatorių, kad galėtumėte sukompiliuoti projektą.
CMake ir run.bat failas buvo išbandyti Windows aplinkoje

<h1>Projekto struktūra</h1>
CMakeLists.txt: failas naudojamas CMake projekto konfigūracijai ir kompiliavimui
run.bat: Windows .bat failas, skirtas paleisti programą.

<h1>Programos diegimas ir paleidimas</h1>
Klonuokite projektą į savo kompiuterį, paleidimas su run.bat atliks visus reikalingus veiksmus, t.y. sukompiliuos ir paleis programą

<h1>V3.0</h1>

Sukurtas programos įdiegimo failas setup.exe, ProgramInstallSetup.msi, remiantis v1.5 versija.

<h1>V2.0</h1>
Šis C++ projektas skirtas studentų vardų, pavardžių ir balų tvarkymui. Programa leidžia įvesti studentų duomenis, apskaičiuoti galutinį balą naudojant vidurkį arba medianą, rūšiuoti studentus pagal jų balus, ir generuoti atsitiktinius studentų sąrašus su įvairiais duomenų kiekiais. Projektas apima optimizaciją ir testavimą naudojant įvairius kompiliatoriaus optimizacijos lygmenis. Pridėta dokumentacija HTML formatu (pateiktas HTML katalogas) bei parašyti Unit testai.

Unit testų išvedimo pvz.: 

![Screenshot 2024-12-12 185710](https://github.com/user-attachments/assets/5f952853-80d8-40db-8423-05c04f8e3c54)

1.Rankinis Duomenų Įvedimas:
* Vartotojas pats įveda studento vardą, pavardę, namų darbų ir egzamino balus.
* Programa leidžia įvesti kelis studentus ir patikrina balų teisingumą.

2.Automatinis Duomenų Generavimas:
* Naudojant funkciją generuotiAtsitiktiniBala(), sugeneruojami vardai, pavardės, atsitiktiniai namų darbų balai ir egzamino rezultatai.
* Sugeneruoti studentai saugomi faile (studentai_[kiekis].txt).

3.Duomenų Nuskaitymas Iš Failo:
* Programa priima .txt failus su struktūrizuotais duomenimis.
* Failo formatas:
Vardas      Pavarde      ND1  ND2  ND3  ND4  ND5  Egzaminas
Jonas       Jonaitis     8    7    6    9    8    10

4.Duomenų išvestis į ekraną:
* Naudojant operator<<, rezultatai pateikiami formatuotai.
* Formatas:
Vardas          Pavarde         Galutinis (Vid.)   Galutinis (Med.)
Jonas           Jonaitis        8.50              8.00

5.Duomenų išvedimas į failus:
* Rezultatai gali būti išsaugomi į failus:
    * vargsiai.txt – studentai, kurių balas mažesnis nei 5.0.
    * kietiakiai.txt – studentai, kurių balas didesnis arba lygus 5.0.
* Rezultatai, kurie sugeneruoti atsitiktiniu būdu išvedami į failą (studentai_[kiekis].txt). Formatas:
Vardas         Pavarde        ND1       ND2       ND3       ND4       ND5       EgzaminoBalas  
Vardas0001     Pavarde0001    7         5         7         1         8         6              
Vardas0002     Pavarde0002    9         3         3         2         9         8              
Vardas0003     Pavarde0003    4         1         9         9         7         8    



<h1>V1.5</h1>
Programoje sukurtos dvi klasės: abstrakti klasė Zmogus ir jos išvestinė klasė Studentas.

Abstrakti bazinė klasė Zmogus negali būti naudojama tiesiogiai, tik jos išvestinėse klasėse. Klasė apima bendrus atributus ir metodus, kurie yra bendri 
visiems žmonėms, tačiau jie negali būti naudojami tiesiogiai. Šioje klasėje yra du privatūs duomenys: vardas ir pavarde. Jie apibrėžiami naudojant kostruktorius.
Jų vertes galima gauti per atitinkamus metodus. Kadangi tai abstrakti klasė, ji turi virtualų metodą "spausdintiInfo()", kuris yra grynasis ir turi būti realizuojamas
tik išvestinėse klasėse, tai užtikrina, kad negalima sukurti Žmogus tipo objekto tiesiogiai pvz.: Zmogus = z; negalimas

Klasė Studentas yra išvestinė klasė, kuri paveldi visus Žmogus klasės atributus ir metodus. Be to, ji prideda papildomus atributus, susijusius su studento akademine veikla: 
namų darbai, egzamino balai, galutinis balas, galutinė mediana.

patobulintas projektas išlaiko funkcionalumą, programa palaiko realizuotą trijų metodų taisyklę.


<h1>V1.2</h1>
Programoje išpildyta "rule of three' ir pridėtas išvesties ir įvesties operatorius.

Išvesties operatorius leidžia patogiai išvesti Studentas objektą į srautą, išsaugant aiškų ir tvarkingą formatavimą.
Įvesties operatorius leidžia lengvai nuskaityti Studentas objektą iš srauto. Jis užtikrina, kad duomenys būtų teisingai nustatyti klasės atributams.

Rankinis Duomenų Įvedimas:
* Vartotojas pats įveda studento vardą, pavardę, namų darbų ir egzamino balus.
* Programa leidžia įvesti kelis studentus ir patikrina balų teisingumą.

Automatinis Duomenų Generavimas:
* Naudojant funkciją generuotiAtsitiktiniBala(), sugeneruojami vardai, pavardės, atsitiktiniai namų darbų balai ir egzamino rezultatai.
* Sugeneruoti studentai saugomi faile (studentai_[kiekis].txt).

Duomenų Nuskaitymas Iš Failo:
* Programa priima .txt failus su struktūrizuotais duomenimis.
* Failo formatas:
Vardas      Pavarde      ND1  ND2  ND3  ND4  ND5  Egzaminas
Jonas       Jonaitis     8    7    6    9    8    10

Duomenų išvestis į ekraną:
* Naudojant operator<<, rezultatai pateikiami formatuotai.
* Formatas:
Vardas          Pavarde         Galutinis (Vid.)   Galutinis (Med.)
Jonas           Jonaitis        8.50              8.00

Duomenų išvedimas į failus:
* Rezultatai gali būti išsaugomi į failus:
    * vargsiai.txt – studentai, kurių balas mažesnis nei 5.0.
    * kietiakiai.txt – studentai, kurių balas didesnis arba lygus 5.0.
* Rezultatai, kurie sugeneruoti atsitiktiniu būdu išvedami į failą (studentai_[kiekis].txt). Formatas:
Vardas         Pavarde        ND1       ND2       ND3       ND4       ND5       EgzaminoBalas  
Vardas0001     Pavarde0001    7         5         7         1         8         6              
Vardas0002     Pavarde0002    9         3         3         2         9         8              
Vardas0003     Pavarde0003    4         1         9         9         7         8    


<h1>V1.1</h1>

Atlikus tyrimus pastebėta, kad greičiau veikia, kai Studentas yra struct'ūra, bendras visų failų analizės laikas
 naudojant struct'ūras ~104s, o klasės ~216s.

 Matavimų laikai:

| 1000 studentų         | STRUCT     | CLASS      |
|-----------------------|------------|------------|
| Failo nuskaitymas     | 0.00360 s  | 0.01254 s  |
| Rūšiavimas            | 0.00015 s  | 0.00007 s  |
| Dalijimas į grupes    | 0.00248 s  | 2.45766 s  |
| Vargšių išsaugojimas  | 0.02096 s  | 0.00578 s  |
| Kietekų išsaugojimas  | 0.00518 s  | 0.00288 s  |
| Bendras laikas        | 2.5198 s   | 3.79922 s  |

| 10000 studentų        | STRUCT     | CLASS      |
|-----------------------|------------|------------|
| Failo nuskaitymas     | 0.03099 s  | 0.03795 s  |
| Rūšiavimas            | 0.00119 s  | 0.00114 s  |
| Dalijimas į grupes    | 1.34269 s  | 2.20461 s  |
| Vargšių išsaugojimas  | 0.01777 s  | 0.01685 s  |
| Kietekų išsaugojimas  | 0.01688 s  | 0.01699 s  |
| Bendras laikas        | 16.5476 s  | 4.21732 s  |

| 100000 studentų       | STRUCT     | CLASS      |
|-----------------------|------------|------------|
| Failo nuskaitymas     | 0.30469 s  | 0.31873 s  | 
| Rūšiavimas            | 0.00665 s  | 0.00725 s  | 
| Dalijimas į grupes    | 1.20666 s  | 1.0955 s   | 
| Vargšių išsaugojimas  | 0.16695 s  | 0.16238 s  | 
| Kietekų išsaugojimas  | 0.16738 s  | 0.15994 s  | 
| Bendras laikas        | 3.05906 s  | 4.82208 s  | 

| 1000000 studentų      | STRUCT     | CLASS      |
|-----------------------|------------|------------|
| Failo nuskaitymas     | 3.10161 s  | 3.21587 s  | 
| Rūšiavimas            | 0.07144 s  | 0.07435 s  | 
| Dalijimas į grupes    | 1.47273 s  | 1.47237 s  | 
| Vargšių išsaugojimas  | 1.63293 s  | 1.59242 s  | 
| Kietekų išsaugojimas  | 1.65165 s  | 1.64607 s  |
| Bendras laikas        | 10.3526 s  | 9.33 s     |

| 10000000 studentų     | STRUCT     | CLASS      |
|-----------------------|------------|------------|
| Failo nuskaitymas     | 31.5896 s  | 28.3868 s  | 
| Rūšiavimas            | 0.89778 s  | 0.77349 s  | 
| Dalijimas į grupes    | 3.45435 s  | 3.46566 s  | 
| Vargšių išsaugojimas  | 16.6124 s  | 15.7654 s  | 
| Kietekų išsaugojimas  | 16.5767 s  | 16.2833 s  |
| Bendras laikas        | 72.3017 s  | 196.722 s  | 

C++ optimizacijos analizė

Šiame eksperimente buvo išmatuotas programos vykdymo laikas naudojant skirtingus kompiliatoriaus
 optimizavimo lygiai: **`-O1`**, **`-O2`**, **`-O3`**. Palyginome laikus, kaip optimizacija veikia programos našumą.

Testavimo metodai:
Kiekvienas programos variantas buvo kompiiliuotas su skirtingais optimizacijos lygiais:

- **`-O1`**: Pagrindinė optimizacija
- **`-O2`**: Vidutinio lygio optimizacija
- **`-O3`**: Maksimali optimizacija

### Testavimo rezultatai
STRUCT
| Optimizacijos lygis | 1000000 | 10000000 | exe |
|---------------------|---------|----------|-----|
| `-O1`               | 10.4 s  |  73.2  s | 73KB|
| `-O2`               | 8.96 s  |  71.59 s | 79KB|
| `-O3`               | 9.56 s  |  71.06 s | 85KB|

CLASS
| Optimizacijos lygis | 1000000 | 10000000 | exe |
|---------------------|---------|----------|-----|
| `-O1`               | 9.10 s  |  83.19 s | 75KB|
| `-O2`               | 8.89 s  |  71.7 s  | 89KB|
| `-O3`               | 8.75 s  |  65 s    | 95KB|

Išvados: greičiausiai veikia '-O3' optimizacija, tačiau jis užima daugiausiai vietos.

<h1>V1.0</h1>
v1.0 versija yra galutinė projekto realizacija, kurioje atliktas optimizavimas studentų rūšiavimo procese naudojant skirtingus konteinerius: vector ir list. Buvo išbandytos trys strategijos, kai studentai skirstomi į dvi kategorijas – "vargšiukai" ir "kietiakiai". Pirmoji strategija apima bendro studentų konteinerio dalijimą į du naujus konteinerius. Antroji strategija naudoja tik vieną papildomą konteinerį "vargšiukams", o trečioji strategija optimizuoja geriau veikiančią strategiją. Programos greičio analizė buvo atlikta tiek vector, tiek list konteinerių atveju, lyginant laiką, praleistą atliekant kiekvieną žingsnį. Gauti rezultatai buvo pateikti su laiko matavimais ir palyginimais, įskaitant vidurkius, gautus su skirtingais studentų skaičiais. Pridėtos naudojimo ir idiegimo instrukcijos, bei paruoštas MakeLists.txt ir run.bat failas diegimui bet kokioje operacinėje sistemoje. 

<h1>Naudojimo instrukcija</h1>
CMake: Įdiegta CMake (versija 3.25 ar vėlesnė)
Kompiliatorius: Turėti C++ kompiliatorių, kad galėtumėte sukompiliuoti projektą.
CMake ir run.bat failas buvo išbandyti Windows aplinkoje

<h1>Projekto struktūra</h1>
CMakeLists.txt: failas naudojamas CMake projekto konfigūracijai ir kompiliavimui
run.bat: Windows .bat failas, skirtas paleisti programą.

<h1>Programos diegimas ir paleidimas</h1>
Klonuokite projektą į savo kompiuterį, paleidimas su run.bat atliks visus reikalingus veiksmus, t.y. sukompiliuos ir paleis programą


<h1>Veikimo greičio analizė</h1>
NAUDOJANT VEKTORIUS (3 strategija paremta 1 strategija)

| 1000 studentų         | 1strat.    | 2strat.    | 3strat.    |
|-----------------------|------------|------------|------------|
| Failo nuskaitymas     | 0.00761 s  | 0.00486 s  | 0.00360 s  |
| Rūšiavimas            | 0.00015 s  | 0.00011 s  | 0.00015 s  |
| Dalijimas į grupes    | 4.88282 s  | 3.73956 s  | 0.00248 s  |
| Vargšių išsaugojimas  | 0.01343 s  | 0.00327 s  | 0.02096 s  |
| Kietekų išsaugojimas  | 0.00198 s  | 0.00252 s  | 0.00518 s  |
| Bendras laikas        | 8.42566 s  | 4.60796 s  | 2.5198 s   |

| 10000 studentų        | 1strat.    | 2strat.    | 3strat.    |
|-----------------------|------------|------------|------------|
| Failo nuskaitymas     | 0.03253 s  | 0.03209 s  | 0.03099 s  |
| Rūšiavimas            | 0.00127 s  | 0.00125 s  | 0.00119 s  |
| Dalijimas į grupes    | 0.72657 s  | 1.03246 s  | 1.34269 s  |
| Vargšių išsaugojimas  | 0.01981 s  | 0.02029 s  | 0.01777 s  |
| Kietekų išsaugojimas  | 0.01860 s  | 0.01685 s  | 0.01688 s  |
| Bendras laikas        | 1.99102 s  | 3.06113 s  | 16.5476 s  |

| 100000 studentų       | 1strat.    | 2strat.    | 3strat.    |
|-----------------------|------------|------------|------------|
| Failo nuskaitymas     | 0.31188 s  | 0.30137 s  | 0.30469 s  |
| Rūšiavimas            | 0.01117 s  | 0.00875 s  | 0.00665 s  |
| Dalijimas į grupes    | 1.00103 s  | 20.2939 s  | 1.20666 s  |
| Vargšių išsaugojimas  | 0.20047 s  | 0.23404 s  | 0.16695 s  |
| Kietekų išsaugojimas  | 0.18373 s  | 0.32992 s  | 0.16738 s  |
| Bendras laikas        | 2.54428 s  | 32.6574 s  | 3.05906 s  |

| 1000000 studentų      | 1strat.    | 2strat.    | 3strat.    |
|-----------------------|------------|------------|------------|
| Failo nuskaitymas     | 3.20199 s  | 2.95 s     | 3.10161 s  |
| Rūšiavimas            | 0.09095 s  | 0.10  s    | 0.07144 s  |
| Dalijimas į grupes    | 1.35433 s  | 183.96 s   | 1.47273 s  |
| Vargšių išsaugojimas  | 1.8513 s   | 1.73 s     | 1.63293 s  |
| Kietekų išsaugojimas  | 1.91238 s  | 1.77 s     | 1.65165 s  |
| Bendras laikas        | 9.82996 s  | 190.51 s   | 10.3526 s  |

| 10000000 studentų     | 1strat.    | 2strat.    | 3strat.    |
|-----------------------|------------|------------|------------|
| Failo nuskaitymas     | 33.5131 s  | 29.41 s    | 31.5896 s  |
| Rūšiavimas            | 1.00636 s  | 1.18 s     | 0.89778 s  |
| Dalijimas į grupes    | 5.25079 s  | 1827.20 s  | 3.45435 s  |
| Vargšių išsaugojimas  | 22.9855 s  | 17.14 s    | 16.6124 s  |
| Kietekų išsaugojimas  | 23.9737 s  | 17.71 s    | 16.5767 s  |
| Bendras laikas        | 233.74 s   | 1892.64 s  | 72.3017 s  |

NAUDOJANT LISTUS ( 3 strategija paremta 2 strategija)

| 1000 studentų         | 1strat.    | 2strat.    | 3strat.    |
|-----------------------|------------|------------|------------|
| Failo nuskaitymas     | 0.00773 s  | 0.00927 s  | 0.00727 s  |
| Rūšiavimas            | 0.00012 s  | 0.00012 s  | 0.00014 s  |
| Dalijimas į grupes    | 1.28421 s  | 3.07488 s  | 1.51019 s  |
| Vargšių išsaugojimas  | 0.00233 s  | 0.00328 s  | 0.00642 s  |
| Kietekų išsaugojimas  | 0.00180 s  | 0.00188 s  | 0.00214 s  |
| Bendras laikas        | 3.8796 s   | 4.53979 s  | 2.747 s   |

| 10000 studentų        | 1strat.    | 2strat.    | 3strat.    |
|-----------------------|------------|------------|------------|
| Failo nuskaitymas     | 0.03489 s  | 0.03181 s  | 0.03406 s  |
| Rūšiavimas            | 0.00120 s  | 0.00167 s  | 0.00141 s  |
| Dalijimas į grupes    | 0.69206 s  | 0.73619 s  | 1.23677 s  |
| Vargšių išsaugojimas  | 0.01947 s  | 0.01797 s  | 0.03087 s  |
| Kietekų išsaugojimas  | 0.01972 s  | 0.01727 s  | 0.02122 s  |
| Bendras laikas        | 1.55398 s  | 1.64636 s  | 1.71895 s  |

| 100000 studentų       | 1strat.    | 2strat.    | 3strat.    |
|-----------------------|------------|------------|------------|
| Failo nuskaitymas     | 0.30813 s  | 0.31262 s  | 0.30469 s  |
| Rūšiavimas            | 0.01772 s  | 0.01741 s  | 0.00665 s  |
| Dalijimas į grupes    | 0.72240 s  | 0.96874 s  | 1.20666 s  |
| Vargšių išsaugojimas  | 0.18533 s  | 0.18000 s  | 0.16695 s  |
| Kietekų išsaugojimas  | 0.18792 s  | 0.16677 s  | 0.16738 s  |
| Bendras laikas        | 1.99891 s  | 2.50482 s  | 1.05906 s  |

| 1000000 studentų      | 1strat.    | 2strat.    | 3strat.    |
|-----------------------|------------|------------|------------|
| Failo nuskaitymas     | 3.15644 s  | 3.15162 s  | 3.10161 s  |
| Rūšiavimas            | 0.44547 s  | 0.41954 s  | 0.07144 s  |
| Dalijimas į grupes    | 1.36666 s  | 1.11087 s  | 1.47273 s  |
| Vargšių išsaugojimas  | 1.85679 s  | 1.78047 s  | 1.63293 s  |
| Kietekų išsaugojimas  | 1.88834 s  | 1.70223 s  | 1.65165 s  |
| Bendras laikas        | 9.61942 s  | 10.1021 s  | 8.9788 s  |

| 10000000 studentų     | 1strat.    | 2strat.    | 3strat.    |
|-----------------------|------------|------------|------------|
| Failo nuskaitymas     | 32.0184 s  | 39.5674 s  | 53.5628 s  |
| Rūšiavimas            | 8.84735 s  | 8.02002 s  | 12.5413 s  |
| Dalijimas į grupes    | 24.4318 s  | 9.45965 s  | 6.34725 s  |
| Vargšių išsaugojimas  | 21.3181 s  | 18.0253 s  | 27.3896 s  |
| Kietekų išsaugojimas  | 21.8156 s  | 17.3682 s  | 26.0323 s  |
| Bendras laikas        | 289.799 s  | 144.252 s  | 137.652 s  |


<h1>V0.3</h1>
Ši programa skirta studentų duomenų įvedimui, generavimui, nuskaitymui iš failo ir jų analizavimui, įskaitant rūšiavimą, grupavimą,
bei išvedimą į skirtingus failus. Apskaičiuojamas vidurkius ir medianas, studentai išrušiuojami pagal didėjantį/mažėjantį vidurkį ir
suskirstomi į kategorijas "kietiakai" ir "vargšiai". Yra du programos kodai viename naudojami vektoriai, kituose listai, atlikus analizę ir paskaičiavus programos veikimo laiko vidurkius pastebime, kad programos veikimas naudojant listus užtrunka daug ilgiau nei vektorius.

| 1000 studentų         | Vektorius  | Listas     |
|-----------------------|------------|------------|
| Failo nuskaitymas     | 0.00506 s  | 0.03374 s  |
| Rūšiavimas            | 0.00015 s  | 0.00028 s  |
| Dalijimas į grupes    | 0.00023 s  | 0.00028 s  |
| Vargšių išsaugojimas  | 0.00498 s  | 0.02096 s  |
| Kietekų išsaugojimas  | 0.00204 s  | 0.01257 s  |
| Bendras laikas        | 1.50272 s  | 1.84917 s  |

| 10000 studentų        | Vektorius  | Listas     |
|-----------------------|------------|------------|
| Failo nuskaitymas     | 0.02669 s  | 0.10784 s  |
| Rūšiavimas            | 0.00082 s  | 0.002  s   |
| Dalijimas į grupes    | 0.00087 s  | 0.002 s    |
| Vargšių išsaugojimas  | 0.01624 s  | 0.1117 s   |
| Kietekų išsaugojimas  | 0.01561 s  | 0.0692 s   |
| Bendras laikas        | 1.03115 s  | 2.5817 s   |

| 100000 studentų       | Vektorius  | Listas     |
|-----------------------|------------|------------|
| Failo nuskaitymas     | 0.25901 s  | 0.5901 s   |
| Rūšiavimas            | 0.00667 s  | 0.0304 s   |
| Dalijimas į grupes    | 0.00877 s  | 0.0516 s   |
| Vargšių išsaugojimas  | 0.14073 s  | 0.3413 s   |
| Kietekų išsaugojimas  | 0.14540 s  | 0.4064 s   |
| Bendras laikas        | 1.12741 s  | 2.5918 s   |

| 1000000 studentų      | Vektorius  | Listas     |
|-----------------------|------------|------------|
| Failo nuskaitymas     | 2.65807 s  | 5.4135 s   |
| Rūšiavimas            | 0.07008 s  | 0.8598 s   |
| Dalijimas į grupes    | 0.11358 s  | 0.5529 s   |
| Vargšių išsaugojimas  | 1.41486 s  | 2.8269 s   |
| Kietekų išsaugojimas  | 1.44917 s  | 3.0424 s   |
| Bendras laikas        | 6.81376 s  | 91.606 s   |

| 10000000 studentų     | Vektorius  | Listas     |
|-----------------------|------------|------------|
| Failo nuskaitymas     | 27.0854 s  | 70.177 s   |
| Rūšiavimas            | 0.85670 s  | 14.633 s   |
| Dalijimas į grupes    | 1.06694 s  | 11.406 s   |
| Vargšių išsaugojimas  | 14.4879 s  | 38.104 s   |
| Kietekų išsaugojimas  | 14.704  s  | 37.76 s    |
| Bendras laikas        | 65.1082 s  | 175.06 s   |


Testavimo sistemos parametrai:
CPU: 11th Gen Intel® Core™ i7-11800H @ 2.30 GHz
RAM: 8.00 GB
SSD: Micron_2400_MTFDKBA512QFM

<h1>V0.2</h1>
Ši v0.2 versija prideda galimybę generuoti penkis atsitiktinių studentų sąrašų failus su 1 000, 10 000, 100 000, 1 000 000 ir
10 000 000 įrašų. Studentų vardai ir pavardės generuojami šabloniškai. Po to studentai suskirstomi į dvi grupes pagal jų galutinį 
balą: "vargšiukai" (balas < 5.0) ir "kietiakiai" (balas >= 5.0). Surūšiuoti studentai išvedami į du atskirus failus.
Programa taip pat atlieka spartą analizuojant keturis žingsnius: failų kūrimą, duomenų nuskaitymą, studentų rūšiavimą 
ir surūšiuotų duomenų išvedimą. Testavimas atliekamas naudojant įvairių dydžių sugeneruotus duomenų failus, o laiko matavimai 
atlikti kiekvienam žingsniui.

<h1>V0.1</h1>
Projekto v0.1 versijoje sukurta programa, kuri leidžia įvesti studentų duomenis (vardas, pavardė, namų darbų ir egzamino rezultatai),
apskaičiuoti galutinį balą naudojant vidurkį arba medianą. Duomenys gali būti įvedami rankiniu būdu arba nuskaityti iš failo
(kursiokai.txt). Studentai rūšiuojami pagal vardą/pavardę, o išvedimas yra tinkamai suformatuotas.
Programa taip pat leidžia generuoti atsitiktinius balus.

 
