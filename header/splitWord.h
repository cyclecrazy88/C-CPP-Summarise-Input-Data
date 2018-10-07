
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

/**************************************************
	Class Defination for the wordItem.
		A word item represents a word which has been found.

	The class is a generic data processing class for the data sets.
**************************************************/

class WordItem{
	// Hold into to the word for the list item.
	char dataInput[WORDLENGTH];
	int maximumLnegth;
	public:
		WordItem(char *inputData);

		void setWord(char *inputData);

		// Copy the word data into a pointer. The calling function is responsible
		// for ensuring that memory has been allocated for this task
		void getWord(char *outputData);

		// Retern a reference to the word object item.
		char* getWord2();

		// Diagnositic function - print the word if it's available.
		void printWord();
	private:
		/*******************************************************
			Function - clearWordData.
				Seek to initialise and set the word data so the corresponding values
				set is equal to null.
			*****************************************************/
		void clearWordData();
}; 

/****************************************
	Once the word data has been created. Create a list manager to manage the
	input data set.
*****************************************/
class ManageList{
	WordItem *wordData;
	ManageList *childList;
	public:
		ManageList(WordItem *inputWordData);

		~ManageList();
		/*************************************
			Handler Function - addListItem
				Function is responsible for adding the item to the end
				 of the list.	
		**************************************/
		int addListItem(WordItem *wordData);

		/************************************
			Get a reference to the current word data object (reference)
			to the corresponding item.
		*************************************/
		WordItem* getWordDataObject();
		/************************************
			Get a reference to the corresponding managed list object.
		*************************************/
		ManageList* getManagedListObject();

		/*************************************
			Set a reference to the next managed list object in sequence.
		*************************************/
		void setNextManagedListObject(ManageList *nextWord);
};




/***************************************************
	Class - ParseInputString
		Split and digest the items into smaller, more compressed/compact objects.
***************************************************/
class ParseInputString{
	public:
		// Constructor for Parse Input String.
		ManageList *listManager;
		
		// Parse an additional string (extra input data).
		ParseInputString(char *inputData);

		// Destructor for the class
		~ParseInputString();
		/************************************
			Function getListStart.
				Handler to request the start of the list (the beginning section). 
		*************************************/
		ManageList* getListStart();

		/******************************
			Allow an additional line to be passed in. This is extra data
			which equals a 'line' of data to be processed.
		*******************************/	
		void passInAdditionalLine(char *inputData);

	private:
		/*********************************************
		 	Function: splitString.
				Loop around all the characters which are present in the string
			*********************************************/
		void splitString(char* inputString);
		/*********************************************
			Function: Initialise the word data so it's values have a default
								value of null.
			Clear the word data - Set everything to be 'null'.
		**********************************************/
		void initialiseWordData(char *inputData);
		/****************************************
			Function - addWordItemDataToList.	
				This is a utility function to pass the word data into
				a managed linked list.
		*****************************************/
		void addWordItemDataToList(char *wordData);
};


