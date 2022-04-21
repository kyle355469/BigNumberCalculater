#include "BigInteger.h"

BigInteger::BigInteger(){
    memset(integer, 0, MAXSIZE);
    memset(decimal, 0, MAXSIZE);
    sign = true;
}

BigInteger::BigInteger(std::string input){
    memset(integer, 0, MAXSIZE);
    memset(decimal, 0, MAXSIZE);
    sign = true;
    int point;
    int intCount = 0;
    int decCount = 0;
    for(int i = 0; i < input.size(); i++){
        if(input[i] == '-') {
            sign = false;
        }
        if(input[i] == '.') break;
    }
    for(int i = point - 1; i >= 0;){
        integer[intCount++] = std::stoi(input.substr(std::max(i - 9, 0), std::min(9, i + 1)));
        i -= 9;
    }
    for(int i = point + 1; i < input.size();){
        decimal[decCount++] = std::stoi(input.substr(i, std::min(9, (int)input.size() - i)));
        i += 9;
    }
}

BigInteger::BigInteger(const BigInteger& call){
    for(int i = 0; i < MAXSIZE; i++){
        integer[i] = call.integer[i];
    }
    for(int i = 0; i < MAXSIZE; i++){
        decimal[i] = call.decimal[i];
    }
}

const BigInteger BigInteger::operator+(const BigInteger& post){
    BigInteger tmp;
    if(this->sign == false && post.sign == true){
        
    }else if(){
        
    }
    
    return tmp;
}

const BigInteger BigInteger::add(const BigInteger& post){
    BigInteger tmp;
    for(int i = 0; i < MAXSIZE; i++){
        tmp.integer[i] = this->integer[i] + post.integer[i];
        tmp.decimal[i] = this->decimal[i] + post.decimal[i];
    }
    for(int i = MAXSIZE - 1; i > 0; i--){
        tmp.integer[i - 1] = tmp.integer[i] / 1e9;
        tmp.integer[i] %= tmp.decimal[i] % (int)1e9;
    }
    for(int i = 0; i < MAXSIZE - 1; i++){
        tmp.decimal[i + 1] = tmp.decimal[i] / 1e9;
        tmp.decimal[i] = tmp.decimal[i] % (int)1e9;
    }
    return tmp;
}
