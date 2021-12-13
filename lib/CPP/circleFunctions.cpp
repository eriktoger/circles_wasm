#include "circleFunctions.h"

bool collideWithWall(int index, int newX, int newY, int width, int height) {

  int r = circles[index].getR();

  // there is a edge case when the circle touches both walls, and my if
  // statments are in the wrong order
  if ((newY + r) >= height) { // top
    animationData[index].direction = getRandomDirection(PI, 2 * PI);
    return true;
  } else if ((newY - r) <= 0) { // bottom
    animationData[index].direction = getRandomDirection(0, PI);
    return true;
  } else if ((newX + r) >= width) { //  right
    animationData[index].direction = getRandomDirection(PI / 2, 3 * PI / 2);
    return true;
  } else if ((newX - r) <= 0) { // left
    animationData[index].direction = getRandomDirection(0, PI) - PI / 2;
    return true;
  }
  return false;
}

bool collideWithCircle(int index, int newX, int newY, int width, int height) {

  double r = (double)circles[index].getR();
  bool collisionMade = false;
  for (int j = index + 1; j < displayNr; j++) {
    int x2 = circles[j].getX();
    int y2 = circles[j].getY();
    int r2 = circles[j].getR();

    double cosVal = cos(animationData[j].direction);
    int newX2 = x2 + cosVal * animationData[j].velocity;
    double sinVal = sin(animationData[j].direction);
    int newY2 = y2 + sinVal * animationData[j].velocity;

    double distance =
        sqrt((newX - newX2) * (newX - newX2) + (newY - newY2) * (newY - newY2));

    if (distance <= r + r2) {

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

      collisionMade = true;

      // I may add side collision later on
    }
  }

  return collisionMade;
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
    }
  }
}
