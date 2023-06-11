# Robot-Hamiltonian-Circuit
A delivery robot that must visit a number of locations in a warehouse. The robot
starts at a designated "home" location and must visit every other location exactly once before returning to the
home location. Additionally, the robot has a limited battery life and must return home before its battery runs
out. 

More formally, you are given an undirected graph G = (V, E) representing the warehouse layout, where each
vertex v ∈ V represents a location and each edge (u, v) ∈ E represents a direct path between locations u and v
that the robot can traverse. The home location is a designated vertex h ∈ V, and each vertex v ∈ V (other than
h) has a delivery time t(v) representing the amount of time it takes the robot to deliver a package at location v. 

The goal is to find a Hamiltonian circuit in G that starts and ends at h and visits every other vertex exactly
once, subject to the constraint that the total time taken by the robot (including delivery times and travel times)
does not exceed a given time limit T. 

* Test case 1:

      V = {h, A, B, C}

      E = {(h, A), (h, B), (h, C), (A, B), (A, C), (B, C)}

      Weights = {2,2,3,4,5,8}

      t(A) = 5, t(B) = 10, t(C) = 8

      T = 38

      Expected output: (h, B, A, C, h) 

* Test case 2:

      V={h, A, B, C}

      E = {(h, A), (h, B), (h, C), (A, B), (A, C), (B, C)}

      Weights = {1,2,3,4,5,6}

      t(A) = 5, t(B) = 10, t(C) = 8

      T = 20

Expected output: NO FEASIBLE CIRCUIT

