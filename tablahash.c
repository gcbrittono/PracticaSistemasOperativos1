#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct mydata_tag {
      int used; /* 0 = empty, 1 = used */
      int key;
      char name[24];
} mydata;



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

     fp=fopen(filename, "r+");
     if(fp == NULL){
       perror("fopen: insert_data");
       exit(1);
     }
     
     while(1){
       fseek(fp, pos*sizeof(mydata), SEEK_SET);
       fread(&slot, sizeof(mydata), 1, fp);
       if(slot.used != 1){
           break;     

       }
       printf("Collison!\n");
       pos++;
       pos %=10;
     }
     printf("pos = %d\n", pos);
     fseek(fp, pos*sizeof(mydata), SEEK_SET);
     fwrite(&data, sizeof(mydata), 1, fp);
     fclose(fp);
}

void print_buckets(char* filename){
     FILE *fp;
     mydata data;
     int i;

     fp=fopen(filename, "r+");
     if(fp == NULL){
       perror("fopen: insert_data");
       exit(1);
     }

     for(i=0;i<10;i++){
        fread(&data, sizeof(mydata), 1, fp);
        printf("used = %d, key = %d, data = %s\n", data.used, data.key, data.name);

     }


     fclose(fp);
}



int main(){
    
  int key;

  char* names[7] ={
     "John",
     "Steve",
     "Ajit",
     "Premal",
     "Kho",
     "Xiang",
     "Yamamoto"
  };

  init_table("myhashtable",10);

/*
  for(int i=0;i<7;i++){
    key = hash_key(names[i]);
    printf("key = %d, name = %s\n", key, names[i]);
  }
*/
 
  for(int i=0;i<7;i++){
     key = hash_key(names[i]);
     insert_data(key, names[i], "myhashtable");
  }
  print_buckets("myhashtable");
  


 return 0;
}
