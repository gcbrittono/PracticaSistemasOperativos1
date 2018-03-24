#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include "Tabla Hash2.c"



char* convertir_minusculas(char* string){
	int size = strlen(string);
	for(int i=0;i<size;i++){
		string [i]=tolower(string[i]);
	}
	return string;
}

int recibir(void *ap){
	struct DogType *dato;
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


void ingresar_registro(struct ListNode *hashAp){

	struct DogType *mascota;
	mascota = malloc(sizeof(struct DogType));
	recibir(mascota);
	printf("nombre: %s \n", mascota->nombre);
	printf("tipo: %s \n", mascota->tipo);
	printf("edad: %i \n", mascota->edad);
	printf("raza %s \n", mascota->raza);
	printf("estatura %i \n", mascota->estatura);
	printf("peso %.2lf \n", mascota->peso);
	printf("sexo %c \n", mascota->sexo);
	int cantidad;
	
	cantidad = cantidadDeRegistros;
	
	setElementInHash(hashAp,cantidad+1,mascota->nombre);
	
    FILE *ach;
    ach = fopen("dataDogs.dat", "a+");
    fwrite(mascota, sizeof(struct DogType),1, ach);
    fclose(ach);
    cantidadDeRegistros++;
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

}

void* generar(char * name){
    FILE *ach;
    char** tipos = calloc (4,sizeof(char*));
    char** razas = calloc(4, sizeof(char*));
    tipos[0] = "Perro";
    tipos[1] = "Gato";
    tipos[2] = "Tortuga";
    tipos[3] = "Hamster";

    int tipo =rand() % 4;

    switch(tipo){
        case(0):
            razas[0] = "Beagle";
            razas[1] = "Rottweiler";
            razas[2] = "Labrador";
            razas[3] = "Terranova";
        break;
        case(1):
            razas[0] = "Bengala";
            razas[1] = "Sphynx";
            razas[2] = "Siberiano";
            razas[3] = "Korat";
        break;
        case(2):
            razas[0] = "Carrey";
            razas[1] = "Golfina";
            razas[2] = "Mediterranea";
            razas[3] = "Estrellada";
        break;
        case(3):
            razas[0] = "Dorado";
            razas[1] = "Enano Ruso";
            razas[2] = "Roborovski";
            razas[3] = "Arlequín";
        break;
    };
    bool randbool = rand() & 1;
    char sexo;
    if(randbool){
        sexo = 'm';
    }else{
        sexo = 'h';
    }

    double peso = (rand() % 100);

    struct DogType *mascota;
    mascota = malloc(sizeof(struct DogType));

    mascota->edad = (rand() % 20);
    mascota->peso = peso;
    mascota->sexo = sexo;
    mascota->estatura = (rand() % 100);
    snprintf(mascota->nombre, sizeof(mascota->nombre), "%s",name);
    snprintf(mascota->tipo, sizeof(mascota->tipo),"%s", tipos[(tipo)]);
    snprintf(mascota->raza, sizeof(mascota->raza),"%s", razas[rand() % 3]);

    ach = fopen("dataDogs.dat", "a+");

    fwrite(mascota, sizeof(struct DogType),1, ach);

    fclose(ach);
    free(mascota);
 };

int main(){
	int menu = 0;
	bool flag=true;
	char hola[32];
	int nregistros = 0;
	int registerToRead=0;
	FILE * archivo;
	char data[1000][32];
	char busqueda[32];
	struct ListNode * hashTable;
	struct DogType *mascota;
	hashTable = readHashTable();


	while(flag){
		printf("Menuº: \n 1. Ingresar registro \n 2. Ver registro \n 3. Borrar registro \n 4. Buscar registro \n 5. Salir \n 6. Generador de Estructuras \n");
		scanf("%i", &menu);

		switch(menu){
			case 1:
				ingresar_registro(hashTable);
				break;
			case 2:
				nregistros=cantidadDeRegistros;
				printf("El numero de registros es: %i\nIngrese el Numero de registro: ", nregistros);
				scanf("%i",&registerToRead);

				if(registerToRead <= nregistros && registerToRead>0){
					leer(registerToRead);
				}else{
					printf("El Numero de registro no es valido\n");
				}
		  		break;
		  	case 3:
		  		nregistros=cantidadDeRegistros;
				printf("El numero de registros es: %i\nIngrese el Numero de registro: ", nregistros);
				scanf("%i",&registerToRead);
				archivo = fopen("dataDogs.dat", "r");
				mascota = malloc(sizeof(struct DogType));
				fseek(archivo, (registerToRead-1)*104, SEEK_SET);
				fread(mascota, sizeof(struct DogType),1,archivo);
				fclose(archivo);
				
		  		removeElementInHash(hashTable, registerToRead, mascota->nombre);
		  		free(mascota);		  		
		  		
		  		break;
		  	case 4:
		  		printf("Ingrese el nombre de la mascota: ");
				scanf("%s",busqueda);
				search(busqueda,hashTable);
				break;
		  	case 5:
				flag=false;
				//saveHashTable(hashTable);
				break;
			case 6:

				archivo = fopen("nombresMascotas.txt", "r");
				for ( int i = 0; i < 1000; i++)
				{
		    		fscanf(archivo, "%s" , data[i]);

				}
				fclose(archivo);
				char nombre[32];
				for ( int i = 0; i < 1e5; i++)
				{
		    		snprintf(nombre, sizeof(nombre),"%s",data[rand() % 1000]);
					convertir_minusculas(nombre);
	  	    	  	generar(nombre);
				}
				hashTable = readHashTable();
				break;
			default:
				printf("default");
			}
		if(flag){
			printf("Presione cualquier tecla para volver al menu principal \n");
			scanf("%s", hola);
		}

	}
	

	return 0;
}
