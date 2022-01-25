#include "../include/arena.h"
#include <iostream>
#include <string.h>
#include <math.h>
#include "../include/geometries.h"

using namespace tinyxml2;

void Item::setGeomType(const char *geomType)
{
  if (strcmp("rect", geomType) == 0)
  {
    setGeomType(RECT);
  }
  else if (strcmp("circle", geomType) == 0)
  {
    setGeomType(CIRCLE);
  }
}

void Item::setGeomType(GeomType geomTypeAsg)
{
  geomType = geomTypeAsg;
}

void Item::setAttr(const char *attrName, const char *attrValue)
{
  if (strcmp("width", attrName) == 0)
  {
    setAttr(WIDTH, std::atof(attrValue));
  }
  else if (strcmp("height", attrName) == 0)
  {
    setAttr(HEIGHT, std::atof(attrValue));
  }
  else if (strcmp("x", attrName) == 0)
  {
    setAttr(X, std::atof(attrValue));
  }
  else if (strcmp("y", attrName) == 0)
  {
    setAttr(Y, std::atof(attrValue));
  }
  else if (strcmp("cx", attrName) == 0)
  {
    setAttr(CX, std::atof(attrValue));
  }
  else if (strcmp("cy", attrName) == 0)
  {
    setAttr(CY, std::atof(attrValue));
  }
  else if (strcmp("r", attrName) == 0)
  {
    setAttr(R, std::atof(attrValue));
  }
  if (strcmp("fill", attrName) == 0)
  {
    setAttr(FILL, attrValue);
  }
}

void Item::setAttr(AttrType attrType, float attrValue)
{
  switch (attrType)
  {
  case WIDTH:
    width = attrValue;
    break;
  case HEIGHT:
    height = attrValue;
    break;
  case X:
    x = attrValue;
    break;
  case Y:
    y = attrValue;
    break;
  case CX:
    cx = attrValue;
    break;
  case CY:
    cy = attrValue;
    break;
  case R:
    r = attrValue;
    break;

  default:
    std::cout << attrType << " unknown" << std::endl;
    break;
  }
}

void Item::setAttr(AttrType attrType, const char *attrValue)
{
  switch (attrType)
  {
  case FILL:
    if (strcmp(attrValue, "red") == 0)
    {
      fill = RED;
    }
    else if (strcmp(attrValue, "blue") == 0)
    {
      fill = BLUE;
    }
    else if (strcmp(attrValue, "green") == 0)
    {
      fill = GREEN;
    }
    else if (strcmp(attrValue, "black") == 0)
    {
      fill = BLACK;
    }
    else
    {
      std::cout << attrValue << " unknown" << std::endl;
    }
    break;

  default:
    std::cout << attrType << " unknown" << std::endl;
    break;
  }
}

void Item::printAttr()
{
  if (geomType == RECT)
  {
    std::cout << "width:" << width << " height:" << height << " x:" << x << " y:" << y << " fill:" << fill.R << fill.G << fill.B << std::endl;
  }
  else if (geomType == CIRCLE)
  {
    std::cout << "cx:" << cx << " cy:" << cy << " r:" << r << " fill:" << fill.R << fill.G << fill.B << std::endl;
  }
}

void Item::draw()
{
  glPushMatrix();
  if (geomType == RECT)
  {
    glTranslatef(x, y, 0.0);
    Geometries::drawRect(height, width, fill.R, fill.G, fill.B);
  }
  else if (geomType == CIRCLE)
  {
    glTranslatef(cx, cy, 0.0);
    Geometries::drawCircle(r, fill.R, fill.G, fill.B);
  }
  glPopMatrix();
}

int Arena::loadScenario(const char *path)
{
  XMLDocument doc;
  doc.LoadFile("input/arena_teste.svg");

  XMLElement *root = doc.FirstChildElement("svg");
  for (XMLElement *node = root->FirstChildElement(); node != NULL; node = node->NextSiblingElement())
  {
    Item *item = new Item();
    item->setGeomType(node->Value());
    for (const tinyxml2::XMLAttribute *attr = node->FirstAttribute(); attr != 0; attr = attr->Next())
    {
      item->setAttr(attr->Name(), attr->Value());
    }
    items.push_back(item);
  }

  return 0;
}

void Arena::printElements()
{
  std::cout << std::endl;
  std::cout << items.size() << " elements" << std::endl;

  for (std::list<Item *>::iterator it = items.begin(); it != items.end(); it++)
  {
    (*it)->printAttr();
  }
}

void Arena::loadElements(std::list<Block *> *blocks, std::list<Opponent *> *opponents, Puppet *puppet)
{
  for (std::list<Item *>::iterator it = items.begin(); it != items.end(); it++)
  {
    if ((*it)->geomType == RECT)
    {
      if ((fabs((*it)->fill.R - BLUE.R) < 1e-8) && (fabs((*it)->fill.G - BLUE.G) < 1e-8) && (fabs((*it)->fill.B - BLUE.B) < 1e-8))
      {
        ArenaHeight = (*it)->height;
        PuppetYRef = (*it)->height;
        ArenaWidth = (*it)->width;
        refX = (*it)->x;
        refY = (*it)->y;
        continue;
      }
      Block *block = new Block((*it)->x, (*it)->y, (*it)->width, (*it)->height, (*it)->fill.R, (*it)->fill.G, (*it)->fill.B);
      blocks->push_back(block);
    }
    else if ((*it)->geomType == CIRCLE)
    {
      if ((fabs((*it)->fill.R - GREEN.R) < 1e-8) && (fabs((*it)->fill.G - GREEN.G) < 1e-8) && (fabs((*it)->fill.B - GREEN.B) < 1e-8))
      {
        PuppetX0 = (*it)->cx;
        PuppetY0 = (*it)->cy + (*it)->r;
        continue;
      }
      Opponent *opponent = new Opponent((*it)->cx, (*it)->cy, (*it)->r, (*it)->fill.R, (*it)->fill.G, (*it)->fill.B);
      opponents->push_back(opponent);
    }
  }

  centerize(blocks, opponents, puppet);
}

void Arena::centerize(std::list<Block *> *blocks, std::list<Opponent *> *opponents, Puppet *puppet)
{
  for (std::list<Block *>::iterator it = blocks->begin(); it != blocks->end(); ++it)
  {
    (*it)->move(-refX, -refY);
  }

  for (std::list<Opponent *>::iterator it = opponents->begin(); it != opponents->end(); ++it)
  {
    (*it)->setInitial(blocks, -refX, -refY);
  }

  puppet->setInitial(PuppetX0 - refX, PuppetYRef);
  puppet->setY(PuppetY0 - refY);
}

void Arena::drawScenario()
{
  glPushMatrix();

  // mirroring
  glTranslatef(0.0, ArenaHeight * 2.0, 0.0);
  glRotatef(180.0, 1.0, 0.0, 0.0);

  glTranslatef(-refX, -refY, 0.0);

  for (std::list<Item *>::iterator it = items.begin(); it != items.end(); it++)
  {
    (*it)->draw();
  }
  glPopMatrix();
}