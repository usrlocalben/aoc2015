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
#include <intrin.h> // popcnt

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


const int SEED = 20151125;
const int MOD = 33554393;

int f(ll x) {
	x *= 252533;
	return x % MOD; }


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string line;
	getline(cin, line);
	auto segs = split(line, ' ');

	const int row = stoi(segs[16]);
	const int col = stoi(segs[18]);

	int x = SEED;
	int height = 2;
	int cy = 2;
	int cx = 1;
    while (1) {
		x = f(x);
		if (cy==row && cx==col) {
			break;}

		cy--; cx++;
		if (cy==0) {
			cy = ++height;
			cx = 1; }}
	
	cout << x << nl;
	return 0; }
