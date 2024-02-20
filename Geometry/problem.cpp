/*
- Program to find perimeter of convex Hull given points on input
*/

#include <iostream>
#include "geometry.hpp"

vector<Point<double>> convexHull(vector<Point<double>> inputPoints) {
    int n = inputPoints.size();
    
    if (n < 3) return {};

    vector<Point<double>> lowerHull;
    vector<Point<double>> upperHull;

    // Sort the points lexicographically
    sort(inputPoints.begin(), inputPoints.end());

    // Build lower hull
    for (int i = 0; i < n; i++) {
        while (lowerHull.size() >= 2 &&
               lowerHull[lowerHull.size() - 2].orientation(lowerHull[lowerHull.size() - 1], inputPoints[i]) != -1) {
            lowerHull.pop_back();
        }
        lowerHull.push_back(inputPoints[i]);
    }

    // Build upper hull
    for (int i = n - 1; i >= 0; i--) {
        while (upperHull.size() >= 2 &&
               upperHull[upperHull.size() - 2].orientation(upperHull[upperHull.size() - 1], inputPoints[i]) != -1) {
            upperHull.pop_back();
        }
        upperHull.push_back(inputPoints[i]);
    }

    // Remove the last point to avoid duplication
    lowerHull.pop_back();  
    // Concatenate the upper and lower hulls
    lowerHull.insert(lowerHull.end(), upperHull.begin(), upperHull.end());

    return lowerHull;
}

double calculatePerimeter(const vector<Point<double>>& hull) {
    double perimeter = 0.0;
    int n = hull.size();

    for (int i = 0; i < n - 1; i++) {
        perimeter += hull[i].dist(hull[i + 1]);
    }

    // Add the last edge (from the last point to the first point)
    perimeter += hull[n - 1].dist(hull[0]);

    return perimeter;
}


int main(){
    int n;

    vector<Point<double>> inputPoints;

    std::cin >> n;

    for(int i = 0; i < n; i++){
        double x, y;
        std::cin >> x >> y;
        Point<double> aux(x,y);
        inputPoints.push_back(aux);
    }

    double answer = calculatePerimeter(convexHull(inputPoints));
   
    std::cout << fixed << setprecision(6) << answer;

    return 0;
}