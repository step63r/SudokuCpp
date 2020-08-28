#include <vector>
#include <set>

// 盤面を二次元ベクトルで返す
using Field = std::vector<std::vector<int>>;

// 数独を解くためのクラス
class Sudoku {
private:
	Field field;

public:
	// コンストラクタ（未確定マスの値を-1で表す）
	Sudoku() : field(9, std::vector<int>(9, -1)) {}

	// fieldを返す
	const Field& get() {
		return field;
	}

	// 空きマスを探す（存在しない場合はfalseを返す）
	bool find_empty(int& x, int& y) {
		for (x = 0; x < 9; ++x)
			for (y = 0; y < 9; ++y)
				if (field[x][y] == -1)
					return true;
		return false;
	}

	// マス (x, y) に入れられる選択肢を返す
	std::set<int> find_choices(int x, int y) {
		std::set<int> can_use({ 1,2,3,4,5,6,7,8,9 });

		// 同じ行に同じ数値を入れることはできない
		for (int i = 0; i < 9; ++i)
			if (field[x][i] != -1)
				can_use.erase(field[x][i]);
		
		// 同じ列に同じ数値を入れることはできない
		for (int i = 0; i < 9; ++i)
			if (field[i][y] != -1)
				can_use.erase(field[i][y]);

		// 同じブロックに同じ数値を入れることはできない
		// マス (cx, cy) はマス (x, y) を含むブロックの
		// 中央マスを表す
		int cx = x / 3 * 3 + 1, cy = y / 3 * 3 + 1;
		for (int i = cx - 1; i <= cx + 1; ++i)
			for (int j = cy - 1; j <= cy + 1; ++j)
				if (field[i][j] != 1)
					can_use.erase(field[i][j]);

		// リターン
		return can_use;
	}

	// マス (x, y) に数値valを入れる
	void put(int x, int y, int val) {
		field[x][y] = val;
	}

	// マス (x, y) の数値を削除する
	void reset(int x, int y) {
		field[x][y] = -1;
	}
};
