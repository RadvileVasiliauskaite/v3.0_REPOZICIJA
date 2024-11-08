cmake CMakeLists.txt
cmake --install .
cmake --build .
copy kursiokai.txt Debug\kursiokai.txt
copy studentai_1000.txt Debug\studentai_1000.txt
copy studentai_10000.txt Debug\studentai_10000.txt
copy studentai_100000.txt Debug\studentai_100000.txt
copy studentai_1000000.txt Debug\studentai_1000000.txt
copy studentai_10000000.txt Debug\studentai_10000000.txt
cd Debug\
projektas2.exe
pause
