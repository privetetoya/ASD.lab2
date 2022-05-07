#pragma once

#include <iostream>
#include <stdexcept>
#include "List.h"
#include "Map.h"
using namespace std;
class ShannonFano {
private:
	char* arrayOfChars; // Array for different text characters storage
	int* counter; // Array for text characters count storage
	string* code; // Aarray for text characters codes storage
	string sourceText;
	int size; // number of different chars

	// BubbleSort algorithm for arrays sorting in descending order
	void BubbleSort() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size - 1; j++) {
				if (counter[j] < counter[j + 1]) {
					int temporaryCounter = counter[j];
					char temporaryStorage = arrayOfChars[j];
					counter[j] = counter[j + 1];
					arrayOfChars[j] = arrayOfChars[j + 1];
					counter[j + 1] = temporaryCounter;
					arrayOfChars[j + 1] = temporaryStorage;
				}
			}
		}
	}

	int getIndex(char letter) {
		for (int i = 0; i < size; i++) {
			if (arrayOfChars[i] == letter) {
				return i;
			}
		}
	}

	int getIndex(string substring) {
		for (int i = 0; i < size; i++) {
			if (code[i] == substring) {
				return i;
			}
		}
	}

									//Return minimum of values
	int minimalValue(int first, int second) {
		if (first > second) {
			return second;
		}
		if (second > first) {
			return first;
		}
	}

	// Check that substring is a code of some char
	bool contains(string substring) {
		for (int i = 0; i < size; i++) {
			if (code[i] == substring) 
				return true;
		}
		return false;
	}

public:
	// ShannonFano class constructor
	ShannonFano(Map<char, int>& map, const int eCounter, string text) {
		arrayOfChars = new char[eCounter];
		counter = new int[eCounter];
		code = new string[eCounter];
		size = eCounter;
		sourceText = text;

		List<char> key = map.getKeys();
		List<int> value = map.getValues();

		for (int i = 0; i < size; i++)
		{
			arrayOfChars[i] = key.getHead();
			counter[i] = value.getHead();
			code[i] = "";
			key.setNext();
			value.setNext();
		}

		BubbleSort();

	}

	// ShannonFano encode algorithm
	void ShannonFanoEncodeHelper(int begin, int end) {
		if (begin == end)
			return;
		int left = begin, right = end;
		int leftSumCounter = 0, rightSumCounter = 0;
		while (left <= right) {
			if (leftSumCounter <= rightSumCounter) {
				leftSumCounter += counter[left];
				left++;
			}
			else {
				rightSumCounter += counter[right];
				right--;
			}
		}
											//Insert '0' to the end of left-subarray chars
		for (int i = begin; i < left; i++) {
			code[i] += "0";
		}
											//Insert '1' to the end of right-subarray chars
		for (int i = left; i <= end; i++) {
			code[i] += "1";
		}
		ShannonFanoEncodeHelper(begin, left - 1);
		ShannonFanoEncodeHelper(left, end);
	}

	void printCounter() {
		for (int i = 0; i < size; i++)
		{
			cout << arrayOfChars[i] << " : " << counter[i] << '\n';
		}
	}

	// Print  code table on the screen
	void printCode() {
		for (int i = 0; i < size; i++)
		{
			cout << arrayOfChars[i] << " : " << code[i] << '\n';
		}
	}

	// Calculate original text size
	int sizeOfOriginalText() {
		int sum = 0;
		for (int i = 0; i < size; i++)
		{
			sum += 8 * counter[i];
		}
		return sum;
	}

	// Calculate encoded text size
	int sizeOfEncodedText() {
		int sum = 0;
		for (int i = 0; i < size; i++)
		{
			sum += code[i].size() * counter[i];
		}
		return sum;
	}
	string encodedText() {
		string encodedText = "";
		for (int i = 0; i < sourceText.size(); i++) {
			encodedText += code[getIndex(sourceText.at(i))];
		}
		return encodedText;
	}

	string decodedText() {
		string decodedText = "";
		string textToDecode = encodedText();
		int maxLength = 0;
		for (int i = 0; i < size; i++) {
			if (code[i].size() > maxLength) { 
				maxLength = code[i].size(); 
			}
		}
		while (textToDecode.size() > 0) {
			for (int i = 0; i <= minimalValue(maxLength, textToDecode.size()); i++) {
				string substring = textToDecode.substr(0, i);
				if (contains(substring)) {
					decodedText += arrayOfChars[getIndex(substring)];
					textToDecode.erase(0, i);
					break;
				}
			}
		}
		return decodedText;
	}

	// ShannonFano class Destructor
	~ShannonFano() {
		delete[] arrayOfChars;
		delete[] counter;
		delete[] code;
	}
};