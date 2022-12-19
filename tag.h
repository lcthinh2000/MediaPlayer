#ifndef TAG_H
#define TAG_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>  
#include <string> 
using namespace std;
//Create a Structure to store MP3s tagged info
struct MP3Tag
{
	string Artist;
	string Title;
	string Album;
	string Year;
	string Comment;
};
//Add Functions to be used
int getsize(FILE* file);
bool checkmp3(string filename);
string ReadThirty(FILE* file, int readloc);
string Header(FILE* file, int readloc);
string Year(FILE* file, int readloc);
void ReadMP3(FILE* file, MP3Tag tag);
void WriteArtist(FILE* file, int filesize, char Artist[]);
void WriteTitle(FILE* file, int filesize, char Title[]);
void WriteAlbum(FILE* file, int filesize, char Album[]);
void WriteYear(FILE* file, int filesize, char Year[]);
void WriteComment(FILE* file, int filesize, char Comment[]);

#endif // !TAG_H

