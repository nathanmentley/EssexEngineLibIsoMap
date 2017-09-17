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
#include <EssexEngineCore/UniquePointer.h>

#include <EssexEngineJsonDaemon/IJsonDocument.h>

#include <EssexEngineLibIsoMap/Daemons.h>

#include <EssexEngineLibIsoMap/MapData.h>
#include <EssexEngineLibIsoMap/MapPlayerCharacter.h>
#include <EssexEngineLibIsoMap/MapNPCCharacter.h>

namespace EssexEngine{
namespace Libs{
namespace IsoMap{
    class Map
    {
    public:
        Map(WeakPointer<Context> _gameContext, WeakPointer<Daemons::Json::IJsonDocument> _gameDocument, WeakPointer<Daemons::Json::IJsonDocument> _mapDocument);
        ~Map();
        
        WeakPointer<MapPlayerCharacter> GetCharacter();
        
        void Render();
        void ZoomIn();
        void ZoomOut();
        
        void Update();
        
        void SetScreenX(double x);
        void SetScreenY(double y);
        double GetScreenX();
        double GetScreenY();
        
        double GetX(int screenX, int screenY);
        double GetY(int screenX, int screenY);
        
        int GetScreenX(double x, double y);
        int GetScreenY(double x, double y);
    protected:
        void InitMap();
        
        void ProcessAction(WeakPointer<MapCharacter> character, WeakPointer<MapCharacterAction> action);
        bool CheckActionCompleteStatus(WeakPointer<MapCharacter> character, WeakPointer<MapCharacterAction> action);
        void ProcessPath(WeakPointer<MapCharacter> character, int x, int y);
        
        double GetDistence(WeakPointer<MapObject> obj1, WeakPointer<MapObject> obj2);
        
        void RunMapScripts(std::string scriptCode);
    private:
        WeakPointer<Context> gameContext;
        
        UniquePointer<MapData> mapData;
        
        float zoom;
        double currentScreenX;
        double currentScreenY;
    };
}}};