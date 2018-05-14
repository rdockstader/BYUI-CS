#include <iostream>
#include <string>

using namespace std;

struct Scripture {
	string book;
	int chapter;
	int verse;
};

void displayScripture(Scripture scrip){
	cout << scrip.book << " " << scrip.chapter << ":" << scrip.verse << endl;
}

Scripture promptScripture() {
	Scripture s;
	cout << "Book: ";
	getline(cin, s.book);
	cout << "Chapter: ";
	cin >> s.chapter;
	cout << "Verse: ";
	cin >> s.verse;
	cin.ignore();

	return s;
}


int main() {
	
	Scripture s[3];

	for (int i = 0; i < 3; i++)
	{
		cin.clear();
		s[i] = promptScripture();
	}

	for (int i = 0; i < 3; i++)
	{
		displayScripture(s[i]);
	}


	char dummy;
	cin >> dummy;
	return 0;
}