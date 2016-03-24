//
//  GridBase.cpp
//  bvunity
//
//  Created by denis zaytcev on 2/29/16.
//
//

#include "GridBase.hpp"

using namespace Geometry;

GridBase::GridBase() {
    _sizeCell   = Size();
    _padding    = Padding();
    _grid       = Rect();
}

GridBase::~GridBase() {}

GridBase* GridBase::createWithSizeCell(int width, int height) {
    auto ref = new GridBase();
    ref->setSizeCell(width, height);
    return ref;
}

GridBase::Point GridBase::pointByIndexPath(int x, int y) {
    GridBase::Point p;
    
    p.x = x * (_sizeCell.width  + _padding.x);
    p.y = y * (_sizeCell.height + _padding.y);
    
    return p;
}

GridBase::IndexPath GridBase::indexPathByPoint(float x, float y) {
    return indexPathByPoint((int)x, (int)y);
}

GridBase::IndexPath GridBase::indexPathByPoint(int x, int y) {
    GridBase::IndexPath index;
    
    index.x = ~~(x / (_sizeCell.width  + _padding.x));
    index.y = ~~(y / (_sizeCell.height + _padding.y));
    
    return index;
}

GridBase::Size GridBase::sizeGrid() {
    GridBase::Size s;
    
    s.width  = _grid.width * _sizeCell.width  + _padding.x * (_grid.width  - 1);
    s.height = _grid.height* _sizeCell.height + _padding.y * (_grid.height - 1);
    
    return s;
}

bool GridBase::containsIndexPath(GridBase::IndexPath indexPath) {
    return containsIndexPath(indexPath.x, indexPath.y);
}

bool GridBase::containsPoint(GridBase::Point point) {
    return containsPoint(point.x, point.y);
}

bool GridBase::containsIndexPath(int x, int y) {
    return x > 0 && y > 0 && _grid.width >= x && _grid.height >= y;
}

bool GridBase::containsPoint(int x, int y) {
    auto size = sizeGrid();
    return x >= 0 && x <= size.width && y >= 0 && y <= size.height;
}

void GridBase::setSizeCell(int width, int height) {
    _sizeCell.width = width;
    _sizeCell.height = height;
}

void GridBase::setGrid(int width, int height) {
    _grid.width = width;
    _grid.height = height;
}

void GridBase::setPadding(int x, int y) {
    _padding.x = x;
    _padding.y = y;
}