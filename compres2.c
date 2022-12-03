/* Compresión de archivos usando el Algoritmo de Huffman: */
/* (C) Noviembre de 2000 Salvador Pozo Coronado           */
/* (C) Noviembre de 2018-2021 Mariano Ruiz (correcciones) */
/* Compresor                                              */

#include "compres2.h"


int main(int argc, char *argv[])
{
   tipoNodo *Lista;       /* Lista de letras y frecuencias */
   tipoNodo *Arbol;       /* Arbol de letras y frecuencias */

   FILE *fe, *fs;         /* Ficheros de entrada y salida */
   unsigned char c;       /* variables auxiliares */
   tipoNodo *p;
   tipoTabla *t;
   int nElementos;        /* Número de elementos en tabla */
   long int Longitud = 0; /* Longitud del fichero original */

   unsigned long int dWORD; /* Soble palabra usada durante la codificación */
   int nBits;               /* Número de bits usados de dWORD */

   if(argc < 3)
   {
      printf("Usar:\n%s <fichero_entrada> <fichero_salida>\n", argv[0]);
      return 1;
   }

   Lista = NULL;
   /* Fase 1: contar frecuencias */
   fe = fopen(argv[1], "r");
   do {
      c = fgetc(fe);
      if( feof(fe) ) {
         break ;
      }
      Longitud++;        /* Actualiza la cuenta de la longitud del fichero */
      Cuenta(&Lista, c); /* Actualiza la lista de frecuencias */
   } while(1);
   fclose(fe);

   /* Ordenar la lista de menor a mayor */
   Ordenar(&Lista);

   /* Crear el arbol */
   Arbol = Lista;
   while(Arbol && Arbol->sig) /* Mientras existan al menos dos elementos en la lista */
   {
      p = (tipoNodo *)malloc(sizeof(tipoNodo)); /* Un nuevo árbol */
      p->letra = 0;                             /* No corresponde a ninguna letra */
      p->uno = Arbol;                           /* Rama uno */
      Arbol = Arbol->sig;                       /* Siguiente nodo en */
      p->cero = Arbol;                          /* Rama cero */
      Arbol = Arbol->sig;                       /* Siguiente nodo */
      p->frecuencia = p->uno->frecuencia +
                      p->cero->frecuencia;      /* Suma de frecuencias */
      InsertarOrden(&Arbol, p);                 /* Inserta en nuevo nodo */
   }                                            /* orden de frecuencia */

   /* Construir la tabla de códigos binarios */
   Tabla = NULL;
   CrearTabla(Arbol, 0, 0);

   /* Crear fichero comprimido */
   fs = fopen(argv[2], "wb");
   /* Escribir la longitud del fichero */
   fwrite(&Longitud, sizeof(long int), 1, fs);
   /* Cuenta el número de elementos de tabla */
   nElementos = 0;
   t = Tabla;
   while(t)
   {
      nElementos++;
      t = t->sig;
   }
   /* Escribir el número de elemenos de tabla */
   fwrite(&nElementos, sizeof(int), 1, fs);
   /* Escribir tabla en fichero */
   t = Tabla;
   while(t)
   {
      fwrite(&t->letra, sizeof(char), 1, fs);
      fwrite(&t->bits, sizeof(unsigned long int), 1, fs);
      fwrite(&t->nbits, sizeof(char), 1, fs);
      t = t->sig;
   }

   /* Codificación del fichero de entrada */
   fe = fopen(argv[1], "r");
   dWORD = 0; /* Valor inicial. */
   nBits = 0; /* Ningún bit */
   do {
      c = fgetc(fe);
      if( feof(fe) ) {
         break ;
      }
      /* Busca c en tabla: */
      t = BuscaCaracter(Tabla, c);
      /* Si nBits + t->nbits > 32, sacar un byte */
      while(nBits + t->nbits > 32)
      {
         c = dWORD >> (nBits-8);           /* Extrae los 8 bits de mayor peso */
         fwrite(&c, sizeof(char), 1, fs);  /* Y lo escribe en el fichero */
         nBits -= 8;                       /* Ya tenemos hueco para 8 bits más */
      }
      dWORD <<= t->nbits; /* Hacemos sitio para el nuevo caracter */
      dWORD |= t->bits;   /* Insertamos el nuevo caracter */
      nBits += t->nbits;  /* Actualizamos la cuenta de bits */
   } while(1);
   /* Extraer los cuatro bytes que quedan en dWORD*/
   while(nBits>0)
   {
      if(nBits>=8) c = dWORD >> (nBits-8);
      else c = dWORD << (8-nBits);
      fwrite(&c, sizeof(char), 1, fs);
      nBits -= 8;
   }

   fclose(fe);  /* Cierra los ficheros */
   fclose(fs);

   /* Borrar Arbol */
   BorrarArbol(Arbol);

   /* Borrar Tabla */
   while(Tabla)
   {
      t = Tabla;
      Tabla = t->sig;
      free(t);
   }

   return 0;
}

/* Actualiza la cuenta de frecuencia del carácter c */
/* El puntero a Lista se pasa por referencia, ya que debe poder cambiar */
/* Ya sea por que la lista esté vacía, o porque el nuevo elemento sea el */
/* primero */


