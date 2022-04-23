#include "BigNum.h"


const void Integer::operator=(const Integer& post) {
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		integer[i] = post.integer[i];
		decimal[i] = post.decimal[i];
	}
	sign = post.sign;
}

const Integer Integer::operator+(const Integer& post) {
	Integer tmp = post;
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		tmp.integer[i] += this->integer[i];
		if (i != MAXARRAYSIZE - 1) {
			tmp.integer[i + 1] += tmp.integer[i] / MAXNUMBERSIZE;
			tmp.integer[i] = tmp.integer[i] % MAXNUMBERSIZE;
		}
	}
	return tmp;
}

const Decimal Integer::operator+(const Decimal& post) {
	Decimal tmp = post;
	for (int i = 0; i < MAXARRAYSIZE; i++) {
		tmp.integer[i] += this->integer[i];
		if (i != MAXARRAYSIZE - 1) {
			tmp.integer[i + 1] += tmp.integer[i] / MAXNUMBERSIZE;
			tmp.integer[i] = tmp.integer[i] % MAXNUMBERSIZE;
		}
	}
	return tmp;
}