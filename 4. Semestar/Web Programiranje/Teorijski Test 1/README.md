## 1. Koji su osnovni principi OOP?

- Enkapsulacija, apstrakcija, nasleđivanje i polimorfizam

1. Enkapsulacija (engl. encapsulation) - Skrivanje podataka i metoda unutar klase, čime se sprečava direktan pristup spoljašnjim entitetima. Ovo pomaže u zaštiti integriteta podataka i smanjuje kompleksnost sistema.
2. Apstrakcija (engl. abstraction) - Fokusiranje na bitne karakteristike objekta dok se zanemaruju nebitne detalje. Ovo omogućava programerima da rade sa složenim sistemima na višem nivou bez potrebe da razumeju sve unutrašnje detalje.
3. Nasleđivanje (engl. inheritance) - Mehanizam kojim jedna klasa može naslediti osobine (atribute i metode) druge klase. Ovo omogućava ponovnu upotrebu koda i olakšava održavanje sistema.
4. Polimorfizam (engl. polymorphism) - Sposobnost objekata različitih klasa da se tretiraju kao objekti iste klase kroz zajednički interfejs. Ovo omogućava fleksibilnost i proširivost koda, jer se može koristiti isti kod za različite tipove objekata.

## 2. Koji tipove veza između različitih klasa postoje u objektno orijentisanim programskim jezicima?

- Nasleđivanje (Inheritance), kompozicija (Composition) i asocijacija (Association)

1. Nasleđivanje (Inheritance) - Veza između dve klase gde jedna klasa (podklasa ili izvedena klasa) nasleđuje osobine i ponašanje druge klase (superklasa ili baza klasa). Ovo omogućava ponovnu upotrebu koda i kreiranje hijerarhija klasa.
2. Kompozicija (Composition) - Veza između dve klase gde jedna klasa sadrži referencu na drugu klasu kao deo svog stanja. Ovo predstavlja "ima" odnos, gde jedan objekat "ima" drugi objekat kao deo svoje strukture. Kompozicija omogućava fleksibilnost i modularnost u dizajnu sistema.
3. Asocijacija (Association) - Veza između dve klase gde objekti jedne klase mogu biti povezani sa objektima druge klase. Asocijacija može biti jednosmerna ili dvosmerna, i može imati različite kardinalnosti (npr. jedan-prema-jedan, jedan-prema-više, više-prema-više). Asocijacija predstavlja "koristi" odnos između objekata.

## 3. Kakvu vezu između klasa opisuje nasleđivanje?

Nasleđivanje opisuje "je" vezu između klasa. Kada jedna klasa nasleđuje drugu, ona postaje specijalizovana verzija te klase i može koristiti njene atribute i metode.

## 4. Kakvu vezu između klasa opisuje kompozicija?

Kompozicija opisuje "ima" vezu između klasa. Kada jedna klasa sadrži referencu na drugu klasu, to znači da jedan objekat "ima" drugi objekat kao deo svoje strukture.

## 5. Kakvu vezu između klasa opisuje asocijacija?

Asocijacija opisuje "koristi" vezu između klasa. Kada objekti jedne klase koriste objekte druge klase, to može biti jednosmerno ili dvosmerno, i može imati različite kardinalnosti.

## 6. Šta je klijent-server model?

Klijent-server model je arhitektura mrežnih aplikacija u kojoj se funkcionalnost deli između klijenata i servera. Klijent je aplikacija koja inicira zahteve za uslugama ili resursima, dok je server aplikacija koja prima te zahteve, obrađuje ih i vraća odgovore klijentu. Ovaj model omogućava centralizovano upravljanje resursima i uslugama, kao i skalabilnost i fleksibilnost u razvoju mrežnih aplikacija.

## 7. Šta je serverska aplikacija i koja je njena uloga u klijent/server modelu?

Serverska aplikacija je softverski program koji radi na serveru i pruža usluge, resurse ili podatke klijentskim aplikacijama. Njena uloga u klijent/server modelu je da prima zahteve od klijenata, obrađuje te zahteve i šalje odgovarajuće odgovore nazad klijentima.

## 8. Šta je klijentska aplikacija i koja je njena uloga u klijent/server modelu?

Klijentska aplikacija je softverski program koji radi na računaru korisnika (klijentu) i inicira zahteve za uslugama, resursima ili podacima od serverske aplikacije. Njena uloga u klijent/server modelu je da šalje zahteve serveru, prima odgovore od servera i prikazuje ili obrađuje te informacije za korisnika.

## 9. Kako se obavlja komunikacija između klijenta i servera?

Komunikacija između klijenta i servera obavlja se putem mrežnih protokola, najčešće koristeći TCP/IP protokol. Klijent šalje zahtev serveru preko mreže, a server prima taj zahtev, obrađuje ga i šalje nazad odgovor klijentu.

## 10. Koji su osnovni protokoli koji se koriste za komunikaciju u web aplikacijama?

- TCP (Transmission Control Protocol) i UDP (User Datagram Protocol) za transport podataka
- HTTP (Hypertext Transfer Protocol) i HTTPS (HTTP Secure) za prenos web stranica i resursa

## 11. Šta su portovi? Šta oni omogućavaju u slučaju da se na računaru pokreće više mrežnih aplikacija?

Portovi su numerisani identifikatori koji omogućavaju različitim mrežnim aplikacijama da komuniciraju preko iste IP adrese na računaru. Svaka aplikacija može biti povezana sa jedinstvenim portom, što omogućava višestrukim aplikacijama da istovremeno koriste mrežu bez konflikta. Na primer, web serveri obično koriste port 80 za HTTP i port 443 za HTTPS, dok druge aplikacije mogu koristiti različite portove za svoje komunikacione potrebe.

## 12. Koji je osnovni paket i osnovne klase koje se koriste za razvoj mrežnih aplikacija u Javi?

Osnovni paket za razvoj mrežnih aplikacija u Javi je `java.net`. Neke od osnovnih klasa koje se koriste u ovom paketu uključuju:

- `Socket`: Klasa koja predstavlja klijentski socket za komunikaciju sa serverom.
- `ServerSocket`: Klasa koja predstavlja serverski socket koji čeka na dolazne klijentske veze.
- `URL`: Klasa koja predstavlja URL adresu i omogućava pristup resursima na mreži.
- `URLConnection`: Klasa koja omogućava komunikaciju sa resursima na mreži putem URL-a.
- `DatagramSocket` i `DatagramPacket`: Klase koje se koriste za komunikaciju putem UDP protokola.
- `MulticastSocket`: Klasa koja omogućava slanje i primanje multicast poruka.

## 13. Šta su i čemu služe Socket-i?

Socket-i su krajnje tačke za komunikaciju između dve mrežne aplikacije. Oni omogućavaju uspostavljanje veze između klijenta i servera, omogućavajući slanje i primanje podataka preko mreže. Socket-i služe kao interfejs između aplikacije i mrežnog protokola, omogućavajući aplikacijama da komuniciraju bez potrebe da se bave detaljima mrežne komunikacije.

## 14. Koja je razlika između ServerSocket-a i Socket-a?

- `Socket` je klasa koja predstavlja klijentski socket, koji se koristi za uspostavljanje veze sa serverom i komunikaciju sa njim.
- `ServerSocket` je klasa koja predstavlja serverski socket, koji se koristi za slušanje dolaznih klijentskih veza i prihvatanje tih veza kako bi se uspostavila komunikacija.

## 15. Šta je server loop?

Server loop je beskonačna petlja koja se koristi u serverskim aplikacijama za kontinuirano slušanje i prihvatanje dolaznih klijentskih veza. U okviru ove petlje, server čeka na nove zahteve, prihvata ih kada stignu, i zatim obrađuje svaki zahtev, često u posebnom niti (thread) kako bi omogućio paralelnu obradu više klijenata istovremeno. Server loop omogućava serveru da ostane aktivan i spreman za komunikaciju sa klijentima tokom celog svog rada.

## 16. Šta je HTTP protokol?

HTTP (Hypertext Transfer Protocol) je protokol koji se koristi za prenos podataka na webu. On definiše pravila i formate za razmenu informacija između klijenta (npr. web pregledača) i servera. HTTP je zasnovan na arhitekturi klijent-server i koristi se za slanje i primanje zahteva i odgovora.

## 17. Koje su osnovne HTTP metode? I kada se koja od njih koristi?

Osnovne HTTP metode su:

- GET: Koristi se za dobijanje podataka sa servera. Ova metoda ne menja stanje servera i koristi se za čitanje resursa.
- POST: Koristi se za slanje podataka na server, često za kreiranje novih resursa ili slanje obrazaca. Ova metoda može menjati stanje servera.
- PUT: Koristi se za ažuriranje postojećih resursa na serveru ili kreiranje novih resursa ako ne postoje.
- DELETE: Koristi se za brisanje resursa sa servera.
- HEAD: Slično kao GET, ali vraća samo zaglavlja odgovora bez tela. Koristi se za proveru postojanja resursa ili dobijanje metapodataka.
- OPTIONS: Koristi se za dobijanje informacija o komunikacionim opcijama koje su podržane za određeni resurs.
- PATCH: Koristi se za delimično ažuriranje resursa na serveru.
- TRACE: Koristi se za dijagnostiku i vraća putanju koju je zahtev prošao do servera.

## 18. Šta su response statusi? Koji je smisao grupa response statusa (100+, 200+, 300+, 400+, 500+)?

<image src="./assets/image.png" alt="HTTP status codes" style="width:400px" />

- 1XX (Informational): Ovi statusi označavaju da je zahtev primljen i da se obrada nastavlja. Na primer, 100 Continue znači da klijent može nastaviti sa slanjem zahteva.
- 2XX (Success): Ovi statusi označavaju da je zahtev uspešno obrađen. Na primer, 200 OK znači da je zahtev uspešno obrađen i da je odgovor uključen u telo odgovora.
- 3XX (Redirection): Ovi statusi označavaju da je potrebna dodatna akcija da bi se zahtev dovršio, obično preusmeravanje na drugi URL. Na primer, 301 Moved Permanently znači da je resurs trajno premešten na novu lokaciju.
- 4XX (Client Error): Ovi statusi označavaju greške koje su nastale zbog neispravnog zahteva od strane klijenta. Na primer, 404 Not Found znači da traženi resurs nije pronađen na serveru.
- 5XX (Server Error): Ovi statusi označavaju greške koje su nastale na strani servera dok je pokušavao da obradi zahtev. Na primer, 500 Internal Server Error znači da je došlo do neočekivane greške na serveru.

<image src="./assets/image-1.png" alt="HTTP status codes" style="width:400px" />

## 19. Šta je i koja je namena SSpring frameworka?

- Okvir za razvoj Java enterprise aplikacija, inicijalna verzija je nastala 2002. godine
- Omogućava lakši razvoj aplikacija kroz različite module i alate
- Spring Framework omogućava razvoj aplikacija zasnovanih na principima Common Annotations i Dependency Injection (DI)

## 20. Šta je, kako se koristi i šta omogućava korišćenje anotacija u Spring-u?

Anotacije u Spring-u su specijalni obeleživači koji se koriste za označavanje klasa, metoda ili polja kako bi se definisalo njihovo ponašanje unutar Spring konteksta. One omogućavaju konfiguraciju i upravljanje komponentama na jednostavan i deklarativan način, bez potrebe za opširnim XML konfiguracionim fajlovima.

Anotacije se koriste tako što se dodaju iznad klasa, metoda ili polja pomoću simbola "@" (npr. @Component, @Service, @Repository, @Autowired). One omogućavaju Spring-u da automatski prepozna i upravlja tim komponentama, kao i da obezbedi potrebne zavisnosti putem Dependency Injection-a.

## 21. Šta je i šta omogućava “ubrizgavanje zavisnosti” (Dependency injection) u Spring-u?

- Implementacija Inversion of Control (IoC) principa
- Omogućava da se zavisnosti između objekata definišu spolja, umesto unutar samih objekata
- Pomaže u smanjenju povezanosti između komponenti, čineći kod fleksibilnijim i lakšim za testiranje
- Programer ne mora sam da poziva konstruktore ili setere za zavisnosti, već to radi Spring kontejner

## 22. Šta su “upravljani objekti” (managed objects, managed beans) u Springu?

- Objekti čiji je životni ciklus i zavisnosti upravljaju Spring kontejnerom
- Kreiraju se, konfigurišu i uništavaju od strane Spring-a
- Mogu biti anotirani sa @Component, @Service, @Repository ili @Controller kako bi ih Spring prepoznao kao upravljane objekte
- Omogućavaju lakše upravljanje zavisnostima i konfiguracijom unutar aplikacije

## 23. Navesti nekoliko najbitnijih modula Spring frameworka

- Spring core container, aspect-oriented programming, authentication and authoriziation, convention over configuration, data access, inversion of control container, messaging, modelview-controller, remote acess framework

- Spring Core: Osnovni modul koji pruža osnovne funkcionalnosti kao što su Dependency Injection i Inversion of Control.
- Spring AOP (Aspect-Oriented Programming): Modul koji omogućava aspektno orijentisano programiranje, što pomaže u razdvajanju poslovne logike od sistemskih aspekata kao što su logovanje i sigurnost.
- Spring Data: Modul koji olakšava rad sa bazama podataka i pruža podršku za različite tehnologije za perzistenciju podataka, uključujući JPA, MongoDB i Redis.
- Spring MVC: Modul koji omogućava razvoj web aplikacija koristeći Model-View-Controller arhitekturu.
- Spring Security: Modul koji pruža sigurnosne funkcionalnosti za aplikacije, uključujući autentifikaciju i autorizaciju.
- Spring Boot: Modul koji pojednostavljuje kreiranje i konfiguraciju Spring aplikacija, omogućavajući brži razvoj i lakše pokretanje aplikacija.
- Messaging: Modul koji omogućava rad sa porukama i integraciju sa različitim messaging sistemima kao što su RabbitMQ i Kafka.

## 24. Koje osnovne principe pri razvoju softvera treba težiti da se koriste?

- KISS (Keep It Simple, Stupid): Održavanje jednostavnosti u dizajnu i implementaciji. Izbegavanje nepotrebne složenosti kako bi se olakšalo razumevanje i održavanje koda.
- SoC (Separation of Concerns): Razdvajanje različitih aspekata aplikacije u odvojene module ili slojeve. Ovo pomaže u organizaciji koda i olakšava njegovo održavanje.

## 25. Koji su osnovni slojevi tipične (troslojne) arhitekture web aplikacija?

1. Web sloj (Presentation Layer): Ovaj sloj je odgovoran za interakciju sa korisnikom i prikaz podataka. Uključuje web stranice, korisničke interfejse i sve što korisnik vidi i koristi.
2. Servisni sloj (Business Logic Layer): Ovaj sloj sadrži poslovnu logiku aplikacije. On obrađuje podatke, vrši validaciju i implementira pravila poslovanja. Servisni sloj deluje kao posrednik između web sloja i sloja za perzistiranje podataka.
3. Sloj za perzistiranje podataka (Repository Layer): Ovaj sloj je odgovoran za komunikaciju sa bazom podataka ili drugim izvorima podataka. On obezbeđuje metode za čuvanje, ažuriranje, brisanje i preuzimanje podataka.

## 26. Šta je MVC arhitektura web aplikacije?

MVC (Model-View-Controller) arhitektura je dizajnerski obrazac koji razdvaja aplikaciju na tri glavne komponente: Model, View i Controller. Ovaj obrazac pomaže u organizaciji koda, olakšava održavanje i omogućava bolju saradnju između različitih delova aplikacije.

## 27. Koje komponente čine model u MVC?

Model u MVC arhitekturi čine komponente koje predstavljaju podatke i poslovnu logiku aplikacije. To uključuje:

- Entitete: Klase koje predstavljaju podatke u aplikaciji (npr. korisnici, proizvodi).
- Repozitorijumi: Interfejsi ili klase koje definišu metode za pristup i manipulaciju podacima (npr. čuvanje, preuzimanje).
- Servisi: Klase koje sadrže poslovnu logiku i pravila (npr. validacija, obrada podataka).

## 28. Koje komponente čine view u MVC?

View u MVC arhitekturi čine komponente koje su odgovorne za prikaz podataka korisniku. To uključuje:

- HTML/CSS: Struktura i stil web stranica.
- Šabloni: Datoteke koje definišu kako se podaci prikazuju (npr. Thymeleaf, JSP).
- JavaScript: Klijentska logika koja omogućava interakciju sa korisničkim interfejsom.

## 29. Koje komponente čine controller u MVC?

Controller u MVC arhitekturi čine komponente koje upravljaju interakcijom između modela i view-a. To uključuje:

- Kontroleri: Klase koje primaju zahteve od korisnika, obrađuju ih i vraćaju odgovore (npr. UserController, ProductController).
- Handler metode: Metode unutar kontrolera koje su odgovorne za obradu specifičnih zahteva (npr. getUser, createProduct).

## 30. Šta je Spring Boot i koja je prednost njegovog korišćenja u odnosu na “obični” Spring?

Spring Boot je ekstenzija Spring frameworka koja pojednostavljuje proces kreiranja i konfiguracije Spring aplikacija. On omogućava brži razvoj aplikacija pružajući podrazumevane konfiguracije, automatsko podešavanje i ugrađene servere (kao što su Tomcat ili Jetty), što eliminiše potrebu za složenim XML konfiguracionim fajlovima.

- Minimizira pisanje boilerplate koda
- Obezbeđuje 'startnu' POM konfiguraciju za Maven projekte
- Omogućava brzo pokretanje aplikacija sa minimalnim podešavanjima
- Ima mnogo gotovih pluginova i dodataka koji olakšavaju integraciju sa drugim tehnologijama

## 31. Koja je osnovna arhitektura (slojevi) Spring Boot aplikacije?

1. Web sloj (Presentation Layer): Ovaj sloj je odgovoran za interakciju sa korisnikom i prikaz podataka. Uključuje kontrolere i view komponente.
2. Servisni sloj (Business Logic Layer): Ovaj sloj sadrži poslovnu logiku aplikacije. On obrađuje podatke, vrši validaciju i implementira pravila poslovanja.
3. Sloj za perzistiranje podataka (Persistence Layer): Ovaj sloj je odgovoran za komunikaciju sa bazom podataka ili drugim izvorima podataka. On obezbeđuje metode za čuvanje, ažuriranje, brisanje i preuzimanje podataka.
4. Sloj za baze podataka (Database Layer): Ovaj sloj se bavi čuvanjem podataka u bazi kao i CRUD operacijama.

## 32. Koje su osnovne komponente Spring (Boot) aplikacije i koja je uloga svake od tih vrsta komponenti?

- Kontroleri (Controllers): Upravljaju HTTP zahtevima i odgovaraju na njih, povezujući korisnički interfejs sa poslovnom logikom.
- Servisi (Services): Sadrže poslovnu logiku aplikacije i obrađuju podatke.
- Repozitorijumi (Repositories): Omogućavaju pristup podacima u bazi podataka, obezbeđujući CRUD operacije.
- Entiteti (Entities): Predstavljaju podatke u aplikaciji, obično mapirane na tabele u bazi podataka.
- Komponente (Components): Opšte komponente koje mogu imati različite funkcionalnosti unutar aplikacije.

## 33. Koja je putanja obrade zahteva (kroz koje komponente prolazi) u Spring Boot aplikaciji?

Klijent -> Korisnički interfejs (View) -> Kontroler (Controller) -> Servis (Service) -> Repozitorijum (Repository) / Model -> Baza podataka (Database) -> Servis (Service) -> Kontroler (Controller) -> Korisnički interfejs (View) -> Klijent

1. Klijent šalje HTTP zahtev.
2. Zahtev stiže do korisničkog interfejsa (View), koji može biti web stranica ili API.
3. Kontroler (Controller) prima zahtev i obrađuje ga.
4. Kontroler poziva odgovarajući servis (Service) da izvrši poslovnu logiku.
5. Servis može koristiti repozitorijum (Repository) ili model (Model) za pristup podacima.
6. Repozitorijum komunicira sa bazom podataka (Database) da izvrši potrebne operacije.
7. Podaci se vraćaju nazad kroz servis i kontroler do korisničkog interfejsa.
8. Korisnički interfejs šalje odgovor nazad klijentu.

## 34. Koje su osnovne Spring Boot anotacije i šta one omogućavaju?

- @Component: Obeležava klasu kao Spring komponentu, omogućavajući Spring-u da je automatski otkrije i upravlja njenim životnim ciklusom.
- @Service: Obeležava klasu kao servisnu komponentu, koja sadrži poslovnu logiku aplikacije.
- @Repository: Obeležava klasu kao repozitorijum, koji je odgovoran za pristup podacima u bazi podataka.
- @Controller: Obeležava klasu kao kontroler, koji upravlja HTTP zahtevima i odgovara na njih.
- @RestController: Kombinacija @Controller i @ResponseBody, koristi se za kreiranje RESTful web servisa.
- @Entity: Obeležava klasu kao JPA entitet, koji predstavlja tabelu u bazi podataka.
- @RequestMapping: Koristi se za mapiranje HTTP zahteva na metode unutar kontrolera.

## 35. Šta je Spring Initializr i čemu služi?

Spring Initializr je web alat koji omogućava brzo generisanje osnovne strukture Spring Boot aplikacije. Korisnici mogu da izaberu različite opcije kao što su verzija Spring-a, zavisnosti, naziv projekta i druge konfiguracije, a zatim preuzmu ZIP fajl sa generisanim kodom.

## 36. Šta je i čemu služi Servlet Dispatcher u Spring Boot aplikaciji?

Servlet Dispatcher je centralna komponenta u Spring MVC arhitekturi koja upravlja HTTP zahtevima i usmerava ih ka odgovarajućim kontrolerima. On takođe obezbeđuje mehanizme za obradu izuzetaka, konverziju podataka i druge aspekte obrade zahteva.

## 37. Koje klase učestvuju u funkcionisanju sloja za perzistiranje podataka u Spring Boot aplikaciji?

- Entiteti (Entities): Predstavljaju podatke koji se čuvaju u bazi podataka.
- Repozitorijumi (Repositories): Interfejsi koji definišu metode za pristup podacima.
- Servisi (Services): Sadrže poslovnu logiku i koriste repozitorijume za pristup podacima.

## 38. Šta je Java JPA?

Java JPA (Java Persistence API) je specifikacija za upravljanje perzistencijom podataka u Java aplikacijama. Ona definiše način na koji se objekti mapiraju na relacione baze podataka i obezbeđuje API za rad sa tim objektima.

## 39. Šta je objektno-relaciono mapiranje?

Objektno-relaciono mapiranje (ORM) je tehnika koja omogućava programerima da rade sa podacima u bazi podataka koristeći objektno-orijentisani pristup. ORM biblioteke automatski mapiraju relacione tabele na Java klase, čime se olakšava rad sa podacima.

## 40. Koje su, čemu služe JPA anotacije?

- @Entity: Obeležava klasu kao JPA entitet, koji predstavlja tabelu u bazi podataka.
- @Table: Obeležava klasu kao tabelu u bazi podataka i definiše njeno ime.
- @Id: Obeležava polje kao primarni ključ entiteta.
- @GeneratedValue: Obeležava polje kao automatski generisani identifikator.
- @Column: Obeležava polje kao kolonu u tabeli i definiše njene atribute.
- @OneToMany, @ManyToOne, @OneToOne, @ManyToMany: Obeležavaju veze između entiteta i definišu kardinalnost tih veza.
- @JoinColumn: Obeležava kolonu koja se koristi za povezivanje entiteta u relaciji.
- @Embedded: Obeležava ugrađeni objekat unutar entiteta.
- @NamedQuery: Definiše unapred definisane upite koji se mogu koristiti za pretragu podataka.
- @NamedQueries: Definiše grupu unapred definisanih upita.
- @UniqueConstraint: Obeležava jedinstvena ograničenja na kolone u tabeli.
- @TableGenerator: Definiše generator tabela za kreiranje primarnih ključeva.

## 41. Šta je Spring Data JPA?

Spring Data JPA je projekat odnosno biblioteka unutar Spring ekosistema koji pojednostavljuje rad sa JPA (Java Persistence API) i omogućava brži razvoj aplikacija koje koriste perzistenciju podataka. On pruža apstrakciju iznad JPA i omogućava korišćenje repozitorijumskih interfejsa za pristup podacima bez potrebe za pisanjem implementacije.

## 42. Koja je osnovna uloga Controller komponente?

Controller komponenta u Spring Boot aplikaciji je da upravlja HTTP zahtevima koje dolaze od klijenata. Ona prima zahteve, obrađuje ih i vraća odgovarajuće odgovore. Kontroler deluje kao posrednik između korisničkog interfejsa (view) i poslovne logike (servisnog sloja), omogućavajući komunikaciju između ta dva sloja.

## 43. Kako se unutar kontrolera definiše koju putanju opslužuje koja handler metoda?

Unutar kontrolera, putanja koju opslužuje određena handler metoda definiše se pomoću anotacije @RequestMapping (ili njenih specifičnih varijanti kao što su @GetMapping, @PostMapping, @PutMapping, @DeleteMapping). Ove anotacije se postavljaju iznad metoda i specificiraju HTTP metodu i URL putanju koju ta metoda treba da opslužuje.

## 44. Čemu služi @RequestMapping anotacija?

@RequestMapping anotacija se koristi za mapiranje HTTP zahteva na određene metode u kontroleru. Ona može da definiše URL putanju, HTTP metodu (GET, POST, itd.), kao i druge atribute kao što su parametri zahteva i zaglavlja.

## 45. Čemu služi objekat tipa ModelAndView?

ModelAndView objekat se koristi za vraćanje podataka iz kontrolera u vid (view). On omogućava da se istovremeno postave podaci (model) i odredi koji će se vid koristiti za prikaz tih podataka. ModelAndView sadrži informacije o modelu (podacima) i imenu pogleda (view) koji treba da se prikaže.

## 46. Čemu služi @RequestParam anotacija?

@RequestParam anotacija se koristi za ekstrakciju vrednosti parametara iz URL-a ili tela HTTP zahteva. Ona omogućava kontroleru da pristupi vrednostima koje su prosleđene kao deo zahteva, bilo da su to query parametri ili form data.

## 47. Koja je razlika između @PathVariable i @RequestParam?

@PathVariable se koristi za ekstrakciju vrednosti iz URL putanje, dok se @RequestParam koristi za ekstrakciju vrednosti iz query parametara ili form data. @PathVariable se obično koristi kada je deo URL-a dinamički, dok se @RequestParam koristi za statičke parametre.

<image src="./assets/image-2.png" alt="PathVariable vs RequestParam" style="width:400px" />

## 48. Čemu služi @ResponseBody anotacija. U kom formatu se najčešće šalju podaci u body-ju zahteva?

@ResponseBody anotacija se koristi za označavanje da se povratna vrednost metode u kontroleru treba serijalizovati i poslati kao telo HTTP odgovora. Najčešće se podaci šalju u JSON formatu.

## 49. Čemu služi @RestController anotacija i koja je ključna razlika u odnosu na “standardni” kontroler?

@RestController anotacija kombinuje @Controller i @ResponseBody anotacije, što znači da se sve metode u kontroleru automatski tretiraju kao RESTful i vraćaju podatke u JSON formatu. Ključna razlika je u tome što @RestController ne zahteva eksplicitno korišćenje @ResponseBody anotacije za svaku metodu.

## 50. Koja je namena servisnog sloja u Spring Boot aplikaciji?

- Koristi se kao omotač (wrapper) oko sloja za pristup podacima (DAO) i predstavlja opšteprihvaćen način za korišćenje DAO sloja.
- U servisni sloj se stavljaju sve CRUD (create, retrieve, update, delete) metode koje repository nudi.
- Ima poslovnu logiku sistema.

## 51. Čemu služi @Autowired anotacija u Spring Boot komponentama?

@Autowired anotacija se koristi za automatsko injektovanje zavisnosti u Spring komponentama. Ona omogućava Spring kontejneru da automatski poveže bean-ove (komponente) koji su potrebni za rad određene klase, čime se smanjuje potreba za ručnim konfigurisanje i instanciranje objekata.
