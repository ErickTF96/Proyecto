#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define sz_header_img 100


typedef struct {
  char nf[40];
  int long sz;
} Header;


//imprime un caracter en binario
void printBin(unsigned char b){
  int i;
  for (i=7; i>=0; i--) { // muestra en binario
	short bit = ((b >> i) & 1);
	printf("%d", bit);
  } 
}

void oculta(char *archivoImg, char *archivoDat){
	unsigned char B, M = 1; 
	
	
	
}

void recupera(char *archivoImg){
	unsigned char B, M = 1; 
	//brincar encabezado del formato de imagen (sz_header_img)
	printf("\nRecuperando nombre y longitud del archivo oculto\n");

	printf("\nRecuperando datos del archivo oculto\n");
	
}

void menu(){
	
	
}

int main(int argc, char *argv[]) {
	
	if(argc==2) //para ocultar
		recupera(argv[1]);
	}
	
	if(argc==3)  //para recuperar
	if(argc==1 || argc>3)

    return 0;
}
