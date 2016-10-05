# GiA
A GUI-oriented, graph problem-solving C++ software.

## About
*GiA* is a software built in **C++** programming language with **Qt5** library. It allows a user to input a desired graph and run a desired graph algorithm (such as *finding shortest paths*, *constructing a minimum cost spanning tree*, *finding transitive closure*, ...) on it.

## Usage

Currently, the user is able to create nodes, create edges, move nodes along with adjacent edges, and create a new graph.
- To create a node, just click on *Add node* button, and a new node will appear. You can drag & drop nodes everywhere around the *Graph creating area*.
- To create an edge, double click on a node where you want an edge to begin (the selected node will be highlighted in red), and double click on another node where you want edge to end, and a new edge will appear. To cancel edge creation, just double click on a beginning edge. Currently, loops are not supported.
- To insert a weighted edge, just tick the *Weighted graph* checkbox, and create an edge. The input dialog will appear.
- To edit edge's weight, simply click on the edge's weight and edit it.
- If you move a node, all adjacent edges will be moved with it.
- To create a new graph, just click on *New graph* button.

## Development
GiA is in a very early development stage. You can see the list of the things that have been successfully developed so far, as well as the next feature that is being worked on right now.
- [x] GUI prototype completed
- [ ] Graphic representation of graph implemented
  - [x] Creation of nodes
  - [x] Creation of edges
  - [ ] Deletion of nodes
  - [ ] Deletion of edges
- [x] Implement basic graph procedures
  - [x] Add node
  - [x] New graph
  - [x] Insert a weighted edge
  - [x] Change edge's weight
- [ ] Graph model implemented
  - [x] Chosen and implemented data structure
  - [ ] Implemented saving/loading a graph to/from a file
- [ ] Implemented algorithms
  - [ ] Depth-First Search
  - [ ] Breadth-First Search
  - [ ] ...
- [ ] ...

## Contact
If you want to contact the developer, send an email to [ajzenhamernikola@gmail.com](mailto:ajzenhamernikola@gmail.com) with the subject starting with "\[GiA\]".
