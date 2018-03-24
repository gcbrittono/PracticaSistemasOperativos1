#include <stdlib.h>
#include <stdio.h>
#include <string.h>




typedef struct mydata_tag {
      int used; /* 0 = empty, 1 = used */
      int key;
      char* name;
} mydata;


/*===========================================================================*/
/* hash function optimized for strings with big hash tables sizes            */
/*===========================================================================*/
typedef unsigned int INDEX;

INDEX hash (char* key, unsigned int H_SIZE){
      unsigned int hash_val=0;
      while(*key != '\0'){
          hash_val = (hash_val<<5)+*key++;
      }
  
      return (hash_val%H_SIZE);
}


/*===========================================================================*/



/*===========================================================================*/
/* improved hash key                                                         */
/*===========================================================================*/

//unsigned long hash(unsigned char *str){
//    unsigned long hash = 5381;
//    int c;

//    while (c = *str++)
//        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

//    return hash;
//}

/*===========================================================================*/


int hash_key(char* name){
    int key=0;
    size_t len;
    
    len= sizeof(name);
    for(int i=0;i<len;i++){
        key += name[i];

    }
    key %=10; 
    printf("key = %d, name= %s\n", key, name);
    return key;
}


void init_table (char* filename, int size){
    FILE *fp;
    mydata data;
    memset(&data, 0, sizeof(data));
    
    fp=fopen(filename,"w+");
    if (fp == NULL){
       perror("fopen: init_table");
       exit(1);
    }
    for(int i=0;i<size;i++){
        fwrite(&data, sizeof(mydata), 1, fp);        

    }
}

void insert_data(int key, char* name, char* filename){
     FILE* fp;
     mydata data, slot;
     int pos;

     pos=key;
     data.used=1;
     data.key=key;
     strcpy(data.name, name);     
 printf(" slot0 : %d", slot.used);
     fp=fopen(filename, "r+");
     if(fp == NULL){
       perror("fopen: insert_data");
       exit(1);
     }
     
     while(1){
       printf(" slot : %d", slot.used);
       fseek(fp, pos*sizeof(mydata), SEEK_SET);
       fread(&slot, sizeof(mydata), 1, fp);
       if(slot.used != 1){
           break;     

       }
       printf(" Collison!\n");
       printf("pos1:%d ",pos);
       pos++;
       pos %=1000;
       printf("posmod:%d ",pos);
     }
     printf(" pos = %d\n", pos);
     fseek(fp, pos*sizeof(mydata), SEEK_SET);
     fwrite(&data, sizeof(mydata), 1, fp);
     fclose(fp);
    
}

void print_buckets(char* filename, unsigned int H_SIZE){
     FILE *fp;
     mydata data;
     int i;

     fp=fopen(filename, "r+");
     if(fp == NULL){
       perror("fopen: insert_data");
       exit(1);
     }

     for(i=0;i<H_SIZE;i++){
        fread(&data, sizeof(mydata), 1, fp);
        printf("used = %d, key = %d, data = %s\n", data.used, data.key, data.name);

     }

     fclose(fp);
}



int main(){
    
  int key;

  char* names[29] ={
     "John",
     "Steve",
     "Ajit",
     "Premal",
     "Kho",
     "Xiang",
     "Yamamoto",
     "Giovani",
     "Daniel",
     "Lucas",
     "Maria",
     "Pedro",
     "Khaterin",
     "Xiomara",
     "Yamamoto",
     "John",
     "Esteban",
     "ndres",
     "Laura",
     "Hector",
     "Ivonne",
     "Luis",
     "John",
     "Steve",
     "Ajit",
     "Premal",
     "Kho",
     "Xiang",
     "Yamamoto"
  };

  init_table("myhashtable",1000);

/*
  for(int i=0;i<7;i++){
    key = hash_key(names[i]);
    printf("key = %d, name = %s\n", key, names[i]);
  }
*/
 
  for(int i=0;i<1000;i++){
     key = hash(names[i],1000);
     insert_data(key, names[i], "myhashtable");
  }
  print_buckets("myhashtable",1000);
  


 return 0;
}
