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


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string line;
	getline(cin, line);

	int sum = accumulate(begin(line), end(line),
	                     0, [](auto ax, auto ch) { return ax + (ch=='('?1:-1); });
	cout << "1: " << sum << nl;

	int ax = 0;
	int pos = 0;
	for (const auto ch : line) {
		pos++;
		ax += (ch=='('?1:-1);
		if (ax < 0) {
			break;}}
	cout << "2: " << pos << nl;
	return 0; }
