#include <stdio.h>
#include "./header/splitWord.h"

void runResultSearch();

void readDataFromFile(){

	FILE *filePointer = fopen("./testData/inputData.txt","r");
	char inputBuffer[WORDLENGTH];
	while (fgets(inputBuffer , WORDLENGTH, filePointer)){
		printf("Input: %s",inputBuffer );
		passInitialData(inputBuffer);
	}


	fclose(filePointer);

	runResultSearch();

	clearDownDataSet();
}

void runResultSearch(){
	WordType wordMessage = getNextWord();
	while (wordMessage.itemFound){
		printf ("WordData: %s %d\n", wordMessage.word , wordMessage.wordLength );
		wordMessage = getNextWord();
	}



}

int main(int arg , char**){
	readDataFromFile();
	return 0;
}

