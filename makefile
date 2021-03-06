#	A Flag -c diz para gerar o arquivo de objeto, o -o $@ diz para colocar a saída da compilação no arquivo nomeado no lado esquerdo do :, o $< é o primeiro item na lista de dependências, e o A macro CFLAGS é definida como acima.
#	Como simplificação final, vamos usar as macros especiais $@ e $^, que são os lados esquerdo e direito de :, respectivamente, para tornar a regra geral de compilação mais geral. 
#	No exemplo abaixo, todos os arquivos de inclusão devem ser listados como parte da macro DEPS e todos os arquivos de objetos devem ser listados como parte da macro OBJ.

#Flags interessantes
#-Wall dispara todos os warnings em seu código
#-g necessário para avaliar o código do valgrind (permite o valgrind dizer em que linha dá merda)
#-lm obrigatorio caso utilize a biblioteca math.h

CC=gcc
CFLAGS=-I. -Wall -g
DEPS= headers/cards.h headers/deck.h headers/player.h headers/jogo.h headers/AI.h
OBJ= cards.o deck.o main.o player.o jogo.o AI.o
EXEC= programa

%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o ${EXEC} $^ $(CFLAGS)
	rm -f *.o

run:
	make main
	./${EXEC}

val:
	make main
	valgrind --leak-check=full ./${EXEC}

clean:
	rm -f *.o
	rm -f ${EXEC}
	rm -f main

push:
	./autopush ${msg}
