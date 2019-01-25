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


int target;
vi nums;
int allmask;
using ill = pair<int, ll>;
const ill MISS{-1,-1};


// part 1
ill p1_f1(int amt, int start, int sz, ll prod, int usemask);
bool p1_f2(int amt, int start, int usemask);
bool p1_f3(int amt, int usemask);
ill p1_f1(const int amt, const int start=0, const int sz=0, const ll prod=1, const int usemask=0) {
	if (amt == 0) {
//		cout << sz << ", " << prod << ", " << hex << usemask << dec << nl;
		int success = p1_f2(target, 0, usemask);
		if (success) {
			return {sz, prod}; }
		else {
			return MISS; }}

	ill best{oo, oo};
	for (int ni=start; ni<sz(nums); ni++) {
		const int bit = 1 << ni;
		const int value = nums[ni];
		if (usemask & bit) continue;
		if (amt-value < 0) continue;
		const auto result = p1_f1(amt-value, ni+1, sz+1, prod*value, usemask|bit);
		if (result != MISS) {
			best = min(best, result); }}

	return (best.first == oo ? MISS : best);}


bool p1_f2(const int amt, const int start, const int usemask) {
	if (amt == 0) {
		return p1_f3(target, usemask); }

	for (int ni=start; ni<sz(nums); ni++) {
		const int bit = 1 << ni;
		const int value = nums[ni];
		if (usemask & bit) continue;
		if (value > amt) continue;
		if (amt-value < 0) continue;
		const auto success = p1_f2(amt-value, ni+1, usemask|bit);
		if (success) {
			return true;}}
	return false; }


bool p1_f3(int amt, const int usemask) {
	int avail = usemask^allmask;
	forn(ni,sz(nums)) {
		const int bit = 1<<ni;
		if (usemask&bit) continue;
		amt -= nums[ni]; }
	return amt == 0; }


// part 2
ill p2_f1(int amt, int start, int sz, ll prod, int usemask);
bool p2_f2(int amt, int start, int usemask);
bool p2_f3(int amt, int start, int usemask);
bool p2_f4(int amt, int usemask);
ill p2_f1(const int amt, const int start=0, const int sz=0, const ll prod=1, const int usemask=0) {
	if (amt == 0) {
//		cout << sz << ", " << prod << ", " << hex << usemask << dec << nl;
		int success = p2_f2(target, 0, usemask);
		if (success) {
			return {sz, prod}; }
		else {
			return MISS; }}

	ill best{oo, oo};
	for (int ni=start; ni<sz(nums); ni++) {
		const int bit = 1 << ni;
		const int value = nums[ni];
		if (usemask & bit) continue;
		if (amt-value < 0) continue;
		const auto result = p2_f1(amt-value, ni+1, sz+1, prod*value, usemask|bit);
		if (result != MISS) {
			best = min(best, result); }}

	return (best.first == oo ? MISS : best);}


bool p2_f2(const int amt, const int start, const int usemask) {
	if (amt == 0) {
		return p2_f3(target, 0, usemask); }

	for (int ni=start; ni<sz(nums); ni++) {
		const int bit = 1 << ni;
		const int value = nums[ni];
		if (usemask & bit) continue;
		if (value > amt) continue;
		if (amt-value < 0) continue;
		const auto success = p2_f2(amt-value, ni+1, usemask|bit);
		if (success) {
			return true;}}
	return false; }

bool p2_f3(const int amt, const int start, const int usemask) {
	if (amt == 0) {
		return p2_f4(target, usemask); }

	for (int ni=start; ni<sz(nums); ni++) {
		const int bit = 1 << ni;
		const int value = nums[ni];
		if (usemask & bit) continue;
		if (value > amt) continue;
		if (amt-value < 0) continue;
		const auto success = p2_f3(amt-value, ni+1, usemask|bit);
		if (success) {
			return true;}}
	return false; }


bool p2_f4(int amt, const int usemask) {
	int avail = usemask^allmask;
	forn(ni,sz(nums)) {
		const int bit = 1<<ni;
		if (usemask&bit) continue;
		amt -= nums[ni]; }
	return amt == 0; }


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string line;
	int nsum = 0;
	while (getline(cin, line)) {
		int val = stoi(line);
		nsum += val;
		nums.emplace_back(val); }
	assert(nsum%3==0);
	target = nsum/3;
	allmask = (1<<sz(nums))-1;
	sort(begin(nums), end(nums), [](auto a, auto b){return b<a;});

	auto best = p1_f1(target);
	cout << "1: " << best.second << nl;

	target = nsum/4;
	best = p2_f1(target);
	cout << "2: " << best.second << nl;
	return 0; }
