#ifndef AnagramMaker_H
#define AnagramMaker_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>


using namespace std;

class AnagramMaker {
public:
   AnagramMaker(const std::string &dictionaryFile);
   unsigned int findAnagrams(const std::string &input, const bool &print) const;

   

private:

	struct wordStruct
	{
		wordStruct(int c, string w)
		{
			count = c;
			word = w;

			for (int i=0; i<26; i++)
			{
				alphabet[i]=0;
			}
			for (int i = count-1; i > -1; i--)
			{
				alphabet[ w[i] - 'a'] ++;
			}
		}
	
	
	wordStruct(){}
	int count;
	char alphabet[26];
	string word;
};

	vector<string> dictionaryVector;
	bool subtraction(const wordStruct &Istruct, const wordStruct &it) const;
	int findAnagramHelper(const string &soFar, const wordStruct &Istruct, const bool &print, const vector<wordStruct> &dictionary, const vector<wordStruct>::const_iterator &myIterator) const;


};

#endif