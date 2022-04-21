#include <iostream>
#include <string>
#include <algorithm>

#define MAXSIZE 100

class Integer;
class Decimal;

class BigNumber
{
public:
    
protected:

    long long int integer[MAXSIZE];
    long long int decimal[MAXSIZE];
    std::string input;
    bool sign;
};


class Integer : public BigNumber
{
public:
    const Integer operator+(const Integer& post);
    const Decimal operator+(const Decimal& post);
    
    const Integer add(const Integer& post);
    const Decimal add(const Decimal& post);

    const Integer operator-(const Integer& post);
    const Decimal operator-(const Decimal& post);

    const Integer minus(const Integer& post);
    const Decimal minus(const Decimal& post);

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