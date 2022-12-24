/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright(c) 2022 Sanpe <sanpeqf@gmail.com>
 */

#include <libmo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

/* Define shortcut for gettext(). */
struct libmo_context moctx;
#define _(string) libmo_lookup(&moctx, string, 0, NULL)

static void load_context(const char *path)
{
    struct stat stat;
    void *block;
    int fd;

    if ((fd = open(path, O_RDWR)) < 0)
        err(errno, "can not open file");

    if (fstat(fd, &stat) < 0)
        err(errno, "fstat error");

    block = mmap(NULL, stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (block == MAP_FAILED)
        err(errno, "mmap error");

    if ((errno = libmo_load(&moctx, block, stat.st_size)))
        err(errno, "load error");

    if ((errno = libmo_verify(&moctx)))
        err(errno, "verify error");
}

int main(void)
{
    load_context("examples/simple.mo");
    printf("%s", _("Hello, world!\n"));
    printf(_("This program is running as process number %d.\n"), getpid());
    return 0;
}
