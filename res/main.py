
out = open('itu-t81-2.otl', 'w');

with open('itu-t81.otl', 'r') as f:
	for l in f:
		words = l.split(' ');
		words[1] = str(int(words[1]) + 4)
		out.write(' '.join(words));

out.close();