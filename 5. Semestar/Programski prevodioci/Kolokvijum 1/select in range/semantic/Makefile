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

# ANSI boje za macOS kompatibilnost
GREEN = \033[01;32m
RED = \033[01;31m
CYAN = \033[01;36m
MAGENTA = \033[01;35m
BLUE = \033[01;34m
RESET = \033[00m

# pravila koja ne generišu nove fajlove
.PHONY: clean test det archive help

# osnovno pravilo za prevođenje kompajlera
$(SRC): $(COMPILER_DEPENDS)
	@if [ "$(COMPILE_SIM)" != "" ]; then \
		printf "$(GREEN)SIMULATOR...$(RESET)\n"; \
		make --silent -C ./hipsim-src/ SIMULATOR_PATH=../; \
	fi
	@printf "$(GREEN)GCC...$(RESET)\n"
	@-rm -f $(SRC) .make.out2 2>/dev/null
	@gcc -o $@ $(COMPILER_BUILD) 2>&1 | tee .make.outg; pstat=$${PIPESTATUS[0]}; \
	cat .make.outf .make.outb .make.outg > .make.out 2>/dev/null; \
	out=`grep -Ei "conflict|warning|error" .make.out 2>/dev/null`; \
	if [ "$$out" != "" ]; then \
		cat .make.outf .make.outb; \
		printf "$(RED)\nThere are errors/warnings in grammar/actions!\n$(RESET)\n" ; \
		rm -f $(SRC) 2>/dev/null ; \
		exit 1; \
	fi; \
	exit $$pstat

lex.yy.c: $(SRC).l $(SRC).tab.c
	@printf "$(GREEN)FLEX...$(RESET)\n"
	@flex $< 2>&1 | tee .make.outf; exit $${PIPESTATUS[0]}

$(SRC).tab.c: $(SRC).y
	@printf "$(GREEN)BISON...$(RESET)\n"
	@bison -d -v $< 2>&1 | tee .make.outb; exit $${PIPESTATUS[0]}

clean:
	@printf "$(GREEN)Deleting temporary files...$(RESET)\n"
	@rm -f $(COMPILER_CLEAN)
	@rm -f hipsim
	@if [ -f ./hipsim-src/Makefile ]; then \
	    make --silent -C ./hipsim-src/ clean ; \
	fi

archive: clean
	@arc=`pwd`; \
	arc=`basename $$arc`; \
	printf "$(GREEN)Creating archive ../$$arc.tar.gz$(RESET)\n"; \
	tar --exclude=*.gz -czf ../$$arc.tar.gz ../$$arc

# testiranje kompajlera, izvršava se samo ako nema grešaka u gramatici
det: $(SRC)
	@if [ ! -f $(SRC) ]; then exit 1; fi
	@printf "\n$(CYAN)Running compiler with test files...$(RESET)\n"
	@if [ "$$TEST" != "" ]; then all_tests=$$TEST; \
	else all_tests=test*.mc; fi; \
	for test in $$all_tests; do \
		if [[ $$test =~ .*synerr.* ]]; then color="$(MAGENTA)"; ttyp="syn"; \
		elif [[ $$test =~ .*semerr.* ]]; then color="$(BLUE)"; ttyp="sem"; \
		elif [[ $$test =~ .*sanity.* ]]; then color="$(GREEN)"; ttyp="san"; \
		else color="$(CYAN)"; ttyp="ok"; fi; \
		printf "$${color}\n\n------------------------\nTesting: $$test\n"; \
		grep "//OPIS:" $$test; \
		printf "------------------------$(RESET)\n"; \
		RETURN=$$(grep "//RETURN:" "$$test"); \
		RETURN=$${RETURN#*:}; \
		RETURN=$$(echo "$$RETURN" | xargs); \
		./$(SRC) < "$$test"; \
		out=$$?; \
		if [ "$$ttyp" = "ok" ] && [ $$out -ne 0 ]; then \
			printf "$(RED)\nError reported for '$$test'!\n$(RESET)\n" ; \
		elif [ "$$ttyp" = "san" ] && [ $$out -ne 0 ]; then \
			printf "$(RED)\nOriginal miniC grammar is corrupted!\n$(RESET)\n" ; \
		elif [ "$$ttyp" = "sem" ] && ([ $$out -eq 0 ] || [ $$out -eq 255 ]); then \
			printf "$(RED)\nSemantic error not reported for '$$test'!\n$(RESET)\n" ; \
		elif [ "$$ttyp" = "syn" ] && [ $$out -ne 255 ]; then \
			printf "$(RED)\nSyntax error not reported for '$$test'!\n$(RESET)\n" ; \
		elif [ "$(ASM)" = "true" ] && [ $$out -eq 0 ]; then \
			outname=$$(basename $$test); \
			outname=$${outname%.*}; \
			mv output.asm "$${outname}.asm"; \
			printf "output.asm saved as $(BLUE)$${outname}.asm\n$(RESET)\n"; \
		fi; \
	done; \
	echo

# testiranje kompajlera sa minimalnim ispisom
test: $(SRC)
	@if [ ! -f $(SRC) ]; then exit 1; fi
	@printf "\n$(CYAN)Running compiler with test files...$(RESET)\n\n"
	@if [ "$$TEST" != "" ]; then all_tests=$$TEST; \
	else all_tests=test*.mc; fi; \
	RESULTP="$(GREEN)PASSED$(RESET)"; \
	RESULTF="$(RED)FAILED$(RESET)"; \
	for test in $$all_tests; do \
		RESULT=$$RESULTP; \
		if [[ $$test =~ .*synerr.* ]]; then ttyp="syn"; \
		elif [[ $$test =~ .*semerr.* ]]; then ttyp="sem"; \
		elif [[ $$test =~ .*sanity.* ]]; then ttyp="san"; \
		else ttyp="ok"; fi; \
		RETURN=$$(grep "//RETURN:" "$$test"); \
		RETURN=$${RETURN#*:}; \
		RETURN=$$(echo "$$RETURN" | xargs); \
		./$(SRC) < "$$test" 1>/dev/null 2>/dev/null; \
		out=$$?; \
		if [ "$$ttyp" = "ok" ] && [ $$out -ne 0 ]; then \
			RESULT=$$RESULTF; \
		elif [ "$$ttyp" = "san" ] && [ $$out -ne 0 ]; then \
			RESULT=$$RESULTF; \
		elif [ "$$ttyp" = "sem" ] && ([ $$out -eq 0 ] || [ $$out -eq 255 ]); then \
			RESULT=$$RESULTF; \
		elif [ "$$ttyp" = "syn" ] && [ $$out -ne 255 ]; then \
			RESULT=$$RESULTF; \
		elif [ "$(ASM)" = "true" ] && [ $$out -eq 0 ]; then \
			outname=$$(basename $$test); \
			outname=$${outname%.*}; \
			mv output.asm "$${outname}.asm"; \
		fi; \
		printf "$$test: $$RESULT\n"; \
	done; \
	printf "\n$(RED)Attention: $(CYAN)tests with errors are valid $(GREEN)only if$(CYAN) ok tests are passed!$(RESET)\n"; \
	printf "\n$(CYAN)Run $(GREEN)make det$(CYAN) for detailed results.$(RESET)\n\n"

help:
	@printf "\n$(CYAN)Kompajliranje programa$(RESET)\n"
	@printf "    $(GREEN)make$(RESET)\n"
	@printf "\n$(CYAN)Brisanje automatski generisanih fajlova$(RESET)\n"
	@printf "    $(GREEN)make clean$(RESET)\n"
	@printf "\n$(CYAN)Pokretanje svih testova sa kratkim ispisom$(RESET)\n"
	@printf "    $(GREEN)make test$(RESET)\n"
	@printf "\n$(CYAN)Pokretanje svih testova sa detaljnim ispisom$(RESET)\n"
	@printf "    $(GREEN)make det$(RESET)\n"
