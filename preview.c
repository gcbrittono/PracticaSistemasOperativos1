#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>

#define HASH_SIZE 1000

#include "hash.c"
char str[32];


struct datos {
	char nombre[32];
	char tipo[32];
	int edad;
	char raza[16];
	int32_t estatura;
	double peso;
	char   sexo;
};



void toLower (char* string){
	int i=0;	
	for(i=0;i<string[i];i++){
		string[i]=tolower(string[i]);	
	}
	snprintf(str,sizeof(str),"%s",string);
	
}

void recibir(void *ap){
    struct datos *dato;
	dato=ap;
	char input[32];

    printf("Ingrese el nombre de su mascota:");
    scanf("%s", input);      
	toLower(input);
	snprintf(dato->nombre,sizeof(dato->nombre),"%s",str);				

	printf("Ingrese el tipo de mascota:");
    scanf("%s", input);
	toLower(input);
	snprintf(dato->tipo,sizeof(dato->tipo),"%s",str);			

    printf("Ingrese la edad de su mascota:");
    scanf("%i", &dato->edad);
    
    printf("Ingrese la raza de su mascota:");
    scanf("%s", input);
	toLower(input);
	snprintf(dato->raza,sizeof(dato->raza),"%s",str);			
        
	printf("Ingrese la estatura de su mascota:");
    scanf("%i", &dato->estatura);

    printf("Ingrese el peso de su mascota:");
    scanf("%lf", &dato->peso);

    printf("Ingrese el sexo de su mascota:");
    scanf(" %c", &dato->sexo);

}


void ingresar_registro(){

	struct datos *mascota;
	mascota = malloc(sizeof(struct datos));
	recibir(mascota);
	printf("nombre: %s \n", mascota->nombre);
	printf("tipo: %s \n", mascota->tipo);
	printf("edad: %i \n", mascota->edad);
	printf("raza %s \n", mascota->raza);
	printf("estatura %i \n", mascota->estatura);
	printf("peso %.2lf \n", mascota->peso);
	printf("sexo %c \n", mascota->sexo);


    FILE *ach;
    ach = fopen("datos.dat", "w");
    fwrite(mascota, sizeof(struct datos),1, ach);
    fclose(ach);


	free(mascota);
}






int main(){
	
	struct ListNode * hashTable = getHashTable();
	
	
	int rnd, hash = -1, nuevo = -1, toDel;
	
	for(int i = 0; i < 100; i++){
		rnd = rand();
		if(i == 50){
			toDel = i;
		}
		
		hash = setElementInHash(hashTable, rnd);	
		
		//nuevo = hashTable[hash % HASH_SIZE].data;
		nuevo = getElementInHash(hashTable, hash);
		if(i == 50){
			printf("->");
		}
		printf("Guardado: %i\t Obtenido: %i \n", rnd, nuevo);
	}
	
	removeELementInHash(hashTable, toDel);
	nuevo = getElementInHash(hashTable, toDel);// nuevo deberia ser -1 pues ya no deberia existir el
											   // elemento con funcion hash toDel
	printf("->%i\n", nuevo);
	
	
	
	
	


/*int menu = 0;
bool flag=true;
while(flag){
	char hola[32];

	
	printf("MenÃº: \n 1. Ingresar registro \n 2. Ver registro \n 3. Borrar registro \n 4. Buscar registro \n 5. Salir \n");
    	scanf("%i", &menu);

     switch(menu){
      case 1:
       ingresar_registro();
      break;
      case 2:
      printf("2");
      break;
      case 3:
      printf("3");
      break;
      case 4:
      printf("4");
      break;
      case 5:
      flag=false;
      break;
      default:
      printf("No se reconoce la entrada");       
     }
	if(flag){
      	printf("Presione cualquier tecla para volver al menu principal \n");
		scanf("%s", hola);   
	}      	
	
}
	*/

    return 0;
}

