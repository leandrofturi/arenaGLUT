#ifndef ARENA_H
#define ARENA_H
#include <list>
#include <iostream>
#include <list>
#include "../tinyxml2/tinyxml2.h"
#include "puppet.h"
#include "opponent.h"
#include "block.h"

enum GeomType
{
  RECT,
  CIRCLE
};

typedef struct Color
{
  double R;
  double G;
  double B;
} Color;

#define RED \
  Color { .R = 1.0, .G = 0.0, .B = 0.0 }
#define GREEN \
  Color { .R = 0.0, .G = 1.0, .B = 0.0 }
#define BLUE \
  Color { .R = 0.0, .G = 0.0, .B = 1.0 }
#define BLACK \
  Color { .R = 0.0, .G = 0.0, .B = 0.0 }

class Item
{
  enum AttrType
  {
    WIDTH,
    HEIGHT,
    X,
    Y,
    CX,
    CY,
    R,
    FILL
  };

public:
  GeomType geomType;
  float width = 0.0,
        height = 0.0,
        x = 0.0,
        y = 0.0,
        cx = 0.0,
        cy = 0.0,
        r = 0.0;
  Color fill;

  Item() {}

  void setGeomType(const char *geomType);
  void setAttr(const char *attrName, const char *attrValue);
  void printAttr();
  void draw();

private:
  void setGeomType(GeomType geomTypeAsg);
  void setAttr(AttrType attrType, float attrValue);
  void setAttr(AttrType attrType, const char *attrValue);
};

class Arena
{
  float ArenaHeight = 0.0;
  float ArenaWidth = 0.0;
  float refX = 0.0;
  float refY = 0.0;

  float PuppetX0 = 0.0;
  float PuppetY0 = 0.0;
  float PuppetYRef = 0.0;

private:
  std::list<Item *> items;
  void centerize(std::list<Block *> *blocks, std::list<Opponent *> *opponents, Puppet *puppet, GLfloat ViewingWidth, GLfloat ViewingHeight);

public:
  Arena(){};
  ~Arena()
  {
    for (std::list<Item *>::iterator it = items.begin(); it != items.end();)
    {
      it = items.erase(it);
    }
  };
  GLfloat getHeight()
  {
    return ArenaHeight;
  };
  GLfloat getWidth()
  {
    return ArenaWidth;
  };

  int loadScenario(const char *path);
  void printElements();
  void loadElements(std::list<Block *> *blocks, std::list<Opponent *> *opponents, Puppet *puppet, GLfloat ViewingWidth, GLfloat ViewingHeight);
  void drawScenario();
};

#endif /* ARENA_H */
