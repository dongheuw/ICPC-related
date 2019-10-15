#include <iostream>
#include <cstring>
#include <limits>
#include <algorithm>

#define MAX_TRACKS 10

#define MAX_DURATION 30
#define MAX_TRAVEL 30

using namespace std;

struct track{
        int duration;
        int begin_begin;
        int begin_end;
        int end_begin;
        int end_end;
};

track tracks[MAX_TRACKS+1];
int cost[2], num_tracks, travel_time[4][MAX_TRACKS+1];

bool checkTrack(){
	if( travel_time[0][num_tracks] + tracks[num_tracks].begin_end == travel_time[1][num_tracks] + tracks[num_tracks].end_end )	//not unique
		return false;
	if( travel_time[0][num_tracks] + tracks[num_tracks].begin_begin == travel_time[1][num_tracks] + tracks[num_tracks].end_begin )	//not unique
		return false;

	if( travel_time[2][num_tracks] + tracks[num_tracks].begin_end == travel_time[3][num_tracks] + tracks[num_tracks].end_end )	//not unique
		return false;
	if( travel_time[2][num_tracks] + tracks[num_tracks].begin_begin == travel_time[3][num_tracks] + tracks[num_tracks].end_begin )	//not unique
		return false;

	if( std::min( travel_time[0][num_tracks] + tracks[num_tracks].begin_begin,travel_time[1][num_tracks] + tracks[num_tracks].end_begin ) ==
		std::min(travel_time[2][num_tracks] + tracks[num_tracks].begin_end, travel_time[3][num_tracks] + tracks[num_tracks].end_end) )
		return false;	//minimal path backwards not unique

	return true;
}

void generate( int length ){
	tracks[0].duration = (rand() % MAX_DURATION) + 1;
	travel_time[0][0] = std::numeric_limits<int>::max() / 2;
	travel_time[1][0] = tracks[0].duration;
	travel_time[2][0] = tracks[0].duration;
	travel_time[3][0] = std::numeric_limits<int>::max() / 2;
	num_tracks = 0;
	while( num_tracks < length ){
		do{
			tracks[num_tracks].begin_begin = (rand() % MAX_TRAVEL) + 1;
			tracks[num_tracks].begin_end = (rand() % MAX_TRAVEL) + 1;
			tracks[num_tracks].end_begin = (rand() % MAX_TRAVEL) + 1;
			tracks[num_tracks].end_end = (rand() % MAX_TRAVEL) + 1;
		} while( !checkTrack() );
		tracks[num_tracks+1].duration = (rand() % MAX_DURATION) + 1;
		travel_time[0][num_tracks+1] = min( travel_time[0][num_tracks] + tracks[num_tracks].begin_end + tracks[num_tracks+1].duration, travel_time[1][num_tracks] + tracks[num_tracks].end_end + tracks[num_tracks+1].duration );
	 	travel_time[1][num_tracks+1] = min( travel_time[0][num_tracks] + tracks[num_tracks].begin_begin + tracks[num_tracks+1].duration, travel_time[1][num_tracks] + tracks[num_tracks].end_begin + tracks[num_tracks+1].duration );
		travel_time[2][num_tracks+1] = min( travel_time[2][num_tracks] + tracks[num_tracks].begin_end + tracks[num_tracks+1].duration, travel_time[3][num_tracks] + tracks[num_tracks].end_end + tracks[num_tracks+1].duration );
	 	travel_time[3][num_tracks+1] = min( travel_time[2][num_tracks] + tracks[num_tracks].begin_begin + tracks[num_tracks+1].duration, travel_time[3][num_tracks] + tracks[num_tracks].end_begin + tracks[num_tracks+1].duration );
		num_tracks++;
	}
}

void output(){
	for( unsigned int i = 0; i < num_tracks; ++i ){
		cout << tracks[i].duration << " " << tracks[i].begin_begin << " " << tracks[i].begin_end << " " << tracks[i].end_begin << " " << tracks[i].end_end << '\n';
	}
}

int main( int argc, char ** args ){
        int cases = 10;
        cout << cases << "\n";		
        while( cases-- ){
				int tracks_to_generate = (rand() % (MAX_TRACKS-1)) + 2;
				int duration = (rand() % (100000-720)) + 720;
                cout << tracks_to_generate << " " << duration << "\n";
				generate( tracks_to_generate );
				output();
        }
        return 0;
}

