# GiA
A GUI-oriented, graph problem-solving C++ software.

## About
*GiA* is a software built in **C++** programming language with **Qt5** library. It allows a user to input a desired graph and run a desired graph algorithm (such as *finding shortest paths*, *constructing a minimum cost spanning tree*, *finding transitive closure*, ...) on it.

## Usage

Currently, the user is able to use several actions.
- To create a node, click on the *Add node* button, and a new node will appear. You can drag & drop nodes everywhere around the *Graph creating area*. If you move a node, all adjacent edges will be moved with it.
- To create an edge, double click on a node where you want an edge to begin (the selected node will be highlighted in red), and double click on another node where you want edge to end. A new edge will appear. To cancel edge creation, just double click on a beginning edge. Currently, loops are not supported.
- To create a weighted edge, first create an edge (which will have weight 1 by default). Then, clicking on edge's weight will give you an option to directly edit it and insert desired weight.
- To create a new graph, click on the *New graph* button, or choose *File* > *New graph* from the menu bar, or press Ctrl+N.
- To save a graph to an .xml file, click on the *Save graph* button, or choose *File* > *Save graph...* from the menu bar, or press Ctrl+S.
- To load a graph from an .xml file, click on the *Load graph* button, or choose *File* > *Load graph...* from the menu bar, or press Ctrl+L.
- To export drawn graph to an image (.png, .jpeg, or .bmp), choose *File* > *Export image...* from the menu bar.

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
  - [x] Export graph to an image
- [x] Graph model implemented
  - [x] Chosen and implemented data structure
  - [x] Implemented saving/loading a graph to/from a file
- [ ] Implemented algorithms
  - [ ] Depth-First Search
  - [ ] Breadth-First Search
  - [ ] ...
- [ ] ...

### Travis CI information

Current build status of the project (note that the branch that is used for building is "Travis-CI" branch, not the "master" one): [![Build Status](https://travis-ci.org/theikeofficial/GiA.svg?branch=Travis-CI)](https://travis-ci.org/theikeofficial/GiA)

Details are available at [https://travis-ci.org/theikeofficial/GiA](https://travis-ci.org/theikeofficial/GiA).

## Contact
If you want to contact the developer, send an email to [ajzenhamernikola@gmail.com](mailto:ajzenhamernikola@gmail.com) with the subject starting with "\[GiA\]".
