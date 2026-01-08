#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int count_island(vector<vector<char>>& grid) {
	int rows = grid.size();
	int cols = grid[0].size();
	if (rows = grid.size())return 0;
	int count = 0;
	for (int x = 0; x < rows; x++) {
		for(int y = 0; y < cols; y++) {
			if (grid[x][y] == '1') {
				count++;
				grid[x][y] = '0';
				queue<pair<int, int>> neighbour;
				neighbour.push({ x,y });

				while (!neighbour.empty()) {
					auto cur = neighbour.front();
					neighbour.pop();
					int row = cur.first;
					int col = cur.second;
					if (row - 1 >= 0 && grid[row - 1][col] == '1') { 
						neighbour.push({ row - 1,col }); 
						grid[row - 1][col] = '0';
					}if (row + 1 < rows && grid[row + 1][col] == '1') {
						neighbour.push({ row +1,col });
						grid[row+1 ][col] = '0';
					}
					if (col + 1 < cols && grid[row ][col+1] == '1') {
						neighbour.push({ row ,col + 1 });
						grid[row][col + 1] = '0';
					}
					if (col -1 >=0 && grid[row][col -1] == '1') {
						neighbour.push({ row ,col -1 });
						grid[row][col - 1] = '0';
					}
				}
			}
		}
	}
	return count;
}
//找到一个岛屿的 “起点”（某个 '1'），
// 然后沿着 “上下左右” 方向 “钻到底”，
// 把整个岛屿的所有 '1' 都标记为 '0'（表示已访问），
// 每找到一个起点就统计一个岛屿。
int count_ialand_dfs(vector<vector<char>>& grid) {
	int rows = grid.size();
	if (rows == 0)return 0;
	int cols = grid[0].size();
	int count = 0;

	for (int x = 0; x < rows; x++) {
		for (int y = 0; y < cols; y++) {
			if (grid[x][y] == '1') {
				count++;
				dfs(grid, x,y);
			}
		}
	}
	return count;
}
void dfs(vector<vector<char>>& grid, int x, int y) {
	int rows = grid.size();
	int cols = grid[0].size();

	grid[x][y] = 0;
	if (x- 1 >= 0 && grid[x - 1][y] == '1') {

		dfs(grid, x - 1, y);
	}
	if (x + 1 < rows && grid[x + 1][y] == '1') {
		dfs(grid, x+ 1, y);
	}
	if (x + 1 < cols && grid[x][y + 1] == '1') {
		dfs(grid, x, y + 1);
	}
	if (x - 1 >= 0 && grid[x][y - 1] == '1') {
		dfs(grid, x, y - 1);
	}
}