#include "biginteger.h"
#include <stdio.h>
#include <stdlib.h>

void initializeBigInteger(struct BigInteger* num) {
    num->head = NULL;
    num->size = 0;
}

void insertDigitAtBeginning(struct BigInteger* num, int digit) {
    struct DigitNode* newNode = (struct DigitNode*)malloc(sizeof(struct DigitNode));
    newNode->digit = digit;
    newNode->next = num->head;
    num->head = newNode;
    num->size++;
}

struct BigInteger add(struct BigInteger a, struct BigInteger b) {
    struct BigInteger result;
    initializeBigInteger(&result);

    int carry = 0;

    struct DigitNode* p = a.head;
    struct DigitNode* q = b.head;

    while (p != NULL || q != NULL) {
        int x = (p != NULL) ? p->digit : 0;
        int y = (q != NULL) ? q->digit : 0;

        int sum = x + y + carry;
        carry = sum / 10;
        insertDigitAtBeginning(&result, sum % 10);

        if (p != NULL) p = p->next;
        if (q != NULL) q = q->next;
    }

    if (carry > 0) {
        insertDigitAtBeginning(&result, carry);
    }

    return result;
}

int compareBigInts(struct BigInteger a, struct BigInteger b) {
    if (a.size > b.size) return 1;
    if (a.size < b.size) return -1;

    struct DigitNode* p = a.head;
    struct DigitNode* q = b.head;

    while (p != NULL && q != NULL) {
        if (p->digit > q->digit) return 1;
        if (p->digit < q->digit) return -1;

        p = p->next;
        q = q->next;
    }

    return 0;
}

struct BigInteger sub(struct BigInteger a, struct BigInteger b) {
    struct BigInteger result;
    initializeBigInteger(&result);

    int borrow = 0;

    struct DigitNode* p = a.head;
    struct DigitNode* q = b.head;

    while (p != NULL) {
        int x = p->digit;
        int y = (q != NULL) ? q->digit : 0;

        int diff = x - y - borrow;
        borrow = (diff < 0) ? 1 : 0;
        diff = (diff < 0) ? diff + 10 : diff;

        insertDigitAtBeginning(&result, diff);

        p = p->next;
        if (q != NULL) q = q->next;
    }

    // Remove leading zeros
    while (result.size > 1 && result.head->digit == 0) {
        struct DigitNode* temp = result.head;
        result.head = result.head->next;
        free(temp);
        result.size--;
    }

    return result;
}

struct BigInteger multiplyBySingleDigit(struct BigInteger a, int digit) {
    struct BigInteger result;
    initializeBigInteger(&result);

    int carry = 0;

    struct DigitNode* p = a.head;

    while (p != NULL) {
        int product = p->digit * digit + carry;
        carry = product / 10;
        insertDigitAtBeginning(&result, product % 10);

        p = p->next;
    }

    if (carry > 0) {
        insertDigitAtBeginning(&result, carry);
    }

    return result;
}

struct BigInteger mul(struct BigInteger a, struct BigInteger b) {
    struct BigInteger result;
    initializeBigInteger(&result);

    struct BigInteger temp;
    initializeBigInteger(&temp);

    int shift = 0;

    struct DigitNode* q = b.head;

    while (q != NULL) {
        struct BigInteger product = multiplyBySingleDigit(a, q->digit);

        for (int i = 0; i < shift; i++) {
            insertDigitAtBeginning(&product, 0);
        }

        result = add(result, product);

        q = q->next;
        shift++;
    }

    return result;
}

void divideBySingleDigit(struct BigInteger a, int digit, struct BigInteger* quotient, int* remainder) {
    initializeBigInteger(quotient);

    int carry = 0;
    struct DigitNode* p = a.head;

    while (p != NULL) {
        int dividend = carry * 10 + p->digit;
        int q = dividend / digit;
        carry = dividend % digit;

        if (!(q == 0 && quotient->size == 0)) {
            insertDigitAtBeginning(quotient, q);
        }

        p = p->next;
    }

    *remainder = carry;
}

void div1(struct BigInteger a, struct BigInteger b, struct BigInteger* quotient, struct BigInteger* remainder) {
    initializeBigInteger(quotient);
    initializeBigInteger(remainder);

    struct BigInteger current;
    initializeBigInteger(&current);

    struct DigitNode* p = a.head;

    while (p != NULL) {
        insertDigitAtBeginning(&current, p->digit);
        if (compareBigInts(current, b) < 0) {
            if (quotient->size > 0) {
                insertDigitAtBeginning(quotient, 0);
            }
        } else {
            int q, r;
            divideBySingleDigit(current, b.head->digit, quotient, &q);
            current = sub(current, multiplyBySingleDigit(b, q));
            if (quotient->size > 0) {
                insertDigitAtBeginning(quotient, q);
            }
        }
        p = p->next;
    }

    *remainder = current;
}

struct BigInteger mod(struct BigInteger a, struct BigInteger b) {
    struct BigInteger quotient, remainder;
    divideBigInts(a, b, &quotient, &remainder);
    return remainder;
}

void freeBigInteger(struct BigInteger num) {
    struct DigitNode* p = num.head;
    while (p != NULL) {
        struct DigitNode* temp = p;
        p = p->next;
        free(temp);
    }
}

void display(struct BigInteger num) {
    struct DigitNode* p = num.head;
    if (p == NULL) {
        printf("0\n");
        return;
    }
    while (p != NULL) {
        printf("%d", p->digit);
        p = p->next;
    }
    printf("\n");
}
