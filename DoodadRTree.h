/* 
 * Essex Engine
 * 
 * Copyright (C) 2017 Nathan Mentley - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 *
 * You should have received a copy of the BSD license with
 * this file. If not, please visit: https://github.com/nathanmentley/EssexEngine
 */
#pragma once

#include <math.h>
#include <vector>

#include <EssexEngineCore/RStarTree.h>
#include <EssexEngineCore/WeakPointer.h>

#include <EssexEngineLibIsoMap/MapDoodad.h>

const int MIN_WORLD_DOODAD_SIZE = 64;
const int MAX_WORLD_DOODAD_SIZE = 65536;

namespace EssexEngine{
namespace Libs{
namespace IsoMap{
    typedef RStarTree<MapDoodad*, 2, MIN_WORLD_DOODAD_SIZE, MAX_WORLD_DOODAD_SIZE> DoodadRTree;
    
    struct DoodadRTreeVisitor {
        struct DoodadDataNode {
            WeakPointer<MapDoodad> doodad;
            RStarBoundingBox<2> box;
        };
        
        int count;
        bool ContinueVisiting;
        std::vector<DoodadDataNode> data;
        
        DoodadRTreeVisitor() : count(0), ContinueVisiting(true), data(std::vector<DoodadDataNode>()) {};
        
        void operator()(const DoodadRTree::Leaf * const leaf)
        {
            DoodadDataNode tuple = DoodadDataNode();
            tuple.doodad = leaf->leaf;
            tuple.box = leaf->bound;
            
            data.push_back(tuple);
            count++;
        }
    };
}}};