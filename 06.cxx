#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <iostream>
#include <numeric>
#include <optional>
#include <queue>
#include <string>
#include <sstream>
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

ivec2 vmin(ivec2 a, ivec2 b) { return ivec2{ min(a.x, b.x), min(a.y, b.y) }; }
ivec2 vmax(ivec2 a, ivec2 b) { return ivec2{ max(a.x, b.x), max(a.y, b.y) }; }

ostream& operator<<(ostream& stream, ivec2 item) {
	stream << "(" << item.x << ", " << item.y << ")";
	return stream; }

ivec2 operator-(ivec2 a, ivec2 b) { return ivec2{ a.x-b.x, a.y-b.y }; }
ivec2 operator+(ivec2 a, ivec2 b) { return ivec2{ a.x+b.x, a.y+b.y }; }
ivec2 operator*(ivec2 a, ivec2 b) { return ivec2{ a.x*b.x, a.y*b.y }; }
bool operator==(ivec2 a, ivec2 b) { return (a.x==b.x && a.y==b.y); }

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


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	vs segments;
	string line;
	vs lines;
	while (getline(cin, line)) {
		lines.emplace_back(line); }

	// part 1
	vs nums;
	vi lights(1000*1000, 0);
	for (auto line : lines) {
		int op = 0;
		int arg = 0;
		if (consumePrefix(line, "turn on ")) {
			op = 1;
			arg = 1; }
		else if (consumePrefix(line, "turn off ")) {
			op = 1;
			arg = 0; }
		else if (consumePrefix(line, "toggle ")) {
			op = 2; }
		else {
			cout << "wtf? " << line << nl;
			exit(EXIT_FAILURE); }

		segments = split(line, ' ');
		auto lt = segments[0];
		auto rb = segments[2];
		nums = split(lt, ',');
		ivec2 leftTop{ stoi(nums[0]), stoi(nums[1]) };
		nums = split(rb, ',');
		ivec2 rightBottom{ stoi(nums[0]), stoi(nums[1]) };

		//cout << op << "," << amt << "," << leftTop << " -> " << rightBottom << "\n";
		for (int yy=leftTop.y; yy<=rightBottom.y; yy++) {
			for (int xx=leftTop.x; xx<=rightBottom.x; xx++) {
				auto& cell = lights[yy*1000+xx];
				if (op == 1) {
					cell = arg;}
				else {
					cell = (cell ? 0 : 1); }}}}

	int cnt = accumulate(begin(lights), end(lights),
	                     0, [](int ax, auto l) { return ax + (l?1:0); });
	cout << "1: " << cnt << nl;


	lights.clear();
	lights.resize(1000*1000, 0);
	for (auto line : lines) {
		int op = 0;
		int arg = 0;
		if (consumePrefix(line, "turn on ")) {
			op = 1;
			arg = 1; }
		else if (consumePrefix(line, "turn off ")) {
			op = 1;
			arg = -1; }
		else if (consumePrefix(line, "toggle ")) {
			op = 2; }
		else {
			cout << "wtf? " << line << "\n";
			exit(EXIT_FAILURE); }

		segments = split(line, ' ');
		auto lt = segments[0];
		auto rb = segments[2];
		nums = split(lt, ',');
		ivec2 leftTop{ stoi(nums[0]), stoi(nums[1]) };

		nums = split(rb, ',');
		ivec2 rightBottom{ stoi(nums[0]), stoi(nums[1]) };

		//cout << op << "," << amt << "," << leftTop << " -> " << rightBottom << "\n";
		for (int yy=leftTop.y; yy<=rightBottom.y; yy++) {
			for (int xx=leftTop.x; xx<=rightBottom.x; xx++) {
				auto& cell = lights[yy*1000+xx];
				if (op == 1) {
					cell = max(0, cell + arg);}
				else {
					cell += 2; }}} }

	int ax = accumulate(begin(lights), end(lights),
	                    0, [](int ax, auto l) { return ax + l; });
	cout << "2: " << ax << nl;
	return 0; }
