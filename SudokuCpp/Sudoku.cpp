#include <vector>
#include <set>

// �Ֆʂ�񎟌��x�N�g���ŕԂ�
using Field = std::vector<std::vector<int>>;

// ���Ƃ��������߂̃N���X
class Sudoku {
private:
	Field field;

public:
	// �R���X�g���N�^�i���m��}�X�̒l��-1�ŕ\���j
	Sudoku() : field(9, std::vector<int>(9, -1)) {}

	// field��Ԃ�
	const Field& get() {
		return field;
	}

	// �󂫃}�X��T���i���݂��Ȃ��ꍇ��false��Ԃ��j
	bool find_empty(int& x, int& y) {
		for (x = 0; x < 9; ++x)
			for (y = 0; y < 9; ++y)
				if (field[x][y] == -1)
					return true;
		return false;
	}

	// �}�X (x, y) �ɓ������I������Ԃ�
	std::set<int> find_choices(int x, int y) {
		std::set<int> can_use({ 1,2,3,4,5,6,7,8,9 });

		// �����s�ɓ������l�����邱�Ƃ͂ł��Ȃ�
		for (int i = 0; i < 9; ++i)
			if (field[x][i] != -1)
				can_use.erase(field[x][i]);
		
		// ������ɓ������l�����邱�Ƃ͂ł��Ȃ�
		for (int i = 0; i < 9; ++i)
			if (field[i][y] != -1)
				can_use.erase(field[i][y]);

		// �����u���b�N�ɓ������l�����邱�Ƃ͂ł��Ȃ�
		// �}�X (cx, cy) �̓}�X (x, y) ���܂ރu���b�N��
		// �����}�X��\��
		int cx = x / 3 * 3 + 1, cy = y / 3 * 3 + 1;
		for (int i = cx - 1; i <= cx + 1; ++i)
			for (int j = cy - 1; j <= cy + 1; ++j)
				if (field[i][j] != 1)
					can_use.erase(field[i][j]);

		// ���^�[��
		return can_use;
	}

	// �}�X (x, y) �ɐ��lval������
	void put(int x, int y, int val) {
		field[x][y] = val;
	}

	// �}�X (x, y) �̐��l���폜����
	void reset(int x, int y) {
		field[x][y] = -1;
	}
};
