/* 
 * Essex Engine
 * 
 * Copyright (C) 2018 Nathan Mentley - All Rights Reserved
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

#include <EssexEngineLibIsoMap/MapCharacter.h>

const int MIN_WORLD_UNIT_SIZE = 64;
const int MAX_WORLD_UNIT_SIZE = 65536;

namespace EssexEngine{
namespace Libs{
namespace IsoMap{
    typedef RStarTree<WeakPointer<MapCharacter>, 2, MIN_WORLD_UNIT_SIZE, MAX_WORLD_UNIT_SIZE> CharacterRTree;
    
    struct CharacterRTreeVisitor {
        struct MapCharacterDataNode {
            WeakPointer<MapCharacter> character;
            RStarBoundingBox<2> box;
        };
        
        int count;
        bool ContinueVisiting;
        std::vector<MapCharacterDataNode> data;
        
        CharacterRTreeVisitor() : count(0), ContinueVisiting(true), data(std::vector<MapCharacterDataNode>()) {};
        
        void operator()(const CharacterRTree::Leaf * const leaf)
        {
            MapCharacterDataNode tuple = MapCharacterDataNode();
            tuple.character = leaf->leaf;
            tuple.box = leaf->bound;
            
            data.push_back(tuple);
            count++;
        }
    };
}}};
