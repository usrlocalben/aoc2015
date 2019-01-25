#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <iostream>
#include <optional>
#include <queue>
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
template <typename T>
auto min3(T a, T b, T c) { return min(a,min(b,c)); }
template <typename T>
auto max3(T a, T b, T c) { return max(a,max(b,c)); }
const int oo = 0x3f3f3f3f;
template <typename T>
void setmax(T& slot, T value) { slot = max(slot, value); }
template <typename T>
void setmin(T& slot, T value) { slot = min(slot, value); }


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


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string line;

	vs segs;
	int p1ax = 0;
	int p2ax = 0;
	while (getline(cin,line)) {
		segs = split(line, 'x');
		int l = stoi(segs[0]);
		int w = stoi(segs[1]);
		int h = stoi(segs[2]);

		// part1
		{
		int s1 = l*w;
		int s2 = l*h;
		int s3 = w*h;

		int smallest = min3(s1, s2, s3);
		int needed = (s1+s2+s3)*2 + smallest;
		p1ax += needed;}

		// part2
		{
		int vol = l*w*h;

		int p1 = l*2 + w*2;
		int p2 = l*2 + h*2;
		int p3 = w*2 + h*2;

		int mp = min3(p1, p2, p3);
		int needed = vol + mp;
		p2ax += needed;}}

	cout << "1: " << p1ax << nl;
	cout << "2: " << p2ax << nl;
	return 0; }
