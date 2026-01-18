#naziv arhive
NAME = $(shell basename "`pwd`")
#verzija programa
VERSION = $(shell grep VERSION defs.h | egrep -o "[0-9]+[.0-9]+")
#naziv source fajlova za skener i parser simulatora
SOURCE = hipsim
# bash je potreban zbog boja
SHELL = /bin/bash
# fajlovi od kojih se sastoji simulator
SIMULATOR_BUILD = lex.yy.c $(SOURCE).tab.c simulator.c
# fajlovi od kojih zavisi ponovno prevođenje
SIMULATOR_DEPENDS = $(SIMULATOR_BUILD) defs.h simulator.h
# putanja na koju će se postaviti izvršni fajl
SIMULATOR_PATH = ./
SIMULATOR = $(SIMULATOR_PATH)$(SOURCE)
# fajlvi koje treba pobrisati da bi ostao samo izvorni kod
SIMULATOR_CLEAN = lex.yy.c $(SOURCE).tab.c $(SOURCE).tab.h $(SOURCE).output $(SIMULATOR) *~
# da li treba vršiti ispis
ifeq (,$(findstring s,$(MAKEFLAGS)))
    ECHO = echo
else
    ECHO = true
endif
# pravila koja ne generišu nove fajlove prilikom kompajliranja
.PHONY: archive clean

$(SIMULATOR): $(SIMULATOR_DEPENDS)
	@$(ECHO) -e "\e[01;32mGCC...\e[00m"
	@gcc -g -o $@ $(SIMULATOR_BUILD)

lex.yy.c: $(SOURCE).l $(SOURCE).tab.c
	@$(ECHO) -e "\e[01;32mFLEX...\e[00m"
	@flex -I $<

$(SOURCE).tab.c: $(SOURCE).y
	@$(ECHO) -e "\e[01;32mBISON...\e[00m"
	@bison -d -v $<

archive: clean
	@$(ECHO) -e "\e[01;32mCreating archive ../$(NAME)-$(VERSION).tar.gz\e[00m"
	@tar --exclude=*.gz -czf ../$(NAME)-$(VERSION).tar.gz ../$(NAME)

clean:
	@$(ECHO) -e "\e[01;32mDeleting temporary files...\e[00m"
	@rm -f $(SIMULATOR_CLEAN)

