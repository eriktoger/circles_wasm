#include "circleFunctions.h"

bool collideWithWall(int index, int newX, int newY, int width, int height) {

  int r = circles[index].getR();

  // there is a edge case when the circle touches both walls, and my if
  // statments are in the wrong order
  if ((newY + r) >= height) { // top
    circles[index].setY(height - r);
    circles[index].setX(newX);
    animationData[index].direction = getRandomDirection(PI, 2 * PI);
    return true;
  } else if ((newY - r) <= 0) { // bottom
    circles[index].setY(r);
    circles[index].setX(newX);
    animationData[index].direction = getRandomDirection(0, PI);
    return true;
  } else if ((newX + r) >= width) { //  right
    circles[index].setX(width - r);
    circles[index].setY(newY);
    animationData[index].direction = getRandomDirection(PI / 2, 3 * PI / 2);
    return true;
  } else if ((newX - r) <= 0) { // left
    circles[index].setX(r);
    circles[index].setY(newY);
    animationData[index].direction = getRandomDirection(0, PI) - PI / 2;
    return true;
  }
  return false;
}

bool collideWithCircle(int index, int newX, int newY, int width, int height) {

  double x = newX;
  double y = newY;
  double r = (double)circles[index].getR();
  // checking 8 points on the circles perimiter
  // (x,y + r)
  double length = r * SINP4;
  std::vector<Point> bounderies = {{x + r, y},      {x + length, y - length},
                                   {x, y - r},      {x - length, y - length},
                                   {x - length, y}, {x - length, y + length},
                                   {x, y + r},      {x + length, y + length}};

  for (int j = index + 1; j < displayNr; j++) {
    int x2 = circles[j].getX();
    int y2 = circles[j].getY();
    int r2 = circles[j].getR();
    for (auto &point : bounderies) {
      double distance = r2 * r2 - (point.x - x2) * (point.x - x2) -
                        (point.y - y2) * (point.y - y2);

      if (distance >= 0) {

        auto dir1 = animationData[index].direction;
        auto dir2 = animationData[j].direction;

        auto reverseDir1 = dir1 + PI;
        if (reverseDir1 > 2 * PI) {
          reverseDir1 -= 2 * PI;
        }

        auto reverseDir2 = dir2 + PI;
        if (reverseDir2 > 2 * PI) {
          reverseDir2 -= 2 * PI;
        }

        // head on collision
        if (abs(reverseDir1 - dir2) < PI) {

          animationData[index].direction = reverseDir1;
          animationData[j].direction = reverseDir2;

        } else {
          // catch up with same direction
          // the faster one should reverse.
          if (animationData[index].velocity >= animationData[j].velocity) {
            animationData[index].direction = reverseDir1;
          } else {
            animationData[j].direction = reverseDir2;
          }
        }

        return true;

        // I may add side collision later on
      }
    }
  }

  return false;
}

void updateCircles(int width, int height) {
  for (int index = 0; index < displayNr; index++) {
    double x = (double)circles[index].getX();
    double y = (double)circles[index].getY();
    double r = (double)circles[index].getR();

    double cosVal = cos(animationData[index].direction);
    int newX = x + cosVal * animationData[index].velocity;
    double sinVal = sin(animationData[index].direction);
    int newY = y + sinVal * animationData[index].velocity;

    // will it collide with a wall?
    auto hitWall = collideWithWall(index, newX, newY, width, height);
    auto hitCircle = collideWithCircle(index, newX, newY, width, height);

    if (!hitWall && !hitCircle) {
      circles[index].setX(newX);
      circles[index].setY(newY);
    };
  }
}
