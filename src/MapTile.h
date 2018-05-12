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

#include <utility>

#include <EssexEngineCore/UniquePointer.h>
#include <EssexEngineGfxDaemon/Entity.h>

namespace EssexEngine{
namespace Libs{
namespace IsoMap{
    class MapTile
    {
    public:
        static const int TILE_WIDTH = 64;
        static const int TILE_HEIGHT = 32;
        
        MapTile(UniquePointer<Daemons::Gfx::Entity> _entity, bool _blocking);
        ~MapTile();
        
        WeakPointer<Daemons::Gfx::Entity> GetEntity();
        bool IsBlocking();
    protected:
    private:
        UniquePointer<Daemons::Gfx::Entity> entity;
        bool blocking;
    };
}}};
