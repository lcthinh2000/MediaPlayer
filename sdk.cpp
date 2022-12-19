#include "sdk.h"

void runSongSDK(string path) {
	int n;
	CoInitialize(NULL);
	CComPtr<IWMPPlayer> player;
	player.CoCreateInstance(__uuidof(WindowsMediaPlayer), 0, CLSCTX_INPROC_SERVER);
	CComPtr<IWMPControls> controls;
	player->get_controls(&controls);
	CComBSTR pathS(path.c_str());
	//player->get_URL(&name);
	player->put_URL(pathS);
	//COLE2T pStr(name);
	while (1) {
		n = MessageBox(NULL, _T("Press OK to pause!\nPress Cancel to exit!"), _T("Window Media Player"), MB_OKCANCEL);
		if (n == 1) {
			controls->pause();
		}
		if (n == 2) {
			break;
		}
		n = MessageBox(NULL, _T("Press OK to play!\nPress Cancel to exit!"), _T("Window Media Player"), MB_OKCANCEL);
		if (n == 1) {
			controls->play();
		}
		if (n == 2) {
			break;
		}
	}
	player.Release();

	CoUninitialize();
}

void runSongSDK1() {
	string path;
	cout << "Path: ";
	cin >> path;
	runSongSDK(path);
}

vector<string> veclist(string path) {
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

void readF(string path) {
	vector<string> list = veclist(path);
	int com;
	string tam;
	for (int i = 0; i < list.size(); i++) {
		cout << i + 1 << ". ";
		tam = list[i];
		if (path.length() == 3) {
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
			runSongSDK(list[com - 1]);
		}
		else {
			readF(list[com - 1]);
		}
	}
}