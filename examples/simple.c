/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright(c) 2022 John Sanpe <sanpeqf@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include "helper.c"

/* Define shortcut for gettext(). */
struct libmo_context moctx;
#define _(string) libmo_gettext(&moctx, string)

int main(int argc, char *argv[])
{
    char *path, *domain;

    domain = get_domain();
    if (strcmp(domain, "C")) {
        asprintf(&path, "examples/simple-mo/%s.mo", domain);
        printf("load machine object file: %s\n", path);
        load_context(&moctx, path);
        free(path);
    }

    printf("%s\n", _("Hello, world!"));
    printf(_("This program is running as process number %d."), getpid());
    putchar('\n');

    return 0;
}
