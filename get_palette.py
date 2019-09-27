import sys
import pdb
import colourlovers
import re

ids = sys.argv[1:]

gammas = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2,
2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5,
5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10,
10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255]

def HTMLColorToRGB(colorstring):
	""" convert RRGGBB to an (R, G, B) tuple """
	if len(colorstring) == 6:
		r, g, b = colorstring[:2], colorstring[2:4], colorstring[4:]
		r, g, b = [int(n, 16) for n in (r, g, b)]
		return (r, g, b)

client = colourlovers.ColourLovers()
with open('Colors.h', 'w') as colors:
	for id in ids:
		print("fetching %s ... " % int(id), end='')
		palette = client.palette(int(id))[0]
		print(palette.title)
		colors.write('//%s %s\n' % (palette.title, palette.url))
		for hex in palette.colours:
			print('\tfetching %s ... ' % hex, end='')
			color = client.color(hex)[0]
			print(color.title)
			name = re.sub(r'[\W]+','_', color.title).lower()
			r, g, b = HTMLColorToRGB(hex[1:])
			colors.write('#define %s Color((uint8_t)%d, (uint8_t)%d, (uint8_t)%d)\n' % (name, gammas[r], gammas[g], gammas[b]))
		colors.write('\n')
