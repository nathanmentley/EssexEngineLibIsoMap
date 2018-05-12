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

#include <EssexEngineLibIsoMap/MapObject.h>


EssexEngine::Libs::IsoMap::MapObject::MapObject() {
    x = 0;
    y = 0;
    screenX = 0;
    screenY = 0;
    zoom = 1;
}

EssexEngine::Libs::IsoMap::MapObject::~MapObject()
{
}

double EssexEngine::Libs::IsoMap::MapObject::GetX() {
    return x;
}
double EssexEngine::Libs::IsoMap::MapObject::GetY() {
    return y;
}
void EssexEngine::Libs::IsoMap::MapObject::SetPosition(double _x, double _y) {
    x = _x;
    y = _y;
}

void EssexEngine::Libs::IsoMap::MapObject::SetScreenPosition(int _x, int _y) {
    screenX = _x;
    screenY = _y;
}
int EssexEngine::Libs::IsoMap::MapObject::GetScreenX() {
    return screenX;
}
int EssexEngine::Libs::IsoMap::MapObject::GetScreenY() {
    return screenY;
}

void EssexEngine::Libs::IsoMap::MapObject::SetZoom(float _zoom) {
    zoom = _zoom;
}
float EssexEngine::Libs::IsoMap::MapObject::GetZoom() {
    return zoom;
}
