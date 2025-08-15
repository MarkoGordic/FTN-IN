# TODO: измени CXX тако да се УМЕСТО наводника налази име програма који гради (компајлира) Ц++ код
CXX = ""
# TODO: измени CXXFLAGS тако да се УМЕСТО наводника налази списак параметара потребан за успешну изградњу (компајлирање) твог Ц++ кода
CXXFLAGS = ""

IZVORNA_DAT = main.cpp
IZVRSNA_DAT = r
TEST_DIR = /tmp/t1234/
ULAZNE_DAT = studenti.csv
IZLAZNE_DAT = kandidati_kredit.csv kandidati_stipendija.csv ostali.csv

.SUFFIXES :
.PHONY : ocisti $(wildcard *.test) test.sh

${IZVRSNA_DAT} : ${IZVORNA_DAT}
	${CXX} ${CXXFLAGS} -o ${IZVRSNA_DAT} ${IZVORNA_DAT}

test : | ${IZVRSNA_DAT} $(wildcard *.test) 

$(wildcard *.test) :
	@rm -rf ${TEST_DIR}
	@mkdir ${TEST_DIR}
	@echo $(basename $@) >> ${TEST_DIR}tbr
	@for dat in test.sh $@/opis ${IZVRSNA_DAT} $(addprefix $@/,${ULAZNE_DAT}) $(addsuffix .test,$(addprefix $@/,${IZLAZNE_DAT})) ; do \
		if [ -f $$dat ] ; then \
			cp $$dat ${TEST_DIR} ; \
		else \
			echo прескачем копирање \{$$dat\} датотеке ; \
		fi ; \
	done
	@chmod +x ${TEST_DIR}test.sh
	@${TEST_DIR}test.sh ${IZVRSNA_DAT} ${IZLAZNE_DAT}
	@rm -rf ${TEST_DIR}

ocisti :
	rm -fr ${IZVRSNA_DAT} ${TEST_DIR}
