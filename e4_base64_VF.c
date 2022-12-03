// e4_base64_VF.c
// Algoritmos para codificar y decodificar en base64
#include <stdio.h>
#include <string.h>
#include "e4_base64_VF.h"

int main() {
  //char mysrc[1024] = "";
   char mysrc[] = "hola";
  char mydco[1024] = "";
  char myb64[1024] = "";
  char mydst[1024] = "";

 //printf("Introduzca cadena a traducir en base 64:\n");
 //scanf("%[^\n]", mysrc);


  b64_encode(mysrc, myb64);
  printf("La cadena\n[%s]\nse codifica en base64 como:\n[%s]\n", mysrc, myb64);
  printf("\n");

  b64_decode(myb64, mydst);
  printf("La cadena\n[%s]\nse decodifica de base64 como:\n[%s]\n", myb64, mydst);

  return 0;
}
