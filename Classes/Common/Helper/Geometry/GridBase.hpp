//
//  GridBase.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/29/16.
//
//

#ifndef GridBase_hpp
#define GridBase_hpp

#include "stdafx.h"

namespace Geometry {
    
    class GridBase: public internal::AIRef {
    public:
        struct Rect {
            int width = 0;
            int height = 0;
        };
        struct Size {
            int width = 0;
            int height = 0;
        };
        
        struct Padding {
            int x = 0;
            int y = 0;
        };
        
        struct Point {
            int x = 0;
            int y = 0;
        };
        
        struct IndexPath {
            int x = 0;
            int y = 0;
        };
        
    private:
        Size    _sizeCell;
        Padding _padding;
        Rect    _grid;
    public:
        GridBase();
        ~GridBase();
        
        Point pointByIndexPath(int x, int y);
        IndexPath indexPathByPoint(float x, float y);
        IndexPath indexPathByPoint(int x, int y);
        Size sizeGrid();
        
        bool containsIndexPath(IndexPath indexPath);
        bool containsPoint(Point point);
        
        bool containsIndexPath(int x, int y);
        bool containsPoint(int x, int y);
        
        void setSizeCell(int width, int height);
        void setPadding (int x, int y);
        void setGrid    (int width, int height);
    public:
        static GridBase* createWithSizeCell(int width, int height);
    };
}

#endif /* GridBase_hpp */
