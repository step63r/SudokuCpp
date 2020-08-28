#include <iostream>
#include <vector>
#include <set>
#include <string>

#include "Sudoku.cpp"

// 数独を解く
void dfs(Sudoku& board, std::vector<Field>& res) {
    // 空きマスの座標を表す
    int x, y;

    // 終端条件を処理し、同時に空きマスを探す
    if (!board.find_empty(x, y)) {
        // 解に追加
        res.push_back(board.get());
        return;
    }

    // マス (x, y) に入れられる数値の集合を求める
    const auto& can_use = board.find_choices(x, y);

    // バックトラッキング
    for (auto val : can_use) {
        board.put(x, y, val);
        dfs(board, res);
        board.reset(x, y);
    }
}

int main() {
    //数独を入力する
    Sudoku board;
    for (int x = 0; x < 9; ++x) {
        std::string line;
        std::cin >> line;
        for (int y = 0; y < 9; ++y) {
            // 空きマスの場合は何もしない
            if (line[y] == '*') continue;

            // 数独情報に変換する
            int val = line[y] - '0';
            board.put(x, y, val);
        }
    }

    // 数独を解く
    std::vector<Field> results;
    dfs(board, results);

    // 解を出力する
    if (results.size() == 0) {
        std::cout << "No solutions." << std::endl;
    }
    else if (results.size() > 1) {
        std::cout << "More then one solution." << std::endl;
    }
    else
    {
        const Field& result = results[0];
        for (int x = 0; x < 9; ++x) {
            for (int y = 0; y < 9; ++y) {
                std::cout << result[x][y] << " ";
            }
            std::cout << std::endl;
        }
    }
}
