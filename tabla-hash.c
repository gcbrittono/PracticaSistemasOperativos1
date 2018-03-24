#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

#define HASH_SIZE 1000


struct ListNode{
	struct ListNode *next;
	int data;
	int hashCode;
	bool used;
};

/*int funHash(char* str){
	int i;
	int ans=0;
	for(i=0;i<strlen(str);i++){
		ans+=(int)str[i];	
	}
	return ans;
}*/

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
	salida->hashCode = -1;
	return salida;
}

struct ListNode * getHashTable(){ //por https://stackoverflow.com/questions/1814463/returning-a-structure-array-using-pointers
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

int setElementInHash(struct ListNode *hashAp, int data){
	char valToHashFunc[80];
	int rnd = rand();
	sprintf(valToHashFunc, "%i%i%i", data, rnd,2*data + 1);//es solo para crear una string del numero dado
	int hashVal = funHash(valToHashFunc);
	struct ListNode *actual = &hashAp[(int)fabs(hashVal % HASH_SIZE)];
	while(actual->used){
		actual = actual->next;		
	}
	
	actual->data = data;
	actual->hashCode = hashVal;
	actual->used = true;
	actual->next = getEmptyListNode();
	return hashVal;
}

int getElementInHash(struct ListNode *hashAp, int hashValue){
	
	struct ListNode *actual = hashAp + ((int)fabs(hashValue % HASH_SIZE)); //fabs() es valor absoluto
	//printf("%i hash %i \n", actual->data, hashAp[(int)fabs(hashValue % HASH_SIZE)].data); //Buena preueba de como funciona
	while(actual->used == true && actual->hashCode != hashValue){
		actual = actual->next;
	}
	return actual->data;
}

int removeELementInHash(struct ListNode *hashAp, int hashValue){
	struct ListNode *actual = hashAp + ((int)fabs(hashValue % HASH_SIZE));
	struct ListNode *last = NULL;
	
	while(actual->used == true && actual->hashCode != hashValue){
		last = actual;
		actual = actual->next;
	}
	
	
	
	if(last == NULL){//Elemento directo del array o cabeza de la lista
		if(actual->next == NULL){
			hashAp[(int)fabs(hashValue % HASH_SIZE)] = *getEmptyListNode();
			//No se pone free aca porque .... (la verdad no se porque pero si lo pongo no sirve)
		}else{
			hashAp[(int)fabs(hashValue % HASH_SIZE)] = *(actual->next);
			free(actual);
		}		
	}else{
		last->next = actual->next;
		free(actual);
	}
	
	
	return actual->data;
}



