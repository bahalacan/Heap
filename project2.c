#include <stdio.h> 
#include <dirent.h> 
#include <stdlib.h>
#include <string.h>

int size = 0;
struct doc{
	char docName[30];
	char text[16000];
	int freq;
};
typedef struct doc doc;

void heapify(doc node[], int size, int i){	//Organizes array and find right place for nodes.
	int n = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (node[l].freq > node[n].freq && l < size){
		n = l;
	}
    if (node[r].freq > node[n].freq && r < size){
		n = r;
	}
    if (n != i){
    	doc temp = node[i];
		node[i] = node[n];
		node[n] = temp; 
  		heapify(node, size, n);
    }
}

void deleteRoot(doc node[]){ //Deletes node which has maximum number of frequency.
	doc temp = node[0];
	node[0] = node[size - 1];
	node[size - 1] = temp;
	
	printf("%s(%d): %s\n\n\n",temp.docName,temp.freq,temp.text);
	size -= 1;
	int i = size / 2 - 1;
	
	for (; i >= 0; i--){
    	heapify(node, size, i);
    }
    
}

int calculateFreq(char keyword[], char text[]){ //Calculates frequency of given word for each file.
	int count = 0;
	int i=0;
	char *word;
	int k=0;
	while(1){
		word = malloc(25 * sizeof(char));
		k =0;
		while(text[i] != ' ' && text[i] != '\n' && text[i] != '\0' && text[i] != ':' && text[i] != ','&& text[i] != '.'&& text[i] != '"'&& text[i] != '!'
		&& text[i] != '?'&& text[i] != '('&& text[i] != ')'&& text[i] != '*'){
			word[k] = text[i];
			i++;
			k++;
		}
		if(strcmp(word,keyword) == 0){
			count++;
		}
		if(text[i] == '\0'){
			break;
		}
		i++;		
	}
	return count;		
}
  
void createHeap(int freq, char docName[], char text[], doc node[]){//Creates heap.
	if (size != 0){
    	node[size].freq = freq;
   		strcpy(node[size].text,text);
    	strcpy(node[size].docName,docName);
    	size += 1;
    	int i = size / 2 - 1;
		for (; i >= 0; i--){
      		heapify(node, size, i);
    	}
  	}
  	else{
  		node[0].freq = freq;
    	strcpy(node[0].text,text);
    	strcpy(node[0].docName,docName);
    	size += 1;
  	}
}
int main(void) 
{ 
	int relevant = 0;
	char ch;
	int i=0;
	struct dirent *de;
	FILE *fp = NULL;
    char name[50];  
    int c=0;
	char keyword[25];
	doc node[120] = {'\0'};
	printf("Enter keyword: ");
	scanf("%s",keyword);
	DIR *dr = opendir("files"); 
  
    if (dr == NULL){ 
        printf("Could not open current directory" ); 
        return 0; 
    } 
  
   	while ((de = readdir(dr)) != NULL){	
   		char *text = malloc(100000 * sizeof(char)); 
   		if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){
        	strcpy(name, "files/");
        	strcat(name , de->d_name);
			fp = fopen(name,"r");	
        	if(fp == NULL){
            	printf("Could not open file");
			}
			i = 0;
			while((ch = fgetc(fp)) != EOF){
	 			text[i] = ch;
	 			i++;
			}		

		text[++i] = '\0';
		int freq = calculateFreq(keyword,text);
		if(freq != 0){
			relevant++;
			}
	createHeap(freq, de->d_name, text, node);
		}
	}
	printf("Number of relevant documents are: %d\n",relevant); 
	
	int e=0;
	if(relevant != 0){
		printf("The relevance order is:\n\n");	
	}
	
	for(; e<relevant;e++){
		deleteRoot(node);
		if(e==4){
			break;
		}	
	}	
	closedir(dr);     
    return 0; 
} 
