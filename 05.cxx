#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <iostream>
#include <optional>
#include <queue>
#include <string>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#define sz(x) (int(x.size()))
#define forn(i,n) for(int i=0;i<int(n);i++)
#define watch(x) cout << (#x) << "(" << (x) << ")\n"
#define dbg(x) (#x) << "(" << (x) << ") "
#define fi first
#define se second
const string nl("\n");
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;
using vs = vector<string>;
#define uset unordered_set
#define umap unordered_map
const int oo = 0x3f3f3f3f;


bool isvowel(char ch) {
	switch(ch) {
		case 'a': return true;
		case 'e': return true;
		case 'i': return true;
		case 'o': return true;
		case 'u': return true;}
	return false; }


bool isnice1(const string& s) {
	char prev = 0;
	int tc = 0;
	int vc = 0;
	forn(i,sz(s)){
		if (isvowel(s[i])) vc++;
		if (s[i] == prev) tc++;
		prev = s[i];
		if (i < sz(s)-1) {
			if (s[i]=='a' && s[i+1]=='b') return false;
			if (s[i]=='c' && s[i+1]=='d') return false;
			if (s[i]=='p' && s[i+1]=='q') return false;
			if (s[i]=='x' && s[i+1]=='y') return false;}}
	return tc>0 && vc>=3; }


bool isnice2(const string& s) {
	static string tmp;
	char p0 = 0;
	char p1 = 0;
	int rc = 0;
	int pc = 0;
	//cout << ">>> " << s << "\n";
	forn(i,sz(s)){
		if (s[i] == p0) rc++;
		p0 = p1;
		p1 = s[i];

		if (i < sz(s)-1) {
			tmp.clear();
			tmp.push_back(s[i]);
			tmp.push_back(s[i+1]);
			//cout << ":" << tmp;

			for (int j=0; j<i-2; j++) {
				//cout << "(" << j << "/" << s.substr(j,2) << ")";
				if (s.substr(j,2) == tmp) {
					pc++; }}
			for (int j=i+2; j<sz(s)-1; j++) {
				//cout << "(" << j << "/" << s.substr(j,2) << ")";
				if (s.substr(j,2) == tmp) {
					pc++; }}}}
	return pc>0 && rc>0;}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string line;
	int p1cnt = 0;
	int p2cnt = 0;
	while (getline(cin, line)) {
		if (isnice1(line)) p1cnt++;
		if (isnice2(line)) p2cnt++; }

	cout << "1: " << p1cnt << nl;
	cout << "2: " << p2cnt << nl;
	return 0; }
