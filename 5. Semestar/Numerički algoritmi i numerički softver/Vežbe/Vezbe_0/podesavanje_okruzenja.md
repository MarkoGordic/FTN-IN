# Okruženja za praktičan deo kursa

Za potrebe praktičnog dela kursa potrebno je instalirati [Python3.14](https://www.python.org/downloads/) i odgovarajuće biblioteke. Spisak svih potrebnih biblioteka sa odgovarajućim verzijama se nalazi u: 
* **requirements.txt** fajlu ovog foldera za *Linux/MacOS*  
* **requirements_win.txt** fajlu ovog foldera za *Windows*.

Postoji nekoliko načina za instalaciju biblioteka i podešavanje odgovarajućeg okruženja, a na vama je da odaberete onaj koji vam najviše odgovara:

## 1. "Prosta" instalacija biblioteka  

#### Linux i MacOS

1) Iz ovog foldera repozitorijuma preuzeti **requirements.txt** fajl
2) Instalirati biblioteke (kroz *Terminal*):  
  a) `$ pip install -r requirements.txt` - ukoliko je na mašini instaliran samo jedan Python  
  b) `$ pip3.14 install -r requirements.txt` - ukoliko je na mašini instalirano više Python-a

#### Windows  

1) Iz ovog foldera preuzeti **requirements_win.txt** fajl  
2) Instalirati biblioteke (kroz *Command Prompt* ili *Powershell*):  
  a) `> pip install -r requirements_win.txt` - ukoliko je na mašini instaliran samo jedan Python  
  b) `> pip3.14 install -r requirements_win.txt` - ukoliko je na mašini instalirano više Pythona

## 2. Virtuelno okruženje  

[venv](https://docs.python.org/3/library/venv.html) je alat za kreiranje izolovanih (virtuelnih) Python okruženja. Vrši kreiranje okruženja koje ima sopstvene instalacione direktorijume i koje ne deli pakete sa ostalim okruženjima (uključujući i globalno instalirane pakete).
Podešavanje i upotreba:

#### Linux i MacOS:  
  
1) U sklopu proizvoljnog foldera kreirati virtuelno okruženje:  
`$ cd my_folder/`  
`$ python -m venv env` ili `$ python3.14 -m venv env`
2) Preuzeti **requirements.txt** fajl, smestiti ga u folder gde ste kreirali virtuelno okruženje, aktivirati virtuelno okruženje i instalirati neophodne biblioteke:  
`$ source env/bin/activate`  
`$ pip install -r requirements.txt`  

Nakon izvršenja poslednje komande, podešavanje virtuelnog okruženja je kompletirano i ono ostaje aktivno za (eventualni) dalji rad. 

Pre početka rada sa virtuelnim okruženjem, neophodno je pozicionirati se u folder u kom je kreiran i aktivirati ga:  
`$ cd my_folder/`  
`$ source env/bin/activate`  

Nakon završetka rada, virtuelno okruženje se deaktivira pomoću sledeće komande:  
`$ deactivate`  

Instalacija novog paketa u aktivno okruženje se vrši pomoću:  
`$ pip install ime_paketa`  

Ažuriranje liste instaliranih paketa u aktivnom okruženju (**requirements.txt**) se vrši pomoću komande:  
`$ pip freeze > requirements.txt`.  

#### Windows  

Na *Windows* operativnom sistemu podešavanja i upotreba su analogna podešavanju i upotrebi na *Linux* i *MacOS* operativnim sistemima. Jedina razlika jeste prilikom aktiviranja i deaktiviranja okruženja.  
Prilikom kreiranja okruženja na *Windows* operativnom sistemu, kreiraju se aktivacione skripte za *Command Prompt* i *Powershell*, te se zbog toga aktivacija okruženja na *Windows*-u vrši pomoću komande:  
`> \path\to\env\Scripts\activate`  
Deaktivacija se vrši pomoću komande:  
`> deactivate`
