#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
typedef struct{
	char* word;
	char* clue;
	int x;
	int y;
	char direction;
	int f;
} Word_t;


Word_t* loadTextFile(FILE* myFile,int nrWords);
void displayBoard(int rows,int cols,char** myBoard);
int isBoardFilled(int rows,int cols,char** myBoard);
char** createArray(int rows,int cols);
int findIndex(int arr[],int size,int val);
void playGame(char** myBoard,int words,Word_t* words2,int x,int y,int countToFinish);
char** updateBoard(char** myBoard,Word_t *words,int solve);

int main (){
	
	FILE *fp;
	int row,col,word;
	char file[50];
	printf("Please enter the file name: ");
	scanf("%s",&file);
	fp = fopen(file,"r");
	fscanf(fp,"%d %d %d\n",&row,&col,&word);
	Word_t* arr = loadTextFile(fp,word);

	char** matrix = createArray(row,col);
	int i,j;

	playGame(matrix,word,arr,row,col,word);
	displayBoard(row,col,matrix);
	printf("\n\nCongratulations! You beat the puzzle!\n");
	
}

Word_t* loadTextFile(FILE* myFile,int nrWords){

	char dir;
	int row_,col_;
	char first[15],sec[150];


	Word_t* array = ( Word_t*)malloc(sizeof(Word_t)*(nrWords+2));
	int i = 2;

	while (fscanf(myFile,"%c %d %d %s",&dir,&row_,&col_,&first) == 4 ){
		fgets(sec,150,myFile);
		
	
		array[i].clue = (char*)malloc(sizeof(char)*150);
		strcpy(array[i].clue,sec);
		array[i].direction = dir;
		array[i].word = (char*)malloc(sizeof(char)*15);
		strcpy(array[i].word,first);
		array[i].x = row_;
		array[i].y = col_;
		array[i].f = 0;
		i++;
	
		
	}
	return array;

}

char** createArray(int rows,int cols){
	char** myarray;
	int i,j;
	*myarray = (char*)malloc(sizeof(char*)*rows);
	for(i=0;i<rows;i++){
		myarray[i] = (char*)malloc(sizeof(char)*cols);
	}
	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
			myarray[i][j] = '#';
		}
	}
	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){

		}
		printf("\n");
	}

	return myarray;
}



void displayBoard(int rows,int cols,char** myBoard){
	int i,j;
	printf("\t  ");
	for(i=0;i<cols;i++){
		printf("%d  ",i+1);
	}
	printf("\n");
	printf("\t  ");
	for(i=0;i<cols;i++){
		printf("-- ");
	}
	printf("\n");



	for(i=0;i<rows;i++){
		printf("%d\t| ",i+1);
		for(j=0;j<cols;j++){
			printf("%c  ",myBoard[i][j]);
		}
		printf("\n");
	}
	printf("\t");
	for(i=0;i<cols;i++){
		printf("***");
	}


}
int isBoardFilled(int rows,int cols,char** myBoard){
	int i,j;
	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
			if(myBoard[i][j] == '_'){
				return 0;
			}
		}
	}
	return 1;
}

int findIndex(int arr[], int size, int val){
	return 0;
}

void playGame(char** myBoard,int words,Word_t* words2,int x,int y,int countToFinish){
	int i,j;
	int rw=0,cl=0,size,size2;
	
	for(i=2;i<words+2;i++){
		rw = words2[i].x -1;		
		cl = words2[i].y -1;
		size = 0;		
		size2 = strlen(words2[i].word);
		
		while(size < size2){
		
			myBoard[rw][cl] = '_';
			
			if(words2[i].direction == 'H'){
				cl++;
			}
			else{
				rw++;
			}
 			size++;
		}
	}
	printf("Game is %d rows x %d cols with %d words\n",x,y,words);
	printf("Words and clues are read!\n");
	int k = 0;
	int m;
	int t=0;
	int which;
	char theword[15];
	while(countToFinish > k){
		printf("Current puzzle:\n\n");
		displayBoard(x,y,myBoard);
		printf("\n\nAsk for hint:\n");
		printf("# Direction\trow  col\n");
		printf("---------------------------\n");
		for(m=2;m<words+2;m++){
			if(words2[m].direction == 'H' && words2[m].f != 1){
				printf("%d: %s\t%d\t%d\n",m-1,"Horizontal",words2[m].x,words2[m].y);		
			}
			else if(words2[m].direction == 'V' && words2[m].f != 1){
				printf("%d: %s\t%d\t%d\n",m-1,"Vertical",words2[m].x,words2[m].y);
			}
	
		}
		printf("\nEnter -1 to exit\n");
		while(1){
			printf("Which word to solve next?:");
			scanf("%d",&which);	
			if(which == -1){
				return ;
			}
			if(words2[which+1].f  == 1){
				printf("The word has been solved before\n");
			}
			else{
				break;
			}
		}

		printf("Current hint:%s",words2[which+1].clue);
		printf("Enter your solution:");
		scanf("%s",&theword);
		t = 0;
		for(t=0;t<strlen(theword);t++){
			theword[t] = toupper(theword[t]);
		}
		
		int xx,yy;

		if(strcmp(theword,words2[which+1].word) == 0){
			
			if(words2[which+1].f  == 0){
				words2[which+1].f = 1;
				printf("\nCorrect!\n\n");
				xx = words2[which+1].x-1;
				yy = words2[which+1].y-1;
				for(t =0;t<strlen(words2[which+1].word);t++){
					
					myBoard[xx][yy] = words2[which+1].word[t];
					if(words2[which+1].direction == 'V'){
						xx++;
					}
					else{
						if("dsa");
						yy++;
					}
				}
				k++;
			}
			else{
				
			}

		}
		else{
			printf("WRONG ANSWER\n");
		}
		
	}
	
}

