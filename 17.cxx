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

#include <intrin.h> //popcnt

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


vi cs;
uint32_t allmask;
int cnt = 0;

void solve1(int amt, const uint32_t usedmask, int si) {
	if (amt == 0) {
		cnt++;
		return;}
	if (usedmask == allmask) {
		return;}
	for (int i=si; i<sz(cs); i++) {
		const int thismask = 1<<i;
		if (usedmask & thismask) continue;

		if (cs[i] <= amt) {
			solve1(amt-cs[i], usedmask|thismask, i+1); }}}


int best = oo;
int bestCnt = 0;

void solve2(int amt, const uint32_t usedmask, int si) {
	if (amt == 0) {
		int containersUsed = __popcnt(usedmask);
		if (containersUsed == best) {
			bestCnt++; }
		else if (containersUsed < best) {
			best = containersUsed;
			bestCnt = 1; }
		return;}
	if (usedmask == allmask) {
		return;}
	for (int i=si; i<sz(cs); i++) {
		const int thismask = 1<<i;
		if (usedmask & thismask) continue;

		if (cs[i] <= amt) {
			solve2(amt-cs[i], usedmask|thismask, i+1); }}}



int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string line;
	while (getline(cin, line)) {
		cs.push_back(stoi(line));}

	sort(cs.begin(), cs.end(), [](int a, int b) { return b < a; });

	allmask = (1<<sz(cs))-1;

	solve1(150, 0, 0);
	cout << "1: " << cnt << nl;

	solve2(150, 0, 0);
	cout << "2: " << bestCnt << nl;
	return 0; }
