# Obrada grešaka

> [!IMPORTANT] 
> Ovaj tekst je generisan veštačkom inteligencijom (AI) i služi kao pomoćni materijal za učenje. Iako je AI sposoban da generiše informativan i koristan sadržaj, važno je imati na umu da može doći do grešaka, netačnosti ili zastarelih informacija. Preporučuje se da se ovaj tekst koristi kao dodatni resurs, a ne kao jedini izvor informacija.

## Greške u kontekstu prevodioca

Obrada grešaka je sastavni deo faze analize prevodioca. Kroz sve faze analize (leksička, sintaksna, semantička) provlači se potreba za prepoznavanjem, izveštavanjem i obradom grešaka, kao i upravljanjem procesom oporavka od grešaka.

Greške koje se mogu pojaviti prilikom korišćenja programskog jezika mogu se podeliti u dve velike kategorije:

**Greške prilikom implementacije programa u nekom jeziku:**

- Leksičke greške - neprepoznati karakteri ili sekvence
- Sintaksne greške - neispravna struktura programa
- Semantičke greške - program nema smisla (pogrešni tipovi, nedeklarisane promenljive...)

**Greške prilikom izvršavanja programa:**

- Programer - logička greška u implementaciji programa (uključuje i dinamičku semantiku)
- Mi (autori kompajlera) - greška u implementaciji samog kompajlera

Kao autori kompajlera, moramo prepoznati što više grešaka i dati što više informacija o njima. Moramo obezbediti kvalitetnu dokumentaciju i jezik učiniti intuitivnim. Moramo maksimalno smanjiti mogućnosti da se naše greške dese. I moramo dati informativne poruke ukoliko je moguće, uzimajući u obzir ograničenja.

## Leksičke greške

Leksička greška nastaje ako prilikom skeniranja naiđemo na nešto što ne pripada jeziku - nešto što ne odgovara nijednom regularnom izrazu. Na primer, u miniC-u, operator `*` ne postoji, ili identifikator koji ne zadovoljava pravila formiranja.

U flex-u, leksička greška se obrađuje podrazumevanim pravilom koje hvata neprepoznate karaktere:

```c
// jezik.l
{ printf("line %d: LEXICAL ERROR on char %c\n", yylineno, *yytext); }
```

## Sintaksne greške

Sintaksna greška nastaje ako prilikom parsiranja ne možemo da pronađemo nijedno pravilo po kome redukujemo. Bison automatski poziva funkciju `yyerror` kada detektuje sintaksnu grešku.

```c
// jezik.y
int yyerror(char *s) {
    fprintf(stderr, "\nline %d: ERROR: %s", yylineno, s);
    return 0;
}
```

Funkcija `yyerror` je funkcija koju mi moramo da definišemo. Bison je poziva svaki put kada parser otkrije sintaksnu grešku. Nakon toga, `yyparse` vraća 1 ili pokušava oporavak od greške.

Povratne vrednosti `yyparse`:

- **0** - parsiranje je uspešno
- **1** - sintaksna greška ili je parsiranje prekinuto
- **2** - nema dovoljno memorije

## Semantičke greške

Semantička greška nastaje kada utvrdimo da je narušeno neko semantičko pravilo. U micko-u, to se radi pozivom `yyerror` na odgovarajućem mestu u kodu:

```c
if(lookup_symbol("main", FUN) == NO_INDEX)
    err("undefined reference to 'main'");
```

Makro `err` je definisan u micko-u za jednostavnije formatiranje poruka:

```c
#define err(args...) sprintf(char_buffer, args), \
                     yyerror(char_buffer)

char char_buffer[CHAR_BUFFER_LENGTH];
```

## Ključna razlika: sintaksna vs. semantička greška

Ovo je izuzetno važna razlika koju treba dobro razumeti.

**Sintaksna greška:**

- Poruka nam je stigla "od bisona"
- Bison je otkrio grešku u gramatici (nije pronađeno pravilo za redukciju)
- Stanje mašine je u stanju greške
- Podrazumevana poruka je "syntax error"
- Parsiranje se zaustavlja (osim ako postoji mehanizam oporavka)

**Semantička greška:**

- Poruka nam je stigla od nas (iz naših akcija)
- Bison je i dalje u procesu parsiranja/sintakse, a ne semantike
- Nema greške u gramatici - sintaksa je ispravna
- Stanje mašine nije u stanju greške
- Naša poruka se ispisuje
- Parsiranje nastavlja normalno jer se nikad nije ni zaustavilo

Drugim rečima, kod semantičke greške iskorišćeno je parsiranje (sintaksa) za detekciju grešaka. Samo je detektovana greška i ispisana poruka. Parser nije u stanju greške. Analiza se nastavlja jer se nikad nije ni zaustavila - nije se pokretao nikakav proces oporavljanja od greške.

### Primer iz prakse

Test fajl `test-synerr1.mc` (nedostaje `num_exp` kod return):

```
line 9: ERROR: syntax error
1 error(s).
```

Test fajl `test-semerr2.mc` (nedefinisane promenljive):

```
line 5: ERROR: 'r1' undeclared
line 5: ERROR: 'r2' undeclared
2 error(s).
```

U prvom slučaju, bison je otkrio grešku i zaustavio se. U drugom slučaju, mi smo detektovali greške, ali parsiranje je nastavilo normalno i pronašlo obe greške.

## Dva ključna pitanja

Na osnovu ove razlike, nameću se dva pitanja:

1. **Da li ipak možemo semantičku grešku da tretiramo kao sintaksnu?** - Da, koristeći makro `YYERROR`.
2. **Da li ipak možemo da nastavimo parsiranje kad detektujemo sintaksnu grešku?** - Da, koristeći mehanizam oporavka od greške (error recovery).

## YYERROR - semantička greška tretirana kao sintaksna

Makro `YYERROR` eksplicitno generiše sintaksnu grešku bez ponovnog poziva `yyerror`. Inicira proces oporavka od greške.

Primer - nedefinisane promenljive tretirane kao sintaksna greška:

```c
//OPIS: Nedefinisane promenljive
int abs(int i) {
    int res;
    if(r1 < r2)
        res = 0 - i;
    else
        res = i;
    return res;
}
int main() {
    return abs(-5);
}
```

Bez `YYERROR`:

```yacc
exp : literal
    | _ID
      {
          $$ = lookup_symbol($1, VAR|PAR);
          if($$ == NO_INDEX)
              err("'%s' undeclared", $1);
      }
    | function_call
    | _LPAREN num_exp _RPAREN
      { $$ = $2; }
    ;
```

Ovde je detektovana semantička greška, parser nastavlja normalno.

Sa `YYERROR`:

```yacc
exp : literal
    | _ID
      {
          $$ = lookup_symbol($1, VAR|PAR);
          if($$ == NO_INDEX) {
              err("'%s' undeclared", $1);
              YYERROR;
          }
      }
    | function_call
    | _LPAREN num_exp _RPAREN
      { $$ = $2; }
    ;
```

Sada se pored ispisa poruke pokreće i proces oporavka od greške kao da je u pitanju sintaksna greška.

## Oporavak od greške (Error Recovery)

Kad se naiđe na grešku, ukoliko je moguće, želimo da nastavimo parsiranje uz davanje odgovarajućih informacija o greškama. Cilj je sprečiti da `yyparse` vrati 1 odmah na prvoj grešci. Ovaj proces se zove oporavljanje/oporavak od greške (error recovery - ER).

### Pristup 1: Predviđanje greške

Možemo pretpostaviti gde će biti greška i dodati alternativno pravilo koje tu grešku hvata:

```yacc
return_statement
    : _RETURN num_exp _SEMICOLON
    | _RETURN num_exp
      { yyerror("Missing ';' \n"); }
    ;
```

Ovde smo dodali pravilo za slučaj kada nedostaje `;` na kraju return iskaza.

### Primer: nedostaje tačka-zarez

```c
int abs(int i) {
    if(i < 0)
        return 0-i;
    else
        return i *    // greška - * nije deo jezika
}
int main() {
    return abs(-5);
}
```

Izlaz:

```
line 6: ERROR: syntax error
line 6: ERROR: Missing ';'
```

Dobijamo informativniju poruku i nastavak parsiranja - oporavak od greške je uspeo jer je pronađeno pravilo.

### Primer sa dve greške

```c
int abs(int i) {
    if(i < 0)
        return 0-i *    // greška
    else
        return i *       // greška
}
int main() {
    return abs(-5);
}
```

Izlaz:

```
line 4: ERROR: syntax error
line 4: ERROR: Missing ';'
line 6: ERROR: Missing ';'
```

Obe greške su detektovane zahvaljujući oporavku od greške.

### Pristup 2: Token error

Bison ima ugrađeni token `error` koji je uvek definisan. Bison ga generiše kad god se pojavi greška. Ako imamo pravilo koje ga prepoznaje, imamo i mogućnost oporavka i parsiranje može da se nastavi.

Na primer, ne želimo da greška u relacionom izrazu za `if_part` prekine ceo proces parsiranja:

```yacc
if_part
    : _IF _LPAREN rel_exp _RPAREN statement
    | _IF _LPAREN error _RPAREN
      { yyerror("Error in if condition"); }
      statement
    ;
```

### Primer sa error tokenom

```c
int abs(int i) {
    if(i = 0)       // greška - = umesto ==
        return 0-i;
    else
        return i *   // greška - * nije deo jezika
}
int main() {
    return abs(-5);
}
```

Izlaz:

```
line 2: ERROR: syntax error
line 2: ERROR: syntax error
line 2: ERROR: Error in if condition
line 6: ERROR: Missing ';'
```

Greška u if uslovu je uhvaćena pomoću `error` tokena, a zatim je parsiranje nastavilo i pronašlo i drugu grešku.

### Kako error token radi (panic mode)

Postupak kada se koristi pravilo sa `error` tokenom:

1. Da bi pravilo sa `error` tokenom moglo da se primeni (da se uradi shift tokena `error`), interno se izvršava odbacivanje svega što je parsirano (ono što je trebalo da bude `rel_exp`).
2. Token `error` se postavlja na stek i čita se ulaz sve dok se ne dođe do `_RPAREN`.
3. Tada se vrši redukcija po tom pravilu.

Ovo se naziva **panic mode** error recovery. Može doći do problema sa memorijom jer se parsirani sadržaj odbacuje.

### Prevencija nagomilavanja grešaka

Error recovery za jednu grešku može dovesti do druge greške za koju imamo ER, što može dovesti do treće greške, i tako dalje. Unutrašnji mehanizam prevencije ovakvog nagomilavanja je da parser zaustavlja prijavu grešaka sve dok se tri puta uspešno ne izvrši preuzimanje tokena. Tek nakon toga se nastavlja prijava grešaka.

Postoji i makro `yyerrok` koji šalje signal da je završen proces ER i da se odmah nastavi sa prijavom grešaka (bez čekanja tri uspešna tokena).

## Smernice za obradu grešaka

Implementacija error recovery-ja je stvar odluka i predviđanja. Smernice za dobru obradu grešaka:

- Informacija o vrsti greške (leksička, sintaksna, semantička)
- Informacija o mestu na kom dolazi do greške (linija, kolona)
- Postojanje mehanizama za oporavak od greške
- Brz oporavak od greške radi detektovanja narednih grešaka
- Bez usporavanja ispravnih programa (error handling ne sme da utiče na performanse kada nema grešaka)

## Obrada grešaka u micko kompajleru

Micko kompajler implementira obradu grešaka na sledeći način:

- **Bez implementacije oporavka od grešaka** u osnovnoj verziji
- **Sintaksne greške** - parsiranje se zaustavlja, bez nastavka
- **Semantičke greške** - parsiranje nastavlja normalno (jer parser nije u stanju greške)
- **Informacija o broju grešaka** se čuva u funkciji `yyerror`
- Verzija `[syntax-errors]` na GitHub-u ima promenjeno pravilo za IF sa `error` tokenom i odgovarajuće test primere