#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Variables Globales
char key[]="FmAt";

//Prototipos de Funciones
void vernam(char *fn1, char *key, char *fn2);



int  main(int argc, char *argv[]){
	
	vernam("uno.txt",key,"dos.txt");
	vernam("dos.txt",key,"tres.txt");
	printf("Cifrado terminado!!\n");
	return 0;
}

void vernam(char *fn1, char *key, char *fn2){
	FILE *f1,*f2;
	char ch;
	int numbytes;
	int keysize = strlen(key);
	unsigned int ct=0;
	
	f1 = fopen(fn1,"rb");
	if(f1==NULL){
		printf("El Archivo %s no Existe!\n", fn1);
		exit(0);
	}
	f2 = fopen(fn2,"wb");
	
	
	while ( (numbytes = fread(&ch, sizeof(char),1, f1)) > 0){
		//terminado
		ch = ch ^ key[ ct ];
		fwrite( &ch, sizeof(char),1, f2);
		if(ct<keysize)
			ct++;
		else
			ct=0;
	}
	
	/* Cierre de archivos */
	fclose(f1);
	fclose(f2);
}


