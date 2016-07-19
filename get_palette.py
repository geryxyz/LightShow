import sys
import pdb
import colourlovers
import re

ids = sys.argv[1:]

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
			colors.write('#define %s Color((uint8_t)%d, (uint8_t)%d, (uint8_t)%d)\n' % (name, r, g, b))
		colors.write('\n')
