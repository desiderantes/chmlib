/* lzx.c - LZX decompression routines
 *
 * Copyright 2020 Jed Wing <jedwin@ugcs.caltech.edu>
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

/*
 *  source:     modified lzx.c from cabextract v0.5
 *  notes:      This file was taken from cabextract v0.5, which was,
 *              itself, a modified version of the lzx decompression code
 *              from unlzx.
 */

#ifndef INCLUDED_LZX_H
#define INCLUDED_LZX_H

#ifdef __cplusplus
extern "C" {
#endif

/* return codes */
#define DECR_OK (0)
#define DECR_DATAFORMAT (1)
#define DECR_ILLEGALDATA (2)
#define DECR_NOMEMORY (3)

/* opaque state structure */
struct lzx_state;

/* create an lzx state object */
struct lzx_state* lzx_init(int window);

/* destroy an lzx state object */
void lzx_teardown(struct lzx_state* pState);

/* reset an lzx stream */
void lzx_reset(struct lzx_state* pState);

/* decompress an LZX compressed block */
int lzx_decompress(struct lzx_state* pState, unsigned char* inpos, unsigned char* outpos, int inlen,
                   int outlen);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDED_LZX_H */
