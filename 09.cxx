#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <iostream>
#include <optional>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#define sz(x) (int((x).size()))
#define forn(i,n) for(int i=0; i<n; i++) 
const string nl("\n");
const int oo = 0x3f3f3f3f;

std::vector<std::string> split(const std::string& str, char ch) {
	std::vector<std::string> items;
	std::string src(str);
	auto nextmatch = src.find(ch);
	while (1) {
		auto item = src.substr(0, nextmatch);
		items.push_back(item);
		if (nextmatch == std::string::npos) { break; }
		src = src.substr(nextmatch + 1);
		nextmatch = src.find(ch); }

	return items; }


int numCities = 0;
uint32_t allmask = 0;
unordered_map<string, int> citytab;
vector<int> cost;

int cityId(const string& s) {
	if (auto search = citytab.find(s); search!=citytab.end()) {
		return search->second; }
	else {
		int nextseq = numCities++;
		citytab[s] = nextseq;
		return nextseq; }}


int proc1(int here, const uint32_t visitmask, int depth=0) {
	//forn(i,depth) cout << " ";
	//cout << "h:" << here << ", " << hex << visitmask << dec << "\n";
	if (visitmask == allmask) {
		return 0; }

	int best = oo;
	for (int ci=0; ci<numCities; ci++) {
		const uint32_t thisMask = 1<<ci;
		const int nextCost = cost[here*10 + ci];
		if (visitmask & thisMask) continue;
		if (nextCost == -1) continue;

		int remainderCost = proc1(ci, visitmask | thisMask, depth+1);
		if (remainderCost == -1) continue;

		best = min(best, nextCost + remainderCost);}

	return best==oo?-1:best;}


int proc2(int here, const uint32_t visitmask, int depth=0) {
	//forn(i,depth) cout << " ";
	//cout << "h:" << here << ", " << hex << visitmask << dec << "\n";
	if (visitmask == allmask) {
		return 0; }

	int best = -1;
	for (int ci=0; ci<numCities; ci++) {
		const uint32_t thisMask = 1<<ci;
		const int nextCost = cost[here*10 + ci];
		if (visitmask & thisMask) continue;
		if (nextCost == -1) continue;

		int remainderCost = proc2(ci, visitmask | thisMask, depth+1);
		if (remainderCost == -1) continue;

		best = max(best, nextCost + remainderCost);}

	return best; }


int main() {
	cost.resize(10*10, -1);

	string line;

	while (getline(cin, line)) {
		auto segs = split(line, ' ');

		int from = cityId(segs[0]);
		int to = cityId(segs[2]);
		int c = stoi(segs[4]);

		cost[from*10 + to] = c;
		cost[to*10 + from] = c; }

	allmask = (1<<numCities)-1;

	// part 1
	int best = oo;
	for (int ci=0; ci<numCities; ci++) {
		int x = proc1(ci, 1<<ci);
		//cout << "ci:" << ci << ", " << x << "\n";
		if (x == -1) continue;
		best = min(best, x); }

	if (best == oo) {
		cout << "no routes found!\n";
		exit(EXIT_FAILURE); }
	cout << "1: " << best << nl;

	// part 2
	best = -1;
	for (int ci=0; ci<numCities; ci++) {
		int x = proc2(ci, 1<<ci);
		//cout << "ci:" << ci << ", " << x << "\n";
		if (x == -1) continue;
		best = max(best, x); }

	if (best == -1) {
		cout << "no routes found!\n";
		exit(EXIT_FAILURE); }
	cout << "2: " << best << nl;
	return 0; }
