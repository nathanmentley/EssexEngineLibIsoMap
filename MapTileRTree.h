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

#include <EssexEngineLibIsoMap/MapTile.h>
#include <EssexEngineLibIsoMap/MapDoodad.h>
#include <EssexEngineLibIsoMap/MapCharacter.h>

const int MIN_WORLD_SIZE = 4096;
const int MAX_WORLD_SIZE = 1048576;


namespace EssexEngine{
namespace Libs{
namespace IsoMap{
    typedef RStarTree<int, 2, MIN_WORLD_SIZE, MAX_WORLD_SIZE> MapTileRTree;
    
    struct MapTileRTreeVisitor {
        struct MapTileDataNode {
            int id;
            RStarBoundingBox<2> box;
        };
            
        int count;
        bool ContinueVisiting;
        std::vector<MapTileDataNode> data;
            
        MapTileRTreeVisitor() : count(0), ContinueVisiting(true), data(std::vector<MapTileDataNode>()) {};
            
        void operator()(const MapTileRTree::Leaf * const leaf)
        {
            MapTileDataNode tuple = MapTileDataNode();
            tuple.id = leaf->leaf;
            tuple.box = leaf->bound;
                
            data.push_back(tuple);
            count++;
        }
    };
}}};