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

#include <intrin.h> // popcnt

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


#define OPCODE_TABLE(XX)  \
	XX(inc, "inc") \
	XX(hlf, "hlf") \
	XX(tpl, "tpl") \
	XX(jmp, "jmp") \
	XX(jie, "jie") \
	XX(jio, "jio")

enum Opcode {
#define XX(op, str) op,
	OPCODE_TABLE(XX)
#undef XX
};

unordered_map<string, Opcode> decoder = {
#define XX(op, str) {str, op},
	OPCODE_TABLE(XX)
#undef XX
};

Opcode decodeOpcodeOrFail(const string& s) {
	if (auto search = decoder.find(s); search!=decoder.end()) {
		return search->second; }
	else {
		cout << "unknown opcode \"" << s << "\"" << nl;
		exit(EXIT_FAILURE); }}


struct Ins {
	Opcode op;
	int p1;
	int p2; };

vs _dt;
Ins decodeIns(const string& s) {
	_dt = split(s, ' ');
	const auto op = decodeOpcode(_dt[0]);
	switch (op) {
		case inc:
		case hlf:
		case tpl:
			return Ins{ op, _dt[1][0]-'a' };
		case jio:
		case jie:
			return Ins{ op, _dt[1][0]-'a', stoi(_dt[2]) };
		case jmp:
			return Ins{ op, stoi(_dt[1]) }; }}


struct VFC {

	void runUntilHalt() {
		while (0 <= pc && pc < sz(code)) {
			//cout << "." << flush;
			runOne(); }}

	void runOne() {
		//cout << "PC: " << pc << ", a:" << reg[0] << ", b:" << reg[1] << nl;
		const auto& ins = code[pc];
		int nextPC = pc+1;
		switch (ins.op) {
		case inc:
			reg[ins.p1]++;
			break;
		case hlf:
			reg[ins.p1] >>= 1;
			break;
		case tpl:
			reg[ins.p1] *= 3;
			break;
		case jio:
			if (reg[ins.p1] == 1) {
				nextPC = pc + ins.p2; }
		 	break;
		case jie:
			if (reg[ins.p1] % 2 == 0) {
				nextPC = pc + ins.p2; }
		 	break;
		case jmp:
			nextPC = pc + ins.p1;
			break; }
		pc = nextPC;}

	void reset() {
		pc = 0;
		reg[0] = 0;
		reg[1] = 0; }

	vector<Ins> code;
	int pc = 0;
	array<int, 2> reg = { 0, 0 }; };

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string line;
	VFC cpu;
	while (getline(cin, line)) {
		cpu.code.emplace_back(decodeIns(line)); }

	// part 1
	cpu.runUntilHalt();
	cout << "1: " << cpu.reg[1] << nl;

	// part 2
	cpu.reset();
	cpu.reg[0] = 1;
	cpu.runUntilHalt();
	cout << "2: " << cpu.reg[1] << nl;
	return 0; }
