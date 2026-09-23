#include <stdio.h>
#include <string.h>

/* 

Ejercicio 1:
Dada una cadena que contenga varios números que pueden ser decimales, octales o hexadecimales, con o sin signo para
el caso de los decimales, separados por el carácter ‘@’ , reconocer los tres grupos de constantes enteras, indicando si
hubo un error léxico , en caso de ser correcto contar la cantidad de cada grupo.

*/

int esDecimal(char *cadena){
    
    //Arranco en el Estado 1
    int estado = 1; 

    //Arranco en 0
    int pos = 0; // Posicion en la q se encuentra leyendo la cadena 

    //De estado 0 -> 1, puedo consumir '+,-' o 'e' (epsilon)
    if(cadena[pos] == '+' || cadena[pos] == '-'){
        pos++;
    }

    //Si en la primera posicion no hay signo, entonces consume e 
    //y la primera posicion queda en 0 para leer el primer digito
    estado = 2;

    //Si empieza con 0
    if(cadena[pos] == '0'){

        pos++;

        //0 solo es decimal
        if(cadena[pos] == '\0'){
            estado = 4;
            return estado;
        }

        //Si hay algo después del 0, no es decimal, deberia de ser octal o hexadecimal
        return -1;
    }

    //Si empieza entre 1 y 9
    if(cadena[pos] >= '1' && cadena[pos] <= '9'){

        pos++;

        //estado 2 ->3
        estado = 3;

        while(cadena[pos] >= '0' && cadena[pos] <= '9'){
            pos++;
        }

        if(cadena[pos] == '\0'){
            estado = 4;
            return estado;
        }
    }

    //Si hay cualquier otro carácter, error léxico o no es decimal
    return -1;
}

int esOctal(char *cadena){

    //Arranco en el Estado 5
    int estado = 5;

    //Arranco en la posición 0
    int pos = 0;

    //Para q sea octal debe consumir inicialmente el caracter '0' sino es un error lexico o no es octal
    if(cadena[pos] == '0'){

        //estado 5 -> 6
        estado = 6;
        pos++;
    }
    else{
        return -1;
    }

    //Este if esta puesta para q si hay un solo 0, lo tome como decimal y no como octal
    if(cadena[pos] >= '0' && cadena[pos] <= '7'){

        //Leo los digitos y cambio el estado de 6 -> 7
        while(cadena[pos] >= '0' && cadena[pos] <= '7'){
            pos++;
        }

        estado = 7;
    }
    else{
        return -1;
    }

    //Si llegamos al final, la cadena es octal
    if(cadena[pos] == '\0'){

        //estado 7 -> 4(Estado Final)
        estado = 4;
        return estado;
    }

    //Si hay cualquier otro carácter, error léxico o no es octal
    return -1;
}

int esHexadecimal(char *cadena){
    //Arranco en el Estado 8
    int estado = 8;

    //Arranco en la posición 0
    int pos = 0;

    //Para q sea hexadecimal debe consumir inicialmente el caracter '0' sino es un error lexico o no es octal
    if(cadena[pos] == '0'){

        //estado 8 -> 9
        estado = 9;
        pos++;
    }
    else{
        return -1;
    }

    //Para q sea hexadecimal debe consumir el caracter 'x' sino es un error lexico o no es octal
    if(cadena[pos] == 'x'){

        //estado 9 -> 10
        estado = 10;
        pos++;
    }
    else{
        return -1;
    }

    //Tiene que haber al menos un dígito hexadecimal
    if((cadena[pos] >= '0' && cadena[pos] <= '9') || (cadena[pos] >= 'A' && cadena[pos] <= 'F')){

        while((cadena[pos] >= '0' && cadena[pos] <= '9') || (cadena[pos] >= 'A' && cadena[pos] <= 'F')){
            pos++;
        }

        //estado 10 -> 11
        estado = 11;
    }

    else{
        return -1;
    }


    //Si llegamos al final, la cadena es hexadecimal
    if(cadena[pos] == '\0'){

        //estado 11 -> 4(Estado Final)
        estado = 4;
        return estado;
    }

    //Si hay cualquier otro carácter, error léxico o no es octal
    return -1;
}

void analizarCadena(char *cadena){

    //Contadores
    int decimales = 0;
    int octales = 0;
    int hexadecimales = 0;
    int errores = 0;

    //Tomo toda la entrada como un token, con separador '@'
    char *token = strtok(cadena, "@");
    while(token != NULL){

         //Cada token lo analizo si es decimal, octal o hexadecimal
        if(esHexadecimal(token) != -1){
            hexadecimales++;
        }
        else if(esOctal(token) != -1){
            octales++;
        }
        else if(esDecimal(token) != -1){
            decimales++;
        }
        //En caso de no sea ninguno es un error lexico, sumo el contador e imprimo en cual token hay error lexico
        else{
            errores++;
            printf("Error lexico: %s\n", token);
        }

        token = strtok(NULL, "@");
    }

    //Imprimo
    printf("\nDecimales: %d\n", decimales);
    printf("Octales: %d\n", octales);
    printf("Hexadecimales: %d\n", hexadecimales);
    printf("Errores lexicos: %d\n", errores);
}

int main() {
    
    char cadena[100];

    printf("Ingrese la cadena: ");
    scanf("%s", cadena);

    analizarCadena(cadena);

    return 0;
}