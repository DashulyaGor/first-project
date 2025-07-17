#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char var;
    int degree;
} Variable;

typedef struct {
    double coefficient;
    Variable *variables;
    int var_count;
} Monomial;

typedef struct {
    Monomial *terms;
    int count;
    int capacity;
} Polynomial;

void print_monomial(const Monomial *m) {
    printf("%.02lf", m->coefficient);
    for (int i = 0; i < m->var_count; i++) {
        printf("*%c^%d", m->variables[i].var, m->variables[i].degree);
    }
    //printf("\n");
}

Monomial init_monomial(int initial_capacity) {
    Monomial m = {
        .coefficient = 0.0,
        .variables = (Variable *)malloc(initial_capacity * sizeof(Variable)),
        .var_count = 0
    };

    if(!m.variables) {
        fprintf(stderr, "Error allocating memory for variables.\n");
        exit(EXIT_FAILURE);
    }
    return m;
}

void free_monomial(Monomial *m) {
    free(m->variables);
    m->variables = NULL;
    m->var_count = 0;
}

void add_variable(Monomial *m, char var, int degree) {
    if (m->var_count >= m->var_count + 1) {
        m->variables = (Variable *)realloc(m->variables, (m->var_count + 1) * sizeof(Variable));
        if (!m->variables) {
            fprintf(stderr, "Memory reallocation error for variables.\n");
            exit(EXIT_FAILURE);
        }
    }
    m->variables[m->var_count++] = (Variable){.var = var, .degree = degree};
}

int compare_variables(const Variable *vars_a, int count_a, const Variable *vars_b, int count_b) {
    if (count_a != count_b) {
        return 0;
    }
    for (int i = 0; i < count_a; i++) {
        if (vars_a[i].var != vars_b[i].var || vars_a[i].degree != vars_b[i].degree) {
            return 0;
        }
    }
    return 1;
}

Monomial add_monomial(const Monomial *a, const Monomial *b) {
    if (!compare_variables(a->variables, a->var_count, b->variables, b->var_count)) {
        return (Monomial) {0};
    }
    Monomial result = init_monomial(a->var_count);
    result.coefficient = a->coefficient + b->coefficient;
    memcpy(result.variables, a->variables, a->var_count *sizeof(Variable));
    result.var_count = a->var_count;
    return result;
}

Monomial multiply_monomials(const Monomial *a, const Monomial *b) {
    Monomial result = init_monomial(a->var_count + b->var_count);
    result.coefficient = a->coefficient * b->coefficient;
    for (int i = 0; i < a->var_count; ++i) {
        result.variables[i] = a->variables[i];
    }
    for (int i = 0; i < b->var_count; ++i) {
        result.variables[a->var_count + i] = b->variables[i];
    }
    result.var_count = a->var_count + b->var_count;
    return result;
}

Monomial subtract_monomials(const Monomial *a, const Monomial *b) {
    if (!compare_variables(a->variables, a->var_count, b->variables,b->var_count)) {
        return (Monomial) {0};
    }
    Monomial result = init_monomial(a->var_count);
    result.coefficient = a->coefficient - b->coefficient;
    memcpy(result.variables, a->variables, a->var_count *sizeof(Variable));
    result.var_count = a->var_count;
    return result;
}

Monomial divide_monomials(const Monomial *a, const Monomial *b) {
    if (b->coefficient == 0) {
        fprintf(stderr, "Error: Division by zero is not allowed!\n");
        exit(EXIT_FAILURE);
    }
    if (!compare_variables(a->variables, a->var_count, b->variables,b->var_count)) {
        return (Monomial) {0};
    }

    Monomial result = init_monomial(a->var_count);
    result.coefficient = a->coefficient / b->coefficient;
    for (int i = 0; i < a->var_count; ++i) {
        result.variables[i].var = a->variables[i].var;
        result.variables[i].degree = a->variables[i].degree -b->variables[i].degree;
    }
    result.var_count = a->var_count;
    return result;
}

void init_polynomial(Polynomial *poly, int capacity) {
    poly->terms = (Monomial*)calloc(capacity, sizeof(Monomial));
    if (!poly->terms) {
        fprintf(stderr, "Error allocating memory for a polynomial.\n");
        exit(EXIT_FAILURE);
    }
    poly->count = 0;
    poly->capacity = capacity;
}

void free_polynomial(Polynomial *poly) {
    for (int i = 0; i < poly->count;++i) {
        free_monomial(&poly->terms[i]);
    }
    free(poly->terms);
    poly->terms = NULL;
    poly->count = 0;
    poly->capacity = 0;
}

void add_term(Polynomial *poly, const Monomial *term) {
    if (poly->count >= poly->capacity) {
        poly->capacity *= 2;
        poly->terms = (Monomial*)realloc(poly->terms, poly->capacity *sizeof(Monomial));
        if (!poly->terms) {
            fprintf(stderr, "Error allocating memory for a polynomial.\n");
            exit(EXIT_FAILURE);
        }
    }
    poly->terms[poly->count++] = *term;
}

void print_polynomial(const Polynomial *poly) {
    for (int i = 0; i < poly->count; ++i) {
        print_monomial(&(poly->terms[i]));
        if (i < poly->count - 1) {
            printf(" + ");
        }
    }
    printf("\n");
}

int main() {
    Polynomial polynomial;
    init_polynomial(&polynomial, 10);

    Monomial first_term = init_monomial(1);
    first_term.coefficient = 3.0;
    add_variable(&first_term, 'x', 2);

    Monomial second_term = init_monomial(1);
    second_term.coefficient = -2.0;
    add_variable(&second_term, 'y', 1);

    Monomial third_term = init_monomial(0);
    third_term.coefficient = 1.0;

    add_term(&polynomial, &first_term);
    add_term(&polynomial, &second_term);
    add_term(&polynomial, &third_term);

    print_polynomial(&polynomial);

    free_polynomial(&polynomial);

    return 0;
}