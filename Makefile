#A Flag -c diz para gerar o arquivo de objeto, o -o $@ diz para colocar a saída da compilação no arquivo nomeado no lado esquerdo do:, o $ <é o primeiro item na lista de dependências, e o A macro CFLAGS é definida como acima.
#Como simplificação final, vamos usar as macros especiais $@ e $ ^, que são os lados esquerdo e direito de :, respectivamente, para tornar a regra geral de compilação mais geral. 
#No exemplo abaixo, todos os arquivos de inclusão devem ser listados como parte da macro DEPS e todos os arquivos de objetos devem ser listados como parte da macro OBJ.

#Flags interessantes
#-Wall dispara todos os warnings em seu código
#-g necessário para avaliar o código do valgrind
#-lm obrigatorio caso utilize a biblioteca math.h

CPP=g++
CFLAGS=-I. -Wall -g -lm
GLUTFLAGS=-lGL -lGLU -lglut
DEPS = geometries.h puppet.h block.h opponent.h gunshot.h arena.h collision.h tinyxml2.h
OBJ = src/geometries.o src/puppet.o src/block.o src/opponent.o src/gunshot.o src/arena.o src/collision.o tinyxml2/tinyxml2.o main.o

all: trabalhocg clean

%.o: %.c $(DEPS)
	$(CPP) -c -o $@ $< $(CFLAGS) $(GLUTFLAGS)

trabalhocg: $(OBJ)
	$(CPP) -o $@ $^ $(CFLAGS) $(GLUTFLAGS)

run: all
	./trabalhocg input/arena_teste.svg

clean:
	rm -f *.o
	rm -f src/*.o