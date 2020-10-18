/* test.c
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "chm_lib.h"
#include "glib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* return true if s contains ',' */
static bool needs_csv_escaping(const char* s) {
    while (*s && (*s != ',')) {
        s++;
    }
    return *s == ',';
}
static uint8_t* extract_entry(struct chm_file* h, chm_entry* e) {
    int64_t len = (int64_t)e->length;

    uint8_t* buf = (uint8_t*)malloc((size_t)len + 1);
    if (buf == NULL) {
        return NULL;
    }
    buf[len] = 0; /* null-terminate just in case */

    int64_t n = chm_retrieve_entry(h, e, buf, 0, len);
    if (n != len) {
        free(buf);
        return NULL;
    }
    return buf;
}

static bool process_entry(struct chm_file* h, chm_entry* e) {
    char buf[128] = {0};
    gchar *sha1 = {0};

    int isFile = e->flags & CHM_ENUMERATE_FILES;

    if (e->flags & CHM_ENUMERATE_SPECIAL)
        strcpy(buf, "special_");
    else if (e->flags & CHM_ENUMERATE_META)
        strcpy(buf, "meta_");

    if (e->flags & CHM_ENUMERATE_DIRS)
        strcat(buf, "dir");
    else if (isFile)
        strcat(buf, "file");

    if (e->length > 0) {
        uint8_t* d = extract_entry(h, e);
        if (d != NULL) {
            sha1 = g_compute_checksum_for_data (G_CHECKSUM_SHA1, d, e->length);
        }
    }

    if (needs_csv_escaping(e->path)) {
        printf("%d,%d,%d,%s,%s,\"%s\"\n", (int)e->space, (int)e->start, (int)e->length, buf,
               sha1, e->path);
    } else {
        printf("%1d,%d,%d,%s,%s,%s\n", (int)e->space, (int)e->start, (int)e->length, buf, sha1,
               e->path);
    }
    return true;
}

static bool test_chm(chm_file* h) {
    for (int i = 0; i < h->n_entries; i++) {
        if (!process_entry(h, h->entries[i])) {
            printf("   *** ERROR ***\n");
            return false;
        }
    }
    if (h->parse_entries_failed) {
        printf("   *** ERROR ***\n");
    }
    return true;
}

static bool test_fd(const char* path) {
    fd_reader_ctx ctx;
    if (!fd_reader_init(&ctx, path)) {
        fprintf(stderr, "failed to open %s\n", path);
        return false;
    }
    chm_file f;
    bool ok = chm_parse(&f, fd_reader, &ctx);
    if (!ok) {
        fprintf(stderr, "chm_parse() failed\n");
        fd_reader_close(&ctx);
        return false;
    }
    ok = test_chm(&f);
    chm_close(&f);
    fd_reader_close(&ctx);
    return ok;
}

static bool show_dbg_out = false;

static void dbg_print(const char* s) {
    fprintf(stderr, "%s", s);
}

int main(int c, char** v) {
    if (c < 2) {
        fprintf(stderr, "usage: %s <chmfile>\n", v[0]);
        exit(1);
    }
    if (show_dbg_out) {
        chm_set_dbgprint(dbg_print);
    }
    bool ok = test_fd(v[1]);
    if (ok) {
        return 0;
    }
    return 1;
}
