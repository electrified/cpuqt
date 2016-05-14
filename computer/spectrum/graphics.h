#pragma once

#include <cstdint>

std::uint16_t memoryAddressToGfx(std::uint16_t i) {

  return ((i & 0x700) >> 8) | ((i & 0xe0) >> 2) | ((i & 0x1800) >> 5);
}

/*
 *
Color number	Binary value	BRIGHT 0 (RGB)	BRIGHT 1 (RGB)	Color name
0	000	#000000	#000000	black
1	001	#0000CD	#0000FF	blue
2	010	#CD0000	#FF0000	red
3	011	#CD00CD	#FF00FF	magenta
4	100	#00CD00	#00FF00	green
5	101	#00CDCD	#00FFFF	cyan
6	110	#CDCD00	#FFFF00	yellow
7	111	#CDCDCD	#FFFFFF	white
 *
 */