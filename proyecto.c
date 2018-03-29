#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include "Tabla Hash2.c"
#include<time.h>


void writeData(struct ListNode *hashAp, char * nombre, char * tipo, int edad, char * raza, int estatura, double peso, char sexo){
	struct DogType *mascota;
	mascota = malloc(sizeof(struct DogType));
	int len=strlen(nombre)-1;

	if(nombre[len]=='\n'){
		nombre[len] = '\0';				
	}
	

	snprintf(mascota->nombre,32,"%s",nombre);
	snprintf(mascota->tipo,32,"%s",tipo);
	mascota->edad = edad;
	snprintf(mascota->raza,32,"%s",raza);
	mascota->estatura = estatura;
	mascota->peso = peso;
	mascota->sexo = sexo;

	//setElementInHash(hashAp,cantidadDeRegistros+1,mascota->nombre);
	//printDogType(mascota);
	FILE *file;
	file = fopen("dataDogs.dat", "a+");
	fwrite(mascota, sizeof(struct DogType),1, file);
	fclose(file);
	free(mascota);	
	cantidadDeRegistros++;

}

void getData(struct ListNode *hashAp){

	char nombre[32];
	char tipo[32];	
	int edad;
	char raza[32];
	int estatura;
	double peso;
	char sexo;
	
	printf("Ingrese el nombre de su mascota:");
	scanf("%s", nombre);
	printf("Ingrese el tipo de mascota:");
	scanf("%s", tipo);
	printf("Ingrese la edad de su mascota:");

	while(true){	
		scanf("%d", &edad);
		if(edad<0){
			printf("La edad debe ser mayor o igual que 0\n");
		}else{
			break;
		}
	}

	printf("Ingrese la raza de su mascota:");
	scanf("%s", raza);
	printf("Ingrese la estatura de su mascota:");

	while(true){	
		scanf("%d", &estatura);
		if(estatura<0){
			printf("La estatura debe ser positiva\n");
		}else{
			break;
		}
	}

	printf("Ingrese el peso de su mascota:");

	while(true){	
		scanf("%lf", &peso);
		if(peso<0){
			printf("El peso debe ser positivo\n");
		}else{
			break;
		}
	}

	printf("Ingrese el sexo de su mascota:");

	while(true){	
		scanf(" %c", &sexo);
		if(sexo =='M' || sexo =='F'){
			break;
		}else{
			printf("El sexo de debe ser M o F\n");
		}
	}

	writeData(hashAp, nombre, tipo, edad, raza, estatura, peso, sexo);
	
}

void leerTodo(){
	FILE *ach;
	ach = fopen("dataDogs.dat", "r");
	struct DogType *mascota;
    	mascota = malloc(sizeof(struct DogType));
	while(fread(mascota, sizeof(struct DogType),1,ach)){
		printDogType(mascota);
	}
	fclose(ach);
	free(mascota);
}
void leer(int a){
	FILE *file;
	file = fopen("dataDogs.dat", "r");

	fseek(file, (a-1)*104, SEEK_SET);

	struct DogType *mascota;
	mascota = malloc(sizeof(struct DogType));
	fread(mascota, sizeof(struct DogType),1,file);
	printDogType(mascota);

	char nameFile[145]={0};

	char commandLine[100]="gedit ";

	char n[64]={0};

	strcat(nameFile,mascota->nombre);
	strcat(nameFile,mascota->tipo);
	strcat(nameFile,mascota->raza);
	strcat(nameFile,&mascota->sexo);
	sprintf(n, "%d", mascota->edad);
	strcat(nameFile,n);

	strcat(commandLine, nameFile);
	system(commandLine);
	fclose(file);
	free(mascota);

};


int main(){
	int menu = 0;
	bool flag = true;
	char trash[32];
	int registerToRead=0;
	FILE *archivo;
	char busqueda[32];

	struct ListNode *hashTable;
	
	hashTable = readHashTable();


	while(flag){
		printf("Menuº: \n 1. Ingresar registro \n 2. Ver registro \n 3. Borrar registro \n 4. Buscar registro \n 5. Salir \n");
		scanf("%i", &menu);

		switch(menu){
			case 1:
				getData(hashTable);
				break;
			case 2:

				printf("El numero de registros es: %i\nIngrese el Numero de registro: ", cantidadDeRegistros);
				scanf("%i",&registerToRead);

				if(registerToRead <= cantidadDeRegistros && registerToRead>0){
					leer(registerToRead);
				}else{
					printf("El Numero de registro no es valido\n");
				}
		  		break;
		  	case 3:
				printf("El numero de registros es: %i\nIngrese el Numero de registro: ", cantidadDeRegistros);
				scanf("%i",&registerToRead);
				if(registerToRead <= cantidadDeRegistros && registerToRead>0){

		  			removeElementInHash(hashTable, registerToRead);

				}else{

					printf("El Numero de registro no es valido\n");

				}
						  		
		  		
		  		break;
		  	case 4:
		  		printf("Ingrese el nombre de la mascota: ");
				scanf("%s",busqueda);
				search(busqueda,hashTable);
				//searchPrueba(hashTable);				
				break;
		  	case 5:
				flag=false;
				break;
			default:
				printf("default");
			}
		if(flag){
			printf("Presione cualquier tecla para volver al menu principal \n");
			scanf("%s", trash);
		}

	}
	

	return 0;
}
