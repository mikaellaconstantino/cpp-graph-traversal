# C++ Graph Traversal — BFS Treasure Hunt

A C++ implementation of Breadth-First Search (BFS) 
graph traversal developed as part of a programming 
course at the University of the Philippines Diliman.

## Problem Overview
Given a graph of nodes labeled as:
- **C** — Clear node (safe to traverse)
- **T** — Trap node (skip, cannot pass through)
- **R** — Reward/Treasure node (destination)

Find the shortest safe path from node 0 to the 
treasure node while avoiding traps.

## How It Works
1. Reads graph input (nodes and edges)
2. Builds an adjacency list representation
3. Performs BFS from node 0
4. Skips trap nodes during traversal
5. Returns the first path that reaches the 
   treasure node

## Input Format
n m          (number of nodes and edges)
L1 L2 ... Ln (node labels: C, T, or R)
u1 v1        (edges)
u2 v2
...

## Example
Input:
5 4
C C T C R
0 1
1 2
2 3
3 4
Output:
0 1 3 4

## Key Concepts
- **Adjacency List** representation of graphs
- **BFS** for shortest path finding
- **Path tracking** via queue of vectors
- **Node labeling** for conditional traversal

## Technologies Used
- **Language:** C++
- **Concepts:** Graph Theory, BFS, Adjacency Lists,
  Pathfinding, Data Structures, Queue Operations

## Course
Programming and Data Structures  
University of the Philippines Diliman

## Status
Completed — University Laboratory Exercise
