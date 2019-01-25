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


int numPeople = 0;
uint32_t allmask = 0;
unordered_map<string, int> names;

int pid(const string& s) {
	if (auto search = names.find(s); search == names.end()) {
		int id = numPeople++;
		names[s] = id;
		return id; }
	else {
		return search->second; }}

int dim;
vector<int> happy;
vector<int> seats;

int solve(int pos, uint32_t iumask) {
	if (pos == numPeople) {
		int p1 = seats[0];
		int p2 = seats[numPeople-1];
		return happy[p1*dim+p2] + happy[p2*dim+p1]; }
	int best = -oo;
	forn(pi,numPeople) {
		const uint32_t pb = 1<<pi;

		if (iumask & pb) continue;  // in-use
		seats[pos] = pi;
		int p1 = seats[pos-1];
		int p2 = seats[pos];
		int amt = happy[p1*dim+p2] + happy[p2*dim+p1];
		best = max(best, amt + solve(pos+1, iumask|pb));}
	return best; }

	
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	vs segs;
	vs lines;
	string line;
	while (getline(cin, line)) {
		lines.emplace_back(line); }

	dim = sz(lines)+1;
	happy.resize(dim*dim, 0);

	for (const auto& line : lines) {
		segs = split(line, ' ');
		string& who = segs[0];
		string& target = segs[10];
		target = target.substr(0, sz(target)-1);

		int whoId = pid(who);
		int targetId = pid(target);

		int amt = stoi(segs[3]);
		if (segs[2] == "lose") {
			amt = -amt;}

		//cout << who << " -> " << target << " == " << amt << "\n";
		happy[whoId*dim+targetId] = amt;}

	// part 1
	allmask = (1<<numPeople)-1;
	seats.resize(numPeople, 0);
	int best = solve(1, 1);
	cout << "1: " << best << nl;

	// part 2
	pid("self");
	allmask = (1<<numPeople)-1;
	seats.resize(numPeople, 0);
	best = solve(1, 1);
	cout << "2: " << best << nl;

	return 0; }
