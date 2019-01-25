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

#include <intrin.h>  // popcnt

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

struct ivec2 {
	int x, y;

	ivec2& operator+=(ivec2 b) { x += b.x; y += b.y; return *this; }
	ivec2& operator-=(ivec2 b) { x -= b.x; y -= b.y; return *this; }
	ivec2& operator*=(ivec2 b) { x *= b.x; y *= b.y; return *this; } };

struct ivec3 {
	int x, y, z;

	ivec3& operator+=(ivec3 b) { x += b.x; y += b.y; z += b.z; return *this; }
	ivec3& operator-=(ivec3 b) { x -= b.x; y -= b.y; z -= b.z; return *this; }
	ivec3& operator*=(ivec3 b) { x *= b.x; y *= b.y; z *= b.z; return *this; } };

ivec2 vmin(ivec2 a, ivec2 b) { return ivec2{ min(a.x, b.x), min(a.y, b.y) }; }
ivec2 vmax(ivec2 a, ivec2 b) { return ivec2{ max(a.x, b.x), max(a.y, b.y) }; }

int area(ivec2 a) { return a.x * a.y; }

ostream& operator<<(ostream& stream, ivec2 item) {
	stream << "(" << item.x << ", " << item.y << ")";
	return stream; }

ivec2 operator-(ivec2 a, ivec2 b) { return ivec2{ a.x-b.x, a.y-b.y }; }
ivec2 operator+(ivec2 a, ivec2 b) { return ivec2{ a.x+b.x, a.y+b.y }; }
ivec2 operator*(ivec2 a, ivec2 b) { return ivec2{ a.x*b.x, a.y*b.y }; }

bool operator==(ivec2 a, ivec2 b) { return (a.x==b.x && a.y==b.y); }

const ivec2 UP{0,-1};
const ivec2 DOWN{0,1};
const ivec2 LEFT{-1,0};
const ivec2 RIGHT{1,0};

const auto NORTH = UP;
const auto SOUTH = DOWN;
const auto EAST = RIGHT;
const auto WEST = LEFT;


struct Rect {
	ivec2 lt;
	ivec2 rb;
	ivec2 dim() const { return { rb.x-lt.x, rb.y-lt.y }; }
	int area() const { return ::area(dim()); } };


/* bfs
	deque<pair<XXX, int>> queue;
	uset<XXX> visited;
	queue.push_back({ xxx, 0 });
	while (!queue.empty()) {
		const auto[hpos, hdist] = queue.front();  queue.pop_front();
		if (auto already = visited.find(hpos); already != visited.end()) { continue; }
		visited.insert(hpos);
		queue.push_back({ xxx, hdist+1 }); }
*/

/* dijkstra
	priority_queue<ii, vii, greater<ii>> queue;
	uset<int> visited;
	umap<int, int> dist;

	auto getDistance = [&](int key) {
		if (auto search = dist.find(key); search != dist.end()) {
			return search->second; }
		else {
			return oo; }};

	queue.push({ 0, INITIAL_POSITION });
	dist[INITIAL_POSITION] = 0;
	vector<pair<int, int>> outLinks;

	int answer = -1;
	while (!queue.empty()) {
		auto [hdist, hpos] = queue.top(); queue.pop();
		if (visited.find(hpos) != visited.end()) {
			continue;}
		visited.insert(hpos);

		// do something with hpos @ hdist
		if (hpos == DESTINATION) {
			//cout << "found target\n";
			answer = hdist;
			break;}

		// fill outlinks
		outLinks.clear();
		// outLinks.push_back({ COST, NEXT_NODE });

		for (const auto& link : outLinks) {
			const auto& cost = link.fi;
			const auto& nextPos = link.se;
			int thisCost = getDistance(hpos) + cost;
			if (getDistance(nextPos) > thisCost) {
				dist[nextPos] = thisCost;
				queue.push({ thisCost, nextPos }); }}}
*/

ostream& operator<<(ostream& stream, const vi& nums) {
	bool first = true;
	for (const auto& num : nums) {
		if (first) {
			stream << "[" << num;
			first = false; }
		else {
			stream << ", " << num; }}
	stream << "]";
	return stream; }


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


bool consumePrefix(string& text, const string& match) {
	if ((text.size() >= sz(match)) &&
		(text.substr(0, sz(match)) == match)) {
		text = text.substr(sz(match));
		return true; }
	return false; }


bool consumeSuffix(string& text, const string& match) {
	if ((text.size() >= sz(match)) &&
	    (text.substr(sz(text)-sz(match), sz(match)) == match)) {
		text = text.substr(0, sz(text)-sz(match));
		return true; }
	return false; }

/*
	string line;
	for (int y=0; y<YYY; y++) {
		line.clear();
		for (int x=0; x<XXX; x++) {
			line.push_back(foo); }
		cout << line << nl;}
*/


int mdist(ivec3 a, ivec3 b) {
	return abs(a.x-b.x) + abs(a.y-b.y) + abs(a.z-b.z); }


bool islower(char ch) { return ('a'<=ch && ch <= 'z'); }
bool isupper(char ch) { return ('A'<=ch && ch <= 'Z'); }
bool isalpha(char ch) { return (islower(ch) || isupper(ch)); }
bool isdigit(char ch) { return ('0'<=ch && ch <= '9'); }


vi _factors;
const vi& fa(const int num) {
	_factors.clear();
	for (int i=1; i<=sqrt(num); i++) {
		if (num%i == 0) {
			if (num/i == i) {
				_factors.push_back(i); }
			else {
				_factors.push_back(i);
				_factors.push_back(num/i); }}}
	return _factors; }

struct Player {
	int hp;
	int damage;
	int armor; };

struct Item {
	int cost;
	int damage;
	int armor; };

Player boss;

const auto weapon = array<Item, 5>{
	Item{8,4,0},
	Item{10,5,0},
	Item{25,6,0},
	Item{40,7,0},
	Item{74,8,0} };

const auto armor = array<Item, 6>{
	Item{0,0,0},
	Item{13,0,1},
	Item{31,0,2},
	Item{53,0,3},
	Item{75,0,4},
	Item{102,0,5} };

const auto ring = array<Item, 6>{
	Item{25,1,0},
	Item{50,2,0},
	Item{100,3,0},
	Item{20,0,1},
	Item{40,0,2},
	Item{80,0,3} };

int p1_f1(Player p);
int p1_f2(Player p);
int p1_f3(Player p);
int p2_f1(Player p);
int p2_f2(Player p);
int p2_f3(Player p);
int f4(Player p);
int play(array<Player, 2> pls);

int p1_f1(Player p) {
	int best = oo;
	for (int i=0; i<sz(weapon); i++) {
		//cout << i << nl;
		const auto& item = weapon[i];
		Player pp{ p.hp, p.damage+item.damage, p.armor+item.armor };
		int outcome = p1_f2(pp);
		if (outcome != -1) {
			int cost = item.cost + outcome;
			best = min(best, cost); }}
	return best == oo ? -1 : best; }

int p1_f2(Player p) {
	int best = oo;
	for (int i=0; i<sz(armor); i++) {
		//cout << "." << i << nl;
		const auto& item = armor[i];
		Player pp{ p.hp, p.damage+item.damage, p.armor+item.armor };
		int outcome = p1_f3(pp);
		if (outcome != -1) {
			int cost = item.cost + outcome;
			best = min(best, cost); }}
	return best == oo ? -1: best; }

vi ringbits;
vector<vi> ringbuys;
int p1_f3(Player p) {
	static bool first = true;
	if (first) {
		for (int i=0; i<=0x3f; i++) {
			if (__popcnt(i) <= 2) {
				ringbits.push_back(i); }}
		ringbuys.resize(sz(ringbits));
		for (int idx=0; idx<sz(ringbits); idx++) {
			int pack = ringbits[idx];
			for (int i=0; i<6; i++) {
				int bit = 1<<i;
				if (pack&bit) {
					ringbuys[idx].push_back(i);}}}
		first = false; }

	int best = oo;
	for (const auto& ringbuy : ringbuys) {
		//cout << ".." << "rb" << nl;
		auto pp = p;
		int ringcost = 0;
		for (const auto& i:ringbuy) {
			const auto& item = ring[i];
			ringcost += item.cost;
			pp.damage += item.damage;
			pp.armor += item.armor; }
		int outcome = f4(pp);
		if (outcome != -1) {
			int cost = ringcost + outcome;
			best = min(best, cost); }}
	return best == oo ? -1 : best; }




int p2_f1(Player p) {
	int best = -oo;
	for (int i=0; i<sz(weapon); i++) {
		//cout << i << nl;
		const auto& item = weapon[i];
		Player pp{ p.hp, p.damage+item.damage, p.armor+item.armor };
		int outcome = p2_f2(pp);
		if (outcome != -1) {
			int cost = item.cost + outcome;
			best = max(best, cost); }}
	return best == -oo ? -1 : best; }

int p2_f2(Player p) {
	int best = -oo;
	for (int i=0; i<sz(armor); i++) {
		//cout << "." << i << nl;
		const auto& item = armor[i];
		Player pp{ p.hp, p.damage+item.damage, p.armor+item.armor };
		int outcome = p2_f3(pp);
		if (outcome != -1) {
			int cost = item.cost + outcome;
			best = max(best, cost); }}
	return best == -oo ? -1: best; }


int p2_f3(Player p) {
	int best = -oo;
	for (const auto& ringbuy : ringbuys) {
		//cout << ".." << "rb" << nl;
		auto pp = p;
		int ringcost = 0;
		for (const auto& i:ringbuy) {
			const auto& item = ring[i];
			ringcost += item.cost;
			pp.damage += item.damage;
			pp.armor += item.armor; }
		int outcome = f4(pp);
		if (outcome != -1) {
			int cost = ringcost + outcome;
			best = max(best, cost); }}
	return best == -oo ? -1 : best; }


int f4(Player p) {
	//cout << "...play" << nl;
	if (play({p, boss}) == 0) {
		return 0; }
	return -1; }


int play(array<Player, 2> pls) {
	int ai = 0;
	int di = 1;
	array<int, 2> d = {
		max(pls[ai].damage - pls[di].armor, 1),
		max(pls[di].damage - pls[ai].armor, 1) };
	while (1) {
		pls[di].hp -= d[ai];
		//cout << di << "==" << pls[di].hp << nl;
		if (pls[di].hp <= 0) {
			return ai; }
		swap(ai, di);}}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string line;
	getline(cin, line);
	boss.hp = stoi(split(line, ' ')[2]);
	getline(cin, line);
	boss.damage = stoi(split(line, ' ')[1]);
	getline(cin, line);
	boss.armor = stoi(split(line, ' ')[1]);

	int minCost = p1_f1(Player{100, 0, 0});
	cout << "1: " << minCost << nl;

	int maxCost = p2_f1(Player{100, 0, 0});
	cout << "2: " << maxCost << nl;
	return 0; }
