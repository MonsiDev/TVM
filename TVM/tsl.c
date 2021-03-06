#include <stdio.h>
#include "tsl.h"

/*
TvmStandartLib v0.3.2
������� ���������� TVM
10.03.2019
by Centrix
*/

int jump(int num) {
	unsigned int i = 0;
	while (memory[i] != end) {
		if (memory[i] == num) {
			return i;
		}
		i++;
	}
	return 0;
}

int gotoMain() {
	unsigned int i = 0;
	while (memory[i] != MAIN) {
		i++;
	}
	return i;
}

void detcoor(int rtype) {
	indxX = rtype / 10;
	indxY = rtype % 10;
}

void detcoorv(int rtype, int* x, int* y) {
	*x = rtype / 10;
	*y = rtype % 10;
}

void clear(int endpoint) {
	int i = 0;
	while (i != endpoint) {
		memory[i] = nil;
	}
}

void memInter() {
	while (memory[cell] != end) {
		if (cell == 0) {
			cell = gotoMain();
		}
		switch (memory[cell])
		{
		case CRG: {
			if (memory[cell + 1] == STDI) {
				indxX = memory[cell + 2];
				cell += 2;
			}
			else if (memory[cell + 1] == STDA) {
				detcoor(memory[cell + 2]);
				cell += 2;
			}
			break;
		}
		case CRC: {
			if (memory[cell + 1] == STDI) {
				indxY = memory[cell + 2];
				cell += 2;
			}
			break;
		}
		case PRG: {
			if (memory[cell + 1] == STDI) {
				reg[indxX][0] = memory[cell + 2];
				cell += 2;
			}
			else if (memory[cell + 1] == STDA) {
				reg[indxX][indxY] = memory[cell + 2];
			}
			break;
		}
		case PRC: {
			if (memory[cell + 1] == STDI) {
				reg[indxX][indxY] = memory[cell + 2];
				cell += 2;
			}
			else if (memory[cell + 1] == STDA) {
				int r1x, r1y, r2x, r2y;
				detcoorv(memory[cell + 2], &r1x, &r1y);
				detcoorv(memory[cell + 3], &r2x, &r2y);
				reg[r2x][r2y] = reg[r1x][r1y];
			}
			break;
		}
		case GJP: {
			if (memory[cell + 1] != nil && memory[cell + 2] > nil) {
				cell = jump(memory[cell + 1]);
				--cell;
			}
			break;
		}
		case PUT: {
			int tmp1, tmp2;
			detcoorv(memory[cell + 2], &tmp1, &tmp2);

			if (memory[cell + 1] == STDI) {
				printf("%d", reg[tmp1][tmp2]);
			}
			else if (memory[cell + 1] == STDC) {
				printf("%c", reg[tmp1][tmp2]);
			}
			break;
		}
		case DEB: {
			printf("%d\n", cell);
			break;
		}
		case RESTART: {
			cell = 0;
			break;
		}
		case QUIT: {
			memory[cell] = end;
			--cell;
			break;
		}
		case CLEAR: {
			if (memory[cell + 1] == ALL) {
				clear(memory[cell]);
			}
			else {
				memory[memory[cell + 1]] = nil;
			}
			break;
		}
		}
		cell++;
	}
}