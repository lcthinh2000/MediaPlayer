#define _CRT_SECURE_NO_WARNINGS
#include <filesystem>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <vector>
#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <direct.h>
#include <ctime>
#include <atlbase.h>
#include <atlwin.h>
#include <wmp.h>

#include <Mmsystem.h>
#include <mciapi.h>
#include <cstddef>
#include <fstream>
#include "tag.h"
#include "sdk.h"

#pragma comment(lib, "Winmm.lib")

namespace fs = std::filesystem;
using namespace std;
TCHAR g_szDrvMsg[] = _T("A:\\");

int disMain();
int disPl();
vector<string> disSorL(string path);
void creatPL(vector<string> plist, string path, string path1);
void deletePL(string path);
void runPL(vector<string> plist, vector<string> plist1, string path, string path1);
void runSong(string path, vector<string> plist, string type);
void metadata(string pathSong, string path);
void runASong();
void readFolder(string path);
void runFile(string path);
void runMain(string pathSong, string pathPL, vector<string> song, vector<string> playlist);

int main()
{
	string pathSong = "E:\\Document\\document fpt\\media\\Media Play";
	string pathPL = "E:\\Document\\document\\PlayList";
	vector<string> song;
	vector<string> playlist;
	song = disSorL(pathSong);
	playlist = disSorL(pathPL);
	runMain(pathSong, pathPL, song, playlist);
	return 0;
}

int disMain() {
	int n;
	cout << "\tMEDIA PLAYER\n\n";
	cout << "1. Show all songs\n";
	cout << "2. Show playlist\n";
	cout << "3. Play a file\n";
	cout << "4. Play a file with SDK\n";
	cout << "0. Exit\n";
	cout << "\nCommand: "; cin >> n;
	return n;
}

int disPl() {
	int n;
	cout << "\n1. Creat new play list\n";
	cout << "2. Delete a play list\n";
	cout << "3. Choose a play list\n";
	cout << "0. Exit\n";
	cout << "\nCommand: "; cin >> n;
	return n;
}

vector<string> disSorL(string path) {
	struct stat sb;
	vector<string> plist;
	for (const auto& entry : fs::directory_iterator(path)) {
		filesystem::path outfilename = entry.path();
		string outfilename_str = outfilename.string();
		const char* path = outfilename_str.c_str();
		plist.push_back(path);
	}
	return plist;
}

void creatPL(vector<string> plist, string path, string path1) {
	string namePL, s, tam;
	int num, n;
	vector<int> choose;
	plist = disSorL(path);
	cout << "\t\tList Songs\n\n";
	for (int i = 0; i < plist.size(); i++) {
		cout << i + 1; cout << ". ";
		tam = plist[i];
		cout << tam.substr(path.length() + 1) << endl;
	}
	//cout << "\nNumber of songs: "; cin >> num;
	cout << "\nName of play list: "; cin >> namePL;
	string pathPL = path1 + "\\" + namePL;
	string command("mkdir ");
	string command1 = "copy ";

	command.append(pathPL);
	const char* final_command = command.c_str();
	system(final_command);
	cout << "\nPress 0 to end!\n";
	cout << "\nSelect the songs: \n";
	while (1) {
		cin >> n;
		if (n == 0) {
			break;
		}
		if (n > 0 && n <= plist.size()) {
			choose.push_back(n);
		}
	}

	vector<string> fcm;
	for (int i = 0; i < choose.size(); i++) {
		s = command1 + "\"" + plist[choose[i] - 1] + "\"" + " " + "\"" + pathPL + "\"" + " /y";
		fcm.push_back(s);
		//cout << s << endl;
		system(fcm[i].c_str());
	}
	cout << "Creat Play List successful!\n";
	Sleep(1500);
}

void deletePL(string path) {
	string cmm = "rmdir /s /q " + path;
	//cout << cmm << endl;
	system(cmm.c_str());
}

void runPL(vector<string> plist, vector<string> plist1, string path, string path1) {
	int cm, cm1, cm2, fun;
	string tam;
	vector<string> plist2;
	system("cls");
	cout << "\t\tList Play List\n\n";
	plist1 = disSorL(path1);
	for (int i = 0; i < plist1.size(); i++) {
		cout << i + 1 << ". ";
		tam = plist1[i];
		cout << tam.substr(path1.length() + 1) << endl;
	}
	cm = disPl();
	switch (cm) {
	case 1:
		system("cls");
		creatPL(plist, path, path1);
		runPL(plist, plist1, path, path1);
		break;
	case 2:
		cout << "\nChoose play list to delete: "; cin >> cm1;
		deletePL(plist1[cm1 - 1]);
		cout << "\nDelete play list successful!\n";
		Sleep(1500);
		runPL(plist, plist1, path, path1);
		break;
	case 3:
		cout << "\nChoose play list to open: "; cin >> cm2;
		system("cls");
		plist2 = disSorL(plist1[cm2 - 1]);
		runSong(plist1[cm2 - 1], plist2, "list");
		runPL(plist, plist1, path, path1);
		break;
	case 0:
		system("cls");
		runMain(path, path1, plist, plist1);
		break;
	default:
		break;
	}
}

void readFolder(string path) {
	vector<string> list = disSorL(path);
	int com;
	string tam;
	for (int i = 0; i < list.size(); i++) {
		cout << i + 1 << ". ";
		tam = list[i];
		if (path.length()==3) {
			cout << tam.substr(path.length()) << endl;
		}
		else {
			cout << tam.substr(path.length() + 1) << endl;
		}
		//cout << tam << endl;
	}
	cout << "\nCommand: "; cin >> com;
	if (com > 0 || com < (list.size() + 1)) {
		if (checkmp3(list[com - 1])) {
			runFile(list[com - 1]);
		}
		else {
			readFolder(list[com - 1]);
		}
	}
}

void runFile(string path) {
	system("cls");
	int n1, n;
	time_t t1, t2, previous_pause_time = 0;
	string lenh = "open \"" + path + "\" type mpegvideo alias mp3";
	mciSendString(lenh.c_str(), NULL, 0, NULL);
	while (1)
	{
		system("cls");
		cout << "\t\nAudio file " << endl;
		cout << "\n1. Play the file";
		cout << "\n0. Exit";
		cout << "\n\nCommand: ";

		cin >> n1;

		if (n1 == 1)
		{
			while (1)
			{

				cout << "Press 1 to play the file and press 2 to exit the file." << endl;
				cin >> n;
				if (n == 1)
				{
					//play the audio file
					t1 = time(0);
					mciSendString("play mp3", NULL, 0, NULL);
					cout << "Audio file playing...\n\n";
				}
				else if (n == 2)
				{
					//close the file and get out of the loop
					mciSendString("close mp3", NULL, 0, NULL);
					break;
				}

				cout << "Press 0 to pause the file and press 2 to exit the file." << endl;
				cin >> n;
				if (n == 0)
				{
					//pause the audio file
					mciSendString("pause mp3", NULL, 0, NULL);
					t2 = time(0);
					cout << "Audio file paused after " << t2 - t1 + previous_pause_time << " seconds.\n\n";
					previous_pause_time += t2 - t1;
				}
				else if (n == 2)
				{
					//close the audio file
					mciSendString("close mp3", NULL, 0, NULL);
					system("cls");
					break;
				}
			}
		}
		if (n1 == 0)
		{
			//close the file and get out of the loop
			mciSendString("close mp3", NULL, 0, NULL);
			system("cls");
			break;
		}
	}
}

void runSong(string path, vector<string> plist, string type) {
	time_t t1, t2, previous_pause_time = 0;
	string pathMusic, tam, name, pathtam;
	string path1 = "E:\\Document\\document\\PlayList";
	vector<string> plist1 = disSorL(path1);
	int comm, n, n1;
	while (1)
	{
		cout << "\t\tList Songs\n\n";
		for (int i = 0; i < plist.size(); i++) {
			cout << i + 1; cout << ". ";
			tam = plist[i];
			cout << tam.substr(path.length() + 1) << endl;
		}

		cout << "\nPress 0 to exit!\n\n";
		cout << "Press command: "; cin >> comm;
		switch (comm) {
		case 0:
			if (type == "song") {
				system("cls");
				runMain(path, path1, plist, plist1);
				break;
			}
			if (type == "list") {
				system("cls");
				runPL(plist, plist1, path, path1);
				break;
			}
		default:
			pathMusic = "open \"" + plist[comm - 1] + "\" type mpegvideo alias mp3";
			pathtam = plist[comm - 1];
			name = pathtam.substr(path.length() + 1);
			break;
		}

		mciSendString(pathMusic.c_str(), NULL, 0, NULL);

		while (1)
		{
			system("cls");
			cout << "\tAudio file: " << name << endl;
			cout << "\n1. Play the file";
			cout << "\n2. Show and edit metadata file";
			cout << "\n0. Exit";
			cout << "\n\nCommand: ";
			
			cin >> n1;

			if (n1 == 1)
			{
				while (1)
				{

					cout << "Press 1 to play the file and press 2 to exit the file." << endl;
					cin >> n;
					if (n == 1)
					{
						//play the audio file
						t1 = time(0);
						mciSendString("play mp3", NULL, 0, NULL);
						cout << "Audio file playing...\n\n";
					}
					else if (n == 2)
					{
						//close the file and get out of the loop
						mciSendString("close mp3", NULL, 0, NULL);
						break;
					}

					cout << "Press 0 to pause the file and press 2 to exit the file." << endl;
					cin >> n;
					if (n == 0)
					{
						//pause the audio file
						mciSendString("pause mp3", NULL, 0, NULL);
						t2 = time(0);
						cout << "Audio file paused after " << t2 - t1 + previous_pause_time << " seconds.\n\n";
						previous_pause_time += t2 - t1;
					}
					else if (n == 2)
					{
						//close the audio file
						mciSendString("close mp3", NULL, 0, NULL);
						system("cls");
						break;
					}
				}
			}
			if (n1 == 2)
			{
				mciSendString("close mp3", NULL, 0, NULL);
				system("cls");
				metadata(pathtam, path);
			}
			if (n1 == 0)
			{
				//close the file and get out of the loop
				mciSendString("close mp3", NULL, 0, NULL);
				system("cls");
				break;
			}
		}
	}
}

void runASong() {
	system("cls");
	string path;
	int n1, n;
	time_t t1, t2, previous_pause_time = 0;
	cin.ignore();
	cout << "\nPress path: ";
	getline(std::cin, path);
	string lenh = "open \"" + path + "\" type mpegvideo alias mp3";
	mciSendString(lenh.c_str(), NULL, 0, NULL);
	while (1)
	{
		system("cls");
		cout << "\t\nAudio file " << endl;
		cout << "\n1. Play the file";
		cout << "\n0. Exit";
		cout << "\n\nCommand: ";

		cin >> n1;

		if (n1 == 1)
		{
			while (1)
			{

				cout << "Press 1 to play the file and press 2 to exit the file." << endl;
				cin >> n;
				if (n == 1)
				{
					//play the audio file
					t1 = time(0);
					mciSendString("play mp3", NULL, 0, NULL);
					cout << "Audio file playing...\n\n";
				}
				else if (n == 2)
				{
					//close the file and get out of the loop
					mciSendString("close mp3", NULL, 0, NULL);
					break;
				}

				cout << "Press 0 to pause the file and press 2 to exit the file." << endl;
				cin >> n;
				if (n == 0)
				{
					//pause the audio file
					mciSendString("pause mp3", NULL, 0, NULL);
					t2 = time(0);
					cout << "Audio file paused after " << t2 - t1 + previous_pause_time << " seconds.\n\n";
					previous_pause_time += t2 - t1;
				}
				else if (n == 2)
				{
					//close the audio file
					mciSendString("close mp3", NULL, 0, NULL);
					system("cls");
					break;
				}
			}
		}
		if (n1 == 0)
		{
			//close the file and get out of the loop
			mciSendString("close mp3", NULL, 0, NULL);
			system("cls");
			break;
		}
	}

}

void metadata(string pathSong, string path) {
	FILE* ifile;
	ifile = fopen(pathSong.c_str(), "r+");
	if (ifile)
	{
		if (!checkmp3(pathSong))
		{
			cout << "ERROR! File Is Not An MP3 and Can Not Be Read. Please Only Use MP3 Files" << endl;

			cin.get();
			fclose(ifile);
			return;
		}
		else
		{
			cout << "File " << pathSong.substr(path.length() + 1) << " Opened Successfully" << endl;
			int readloc = getsize(ifile) - 128; //Go to byte location of information
			int filesize = getsize(ifile);
			string tag = Header(ifile, readloc); //read The Tag to make sure the audio file is tagged
			if (tag == "TAG")
			{
				cout << "File Has A Valid MP3 Tag And Will Be Read Now" << endl << endl;
				readloc += 3; //move past Tag location to next information
				MP3Tag tag;
				//Calls Function to read all data from the MP3 file
				ReadMP3(ifile, tag);

				cout << "You May Now Edit the File's Tags" << endl;
				cout << "0: Exit Program" << endl;
				cout << "1. Edit Artist" << endl;
				cout << "2. Edit Title" << endl;
				cout << "3. Edit Album" << endl;
				cout << "4. Edit Year" << endl;
				cout << "5. Edit Comment" << endl;
				cout << "6. ReRead Info" << endl << endl;
				short r, reboot = 0;
				while (reboot < 1)
				{
					cout << "Please Enter Your Choice And Then Press Enter: ";
					cin >> r;
					switch (r)
					{
					case 0:
						fclose(ifile);
						return;
						break;
					case 1:
						char artist[31];
						cout << "Enter Desired Artist Name" << endl;
						cin.ignore(); //sets break time for user to enter input
						cin.getline(artist, 31);
						WriteArtist(ifile, filesize, artist);
						break;
					case 2:
						char title[31];
						cout << "Enter Desired Title" << endl;
						cin.ignore();
						cin.getline(title, 31);
						WriteTitle(ifile, filesize, title);
						break;
					case 3:
						char album[31];
						cout << "Enter Desired Album Title" << endl;
						cin.ignore();
						cin.getline(album, 31);
						WriteAlbum(ifile, filesize, album);
						break;
					case 4:
						char year[5];
						cout << "Enter Desired Release Year" << endl;
						cin.ignore();
						cin.getline(year, 5);
						WriteYear(ifile, filesize, year);
						break;
					case 5:
						char comment[31];
						cout << "Enter Desired Comments" << endl;
						cin.ignore();
						cin.getline(comment, 31);
						WriteComment(ifile, filesize, comment);
						break;
					case 6:
						cout << endl;
						ReadMP3(ifile, tag);
						break;
					default:
						cout << "The Number You Entered Is Not A Valid Option. Please Try Again" << endl;
						break;
					}
				}
				cin.get();
				fclose(ifile);
				return;
			}
			else
			{
				cout << "File Is Not Tagged With Information. Please Try A Different MP3" << endl;
				cin.get();
				fclose(ifile);
				return;
			}
		}
	}
	else
	{
		cout << "Error Opening File. Press The Enter Key To Exit" << endl;
		cin.get(); //If opening error end program
		return;
	}
}

void runMain(string pathSong, string pathPL, vector<string> song, vector<string> playlist) {
	int command, cm, cm1;
	string hardware;
	command = disMain();
	ULONG uDriveMask = _getdrives();
	vector<string> list;
	switch (command) {
	case 1:
		system("cls");
		runSong(pathSong, song, "song");
		break;
	case 2:
		runPL(song, playlist, pathSong, pathPL);
		break;
	case 3:
		system("cls");
		cout << "1. Press path\n";
		cout << "2. Choose from folder tree\n";
		cout << "\nCommand: "; cin >> cm;
		if (cm == 1) {
			runASong();
		}
		if (cm == 2) {
			system("cls");
			if (uDriveMask == 0)
			{
				printf("_getdrives() failed with failure code: %d\n",
					GetLastError());
			}
			else
			{
				while (uDriveMask) {
					if (uDriveMask & 1) {
						list.push_back(g_szDrvMsg);
					}

					++g_szDrvMsg[0];
					uDriveMask >>= 1;
				}
				for (int i = 0; i < list.size(); i++) {
					cout << i + 1 << ". " << list[i] << endl;
				}
			}
			cout << "\nCommand: "; cin >> cm1;
			hardware = list[cm1 - 1];
			//system("cls");
			readFolder(hardware);
		}
		break;
	case 4:
		system("cls");
		if (uDriveMask == 0)
		{
			printf("_getdrives() failed with failure code: %d\n",
				GetLastError());
		}
		else
		{
			while (uDriveMask) {
				if (uDriveMask & 1) {
					list.push_back(g_szDrvMsg);
				}

				++g_szDrvMsg[0];
				uDriveMask >>= 1;
			}
			for (int i = 0; i < list.size(); i++) {
				cout << i + 1 << ". " << list[i] << endl;
			}
		}
		cout << "\nCommand: "; cin >> cm1;
		hardware = list[cm1 - 1];
		//system("cls");
		readF(hardware);

		break;

	case 0:
		exit(0);
	default:
		break;
	}
}