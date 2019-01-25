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



int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string line;
	vs segs;

	vector<unordered_map<string, int>> aunts(500+1);

	while (getline(cin, line)) {
		segs = split(line, ' ');

		int num = stoi(segs[1]);

		auto& fn1 = segs[2];
		fn1 = fn1.substr(0, sz(fn1)-1);
		int amt1 = stoi(segs[3]);
		auto& fn2 = segs[4];
		fn2 = fn2.substr(0, sz(fn2)-1);
		int amt2 = stoi(segs[5]);
		auto& fn3 = segs[6];
		fn3 = fn3.substr(0, sz(fn3)-1);
		int amt3 = stoi(segs[7]);

		auto& map = aunts[num];
		map["__candidate__"] = 1;
		map[fn1] = amt1;
		map[fn2] = amt2;
		map[fn3] = amt3; }

	auto removeIfNot = [&](const string& fact, int amt) {
		for (auto& map : aunts) {
			if (auto search = map.find(fact); search!=map.end()) {
				if (search->second != amt) {
					map["__candidate__"] = 0; }}}};

	auto removeIfNotGreater = [&](const string& fact, int amt) {
		for (auto& map : aunts) {
			if (auto search = map.find(fact); search!=map.end()) {
				if (search->second <= amt) {
					map["__candidate__"] = 0; }}}};

	auto removeIfNotFewer = [&](const string& fact, int amt) {
		for (auto& map : aunts) {
			if (auto search = map.find(fact); search!=map.end()) {
				if (search->second >= amt) {
					map["__candidate__"] = 0; }}}};

	// part 1
	removeIfNot("children", 3);
	removeIfNot("cats", 7);
	removeIfNot("samoyeds", 2);
	removeIfNot("pomeranians", 3);
	removeIfNot("akitas", 0);
	removeIfNot("vizslas", 0);
	removeIfNot("goldfish", 5);
	removeIfNot("trees", 3);
	removeIfNot("cars", 2);
	removeIfNot("perfumes", 1);

	int p1aunt = -1;
	for (int i=1; i<sz(aunts); i++) {
		auto& aunt = aunts[i];
		if (aunt["__candidate__"] == 1) {
			if (p1aunt == -1) {
				p1aunt = i; }
			else {
				cout << "p1 ambiguous aunts\n";
				exit(EXIT_FAILURE); }}}
	cout << "1: " << p1aunt << nl;

	// part 2
	for (auto& aunt : aunts) {
		aunt["__candidate__"] = 1; }

	removeIfNot("children", 3);
	removeIfNotGreater("cats", 7);
	removeIfNot("samoyeds", 2);
	removeIfNotFewer("pomeranians", 3);
	removeIfNot("akitas", 0);
	removeIfNot("vizslas", 0);
	removeIfNotFewer("goldfish", 5);
	removeIfNotGreater("trees", 3);
	removeIfNot("cars", 2);
	removeIfNot("perfumes", 1);

	int p2aunt = -1;
	for (int i=1; i<sz(aunts); i++) {
		auto& aunt = aunts[i];
		if (aunt["__candidate__"] == 1) {
			if (p2aunt == -1) {
				p2aunt = i; }
			else {
				cout << "p2 ambiguous aunts\n";
				exit(EXIT_FAILURE); }}}
	cout << "2: " << p2aunt << nl;

	return 0; }
