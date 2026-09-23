#include <stdio.h>
#include <string.h>

/*

Ejercicio 3:
Ingresar una cadena que represente una operación simple con enteros decimales y obtener su resultado, se debe operar
con +,_ y *. Ejemplo = 3+4*7+3-5 = 29.
Considerando que el alfabeto son los números decimales, signos +,- y * valide con un automata previo a la operación
que dicha cadena que representa la operación pertenezca al lenguaje.

*/
int validarCadena(char *cadena){
    int estado = 0;
    int pos = 0;

    //Cada case representa un estado del automata
    while(estado != 5){

        switch (estado){

            case 0:
                //Primero puedo permitir - o e
                if(cadena[pos] == '-'){
                    pos++;
                }

                //Estado de 0 -> 1, ya se por - o e
                estado = 1;
                break;
            
            case 1:
                //Ahora puede ir de 1 -> 2 consumiendo un digito
                if(cadena[pos] >= '0' && cadena[pos] <= '9'){
                    pos++;
                    estado = 2;
                }
                else{
                    //Cadena no valida
                    return -1;
                }
                break;

            case 2:
                //Puedo agregar mas de un digito en el estado 2 (esto representa un bucle)
                while(cadena[pos] >= '0' && cadena[pos] <= '9'){
                    pos++;
                }

                //Puede ir un operador
                if(cadena[pos] == '-' || cadena[pos] == '+' || cadena[pos] == '*'){
                    pos++;
                    estado = 3;        
                }else{
                    //Cadena no valida
                    return -1;
                }
                break;

            case 3:
                //Ahora puede ir de 3 -> 4 consumiendo un digito
                if(cadena[pos] >= '0' && cadena[pos] <= '9'){
                    pos++;
                    estado = 4;
                }
                else{
                    //Cadena no valida
                    return -1;
                }
                break;

            case 4:
                //Otro bucle en el estado 4
                while(cadena[pos] >= '0' && cadena[pos] <= '9'){
                    pos++;
                }

                //Si no entra en el while vuelve al dos o termina la cadena
                if (cadena[pos] == '\0'){
                    estado = 5; //Termino de leer la cadena
                    return 1;
                }
                else {
                    estado = 2;
                }
                
                if(cadena[pos] == '-' || cadena[pos] == '+' || cadena[pos] == '*'){
                    return -1;
                }
                break;
        }
    }
    
    return 1;
}

int main(){
    char cadena[100];

    printf("Ingrese la cadena: ");
    scanf("%s", cadena);

    //Validamos la cadena siguiendo el automata diseñado
    if(validarCadena(cadena) == 1){
        printf("La cadena ingresa es correcta\n");
    }else{
        printf("La cadena ingresa NO es correcta\n");
    }

    //Imprimimos el resultado de operar la cadena
    printf("El numero es: %d\n", operarCadena(cadena));

    return 0;
}