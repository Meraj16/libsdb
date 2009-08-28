/*
 * base64.c
 * Amazon SimpleDB C bindings
 *
 * Created by Peter Macko on 1/23/09.
 *
 * Copyright 2009
 *      The President and Fellows of Harvard College.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *
 * This file includes parts of http://base64.sourceforge.net/b64.c
 * Copyright (c) 2001 Bob Trower, Trantor Standard Systems Inc.
 */

#include <stdio.h>
#include <stdlib.h>
 

/*
 * Translation Table as described in RFC1113
 * 
 * Taken from: http://base64.sourceforge.net/b64.c
 */
static const char cb64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


/**
 * Encode a block
 *
 * @param in three 8-bit binary input bytes
 * @param out the buffer to store the four output '6-bit' characters
 * @param len the length of the input buffer 
 */
void encodeblock(const unsigned char* in, unsigned char* out, int len)
{
	// Taken from: http://base64.sourceforge.net/b64.c
	
    out[0] = cb64[ in[0] >> 2 ];
    out[1] = cb64[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
    out[2] = (unsigned char) (len > 1 ? cb64[ ((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6) ] : '=');
    out[3] = (unsigned char) (len > 2 ? cb64[ in[2] & 0x3f ] : '=');
}


/**
 * Encode a buffer using base64 
 *
 * @param input the input buffer
 * @param output the output buffer (must be large enough to receive the entire output)
 * @param length the length of the input buffer
 * @return the length of the output
 */
int encode64(const char* input, char* output, int length)
{
	unsigned char in[3];
	int i, j, bytes = 0;
	
	for (j = 0; j < length; j += 3) {
	
		int len = length - j;
		if (len >= 3) len = 3;
		for (i = 0; i < len; i++) in[i] = input[j + i];
		for (i = len; i < 3; i++) in[i] = 0; 
		
		if (len > 0) {
			encodeblock(in, (unsigned char*) output + bytes, len);
			bytes += 4;
		}
	}
	
	output[bytes] = '\0';
	return bytes;
}
