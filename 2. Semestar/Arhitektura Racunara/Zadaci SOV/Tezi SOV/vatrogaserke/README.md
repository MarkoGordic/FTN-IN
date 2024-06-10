# Vatrogaserke 🚒

Naše omiljene vatrogaserke, Aleks i Jomi, su se upravo prijavile na dužnost! Potrebna im je vaša pomoć... Računar u vatrogasnoj stanici se pokvario i prikazuje sve informacije o njihovoj potrošnji vode u heksadecimalnim vrednostima. Nažalost, one ne znaju da čitaju te brojeve i zbog toga nisu u mogućnosti da pomognu ljudima. Morate biti brzi!

Potrebno je napisati asemblerski program koji na ulazu prima sledeći string:
```
Z-A V-0x32,Z-A V-0x11,Z-J V-0x1E,Z-A V-0xAa,Z-J V-0xFFF,Z-J V-0xa1c
```

Z označava zaposlenog, A je Aleks, a J je Jomi. V obeležava količinu vode u litrima koju je ta vatrogaserka potrošila tokom te intervencije. Potrebno je izračunati ukupnu količinu potrošene vode za Aleks i Jomi u litrima, kao i ispisati poruku o tome ko je potrošio više vode. Brojevi na izlazu trebaju da budu u bazi 10. Tokom obrade stringa, program treba da ispiše poruku greške "Došlo je do greške tokom rada programa!\n" i prekine rad ukoliko se desi nešto od sledećeg:

1. Broj ne počne sa 0x
2. Posle 0x nisu mala ili velika slova od A-F ili cifre. Dozvoljeno je mešati mala i velika slova
3. Ukoliko dođe do prekoračenja
4. Vatrogaserke mogu biti samo Aleks i Jomi, tako da vrednost zaposlenog sme biti samo A ili J

Primer interakcije sa programom:
```
Unesite informacije o vatrogaserkama: Z-A V-0x32,Z-A V-0x11,Z-J V-0x1E,Z-A V-0xAa,Z-J V-0xFFF,Z-J V-0xa1c 

Aleks je ukupno potrošila X litara vode.
Jomi je ukupno potrošila X litara vode.

X je potrošila više vode od X.
```