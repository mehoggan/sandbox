#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;

class output {
	public:
		output( ostream& out ) : os( out ) {}
		void operator() ( pair<string,string> in ) { 
			os	<< in.first << " - " << in.second << endl;
		}
	private:
		ostream& os;
};

int main( int argc, char** argv ) {
	cout 	<< "Anagram finding program:\n"
		<< "find all words in a dictionary that can\n"
		<< "be formed with the letters of a given word"
		<< endl;
	cout 	<< "First enter the name of the file containing\n"
		<< "the dictionary: " << flush;

	string dictionary_name;
	cin 	>> dictionary_name;
	map<string,string> dictionary;
	ifstream ifs( dictionary_name.c_str(),ios_base::in );

	if( !ifs.is_open( ) ) {
		cout	<< "Eh? Could not open file named: "
			<< dictionary_name << endl;
		exit( 1 );
	} else {
		dictionary.clear( );
		string input_line;
		while( getline( ifs, input_line, '\n' ) ) {
			string word;
			string def;
			string::iterator it = input_line.begin( );
			int index = 0;
			while( *(it) != ' ' && it != input_line.end( ) )  {
				word += *(it++);
				index++;
			}
			if( *(it) == '\n' ) {
				def = "";
			} else {
				string tmp( it, input_line.end( ) );
				def = tmp;
			}
			dictionary[word]=def;
		}
	}
	//for_each( dictionary.begin( ), dictionary.end( ), output( cout )  );
	cout 	<< "The dictionary contains "
		<< dictionary.size( ) << " words" << endl << endl;

	cout 	<< "Now type a word (or any combination of letters)\n"
		<< "and I'll see if it has an anagrams: " << flush;
	for( istream_iterator<string> i( cin ); i != istream_iterator<string>( ); ++i ) {
		string word = *(i);
		sort( word.begin( ), word.end( ) );
		bool found_one = false;
		do {
			map<string,string>::iterator it = dictionary.find( word );
			if( it != dictionary.end( ) && (*it).first == word ) {
				found_one = true;
				cout 	<< " " << (*it).first << (*it).second << endl;
			}
		} while( next_permutation( word.begin( ), word.end( ) ) );
		if( !found_one ) {
			cout << "Sorry, none found : " << endl;
		}
		cout << "Type another word (or the end-of-file char to stop): " << flush;
	}
}
