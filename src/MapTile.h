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

#include <EssexEngineCore/SharedPointer.h>
#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineGfxDaemon/ISprite.h>

namespace EssexEngine{
namespace Libs{
namespace IsoMap{
    class MapTile
    {
    public:
        static const int TILE_WIDTH = 64;
        static const int TILE_HEIGHT = 32;
        
        MapTile(SharedPointer<Daemons::Gfx::ISprite> _sprite, bool _blocking);
        ~MapTile();
        
        WeakPointer<Daemons::Gfx::ISprite> GetSprite();
        bool IsBlocking();
    protected:
    private:
        SharedPointer<Daemons::Gfx::ISprite> sprite;
        bool blocking;
    };
}}};