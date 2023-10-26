#ifndef BIGINTEGER_H
#define BIGINTEGER_H

struct DigitNode {
    int digit;
    struct DigitNode* next;
};

struct BigInteger {
    struct DigitNode* head;
    int size;
};

void initializeBigInteger(struct BigInteger* num);
void insertDigitAtBeginning(struct BigInteger* num, int digit);
struct BigInteger add(struct BigInteger a, struct BigInteger b);
int compareBigInts(struct BigInteger a, struct BigInteger b);
struct BigInteger sub(struct BigInteger a, struct BigInteger b);
struct BigInteger multiplyBySingleDigit(struct BigInteger a, int digit);
struct BigInteger mul(struct BigInteger a, struct BigInteger b);
void divideBySingleDigit(struct BigInteger a, int digit, struct BigInteger* quotient, int* remainder);
void div1(struct BigInteger a, struct BigInteger b, struct BigInteger* quotient, struct BigInteger* remainder);
struct BigInteger mod(struct BigInteger a, struct BigInteger b);
void freeBigInteger(struct BigInteger num);
void display(struct BigInteger num);

#endif