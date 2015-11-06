//
//  Group.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/31/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef Group_hpp
#define Group_hpp

#include <stdio.h>
#include <list>
#include "Node.hpp"
#include "Material.h"
class Group : public Node{
protected:
    std::list<Node *> children;
    
    
public:
    virtual void draw(Matrix4 m);
    virtual void addChild(Node *(*spawn)());
    virtual void removeChild();
    virtual void removeChild(Node *);
    
    virtual void addChild(Node * a);
    virtual void update();
    
    
    
};
#endif /* Group_hpp */
