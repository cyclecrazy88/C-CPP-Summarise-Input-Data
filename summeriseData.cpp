#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <ctype.h>
#include "./header/splitWord.h"
#include "./header/summeriseData.h"

using namespace std; 

class DataSetGrouping{
	public:
	DataSetGrouping(){
		cout << "Initialise Data Set\n";
	}

	void addDataSetItem(char *inputData){
		cout << "Input Word: "<<inputData<<"\n";
	}	

	private:
	


};

DataSetGrouping *dataItems;

/*************************
	SummeriseData Set - Input function.
		Input handler - Allow the dataset (input) to be summerised.
**************************/
void summeriseDataStart(){
	dataItems = new DataSetGrouping();
}

/******************************
	Input Function: addNextItemToGrouping
		Allow the next item to be added to the grouping for the
		data items.
******************************/
void addNextItemToGrouping(char *inputData){
	(*dataItems).addDataSetItem(inputData);
}

/*************************
	Once the data set has been summerised, provide confirmation of this
	and seek to 'end', well tidy up any left over objects afterwards.
*************************/
void endDataSetSummary(){
	delete dataItems;
}

