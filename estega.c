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
	unsigned char B, M = 1; 	unsigned char c = 0;	char sn='n', nnombre[50];		FILE *out, *orig;	Header cabeza;		short cont=0, cont2, cont1;	size_t result;	long lSizeOut, lSizeOrig, i=0, max=0;	unsigned char * bufferOrig, * bufferOut;	
		out=fopen(archivoImg, "rb+"); // la imagen	orig=fopen(archivoDat, "rb"); //el archivo a ocultar		if(out==NULL){ 		printf("error al leer el archivo  %s !", archivoImg);		exit(1);	}		if(orig==NULL){ 		printf("error al leer el archivo  %s !", archivoDat);		exit(1);	}		// tamanio del archivo de imagen	fseek (out , 0 , SEEK_END);	lSizeOut = ftell (out);	rewind (out);			// tamanio del archivo de origen	fseek (orig , 0 , SEEK_END);	lSizeOrig = ftell (orig);	rewind (orig);			if(lSizeOrig*8+16+sizeof(Header)*8 >= lSizeOut ){		printf("Se necesita un archivo de imagen mas grande!\n");		exit(1);	}			// memoria para  el archivo de origen:	bufferOrig = (unsigned char*) malloc (sizeof(char)*lSizeOrig + sizeof(Header));	if (bufferOrig == NULL) {fputs ("error de memoria orig",stderr); exit (2);}		// memoria para el archivo de salida	bufferOut = (unsigned char*) malloc (sizeof(char)*lSizeOut );	if (bufferOut == NULL) {fputs ("error de memoria out",stderr); exit (2);}		// copia el archivo origen texto al buffer:	result = fread (&bufferOrig[sizeof(Header)],1,lSizeOrig,orig);	if (result != lSizeOrig) {fputs ("error de lectura orig ",stderr); exit (3);}				// copia el archivo out imagen al buffer:	result = fread (bufferOut,1,lSizeOut,out);	if (result != lSizeOut) {fputs ("error de lectura out ",stderr); exit (3);}			strcpy(cabeza.nf, archivoDat);	cabeza.sz = lSizeOrig;	memcpy(bufferOrig, &cabeza, sizeof(Header));		cont=0;  			//brincar encabezado del formato de imagen (sz_header_img)		long k = sz_header_img;
		for(i=0; i<(lSizeOrig+sizeof(Header) ); i++){				B = bufferOrig[i];				if(sn!='s') {			printf("\nBytes originales en la imagen\n");			printBin(bufferOut[k]);  printf("\n");			printBin(bufferOut[k+1]); printf("\n");			printBin(bufferOut[k+2]); printf("\n");			printBin(bufferOut[k+3]); printf("\n");			printBin(bufferOut[k+4]); printf("\n");			printBin(bufferOut[k+5]); printf("\n");			printBin(bufferOut[k+6]); printf("\n");			printBin(bufferOut[k+7]); printf("\n");		}						// Proceso de codificacion - esteganografia 		bufferOut[k] =  (B >> 7) | (bufferOut[k] & 254); //borrar antes el primer bit   		bufferOut[k+1] =  ((B >> 6) & 1) | (bufferOut[k+1] & 254);		bufferOut[k+2] =  ((B >> 5) & 1) | (bufferOut[k+2] & 254);			bufferOut[k+3] =  ((B >> 4) & 1) | (bufferOut[k+3] & 254);		bufferOut[k+4] =  ((B >> 3) & 1) | (bufferOut[k+4] & 254);		bufferOut[k+5] =  ((B >> 2) & 1) | (bufferOut[k+5] & 254);		bufferOut[k+6] =  ((B >> 1) & 1) | (bufferOut[k+6] & 254);		bufferOut[k+7] =  (B & 1) | (bufferOut[k+7] & 254);				if(sn!='s') {			printf("\nCaracter: %c   binario: ", B); printBin(B);			printf("\n\n");			printf("Codificacion en 8 bytes (bit menos significativo): \n");			printBin(bufferOut[k]);  printf("\n");			printBin(bufferOut[k+1]); printf("\n");			printBin(bufferOut[k+2]); printf("\n");			printBin(bufferOut[k+3]); printf("\n");			printBin(bufferOut[k+4]); printf("\n");			printBin(bufferOut[k+5]); printf("\n");			printBin(bufferOut[k+6]); printf("\n");			printBin(bufferOut[k+7]);			printf("\n\n");			printf("Codificar todo sin mostrar s=si, otra_tecla=no: ");			sn=getchar();		}				k=k+8;			}			//guardar imagen modificada	rewind (out);	result = fwrite (bufferOut,1,lSizeOut,out);	printf("\nArchivo %s actualizado con datos ocultos!\n", archivoImg);		free(bufferOrig);	free(bufferOut);		fclose(orig);	fclose(out);
	
}

void recupera(char *archivoImg){
	unsigned char B, M = 1; 	unsigned char c = 0;	char sn='n', nnombre[50];		FILE *out, *nuevo;	Header cabeza;		short cont=0, cont2, cont1;	size_t result;	long lSizeOut, lSizeOrig, i=0, max=0;	unsigned char buffer1[sizeof(Header)], * bufferOut, *buffer2;		out=fopen(archivoImg, "rb"); // la imagen		if(out==NULL){ 		printf("error al leer el archivo  %s !", archivoImg);		exit(1);	}			// tamanio del archivo de imagen	fseek (out , 0 , SEEK_END);	lSizeOut = ftell (out);	rewind (out);			// memoria para cargar el archivo de imagen	bufferOut = (unsigned char*) malloc (sizeof(char)*lSizeOut );	if (bufferOut == NULL) {fputs ("error de memoria out",stderr); exit (2);}		// copia el archivo out imagen al buffer:	result = fread (bufferOut,1,lSizeOut,out);	if (result != lSizeOut) {fputs ("error de lectura out ",stderr); exit (3);}			cont=0;  		printf("\nProceso de recuperacion de archivo\n");
	//brincar encabezado del formato de imagen (sz_header_img)		long k = sz_header_img;	unsigned char dato;	k = sz_header_img;	
	printf("\nRecuperando nombre y longitud del archivo oculto\n");	//leer y decodificar el encabezado	for(i=0; i<(sizeof(Header) ); i++){		dato=0;		dato = bufferOut[k]&1;		dato<<=1;		dato = dato | (bufferOut[k+1]&1);		dato<<=1;		dato = dato | (bufferOut[k+2]&1);		dato<<=1;		dato = dato | (bufferOut[k+3]&1);		dato<<=1;		dato = dato | (bufferOut[k+4]&1);		dato<<=1;		dato = dato | (bufferOut[k+5]&1);		dato<<=1;		dato = dato | (bufferOut[k+6]&1);		dato<<=1;		dato = dato | (bufferOut[k+7]&1);		buffer1[i]=dato;		k=k+8;	}		Header h2;	memcpy(&h2, buffer1, sizeof(Header));
	printf("\nNombre: %s   bytes: %ld \n", h2.nf, h2.sz);		buffer2 = (unsigned char*) malloc (sizeof(char)*h2.sz );	if (buffer2 == NULL) {fputs ("error de memoria buffer2 ",stderr); exit (2);}		
	printf("\nRecuperando datos del archivo oculto\n");	//leer y decodificar el contenido del archivo oculto	for(i=0 ; i<(h2.sz); i++){		dato=0;		dato = bufferOut[k]&1;		dato<<=1;		dato = dato | (bufferOut[k+1]&1);		dato<<=1;		dato = dato | (bufferOut[k+2]&1);		dato<<=1;		dato = dato | (bufferOut[k+3]&1);		dato<<=1;		dato = dato | (bufferOut[k+4]&1);		dato<<=1;		dato = dato | (bufferOut[k+5]&1);		dato<<=1;		dato = dato | (bufferOut[k+6]&1);		dato<<=1;		dato = dato | (bufferOut[k+7]&1);		buffer2[i]=dato;		// printf("%c",buffer2[i]);		k=k+8;	}		//guardar el archivo recuperado	strcpy(nnombre, h2.nf);	strcat(nnombre,"_bak");	nuevo=fopen(nnombre, "wb"); //el archivo recuperado		if(out==NULL){ 		printf("error al leer el archivo  %s !", nnombre );		exit(1);	}		result = fwrite (buffer2,1,h2.sz,nuevo);	printf("\nSe genero archivo: %s \n", nnombre);		free(buffer2);	free(bufferOut);		fclose(out);	fclose(nuevo);		printf("\nArchivo oculto %s recuperado con exito!\n",h2.nf);
	
}

void menu(){
	
	
}

int main(int argc, char *argv[]) {
	
	if(argc==2) //para ocultar	{
		recupera(argv[1]);
	}
	
	if(argc==3)  //para recuperar	{		oculta(argv[1], argv[2]);	}	
	if(argc==1 || argc>3)	{		printf("Puedes usar el programa asi:\nPara ocultar: \nestega archivo.img  archivo.ocultar\n");		printf("Para recuperar: \nestega archivo.img \n\n");			}

    return 0;
}

