
#define SPACECHAR ' '
#define WORDLENGTH 1024

/***************
	Input/Output Structure Type
****************/
typedef struct{
	char word[WORDLENGTH];
	int  wordLength;
	bool itemFound;
} WordType;


// Interface functions permitted for usage.
void passInitialData(char *inputData);
int clearDownDataSet();


// Request the next word - (If available.
WordType getNextWord();
