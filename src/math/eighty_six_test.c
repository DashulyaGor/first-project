#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double coefficient;
    int degree;
} Monomial;

typedef struct {
    Monomial *terms;
    int count;
    int capacity;
} Polinomial;

void print_monomial(const Monomial *m) {
    printf("%lf * x^%d\n", m->coefficient, m->degree);
}

Monomial add_monomial(const Monomial *a, const Monomial *b) {
    if (a->degree != b->degree) {
        return (Monomial) {0, 0};
    } else {
        return (Monomial) {a->coefficient + b->coefficient, a->degree};
    }
}

Monomial multiply_monomials(const Monomial *a, const Monomial *b) {
    return (Monomial) {
        .coefficient = a->coefficient * b->coefficient,
        .degree = a->degree + b->degree
    };
}