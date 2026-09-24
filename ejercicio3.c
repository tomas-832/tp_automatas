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
                }
                else{
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
                if(cadena[pos] == '\0'){
                    estado = 5; //Termino de leer la cadena
                    return 1;
                }
                else {
                    estado = 2;
                }
                break;
        }
    }
    
    return 1;
}

//Funcion reutilizada del ejercicio 2
int convertir(char caracter){
    return caracter - '0';
}

int operarCadena(char *cadena){
    int numeros[50];
    char operadores[50];
    int cant_num = 0;
    int cant_op = 0;
    int acumulador = 0;
    int es_negativo = 0;

    //Bucle para separar los caracteres
    for(int i = 0; cadena[i] != '\0'; i++){
        //Verificacion de signo del primer numero
        if(i == 0 && cadena[i] == '-'){
            es_negativo = 1;
            continue; //Pasa directamente al siguiente caracter
        }

        if(cadena[i] >= '0' && cadena[i] <= '9'){
            //Acumulador para numeros de multiples digitos
            acumulador = (acumulador * 10) + convertir(cadena[i]);
        }
        else if(cadena[i] == '+' || cadena[i] == '-' || cadena[i] == '*'){
            //Invierto el signo del numero
            if(es_negativo == 1){
                acumulador = acumulador * -1;
                es_negativo = 0;
            }
            
            //Una vez llegado a un operador, da por terminado el numero y
            //almacena el numero, el operador y actualiza la cantidad que hay de cada uno
            numeros[cant_num] = acumulador;
            cant_num++;
            operadores[cant_op] = cadena[i];
            cant_op++;

            //Reinicio el acumulador
            acumulador = 0;
        }
    }

    //Se realiza otro guardado para el ultimo digito ya que no hay operador que de por terminado el numero
    numeros[cant_num] = acumulador;
    cant_num++;
    
    //Bucle para resolver las multiplicaciones
    for(int i = 0; i < cant_op; i++){
        //Busca las multiplicaciones
        if(operadores[i] == '*'){
            //Realiza la multiplicacion con el digito siguiente
            numeros[i] = numeros[i] * numeros[i+1];
        

            //Acomoda las listas para 
            for(int j = i; j < cant_op - 1; j++){
                operadores[j] = operadores[j+1];
                numeros[j+1] = numeros[j+2];
            }

            //Reducimos la cantidad de operadores y volvemos un lugar en el indice
            cant_op--;
            i--;
        }
    }
    
    //Inicia desde el primer numero
    int resultado = numeros[0];

    //Bucle para resolver sumas y restas
    for(int i = 0; i < cant_op; i++){
        if(operadores[i] == '+'){
            resultado += numeros[i+1];
        }
        else if(operadores[i] == '-'){
            resultado -= numeros[i+1];
        }
    }

    return resultado;
}

int main(){
    char cadena[100];

    printf("Ingrese la cadena: ");
    scanf("%s", cadena);

    //Validamos la cadena siguiendo el automata diseñado
    if(validarCadena(cadena) == 1){
        printf("La cadena ingresada es correcta\n");
    
        //Imprimimos el resultado de operar la cadena valida
        printf("El numero es: %d\n", operarCadena(cadena));
    }
    else{
        printf("La cadena ingresada NO es correcta\n");
    }

    return 0;
}