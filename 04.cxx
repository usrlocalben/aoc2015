#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <iostream>
#include <optional>
#include <queue>
#include <string>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "third_party/md5.hxx"

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


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string line;
	getline(cin, line);

	string hex;
	stringstream ss;
	int p1val = -1;
	int p2val = -1;
	int val = 0;
	while (p1val==-1 || p2val==-1) {
		ss.str(string());
		ss << line;
		ss << val;
		hex = md5(ss.str());

		if (hex.substr(0,6) == "000000" && p2val==-1) {
			p2val = val; }
		if (hex.substr(0,5) == "00000" && p1val==-1) {
			p1val = val; }
		val++; }

	cout << "1: " << p1val << nl;
	cout << "2: " << p2val << nl;
	return 0; }
