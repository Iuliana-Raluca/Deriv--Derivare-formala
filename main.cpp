#include <fstream>
#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

ifstream fin("proiect.in");
ofstream fout("proiect.out");

char infix[100], postfixata[100], primaderivata[200], adouaderivata[200];

struct nod {
    char info;
    nod* urm;
};

struct arbore {
    char info[10];
    arbore* st, * dr;
};

struct nodarbore {
    arbore* info;
    nodarbore* urm;
};

struct stiva {
    nod* varf;
    int nrElemente;
};

struct stivaarbore {
    nodarbore* varf;
    int nrElemente;
};

struct coada {
    nod* prim;
    nod* ultim;
    int nrElemente;
};

coada postfix;

bool esteVida(stiva S) {
    return S.nrElemente == 0;
}

bool esteVida(stivaarbore S) {
    return S.nrElemente == 0;
}

void pop(stiva& S) {
    if (!esteVida(S)) {

        nod* varf_nou;
        varf_nou = S.varf->urm;
        delete S.varf;
        S.varf = varf_nou;
        S.nrElemente--;
    }
}

void poparbore(stivaarbore& S) {
    if (!esteVida(S)) {
        nodarbore* varf_nou;
        varf_nou = S.varf->urm;
        delete S.varf;
        S.varf = varf_nou;
        S.nrElemente--;
    }
}

void push(stiva& S, char element) {
    nod* nod_nou;

    if (esteVida(S)) {
        S.nrElemente = 1;
        S.varf = new nod;
        S.varf->info = element;
        S.varf->urm = NULL;
    }
    else {
        S.nrElemente++;
        nod_nou = new nod;
        nod_nou->info = element;
        nod_nou->urm = S.varf;
        S.varf = nod_nou;
    }
}

void pusharbore(stivaarbore& S, arbore* element) {
    nodarbore* nod_nou;

    if (esteVida(S)) {
        S.nrElemente = 1;
        S.varf = new nodarbore;
        S.varf->info = element;
        S.varf->urm = NULL;
    }
    else {
        S.nrElemente++;
        nod_nou = new nodarbore;
        nod_nou->info = element;
        nod_nou->urm = S.varf;
        S.varf = nod_nou;
    }
}

void initializeazastiva(stiva& S) {
    S.varf = NULL;
    S.nrElemente = 0;
}

void initializeazastivaarbore(stivaarbore& S) {
    S.varf = NULL;
    S.nrElemente = 0;
}

void initializeazacoada(coada& C) {
    C.prim = NULL;
    C.ultim = NULL;
    C.nrElemente = 0;
}

bool esteVida(coada C) {
    return C.nrElemente == 0;
}

char dequeue(coada& C) {
    char element = C.prim->info;
    nod* primul;
    primul = C.prim;
    C.prim = C.prim->urm;
    delete primul;
    C.nrElemente--;
    return element;
}

void enqueue(coada& C, char element) {
    nod* nod_nou;

    if (esteVida(C)) {
        C.nrElemente = 1;
        C.prim = new nod;
        C.prim->info = element;
        C.prim->urm = NULL;
        C.ultim = C.prim;
    }
    else {
        C.nrElemente++;
        nod_nou = new nod;
        nod_nou->info = element;
        nod_nou->urm = NULL;
        C.ultim->urm = nod_nou;
        C.ultim = nod_nou;
    }
}

void afiseaza(coada C) {
    nod* nod_curent;
    nod_curent = C.prim;
    int i = 0;

    while (nod_curent != NULL) {
        fout << nod_curent->info;
        postfixata[i++] = nod_curent->info;
        nod_curent = nod_curent->urm;

    }
}

int prioritate(char c) {
    switch (c) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    case 's':
    case 'c':
    case 't':
    case 'g':
    case 'l':
    case 'r':
    case 'e':
    case 'z':
        return 4;
    case '(':
        return 5;
    case ')':
        return 6;
    default:
        return 7;
    }
}

int prioritate1(char c[]) {
    if (!strcmp(c, "+"))
        return 1;
    if (!strcmp(c, "-"))
        return 2;
    if (!strcmp(c, "*"))
        return 3;
    if (!strcmp(c, "^"))
        return 4;
    if (!strcmp(c, "/"))
        return 5;
    else
        return 6;
}

void adaugaincoada(coada& postfix, stiva& S) {

    if (S.varf->info == 's') {
        enqueue(postfix, 's');
        enqueue(postfix, 'i');
        enqueue(postfix, 'n');
    }
    else if (S.varf->info == 'c') {
        enqueue(postfix, 'c');
        enqueue(postfix, 'o');
        enqueue(postfix, 's');
    }
    else if (S.varf->info == 't') {
        enqueue(postfix, 't');
        enqueue(postfix, 'g');
    }
    else if (S.varf->info == 'g') {
        enqueue(postfix, 'c');
        enqueue(postfix, 't');
        enqueue(postfix, 'g');
    }
    else if (S.varf->info == 'l') {
        enqueue(postfix, 'l');
        enqueue(postfix, 'o');
        enqueue(postfix, 'g');
    }
    else if (S.varf->info == 'r') {
        enqueue(postfix, 'r');
        enqueue(postfix, 'a');
        enqueue(postfix, 'd');
    }
    else if (S.varf->info == 'e') {
        enqueue(postfix, 'l');
        enqueue(postfix, 'n');
    }
    else if (S.varf->info == 'z') {
        enqueue(postfix, 'l');
        enqueue(postfix, 'g');
    }
    else
        enqueue(postfix, S.varf->info);

    pop(S);
}

void adaugainstiva(stiva& S, coada& postfix, char& x, int& i) {

    if (x == 's' && infix[i + 1] == 'i' && infix[i + 2] == 'n') {
        push(S, 's');
        i = i + 2;
    }
    else if (x == 'c' && infix[i + 1] == 'o' && infix[i + 2] == 's') {
        push(S, 'c');
        i = i + 2;
    }
    else if (x == 't' && infix[i + 1] == 'g') {
        push(S, 't');
        i = i + 1;
    }
    else if (x == 'c' && infix[i + 1] == 't' && infix[i + 2] == 'g') {
        push(S, 'g');
        i = i + 2;
    }
    else if (x == 'l' && infix[i + 1] == 'o' && infix[i + 2] == 'g') {
        push(S, 'l');
        i = i + 2;
    }
    else if (x == 'r' && infix[i + 1] == 'a' && infix[i + 2] == 'd') {
        push(S, 'r');
        i = i + 2;
    }
    else if (x == 'l' && infix[i + 1] == 'n') {
        push(S, 'e');
        i = i + 1;
    }
    else if (x == 'l' && infix[i + 1] == 'g') {
        push(S, 'z');
        i = i + 1;
    }
    else
        push(S, x);
}

bool esteoperator(char infix[], int i) {

    if (strchr("+-*/^(),", infix[i])) return 1;
    if (strchr("sctglr", infix[i]) && strchr("iogtan", infix[i + 1]))
        return 1;
    return 0;
}

int esteoperator1(char element[]) {

    if (strchr("+-*/^", element[0]) && element[1] == NULL) return 2;
    if ((element[0] == 'l') && (element[1] == 'o') && (element[2] == 'g')) return 2;
    if ((element[0] == 'r') && (element[1] == 'a') && (element[2] == 'd')) return 2;
    if (strchr("sctgl", element[0]) && strchr("iogtn", element[1]) && element[1] != NULL)
        return 1;
    return 0;
}

int esteoperator2(char element[]) {

    if (strchr("+-*/^", element[0]) && element[1] == NULL) return 2;
    if ((element[0] == 'l') && (element[1] == 'o') && (element[2] == 'g')) return 1;
    if ((element[0] == 'r') && (element[1] == 'a') && (element[2] == 'd')) return 1;
    if (strchr("sctgl", element[0]) && strchr("iogtn", element[1]) && element[1] != NULL)
        return 1;
    return 0;
}

void conversieinfixpostfix(char infix[], coada& postfix) {

    int i, lg = strlen(infix), j = 0;
    char x;
    stiva S;
    initializeazastiva(S);

    if (infix[j] == '-') {
        enqueue(postfix, '-');
        j = j + 1;
    }


    for (i = j; i < lg; i++) {
        x = infix[i];
        if (!esteoperator(infix, i))
            enqueue(postfix, x);
        else {

            if (x != '(' && infix[i - 1] != ')' && !strchr("sctglrez", x))
                enqueue(postfix, ',');

            if (x == '(' && infix[i + 1] == '-') {
                enqueue(postfix, '-');
                i++;
            }

            if (x == ')') {

                while (S.varf->info != '(') {
                    adaugaincoada(postfix, S);
                    enqueue(postfix, ',');
                }

                pop(S);
            }
            else if (x != ',') {

                while (!esteVida(S) && (S.varf->info != '(') && (prioritate(S.varf->info) >= prioritate(x))) {
                    adaugaincoada(postfix, S);
                    enqueue(postfix, ',');
                }
                adaugainstiva(S, postfix, x, i);
            }
        }
    }
    if (!esteoperator(infix, i - 1))
        enqueue(postfix, ',');

    while (S.nrElemente > 1) {
        adaugaincoada(postfix, S);
        enqueue(postfix, ',');
    }

    adaugaincoada(postfix, S);
}


int nrNiveluri(arbore* a) {

    if (a == NULL)return 0;
    else {
        int n1 = nrNiveluri(a->st);
        int n2 = nrNiveluri(a->dr);
        return 1 + max(n1, n2);
    }
}

int nrColoane(arbore* a) {

    if (a == NULL)return 0;
    else {
        int n1 = nrColoane(a->st);
        int n2 = nrColoane(a->dr);
        return 1 + n1 + n2;
    }
}

void deseneazaNod(char elem[], int xc, int yc, int latime, int inaltime) {
    char arr[50];
    sprintf(arr, "%s", elem);
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, 12);
    fillellipse(xc, yc, 23, 23);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    setbkcolor(12);
    setcolor(BLACK);
    settextjustify(1, 1);
    settextstyle(3, 0, 2);
    outtextxy(xc, yc + 4, arr);
}

void deseneazaArbore(arbore* a, int niv, int stanga, int latime, int inaltime) {

    if (a != NULL) {
        int n1 = nrColoane(a->st);
        int yc = niv * inaltime - inaltime / 2;
        int xc = stanga + latime * n1 + latime / 2;

        if (a->st != NULL) {
            int xcs = stanga + latime * nrColoane(a->st->st) + latime / 2;
            setcolor(RED);
            line(xc, yc, xcs, yc + inaltime);
        }

        if (a->dr != NULL) {
            int xcd = stanga + latime * (n1 + 1) + latime * nrColoane(a->dr->st) + latime / 2;
            setcolor(RED);
            line(xc, yc, xcd, yc + inaltime);
        }
        deseneazaArbore(a->st, niv + 1, stanga, latime, inaltime);
        deseneazaArbore(a->dr, niv + 1, stanga + latime * (n1 + 1), latime, inaltime);
        deseneazaNod(a->info, xc, yc, latime, inaltime);
    }
}


void Elementearbore(coada C, stivaarbore& S) {
    int i = 0;
    arbore* arbore_nou;
    char element[10];
    memset(element, '\0', 10);

    while (C.prim != NULL) {
        if (C.prim->info == ',') {
            if (!(esteoperator1(element))) {
                arbore_nou = new arbore;
                strcpy(arbore_nou->info, element);
                arbore_nou->st = NULL;
                arbore_nou->dr = NULL;
                pusharbore(S, arbore_nou);
            }
            else if (esteoperator1(element) == 2) {
                arbore_nou = new arbore;
                strcpy(arbore_nou->info, element);
                arbore_nou->dr = S.varf->info;
                poparbore(S);
                arbore_nou->st = S.varf->info;
                poparbore(S);
                pusharbore(S, arbore_nou);
            }
            else {
                arbore_nou = new arbore;
                strcpy(arbore_nou->info, element);
                arbore_nou->dr = NULL;
                arbore_nou->st = S.varf->info;
                poparbore(S);
                pusharbore(S, arbore_nou);
            }
            memset(element, '\0', strlen(element));
            i = 0;
        }
        else
            element[i++] = C.prim->info;
        C.prim = C.prim->urm;
    }

    if (esteoperator1(element) == 2) {
        arbore_nou = new arbore;
        strcpy(arbore_nou->info, element);
        arbore_nou->dr = S.varf->info;
        poparbore(S);
        arbore_nou->st = S.varf->info;
        poparbore(S);
        pusharbore(S, arbore_nou);
    }
    else {
        arbore_nou = new arbore;
        strcpy(arbore_nou->info, element);
        arbore_nou->dr = NULL;
        arbore_nou->st = S.varf->info;
        poparbore(S);
        pusharbore(S, arbore_nou);
    }
}

arbore* simplifica(arbore* a) {

    if (!strcmp(a->info, "+")) {
        if (!strcmp(a->st->info, "0")) {
            a = a->dr;
        }
        else if (!strcmp(a->dr->info, "0")) {
            a = a->st;
        }
        else if (!strcmp(a->dr->info, "-")) {
            a->dr = a->dr->dr;
            strcpy(a->info, "-");
        }
    }

    if (!strcmp(a->info, "-")) {
        if (!strcmp(a->dr->info, "0")) {
            a = a->st;
        }
        else if (!strcmp(a->dr->info, "-")) {
            a->dr = a->dr->dr;
            strcpy(a->info, "+");
        }
    }
    if (!strcmp(a->info, "*")) {
        if (!strcmp(a->st->info, "0") || !strcmp(a->dr->info, "0")) {
            strcpy(a->info, "0");
            a->st = NULL;
            a->dr = NULL;
        }
        else if (!strcmp(a->st->info, "1")) {
            a = a->dr;
        }
        else if (!strcmp(a->dr->info, "1")) {
            a = a->st;
        }
    }

    if (!strcmp(a->info, "/")) {
        if (!strcmp(a->st->info, "0")) {
            strcpy(a->info, "0");
            a->st = NULL;
            a->dr = NULL;
        }
        else if (!strcmp(a->dr->info, "1")) {
            a = a->st;
        }
    }

    if (!strcmp(a->info, "^")) {
        if (!strcmp(a->st->info, "0")) {
            strcpy(a->info, "0");
            a->st = NULL;
            a->dr = NULL;
        }
        else if (!strcmp(a->dr->info, "0")) {
            strcpy(a->info, "1");
            a->st = NULL;
            a->dr = NULL;
        }
        else if (!strcmp(a->st->info, "1")) {
            strcpy(a->info, "1");
            a->st = NULL;
            a->dr = NULL;
        }
        else if (!strcmp(a->dr->info, "1")) {
            a = a->st;
        }
    }

    if (!strcmp(a->info, "ln")) {
        if (!strcmp(a->st->info, "e")) {
            strcpy(a->info, "1");
            a->st = NULL;
            a->dr = NULL;
        }
    }

    return a;
}

arbore* derivare(arbore* a, arbore* d) {
    if ( (a->info[0] == '-') && (a->info[1] == NULL)) {
        arbore* t1; arbore* t2;
        t1 = new arbore;
        t1->st = NULL;
        t1->dr = NULL;
        t2 = new arbore;
        t2->st = NULL;
        t2->dr = NULL;
        derivare(a->st, t1);
        t1 = simplifica(t1);
        d->st = t1;
        derivare(a->dr, t2);
        t2 = simplifica(t2);
        d->dr =t2;
        strcpy(d->info, a->info);
        d = simplifica(d);
    }

    if ((a->info[0] == '+')  && (a->info[1] == NULL)) {
        arbore* t1; arbore* t2;
        t1 = new arbore;
        t1->st = NULL;
        t1->dr = NULL;
        t2 = new arbore;
        t2->st = NULL;
        t2->dr = NULL;
        derivare(a->st, t1);
        t1 = simplifica(t1);
        d->st = t1;
        derivare(a->dr, t2);
        t2 = simplifica(t2);
        d->dr = t2;
        strcpy(d->info, a->info);
        d = simplifica(d);
    }

    if (a->info[0] == '*') {
        arbore* t1;
        arbore* t2;
        arbore* t3;
        arbore* t4;
        t1 = new arbore;
        t1->st = NULL;
        t1->dr = NULL;
        t2 = new arbore;
        t2->st = NULL;
        t2->dr = NULL;
        t3 = new arbore;
        t3->st = NULL;
        t3->dr = NULL;
        t4 = new arbore;
        t4->st = NULL;
        t4->dr = NULL;
        derivare(a->st, t1);
        t1 = simplifica(t1);
        derivare(a->dr, t2);
        t2 = simplifica(t2);
        strcpy(t3->info, "*");
        t3->st = t1;
        t3->dr = a->dr;
        t3 = simplifica(t3);
        strcpy(t4->info, "*");
        t4->st = a->st;
        t4->dr = t2;
        t4 = simplifica(t4);
        strcpy(d->info, "+");
        d->st = t3;
        d->dr = t4;
        d = simplifica(d);
    }

    if (a->info[0] == '/') {
       arbore* t1;
       arbore* t2;
       arbore* t3;
       arbore* t4;
       arbore* t5;
       arbore* t6;
       arbore* t7;
        t1 = new arbore;
        t1->st = NULL;
        t1->dr = NULL;
        t2 = new arbore;
        t2->st = NULL;
        t2->dr = NULL;
        t3 = new arbore;
        t3->st = NULL;
        t3->dr = NULL;
        t4 = new arbore;
        t4->st = NULL;
        t4->dr = NULL;
        t5 = new arbore;
        t5->st = NULL;
        t5->dr = NULL;
        t6 = new arbore;
        t6->st = NULL;
        t6->dr = NULL;
        t7 = new arbore;
        t7->st = NULL;
        t7->dr = NULL;
        strcpy(t7->info, "2");
        derivare(a->st, t1);
        t1 = simplifica(t1);
        derivare(a->dr, t2);
        t2 = simplifica(t2);
        strcpy(t3->info, "*");
        t3->st = t1;
        t3->dr = a->dr;
        t3 = simplifica(t3);
        strcpy(t4->info, "*");
        t4->st = a->st;
        t4->dr = t2;
        t4 = simplifica(t4);
        strcpy(t5->info, "-");
        t5->st = t3;
        t5->dr = t4;
        t5 = simplifica(t5);
        strcpy(t6->info, "^");
        t6->st = a->dr;
        t6->dr = t7;
        t6 = simplifica(t6);
        strcpy(d->info, "/");
        d->st = t5;
        d->dr = t6;
        d = simplifica(d);
    }

    if (a->info[0] == '^') {
        if (strchr("0123456789e", a->st->info[0])) {
           arbore* t1;
           arbore* t2;
           arbore* t3;
            t1 = new arbore;
            t1->st = NULL;
            t1->dr = NULL;
            t2 = new arbore;
            t2->st = a->st;
            t2->dr = NULL;
            strcpy(t2->info, "ln");
            t2 = simplifica(t2);
            t3 = new arbore;
            t3->st = a;
            t3->dr = t2;
            strcpy(t3->info, "*");
            t3 = simplifica(t3);
            derivare(a->dr, t1);
            t1 = simplifica(t1);
            strcpy(d->info, "*");
            d->st = t3;
            d->dr = t1;
            d = simplifica(d);
        }
        else {
           arbore* t1;
           arbore* t2;
           arbore* t3;
           arbore* t4;
           arbore* t5;
            t1 = new arbore;
            t1->st = NULL;
            t1->dr = NULL;
            t2 = new arbore;
            t2->st = NULL;
            t2->dr = NULL;
            strcpy(t2->info, "1");
            t3 = new arbore;
            t3->st = a->dr;
            t3->dr = t2;
            strcpy(t3->info, "-");
            t3 = simplifica(t3);
            t3->info[0] = '0' + t3->st->info[0] - t3->dr->info[0];
            t3->st = NULL;
            t3->dr = NULL;
            t4 = new arbore;
            t4->st = a->st;
            t4->dr = t3;
            strcpy(t4->info, "^");
            t4 = simplifica(t4);
            t5 = new arbore;
            t5->st = a->dr;
            t5->dr = t4;
            strcpy(t5->info, "*");
            t5 = simplifica(t5);
            derivare(a->st, t1);
            t1 = simplifica(t1);
            strcpy(d->info, "*");
            d->st = t5;
            d->dr = t1;
            d = simplifica(d);
        }
    }

    if (!strcmp("sin", a->info)) {
       arbore* t1;
       arbore* t2;
        t1 = new arbore;
        t1->st = NULL;
        t1->dr = NULL;
        t2 = new arbore;
        t2->st = a->st;
        t2->dr = NULL;
        strcpy(t2->info, "cos");
        derivare(a->st, t1);
        t1 = simplifica(t1);
        strcpy(d->info, "*");
        d->st = t2;
        d->dr = t1;
        d = simplifica(d);
    }

    if (!strcmp("cos", a->info)) {
       arbore* t1;
       arbore* t2;
       arbore* t3;
        t1 = new arbore;
        t1->st = NULL;
        t1->dr = NULL;
        t2 = new arbore;
        t2->st = a->st;
        t2->dr = NULL;
        strcpy(t2->info, "sin");
        t3 = new arbore;
        t3->st = NULL;
        t3->dr = NULL;
        derivare(a->st, t1);
        t1 = simplifica(t1);
        strcpy(t3->info, "*");
        t3->st = t2;
        t3->dr = t1;
        t3 = simplifica(t3);
        strcpy(d->info, "-");
        d->st = NULL;
        d->dr = t3;
        d = simplifica(d);
    }

    if (!strcmp("tg", a->info)) {
       arbore* t1;
       arbore* t2;
       arbore* t3;
       arbore* t4;
       arbore* t5;
       arbore* t6;
        t1 = new arbore;
        t1->st = NULL;
        t1->dr = NULL;
        strcpy(t1->info, "1");
        t2 = new arbore;
        t2->st = NULL;
        t2->dr = NULL;
        strcpy(t2->info, "2");
        t3 = new arbore;
        t3->st = a->st;
        t3->dr = NULL;
        strcpy(t3->info, "cos");
        t4 = new arbore;
        t4->st = t3;
        t4->dr = t2;
        strcpy(t4->info, "^");
        t4 = simplifica(t4);
        t5 = new arbore;
        t5->st = t1;
        t5->dr = t4;
        strcpy(t5->info, "/");
        t5 = simplifica(t5);
        t6 = new arbore;
        t6->st = NULL;
        t6->dr = NULL;
        derivare(a->st, t6);
        t6 = simplifica(t6);
        strcpy(d->info, "*");
        d->st = t5;
        d->dr = t6;
        d = simplifica(d);
    }

    if (!strcmp("ctg", a->info)) {
       arbore* t1;
       arbore* t2;
       arbore* t3;
       arbore* t4;
       arbore* t5;
       arbore* t6;
       arbore* t7;
       arbore* t8;
        t1 = new arbore;
        t1->st = NULL;
        t1->dr = NULL;
        strcpy(t1->info, "1");
        t2 = new arbore;
        t2->st = NULL;
        t2->dr = NULL;
        strcpy(t2->info, "2");
        t3 = new arbore;
        t3->st = a->st;
        t3->dr = NULL;
        strcpy(t3->info, "sin");
        t4 = new arbore;
        t4->st = t3;
        t4->dr = t2;
        strcpy(t4->info, "^");
        t4 = simplifica(t4);
        t5 = new arbore;
        t5->st = t1;
        t5->dr = t4;
        strcpy(t5->info, "/");
        t5 = simplifica(t5);
        t6 = new arbore;
        t6->st = NULL;
        t6->dr = NULL;
        derivare(a->st, t6);
        t6 = simplifica(t6);
        t8 = new arbore;
        t8->st = t5;
        t8->dr = t6;
        strcpy(t8->info, "*");
        t8 = simplifica(t8);
        strcpy(d->info, "-");
        d->st = NULL;
        d->dr = t8;
        d = simplifica(d);
    }

    if (!strcmp("ln", a->info)) {
      arbore* t1;
      arbore* t2;
      arbore* t3;
        t1 = new arbore;
        t1->st = NULL;
        t1->dr = NULL;
        strcpy(t1->info, "1");
        t2 = new arbore;
        t2->st = t1;
        t2->dr = a->st;
        strcpy(t2->info, "/");
        t2 = simplifica(t2);
        t3 = new arbore;
        t3->st = NULL;
        t3->dr = NULL;
        derivare(a->st, t3);
        t3 = simplifica(t3);
        strcpy(d->info, "*");
        d->st = t2;
        d->dr = t3;
        d = simplifica(d);
    }

    if (!strcmp("log", a->info)) {
       arbore* t1;
       arbore* t2;
       arbore* t3;
       arbore* t4;
       arbore* t5;
        t1 = new arbore;
        t1->st = NULL;
        t1->dr = NULL;
        strcpy(t1->info, "1");
        t2 = new arbore;
        t2->st = a->st;
        t2->dr = NULL;
        strcpy(t2->info, "ln");
        t3 = new arbore;
        t3->st = a->dr;
        t3->dr = t2;
        strcpy(t3->info, "*");
        t3 = simplifica(t3);
        t4 = new arbore;
        t4->st = t1;
        t4->dr = t3;
        strcpy(t4->info, "/");
        t4 = simplifica(t4);
        t5 = new arbore;
        t5->st = NULL;
        t5->dr = NULL;
        derivare(a->dr, t5);
        t5 = simplifica(t5);
        strcpy(d->info, "*");
        d->st = t4;
        d->dr = t5;
        d = simplifica(d);
    }

    if (!strcmp("lg", a->info)) {
       arbore* t1;
       arbore* t2;
       arbore* t3;
       arbore* t4;
       arbore* t5;
       arbore* t6;
        t1 = new arbore;
        t1->st = NULL;
        t1->dr = NULL;
        strcpy(t1->info, "1");
        t2 = new arbore;
        t2->st = NULL;
        t2->dr = NULL;
        strcpy(t2->info, "10");
        t3 = new arbore;
        t3->st = t2;
        t3->dr = NULL;
        strcpy(t3->info, "ln");
        t4 = new arbore;
        t4->st = a->st;
        t4->dr = t3;
        strcpy(t4->info, "*");
        t4 = simplifica(t4);
        t5 = new arbore;
        t5->st = t1;
        t5->dr = t4;
        strcpy(t5->info, "/");
        t5 = simplifica(t5);
        t6 = new arbore;
        t6->st = NULL;
        t6->dr = NULL;
        derivare(a->st, t6);
        t6 = simplifica(t6);
        strcpy(d->info, "*");
        d->st = t5;
        d->dr = t6;
        d = simplifica(d);
    }

     if (strchr("0123456789", a->info[0])) strcpy(d->info, "0");
       if (a->info[0] == 'x') strcpy(d->info, "1");

    return d;
}


void parcurge(arbore* a, char derivata[]) {
    if (a != NULL) {
        if (esteoperator2(a->info) == 1) {
            strcat(derivata, a->info);
            strcat(derivata, "(");
            parcurge(a->st, derivata);
            if (((a->info[0] == 'l') && (a->info[1] == 'o') && (a->info[2] == 'g')) || ((a->info[0] == 'r') && (a->info[1] == 'a') && (a->info[2] == 'd')))
                strcat(derivata, ",");
            parcurge(a->dr, derivata);
            strcat(derivata, ")");
        }
        else {
            parcurge(a->st, derivata);
            strcat(derivata, a->info);
            if ((a->dr != NULL) && (prioritate1(a->info) > prioritate1(a->dr->info))) {
                strcat(derivata, "(");
                parcurge(a->dr, derivata);
                strcat(derivata, ")");
            }
            else parcurge(a->dr, derivata);
        }

    }
}


void titlu(int x, int y, char* n) {
    settextstyle(4, 0, 5);
    setcolor(12);
    setlinestyle(0, 0, 7);

    setfillstyle(EMPTY_FILL, 2);
    outtextxy(x, y, n);
}

int optiuni() {

setlinestyle(0, 0, 3);
    rectangle(600, 100, 1020, 185);
    settextstyle(4, 0, 4);
    outtextxy(620, 123, "Meniu");

    setlinestyle(0, 0, 3);
    rectangle(600, 185, 1022, 249);
    settextstyle(4, 0, 2);
    outtextxy(660, 210, "Informatii");

    rectangle(600, 249, 1022, 313);
    settextstyle(4, 0, 2);
    outtextxy(620, 262, "Preluati formula");
    outtextxy(660, 282, "de la tastatura");

    rectangle(600, 313, 1022, 377);
    settextstyle(4, 0, 2);
    outtextxy(620, 326, "Preluati formula");
    outtextxy(660, 346, "din fisierul proiect.in");

    rectangle(600, 377, 1022, 441);
    settextstyle(4, 0, 2);
    outtextxy(620, 398, "Notatia postfixata");

    rectangle(600, 441, 1022, 505);
    settextstyle(4, 0, 2);
    outtextxy(620, 462, "Arborele formulei");

    rectangle(600, 505, 1022, 569);
    settextstyle(4, 0, 2);
    outtextxy(660, 526, "Derivata");

    rectangle(600, 569, 1022, 633);
    settextstyle(4, 0, 2);
    outtextxy(620, 590, "Derivata de ordinul 2");

    rectangle(600, 633, 1022, 697);
    settextstyle(4, 0, 2);
    outtextxy(660, 654, "Iesire");

   int x, y;

    while (!ismouseclick(WM_LBUTTONDOWN)) {
        x = mousex();
      y = mousey();
    }

    if (x > 600 && x < 1022 && y > 185 && y < 249)
      return 1;
    else if (x > 600 && x < 1022 && y>249 && y < 313)
        return 2;
    else if (x > 600 && x < 1022 && y>313 && y < 377)
        return 3;
    else if (x > 600 && x < 1022 && y>377 && y < 441)
        return 4;
    else if (x > 600 && x < 1022 && y>441 && y < 505)
        return 5;
    else if (x > 600 && x < 1022 && y>505 && y < 569)
        return 6;
    else if (x > 600 && x < 1022 && y>569 && y < 633)
        return 7;
    else if (x > 600 && x < 1022 && y>633 && y < 697)
        return 0;

return 0;
}



void meniu() {

    clearmouseclick(WM_LBUTTONDOWN);

    if (optiuni()==0) {
        exit(0);
    }
    if (optiuni()==1) {

        setactivepage(0);
        titlu(250, 30, "Derivare formala");
        optiuni();
        bar(1023, 103, 1400, 697);
        setvisualpage(0);
        outtextxy(30, 110, "1.Programul accepta ca operanzi numere ");
        outtextxy(50, 132, " intregi si numere rationale (pentru cele ");
        outtextxy(50, 152, "rationale se va folosi '.' ca");
        outtextxy(50, 176, "separator), iar ca si variabila, ");
         outtextxy(50, 198, "programul accepta 'x'.");
        outtextxy(50, 216, "2.   Notatia postfixata, derivata intai si");
         outtextxy(50, 238, "derivata de ordinul al doilea vor  ");
        outtextxy(50, 258, " fi salvate in fisierul proiect.out.");
        meniu();
    }
    if (optiuni()==2) {
        clearviewport();
        titlu(250, 30, " Derivare formala");
        optiuni();
        bar(1023, 103, 1400, 697);
        memset(infix, NULL, 100);
        char c;
        int pozitie = 0;
        outtextxy(50, 110, "Preluati formula de la tastatura:");
        c = getch();
        while (c != 13) {
            if (c == 8) {
                pozitie--;
                infix[pozitie] = '\0';

                titlu(250, 30, " Derivare formala");
                optiuni();
                bar(1023, 103, 1200, 697);
                outtextxy(50, 110, "Preluati formula de la tastatura:");
            }
            else {
                infix[pozitie] = c;
                pozitie++;
                infix[pozitie] = '\0';
            }
            outtextxy(50, 132, infix);
            c = getch();
        }
        meniu();

    }

    if (optiuni()==3) {
        setactivepage(0);
        clearviewport();
        titlu(250, 30, "Derivare formala");
        optiuni();
        bar(1023, 103, 1400, 697);
        setvisualpage(0);
        memset(infix, NULL, 100);
        fin >> infix;
        outtextxy(50, 110, "Preluati formula din fisierul proiect.in:");
        outtextxy(50, 132, infix);
        meniu();

    }
    if (optiuni()==4) {
        clearviewport();
        memset(postfixata, NULL, 100);
        titlu(250, 30, "Derivare formala");
        optiuni();
        bar(1023, 103, 1400, 697);
        initializeazacoada(postfix);
        conversieinfixpostfix(infix, postfix);
        fout << "Notatia postfixata a expresiei " << infix << " este: ";
        afiseaza(postfix);
        fout << endl;
        outtextxy(50, 110, "Notatia postfixata a expresiei este:");
        outtextxy(50, 132, postfixata);
        meniu();


    }
    if (optiuni()==5) {
        clearviewport();
        setactivepage(0);
        titlu(250, 30, "Derivare formala");
        optiuni();
        bar(1023, 103, 1400, 697);
        setvisualpage(0);

        initializeazacoada(postfix);
        conversieinfixpostfix(infix, postfix);
        stivaarbore S;
        initializeazastivaarbore(S);
        Elementearbore(postfix, S);

        outtextxy(50, 110, "Arborele expresiei este:");

         int height = 697, width = 1200;
        int window1 = initwindow(width, height, "Arborele formulei");
        setcurrentwindow(window1);
        setcolor(WHITE);
        setbkcolor(BLACK);
        cleardevice();
        rectangle(1, 1, width - 1, height - 1);
        int latime, inaltime;
        latime = width / nrColoane(S.varf->info);
        inaltime = height / nrNiveluri(S.varf->info);
        deseneazaArbore(S.varf->info, 1, 0, latime, inaltime);
        setcolor(12);
        setlinestyle(0, 0, 2);

        settextstyle(4, 0, 2);
        setbkcolor(BLACK);
        outtextxy(1125, 35, "INAPOI");
        int coordx, coordy;
        clearmouseclick(WM_LBUTTONDOWN);
        while (!ismouseclick(WM_LBUTTONDOWN)) {
            coordx = mousex();
            coordy = mousey();
        }
        if (coordx > 1030 && coordx < 1180 && coordy > 20 && coordy < 70)
            closegraph(CURRENT_WINDOW);

        setcurrentwindow(0);
        meniu();

    }
     if (optiuni()==6) {
        clearviewport();
        setactivepage(0);
        titlu(250, 30, "Derivare formala");
        optiuni();
        bar(1023, 103, 1400, 697);
        setvisualpage(0);

        initializeazacoada(postfix);
        conversieinfixpostfix(infix, postfix);
        stivaarbore S;
        initializeazastivaarbore(S);
        Elementearbore(postfix, S);

        arbore* d;
        d = new arbore;
        d->st = NULL;
        d->dr = NULL;
        d = derivare(S.varf->info, d);

        memset(primaderivata, NULL, 200);
        parcurge(d, primaderivata);
        outtextxy(50, 110, "Derivata expresiei este:");

        if (strlen(primaderivata) < 50)
            outtextxy(50, 136, primaderivata);
        else if (strlen(primaderivata) < 100) {
            char sir[50];
            strncpy(sir, primaderivata, 50);
            sir[50] = NULL;
            outtextxy(50, 136, sir);
            outtextxy(50, 158, primaderivata + 50);
        }
        else {
            char sir1[50], sir2[50];
            strncpy(sir1, primaderivata, 50);
            sir1[50] = NULL;
            strncpy(sir2, primaderivata + 51, 50);
            sir2[50] = NULL;
            outtextxy(50, 136, sir1);
            outtextxy(50, 158, sir2);
            outtextxy(50, 178, primaderivata + 100);
        }

        fout << "Derivata expresiei " << infix << " este: " << primaderivata << endl;

        setcurrentwindow(0);
        meniu();

    }
     if (optiuni()==7) {
         clearviewport();
        setactivepage(0);
        titlu(250, 30, "Derivare formala");
        optiuni();
        bar(1023, 103, 1400, 697);
        setvisualpage(0);

        initializeazacoada(postfix);
        conversieinfixpostfix(infix, postfix);
        stivaarbore S;
        initializeazastivaarbore(S);
         Elementearbore(postfix, S);

        arbore* d;
        d = new arbore;
        d->st = NULL;
        d->dr = NULL;
        d = derivare(S.varf->info, d);

        arbore* d1;
        d1 = new arbore;
        d1->st = NULL;
        d1->dr = NULL;
        d1 = derivare(d, d1);

        memset(adouaderivata, NULL, 200);
        parcurge(d1, adouaderivata);
        outtextxy(50, 110, "Derivata de ordinul 2 a expresiei este:");
        if (strlen(adouaderivata) < 50)
            outtextxy(50, 132, adouaderivata);
        else if (strlen(adouaderivata) < 100) {
            char sir[50];
            strncpy(sir, adouaderivata, 50);
            sir[50] = NULL;
            outtextxy(50, 132, sir);
            outtextxy(50, 154, adouaderivata + 50);
        }
        else {
            char sir1[50], sir2[50];
            strncpy(sir1, adouaderivata, 50);
            sir1[50] = NULL;
            strncpy(sir2, adouaderivata + 51, 50);
            sir2[50] = NULL;
            outtextxy(50, 132, sir1);
            outtextxy(50, 154, sir2);
            outtextxy(50, 176, adouaderivata + 100);
        }

        fout << "Derivata de ordinul 2 a expresiei " << infix << " este: " << adouaderivata << endl;
        meniu();

    }

    }

int main() {
    PlaySound(TEXT("sound.wav"),NULL,SND_FILENAME|SND_ASYNC);
    initwindow(1200, 697, "Derivare formala");
    titlu(250, 30, "Derivare formala");
    optiuni();
    meniu();
    return 0;
}

