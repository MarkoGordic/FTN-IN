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
COMPILER_CLEAN = lex.yy.c $(SRC).tab.c $(SRC).tab.h $(SRC).output $(SRC) *.?~ *.mc~ .make.out* *.asm Makefile~
# ako treba sprovesti samo neke testove, ovu promenljivu treba postaviti na naziv testa
TEST = ""

# pravila koja ne generišu nove fajlove
.PHONY: clean test det archive help

# osnovno pravilo za prevođenje kompajlera
$(SRC): $(COMPILER_DEPENDS)
	@if [ "$(COMPILE_SIM)" != "" ]; then \
		echo -e "\033[01;32mSIMULATOR...\033[00m"; \
		make --silent -C ./hipsim-src/ SIMULATOR_PATH=../; \
	fi
	@echo -e "\033[01;32mGCC...\033[00m"
	@-rm -f $(SRC) .make.out2 2>/dev/null
	@gcc -o $@ $(COMPILER_BUILD) 2>&1 | tee .make.outg; pstat=$${PIPESTATUS[0]}; \
	cat .make.outf .make.outb .make.outg > .make.out 2>/dev/null; \
	out=`grep -Ei "conflict|warning|error" .make.out 2>/dev/null`; \
	if [ "$$out" != "" ]; then \
		cat .make.outf .make.outb; \
		echo -e "\033[01;31m\nThere are errors/warnings in grammar/actions!\n\033[00m" ; \
		rm -f $(SRC) 2>/dev/null ; \
		exit 1; \
	fi; \
	exit $$pstat

lex.yy.c: $(SRC).l $(SRC).tab.c
	@echo -e "\033[01;32mFLEX...\033[00m"
	@flex $< 2>&1 | tee .make.outf; exit $${PIPESTATUS[0]}

$(SRC).tab.c: $(SRC).y
	@echo -e "\033[01;32mBISON...\033[00m"
	@bison -d -v $< 2>&1 | tee .make.outb; exit $${PIPESTATUS[0]}

clean:
	@echo -e "\033[01;32mDeleting temporary files...\033[00m"
	@rm -f $(COMPILER_CLEAN)
	@rm -f hipsim
	@if [ -f ./hipsim-src/Makefile ]; then \
	    make --silent -C ./hipsim-src/ clean ; \
	fi

archive: clean
	@arc=`pwd`; \
	arc=`basename $$arc`; \
	echo -e "\033[01;32mCreating archive ../$$arc.tar.gz\033[00m"; \
	tar --exclude=*.gz -czf ../$$arc.tar.gz ../$$arc

# testiranje kompajlera, izvršava se samo ako nema grešaka u gramatici
# - u petlji će se kompajleru proslediti svi test*.mc fajlovi
# - ako u test fajlu postoji linija sa tekstom "//OPIS:", ispisaće se na ekranu
# - ukoliko prilikom poziva kompajlera nije bilo grešaka, i ako postoji
#   generisanje koda, ispisaće se i asemblerski izlaz
det: $(SRC)
	@if [ ! -f $(SRC) ]; then exit 1; fi
	@echo -e "\n\033[01;36mRunning compiler with test files...\033[00m"
	@if [ "$$TEST" != "" ]; then all_tests=$$TEST; \
	else all_tests=test*.mc; fi; \
	for test in $$all_tests; do \
		if [[ $$test =~ .*synerr.* ]]; then echo -e "\033[01;35m"; ttyp="syn"; \
		elif [[ $$test =~ .*semerr.* ]]; then echo -e "\033[01;34m"; ttyp="sem"; \
		elif [[ $$test =~ .*sanity.* ]]; then echo -e "\033[01;32m"; ttyp="san"; \
		else echo -e "\033[01;36m"; ttyp="ok"; fi; \
		echo -e "\n\n------------------------\nTesting: $$test"; \
		grep "//OPIS:" $$test; \
		echo -e "------------------------\033[00m"; \
		RETURN=$$(grep "//RETURN:" "$$test"); \
		RETURN=$${RETURN#*:}; \
		RETURN=$$(echo "$$RETURN" | xargs); \
		./$(SRC) < "$$test"; \
		out=$$?; \
		if [ $$ttyp == "ok" ] && [ $$out -ne 0 ]; then \
			echo -e "\033[01;31m\nError reported for '$$test'!\n\033[00m" ; \
		elif [ $$ttyp == "san" ] && [ $$out -ne 0 ]; then \
			echo -e "\033[01;31m\nOriginal miniC grammar is corrupted!\n\033[00m" ; \
		elif [ $$ttyp == "sem" ] && ([ $$out -eq 0 ] || [ $$out -eq 255 ]); then \
			echo -e "\033[01;31m\nSemantic error not reported for '$$test'!\n\033[00m" ; \
		elif [ $$ttyp == "syn" ] && [ $$out -ne 255 ]; then \
			echo -e "\033[01;31m\nSyntax error not reported for '$$test'!\n\033[00m" ; \
		elif [ "$(ASM)" == "true" ] && [ $$out -eq 0 ]; then \
			outname=$$(basename $$test); \
			outname=$${outname%.*}; \
			mv output.asm "$${outname}.asm"; \
			echo -e "output.asm saved as \033[01;34m$${outname}.asm\n\033[00m"; \
			if [ -f $${outname}.asm.ok ]; then \
				diff -w -B "$${outname}.asm" "$${outname}.asm.ok" > /dev/null; \
				if [ $$? -ne 0 ]; then \
					if [[ $$ttyp == "san" ]]; then \
						echo -e "\033[01;31m\nASM code generation for original miniC is changed!"; \
					else \
						echo -e "\033[01;31m\nASM code differs from expected!"; \
					fi; \
					echo -e "Run\033[00m fldiff $${outname}.asm $${outname}.asm.ok"; \
				fi; \
			elif [ "$$RETURN" != "" ]; then \
				echo -e "\033[01;34mRunning simulator...\033[00m"; \
				RETVAL=$$(./hipsim -r -s 500 < "$${outname}.asm"); \
				CODE=$$?; \
				if [ $$CODE -ne 0 ]; then \
					if [ $$CODE -eq 4 ]; then \
						echo -e -n "\n\n\033[01;31mASM code has an infinite loop (didn't finish in 500 steps).\033[00m"; \
					elif [ $$CODE -eq 3 ]; then \
						echo -e -n "\n\n\033[01;31mASM code produced illegal operation.\033[00m"; \
					else \
						echo -e -n "\n\n\033[01;31mErrors found in generated ASM code.\033[00m"; \
					fi; \
				else \
					if [ "$$RETVAL" == "$$RETURN" ]; then \
						echo -e -n "\033[01;32mReturn value: $$RETVAL\033[00m"; \
					else \
						echo -e -n "\033[01;31mReturn value: $$RETVAL\033[00m, should be $$RETURN."; \
					fi; \
				fi; \
			fi; \
		fi; \
	done; \
	echo

# testiranje kompajlera sa minimalnim ispisom
test: $(SRC)
	@if [ ! -f $(SRC) ]; then exit 1; fi
	@echo -e "\n\033[01;36mRunning compiler with test files...\033[00m\n"
	@if [ "$$TEST" != "" ]; then all_tests=$$TEST; \
	else all_tests=test*.mc; fi; \
	RESULTP="\033[01;32mPASSED\033[00m"; \
	RESULTF="\033[01;31mFAILED\033[00m"; \
	for test in $$all_tests; do \
		RESULT=$$RESULTP; \
		if [[ $$test =~ .*synerr.* ]]; then echo -e -n "\033[01;35m"; ttyp="syn"; \
		elif [[ $$test =~ .*semerr.* ]]; then echo -e -n "\033[01;34m"; ttyp="sem"; \
		elif [[ $$test =~ .*sanity.* ]]; then echo -e -n "\033[01;32m"; ttyp="san"; \
		else echo -e -n "\033[01;36m"; ttyp="ok"; fi; \
		RETURN=$$(grep "//RETURN:" "$$test"); \
		RETURN=$${RETURN#*:}; \
		RETURN=$$(echo "$$RETURN" | xargs); \
		./$(SRC) < "$$test" 1>/dev/null 2>/dev/null; \
		out=$$?; \
		if [ $$ttyp == "ok" ] && [ $$out -ne 0 ]; then \
			RESULT=$$RESULTF; \
		elif [ $$ttyp == "san" ] && [ $$out -ne 0 ]; then \
			RESULT=$$RESULTF; \
		elif [ $$ttyp == "sem" ] && ([ $$out -eq 0 ] || [ $$out -eq 255 ]); then \
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
		echo -e "$$test: $$RESULT"; \
	done; \
	echo -e "\n\033[01;31mAttention: \033[01;36mtests with errors are valid \033[01;32monly if\033[01;36m ok tests are passed!\033[00m"; \
	echo -e "\n\033[01;36mRun \033[01;32mmake det\033[01;36m for detailed results.\033[00m\n"

help:
	@echo -e "\n\033[01;36mKompajliranje programa\033[00m"
	@echo -e "    \033[01;32mmake\033[00m"
	@echo -e "\n\033[01;36mBrisanje automatski generisanih fajlova\033[00m"
	@echo -e "    \033[01;32mmake clean\033[00m"
	@echo -e "\n\033[01;36mPokretanje svih testova sa kratkim ispisom\033[00m"
	@echo -e "    \033[01;32mmake test\033[00m"
	@echo -e "\n\033[01;36mPokretanje svih testova sa detaljnim ispisom\033[00m"
	@echo -e "    \033[01;32mmake det\033[00m"
	@echo -e "\n\033[01;36mPokretanje samo nekih testova\033[00m"
	@echo -e "    \033[01;32mmake test TEST=test-ok1.mc\033[00m"
	@echo -e "    \033[01;32mmake det TEST=\"test-ok1.mc test-ok2.mc\"\033[00m"
	@echo -e "\n\033[01;36mNazivi test fajlova treba da slede sledeću konvenciju:\033[00m"
	@echo -e "  \033[01;35mPočetak naziva  Značenje\033[00m"
	@echo -e "    \033[01;36mtest-sanity\033[00m - korektan miniC program bez novih konstrukcija"
	@echo -e "                  (provera originalne gramatike)"
	@echo -e "    \033[01;36mtest-ok\033[00m ----- korektan miniC program sa novim konstrukcijama"
	@echo -e "                  - ukoliko sadrži komentar \033[01;36m//RETURN: <num>\033[00m, nakon"
	@echo -e "                    generisanja koda će se proveriti da li se povratna"
	@echo -e "                    vrednost izgenerisanog koda poklapa sa navedenom"
	@echo -e "    \033[01;36mtest-semerr\033[00m - nekorektan miniC program sa jednom semantičkom greškom"
	@echo -e "    \033[01;36mtest-synerr\033[00m - nekorektan miniC program sa jednom sintaksnom greškom"
	@echo -e "Ukoliko se u test fajlu nalazi red koji počinje sa \033[01;36m//OPIS: <tekst>\033[00m, ta linija"
	@echo -e "će biti ispisana pre testa.\n"

