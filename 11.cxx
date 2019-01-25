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


struct NextPass {
	string findNext(const string& a) {
		ds = a;
		len = sz(a);
		auto result = proc(0, false, -1, -1);
		assert(result);
		return ds; }

	bool proc(int pos, const bool hasStraight, char chm2, char chm1) {
		if (pos == len) {
			if (!hasStraight) {
				return false; }
			//cout << ">>> " << ds << "\n";

			if (0) { //(ds == "ghjaabcc") {
			int pc = 0;
			forn(i, len-1) {
				cout << "[" << ds[i] << "," << ds[i+1] << "]";
				if (ds[i] == ds[i+1]) {
					pc++;
					cout << "EQ, pc now " << pc << "\n";
					i++;}}
			if (pc < 2) {
				return false; }
			} else {
			int pc = 0;
			//memset(&buf[0], 0, 26*sizeof(int));
			forn(i, len-1) {
				if (ds[i] == ds[i+1]) {
					pc++;
					i++;}}
			if (pc < 2) {
				return false; }}

			return true; }

		char& ch = ds[pos];
		while (ch<= 'z') {
			if (ch == 'i' || ch=='o' || ch=='l') goto loop;

			bool nowHasStraight = hasStraight;
			if (!hasStraight) {
				if (chm2+1 == chm1 && chm1+1 == ch) {
					nowHasStraight = true; }}
			bool ok = proc(pos+1, nowHasStraight, chm1, ch);
			if (ok) return true;
	
loop:
			ch++;
			for (int i=pos+1; i<len; i++) {
				ds[i] = 'a'; }}

		return false;}

	int len;
	array<int,26> buf;
	string ds;
	string p; };


struct NextPass2 {
	void init(const string& a) {
		ds = a;
		len = sz(a); }

	string next() {
		incr();
		auto result = proc(0, false, -1, -1);
		assert(result);
		return ds; }

	int incr(int pos=0) {
		auto& ch = ds[pos];
		if (pos == len-1) {
			ch++;
			if (ch > 'z') {
				ch = 'a';
				return 1; }
			return 0; }
		else {
			int carry = incr(pos+1);
			ch += carry;
			if (ch > 'z') {
				ch = 'a';
				return 1; }
			return 0; }}

	bool proc(int pos, const bool hasStraight, char chm2, char chm1) {
		if (pos == len) {
			if (!hasStraight) {
				return false; }
			//cout << ">>> " << ds << "\n";

			if (0) { //(ds == "ghjaabcc") {
			int pc = 0;
			forn(i, len-1) {
				cout << "[" << ds[i] << "," << ds[i+1] << "]";
				if (ds[i] == ds[i+1]) {
					pc++;
					cout << "EQ, pc now " << pc << "\n";
					i++;}}
			if (pc < 2) {
				return false; }
			} else {
			int pc = 0;
			//memset(&buf[0], 0, 26*sizeof(int));
			forn(i, len-1) {
				if (ds[i] == ds[i+1]) {
					pc++;
					i++;}}
			if (pc < 2) {
				return false; }}

			return true; }

		char& ch = ds[pos];
		while (ch<= 'z') {
			if (ch == 'i' || ch=='o' || ch=='l') goto loop;

			bool nowHasStraight = hasStraight;
			if (!hasStraight) {
				if (chm2+1 == chm1 && chm1+1 == ch) {
					nowHasStraight = true; }}
			bool ok = proc(pos+1, nowHasStraight, chm1, ch);
			if (ok) return true;
	
loop:
			ch++;
			for (int i=pos+1; i<len; i++) {
				ds[i] = 'a'; }}

		return false;}

	int len;
	array<int,26> buf;
	string ds;
	string p; };


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string line;
	getline(cin, line);

	{NextPass np;
	auto s = np.findNext(line);
	s = np.findNext(s);
	//auto s = np.findNext("abcdefgh");
	//auto s = np.findNext("ghijklmn");
	cout << "1: " << s << nl;}


	{NextPass2 np;
	np.init(line);
	np.next();
	auto s = np.next();
	//auto s = np.findNext("abcdefgh");
	//auto s = np.findNext("ghijklmn");
	cout << "2: " << s << nl;}

	return 0; }
