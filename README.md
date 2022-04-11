# CompGeometryCpp
To prepare for the final project of the first year at University I started reading book on Computational Geometry and here I upload my implementations of the algorithms from there

<h2> Convex Hull </h2>

Convex Hull - updated algorithm, with O(n*logn) complexity: 

   1. Sort all the points by x-axis and if there are points with same x-coordinate, sort them by y-axis
   2. Go through sorted set of points and create the upper line of a convex hull 
   3. Gp through the set in reverse order and create the lower line
   4. Append lines

Here you can see a comparison between O(n^3) and O(n*logn) algorithms

https://user-images.githubusercontent.com/68334150/162422923-8ad9fc1d-7b9c-4255-8007-3ec6ae4d11a5.mp4

https://user-images.githubusercontent.com/68334150/162422972-0c57c35e-b3bc-4bae-a867-b465767f21a8.mp4


<h2>Lines Intersections</h2>

Coded bruteforce algorithm O(n^2) using inverse matrices

https://user-images.githubusercontent.com/68334150/162722344-25480fb6-cde1-4866-90af-1417170d4061.mp4

