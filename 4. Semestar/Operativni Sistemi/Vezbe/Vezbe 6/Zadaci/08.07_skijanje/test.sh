#!/bin/bash
ZELENO="\033[0;32m"
CRVENO="\033[0;31m"
PLAVO="\033[0;34m"
BEZBOJNO="\033[0m"

TEST_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

if [ ${TEST_DIR} != "/tmp/t1234" ] ; then
	echo -e ${CRVENO}Скрипт није покренут у добром директоријуму!!!${BEZBOJNO}
	return false
else
	cd ${TEST_DIR}
fi

echo -e ${PLAVO}#######################################${BEZBOJNO}
echo -e ${PLAVO}Тест $(cat ${TEST_DIR}/tbr) се покреће.${BEZBOJNO}
echo -e ${PLAVO}Опис: $(cat ${TEST_DIR}/opis)${BEZBOJNO}
echo -e ${PLAVO}#######################################${BEZBOJNO}

./$1

t7t_tac=true
for ((i = 2; i <= $#; i++)) do
    t7t_dat=${!i}
	if ! [ -f ${t7t_dat} ] ; then 
		echo -e ${CRVENO}Датотека ${t7t_dat} не постоји.${BEZBOJNO}
		t7t_tac=false
		continue
	fi
	t7t_tdt=${t7t_dat}.test
	grep "\S" ${t7t_tdt} > ${t7t_tdt}.osisan
	grep "\S" ${t7t_dat} > ${t7t_dat}.osisan
	if [ -s ${t7t_tdt}.osisan ] ; then 
		if [ $(cat ${t7t_tdt}.osisan | wc -l) -eq $(cat ${t7t_dat}.osisan | wc -l) ] ; then
			if [ $(grep -Fcxf ${t7t_dat}.osisan ${t7t_tdt}.osisan) -ne $(cat ${t7t_tdt}.osisan | wc -l) ] ; then
				echo -e ${CRVENO}Датотека ${t7t_dat} није добра.${BEZBOJNO}
				t7t_tac=false
			else
				if [ $(cat ${t7t_tdt}.osisan | wc -l) -eq 0 ] ; then
					if ! diff ${t7t_tdt}.osisan ${t7t_dat}.osisan ; then
						echo -e ${CRVENO}Датотека ${t7t_dat} није добра.${BEZBOJNO}
						t7t_tac=false
					fi
				fi
			fi
		else
			echo -e ${CRVENO}Датотека ${t7t_dat} није добра.${BEZBOJNO}
			t7t_tac=false
		fi
	else
		if [ -s ${t7t_dat}.osisan ] ; then
			echo -e ${CRVENO}Датотека ${t7t_dat} није добра.${BEZBOJNO}
			t7t_tac=false
		fi 
	fi
done

if ${t7t_tac} ; then
	echo -e ${ZELENO}Тест прошао!${BEZBOJNO}
else
	echo -e ${CRVENO}Тест пао!${BEZBOJNO}
fi
