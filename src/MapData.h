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
#include <string>
#include <memory>
#include <algorithm>
#include <utility>

#include <EssexEngineCore/RStarTree.h>
#include <EssexEngineCore/Context.h>
#include <EssexEngineCore/UniquePointer.h>
#include <EssexEngineCore/WeakPointer.h>

#include <EssexEngineLibIsoMap/Daemons.h>

#include <EssexEngineLibIsoMap/MapCharacterDef.h>
#include <EssexEngineLibIsoMap/MapDoodadDef.h>
#include <EssexEngineLibIsoMap/MapTileRTree.h>
#include <EssexEngineLibIsoMap/DoodadRTree.h>
#include <EssexEngineLibIsoMap/CharacterRTree.h>
#include <EssexEngineLibIsoMap/MapNPCCharacter.h>
#include <EssexEngineLibIsoMap/MapPlayerCharacter.h>

namespace EssexEngine{
namespace Libs{
namespace IsoMap{
    class MapData
    {
    public:
        MapData(WeakPointer<Context> _gameContext, WeakPointer<Daemons::Json::IJsonDocument> _gameDocument, WeakPointer<Daemons::Json::IJsonDocument> _mapDocument);
        ~MapData();
        
        WeakPointer<MapTile> GetTile(int id);
        
        MapTileRTreeVisitor GetTiles(MapTileRTree::BoundingBox bounds);
        
        DoodadRTreeVisitor GetDoodads();
        DoodadRTreeVisitor GetDoodads(DoodadRTree::BoundingBox bounds);
        
        CharacterRTreeVisitor GetCharacters();
        CharacterRTreeVisitor GetCharacters(CharacterRTree::BoundingBox bounds);
        
        std::vector<std::string>* GetScripts(std::string scriptCode);
        
        void AddCharacter(WeakPointer<MapCharacter> characeter, CharacterRTree::BoundingBox box);
        bool MoveCharacter(WeakPointer<MapCharacter> characeter, CharacterDirections direction);
        bool DetectCollision(WeakPointer<MapCharacter> character, CharacterDirections direction, double &newX, double &newY);
        
        WeakPointer<MapPlayerCharacter> GetCharacter();
        
        int GetMapWidth();
        int GetMapHeight();
    protected:
        void LoadTiles();
        void LoadDoodadDefs();
        void LoadCharacterDefs();
        void LoadMapTiles();
        void LoadDoodads();
        void LoadNPCs();
        void LoadPlayer();
        void LoadScripts();
    private:
        WeakPointer<Context> gameContext;
        WeakPointer<Daemons::Json::IJsonDocument> gameDocument;
        WeakPointer<Daemons::Json::IJsonDocument> mapDocument;
        
        std::map<int, UniquePointer<MapTile>> tiles;
        std::map<int, UniquePointer<MapDoodadDef>> doodadDefs;
        std::map<int, UniquePointer<MapCharacterDef>> characterDefs;
        
        MapTileRTree map;
        DoodadRTree doodads;
        CharacterRTree characters;
        
        UniquePointer<MapPlayerCharacter> player;
        
        std::map<std::string, std::vector<std::string>> scripts;
    };
}}};
