#include "AnagramMaker.h"
#include <iostream>
#include <string>

using namespace std;

AnagramMaker::AnagramMaker(const string &dictionaryFile) //sets up the inital string dictionary, is only loaded once
{
	string line;
	ifstream file (dictionaryFile);
	while (file >> line)
	{
		dictionaryVector.push_back(line);
	}
}

 unsigned int AnagramMaker::findAnagrams(const string &input, const bool &print) const
{
	wordStruct inputStruct(input.length(), input);

	vector<string>::const_iterator it=dictionaryVector.begin();//itterator to first slot in the dictionary string vector
	vector<wordStruct> temp; //temp sctruct to hold words that are <= the input


	while(it!=dictionaryVector.end())
	{
		if (it->length() <= input.length()) //used to elimiate words in the dictionary that are larger then the input word
		{
			wordStruct tempWord(it->length(), *it);
			temp.push_back(tempWord); //makes a temp dictionary that has only words that are <= the input word.
		}
		++it;
	}
	
	return findAnagramHelper("", inputStruct, print, temp, temp.begin());//sends in the temp dictionary and pointer to the first slot, to prevent repeats, cause we are upping the pointer every recusion

}

 int AnagramMaker::findAnagramHelper(const string &soFar, const wordStruct &Istruct, const bool &print, const vector<wordStruct> &dictionary, const vector<wordStruct>::const_iterator &myIterator) const 
	 // a helper function since we need more parameters
{
	int count = 0;//number of anagrams found
	vector<wordStruct>::const_iterator it;
	it = myIterator;//iterator to the slot in the dictionary we are at
	wordStruct newStruct;
	
	while(it!=dictionary.end())//loops through the temp dictionary till end
	{
		if (subtraction(Istruct, *it))
		{
			
			for (int i=0;i<26;++i)
			{
				newStruct.alphabet[i] = Istruct.alphabet[i] - it->alphabet[i];//checks the alphabet count
				newStruct.count=Istruct.count - it->count;
			}

			if(newStruct.count==0)//if its 0 then its a anagram and it adds one to count and adds it to soFar to be printed.
			{
				++count;
				if(print){cout << soFar + it->word << endl;}

			}

			else {count += findAnagramHelper(soFar + " " + it->word + " ", newStruct, print, dictionary, it);} //else it recuses to next word, passing in our place in the dictionary
		}
		++it;
	}
	return count;// returns how many anagrams were found
}

bool AnagramMaker::subtraction(const wordStruct &Istruct, const wordStruct &it) const //used to subtract letters off a word to find anagrams
{
	for (int i=0; i < it.count; ++i) //loop through the input word
	{
		if (Istruct.alphabet[it.word[i] - 'a'] < it.alphabet[it.word[i] - 'a']) return false;
	}
	return true;
}