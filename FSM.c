#include <stdio.h>

int STATE = -1;
float number = 0;
struct Dimension {
 int length;
 int width;
};

struct Dimension dim;
int main() {
    FILE *file;
    int c;  // Note: int instead of char to handle EOF correctly
    
    file = fopen("gui.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1 ;
    }
    
    while ((c = fgetc(file)) != EOF) {

		 
        //<dim>
		if(c == '<'){
          STATE = 0 ;
		}

		if(STATE==0 && c=='d'){
           STATE = 1 ; 
		}

        if(STATE==1 && c=='i'){
           STATE = 2 ; 
		}

        if(STATE==2 && c=='m'){
           STATE = 3 ;
		}

        if(STATE==3 && c=='l'){
           STATE = 4 ; 
		}

		if(STATE==4 && c=='e'){
           STATE = 5 ; 
		}

		if(STATE==5 && c=='n'){
           STATE = 6 ; 
		}
		 
        if(STATE==6 && c=='='){
           STATE = 7 ;
		}

        if(STATE==7 && (fscanf(file, "%f", &number) == 1)){
           STATE = 8 ;
		   printf("Read float: %f\n", number);
		   dim.length = number;
		   number = -1 ;
		}

        if(STATE==8 && c=='w'){
           STATE = 9 ;
		}

		if(STATE==9 && c=='i'){
           STATE = 10 ;
		}

		if(STATE==10 && c=='d'){
           STATE = 11 ;
		}

        if(STATE==11 && c=='='){
           STATE = 12 ;
		}

		if(STATE==12 && (fscanf(file, "%f", &number) == 1)){
           STATE = 13 ;
		   printf("Read float: %f\n", number);
		   dim.width = number;
		   number = -1 ;
		}

		if(STATE==13 && c=='>'){
           STATE = 14 ;
		}

        printf("[%c]-->[%d]\n",c,STATE);
		//</dim>

    }

	while(1==1){}
    
    fclose(file);
    return 0;
}
