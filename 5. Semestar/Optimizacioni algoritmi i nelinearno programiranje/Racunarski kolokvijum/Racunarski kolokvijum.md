# Jednodimenzione numeričke metode

Kod jednodimenzione optimizacije (funkcija jedne promenljive) numeričke metode su korisne u situacijama kada je analitički teško odrediti izvode ili kada funkcija uopšte nije diferencijabilna. U praksi se zato često oslanjamo na iterativne postupke koji ili koriste informacije o izvodima (gradijentne metode), ili uopšte ne zahtevaju diferencijabilnost (metode direktnog pretraživanja), ili aproksimiraju funkciju jednostavnijim polinomom (metode aproksimacije polinomom).

U kontekstu optimizacije, cilj je da nađemo tačku optimuma (minimum ili maksimum). Ako je funkcija diferencijabilna, optimum se traži preko stacionarnih tačaka, tj. uslova $f'(x)=0$. Ako funkcija nije diferencijabilna ili ne želimo da računamo izvode, onda se oslanjamo na pretraživanje intervala u kojem se optimum nalazi.

---

## Gradijentne metode: Newton–Raphson metod (za optimum)

Da bismo našli optimum diferencijabilne funkcije $f(x)$, tražimo stacionarne tačke rešavanjem jednačine $f'(x)=0$. Ideja Newton–Raphson metode je da lokalno aproksimiramo funkciju (odnosno ovde izvod $f'(x)$) Tejlorovim razvojem oko trenutne tačke $x_k$, i zatim iz te aproksimacije dobijemo novu, bolju procenu rešenja.

Klasični Newtonov korak za rešavanje $g(x)=0$ je:
$$
x_{k+1}=x_k-\frac{g(x_k)}{g'(x_k)}.
$$
Ako postavimo $g(x)=f'(x)$, tada je $g'(x)=f''(x)$ i dobijamo Newtonovu iteraciju za nalaženje optimuma:
$$
x_{k+1}=x_k-\frac{f'(x_k)}{f''(x_k)}.
$$

Početno pogađanje (prvi korak) se često piše kao:
$$
x_1=x_0-\frac{f'(x_0)}{f''(x_0)}.
$$
Zatim se ista forma ponavlja iterativno za $k=0,1,2,\dots$.

Zaustavljanje iteracija se tipično radi preko greške između uzastopnih iterata. U beleškama su navedene dve varijante: apsolutna i relativna greška. Apsolutni kriterijum je:
$$
|x_{k+1}-x_k|<\varepsilon,
$$
a relativni kriterijum je:
$$
\left|\frac{x_{k+1}-x_k}{x_{k+1}}\right|<\varepsilon.
$$
Napomena iz beleški je da se često uzima apsolutna greška kako bismo izbegli problem deljenja nulom.

Konvergencija Newtonove metode značajno zavisi od izbora početnog pogađanja. Ako je početna tačka loša, metoda može sporo konvergirati ili čak otići ka pogrešnom rešenju.

---

## Gradijentne metode: metod sečice (secant) za optimizaciju

Metod sečice je varijanta Newtonovog pristupa u kojoj se izvodi aproksimiraju razlikama, tako da ne moramo eksplicitno računati (ili tačno znati) drugi izvod. U beleškama su zapisane aproksimacije prvog izvoda pomoću konačnih razlika:
$$
f'(x_k)\approx\frac{f(x_k)-f(x_{k-1})}{x_k-x_{k-1}},
$$
kao i ekvivalentna forma unapred:
$$
f'(x_k)\approx\frac{f(x_{k+1})-f(x_k)}{x_{k+1}-x_k}.
$$

Drugi izvod se zatim aproksimira razlikom prvih izvoda:
$$
f''(x_k)\approx\frac{f'(x_k)-f'(x_{k-1})}{x_k-x_{k-1}}.
$$

Početno pogađanje (na osnovu dve početne tačke $x_0$ i $x_1$) je zapisano kao:
$$
x_2=x_1-f'(x_1)\,\frac{x_1-x_0}{f'(x_1)-f'(x_0)}.
$$

Iterativni postupak u opštem koraku je:
$$
x_{k+1}=x_k-f'(x_k)\,\frac{x_k-x_{k-1}}{f'(x_k)-f'(x_{k-1})}.
$$

Kriterijum zaustavljanja je dat preko relativne greške:
$$
\varepsilon_{n+1}=\left|\frac{x_{n+1}-x_n}{x_{n+1}}\right|.
$$

---

# Metode direktnog pretraživanja

Metode direktnog pretraživanja su u osnovi metode jednodimenzione optimizacije koje se svode na sistematsko sužavanje zatvorenog intervala $[a,b]$. Ključna prednost je da se ne traži da funkcija bude diferencijabilna, već da bude unimodalna na intervalu (da ima jedan lokalni minimum ili maksimum u tom opsegu).

Postupak pretrage minimuma u beleškama je opisan koracima. Prvo pretpostavimo interval $[a,b]$ u kome se nalazi minimum. Zatim po nekoj formuli biramo dve tačke $x_1$ i $x_2$ unutar intervala i upoređujemo vrednosti $f(x_1)$ i $f(x_2)$. Ako je $f(x_1)<f(x_2)$, eliminišemo deo $x>x_2$ i postavljamo $b=x_2$. Ako je $f(x_1)>f(x_2)$, eliminišemo deo $x<x_1$ i postavljamo $a=x_1$. Ako je $f(x_1)=f(x_2)$, biramo novi par tačaka i nastavljamo.

Proces se ponavlja dok interval ne postane dovoljno mali. U beleškama je zapisano da se nastavlja dok širina intervala ne bude manja od $2\varepsilon$, a zatim je dodat i opšti zapis da je kraj kada je širina intervala između $a$ i $b$ manja od unapred zadatog $\varepsilon$.

Dve konkretne metode direktnog pretraživanja koje su navedene su Fibonacci-jev metod i metod zlatnog preseka.

---

## Fibonacci-jev metod

Fibonacci-jev metod sužava interval koristeći odnose Fibonacci-jevih brojeva. Fibonacci-jevi brojevi zadovoljavaju rekurziju:
$$
F_n=F_{n-1}+F_{n-2}.
$$

Algoritam počinje tako što odredimo interval $[a,b]$ koji sadrži optimalnu tačku $x^*$ i zadamo tačnost $\varepsilon>0$. Zatim biramo $n$ tako da važi:
$$
F_n>\frac{b-a}{\varepsilon},
$$
pri čemu se $n$ interpretira kao broj iteracija.

Tačke unutar intervala se biraju formulama:
$$
x_1=a+\frac{F_{n-2}}{F_n}(b-a),
$$
a druga tačka se dobija simetrično:
$$
x_2=b-\frac{F_{n-2}}{F_n}(b-a)
      =a+\frac{F_{n-1}}{F_n}(b-a),
$$
odakle u beleškama stoji i praktična veza:
$$
x_2=a+b-x_1.
$$

Nakon toga se u svakoj iteraciji izračuna novi (užи) interval na osnovu poređenja $f(x_1)$ i $f(x_2)$, i postupak se ponavlja do $k=n$.

---

## Metod zlatnog preseka

Metod zlatnog preseka je sličan Fibonacci-jevom, ali se umesto diskretnih odnosa $F_n$ koristi konstanta koja je limit odnosa Fibonacci-jevih brojeva. U beleškama je definisana konstanta:
$$
c=\frac{3-\sqrt{5}}{2}\approx 0.38197.
$$

Algoritam počinje izborom intervala $[a,b]$ koji sadrži $x^*$ i zadavanjem $\varepsilon>0$. Zatim biramo tačke:
$$
x_1=a+c(b-a),
$$
i
$$
x_2=a+b-x_1.
$$

Potom se poređenjem $f(x_1)$ i $f(x_2)$ eliminiše odgovarajući deo intervala, i postupak se ponavlja sve dok ne bude ispunjen uslov:
$$
(b-a)<\varepsilon.
$$

---

# Metode aproksimacije polinomom

Kod metoda aproksimacije polinomom, originalna funkcija $f(x)$ se aproksimira polinomom $y(x)$ na intervalu $I$ koji sadrži optimum. Zatim se minimum (ili maksimum) aproksimacione funkcije $y(x)$ određuje, i ta tačka se uzima kao procena optimuma $x_{\text{opt}}$. U okolini dobijenog $x_{\text{opt}}$ zatim se formira novi interval (manji od prethodnog) i vrši se nova aproksimacija, čime se postupak iterativno poboljšava.

U beleškama su navedene dve vrste ovih metoda: metod parabole i kubna metoda.

---

# Višedimenzioni gradijentni algoritmi

Kod višedimenzione optimizacije minimizujemo diferencijabilnu funkciju više promenljivih $f(x)=f(x_1,x_2,\dots,x_n)$. Osnovna ideja gradijentnih metoda je da se u svakoj iteraciji trenutna tačka pomera u smeru negativnog gradijenta, jer gradijent pokazuje smer najvećeg porasta funkcije, pa negativan gradijent pokazuje smer najbržeg opadanja.

Gradijent je definisan kao vektor parcijalnih izvoda:
$$
\nabla f=\left[\frac{\partial f}{\partial x_1}\ \frac{\partial f}{\partial x_2}\ \dots\ \frac{\partial f}{\partial x_n}\right]^T.
$$

---

## Metod najbržeg pada (najstrmijeg opadanja)

Metod najbržeg pada traži minimum tako što u svakoj iteraciji pomera tačku u pravcu $-\nabla f(x_k)$. Inicijalizacija podrazumeva izbor početne tačke $x_0$, izbor veličine koraka (u beleškama je navedeno da je korak pozitivan), tolerancije $\varepsilon>0$ i maksimalnog broja iteracija $N$.

Osnovni iterativni korak je:
$$
X_{k+1}=X_k-\varepsilon\,\nabla f(X_k).
$$

Kriterijum zaustavljanja se u beleškama proverava uslovom:
$$
\|\nabla f(X_k)\|<\varepsilon,
$$
ili se algoritam prekida kada se dosegne maksimalno dozvoljen broj iteracija.

Dodatno je navedena adaptacija koraka kojom se normalizuje gradijent, tako da se kontroliše dužina koraka:
$$
X_{k+1}=X_k-\frac{d}{\|\nabla f(X_k)\|}\,\nabla f(X_k),
$$
uz napomenu da se na ovaj način ne menja dužina koraka, već se korak pravi u smeru gradijenta, ali sa kontrolisanom magnitudom.

U opisnom delu beleški stoji da je algoritam jednostavan, ali da može oscilovati i sporije konvergirati u uskim dolinama, jer uvek “gleda” samo lokalno najstrmiji smer.

---

## Gradijentni metod sa momentom

Gradijentni metod sa momentom zadržava osnovnu strukturu metode najbržeg pada, ali uvodi “memoriju” prethodnog kretanja. Time se smanjuju oscilacije i ubrzava konvergencija, naročito kada se algoritam više iteracija kreće u približno istom smeru.

U beleškama je dat zapis sa brzinom (momentom) $v_k$:
$$
v_k=\omega v_{k-1}+\varepsilon\,\nabla f(x_k),
$$
a ažuriranje pozicije:
$$
x_{k+1}=x_k-v_k.
$$

Moment je opisan kao veličina koja predstavlja energiju koju akumuliramo tokom kretanja. Komponente brzine iz iteracije u iteraciju mogu ostati slično usmerene i sabiraju se, dok se komponente promenljivog smera međusobno poništavaju.

---

## Nesterovljev algoritam (ubrzani gradijent)

Nesterovljev pristup je ubrzani gradijentni metod gde se gradijent ne računa u tekućoj tački, već u unapred procenjenoj “budućoj” tački, čime postupak dobija prediktivni karakter.

U beleškama je navedeno:
$$
x'_k=x_{k-1}-\omega v_{k-1},
$$
$$
v_k=\omega v_{k-1}+\varepsilon\,\nabla f(x'_k),
$$
$$
x_{k+1}=x_k-v_k.
$$

Ključna poruka je da se gradijent računa u pretpostavljenoj budućoj tački, a ne u trenutnoj, što često daje stabilnije i brže približavanje optimumu.

---

## AdaGrad

AdaGrad je adaptivni gradijentni algoritam koji svakoj promenljivoj (svakoj osi) dodeljuje svoju efektivnu brzinu učenja. Time dimenzije u kojima su gradijenti veliki dobijaju manje korake, dok dimenzije sa manjim gradijentima dobijaju veće korake.

U beleškama su definisane veličine:
$$
g_{k,i}=\nabla f(x_k)_i=\frac{\partial f(x_k)}{\partial x_i},
$$
i akumulacija kvadrata gradijenata po koordinati:
$$
G_{k,i}=\sum_{j=0}^{k} g_{j,i}^2.
$$

Ažuriranje po koordinati je:
$$
x_{k+1,i}=x_{k,i}-\frac{\varepsilon}{\sqrt{G_{k,i}+\varepsilon_1}}\,g_{k,i},
$$
gde je u beleškama navedeno da je $\varepsilon_1\approx 10^{-8}$ i služi za regularizaciju izraza u početnim iteracijama.

Navedena mana AdaGrad-a je da $G$ stalno raste, pa efektivna brzina učenja stalno opada, zbog čega algoritam vremenom postaje sve sporiji.

---

## RMSprop

RMSprop radi slično kao AdaGrad, ali sprečava neograničeno akumuliranje kvadrata gradijenata. Umesto sume koristi eksponencijalno ponderisan prosek:

$$
G_{k+1,i}=\omega G_{k,i}+(1-\omega)g_{k,i}^2.
$$

U beleškama je naglašeno da je $g^2$ konstantno, i da kada se gornji izraz “smiri” (konvergira), dobijamo stabilnu vrednost $G$.

---

## Adam

Adam je jedan od najčešće korišćenih savremenih modifikacija gradijentnih metoda. Kombinuje ideju momenta (preko eksponencijalnog proseka gradijenata) i adaptivnog skaliranja koraka (preko eksponencijalnog proseka kvadrata gradijenata, kao u RMSprop-u).

U beleškama su pomoćne veličine:
$$
m_k=\omega_1 m_{k-1}+(1-\omega_1)g_k,
$$
$$
v_k=\omega_2 v_{k-1}+(1-\omega_2)g_k^2.
$$

Korigovane (bias-corrected) verzije su:
$$
\hat m_k=\frac{m_k}{1-\omega_1},
$$
$$
\hat v_k=\frac{v_k}{1-\omega_2}.
$$

Ažuriranje je zapisano kao:
$$
x_{k+1}=x_k-\frac{\varepsilon}{\sqrt{\hat v_k+\varepsilon_1}}\,\hat m_k.
$$

U opisnom delu stoji da Adam kombinuje ideju momenta i adaptivne brzine učenja iz RMSprop-a, zbog čega je brz i stabilan.

---

## Ukratko (zajednička ideja)

U beleškama je sumirana zajednička ideja gradijentnih metoda: kreće se od početne tačke, izračuna se u kom smeru funkcija najbrže opada, pomeri se malo u tom smeru, i postupak se ponavlja dok se ne dođe blizu minimuma. Razlika između algoritama je pre svega u tome kako biraju pravac i koliki korak prave.

---

# Genetski algoritam (realno kodiranje)

Genetski algoritam je populaciona metoda optimizacije u kojoj ne pretpostavljamo ništa specijalno o kriterijumu (funkciji cilja) koji optimizujemo. Umesto da se oslanjamo na gradijente, radimo sa skupom kandidata (populacijom) i iterativno stvaramo nove kandidate kroz selekciju, ukrštanje i mutaciju.

U terminologiji iz beleški, populacija je skup svih rešenja u tekućoj generaciji, generacija je iteracija algoritma, a jedinka je jedno konkretno rešenje. Prilagođenost (fitness) predstavlja kriterijum optimalnosti kojim merimo koliko je jedinka dobra. Gen je deo rešenja nad kojim se neposredno vrši mutacija, dok kodiranje predstavlja način predstavljanja rešenja (reprezentaciju).

Osnovni koraci algoritma su sledeći. Prvo se radi inicijalizacija: bira se početna populacija (broj jedinki $N$) i jedinke se na slučajan način rasporede po prostoru pretrage. Zatim se računa prilagođenost za svaku jedinku, tj. vrednost funkcije $f(x)$. Nakon toga sledi selekcija roditelja, gde se biraju parovi roditelja iz populacije, pri čemu jedinke sa većom prilagođenošću imaju veću verovatnoću da budu izabrane. U beleškama je naznačeno da se bira $N/2$ parova (u $N/2$ “iteracija” biramo po jedan par roditelja). Slede ukrštanje i mutacija, gde svaki par daje dva potomka, tako da broj jedinki ostaje kao na početku. Na kraju, bira se $N$ jedinki od ukupno $2N$ (roditelji i potomci), čime se formira nova populacija.

Selektovanje roditelja je opisano kroz dve tipične strategije. Ruletska selekcija identifikuje “prilagođenije” jedinke koje imaju veće šanse da prenesu osobine na potomke, pa se populacija postepeno poboljšava kroz generacije. Turnirska selekcija nasumično izabere malu grupu jedinki, one se “takmiče”, a najbolja iz te grupe se bira za reprodukciju.

Ukrštanje (crossover) je operacija u kojoj se od dva roditelja kombinuju delovi “hromozoma” da bi se dobila nova jedinka. U beleškama su navedeni primeri kao što su jednotočkaško ukrštanje, dvotočkaško ukrštanje, realno ukrštanje i prirodna selekcija. Mutacija podrazumeva nasumičnu izmenu genetskog materijala jedinke; time se obezbeđuje raznovrsnost u populaciji i omogućava istraživanje novih delova prostora pretrage, što pomaže izbegavanju lokalnih ekstrema. Elitizam je mehanizam koji čuva određeni procenat najbolje prilagođenih jedinki.

Kao najvažniji parametri genetskog algoritma navedeni su: veličina populacije, verovatnoća mutacije, maksimalni broj generacija i način selekcije.

U beleškama su pomenuta i dva tipična problemska okvira. Kod TSP (problem trgovačkog putnika), cilj je obići sve gradove tačno jednom i vratiti se u početni grad tako da ukupna dužina puta bude minimalna. Jedinka je jedna permutacija gradova, a fitness je ukupna dužina rute; ukrštanje i mutacija menjaju redosled gradova. Kod JSS (Job Shop Scheduling), problem je rasporediti više poslova na više mašina tako da se minimizuje ukupno vreme završetka uz poštovanje redosleda operacija. Jedinka je redosled izvršavanja operacija, fitness je ukupno vreme trajanja rasporeda, a ukrštanje i mutacija menjaju raspored poslova.

---

# PSO (Particle Swarm Optimization)

PSO je algoritam optimizacije zasnovan na roju čestica. U beleškama su osnovni pojmovi: prilagođenost (kriterijum optimalnosti), čestica (jedno rešenje) i roj (skup čestica). Svaka čestica pamti svoj najbolji položaj $p$ (personal best, najbolja sopstvena pozicija) i koristi informaciju o najboljoj globalnoj poziciji $g$ (global best).

Ažuriranje brzine čestice je dato formulom:
$$
v_k=\omega v_{k-1}+c_p r_p (p_k-x_k)+c_g r_g (g_k-x_k),
$$
gde je $\omega$ koeficijent inercije, $r_p$ i $r_g$ slučajni brojevi, a $c_p$ i $c_g$ koeficijenti “brzine” (težine) kognitivne i socijalne komponente. Zatim se položaj ažurira kao:
$$
x_{k+1}=x_k+v_k,
$$
a u beleškama je dopisano i da je $\omega\in[0,1]$. Takođe je navedeno značenje promenljivih: $x_k$ je trenutna pozicija čestice, a $v_k$ je trenutna brzina čestice.

Računanje brzine se sastoji iz tri komponente. Inercijalna komponenta znači da čestica nastavlja da se kreće u pravcu u kom se kretala do tada. Kognitivna komponenta usmerava česticu ka sopstvenom najboljem saznanju, odnosno ka najboljoj sopstvenoj vrednosti kriterijuma optimalnosti. Socijalna komponenta usmerava česticu ka najboljoj globalnoj vrednosti kriterijuma optimalnosti.

Koraci PSO algoritma su dati kao: inicijalizacija (postavljanje parametara, kao što su broj iteracija i broj čestica, zatim nasumično postavljanje početnih pozicija i početnih brzina), optimizacija (izračunavanje kriterijuma optimalnosti svake čestice, ažuriranje najboljih ličnih i globalnih prilagođenosti i pozicija, pa ažuriranje brzine i pozicije svake čestice), i na kraju provera kriterijuma zaustavljanja.

U beleškama su navedene i standardne test funkcije za proveru PSO algoritma, kao što su Ackley, Griewank i Rastrigin.
