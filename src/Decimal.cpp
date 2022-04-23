#include "BigNum.h"

const void Decimal::operator=(const Decimal& post) {
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		integer[i] = post.integer[i];
		decimal[i] = post.decimal[i];
	}
	sign = post.sign;
}
