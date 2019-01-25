#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <iostream>
#include <numeric>
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


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	vi vel;
	vi don;
	vi doff;

	string line;
	vs segs;
	while (getline(cin, line)) {
		segs = split(line, ' ');
		auto& name = segs[0];
		int v = stoi(segs[3]);
		int on = stoi(segs[6]);
		int off = stoi(segs[13]);

		vel.push_back(v);
		don.push_back(on);
		doff.push_back(off);}

	const int num = sz(vel);

	const int Tend = 2503;

	// part 1
	int best = 0;
	forn(i,num) {
		int cycle = don[i]+doff[i];
		int numCycles = Tend/cycle;
		int ax = numCycles * vel[i] * don[i];
		int RT = Tend % cycle;

		if (don[i] <= RT) {
			ax += vel[i] * don[i]; }
		else {
			ax += vel[i] * RT; }
		//cout << ax << "\n";
		best = max(best, ax); }

	cout << "1: " << best << nl;

	// part 2
	vi points(num, 0);

	for (int tick=1; tick<=Tend; tick++) {
		int bestPos = -oo;
		int bestIdx = -1;

		forn(i,num) {
			int cycle = don[i]+doff[i];
			int numCycles = tick/cycle;
			int ax = numCycles * vel[i] * don[i];
			int RT = tick % cycle;

			if (don[i] <= RT) {
				ax += vel[i] * don[i]; }
			else {
				ax += vel[i] * RT; }

			if (ax > bestPos) {
				bestPos = ax;
				bestIdx = i;}}
		points[bestIdx]++;}

	int m = *max_element(points.begin(), points.end());
	cout << "2: " << m << nl;
	return 0; }
