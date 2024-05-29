# Cigarettes After Sex 🚬🔞

Dolazi leto. Ležite na ležaljci na plaži, sunce sija, a šum talasa vas opušta. U ruci držite telefon i puštate omiljeni album benda Cigarettes After Sex. Dok tonete u muziku, odlučili ste da izračunate koliko će vam trebati vremena da poslušate sve pesme koje ste dodali u queue. Inspirisani romantičnim tonom, pišete asemblerski program koji prima sledeće stringove:

```
Apocalypse - 4:50|K. - 5:20|Each_Time_You_Fall_in_Love - 4:50|Sweet - 4:52|Young_&_Dumb - 4:33
```

ili

```
Sunsetz - 3:35|Flash - 4:34|Truly - 4:O4|John_Wayne - 4:18
```

Potrebno je voditi računa o sledećim uslovima:

1. Ime pesme sme da sadrži samo mala i velika slova, kao i znakove `.` `!` `_` `?` i `&`
2. Nakon imena pesme mora uslediti znak - (nakon svakog imena pesme će se sigurno nalaziti razmak)
3. Dužina pesme sme da sadrži samo cifre

Ukoliko nešto nije ispunjeno od zadatih uslova, potrebno je ispisati poruku greške "Doslo je do greske tokom rada programa!\n" i prekinuti rad programa.
Program treba da prođe kroz ceo string, i da izračuna ukupnu dužinu trajanja svih pesama zajedno **u sekundama**.

Primer interakcije sa programom, potrebno je rekreirati poruke:
```
Unesite pesme: Apocalypse - 4:50|K. - 5:20|Each_Time_You_Fall_in_Love - 4:50|Sweet - 4:52|Young_&_Dumb - 4:33

Ukupna duzina svih pesama u sekundama je : X sekundi
```