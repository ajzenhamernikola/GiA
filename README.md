# GiA
A GUI-oriented, graph problem-solving C++ software.

## About
*GiA* is a software built in **C++** programming language with **Qt5** libraries. It allows a user to input a desired graph and run a desired graph algorithm (such as *finding shortest paths*, *constructing a minimum cost spanning tree*, *finding transitive closure*, ...) on it.

## Usage

Currently, the user is able to create nodes, create edges, and to move nodes along with adjacent edges.
- To create a node, just click on *Add node* button, and a new node will appear. You can drag & drop nodes everywhere around the *Graph creating area*.
- To create an edge, double click on a node where you want an edge to begin (the selected node will be highlighted in red), and double click on another node where you want edge to end, and a new edge will appear. To cancel edge creation, just double click on a beginning edge. Currently, loops are not supported.
- If you move a node, all adjacent edges will be moved with it.

## Development
GiA is in a very early development stage. You can see the list of the things that have been successfully developed so far, as well as the next feature that is being worked on right now.
- [x] GUI prototype completed
- [ ] Graphic representation of graph implemented
  - [x] Creation of nodes
  - [x] Creation of edges
  - [ ] Deletion of nodes
  - [ ] Deletion of edges
- [ ] Matrix representation
- [ ] Implement button procedures
  - [x] Exit
  - [x] Add node
  - [ ] Add edge
  - [ ] ...
- [ ] ...

## Contact
If you want to contact the developer, send an email to [ajzenhamernikola@gmail.com](mailto:ajzenhamernikola@gmail.com) with the subject starting with "\[GiA\]".
