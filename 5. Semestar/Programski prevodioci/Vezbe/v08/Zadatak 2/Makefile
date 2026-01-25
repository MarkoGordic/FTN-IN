# bash je potreban da bi radila redirekcija stderr i stdout, kao i zbog PIPESTATUS promenljive
SHELL = /bin/bash
# naziv kompajlera i osnovnih source fajlova
COMP = $(wildcard *.l)
SRC = $(basename $(COMP))
# da li je kompajler sa generisanjem koda?
ifeq ($(SRC),micko)
    ASM = true
    CGENC = codegen.c
    CGENH = codegen.h
endif
# da li je prisutan simulator?
ifeq ($(wildcard ./hipsim),)
   COMPILE_SIM = $(wildcard ./hipsim-src/Makefile)
else
    COMPILE_SIM =
endif
# fajlovi od kojih se sastoji kompajler
COMPILER_BUILD = lex.yy.c $(SRC).tab.c symtab.c $(CGENC)
# fajlovi od kojih zavisi ponovno prevođenje
COMPILER_DEPENDS = $(COMPILER_BUILD) defs.h symtab.h $(CGENH)
# fajlovi koje treba pobrisati da bi ostao samo izvorni kod
COMPILER_CLEAN = lex.yy.c $(SRC).tab.c $(SRC).tab.h $(SRC).output $(SRC) *.?~ *.mc~ .make.out* *.asm Makefile~ *.txt~
# ako treba sprovesti samo neke testove, ovu promenljivu treba postaviti na naziv testa
TEST = ""

# pravila koja ne generišu nove fajlove
.PHONY: clean test det archive help

# osnovno pravilo za prevođenje kompajlera
$(SRC): $(COMPILER_DEPENDS)
	@if [ "$(COMPILE_SIM)" != "" ]; then \
		printf "\e[01;32mSIMULATOR...\e[00m\n"; \
		make --silent -C ./hipsim-src/ SIMULATOR_PATH=../; \
	fi
	@printf "\e[01;32mGCC...\e[00m\n"
	@-rm -f $(SRC) .make.out2 2>/dev/null
	@gcc -o $@ $(COMPILER_BUILD) 2>&1 | tee .make.outg; pstat=$${PIPESTATUS[0]}; \
	cat .make.outf .make.outb .make.outg > .make.out 2>/dev/null; \
	out=`grep -Ei "conflict|warning|error" .make.out 2>/dev/null`; \
	if [ "$$out" != "" ]; then \
		cat .make.outf .make.outb; \
		printf "\e[01;31m\nThere are errors/warnings in grammar/actions!\n\e[00m\n" ; \
		rm -f $(SRC) 2>/dev/null ; \
		exit 1; \
	fi; \
	exit $$pstat

lex.yy.c: $(SRC).l $(SRC).tab.c
	@printf "\e[01;32mFLEX...\e[00m\n"
	@flex $< 2>&1 | tee .make.outf; exit $${PIPESTATUS[0]}

$(SRC).tab.c: $(SRC).y
	@printf "\e[01;32mBISON...\e[00m\n"
	@bison -d -v $< 2>&1 | tee .make.outb; exit $${PIPESTATUS[0]}

clean:
	@printf "\e[01;32mDeleting temporary files...\e[00m\n"
	@rm -f $(COMPILER_CLEAN)
	@rm -f hipsim
	@if [ -f ./hipsim-src/Makefile ]; then \
	    make --silent -C ./hipsim-src/ clean ; \
	fi

archive: clean
	@arc=`pwd`; \
	arc=`basename "$$arc"`; \
	printf "\e[01;32mCreating archive ../$$arc.tar.gz\e[00m\n"; \
	tar --exclude=*.gz -czf ../$$arc.tar.gz ../$$arc

# testiranje kompajlera, izvršava se samo ako nema grešaka u gramatici
# - u petlji će se kompajleru proslediti svi test*.mc fajlovi
# - ako u test fajlu postoji linija sa tekstom "//OPIS:", ispisaće se na ekranu
# - ukoliko prilikom poziva kompajlera nije bilo grešaka, i ako postoji
#   generisanje koda, ispisaće se i asemblerski izlaz
det: $(SRC)
	@if [ ! -f $(SRC) ]; then exit 1; fi
	@printf "\n\e[01;36mRunning compiler with test files...\e[00m\n"
	@if [ "$$TEST" != "" ]; then all_tests=$$TEST; \
	else all_tests=test*.mc; fi; \
	for test in $$all_tests; do \
		if [[ $$test =~ .*synerr.* ]]; then printf "\e[01;35m"; ttyp="syn"; \
		elif [[ $$test =~ .*semerr.* ]]; then printf "\e[01;34m"; ttyp="sem"; \
		elif [[ $$test =~ .*sanity.* ]]; then printf "\e[01;32m"; ttyp="san"; \
		elif [[ $$test =~ .*warn.* ]]; then printf "\e[01;33m"; ttyp="war"; \
		else printf "\e[01;36m"; ttyp="ok"; fi; \
		printf "\n\n------------------------\nTesting: $$test\n"; \
		grep "//OPIS:" $$test; \
		printf "------------------------\e[00m\n"; \
		RETURN=$$(grep "//RETURN:" "$$test"); \
		RETURN=$${RETURN#*:}; \
		RETURN=$$(echo "$$RETURN" | xargs); \
		./$(SRC) < "$$test"; \
		out=$$?; \
		if [ $$ttyp == "ok" ] && [ $$out -ne 0 ]; then \
			printf "\e[01;31m\nError/warning reported for '$$test'!\n\e[00m\n" ; \
		elif [ $$ttyp == "war" ] && ([ $$out -lt 128 ] || [ $$out -eq 255 ]); then \
			printf "\e[01;31m\nWarning not reported for '$$test'!\n\e[00m\n" ; \
		elif [ $$ttyp == "san" ] && [ $$out -ne 0 ]; then \
			printf "\e[01;31m\nOriginal miniC grammar is corrupted!\n\e[00m\n" ; \
		elif [ $$ttyp == "sem" ] && ([ $$out -eq 0 ] || [ $$out -gt 127 ]); then \
			printf "\e[01;31m\nSemantic error not reported for '$$test'!\n\e[00m\n" ; \
		elif [ $$ttyp == "syn" ] && [ $$out -ne 255 ]; then \
			printf "\e[01;31m\nSyntax error not reported for '$$test'!\n\e[00m\n" ; \
		elif [ "$(ASM)" == "true" ] && [ $$out -eq 0 ]; then \
			outname=$$(basename $$test); \
			outname=$${outname%.*}; \
			mv output.asm "$${outname}.asm"; \
			printf "output.asm saved as \e[01;34m$${outname}.asm\n\e[00m\n"; \
			if [ -f $${outname}.asm.ok ]; then \
				diff -w -B "$${outname}.asm" "$${outname}.asm.ok" > /dev/null; \
				if [ $$? -ne 0 ]; then \
					if [[ $$ttyp == "san" ]]; then \
						printf "\e[01;31m\nASM code generation for original miniC is changed!"; \
					else \
						printf "\e[01;31m\nASM code differs from expected!"; \
					fi; \
					printf "Run\e[00m fldiff $${outname}.asm $${outname}.asm.ok\n"; \
				fi; \
			elif [ "$$RETURN" != "" ]; then \
				printf "\e[01;34mRunning simulator...\e[00m\n"; \
				RETVAL=$$(./hipsim -r -s 500 < "$${outname}.asm"); \
				CODE=$$?; \
				if [ $$CODE -ne 0 ]; then \
					if [ $$CODE -eq 4 ]; then \
						printf "\n\n\e[01;31mASM code has an infinite loop (didn't finish in 500 steps).\e[00m"; \
					elif [ $$CODE -eq 3 ]; then \
						printf "\n\n\e[01;31mASM code produced illegal operation.\e[00m"; \
					else \
						printf "\n\n\e[01;31mErrors found in generated ASM code.\e[00m"; \
					fi; \
				else \
					if [ "$$RETVAL" == "$$RETURN" ]; then \
						printf "\e[01;32mReturn value: $$RETVAL\e[00m"; \
					else \
						printf "\e[01;31mReturn value: $$RETVAL\e[00m, should be $$RETURN."; \
					fi; \
				fi; \
			fi; \
		fi; \
	done; \
	echo

# testiranje kompajlera sa minimalnim ispisom
test: $(SRC)
	@if [ ! -f $(SRC) ]; then exit 1; fi
	@printf "\n\e[01;36mRunning compiler with test files...\e[00m\n\n"
	@if [ "$$TEST" != "" ]; then all_tests=$$TEST; \
	else all_tests=test*.mc; fi; \
	RESULTP="\e[01;32mPASSED\e[00m"; \
	RESULTF="\e[01;31mFAILED\e[00m"; \
	for test in $$all_tests; do \
		RESULT=$$RESULTP; \
		if [[ $$test =~ .*synerr.* ]]; then printf "\e[01;35m"; ttyp="syn"; \
		elif [[ $$test =~ .*semerr.* ]]; then printf "\e[01;34m"; ttyp="sem"; \
		elif [[ $$test =~ .*sanity.* ]]; then printf "\e[01;32m"; ttyp="san"; \
		elif [[ $$test =~ .*warn.* ]]; then printf "\e[01;33m"; ttyp="war"; \
		else printf "\e[01;36m"; ttyp="ok"; fi; \
		RETURN=$$(grep "//RETURN:" "$$test"); \
		RETURN=$${RETURN#*:}; \
		RETURN=$$(echo "$$RETURN" | xargs); \
		./$(SRC) < "$$test" 1>/dev/null 2>/dev/null; \
		out=$$?; \
		if [ $$ttyp == "ok" ] && [ $$out -ne 0 ]; then \
			RESULT=$$RESULTF; \
		elif [ $$ttyp == "war" ] && ([ $$out -lt 128 ] || [ $$out -eq 255 ]); then \
			RESULT=$$RESULTF; \
		elif [ $$ttyp == "san" ] && [ $$out -ne 0 ]; then \
			RESULT=$$RESULTF; \
		elif [ $$ttyp == "sem" ] && ([ $$out -eq 0 ] || [ $$out -gt 127 ]); then \
			RESULT=$$RESULTF; \
		elif [ $$ttyp == "syn" ] && [ $$out -ne 255 ]; then \
			RESULT=$$RESULTF; \
		elif [ "$(ASM)" == "true" ] && [ $$out -eq 0 ]; then \
			outname=$$(basename $$test); \
			outname=$${outname%.*}; \
			mv output.asm "$${outname}.asm"; \
			if [ -f $${outname}.asm.ok ]; then \
				diff -w -B "$${outname}.asm" "$${outname}.asm.ok" > /dev/null; \
				if [ $$? -ne 0 ]; then \
					if [[ $$ttyp == "san" ]]; then \
						RESULT=$$RESULTF; \
					else \
						RESULT=$$RESULTF; \
					fi; \
				fi; \
			elif [ "$$RETURN" != "" ]; then \
				RETVAL=$$(./hipsim -r -s 500 < "$${outname}.asm" 2>/dev/null); \
				CODE=$$?; \
				if [ $$CODE -ne 0 ]; then \
					if [ $$CODE -eq 4 ]; then \
						RESULT=$$RESULTF; \
					elif [ $$CODE -eq 3 ]; then \
						RESULT=$$RESULTF; \
					else \
						RESULT=$$RESULTF; \
					fi; \
				else \
					if ! [ "$$RETVAL" == "$$RETURN" ]; then \
						RESULT=$$RESULTF; \
					fi; \
				fi; \
			fi; \
		fi; \
		printf "$$test: $$RESULT\n"; \
	done; \
	printf "\n\e[01;31mAttention: \e[01;36mtests with errors are valid \e[01;32monly if\e[01;36m ok tests are passed!\e[00m\n"; \
	printf "\n\e[01;36mRun \e[01;32mmake det\e[01;36m for detailed results.\e[00m\n\n"

help:
	@printf "\n\e[01;36mKompajliranje programa\e[00m\n"
	@printf "    \e[01;32mmake\e[00m\n"
	@printf "\n\e[01;36mBrisanje automatski generisanih fajlova\e[00m\n"
	@printf "    \e[01;32mmake clean\e[00m\n"
	@printf "\n\e[01;36mPokretanje svih testova sa kratkim ispisom\e[00m\n"
	@printf "    \e[01;32mmake test\e[00m\n"
	@printf "\n\e[01;36mPokretanje svih testova sa detaljnim ispisom\e[00m\n"
	@printf "    \e[01;32mmake det\e[00m\n"
	@printf "\n\e[01;36mPokretanje samo nekih testova\e[00m\n"
	@printf "    \e[01;32mmake test TEST=test-ok1.mc\e[00m\n"
	@printf "    \e[01;32mmake det TEST=\"test-ok1.mc test-ok2.mc\"\e[00m\n"
	@printf "\n\e[01;36mNazivi test fajlova treba da slede sledeću konvenciju:\e[00m\n"
	@printf "  \e[01;35mPočetak naziva  Značenje\e[00m\n"
	@printf "    \e[01;36mtest-sanity\e[00m - korektan miniC program bez novih konstrukcija\n"
	@printf "                  (provera originalne gramatike)\n"
	@printf "    \e[01;36mtest-ok\e[00m ----- korektan miniC program sa novim konstrukcijama\n"
	@printf "                  - ukoliko sadrži komentar \e[01;36m//RETURN: <num>\e[00m, nakon\n"
	@printf "                    generisanja koda će se proveriti da li se povratna\n"
	@printf "                    vrednost izgenerisanog koda poklapa sa navedenom\n"
	@printf "    \e[01;36mtest-warn\e[00m --- nekorektan miniC program sa jednim upozorenjem\n"
	@printf "    \e[01;36mtest-semerr\e[00m - nekorektan miniC program sa jednom semantičkom greškom\n"
	@printf "    \e[01;36mtest-synerr\e[00m - nekorektan miniC program sa jednom sintaksnom greškom\n"
	@printf "Ukoliko se u test fajlu nalazi red koji počinje sa \e[01;36m//OPIS: <tekst>\e[00m, ta linija\n"
	@printf "će biti ispisana pre testa.\n\n"

