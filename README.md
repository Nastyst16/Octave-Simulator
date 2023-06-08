# Octave-Simulator
### PCLP 1 Homework 2 -> Octave language simulator in C

    Copyright 2022
    Nastase Cristian-Gabriel Grupa 315CA
    Tema 2
    PCLP

              -Simulator de Octave-

      Am considerat ca folosirea structurilor va duce la o rezolvare a temei
    mult mai organizata. Astfel, declaram vectorul ( *v ) de structuri, in care avem
    posibilitatea de a stoca:
        -- **a care reprezinta matricea;
        -- m (linii) care reprezinta numarul de linii al matricii;
        -- n (coloane) care reprezinta numarul de coloane al matricii;
      Pentru fiecare v[index] vom avea cate o matrice (**a) si totodata si
    dimensiunile acesteia (m si n).

      Citim litere introduse de la tastatura pana in momentul in care se introduce
    valoarea 'Q'. Astfel programul intra in case 'Q', initializeaza variabila
    'ok' cu 0 si astfel while-ul se va incheia;

      Prin intermediul structurii de decizie "switch" avem posibilitatea
    sa tratam fiecare caz special in parte:

      a) In cazul aparitiei literei 'L':
      Se introduce o matrice noua, astfel trebuie sa realocam dimensiunea vectorului
    de structuri (v), facandu-l cu un element mai mare. Totodata nu uitam de programarea
    defensiva.
      Acum ca avem unde sa stocam matricea noua, apelam functia 'citire_matrice', care
    contine toate instructiunile necesare pentru indeplinirea taskului: citirea dimensiunii
    si elementelor matricei noi.

      b) In cazul aparitiei literei 'D':
      Apelam functia 'afisare_dimensiuni_matrice', care verifica existenta matricei, iar
    daca acest aspect este adevarat afisam dimensiunile matricei corespunzatoare indexului.

      c) In cazul aparitiei literei 'P':
      Apelam functia 'afisare_matrice', care verifica existenta matricei, iar daca acest
    aspect este adevarat, afisam elementele matricei corespunzatoare indexului.

      d) In cazul aparitiei literei 'C':
      Apelam functia 'redimensionare_matrice' (verificam existenta ei). Citim de la
    tastatura numarul de linii, numarul de coloane, si valorile pentru care se doreste
    redimensionarea. Stocam aceste valori in doi vectori separati.
      Ne folosim de o matricea ajutatoare (**matrice_noua), pe care o alocam dinamic in
    functie de 'linii' si 'coloane', copiem in ea valorile corespunzatoare.
      Dealocam matricea veche, deoarece dimensiunile acesteia se schimba, si nu dorim
    sa avem leak-uri de memorie.
      Alocam din nou matricea, de data asta cu dimensiunile corespunzatoare, copiem in
    aceasta, valorile din matricea ajutatoare.
      Matricea ajutatoare si-a indeplinit scopul, iar acum trebuie sa o eliberam.

      e) In cazul aparitiei literei 'M':
      Citim indicii matricelor care trebuiesc inmultite (ne asiguram ca aceste matrici exista;
    ne asiguram ca matricile se pot inmulti), iar apoi realocam vectorul de structuri
    cu inca un element in plus, intrucat rezulatul operatiei de inmultire va fi adaugat la finalul
    multimii de matrici (adica in *v).
      Se apeleaza functia 'inmultire_matrici'. Alocam noua matrice din capatul vectorului
    de structuri *v. Facem programare defensiva pentru a ne asigura ca totul functioneaza optim.
    Aplicam algoritmul clasic de inmultire a matricilor.

      f) In cazul aparitiei literei 'O':
      Se apeleaza functia 'sortare_matrici', in care se foloseste algoritmul clasic de
    interschimbare a variabilelor, doar ca acum interschimbam structuri. Sortarea se face in
    functie de suma tuturor elementelor, asa ca am creeat inca o functie ('suma_elemente_matrice').

      g) In cazul aparitiei literei 'T':
      Se apeleaza functia 'transpunere_matrice'. Ne folosim de o matrice ajutatoare (**m), pe care
    o alocam in functie de inversul dimensiunilor matricii pe care dorim sa o transpunem.
    Copiem in aceasta valorile din matricea veche.
      Deaclocam matricea veche, deoarece dimensiunile matricii se schimba, si nu dorim sa avem
    leak-uri de memorie. Urmeaza din nou alocarea matricii noi, de data aceasta cu dimensiunile
    corespunzatoare. Copiem in matricea noua elementele din matricea ajutatoare.
      Matricea ajutatoare nu mai are vreo intrebuintare, asa ca o eliberam.

      h) In cazul aparitiei literei 'R':
      Se apeleaza functia 'ridicare_putere_logaritmic'. Verificam existenta matricii; verificam daca
    matricea este patratica.
      Ne folosim de 3 matrici ajutatoare: **rezultat, **N, **copie, pe care le alocam dinamic.
    De-a lungul functiei initializam elementele din matricea 'rezultat' cu 0, deoarece utilizam operatia
    de adunare si nu dorim sa se schimbe suma. Folosim algoritmul de ridicare la putere de complexitate
    logaritmica de pe "infoarena".
      Nu mai avem nevoie de matricile ajutatoare, asa ca le eliberam.

      i) In cazul aparitiei literei 'F':
      Se verifica existenta matricii. Se apeleaza functia 'eliminare_matrice'. Dealocam
    matricea corespunzatoare indexului, deoarece dimensiunile se schimba. O alocam din nou cu noile
    dimensiuni si copiem elementele din urmatoarea matrice. Toti acesti pasi sunt cuprinsi intr-un
    'for' deoarece trebuie sa mutam fiecare matrice in parte cu cate o pozitie la stanga.
      Atunci cand iesim din functie, trebuie sa realocam vectorul de structuri si sa il scadem cu
    un element.

      j) In cazul aparitiei litrei 'Q':
      Se apeleaza functia 'dealocare_matrici'. Ne pregatim pentru sfarsitul programului si atfel
    trebuie sa dealocam absolut toate matricile, dar si vectorul de structuri.

      k) In cazul aparitiei unei litere necorespunzatoare afisam "Unrecognized command".

      De-a lungul programului am creat 14 functii care ma ajuta in rezolvarea temei 2.
