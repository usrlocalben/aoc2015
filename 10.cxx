#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <iostream>
#include <optional>
#include <string>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#define sz(x) (int((x).size()))
#define forn(i,n) for(int i=0; i<n; i++) 
const string nl("\n");
const int oo = 0x3f3f3f3f;


struct LookAndSay {
	string xform(const string& s) {
		d_out.str("");
		d_out.clear();
		char cur = -1;
		int cnt = 0;
		for (const char ch: s) {
			if (ch == cur) {
				cnt++; }
			else {
				if (cur != -1) {
					d_out << cnt;
					d_out << int(cur-'0'); }
				cur = ch;
				cnt = 1; }}
		if (cur != -1) {
			d_out << cnt;
			d_out << int(cur-'0'); }
		return d_out.str(); }
	ostringstream d_out; };


int main() {
	LookAndSay las;

	string line;
	getline(cin, line);
	line.reserve(65536);

	forn(i,50) {
		if (i==40) {
			cout << "1: " << sz(line) << nl;}
		//cout << "#" << i << ": " << sz(line) << "\n";
		line = las.xform(line);}
	cout << "2: " << sz(line) << "\n";
	return 0; }
