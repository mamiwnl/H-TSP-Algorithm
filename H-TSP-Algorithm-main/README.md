# H-TSP-Algorithm
The travelling salesman problem (TSP) asks the following question: Given a list of cities and the
distances between each pair of cities, what is the shortest possible route that visits each city exactly
once and returns to the origin city? In this assignment, we will focus on a modified version of TSP,
Half TSP, where the salesman should visit exactly half of the cities and return back to the origin city.
You may start from any city.
Inputs are: n cities, with their locations (x and y coordinates) in a 2D grid.
Output is: Ordering (tour) of half of these cities ((⌈n⁄2⌉ cities), such that total distance to travel is
minimized.
Distance between two cities is defined as the Euclidian distance rounded to the nearest integer. In
other words, you will compute distance between two cities c1 = (x1, y1) and c2 = (x2, y2) as
follows:

d(c1, c2) = round (√(x1 − x2)^2 + (y1 − y2)^2)

For example, if three cities are given with the coordinates c1 = (0,2), c2 = (2,3) and c3 = (3,0),
then a tour with ordering c1, c2, c3, c1 has a total distance of :
rnd(√5) + rnd(√10) + rnd(√13) = rnd(2,23) + rnd(3,16) + rnd(3,60) = 2 + 3 + 4 = 9

## **This project had a competition system in which the more optimum result received extra points.**


## **We earned extra points as the 3rd best performing project**



