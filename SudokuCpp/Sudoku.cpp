#include <iostream>
#include <vector>
#include <set>
#include <string>

// �Ֆʂ�񎟌��x�N�g���ŕ\��
using Field = std::vector<std::vector<int>>;

// ���ׂĂ̒l
const std::set<int> all_numbers({ 1,2,3,4,5,6,7,8,9 });

// ���Ƃ��������߂̃N���X
class Sudoku {
private:
	// ���ƔՖ�
	Field field;

	// nums[x][y][v] �� �}�X (x, y) ���܂ލs�E��E�u���b�N�ɒl v+1 �������邩
	std::vector<std::vector<std::vector<int>>> nums;

	// choices[x][y] �� �}�X (x, y) �ɓ���邱�Ƃ̂ł���I����
	std::vector<std::vector<std::set<int>>> choices;

public:
	// �R���X�g���N�^�i���m��}�X�̒l��-1�ŕ\���j
	Sudoku() : field(9, std::vector<int>(9, -1)),
		nums(9, std::vector<std::vector<int>>(9, std::vector<int>(9, 0))),
		choices(9, std::vector<std::set<int>>(9, all_numbers)) {}

	// field��Ԃ�
	const Field& get() {
		return field;
	}

	// �󂫃}�X�̂����A�I�������ł����Ȃ��}�X��T��
	bool find_empty(int& x, int& y) {
		size_t min_num_choices = 10;
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				if (field[i][j] != -1) continue;
				if (min_num_choices > choices[i][j].size()) {
					min_num_choices = choices[i][j].size();
					x = i;
					y = j;
				}
			}
		}
		// ���݂��Ȃ��ꍇ�� false
		if (min_num_choices == 10) return false;
		else return true;

	}

	// �}�X (x, y) �ɓ������I������Ԃ�
	std::set<int> find_choices(int x, int y) {
		return choices[x][y];
	}

	void print() {
		for (int x = 0; x < 9; ++x) {
			for (int y = 0; y < 9; ++y) {
				if (field[x][y] == -1) std::cout << "*";
				else std::cout << field[x][y];
				std::cout << " ";
			}
			std::cout << std::endl;
		}
	}

	// �}�X (x, y) �ɐ��l val �����邱�Ƃɂ��}�X (x2, y2) �ւ̉e��
	void put_detail(int x, int y, int val, int x2, int y2) {
		if (x == x2 && y == y2) return;

		// (x2, y2) �ɂ��łɒl�������Ă���ꍇ�͉������Ȃ�
		if (field[x2][y2] != -1) return;

		// ����܂� (x2, y2) �̉e���͈͂ɒl val ���Ȃ������ꍇ�͑I�������珜��
		if (nums[x2][y2][val - 1] == 0) choices[x2][y2].erase(val);

		// nums ���X�V
		++nums[x2][y2][val - 1];
	}

	// �}�X (x, y) �ɐ��l val ������
	void put(int x, int y, int val) {
		// ���l������
		field[x][y] = val;

		// �}�X (x, y) ���܂ލs�E��E�u���b�N�ւ̉e�����X�V����
		for (int i = 0; i < 9; ++i) put_detail(x, y, val, x, i);
		for (int i = 0; i < 9; ++i) put_detail(x, y, val, i, y);
		int cx = x / 3 * 3 + 1, cy = y / 3 * 3 + 1;
		for (int i = cx - 1; i <= cx + 1; ++i)
			for (int j = cy - 1; j <= cy + 1; ++j)
				put_detail(x, y, val, i, j);
	}

	// �}�X (x, y) ���琔�l val �������������Ƃɂ��}�X (x2, y2) �ւ̉e��
	void reset_detail(int x, int y, int val, int x2, int y2) {
		if (x == x2 && y == y2) return;

		// (x2, y2) �ɂ��łɒl�������Ă���ꍇ�͉������Ȃ�
		if (field[x2][y2] != -1) return;

		// nums ���X�V
		--nums[x2][y2][val - 1];

		// nums �� 0 �ɂȂ�ꍇ�͑I�����ɕ�������
		if (nums[x2][y2][val - 1] == 0) choices[x2][y2].insert(val);
	}

	// �}�X (x, y) �̐��l���폜����
	void reset(int x, int y) {
		// �}�X (x, y) ���܂ލs�E��E�u���b�N�ւ̉e�����X�V����
		int val = field[x][y];
		for (int i = 0; i < 9; ++i) reset_detail(x, y, val, x, i);
		for (int i = 0; i < 9; ++i) reset_detail(x, y, val, i, y);
		int cx = x / 3 * 3 + 1, cy = y / 3 * 3 + 1;
		for (int i = cx - 1; i <= cx + 1; ++i)
			for (int j = cy - 1; j <= cy + 1; ++j)
				reset_detail(x, y, val, i, j);

		// ���l����������
		field[x][y] = -1;
	}

	// ��ӂɌ��܂�}�X�𖄂߂Ă���
	void process() {
		// ���l 1, 2, ..., 9 �ɂ��ď��ɏ�������
		for (int val = 1; val <= 9; ++val) {
			// x �s�ڂɂ���
			for (int x = 0; x < 9; ++x) {
				bool exist = false;
				std::vector<int> can_enter;
				for (int y = 0; y < 9; ++y) {
					if (field[x][y] == val) exist = true;
					if (field[x][y] == -1
						&& choices[x][y].count(val)) {
						can_enter.push_back(y);
					}
				}
				// val ��������}�X�ڂ�������Ȃ�Γ����
				if (!exist && can_enter.size() == 1) {
					int y = can_enter[0];
					put(x, y, val);
				}
			}

			// y ��ڂɂ���
			for (int y = 0; y < 9; ++y) {
				bool exist = false;
				std::vector<int> can_enter;
				for (int x = 0; x < 9; ++x) {
					if (field[x][y] == val) exist = true;
					if (field[x][y] == -1
						&& choices[x][y].count(val)) {
						can_enter.push_back(x);
					}
				}
				// val ��������}�X�ڂ�������Ȃ�Γ����
				if (!exist && can_enter.size() == 1) {
					int x = can_enter[0];
					put(x, y, val);
				}
			}

			// �e�u���b�N�ɂ���
			for (int bx = 0; bx < 3; ++bx) {
				for (int by = 0; by < 3; ++by) {
					bool exist = false;
					std::vector<std::pair<int, int>> can_enter;
					for (int x = bx * 3; x < (bx + 1) * 3; ++x) {
						for (int y = by * 3; y < (by + 1) * 3; ++y) {
							if (field[x][y] == val) exist = true;
							if (field[x][y] == -1
								&& choices[x][y].count(val)) {
								can_enter.emplace_back(x, y);
							}
						}
					}
					// val ��������}�X�ڂ�������Ȃ�Γ����
					if (!exist && can_enter.size() == 1) {
						int x = can_enter[0].first;
						int y = can_enter[0].second;
						put(x, y, val);
					}
				}
			}
		}
	}
};
