#ifndef AITHREAD_H
#define AITHREAD_H

#include "base.h"
#include "../Board.h"
#include "Fubuki_macro.h"
#include <utility>

class Fubuki
{

	private:

		// 记录棋局轮次 和 经过计算得到的ai下一次落子位置
		int round;
		bool is_black;
		bool warned;
		Grid ai_next_move; // 未初始化

		int prev_score;

		// 棋盘的备份（为了更快读写）（初始化置0）
		Chessid mirror_board[GRID_N][GRID_N];

		/* 记录某条直线上的棋子，每2个bit表示一颗棋子（初始化置0）
		 *  列：最左的是第0列，每列靠上的是低位，扫描次数10
		 *  行：最上的是第0行，每行靠左的是低位，扫描次数10
		 *  左斜（左上右下）：最左下的是第0左斜列，靠左上的是低位，扫描次数与位置有关
		 *  右斜（左下右上）：最左上的是第0右斜列，靠右上的是低位，扫描次数与位置有关
		 */
		int col_chess[GRID_N];
		int row_chess[GRID_N];
		int left_chess[GRID_DN];
		int right_chess[GRID_DN];

		// 记录每条直线上的棋型，每 1 个 int 表示一条直线上的棋型（初始化置0）
		int col_type[GRID_N];
		int row_type[GRID_N];
		int left_type[GRID_DN];
		int right_type[GRID_DN];

		// 记录整个棋盘的棋型，每 1 个 int 表示一种棋型的个数（初始化置0）
		int all_type[CHESS_TYPE_N];

		// 棋型标志位映射表（初始化置0）
		int M_TABLE[MAX_INDEX_OF_M_TABLE];

		// 关键位置映射表（初始化置-1）
		char P4_KEY_POS_TABLE[MAX_INDEX_OF_M_TABLE];		// 冲四的关键点位置（落子成五：1个位置）
		char A3_KEY_POS_TABLE[MAX_INDEX_OF_M_TABLE][3];		// 活三的关键点位置（落子成活四/冲四：2+1=3个位置）
		char S3_KEY_POS_TABLE[MAX_INDEX_OF_M_TABLE][2];		// 眠三的关键点位置（落子成冲四：2个位置）

		// 获取斜列扫描次数映射表（初始化置0）
		int XY_TO_LEFT_COUNT[GRID_N][GRID_N];
		int XY_TO_RIGHT_COUNT[GRID_N][GRID_N];
		int L_TO_LEFT_COUNT[GRID_DN];
		int R_TO_RIGHT_COUNT[GRID_DN];

	public:
		// run函数
		std::pair<int, int> makeAction();

		Fubuki();

		// Fubuki初始化系统
		void initSystem();
		void setPlayer(Board::ChessPlayer player);

		// 初始化接口函数
		void initHashTable();
		void initBoard();
		void setIsBlack();
		void setNotBlack();
		void setNotWarned();
		void resetRound();

		// 棋盘接口函数
		void putChess(const int x, const int y, const Chessid id);
		void takeChess(const int x, const int y);
		bool win(void) const;
		bool lose(void) const;
		void printChessType();
		void algoDebuging(void) const;

		// 寻找敌方唯一的P4
		int findEnemyP4(Choice *choices_buffer, const Chessid cur_player) const;
		int findS3A3(Choice *choices_buffer, const Chessid cur_player) const;
		int findAllS3A3(Choice *choices_buffer, const Chessid cur_player) const;

	private:

		// 初始化函数：
		void initMTable();
		void initCountTable();

		// 基础函数：
		void updateChessType(const int x, const int y);

		// 估值函数：
		int evalBoard();
		int evalMinMaxPrior(const int x, const int y, const Chessid id) const;
		int evalKillPrior(const int x, const int y, const Chessid id) const;
		int evalKilledScore(Chessid cur_player, int depth) const;

		// 算法函数：
		int minMaxSearch(const Chessid cur_player, const int depth, int alpha, int beta);
		int killSearch(const Chessid cur_player, const int depth, int alpha, int beta);
		int resSearch(const Chessid cur_player, const int depth, int alpha, int beta);
		int getMinMaxSearchChoices(Choice *choices_buffer, Chessid cur_player) const;
		int getKillSearchChoices(Choice *choices_buffer, Chessid cur_player) const;
		void myQuickSort(Choice *a, int n) const;

		// 特殊局面函数：
		void firstRound();
		void secondRound();
		void highestPriorityAttack();
		void highestPriorityDefence();

	//signals:

	//	// 线程间信号传输
	//	void foundNextMove(const Grid &ai_next_move);
	//	void findingNextMove(const Grid &ai_next_move);
	//	void sweetWarning();

};

#endif // AITHREAD_H
