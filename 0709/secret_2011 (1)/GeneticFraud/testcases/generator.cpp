#include <iostream>
#include <cstdlib>

using namespace std;

#define MAX_M 1000000
char output[MAX_M+1];

int main( int argc, char ** args ){
	if( argc == 1 ){
		cout << "Usage: " << args[0] << endl
			 << "\t-n number of testcases" << endl
			 << "\t-m maximal length of string" << endl
			 << "\t-s number of modifications" << endl;
		return 0;
	}

	int c;
	int cases, max_length, max_mod;
	while( ( c = getopt(argc, args, "n:m:s:") ) != -1 ){
		switch( c ){
			case 'n': cases = atoi( optarg ); break;
			case 'm': max_length = atoi( optarg ); break;
			case 's': max_mod = atoi(optarg); break;
		}
	}

	cout << cases << "\n";
	for( int c = 0; c < cases; ++c ){
		int cur = rand() % (max_length - 1) + 1;
		cout << cur << "\n";
		for( int i = 0; i < cur; ++i )
			output[i] = (rand() % 26) + 'a';
		output[cur] = '\0';
		cout << output << '\n';
		int diff = rand() % max_mod;
		for( int i = 0; i < diff; ++i ){
			int pos = rand() % cur;
			output[pos] = 'a' + (((output[pos] - 'a') + 1) % 26);
		}
		output[cur] = '\0';
		cout << output << '\n';
	}
	return 0;
}
