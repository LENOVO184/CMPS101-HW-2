//Robert Mushkot
//rmushkot
//1543374
//pa2
//Lex.c



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"


int main(int argc, char * argv[]){

   int n, count=0;
   FILE *in, *out;
   char line[100];
   
   	if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}


	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	
	if( in==NULL ){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if( out==NULL ){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	n =0;
	//determines the size of the array
	while( fgets(line,sizeof(line), in) !=NULL){
		count++;
	}
	
	char** words = malloc(sizeof(char *)*count);
	rewind(in);


	//takes line from input file and puts it into array 
	while(fgets(line,sizeof(line),in) != NULL){
		words[n] = malloc(strlen(line));
		strcpy(words[n], line);
		n++;
	}	
	
	List list = newList();
	append(list,0);
	
	// sorts the list of words using a variation of insertion ssort
	for(int j = 1; j<count; j++){
		moveFront(list);
		while(strcmp(words[j], words[get(list)]) > 0){
			if(length(list) == 1) append(list,j);
			if(length(list) == index(list) +1) append(list,j);
			moveNext(list);
		}
		
		if(strcmp(words[j],words[get(list)]) < 0){
			insertBefore(list,j);
		}
	}

	//ttraverses list and prints the sorted list to the out file
	moveFront(list);
	while(index(list) >=0){
		int k = get(list);
		fprintf(out, "%s", words[k]);
		moveNext(list);
	}
	

	//frees 
	freeList(&list);
	free(list);
	fclose(in);
	fclose(out);
	for(int i = 0; i < count; i++){
		free(words[i]);
	}
	free(words);

	return(0);
}



