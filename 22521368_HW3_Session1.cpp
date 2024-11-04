//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Session 01 - Homework 03

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

struct Point {
    vector<double> coordinates;
    Point(int k) : coordinates(k) {}
};

struct KDNode {
    Point point;
    KDNode *left, *right;
    KDNode(Point p) : point(p), left(nullptr), right(nullptr) {}
};

class KDTree {
public:
    KDTree(int k) : k(k), root(nullptr) {}

    void insert(const Point& point) {
        root = insertRec(root, point, 0);
    }

    Point nearestNeighbor(const Point& target) {
        return nearestNeighborRec(root, target, 0, Point(k), numeric_limits<double>::max());
    }

private:
    int k;
    KDNode* root;

    KDNode* insertRec(KDNode* node, const Point& point, int depth) {
        if (node == nullptr) {
            return new KDNode(point);
        }

        int cd = depth % k;
        if (point.coordinates[cd] < node->point.coordinates[cd]) {
            node->left = insertRec(node->left, point, depth + 1);
        } else {
            node->right = insertRec(node->right, point, depth + 1);
        }

        return node;
    }

    Point nearestNeighborRec(KDNode* node, const Point& target, int depth, Point best, double bestDist) {
        if (node == nullptr) {
            return best;
        }

        double dist = distance(node->point, target);
        if (dist < bestDist) {
            bestDist = dist;
            best = node->point;
        }

        int cd = depth % k;
        KDNode* next = (target.coordinates[cd] < node->point.coordinates[cd]) ? node->left : node->right;
        KDNode* other = (next == node->left) ? node->right : node->left;

        best = nearestNeighborRec(next, target, depth + 1, best, bestDist);
        if (abs(target.coordinates[cd] - node->point.coordinates[cd]) < bestDist) {
            best = nearestNeighborRec(other, target, depth + 1, best, bestDist);
        }

        return best;
    }

    double distance(const Point& p1, const Point& p2) {
        double dist = 0;
        for (int i = 0; i < k; ++i) {
            dist += (p1.coordinates[i] - p2.coordinates[i]) * (p1.coordinates[i] - p2.coordinates[i]);
        }
        return sqrt(dist);
    }
};

int main() {
    int k = 2; // Example for 2-dimensional space
    KDTree tree(k);

    vector<Point> points = {Point(k), Point(k), Point(k)};
    points[0].coordinates = {3, 6};
    points[1].coordinates = {17, 15};
    points[2].coordinates = {13, 15};

    for (const auto& point : points) {
        tree.insert(point);
    }

    Point target(k);
    target.coordinates = {10, 10};

    Point nearest = tree.nearestNeighbor(target);
    cout << "Nearest neighbor: (" << nearest.coordinates[0] << ", " << nearest.coordinates[1] << ")" << endl;

    return 0;
}
