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


struct Player {
	int hp;
	int damage;
	int mana;
	int armor;
};

int bossDamage;
int bossHP;

int solve(bool hard, array<int,2> hp, const int ai, int mana, int tShield=0, int tPoison=0, int tRecharge=0) {
	int armor = 0;
	if (hard) {
		hp[0]--; }

	if (tShield > 0) {
		armor += 7;
		tShield--; }

	if (tPoison > 0) {
		hp[1] -= 3;
		tPoison--; }

	if (tRecharge > 0) {
		mana += 101;
		tRecharge--; }

	if (hp[0] <= 0) {
		return -1; }
	if (hp[1] <= 0) {
		return 0; }

	if (ai == 1) {
		// boss turn
		int ed = max(bossDamage - armor, 1);
		hp[0] -= ed;
		return solve(hard, hp, 0, mana, tShield, tPoison, tRecharge); }

	int best = oo;
	for (int i=0; i<5; i++) {
		int cost;
		int result = -1;
		auto thp = hp;
		switch (i) {
		case 0:
			// magic missile
			if (mana >= 53) {
				cost = 53;
				thp[1] -= 4;
				result = solve(hard, thp, 1, mana-cost, tShield, tPoison, tRecharge); }
			break;
		case 1:
			// drain
			if (mana >= 73) {
				cost = 73;
				thp[0] += 2;
				thp[2] -= 2;
				result = solve(hard, thp, 1, mana-cost, tShield, tPoison, tRecharge); }
			break;
		case 2:
			// shield
			if (mana >= 113 && tShield==0) {
				cost = 113;
				result = solve(hard, thp, 1, mana-cost, 6, tPoison, tRecharge); }
			break;
		case 3:
			// poison
			if (mana >= 173 && tPoison==0) {
				cost = 173;
				result = solve(hard, thp, 1, mana-cost, tShield, 6, tRecharge); }
			break;
		case 4:
			// recharge
			if (mana >= 229 && tRecharge==0) {
				cost = 229;
				result = solve(hard, thp, 1, mana-cost, tShield, tPoison, 5); }
			break;}
		if (result > -1) {
			best = min(best, cost+result); }}

	return (best == oo ? -1 : best);}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string line;
	getline(cin, line);
	bossHP = stoi(split(line, ' ')[2]);
	getline(cin, line);
	bossDamage = stoi(split(line, ' ')[1]);

	// part 1
	int minMana = solve(false, {50, bossHP}, 0, 500);
	cout << "1: " << minMana << nl;

	// part 2
	minMana = solve(true, {50, bossHP}, 0, 500);
	cout << "2: " << minMana << nl;
	return 0; }
