/*
 * StringParserClass.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: Elijah Weske
 */

#include <string>
#include <string.h>
#include "../327_proj3_test/includes/StringParserClass.h"
#include "../327_proj3_test/includes/constants.h"

using namespace std;
using namespace KP_StringParserClass;

// initialize member variables
StringParserClass::StringParserClass(void) {
	pStartTag = NULL;
	pEndTag = NULL;
	areTagsSet = false;
}

// call cleanup to release memory
StringParserClass::~StringParserClass(void) {
	cleanup();
}

// these are the start tag and the end tags that we want to find,
// presumably the data of interest is between them, please make a
// COPY of what pStartTag and pEndTag point to. In other words
// DO NOT SET pStartTag = pStart
// returns:
// SUCCESS
// ERROR_TAGS_NULL if either pStart or pEnd is null
int StringParserClass::setTags(const char *pStart, const char *pEnd) {
	int startLen;
	int endLen;

	if (pStart == NULL || pEnd == NULL) {
		return ERROR_TAGS_NULL;
	}

	startLen = (strlen(pStart) + 1);
	endLen = (strlen(pStart) + 1);

	pStartTag = new char[startLen];
	pEndTag = new char[endLen];
	areTagsSet = true;

	strcpy(pStartTag, pStart);
	strcpy(pEndTag, pEnd);

	return SUCCESS;
}

//First clears myVector
//going to search thru pDataToSearchThru, looking for info bracketed by
//pStartTag and pEndTag, will add that info only to myVector
//returns:
//SUCCESS  finished searching for data between tags, results in myVector (0 or more entries)
//ERROR_TAGS_NULL if either pStart or pEnd is null
//ERROR_DATA_NULL pDataToSearchThru is null
int StringParserClass::getDataBetweenTags(char *pDataToSearchThru, std::vector<std::string> &myVector) {
	int dataSize;
	int startSize;
	int loopTracker;
	char *tempStart;
	char *tempEnd;
	string tagData;

	myVector.clear();

	if (pStart == NULL|| pEnd == NULL){
		return ERROR_TAGS_NULL;
	}

	if (pDataToSearchThru == NULL){
		return ERROR_DATA_NULL;
	}

	dataSize = strlen(pDataToSearchThru);
	dataHolder = pDataToSearchThru;
	startSize = strlen(pStartTag);
	*tempStart = pStartTag;
	*tempEnd = pEndTag;

	dataHolder = dataHolder + dataSize;
	loopTracker = findTag(pStartTag, dataHolder, tempEnd);

	while (loopTracker == SUCCESS){
		tagData = "";
			while (dataHolder != tempEnd){
				tagData = tagData + dataHolder;
				dataHolder++;
			}
			loopTracker = findTag(pStartTag, dataHolder, tempEnd);

			myVector.push_back(tagData);
			dataHolder = dataHolder + dataSize;
	}
	pDataToSearchThru = dataHolder;
	return SUCCESS;
}

//private:
void StringParserClass::cleanup() {
	if (pStartTag) {
		delete[] pStartTag;
	}
	if (pEndTag) {
		delete[] pEndTag;
	}
}

//private:
//Searches a string starting at pStart for pTagToLookFor
//returns:
//SUCCESS  found pTagToLookFor, pStart points to beginning of tag and pEnd points to end of tag
//FAIL did not find pTagToLookFor and pEnd points to 0
//ERROR_TAGS_NULL if either pStart or pEnd is null
int StringParserClass::findTag(char *pTagToLookFor, char *&pStart,char *&pEnd) {
	int startLen;
	int endLen;

	if (pStart == NULL || pEnd == NULL){
		return ERROR_TAGS_NULL;
	}

	//Not using these...
	startLen = strlen(pStart) + 1;
	endLen = strlen(pEnd) + 1;

	while (pStart != pEnd){
		if (*pStart == *pTagToLookFor){
			if (strncmp(pStart, pTagToLookFor, strlen(pTagToLookFor)) == SUCCESS){
				pEnd = pStart + strlen(pTagToLookFor);
				return SUCCESS;
			}
		}
		pStart++;
	}
	return FAIL;
}


