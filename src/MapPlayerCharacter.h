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

#include <EssexEngineLibIsoMap/MapCharacter.h>

namespace EssexEngine{
namespace Libs{
namespace IsoMap{
    class MapPlayerCharacter: public MapCharacter
    {
    public:
        MapPlayerCharacter(WeakPointer<Context> gameContext, WeakPointer<Daemons::Window::IRenderContext> _target, std::string bodyTexture, std::string headTexture, std::string weaponTexture);
        virtual ~MapPlayerCharacter();
    protected:
    private:
    };
}}};
