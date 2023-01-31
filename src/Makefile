.DEFAULT_GOAL:=
detectCycles: main.o LinkedList.o Graph.o cycleDetection.o
	gcc -o detectCycles main.o LinkedList.o Graph.o cycleDetection.o

main.o: main.c
	gcc -g -c -o main.o main.c

LinkedList.o: LinkedList.c
	gcc -g -c -o LinkedList.o LinkedList.c

Graph.o: Graph.c
	gcc -g -c -o Graph.o Graph.c

cycleDetection.o: cycleDetection.c
	gcc -g -c -o cycleDetection.o cycleDetection.c

clean:
	rm -f detectCycles
	rm -f *.o
