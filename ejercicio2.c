#include <stdio.h>
#include <string.h>

/*

Ejercicio 2:
Debe realizar una función que reciba un carácter numérico y retorne un número entero.

*/

int convertir(char caracter){
    return caracter - '0';
}

int main(){

    char caracter;

    //%c -> caracter
    printf("Ingrese un caracter numerico: ");
    scanf("%c", &caracter);

    //%d -> decimal
    printf("El numero es: %d\n", convertir(caracter));

    return 0;
}