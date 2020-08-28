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

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
