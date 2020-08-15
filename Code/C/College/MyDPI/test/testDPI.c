/*
 * testDPI.c
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

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int on = 1;

void cleanup(int sig) {
    on = 0;

    sleep(10);
    int ret = system("rm -rf phd*");
    exit(0);
}

int main() {
    signal(SIGINT, cleanup);
    while (on) {
        int ret = system("wget sadjad.me/phd > /dev/null");
#if SLOW
        sleep(1);
#else
        sleep(0);
#endif
    }
    return 0;
}
