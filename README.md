Ši programa skirta studentų duomenų įvedimui, generavimui, nuskaitymui iš failo ir jų analizavimui, įskaitant rūšiavimą, grupavimą,
bei išvedimą į skirtingus failus. Apskaičiuojamas vidurkius ir medianas, studentai išrušiuojami pagal didėjantį/mažėjantį vidurkį ir
suskirstomi į kategorijas "kietiakai" ir "vargšiai". Yra du programos kodai viename naudojami vektoriai, kituose listai, atlikus analizę 
ir paskaičiavus programos veikimo laiko vidurkius pastebime, kad programos veikimas naudojant listus užtrunka daug ilgiau nei vektorius.

#V0.1
Projekto v0.1 versijoje sukurta programa, kuri leidžia įvesti studentų duomenis (vardas, pavardė, namų darbų ir egzamino rezultatai),
apskaičiuoti galutinį balą naudojant vidurkį arba medianą. Duomenys gali būti įvedami rankiniu būdu arba nuskaityti iš failo
(kursiokai.txt). Studentai rūšiuojami pagal vardą/pavardę, o išvedimas yra tinkamai suformatuotas.
Programa taip pat leidžia generuoti atsitiktinius balus.

#V0.2 
Ši v0.2 versija prideda galimybę generuoti penkis atsitiktinių studentų sąrašų failus su 1 000, 10 000, 100 000, 1 000 000 ir
10 000 000 įrašų. Studentų vardai ir pavardės generuojami šabloniškai. Po to studentai suskirstomi į dvi grupes pagal jų galutinį 
balą: "vargšiukai" (balas < 5.0) ir "kietiakiai" (balas >= 5.0). Surūšiuoti studentai išvedami į du atskirus failus.
Programa taip pat atlieka spartą analizuojant keturis žingsnius: failų kūrimą, duomenų nuskaitymą, studentų rūšiavimą 
ir surūšiuotų duomenų išvedimą. Testavimas atliekamas naudojant įvairių dydžių sugeneruotus duomenų failus, o laiko matavimai 
atlikti kiekvienam žingsniui. 

#V0.3


Testavimo sistemos parametrai:
CPU: 11th Gen Intel® Core™ i7-11800H @ 2.30 GHz
RAM: 8.00 GB
SSD: Micron_2400_MTFDKBA512QFM
