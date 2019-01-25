#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <iostream>
#include <numeric>
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


enum Op {
	AND, OR, NOT, RSHIFT, LSHIFT, COPY };

struct Node {
	Op op;
	string arg1;
	string arg2;
	optional<uint16_t> cache = {};};

bool swa(const string& s) {
	return (s[0]>='a' && s[0]<='z'); }

using targetmap = unordered_map<string, Node>;

uint16_t teval(targetmap& targets, const string& target) {
	if (target == "") {
		return 0;}
	if (!swa(target)) {
		return stoi(target); }

	auto search = targets.find(target);
	if (search == targets.end()) {
		cout << "target [" << target << "] not found?\n";
		exit(EXIT_FAILURE); }
	auto& todo = search->second;
	if (todo.cache.has_value()) {
		return todo.cache.value();}

	uint16_t ax = teval(targets, todo.arg1);
	uint16_t bx = teval(targets, todo.arg2);
	uint16_t output;
	switch (todo.op) {
	case Op::COPY: output = ax; break;
	case Op::NOT: output = ~ax; break;
	case Op::LSHIFT: output = ax << bx; break;
	case Op::RSHIFT: output = ax >> bx; break;
	case Op::AND: output = ax & bx; break;
	case Op::OR: output = ax | bx; break;
	default:
		cout << "wtf?\n";
		exit(EXIT_FAILURE); }
	todo.cache = output;
	return output; }


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	targetmap targets;

	string line;
	vs seg;
	while (getline(cin, line)) {
		seg = split(line, ' ');
		if (sz(seg) == 3) {
			// zz -> o
			// 9999 -> o
			targets[seg[2]] = Node{ Op::COPY, seg[0], "" }; }
		else if (sz(seg) == 4) {
			// NOT zz -> o
			targets[seg[3]] = Node{ Op::NOT, seg[1], "" }; }
		else if (sz(seg) == 5) {
			// <n|zz> {AND,OR,{L,R}SHIFT} <n|zz> -> o
			if (seg[1] == "AND") {
				targets[seg[4]] = Node{ Op::AND, seg[0], seg[2] }; }
			else if (seg[1] == "OR") {
				targets[seg[4]] = Node{ Op::OR, seg[0], seg[2] }; }
			else if (seg[1] == "RSHIFT") {
				targets[seg[4]] = Node{ Op::RSHIFT, seg[0], seg[2] }; }
			else if (seg[1] == "LSHIFT") {
				targets[seg[4]] = Node{ Op::LSHIFT, seg[0], seg[2] }; }
			else {
				cout << "unknown op [" << seg[1] << "]\n";
				exit(EXIT_FAILURE); }}
		else {
			cout << "unknown seg sz " << sz(seg) << "\n";
			cout << "[" << line << "]\n";
			exit(EXIT_FAILURE); }}

	uint16_t value = teval(targets, "a");
	cout << "1: " << value << nl;

	// part 2	
	for (auto& t : targets) {
		t.second.cache = {}; }
	targets["b"].cache = value;
	value = teval(targets, "a");
	cout << "2: " << value << nl;
	return 0; }
