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
    return hash;
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
	printf("Nombre: \t%s\n", mascota->nombre);
	printf("Tipo: \t\t%s\n", mascota->tipo);
	printf("Edad: \t\t%i\n", mascota->edad);
	printf("Raza: \t\t%s\n", mascota->raza);
	printf("Estatura: \t%i\n", mascota->estatura);
	printf("Peso: \t\t%.2lf\n", mascota->peso);
	printf("Sexo: \t\t%c\n", mascota->sexo);
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
			printf("\n");
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
	temp = fopen("temp.dat","a+");
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
	system("cp -f temp.dat dataDogs.dat");
	system("rm temp.dat");
}
void removeElementInHash(struct ListNode * hashAp, int value/*char *name*/){
	removeFromFile(value);
	hashAp=readHashTable();
	/*int hashValue = funHash(name);
	struct ListNode *actual = &hashAp[(int)fabs(hashValue % HASH_SIZE)];
	struct ListNode *last = NULL;
	while(actual->used == true && actual->data != value){
		last = actual;
		
		actual = actual->next;
	}
	
	if(last == NULL){//Elemento directo del array o cabeza de la lista
		if(actual->used){
			hashAp[(int)fabs(hashValue % HASH_SIZE)] = *(actual->next);
		}else{
			printf("El valor %i no tiene como nombre %s\n", value, name);
		}
	}else{
		last->next = actual->next;
		free(actual);
	}
	
	
	for(int i = 0; i< HASH_SIZE; i++){
		actual = &hashAp[i];
		while(actual->used){
			if(actual->data > value){
				actual->data = actual->data - 1;
			}
			actual = actual->next;
		}
	}*/
	
	cantidadDeRegistros--;
}


