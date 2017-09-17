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

#include <EssexEngineLibIsoMap/MapObject.h>

namespace EssexEngine{
namespace Libs{
namespace IsoMap{
    enum MapCharacterActionTypes {
        MoveWest = 0,
        MoveNorthWest = 1,
        MoveNorth = 2,
        MoveNorthEast = 3,
        MoveEast = 4,
        MoveSouthEast = 5,
        MoveSouth = 6,
        MoveSouthWest = 7,
        MoveTo = 8,
        Attack = 9
    };
    
    class MapCharacterAction
    {
    public:
        MapCharacterAction(MapCharacterActionTypes _type, WeakPointer<MapObject> _target);
        ~MapCharacterAction();
        
        bool GetIsRunning();
        bool GetIsCancelled();
        void Start();
        MapCharacterActionTypes GetType();
        WeakPointer<MapObject> GetTarget();
        void Cancel();
    protected:
    private:
        bool isRunning;
        bool isCancelled;
        MapCharacterActionTypes type;
        WeakPointer<MapObject> target;
    };
}}};