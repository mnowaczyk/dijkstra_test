#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#generator wielkiego grafu typu kratka o boku n węzłów
from random import randint
from sys import argv

def generate(n):
    nodes = list(range(n*n))
    edges = []
    for i in range(n):
        for j in range(n):
            if i < n-1:
                edges.append((i*n+j, (i+1)*n+j, randint(1,10)))
#               edges.append((i*n+j, (i+1)*n+j, 1))
            if j < n-1:
                edges.append((i*n+j, i*n+j+1, randint(1, 10)))
#               edges.append((i*n+j, i*n+j+1, 1))
    return {'nodes': nodes, 'edges': edges}

size = int(argv[1])

data = generate(size)

print(size*size)

#for node in data['nodes']:
#    print(node)

for edge in data['edges']:
    print(edge[0], " ", edge[1], " ", edge[2])
