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

#include <EssexEngineLibIsoMap/MapDoodadDef.h>

EssexEngine::Libs::IsoMap::MapDoodadDef::MapDoodadDef(std::string _filename, int _x, int _y, int _w, int _h) {
    filename = _filename;
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}

EssexEngine::Libs::IsoMap::MapDoodadDef::~MapDoodadDef() {
}

std::string EssexEngine::Libs::IsoMap::MapDoodadDef::GetFilename() {
    return filename;
}

int EssexEngine::Libs::IsoMap::MapDoodadDef::GetX() {
    return x;
}

int EssexEngine::Libs::IsoMap::MapDoodadDef::GetY() {
    return y;
}

int EssexEngine::Libs::IsoMap::MapDoodadDef::GetW() {
    return w;
}

int EssexEngine::Libs::IsoMap::MapDoodadDef::GetH() {
    return h;
}
