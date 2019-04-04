// https://codeforces.com/problemset/problem/611/C?locale=en
/*

The solution for a single line can be computed from solutions on the prefixes
by difference: sol(A[i:j]) = sol(A[0:j]) - sol(A[0:i]) where A[i:j] includes
both A[i] and A[j].

So the solution on a generic rectangle considering only horizontal dominos can
be computed summing A[i:j] on the rows, performed in constant time by difference
storing prefix sums. Solution with vertical dominos is the same.

*/

#include <bits/stdc++.h>

using namespace std;

// The query gives grids positions from 1 to h/w, and having 0 simplifies
// the subtraction of res[i - 1]
uint_fast32_t hor[502][502] = {0};
uint_fast32_t ver[502][502] = {0};

int main() {
	ios_base::sync_with_stdio(false);

	uint_fast16_t h, w;
	cin >> h >> w;
	bool grid[h][w];
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			char c;
			cin >> c;
			grid[i][j] = c == '.' ? true : false;
		}
	}

	// for (int i = 0; i < h + 1; ++i) {
	// 	hor[i][0] = ver[i][0] = 0;
	// }
	// for (int j = 0; j < w + 1; ++j) {
	// 	hor[0][j] = ver[0][j] = 0;
	// }

	for (int i = 0; i < h; ++i) {
		hor[i + 1][1] = 0;
		for (int j = 1; j < w; ++j) {
			hor[i + 1][j + 1] = hor[i + 1][j] + (grid[i][j] && grid[i][j - 1] ? 1 : 0);
		}
	}
	// Makes hor vertical prefix sums
	for (int i = 0; i < h; ++i) {
		for (int j = 1; j < w; ++j) {
			hor[i + 1][j + 1] += hor[i][j + 1];
			// cout << "hor[" << i << ", " << j << "] = " << hor[i + 1][j + 1] << "\n";
		}
	}

	for (int j = 0; j < w; ++j) {
		ver[1][j + 1] = 0;
		for (int i = 1; i < h; ++i) {
			ver[i + 1][j + 1] = ver[i][j + 1] + (grid[i][j] && grid[i - 1][j] ? 1 : 0);
		}
	}
	// Makes ver horizontal prefix sums
	for (int i = 0; i < h; ++i) {
		for (int j = 1; j < w; ++j) {
			ver[i + 1][j + 1] += ver[i + 1][j];
		}
	}


	uint_fast16_t u;
	cin >> u;
	for (int u1 = 0; u1 < u; ++u1) {
		uint_fast16_t r1, r2, c1, c2;
		cin >> r1 >> c1 >> r2 >> c2;
		uint_fast32_t hsol = hor[r2][c2] + hor[r1 - 1][c1] - hor[r2][c1] - hor[r1 - 1][c2];
		uint_fast32_t vsol = ver[r2][c2] + ver[r1][c1 - 1] - ver[r2][c1 - 1] - ver[r1][c2];
		cout << (hsol + vsol) << "\n";
	}

	return 0;
}
