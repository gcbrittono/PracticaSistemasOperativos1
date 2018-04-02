#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#define HASH_SIZE 1000

int cantidadDeRegistros = -1;

struct DogType {
        char nombre[32];
        char tipo[32];
        int edad;
        char raza[16];
        int estatura;
        double peso;
        char   sexo;
};

struct ListNode{
	struct ListNode *next;
	struct ListNode *tail;
	int data;
	bool used;
};

int funHash(char* str){ // tomado de https://stackoverflow.com/questions/7666509/hash-function-for-string
	int hash, i;
	int len = strlen(str);
	
    for(hash = i = 0; i < len; ++i)
    {
        hash += str[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return (int)fabs(hash % HASH_SIZE);
}

struct ListNode * getEmptyListNode(){
	struct ListNode * salida = malloc(sizeof(struct ListNode));
	salida->next = NULL;
	salida->used = false;
	salida->data = -1;
	salida->tail = salida;
	return salida;
}

struct ListNode * getHashTable(){
	struct ListNode *hashTable;
	hashTable = malloc(HASH_SIZE * sizeof(struct ListNode));
	int j;
	struct ListNode new;
	for(j = 0; j < HASH_SIZE; j++){
		new = *getEmptyListNode();
		hashTable[j] = new;
	}
	return hashTable;
}

int setElementInHash(struct ListNode *hashAp, int data, char *nombre){
	
	int hashVal = funHash(nombre);

	struct ListNode *actual = &hashAp[hashVal];

	if(actual->used){
		struct ListNode *last = actual->tail;
		last->data = data;
		last->used = true;
		last->next = getEmptyListNode();
		actual->tail = last->next;			
	}else{
		actual->data=data;
		actual->used = true;
		actual->next=getEmptyListNode();
		actual->tail= actual->next;
	}
	
	return hashVal;
}

void printDogType(struct DogType *mascota){
	printf("\nNombre: \t%s\n", mascota->nombre);
	printf("Tipo: \t\t%s\n", mascota->tipo);
	printf("Edad: \t\t%i\n", mascota->edad);
	printf("Raza: \t\t%s\n", mascota->raza);
	printf("Estatura: \t%i\n", mascota->estatura);
	printf("Peso: \t\t%.2lf\n", mascota->peso);
	printf("Sexo: \t\t%c\n\n", mascota->sexo);
}

void search(char* nombre, struct ListNode *hashAp){

	int hashVal = funHash(nombre);
	struct ListNode *actual = &hashAp[(int)fabs(hashVal % HASH_SIZE)];
	int index;
	FILE *file;
	file = fopen("dataDogs.dat","r");
	struct DogType *mascota;
	mascota = malloc(sizeof(struct DogType));
	while(actual->used){	
		index = actual->data;	
		fseek(file, (index-1)*104, SEEK_SET);		
		fread(mascota,sizeof(struct DogType),1,file);
		if(strcmp(mascota->nombre,nombre)==0){
			printDogType(mascota);
		}
		actual = actual->next;			
	}
	fclose(file);
	free(mascota);
}
struct ListNode *readHashTable(){
	struct ListNode * hashTable = getHashTable();
	FILE *file;
	file = fopen("dataDogs.dat", "r");
	if(file != NULL){
		struct DogType *mascota;
    		mascota = malloc(sizeof(struct DogType));
    		int i = 1;
		while(fread(mascota, sizeof(struct DogType),1,file)){
			setElementInHash(hashTable, i, mascota->nombre);
			i++;
		}
		fclose(file);
		free(mascota);
		cantidadDeRegistros = i - 1;
	}else{
		cantidadDeRegistros = 0; 
	}
	return hashTable;
}

void removeFromFile(int index){
	FILE *file;
	FILE *temp;
	temp = fopen("temp.dat","w+");
	file = fopen("dataDogs.dat","r");
		
	struct DogType *mascota;
	mascota = malloc(sizeof(struct DogType));
	
	for(int i = 1; i<=cantidadDeRegistros; i++){
		fread(mascota, sizeof(struct DogType),1,file);		
		if(i!=index){
			fwrite(mascota, sizeof(struct DogType),1, temp);
		}
	}

	free(mascota);
	fclose(file);
	fclose(temp);
	system("rm dataDogs.dat");
	system("mv temp.dat dataDogs.dat");

}


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

	setElementInHash(hashAp,cantidadDeRegistros+1,mascota->nombre);
	printDogType(mascota);

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
void read(int a){
	FILE *file;
	file = fopen("dataDogs.dat", "r");

	fseek(file, (a-1)*104, SEEK_SET);

	struct DogType *mascota;
	mascota = malloc(sizeof(struct DogType));
	fread(mascota, sizeof(struct DogType),1,file);
	printDogType(mascota);

	char nameFile[200]="";

	char commandLine[100]="gedit ";

	char n[64]={0};

	strcat(nameFile,mascota->nombre);
	strcat(nameFile,mascota->tipo);
	strcat(nameFile,mascota->raza);
	nameFile[strlen(nameFile)]=mascota->sexo;
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
					read(registerToRead);
				}else{
					printf("El Numero de registro no es valido\n");
				}
		  		break;
		  	case 3:
				printf("El numero de registros es: %i\nIngrese el Numero de registro: ", cantidadDeRegistros);
				scanf("%i",&registerToRead);
				if(registerToRead <= cantidadDeRegistros && registerToRead>0){

		  			removeFromFile(registerToRead);
					hashTable=readHashTable();

				}else{

					printf("El Numero de registro no es valido\n");

				}
						  		
		  		
		  		break;
		  	case 4:
		  		printf("Ingrese el nombre de la mascota: ");
				scanf("%s",busqueda);
				search(busqueda,hashTable);
				break;
		  	case 5:
				flag=false;
				break;
			default:

			}
		if(flag){
			printf("Presione cualquier tecla para volver al menu principal \n");
			scanf("%s", trash);
		}

	}
	

	return 0;
}
