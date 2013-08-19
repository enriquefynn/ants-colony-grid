#!/usr/bin/python

import networkx as nx

def main(filename):
	G = buildGraph(filename)
	printGraph(G)

def buildGraph(filename):
	f = open(filename, 'r')
	G = nx.DiGraph()
	import ast
	for line in f:
		l = []
		splited = line.split()
		for edge in splited[1:]:
			(y, w) = ast.literal_eval(edge)
			l.append((splited[0], y, w))
		G.add_weighted_edges_from(l)
	return G
def printGraph(G):
	import matplotlib.pyplot as plt
	nx.draw(G)
	plt.show()
	plt.savefig("graph.png")


if __name__ == "__main__":
	import sys
	main(sys.argv[1])
	
