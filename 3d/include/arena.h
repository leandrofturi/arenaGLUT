#ifndef ARENA_H
#define ARENA_H
#include <list>
#include <iostream>
#include <list>
#include "tinyxml2.h"
#include "geometries.h"
#include "puppet.h"
#include "block.h"
#include "opponent.h"
#include "gunshot.h"
#include "lava.h"

enum GeomType
{
  RECT,
  CIRCLE
};

#define RED \
  COLOR { .R = 1.0, .G = 0.0, .B = 0.0 }
#define GREEN \
  COLOR { .R = 0.0, .G = 1.0, .B = 0.0 }
#define BLUE \
  COLOR { .R = 0.0, .G = 0.0, .B = 1.0 }
#define BLACK \
  COLOR { .R = 0.0, .G = 0.0, .B = 0.0 }

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
  COLOR fill;

  Item() {}

  void setGeomType(const char *geomType);
  void setAttr(const char *attrName, const char *attrValue);
  void printAttr();

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

  std::list<Item *> items;

public:
  std::list<Block *> blocks;
  std::list<Opponent *> opponents;
  std::list<Gunshot *> gunshots;

  Lava lava;
  int cam = 0;

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
  GLfloat getDepth()
  {
    return ArenaHeight / 2.0;
  };
  GLfloat getRefX()
  {
    return refX;
  };
  GLfloat getRefY()
  {
    return refY;
  };

  void init(const char *path);
  void print();
  void load(Puppet *puppet);
  void draw();
  void move();
  void opponentMove();
  void opponentRotate(Puppet *puppet);
  void opponentShot(Puppet *puppet);
  void handleGravity();
};

#endif /* ARENA_H */
