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

#include <EssexEngineCore/Context.h>
#include <EssexEngineGfxDaemon/GfxDaemon.h>
#include <EssexEngineFileSystemDaemon/FileSystemDaemon.h>

#include <EssexEngineGfxDaemon/Entity.h>

namespace EssexEngine{
namespace Libs{
namespace IsoMap{
    class MapObject
    {
    public:
        MapObject();
        ~MapObject();
        
        virtual void Render(WeakPointer<Context> gameContext) = 0;
        virtual void Update() = 0;
        
        virtual void SetPosition(double _x, double _y);
        double GetX();
        double GetY();
        
        virtual void SetScreenPosition(int _x, int _y);
        int GetScreenX();
        int GetScreenY();
        
        virtual void SetZoom(float _zoom);
        float GetZoom();
    protected:
    private:
        double x;
        double y;
        int screenX;
        int screenY;
        float zoom;
    };
}}};