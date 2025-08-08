#include <stdio.h>
#include <stdlib.h>
# define BUTTON 2 
# define IMAGE 1  
# define NORMAL 0 

int boxesIndex = -1 ;
int STATE = -1;
float number = 0;

struct Dimension {
 int length;
 int width;
};

struct Box {
 int type; // 1 = image . 0 = normal . 2 = button
 int length;
 int width;
 int R;
 int G;
 int B;
 int positionX;
 int positionY;
 char *src;
};

struct Dimension dim;
struct Box boxes[100];
int boxesLength;
int runFSM() {

    FILE *file;
    int c;  // Note: int instead of char to handle EOF correctly
    file = fopen("gui.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1 ;
    }
    
    while ((c = fgetc(file)) != EOF) {

		if(c == '<'){ STATE = 0 ; }
		if(STATE==0 && c=='d'){ STATE = 1 ; }
        if(STATE==1 && c=='i'){ STATE = 2 ; }
        if(STATE==2 && c=='m'){ STATE = 3 ; }
		if(STATE==3 && c=='l'){ STATE = 4 ; }
		if(STATE==4 && c=='e'){ STATE = 5 ; }
		if(STATE==5 && c=='n'){ STATE = 6 ; }
		if(STATE==6 && c=='='){ STATE = 7 ; }

		if(STATE==7 && (fscanf(file, "%f", &number) == 1)){
		   printf("Read float dimension length : %f\n", number);
		   dim.length = number;
		   number = -1 ;
		   STATE = 3;
		}

		if(STATE==3 && c=='w'){  STATE =  9 ; }
		if(STATE==9 && c=='i'){  STATE = 10 ; }
		if(STATE==10 && c=='d'){ STATE = 11 ; }
		if(STATE==11 && c=='='){ STATE = 12 ; }

		if(STATE==12 && (fscanf(file, "%f", &number) == 1)){
		   printf("Read float dimension width: %f\n", number);
		   dim.width = number;
		   number = -1 ;
		   STATE = 3;
		}

		if(STATE==3 && c=='>'){ STATE = 0;} // push dimension data into an from hear
		if(STATE==0 && c =='b'){ STATE = 15 ; }
		if(STATE == 15 && c =='o'){ STATE = 16; }

		if(STATE == 16 && c=='x'){
			if(100>boxesIndex+1){
              boxesIndex++;
			  boxes[boxesIndex].type = NORMAL ; 
		   }
		   STATE = 17;
		}
		
		if(STATE == 17 && c=='l'){ STATE = 18; }
		if(STATE == 18 && c =='e'){ STATE = 19; } 
        if(STATE == 19 && c == 'n'){ STATE = 20; }
		if(STATE == 20 && c == '='){ STATE = 21; }

		if(STATE==21 && (fscanf(file, "%f", &number) == 1)){
			printf("Read float length : %f\n", number);
		    boxes[boxesIndex].length= number;
		    number = -1 ;
			STATE = 17;
		}

		if(STATE == 17 && c=='w'){ STATE=23; }
		if(STATE == 23 && c =='i'){ STATE = 24;} 
        if(STATE == 24 && c == 'd'){ STATE = 25; }
		if(STATE == 25 && c == '='){ STATE = 26; }

		if(STATE==26 && (fscanf(file, "%f", &number) == 1)){
		    printf("Read float width: %f\n", number);
		    boxes[boxesIndex].width= number;
		    number = -1 ;
			STATE = 17;
		}

		if(STATE == 17 && c == 'c'){ STATE = 27; }
		if(STATE == 27 && c == 'o'){ STATE = 28; }
		if(STATE == 28 && c == 'l'){ STATE = 29; }
		if(STATE == 29 && c == '('){ STATE = 30; }
        
		if(STATE == 30 && (fscanf(file, "%f", &number) == 1)){
           printf("Read float colour R : %f\n", number);
		    boxes[boxesIndex].R = number;
		    number = -1 ;
			STATE = 31;
		}

		if(STATE==31 && c==','){STATE = 32; }

        if(STATE == 32 && (fscanf(file, "%f", &number) == 1)){
            printf("Read float colour G : %f\n", number);
		    boxes[boxesIndex].G = number;
		    number = -1 ;
			STATE = 33;
		}
       
        if(STATE==33 && c==','){STATE = 34; }
       
		if(STATE == 34 && (fscanf(file, "%f", &number) == 1)){
            printf("Read float colour B : %f\n", number);
		    boxes[boxesIndex].B = number;
		    number = -1 ;
			STATE = 35;
		}
        
		if(STATE==35 && c==')'){STATE = 36; }
        if(STATE == 17 && c=='p'){ STATE = 37; }
        if(STATE == 37 && c=='o'){ STATE = 38; }
		if(STATE == 38 && c=='s'){ STATE = 39; }
        if(STATE == 39 && c=='='){ STATE = 40; }
		if(STATE == 40 && c=='('){ STATE = 41; }
		
		if(STATE == 41 && (fscanf(file, "%f", &number) == 1)){
		   printf("Read float position X : %f\n", number);
		   boxes[boxesIndex].positionX = number;
		   number = -1 ;
		   STATE = 42 ;
		}

		if(STATE == 42 && c==','){ STATE = 43 ; }
		
		if(STATE == 43 && (fscanf(file, "%f", &number) == 1)){
           printf("Read float position y : %f\n", number);
		   boxes[boxesIndex].positionY = number;
		   number = -1 ;
		   STATE = 17 ;
		}
		
		if(STATE == 17 && c=='T'){ STATE = 47; }
		if(STATE == 47 && c=='y'){ STATE = 48; }
        if(STATE == 48 && c=='p'){ STATE = 49; }
		if(STATE == 49 && c=='='){ STATE = 50; }
		if(STATE == 50 && c=='b'){ STATE = 51; }
		if(STATE == 51 && c=='u'){ STATE = 52; }
        
		if(STATE == 52 && c=='t'){ 
		   boxes[boxesIndex].type = BUTTON ;
		   STATE = 17;
		}

		if(STATE == 50 && c=='i'){ STATE = 54; }
		if(STATE == 54 && c=='m'){ STATE = 55; }
		if(STATE == 55 && c=='a'){ STATE = 56; }
		if(STATE == 56 && c==':'){ STATE = 57; }
		
		if(STATE == 57 && c=='~'){
			char buffer [1024];
			int index = 0 ;
			while(((c = fgetc(file)) != '~')){
				buffer[index] = c ;
				index++;
			}
			
			boxes[boxesIndex].src = (char *)malloc(sizeof(char)*index);
			boxesLength = index;
			for(int i = 0 ; i < index ; i++ ){
				boxes[boxesIndex].src[i] = buffer[i];
			}
            boxes[boxesIndex].type = IMAGE ; 
		}
		
		if(c=='/'){ STATE = 58; }
		if(STATE == 58 && c=='>'){ STATE = 59; }
	
    }

	for(int i = 0 ; i < 10 ;i++ ){
		printf("dimension lenght :%d\n",dim.length);
		printf("dimension width :%d\n",dim.width);
		printf("length :%d\n",boxes[i].length);
		printf("width :%d\n",boxes[i].width);
		printf("type :%d\n",boxes[i].type);
		printf("R :%d\n",boxes[i].R);
		printf("G :%d\n",boxes[i].G);
		printf("B :%d\n",boxes[i].B);
	    printf("position X :%d\n",boxes[i].positionX);
		printf("position y :%d\n",boxes[i].positionY);
		printf("src :%s\n",boxes[i].src);
		printf("--------------\n");
	}
	
    fclose(file);
    return 0;
}

/*void main(){
	runFSM();
printf("main");
}*/
