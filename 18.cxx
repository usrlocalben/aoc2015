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

const int dim = 100;

vs original, map, tmp;

int numLit(int px, int py) {
	int cnt = 0;
	for (int y=py-1; y<=py+1; y++) {
		for (int x=px-1; x<=px+1; x++) {
			if (px==x && py==y) continue;
			if (map[y][x] == '#') cnt++; }}
	return cnt; }


void update() {
	for (int y=1; y<dim+1; y++) {
		for (int x=1; x<dim+1; x++) {
			char out;
			const int nl = numLit(x, y);
			if (map[y][x] == '#') {
				out = ((nl==2 || nl==3) ? '#' : '.');}
			else {
				out = (nl == 3 ? '#' : '.');}
			tmp[y][x] = out; }}
	swap(tmp, map); }


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string line;
	string pad;
	forn(i,102)pad.push_back('.');
	original.push_back(pad);
	while (getline(cin, line)) {
		line = "." + line + ".";
		original.emplace_back(line); }
	original.push_back(pad);
	
	// part 1
	map = original;
	tmp = original;
	forn(i,100) {
		update();}

	int cnt = 0;
	for (const auto& row: map) {
		for (const auto ch: row) {
			if (ch == '#') cnt++; }}
	cout << "1: " << cnt << nl;

	// part 2
	map = original;
	tmp = original;

	map[1][1] = '#';
	map[dim][1] = '#';
	map[1][dim] = '#';
	map[dim][dim] = '#';

	forn(i,100) {
		update();
		map[1][1] = '#';
		map[dim][1] = '#';
		map[1][dim] = '#';
		map[dim][dim] = '#';}

	cnt = 0;
	for (const auto& row: map) {
		for (const auto ch: row) {
			if (ch == '#') cnt++; }}
	cout << "2: " << cnt << nl;
	return 0; }
