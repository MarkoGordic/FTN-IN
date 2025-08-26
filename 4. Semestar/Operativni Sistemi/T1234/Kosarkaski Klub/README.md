# Košarkaški Klub

<center>
<img src="./image.png" alt="USB" width="500"/>
</center>

## Zadatak

Bila je hladna zimska noć u Crnoj Gori. Nakon duge sezone i brojnih utakmica, došao je trenutak da se trener osvrne na učinak svojih košarkaša i košarkašica. Želeo je da nagradi one sa najboljim rezultatima, pa je zbog velike konkurencije morao da sprovede detaljne proračune.

## Ulazni podaci

Ulazni podaci se nalaze u datoteci **`kosarkasi.txt`**.  
Svaki red sadrži informacije o jednom igraču, pri čemu su vrednosti odvojene delimiterom `:` i imaju sledeći format:

1. **ID igrača** – _int_
2. **Ime i prezime igrača** – _string_ (maksimalno 100 karaktera)
3. **Komanda** – _unsigned char_
4. **Niz rezultata** u poslednjih _x_ utakmica – niz celobrojnih vrednosti odvojenih zarezom

**Primer reda:**
`23:Sara Nikolic:1:12,15,20,22,30`

## Pravila obrade

Na osnovu komande vrši se sledeća obrada:

1. **Komanda 1** – Izračunati prosečan rezultat igrača i broj utakmica u kojima je postignuto više poena od proseka. (prosecan rezultat se prebacuje u int secenjem ostatka)
2. **Komanda 2** – Izračunati maksimalan rezultat igrača. Rezultat mora biti veci ili jedan nuli.
3. **Komanda 3** – Sortirati niz rezultata u rastućem redosledu.
4. Sve ostale komande smatraju se **nevažećim** i treba ih ignorisati.

## Izlazni podaci

Rezultati obrade se upisuju u datoteku **`izvestaj.txt`**.  
Svaki red izlazne datoteke sadrži sledeće informacije, odvojene delimiterom `:`:

1. **ID igrača** – _int_
2. **Ime i prezime igrača** – _string_ (maksimalno 100 karaktera)
3. **Rezultat obrade**

## Paralelizacija

Obrada se vrši u više niti.

1. **Ulazna nit** – čita redove iz ulazne datoteke
2. **3 niti radnika** – obrađuju redove na osnovu komande
3. **Izlazna nit** – upisuje rezultate obrade u izlaz
