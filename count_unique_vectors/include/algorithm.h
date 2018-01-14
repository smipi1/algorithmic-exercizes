#ifndef TEMPLATE_ALGORITHM_H_
#define TEMPLATE_ALGORITHM_H_

#include <vector>

struct Point {
public:
    Point(int const x, int const y): x(x), y(y) {}
    int x, y;
};

int count_unique_vectors(std::vector<Point> const& positions);

#endif /* TEMPLATE_ALGORITHM_H_ */
