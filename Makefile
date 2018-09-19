
sumaAleatorios: sumaAleatorios.c
	gcc -O2 -o sumaAleatorios sumaAleatorios.c

testSumaAleatorios: sumaAleatorios
	time ./sumaAleatorios 270496 ./output/salidaTest.txt

generaTaskFile: generaTaskFile.c
	gcc -o generaTaskFile generaTaskFile.c  

Taskfile: generaTaskFile
	./generaTaskFile Taskfile ./ sumaAleatorios ./output/ 1000

testGeneraTaskfile: generaTaskFile
	./generaTaskFile TaskfileTest ./ sumaAleatorios ./output/ 3

planificador: planificador.c
	gcc -O2 -o planificador planificador.c

testPlanificador: planificador
	./planificador MachinefileTest TaskfileTest 1

clean:
	rm -f sumaAleatorios generaTaskFile planificador output/*.txt