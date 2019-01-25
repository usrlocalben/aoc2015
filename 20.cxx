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


int hp1(int num) {
	int ax = 0;
	for (int i=1; i<=sqrt(num); i++) {
		if (num%i == 0) {
			if (num/i == i) {
				ax += (i*10); }
			else {
				ax += (i*10);
				ax += ((num/i)*10);}}}
	return ax;}


vi dcnt;
int hp2(int num) {
	int ax = 0;
	int f;
	for (int i=1; i<=sqrt(num); i++) {
		if (num%i == 0) {
			if (num/i == i) {
				f = i;
				if (dcnt[f] < 50) { ax += f*11; dcnt[f]++; }
				}
			else {
				f = i;
				if (dcnt[f] < 50) { ax += f*11; dcnt[f]++; }
				f = num/i;
				if (dcnt[f] < 50) { ax += f*11; dcnt[f]++; }
				}}}
	return ax;}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int target;
	cin >> target;

	int hn;
	for (hn=1; hp1(hn)<target; hn++);
	cout << "1: " << hn << nl;


	dcnt.resize(1000000*10, 0);
	for (hn=1; hp2(hn)<target; hn++);
	cout << "2: " << hn << nl;
	return 0; }
