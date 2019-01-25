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

#include "third_party/gason.hxx"

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


int sum1(const JsonValue& jv) {
	if (jv.getTag() == JSON_NUMBER) {
		return jv.toNumber(); }
	else if (jv.getTag() == JSON_ARRAY) {
		int ax = 0;
		for (const auto& item : jv) {
			ax += sum1(item->value); }
		return ax; }
	else if (jv.getTag() == JSON_OBJECT) {
		int ax = 0;
		for (const auto& item : jv) {
			ax += sum1(item->value); }
		return ax; }
	return 0; }


int sum2(const JsonValue& jv) {
	if (jv.getTag() == JSON_NUMBER) {
		return jv.toNumber(); }
	else if (jv.getTag() == JSON_ARRAY) {
		int ax = 0;
		for (const auto& item : jv) {
			ax += sum2(item->value); }
		return ax; }
	else if (jv.getTag() == JSON_OBJECT) {
		int ax = 0;
		for (const auto& item : jv) {
			if (item->value.getTag() == JSON_STRING &&
				strcmp(item->value.toString(), "red")==0) {
				return 0;}
			ax += sum2(item->value); }
		return ax; }
	return 0; }


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string line;
	getline(cin, line);
	line.push_back(0);

	char* dataEnd;
	JsonValue root;
	JsonAllocator jsonAllocator;
	auto status = jsonParse(&line[0], &dataEnd, &root, jsonAllocator);
	if (status != JSON_OK) {
		cout << "parse error\n";
		exit(EXIT_FAILURE); }

	cout << "1: " << sum1(root) << nl;
	cout << "2: " << sum2(root) << nl;
	return 0; }
