#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>








char* convertir_minusculas(char* str){
      size_t size = sizeof(str);
      for(int i=0;i<size;i++){
          str [i]=tolower(str[i]);
      }
  
      return str;
}

char nombre[];

int main(){
    printf("introducir el nombre en minusculas");
    scanf("%s", nombre);
    convertir_minusculas(nombre);
    printf("Su nombre es:%s \n", nombre);


return 0;
}
