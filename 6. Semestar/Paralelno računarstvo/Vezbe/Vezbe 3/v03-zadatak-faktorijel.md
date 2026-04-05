# Zadatak2 PR

Napisati C++ program koji omogucava korisniku unos prirodnog broja N (vece od 8), deli opseg [1, N] na cetiri priblizno jednaka dela i na izlazu ispisuje parcijalne proizvode svake cetvrtine opsega i ukupan faktorijel broja N.

Potrebno je pokrenuti cetiri asinhrone funkcije (obavezno koristiti **async**) i omoguciti im da racunaju parcijalne proizvode u dodeljenim delovima opsega istovremeno. Svaka asinhrona funkcija mnozi sve brojeve u svom delu opsega i vraca rezultat kao parcijalni proizvod. Pokrenuti i petu **nit za ispisivanje** koja se paralelno izvrsava sa prethodne cetiri niti i njena uloga je ispisivanje parcijalnih proizvoda koje asinhrone funkcije izracunaju u obrnutom redosledu. Parcijalni proizvod koji racuna nit koja radi nad poslednjom cetvrtinom opsega ce se prvi ispisati na konzoli. Posle toga, ispisuje se parcijalni proizvod izracunat u pretposlednjoj cetvrtini opsega... Rezultat niti koja radi nad prvom cetvrtinom opsega se poslednji ispisuje u konzoli.

Uz racunanje parcijalnih proizvoda, niti istovremeno racunaju i zbir svih brojeva u opsegu [1, N] (svaka nit racuna zbir nad delom opsega koji joj je dodeljen). Pri racunanju zbira koristiti **atomicne promenljive**. Nakon zavrsetka svih pet prethodno spomenutih niti, ispisati u konzoli koliki je ukupan faktorijel broja N (proizvod svih parcijalnih proizvoda) kao i zbir svih brojeva od 1 do N.

Pri izradi zadatka obavezno je koriscenje **lambda funkcija**.
