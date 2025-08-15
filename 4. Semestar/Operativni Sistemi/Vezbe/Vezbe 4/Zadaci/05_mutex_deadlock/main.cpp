/*
Napisati konkurentni program koji stvara 2 niti od funkcije f. Funkcija f treba da prolazi kroz petlju dužine 10000 elemenata i ispisuje parne ili neparne brojeve (među tih 10000 elemenata).

Ispis parnih ili neparnih brojeva se vrši pozivom funkcija ispisi_parne i ispisi_neparne. U funkciji ispisi_parne prvo se pre ispisa zaključava muteks m1, a potom muteks m2. U funkciji ispisi_neparne prvo se pre ispisa zaključava muteks m2, a potom muteks m1.

Sva zaključavanja se vrše kroz objekte klase unique_lock.

Pratiti izvršavanje programa.
*/

