#include <algorithm>
#include <array>
#include <cassert>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <optional>
#include <queue>
#include <sstream>
#include <string>
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

vs split(const string& str, char ch) {
	vs items;
	string src(str);
	auto nextmatch = src.find(ch);
	while (1) {
		items.emplace_back(src.substr(0, nextmatch));
		if (nextmatch == string::npos) { break; }
		src = src.substr(nextmatch + 1);
		nextmatch = src.find(ch); }
	return items; }

bool islower(char ch) { return ('a'<=ch && ch <= 'z'); }


vector<pair<string, string>> mods;
string mole;



int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string line;
	vs segs;
	int section = 0;
	while (getline(cin, line)) {
		if (section == 0) {
			if (line == "") {
				section++; }
			else {
				segs = split(line, ' ');
				mods.emplace_back(segs[0], segs[2]); }}
		else {
			mole = line; }}

	// part 1
	uset<string> p;
	string left, right, tmp;
	for (int i=0; i<sz(mole); i++) {
		if (islower(mole[i])) continue;

		left = mole.substr(0,i);
		right = mole.substr(i+1);
		for (const auto& mod : mods) {
			if (sz(mod.first) == 1 && mod.first[0] == mole[i]) {
				p.insert(left + mod.second + right); }}

		if (i < sz(mole)-1) {
			right = mole.substr(i+2); 
			for (const auto& mod : mods) {
				if (sz(mod.first) == 2 && mod.first[0] == mole[i] && mod.first[1] == mole[i+1]) {
					p.insert(left + mod.second + right); }}}}

	cout << "1: " << sz(p) << nl;

	// part 2
	vs m2;
	bool first = true;
	tmp.clear();
	for (int i=0; i<sz(mole); i++) {
		if (!islower(mole[i])) {
			if (first) {
				first=false; }
			else {
				m2.emplace_back(tmp);
				tmp.clear(); }}
		tmp.push_back(mole[i]); }
	m2.emplace_back(tmp);

	int rnar = 0;
	int y = 0;
	for (const auto& s:m2) {
		if (s == "Rn") rnar++;
		else if (s == "Ar") rnar++;
		else if (s == "Y") y++;}

	cout << "2: " << (sz(m2) - rnar - 2*y - 1) << nl;
	return 0; }
