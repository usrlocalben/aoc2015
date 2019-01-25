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


struct Factor {
	//string name;
	array<int, 4> co;
	int cal; };

vector<Factor> fs;


int solve1(const int rem, const int fi, const array<int, 4> sum) {
	const auto& factor = fs[fi];
	if (fi == sz(fs)-1) {
		int ax = 1;
		for (int i=0; i<4; i++) {
			int x = (factor.co[i] * rem) + sum[i];
			x = max(x, 0);
			ax *= x; }
		return ax; }

	int best = 0;
	for (int amt=rem; amt>=0; amt--) {
		array<int, 4> newSum;
		for (int i=0; i<4; i++) {
			newSum[i] = sum[i] + factor.co[i]*amt; }
		int score = solve1(rem-amt, fi+1, newSum);
		best = max(best, score); }
	return best; }


const int TARGET_CALORIES = 500;

int solve2(const int rem, const int fi, const array<int, 4> sum, const int cal) {
	const auto& factor = fs[fi];
	if (fi == sz(fs)-1) {
		int ax = 1;
		for (int i=0; i<4; i++) {
			int x = (factor.co[i] * rem) + sum[i];
			x = max(x, 0);
			ax *= x; }
		int totCal = factor.cal*rem + cal;
		if (totCal != TARGET_CALORIES) {
			return -1; }
		return ax; }

	int best = -1;
	for (int amt=rem; amt>=0; amt--) {
		array<int, 4> newSum;
		for (int i=0; i<4; i++) {
			newSum[i] = sum[i] + factor.co[i]*amt; }
		int newCal = cal + factor.cal * amt;
		int score = solve2(rem-amt, fi+1, newSum, newCal);
		if (score == -1) continue;
		best = max(best, score); }
	return best; }


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string line;
	vs segs;

	while (getline(cin, line)) {
		segs = split(line, ' ');

		auto& factor = segs[0];
		factor = factor.substr(0, sz(factor)-1);

		int co1 = stoi(segs[2]);
		int co2 = stoi(segs[4]);
		int co3 = stoi(segs[6]);
		int co4 = stoi(segs[8]);
		int cal_ = stoi(segs[10]);

		fs.push_back({ {co1,co2,co3,co4}, cal_ }); }

	// part 1
	int amt = solve1(100, 0, {0,0,0,0});
	cout << "1: " << amt << nl;

	// part 2
	amt = solve2(100, 0, {0,0,0,0}, 0);
	cout << "2: " << amt << nl;
	return 0; }
