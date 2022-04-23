#pragma once
#include <iostream>
#include <string>
#include <algorithm>

#define MAXARRAYSIZE 100
#define MAXNUMBERSIZE (int)1e9

class Integer;
class Decimal;

class BigNumber
{
public:

    long long int integer[MAXARRAYSIZE];
    long long int decimal[MAXARRAYSIZE];
    std::string input;
    bool sign;
};


class Integer : public BigNumber
{
public:
    Integer();
    Integer(BigNumber post);
    const void operator=(const Integer& post);
    const Integer operator+(const Integer& post);
    const Decimal operator+(const Decimal& post);
    
    const Integer add(const Integer& pre, const Integer& post); // not nessesary
    const Decimal add(const Integer& pre, const Decimal& post);

    const Integer operator-(const Integer& post);
    const Decimal operator-(const Decimal& post);

    const Integer minus(const Integer& pre, const Integer& post);
    const Decimal minus(const Integer& pre, const Decimal& post);

    const Integer operator*(const Integer& post);
    const Decimal operator*(const Decimal& post);

    const Integer operator/(const Integer& post);
    const Decimal operator/(const Decimal& post);

    friend const Integer operator!(const Integer& post);
    friend const Integer operator-(const Integer& post);
    friend const Integer operator+(const Integer& post);

    const Integer operator^(const Integer& times);
    const Decimal operator^(const Decimal& times);

};

class Decimal : public BigNumber
{
public:
    const void operator=(const Decimal& post);
    const Decimal operator+(const Integer& post);
    const Decimal operator+(const Decimal& post);

    const Decimal add(const Decimal& post);
    const Decimal add(const Integer& post);

    const Decimal operator-(const Integer& post);
    const Decimal operator-(const Decimal& post);

    const Decimal minus(const Decimal& post);
    const Decimal minus(const Integer& post);

    const Decimal operator*(const Integer& post);
    const Decimal operator*(const Decimal& post);

    const Decimal operator/(const Integer& post);
    const Decimal operator/(const Decimal& post);

    friend const Decimal operator!(const Decimal& post);
    friend const Decimal operator-(const Decimal& post);
    friend const Decimal operator+(const Decimal& post);

    const Decimal operator^(const Integer& times);
    const Decimal operator^(const Decimal& times);
};
