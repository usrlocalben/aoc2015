#include <algorithm>
#include <array>
#include <cassert>
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


int as(const string& s) {
	int c = 0;
	forn(i,sz(s)) {
		if (i==0) continue;
		if (i==sz(s)-1) continue;
		if (s[i] == '\\') {
			if (s[i+1] == 'x') {
				i += 3; }
			else {
				i++;}}
		c++; }
	return c;}


int bs(const string& s) {
	int c = 0;
	forn(i,sz(s)) {
		if (i==0) c += 2;
		if (i==sz(s)-1) c += 2;
		if (s[i] == '\\') {
			if (s[i+1] == 'x') {
				i += 3;
				c += 4;
			}
			else {
				c+=3;
				i++;}}
		c++; }
	return c;}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	/*
	cout << as("\"\"") << "\n";
	cout << as("\"abc\"") << "\n";
	cout << as("\"aaa\\\"aaa\"") << "\n";
	cout << as("\"\\x27\"") << "\n";
	return 0;*/

	/*cout << bs("\"\"") << "\n";
	cout << bs("\"abc\"") << "\n";
	cout << bs("\"aaa\\\"aaa\"") << "\n";
	cout << bs("\"\\x27\"") << "\n";
	return 0;*/

	int escapedsize = 0;
	int memsize = 0;
	int bigsize = 0;
	string line;
	while (getline(cin, line)) {
		escapedsize += sz(line);
		memsize += as(line);
		bigsize += bs(line); }

	cout << "1: " << (escapedsize-memsize) << nl;
	cout << "2: " << (bigsize-escapedsize) << nl;
	return 0; }
