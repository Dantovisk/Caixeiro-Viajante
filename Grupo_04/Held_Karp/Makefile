all: item.o lista.o deque.o
	gcc item.o lista.o deque.o main.c -o caixeiropotente -std=c99 -Wall -Werror -lm
run:
	./caixeiropotente
item.o:
	gcc -c item.c -o item.o
lista.o:
	gcc -c lista.c -o lista.o
deque.o:
	gcc -c deque.c -o deque.o
clean:
	rm *.o caixeiropotente caixapotente.zip
zip:
	zip -r caixapotente.zip *