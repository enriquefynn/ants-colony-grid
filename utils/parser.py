
def main():
	import sys
	if len(sys.argv) < 4:
		print "Usage: :\n{} <filename> <maxGrid> <N (NxN)>".format(sys.argv[0])
		sys.exit(1)
	parse(sys.argv[1], sys.argv[2], sys.argv[3])


def parse(filename, gridMax, n):
	ids = {}
	lastId = 0
	gridDiv = int(gridMax)/int(n)
	f = open(filename, 'r')
	for line in f:
		data = "{1} {2} {3}".format(*line.split()).split()
		if data[0] not in ids:
			ids[data[0]] = lastId
			lastId+=1
		x = float(data[1])/gridDiv
		y = float(data[2])/gridDiv
		print "{0} {1} {2}".format(ids[data[0]], int(x), int(y)) 

if __name__ == "__main__":
	main()
