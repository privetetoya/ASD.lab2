#pragma once
#include <iostream>
#include "List.h"
#include "Map.h"
#include "ShannonFano.h"
using namespace std;

int main()
{
	Map<char, int> map;
	char letter;
	int excounter = 0;
	string text = "";

	cout << "Enter text:\n";

	while (cin.get(letter)) {
		if (letter == '\n') {
			break;
		}
		if (map.contains(letter)) {
			map.find(letter)->value++;
		}
		else {
			map.insert(letter, 1);
			excounter++;
		}
		text += letter;
	}

	ShannonFano ShannonFanoMap(map, excounter, text);
	cout << "\nCounter table\n";
	ShannonFanoMap.printCounter();
	ShannonFanoMap.ShannonFanoEncodeHelper(0, excounter - 1);
	cout << "\nCode table\n";
	ShannonFanoMap.printCode();
	cout << "Compression ratio: " << (ShannonFanoMap.sizeOfOriginalText() / 1.0f) / (ShannonFanoMap.sizeOfEncodedText() / 1.0f) << "\n";
	cout << "Encoded text:\n";
	cout << ShannonFanoMap.encodedText();
	cout << "\n\nDecoded text:\n";
	cout<< ShannonFanoMap.decodedText();

}