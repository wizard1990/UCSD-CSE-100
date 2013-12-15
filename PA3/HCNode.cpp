//
//  HCNode.cpp
//  PA3
//
//  Created by zhang yan on 11/2/13.
//  Copyright (c) 2013 zhang yan. All rights reserved.
//

//Yan Zhang A53050564
//Xiaoxiao Zheng A53044872

#include "HCNode.hpp"

bool HCNode::operator<(const HCNode& other)
{
    //if counts are equal, compare the symbol ASCII code
    //to make sure the HCTree is fixed inspite of the access order
    if (count == other.count) {
        return symbol < other.symbol;
    }
    return count < other.count;
}