#include "tag.h"

int getsize(FILE* file)
{
	if (file) {
		int loc = ftell(file);
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		fseek(file, loc, SEEK_SET);
		return size;
	}
	else {
		cout << "Error cann't read file!\n";
		return 0;
	}
}

bool checkmp3(string filename)
{
	//Checks if the file extension is mp3
	int filetype = filename.length() - 4;
	string filetipe = filename.substr(filetype, 4);
	if (filetipe == ".mp3")
	{
		return true;
	}
	else
	{
		return false;
	}
}

string Header(FILE* file, int readloc)
{
	//Checks for ID3v1 Tag Header 4bytes long...
	//currently only supports v1
	//v1+ coming later
	if (file) {
		char magic[4];
		fseek(file, readloc, SEEK_SET);
		fread(magic, 1, 4, file);
		string str(magic);
		string mag = str.substr(0, 3);
		return mag;
	}
	else {
		cout << "Error cann't read file!\n";
		return "";
	}
}
string Year(FILE* file, int readloc)
{
	//Reads Year Of Track...4bytes long
	if (file) {
		char magic[4];
		fseek(file, readloc, SEEK_SET);
		fread(magic, 1, 4, file);
		string str(magic);
		return str;
	}
	else {
		cout << "Error cann't read file!\n";
		return "";
	}
}
string ReadThirty(FILE* file, int readloc)
{
	//Used to read Title, Artist, Album, Comment
	//Each is 30 bytes long
	if (file) {
		char magic[30];
		fseek(file, readloc, SEEK_SET);
		fread(magic, 1, 30, file);
		string str(magic);
		return str;
	}
	else {
		cout << "Error cann't read file!\n";
		return "";
	}
}
void ReadMP3(FILE* file, MP3Tag tag)
{
	//The following code reads the information for x bytes and then increases the readlocation x spaces
	//so the next information can be read
	if (file) {
		int readloc = getsize(file) - 125;
		tag.Title = ReadThirty(file, readloc);
		readloc += 30;
		tag.Artist = ReadThirty(file, readloc);
		readloc += 30;
		tag.Album = ReadThirty(file, readloc);
		readloc += 30;
		tag.Year = Year(file, readloc);
		readloc += 4;
		tag.Comment = ReadThirty(file, readloc);
		cout << "Artist: " << tag.Artist << endl;
		cout << "Title: " << tag.Title << endl;
		cout << "Album: " << tag.Album << endl;
		cout << "Year: " << tag.Year << endl;
		cout << "Comment: " << tag.Comment << endl << endl;
	}
	else {
		cout << "Error cann't read file!\n";
	}
}
void WriteArtist(FILE* file, int filesize, char Artist[])
{
	if (file) {
		int writeloc = filesize - 95;
		fseek(file, writeloc, SEEK_SET);
		fwrite(Artist, 1, 30, file); //goes to the storage of Artist data and writes new data
		cout << Artist << " set as The Artist" << endl;
	}
	else {
		cout << "Error cann't read file!\n";
		cout << "Set the Artist failed!\n";
	}
}
void WriteTitle(FILE* file, int filesize, char Title[])
{
	if (file) {
		int writeloc = filesize - 125;
		fseek(file, writeloc, SEEK_SET);
		fwrite(Title, 1, 30, file); //goes to the storage of Title data and writes new data
		cout << Title << " set as The Title" << endl;
	}
	else {
		cout << "Error cann't read file!\n";
		cout << "Set the Title failed!\n";
	}
}
void WriteAlbum(FILE* file, int filesize, char Album[])
{
	if (file) {
		int writeloc = filesize - 65;
		fseek(file, writeloc, SEEK_SET);
		fwrite(Album, 1, 30, file); //goes to the storage of Album data and writes new data
		cout << Album << " set as The Album" << endl;
	}
	else {
		cout << "Error cann't read file!\n";
		cout << "Set the Album failed!\n";
	}
}
void WriteYear(FILE* file, int filesize, char Year[])
{
	if (file) {
		int writeloc = filesize - 35;
		fseek(file, writeloc, SEEK_SET);
		fwrite(Year, 1, 4, file); //goes to the storage of Year data and writes new data
		cout << Year << " set as The Release Year" << endl;
	}
	else {
		cout << "Error cann't read file!\n";
		cout << "Set the Year failed!\n";
	}
}
void WriteComment(FILE* file, int filesize, char Comment[])
{
	if (file) {
		int writeloc = filesize - 31;
		fseek(file, writeloc, SEEK_SET);
		fwrite(Comment, 1, 30, file); //goes to the storage of Comment data and writes new data
		cout << Comment << " set as The Comment" << endl;
	}
	else {
		cout << "Error cann't read file!\n";
		cout << "Set the Comment failed!\n";
	}
}