#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import heapq
import sys

class edge:
    destination = 0
    distance = float('inf')
    def __init__(self, destination, distance):
        self.distance = distance
        self.destination = destination

class vertex:
    def __init__(self):
        self.distance = float('inf')
        self.visited = False
        self.in_queue = False
        self.parent = 0
        self.neighbors = []
    
    
class node:
    index = 0
    distance = float('inf')
    def __init__(self, index, distance):
        self.index = index
        self.distance = distance
    def __lt__(self, other):
        return (self.distance <= other.distance)

    
def dijkstra(graph, source, destination):
    q = []
    graph[source].distance = 0
    current = 0
    heapq.heappush(q, node(source, graph[source].distance))
    while q:
        current = heapq.heappop(q).index
        if current == destination:
            return graph[current].distance
        graph[current].visited = True;
        for e in graph[current].neighbors:
            if graph[e.destination].distance > graph[current].distance + e.distance and not graph[e.destination].visited:
                graph[e.destination].distance = graph[current].distance + e.distance;
                graph[e.destination].parent = current;
                heapq.heappush(q, node(e.destination, graph[e.destination].distance))
    return float('inf');
    
    
    
source  = int(sys.argv[1])
destination = int(sys.argv[2])

size_line = sys.stdin.readline()
size = int(size_line)

graph = []
for i in range(size):
    graph.append(vertex())

line = sys.stdin.readline()
while line:
    numbers = line.split()
    a = int(numbers[0])
    b = int(numbers[1])
    dist = float(numbers[2])
    graph[a].neighbors.append(edge(b, dist))
    graph[b].neighbors.append(edge(a, dist))
    
    line = sys.stdin.readline()
print("wczytałem.")
print (dijkstra(graph, source, destination)) 


