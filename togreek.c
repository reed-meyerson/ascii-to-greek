#include <stdio.h>
#include <stdint.h>
#include "letters.h"

#define ACUTE_CHAR '/'
#define GRAVE_CHAR '\\'
#define CIRC_CHAR '^'
#define ROUGH_CHAR '`'
#define SMOOTH_CHAR '\''
#define ISUB_CHAR '_'
#define LAST_CHAR '>'
#define MACRON_CHAR '~'

#define GREEK2HEX(g) ((uint16_t) (g & 0xFFFF))
#define GREEK2DESC(g) (g & 0xFFFF0000)
#define LATIN(c) (('A' <= c && c <= 'Z') \
					|| ('a' <= c && c <= 'z'))
#define MODIFIER(c) (c == ACUTE_CHAR \
					|| c == GRAVE_CHAR \
					|| c == CIRC_CHAR \
					|| c == ROUGH_CHAR \
					|| c == SMOOTH_CHAR \
					|| c == ISUB_CHAR \
					|| c == MACRON_CHAR \
					|| c == LAST_CHAR)

/* assumes hex <= 0xFFFF */
uint32_t hex2unicode(uint16_t hex) {
	uint32_t bighex;
	bighex = (uint32_t) hex;
	if(hex <= 0x7Fu) {
		return bighex;
	} else if(bighex <= 0x07FFu) {
		return (bighex << 2 & 0xFF00u) | (bighex & 0x3Fu) | 0xC080u;
	} else {
		return (bighex << 4 & 0xFF0000u) | (bighex << 2 & 0x3F00u) | (bighex & 0x3Fu) | 0xE08080u;
	}
}

/* assumes ucode <= 0xFFFFFF */
void printUnicode(uint32_t ucode) {
	if(ucode <= 0xFF) {
		printf("%c", (uint8_t) ucode);
	} else if(ucode <= 0xFFFF) {
		printf("%c%c", (uint8_t) (ucode >> 8 & 0xFFu), (uint8_t) (ucode & 0xFFu));
	} else {
		printf("%c%c%c", (uint8_t) (ucode >> 16 & 0xFFu), (uint8_t) (ucode >> 8 & 0xFFu), (uint8_t) (ucode & 0xFFu));
	}
}

/* if it is in the list, then returns zero and puts
 * the hex value in *hex, else returns -1 */
/* buff[i] should be the ASCII letter, and earlier
	entries should be modifiers */
int lookupGreek(uint8_t *buff, int i, uint16_t *hex) {
	uint32_t key = ((uint32_t) buff[i]) << 24;
	int j;
	for(j = 0; j < i; j++) {
		switch(buff[j]) {
			case ACUTE_CHAR:
				if(key & Acute)
					return -1;
				key |= Acute;
				break;
			case GRAVE_CHAR: 
				if(key & Grave)
					return -1;
				key |= Grave;
				break;
			case CIRC_CHAR:
				if(key & Circ)
					return -1;
				key |= Circ;
				break;
			case SMOOTH_CHAR:
				if(key & Smooth)
					return -1;
				key |= Smooth;
				break;
			case ROUGH_CHAR:
				if(key & Rough)
					return -1;
				key |= Rough;
				break;
			case ISUB_CHAR:
				if(key & ISub)
					return -1;
				key |= ISub;
				break;
			case MACRON_CHAR:
				if(key & Macron)
					return -1;
				key |= Macron;
				break;
			case LAST_CHAR:
				if(key & Last)
					return -1;
				key |= Last;
				break;
		}
	}
	/* binary search */
	int lo, hi, mid;
	lo = 0;
	hi = NUM_LETTERS;
	while(lo < hi) {
		mid = (lo + hi) / 2;
		if(key < GREEK2DESC(letters[mid])) {
			hi = mid;
		} else if(GREEK2DESC(letters[mid]) < key) {
			lo = mid + 1;
		} else {
			*hex = GREEK2HEX(letters[mid]);
			return 0;
		}
	}
	return -1;
}

struct CircBuff {
	uint8_t buff[4];
	uint8_t beg;
	uint8_t size;
};

void empty(struct CircBuff *b) {
	b->beg = 0;
	b->size = 0;
}

/* if there is room, adds new to buffer
	if there is no room, prints first element, then
	adds new and rotates */
void push(struct CircBuff *b, uint8_t new) {
	if(b->size < 4) {
		b->buff[(b->beg + b->size) % 4] = new;
		b->size += 1;
	} else {
		printf("%c",b->buff[b->beg]);
		b->buff[b->beg] = new;
		b->beg = (b->beg + 1) % 4;
	}
}

void flush(struct CircBuff *b) {
	int i;
	for(i = 0; i < b->size; i++) {
		printf("%c", b->buff[(b->beg + i) % 4]);
	}
	empty(b);
}

/* assumes char is in buff[beg+size-1 mod 4] */
void process(struct CircBuff *b) {
	uint8_t unwrap[4];
	uint16_t hex;
	int i;
	while(b->size > 0) {
		for(i = 0; i < b->size; i++) {
			unwrap[i] = b->buff[(b->beg + i) % 4];
		}
		if(lookupGreek(unwrap, b->size - 1, &hex) == -1) {
			printf("%c", b->buff[b->beg]);
			b->beg = (b->beg + 1) % 4;
			b->size -= 1;
		} else {
			printUnicode(hex2unicode(hex));
			empty(b);
		}
	}
}

int main () {
	struct CircBuff b;
	b.beg = 0;
	b.size = 0;
	int c;
	while((c = getchar()) != EOF) {
		push(&b, (uint8_t) c);
		if(LATIN(c)) {
			process(&b);
		} else if(!MODIFIER(c)) {
			flush(&b);
		}
	}
	flush(&b);
	return 0;
}
