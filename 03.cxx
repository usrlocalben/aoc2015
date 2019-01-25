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


struct ivec2 {
	int x, y;
	ll toLong() const { return (ll(y)<<32)+x; }
	ivec2& operator+=(ivec2 b) { x += b.x; y += b.y; return *this; }
	ivec2& operator-=(ivec2 b) { x -= b.x; y -= b.y; return *this; }
	ivec2& operator*=(ivec2 b) { x *= b.x; y *= b.y; return *this; } };

ivec2 vmin(ivec2 a, ivec2 b) { return ivec2{ min(a.x, b.x), min(a.y, b.y) }; }
ivec2 vmax(ivec2 a, ivec2 b) { return ivec2{ max(a.x, b.x), max(a.y, b.y) }; }
ivec2 operator-(ivec2 a, ivec2 b) { return ivec2{ a.x-b.x, a.y-b.y }; }
ivec2 operator+(ivec2 a, ivec2 b) { return ivec2{ a.x+b.x, a.y+b.y }; }
ivec2 operator*(ivec2 a, ivec2 b) { return ivec2{ a.x*b.x, a.y*b.y }; }
bool operator==(ivec2 a, ivec2 b) { return (a.x==b.x && a.y==b.y); }
ostream& operator<<(ostream& stream, ivec2 item) {
	stream << "(" << item.x << ", " << item.y << ")"; return stream; }

const ivec2 NORTH{0,-1};
const ivec2 SOUTH{0,1};
const ivec2 EAST{1,0};
const ivec2 WEST{-1,0};


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string line;
	getline(cin, line);

	// part1
	ivec2 pos{0,0};
	unordered_set<ll> visited;
	visited.insert(pos.toLong());
	for (const char dir : line) {
		if      (dir == 'v') { pos += SOUTH; }
		else if (dir == '^') { pos += NORTH; }
		else if (dir == '<') { pos += WEST; }
		else if (dir == '>') { pos += EAST; }
		visited.insert(pos.toLong()); }

	cout << "1: " << sz(visited) << nl;


	// part2
	array<ivec2,2> bots = { ivec2{0,0}, ivec2{0,0} };
	int bi = 0;
	visited.clear();
	visited.insert(0);
	for (const auto& dir : line) {
		auto& pos_ = bots[bi];
		if      (dir == 'v') { pos_ += SOUTH; }
		else if (dir == '^') { pos_ += NORTH; }
		else if (dir == '<') { pos_ += WEST; }
		else if (dir == '>') { pos_ += EAST; }
		visited.insert(pos_.toLong());
		bi ^= 1; }

	cout << "2: " << sz(visited) << nl;
	return 0; }
