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

#include <map>
#include <vector>
#include <queue>
#include <string>

#include <EssexEngineLibIsoMap/MapObject.h>
#include <EssexEngineLibIsoMap/MapCharacterAction.h>

namespace EssexEngine{
namespace Libs{
namespace IsoMap{
    enum CharacterAnimations {
        Stance = 0,
        Running = 1,
        MeleeSwing = 2,
        Block = 3,
        HitAndDie = 4,
        CastSpell = 5,
        ShootBow = 6
    };
    enum CharacterDirections {
        West = 0,
        NorthWest = 1,
        North = 2,
        NorthEast = 3,
        East = 4,
        SouthEast = 5,
        South = 6,
        SouthWest = 7
    };
    
    class MapCharacter: public MapObject
    {
    public:
        static const int CHARACTER_WIDTH = 128;
        static const int CHARACTER_HEIGHT = 128;
        
        MapCharacter(WeakPointer<Context> gameContext, std::string bodyTexture, std::string headTexture, std::string weaponTexture);
        ~MapCharacter();
        
        void SetScreenPosition(int _x, int _y) override;
        
        void Render(WeakPointer<Context> gameContext) override;
        virtual void Update() override;
        
        void SetAnimation(CharacterAnimations animation);
        void SetDirection(CharacterDirections direction);
        
        double GetSpeed();
        double GetSightRange();
        double GetAttackRange();
        int GetTeam();
        int GetLife();
        int GetHealth();
        int GetDamage();
        
        void SetSpeed(double _speed);
        void SetSightRange(double _sightRange);
        void SetAttackRange(double _attackRange);
        void SetTeam(int _team);
        void SetLife(int _life);
        void SetHealth(int _health);
        void SetDamage(int _damage);
        
        std::queue<WeakPointer<MapCharacterAction>> GetQueuedAction();
        void QueueAction(WeakPointer<MapCharacterAction> action);
        
        bool IsDead();
    protected:
        int GetFramesForAnimation(CharacterAnimations animation);
    private:
        std::map<CharacterAnimations, std::map<CharacterDirections,std::vector<SharedPointer<Daemons::Gfx::Entity>>>> bodyEntities;
        std::map<CharacterAnimations, std::map<CharacterDirections,std::vector<SharedPointer<Daemons::Gfx::Entity>>>> headEntities;
        std::map<CharacterAnimations, std::map<CharacterDirections,std::vector<SharedPointer<Daemons::Gfx::Entity>>>> weaponEntities;
        
        std::queue<WeakPointer<MapCharacterAction>> actionQueue;
        
        CharacterAnimations currentAnimation;
        CharacterDirections currentDirection;
        int currentAnimationFrame;
        
        int cooldown;
        int cooldownCounter;
        
        double speed;
        double sightRange;
        double attackRange;
        int team;
        int life;
        int health;
        int damage;
    };
}}};