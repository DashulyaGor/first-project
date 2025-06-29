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
} Polynomial;

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

Monomial subtraction(const Monomial *a, const Monomial *b) {
    if (a->degree != b->degree) {
        return (Monomial) {0, 0};
    } else {
        return (Monomial) {a->coefficient - b->coefficient, a->degree};
    }
}

Monomial divide_monomials(const Monomial *a, const Monomial *b) {
    if (b->coefficient == 0) {
        fprintf(stderr, "Error: Division by zero is not allowed!\n");
        exit(EXIT_FAILURE);
    }

    return (Monomial) {
        .coefficient = a->coefficient / b->coefficient,
        .degree = a->degree - b->degree
    };
}

void init_polynomial(Polynomial *poly, int capacity) {
    poly->terms = (Monomial*)calloc(capacity, sizeof(Monomial));
    poly->count = 0;
    poly->capacity = capacity;
}

void free_polynomial(Polynomial *poly) {
    free(poly->terms);
    poly->terms = NULL;
    poly->count = 0;
    poly->capacity = 0;
}

void add_term(Polynomial *poly, const Monomial *term) {
    if (poly->count >= poly->capacity) {
    poly->capacity *= 2;
    poly->terms = (Monomial*)realloc(poly->terms, poly->capacity *sizeof(Monomial));
    }
    poly->terms[poly->count++] = *term;
}

void print_polynomial(const Polynomial *poly) {
    for (int i = 0; i < poly->count; i++) {
        print_monomial(&(poly->terms[i]));
    }
    printf("\n");
}

int main() {
    Polynomial polynomial;
    init_polynomial(&polynomial, 10);

    Monomial first_term = {3.0, 2};
    Monomial second_term = {-2.0, 1};
    Monomial third_term = {1.0, 0};

    add_term(&polynomial, &first_term);
    add_term(&polynomial, &second_term);
    add_term(&polynomial, &third_term);

    print_polynomial(&polynomial);

    free_polynomial(&polynomial);

    return 0;
}