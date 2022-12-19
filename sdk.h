#ifndef SDK_H
#define SDK_H
#include <iostream>
#include <atlbase.h>
#include <atlwin.h>
#include <wmp.h>
#include <vector>
#include <filesystem>
#include "tag.h"

namespace fs = std::filesystem;
using namespace std;

void runSongSDK(string path);
void runSongSDK1();
vector<string> veclist(string path);
void readF(string path);

#endif // !SDK_H

