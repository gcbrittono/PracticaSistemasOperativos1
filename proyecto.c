#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>

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


char* convertir_minusculas(char* string){
      size_t size = sizeof(string);
      for(int i=0;i<size;i++){
          string [i]=tolower(string[i]);
      }
  
      return string;
}

int funHash(char* str){
	int i;
	int ans=0;
	for(i=0;i<strlen(str);i++){
		ans+=(int)str[i];	
	}
	return ans%1000;
}

int recibir(void *ap){
   struct datos *dato;
   dato=ap;
   

        printf("Ingrese el nombre de su mascota:");
         scanf("%s", dato->nombre);
         convertir_minusculas(dato->nombre);
	printf("Ingrese el tipo de mascota:");
         scanf("%s", dato->tipo);
         convertir_minusculas(dato->tipo);	 		
        printf("Ingrese la edad de su mascota:");
         scanf("%i", &dato->edad);
        printf("Ingrese la raza de su mascota:");
         scanf("%s", dato->raza);
         convertir_minusculas(dato->raza);
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



}

int main(){
int menu = 0;
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
      printf("default");       
     }
	printf("%s",str);
	if(flag){
      	printf("Presione cualquier tecla para volver al menu principal \n");
		scanf("%s", hola);   
	}      	
	
}
	
    return 0;
}

