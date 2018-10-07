#include <stdio.h>
#include "./header/splitWord.h"
#include "./header/summeriseData.h"

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
	summeriseDataStart();
	WordType wordMessage = getNextWord();
	while (wordMessage.itemFound){
		//printf ("WordData: %s %d\n", wordMessage.word , wordMessage.wordLength );
		addNextItemToGrouping(wordMessage.word);
		wordMessage = getNextWord();
		break;
	}
	endDataSetSummary();



}

int main(int arg , char**){
	readDataFromFile();
	return 0;
}

