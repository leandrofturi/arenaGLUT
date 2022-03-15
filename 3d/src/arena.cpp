#include "../include/arena.h"
#include <iostream>
#include <string.h>
#include <math.h>

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

void Arena::init(const char *path)
{
  XMLDocument doc;
  doc.LoadFile(path);

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
}

void Arena::print()
{
  std::cout << std::endl;
  std::cout << items.size() << " elements" << std::endl;

  for (std::list<Item *>::iterator it = items.begin(); it != items.end(); it++)
  {
    (*it)->printAttr();
  }
}

void Arena::load(Puppet *puppet)
{
  // centering
  for (std::list<Item *>::iterator it = items.begin(); it != items.end(); it++)
  {
    if ((*it)->geomType == RECT)
    {
      if ((fabs((*it)->fill.R - BLUE.R) < 1e-8) && (fabs((*it)->fill.G - BLUE.G) < 1e-8) && (fabs((*it)->fill.B - BLUE.B) < 1e-8))
      {
        ArenaHeight = (*it)->height;
        ArenaWidth = (*it)->width;
        refX = (*it)->x;
        refY = (*it)->y;

        continue;
      }
    }
    else if ((*it)->geomType == CIRCLE)
    {
      if ((fabs((*it)->fill.R - GREEN.R) < 1e-8) && (fabs((*it)->fill.G - GREEN.G) < 1e-8) && (fabs((*it)->fill.B - GREEN.B) < 1e-8))
      {
        PuppetX0 = (*it)->cx - refX;
        PuppetY0 = (*it)->cy + (*it)->r - refY;

        puppet->setX(PuppetX0);
        puppet->setY(PuppetY0);
        puppet->setY0(PuppetY0);

        continue;
      }
    }
  }

  // loading
  for (std::list<Item *>::iterator it = items.begin(); it != items.end(); it++)
  {
    if ((*it)->geomType == RECT)
    {
      if ((fabs((*it)->fill.R - BLUE.R) < 1e-8) && (fabs((*it)->fill.G - BLUE.G) < 1e-8) && (fabs((*it)->fill.B - BLUE.B) < 1e-8))
      {
        continue;
      }
      Block *block = new Block((*it)->x - refX, -(*it)->y + refY + ArenaHeight * 2.0, 0.0, (*it)->width, (*it)->height, ArenaHeight / 2.0);
      blocks.push_back(block);
    }
  }

  for (std::list<Item *>::iterator it = items.begin(); it != items.end(); it++)
  {
    if ((*it)->geomType == CIRCLE)
    {
      if ((fabs((*it)->fill.R - GREEN.R) < 1e-8) && (fabs((*it)->fill.G - GREEN.G) < 1e-8) && (fabs((*it)->fill.B - GREEN.B) < 1e-8))
      {
        continue;
      }

      Opponent *opponent = new Opponent();
      opponent->init();
      opponent->setZ(-(*it)->cx + refX);
      opponent->setY(-(*it)->cy + refY + ArenaHeight * 2.0);
      opponent->setY0(puppet->getY0());

      opponent->setInitial(&blocks, ArenaWidth, ArenaHeight, ArenaHeight / 2.0);

      opponents.push_back(opponent);
    }
  }
}

void Arena::draw()
{
  glPushMatrix();

  // arena at front
  glRotatef(-90.0, 0.0, 1.0, 0.0);
  for (std::list<Block *>::iterator it = blocks.begin(); it != blocks.end(); it++)
  {
    (*it)->draw();
  }

  for (std::list<Gunshot *>::iterator it = gunshots.begin(); it != gunshots.end(); ++it)
  {
    (*it)->draw();
  }
  glPopMatrix();

  for (std::list<Opponent *>::iterator it = opponents.begin(); it != opponents.end(); ++it)
  {
    glPushMatrix();
    (*it)->draw();
    glPopMatrix();
  }
}

void Arena::move()
{
  for (std::list<Gunshot *>::iterator it = gunshots.begin(); it != gunshots.end();)
  {
    (*it)->move();
    if (!(*it)->valid())
    {
      it = gunshots.erase(it);
    }
    else
    {
      ++it;
    }
  }
}

void Arena::opponentMove()
{
  for (std::list<Opponent *>::iterator it = opponents.begin(); it != opponents.end(); ++it)
  {
    (*it)->takeRandMoviment();
  }
}

void Arena::opponentShot(Puppet *puppet)
{
  int i = (int)(rand() % opponents.size());
  std::list<Opponent *>::iterator it = opponents.begin();
  std::advance(it, i);

  gunshots.push_back((*it)->shoot());
}

void Arena::handleGravity()
{
  for (std::list<Opponent *>::iterator it = opponents.begin(); it != opponents.end(); ++it)
  {
    (*it)->handleGravity();
  }
}