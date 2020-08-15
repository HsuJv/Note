/*
 * except.c
 * Copyright (C) 2019-2019 by jovi Hsu(jv.hsu@outlook.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "except.h"
#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#define T Except_T
Except_Frame *Except_stack = NULL;
void Except_raise(const T *e, const char *file, int line) {
#ifdef WIN32
    Except_Frame *p;

    if (Except_index == -1) Except_init();
    p = TlsGetValue(Except_index);
#else
    Except_Frame *p = Except_stack;
#endif
    assert(e);
    if (p == NULL) {
        fprintf(stderr, "Uncaught exception");
        if (e->reason)
            fprintf(stderr, " %s", e->reason);
        else
            fprintf(stderr, " at 0x%p", e);
        if (file && line > 0) fprintf(stderr, " raised at %s:%d\n", file, line);
        fprintf(stderr, "aborting...\n");
        fflush(stderr);
        abort();
    }
    p->exception = e;
    p->file = file;
    p->line = line;
#ifdef WIN32
    Except_pop();
#else
    Except_stack = Except_stack->prev;
#endif
    longjmp(p->env, Except_raised);
}
#ifdef WIN32
_CRTIMP void __cdecl _assert(void *, void *, unsigned);
#undef assert
#define assert(e) ((e) || (_assert(#e, __FILE__, __LINE__), 0))

int Except_index = -1;
void Except_init(void) {
    BOOL cond;

    Except_index = TlsAlloc();
    assert(Except_index != TLS_OUT_OF_INDEXES);
    cond = TlsSetValue(Except_index, NULL);
    assert(cond == TRUE);
}

void Except_push(Except_Frame *fp) {
    BOOL cond;

    fp->prev = TlsGetValue(Except_index);
    cond = TlsSetValue(Except_index, fp);
    assert(cond == TRUE);
}

void Except_pop(void) {
    BOOL cond;
    Except_Frame *tos = TlsGetValue(Except_index);

    cond = TlsSetValue(Except_index, tos->prev);
    assert(cond == TRUE);
}
#endif