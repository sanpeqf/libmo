/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright(c) 2022 John Sanpe <sanpeqf@gmail.com>
 */

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <libmo.h>

#ifndef DEFAULT_LANG
# define DEFAULT_LANG "C"
#endif

static void load_context(struct libmo_context *moctx, const char *path)
{
    struct stat stat;
    void *block;
    int fd;

    if ((fd = open(path, O_RDONLY)) < 0)
        err(errno, "can not open file");

    if (fstat(fd, &stat) < 0)
        err(errno, "fstat error");

    block = mmap(NULL, stat.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (block == MAP_FAILED)
        err(errno, "mmap error");

    if ((errno = libmo_load(moctx, block, stat.st_size)))
        err(errno, "libmo load error");

    if ((errno = libmo_verify(moctx)))
        err(errno, "libmo verify error");
}

static char *get_domain(void)
{
    char *value, *delimiter;

    value = getenv("LANG");
    if (!value || !*value)
        return DEFAULT_LANG;

    delimiter = strchr(value, '.');
    if (delimiter)
        *delimiter = '\0';

    return value;
}
