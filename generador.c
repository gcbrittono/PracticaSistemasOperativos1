#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>


struct DogType {
        char nombre[32];
        char tipo[32];
        int edad;
        char raza[16];
        int estatura;
        double peso;
        char   sexo;
};

int main(){
	FILE *file;
	file = fopen("nombresMascotas.txt", "r");
	char nombres[1716][32];
	for ( int i = 0; i < 1717; i++){

		fgets(nombres[i],32,file);
	}
	
	fclose(file);
	
	time_t t;
	srand((unsigned) time(&t));
	char nombre[32];
	char tipo[32];
	char raza[32];
	int edad;
	int peso;
	double estatura;
	char sexo;
	
	const char *tipoAnimal[] = {"Perro","Gato","Ave","Hamster","Tiburon"};
	const char *razaP[] = {"Labrador","Rottweiler","Beagle","Bulldog","Pug"};	
	const char *razaG[] = {"Siames","Persa","Ragdoll","Bengala","Sphynx"};	
	const char *razaA[] = {"Pato","Gallina","Loro","Ganzo","Perico"};	
	const char *razaH[] = {"Dorado","Roborovski","Chino","Ruso","Campbell"};	
	const char *razaT[] = {"Blanco","Tigre","Ballena","Toro","Mako"};
	int tipoAni;
	int razaAni;

	file = fopen("dataDogs.dat", "a+");

	struct DogType *mascota;
	mascota = malloc(sizeof(struct DogType));

	for(int i=0;i<1e2;i++){

		edad=(rand()%20)+1;
		peso=(rand()%20)+1;
		estatura=(rand()%50)+1;
		tipoAni = rand()%5;
		razaAni = rand()%5;		
		switch(tipoAni){
			case 0:
				snprintf(raza,32,"%s",razaP[razaAni]);
				break;
			case 1:
				snprintf(raza,32,"%s",razaG[razaAni]);
				break;
			case 2:
				snprintf(raza,32,"%s",razaA[razaAni]);
				break;
			case 3:
				snprintf(raza,32,"%s",razaH[razaAni]);
				break;
			case 4:
				snprintf(raza,32,"%s",razaT[razaAni]);
				break;
		}
	
		snprintf(tipo,32,"%s",tipoAnimal[tipoAni]);
		snprintf(nombre,32,"%s",nombres[rand()%1717]);

		if(tipoAni%2==0){
			sexo='F';		
		}else{
			sexo='M';
		}
		
		nombre[strlen(nombre)-1] = '\0';
		snprintf(mascota->nombre,32,"%s",nombre);
		snprintf(mascota->tipo,32,"%s",tipo);
		mascota->edad = edad;
		snprintf(mascota->raza,32,"%s",raza);
		mascota->estatura = estatura;
		mascota->peso = peso;
		mascota->sexo = sexo;	
	
		fwrite(mascota, sizeof(struct DogType),1, file);
	}

	fclose(file);
	free(mascota);
	return 0;
}
