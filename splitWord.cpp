#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <ctype.h>
#include "./header/splitWord.h"

using namespace std; 

/*************************************************
	Section Start - WordItem

 Constuctor for the class
*************************************************/
WordItem::WordItem(char *inputData){
	this->clearWordData();
	//cout << "Initialise Word: "<< inputData <<"\n";
	if (strlen(inputData) < WORDLENGTH ){	
		//cout << "Constructor. Word can be added - "<<inputData<<"\n";
		strcpy(this->dataInput,inputData);
		//cout << "SetWord: " << this->dataInput<<"\n";
	}
}
/*************************************************
	Function - setWord. Set a word value for the item.
*************************************************/
void WordItem::setWord(char *inputData){
	this->clearWordData();
	if (strlen(inputData) < WORDLENGTH ){	
	//cout << "WordItem -> setWord. Word can be added - "<<inputData<<"\n";
		strcpy(this->dataInput,inputData);
	}
}

/*************************************************
	Function - getWord.
		Copy a reference to the word into a memory location.
*************************************************/
void WordItem::getWord(char *outputData){
	strcpy(outputData,this->dataInput);
}

/*************************************************
	Function - getWord2.
		Return a reference to the word.
*************************************************/
char* WordItem::getWord2(){
	return this->dataInput;
}


/*************************************************
	Function - getWord2.
		Analysis Function - Output the word to the console.
*************************************************/
void WordItem::printWord(){
	//cout << "WordItem -> printWord -> Current Word: "<<this->dataInput<<"\n";
}

/*************************************************
	Function - clearWordData.
		Data management function. - Initialise the word item
		(Ensure the data set is nice and cleanly organised) - Zeroed array.
*************************************************/
void WordItem::clearWordData(){
	// Initialise the pointer to the start of the array item.
	char *characterData = &(this->dataInput[0]);
	int dataLength = strlen(this->dataInput);
	// Loop around the for loop, Ensure all the entries have a value of
	// null to suggest not set.
	for (int count = 0 ; count < dataLength ; count++){
		// Set the value of the pointer variable at this position to null.
		characterData[0] = '\0';
		characterData++;
	}
}

/*************************************************
	Section Start - ManageList

 Constuctor for the class
*************************************************/
ManageList::ManageList(WordItem *inputWordData){
	wordData = inputWordData;
	// Initialise the child list as this hasn't been set yet.
	this->childList = NULL;
	//cout << "ManageList -> Manage the word data list\n";
}
/*************************************************
	Destrutor for the class.
*************************************************/
ManageList::~ManageList(){
	//cout << "Delete the the list item data.\n";
	// Check to see if there is a word and a child. Cause these
	// destructions to be initialised as well.
  if (this->wordData != NULL)
		delete this->wordData;
	if (this->childList != NULL)
		delete this->childList;
}
/*************************************
	Handler Function - addListItem
	Function is responsible for adding the item to the end
		 of the list.	
**************************************/
int ManageList::addListItem(WordItem *wordData){
			// Flag to indicate if the item was set or not.
			bool itemIsSet = false;

			// Check to see if there is anything on the front of the 
			// list first.
			if (this->childList == NULL){
				//cout << "addListItem -> Start List -> Add list item\n";		
				ManageList *nextWord = new ManageList(wordData);
				this->childList = nextWord;
				this->childList->getWordDataObject()->printWord();
			}
			else{
				ManageList *nextChild = this->childList;

				ManageList *childListTemp = this->childList->getManagedListObject();
				ManageList *lastInSearch = NULL;

				//cout << "\n\nWord Data Input "<<(*wordData).getWord2()<<"\n";
				//cout << "Next Child: "<<nextChild << "\n";
				//cout << "Parent Child: "<<childListTemp << "\n";

				ManageList *nextWord = new ManageList(wordData);
				// See if this is the just the beginning of the list item.
				if (childListTemp == NULL){
					//cout << "\tSet next child value\n";
					// Add the next child in the sequence.
					(*nextChild).setNextManagedListObject(nextWord);	
					itemIsSet = true; // Flag item set	
				}
				else{
					while (childListTemp != NULL){
						if (childListTemp != NULL){
							// Hold onto the last value found in the sequence.
							lastInSearch = childListTemp;
							//cout << "Current Value in sequence: "<<	
							//				(*childListTemp).getWordDataObject()->getWord2()<<"\n";
						}

						childListTemp = childListTemp->getManagedListObject();
					}
					//cout << "Last Item In Search: "<<lastInSearch<<"\n";
					(*lastInSearch).setNextManagedListObject(nextWord);	
					itemIsSet = true; // Flag item set
				}
				// Flag if item is set or not.
				if (!itemIsSet){
					cout << "Unable to set item";	
					delete nextWord;		
					// Return -1 to indicate an error
					return -1;
				}
			}
			// Return 0 to indicate the update was successful.
			return 0;

		}

/************************************
	Get a reference to the current word data object (reference)
	to the corresponding item.
*************************************/
WordItem* ManageList::getWordDataObject(){
	return this->wordData;
}

/************************************
	Get a reference to the corresponding managed list object.
*************************************/
ManageList* ManageList::getManagedListObject(){
	return this->childList;		
}


/*************************************
	Set a reference to the next managed list object in sequence.
*************************************/
void ManageList::setNextManagedListObject(ManageList *nextWord){
	//cout << "Set Next Word: "<< 
	//						nextWord->getWordDataObject()->getWord2() << "\n";
	// Set the reference to the next child in the sequence.
	if (this->childList == NULL)
		this->childList = nextWord;
	else{
		cout << "\nCan't override child\n";
	}
}
/*************************************************
	Section Start - ParseInputString

 Constuctor for the class
*************************************************/
ParseInputString::ParseInputString(char *inputData){
	cout << "InputData: "<<inputData<<"\n";
	this->listManager = NULL;
	this->splitString(inputData);
}
/*************************************************
 Destructor for the class
*************************************************/
ParseInputString::~ParseInputString(){
	//cout << "Destruct Object\n";
	delete listManager;
}
/*************************************************
 Parse an additional string (extra input data).
*************************************************/
ManageList* ParseInputString::getListStart(){
	return this->listManager;	
}

/***************************************************
 Allow an additional line to be passed in. This is extra data
 which equals a 'line' of data to be processed.
***************************************************/	
void ParseInputString::passInAdditionalLine(char *inputData){
	this->splitString(inputData);
}

/***************************************************
 Function: splitString.
	Loop around all the characters which are present in the string
****************************************************/
void ParseInputString::splitString(char* inputString){
			// Initialise the character sets for the individual works.
			char wordData [WORDLENGTH];
			this->initialiseWordData(&wordData[0]);
			char *currentWordPointer = &wordData[0];

			if (inputString != NULL){
				int stringLength = strlen(inputString);
				//cout << "Data Length: "<< stringLength << "\n";

				char *stringPointer = &(inputString[0]);
				for (int count = 0 ; count < stringLength ; count++){
					char currentCharacter = stringPointer[0];
					int characterNumber = stringPointer[0];
					// Check to see if this looks like a character (isAlpha).
					// something that can be selected/filtered.
					if (isalpha(currentCharacter) ){
						//cout << "Character Found: "<< currentCharacter<<"\n";
						currentWordPointer[0] = currentCharacter;
						currentWordPointer++;
					}
					else{
						this->addWordItemDataToList(wordData);

						// Clear the word data.
						this->initialiseWordData(&wordData[0]);
						currentWordPointer = &wordData[0];
					}
					stringPointer++;
				}
				//cout << "End of string - "<< wordData << "\n";
				// Add anything left to the list.
				this->addWordItemDataToList(wordData);

			}
		}
/*********************************************
	Function: Initialise the word data so it's values have a default
						value of null.
	Clear the word data - Set everything to be 'null'.
**********************************************/
void ParseInputString::initialiseWordData(char *inputData){
	for (int count = 0 ; count < WORDLENGTH ; count++){
		inputData[0] = '\0';
		inputData++;
	}
}
/****************************************************
 Function - addWordItemDataToList.	
	This is a utility function to pass the word data into
		a managed linked list.
****************************************************/
void ParseInputString::addWordItemDataToList(char *wordData){
	if (strlen(wordData) > 0 ){
		WordItem *wordItemData = new WordItem(wordData);
		// Create a new object to manage the list data.
		if (this->listManager == NULL){
			this->listManager = new ManageList(wordItemData);
		}
		else{
			// Add a new item onto the list.
			this->listManager->addListItem(wordItemData); 
		}			
	}						
}

/*************************************
	Input String Handler - Handler for the input data.
	
	- Input/output handler functions for the request activity/data processing.

	- The corresponding functions are designed to allow 'portability' from a C
		program doing the data processing.
**************************************/
ParseInputString *parseInputData = NULL;
ManageList *listManager = NULL;

void passInitialData(char *inputData){
	if (strlen(inputData)>0){
		// Check to see if the data set has been initialised yet.
		if (parseInputData == NULL){
			//cout << "\nInitialise Input Data - passInitialData\n";
			// Initialise the parse of the string data
			parseInputData = new ParseInputString(&inputData[0]);	
		}
		else{
			//cout << "\nContinue to process Input Data - passInitialData\n";
			parseInputData->passInAdditionalLine(&inputData[0]);
		}

		
	
		// Setup the beginning of the list.
		listManager = parseInputData->getListStart();
	}
}
/****************************
	Function getNextWord.
		If the list message is available get the next item in the sequence.
*****************************/
WordType getNextWord(){
	//cout << "Get Next Word.\n";
	WordType word;
	word.wordLength = 0;
	word.itemFound = false;

	// Check to see if there is a data item/value to return.
	if (listManager != NULL){
		WordItem *wordData = (*listManager).getWordDataObject();
		if (wordData != NULL){
			// Fetch the word, pass the first location as a reference
			// to copy into.
			wordData->getWord( &(word.word[0]) );
			word.wordLength = strlen(word.word);

			// Check to see if the data has some length to work with.
			if (word.wordLength > 0){
				word.itemFound = true;
			}
		}
		// -------------------------------------------------------
		// Move the pointer down to the next position in the list.
		// -------------------------------------------------------
		if ((*listManager).getManagedListObject() != NULL)
			listManager = (*listManager).getManagedListObject();
		else
			listManager = NULL;
	}

	return word;
}

/********************************
	Function - clearDownDataSet.
		Unload the contents of the dataset (this is to trigger the 
		destructors for the functions and listing handlers.
********************************/
int clearDownDataSet(){
	if (parseInputData != NULL){
		delete parseInputData;
		return 0;
	}
	else{	
		return -1;
	}
}

