/*! Wrappers for the sound effects.  See comments and headers for proper use. 
	Author: plaukautis
	modified by jmccrory 2/04
*/

#pragma warning (disable: 4786)

#include "fmod.h"
#include "precompiled.h"
using namespace std;


class CSoundMgrS : public nsl::singleton < CSoundMgrS >
{
public:
	CSoundMgrS();
	~CSoundMgrS();
	bool OpenFile(char * filename, vector<string> &file_list);		// used to open a file in the current directory
	bool Init();		// call this at the start of the game
	bool Play(const char * filename, bool repeat);	// use this to play a new song
	bool Stop();		// Must call this before starting a new track
	void Pause(bool pause);		// Pauses stream
	void Destroy();		// call this at the end of the game

private:
	FSOUND_STREAM *Stream;
	FSOUND_SAMPLE *Sptr;
	int channel;
};

class Effect
{
public:
	Effect();
	~Effect();
	bool PlayEffect(char * filename, int channel);
	void StopEffect();
		
private:
	FSOUND_SAMPLE *Sptr;
};

// singleton accessor
#define CSoundMgr  CSoundMgrS::GetInstancePtr()