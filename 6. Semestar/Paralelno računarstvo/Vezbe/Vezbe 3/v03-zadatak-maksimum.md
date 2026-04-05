# Zadatak3 PR

Napisati C++ program koji omogucava korisniku unos niza (vise od 4 elementa), deli niz na cetiri priblizno jednaka dela i na izlazu ispisuje maksimum svake cetvrtine niza i ukupan broj parnih elemenata u nizu.

Potrebno je pokrenuti cetiri asinhrone funkcije (obavezno koristiti **async**) i omoguciti im da traze maksimume u dodeljenim delovima niza istovremeno. Pokrenuti i petu **nit za ispisivanje** koja se paralelno izvrsava sa prethodne cetiri niti i njena uloga je ispisivanje lokalnih maksimuma koje asinhrone funkcije pronadju u obrnutom redosledu. Lokalni maksimum koji pronalazi nit koja radi nad poslednjom cetvrtinom niza ce se prvi ispisati na konzoli. Posle toga, ispisuje se maksimum pronadjen u pretposlednjoj cetvrtini niza... Rezultat niti koja radi nad prvom cetvrtinom niza se poslednji ispisuje u konzoli.

Uz pronalazenje lokalnih maksimuma niti istovremeno broje i koliko parnih elemenata ima u nizu (svaka nit broji parne elemente nad delom niza koji joj je dodeljen). Pri brojanju parnih elemenata koristiti **atomicne promenljive**. Nakon zavrsetka svih pet prethodno spomenutih niti, ispisati u konzoli koliki je ukupan broj parnih elemenata u celom nizu.

Pri izradi zadatka obavezno je koriscenje **lambda funkcija**.
