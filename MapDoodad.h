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

#include <vector>

#include <EssexEngineCore/SharedPointer.h>
#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineLibIsoMap/MapObject.h>

namespace EssexEngine{
namespace Libs{
namespace IsoMap{
    class MapDoodad: public MapObject
    {
    public:
        MapDoodad(WeakPointer<Context> gameContext, std::string texture, int x, int y, int w, int h);
        ~MapDoodad();
        void Render(WeakPointer<Context> gameContext);
        void Update();
    protected:
    private:
        std::vector<SharedPointer<Daemons::Gfx::Entity>> entities;
        int currentAnimationFrame;
    };
}}};