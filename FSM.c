#include <stdio.h>

int STATE = -1;
float number = 0;

struct Dimension {
 int length;
 int width;
};

struct Box {
int type;// (button,image,div) = (1,2,3)
int length;
int width;
int R;
int G;
int B;
int positionX;
int positionY;
};

struct Dimension dim;
struct Box boxes[100];
int boxesIndex = 0;
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

		if(STATE==13 && c=='>'){ // push dimension data into an from hear
           STATE = 14 ;
		}

		if(STATE==0 && c =='b'){
           STATE = 15 ;
		}

		if(STATE == 15 && c =='o'){
           STATE = 16;
		}

		if(STATE == 16 && c=='x'){
           STATE = 17;
		   // box
		   if(100>boxesIndex+1){
              boxesIndex++;
		   }
		}

		if(STATE == 17 && c=='l'){
            STATE=18;
		}

		if(STATE == 18 && c =='e'){
            STATE = 19;
		} 
         
		if(STATE == 19 && c == 'n'){
			STATE = 20;
		}

		if(STATE == 20 && c == '='){
			STATE = 21;
		}

		if(STATE==21 && (fscanf(file, "%f", &number) == 1)){
            STATE = 22 ;
		    printf("Read float: %f\n", number);
		    boxes[boxesIndex].length= number;
		    number = -1 ;
		}

        printf("[%c]-->[%d]\n",c,STATE);
		//</dim>

    }

	while(1==1){}
    
    fclose(file);
    return 0;
}

/*
 *Dimension tag has been completed and we are in the process of doing the box tag 
 * we have implemented the length variable of box as of now
 *
 *
 *
 *
 *
 *
 * */
