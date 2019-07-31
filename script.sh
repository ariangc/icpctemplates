#Args: T.cpp A.cpp B.cpp
#T.cpp genera el input

g++ "$1" -o "gen";
g++ "$2" -o "code1";
g++ "$3" -o "code2";
let var=1;

while true; do 	
	./gen > inp && ./code1 < inp > out1 && ./code2 < inp > out2;
	DIFF=$(diff out1 out2);
	if [ "$DIFF" != "" ]; then 
		echo "WRONG ANSWER INPUT FOUND!";
		cat inp;
		echo "Result for $1:";
		cat out1;
		echo "Result for $2:";
		cat out2;
		echo "Differences:";
		diff out1 out2;
		break; 
	else
		echo "Testcase #$var: OK";
		((var++))
	fi
	sleep 1;
done
