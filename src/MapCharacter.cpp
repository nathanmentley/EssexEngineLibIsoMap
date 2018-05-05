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

#include <EssexEngineLibIsoMap/MapCharacter.h>

EssexEngine::Libs::IsoMap::MapCharacter::MapCharacter(WeakPointer<Context> gameContext, WeakPointer<Daemons::Window::IRenderContext> _target, std::string bodyTexture, std::string headTexture, std::string weaponTexture)
:MapObject() {
    target = _target;
    bodyEntities = std::map<CharacterAnimations, std::map<CharacterDirections,std::vector<UniquePointer<Daemons::Gfx::Entity>>>>();
    headEntities = std::map<CharacterAnimations, std::map<CharacterDirections,std::vector<UniquePointer<Daemons::Gfx::Entity>>>>();
    weaponEntities = std::map<CharacterAnimations, std::map<CharacterDirections,std::vector<UniquePointer<Daemons::Gfx::Entity>>>>();
    
    for(int i = 0; i < 7; i++) {
        int animationOffSet = 0;
        
        for(int j = 0; j < i; j++) {
            animationOffSet += GetFramesForAnimation(static_cast<CharacterAnimations>(j));
        }
        
        bodyEntities[static_cast<CharacterAnimations>(i)] = std::map<CharacterDirections, std::vector<UniquePointer<Daemons::Gfx::Entity>>>();
        
        for(int j = 0; j < 8; j++) {
            bodyEntities[static_cast<CharacterAnimations>(i)][static_cast<CharacterDirections>(j)] = std::vector<UniquePointer<Daemons::Gfx::Entity>>();
            
            for(int k = 0; k < GetFramesForAnimation(static_cast<CharacterAnimations>(i)); k++) {
                bodyEntities[static_cast<CharacterAnimations>(i)][static_cast<CharacterDirections>(j)].push_back(
                    gameContext->GetDaemon<EssexEngine::Daemons::Gfx::GfxDaemon>()->GetEntity(
                        gameContext->GetDaemon<EssexEngine::Daemons::Gfx::GfxDaemon>()->GetSprite(
                            target,
                            gameContext->GetDaemon<Daemons::FileSystem::FileSystemDaemon>()->ReadFile(bodyTexture),
                            CHARACTER_WIDTH * (animationOffSet + k),
                            CHARACTER_HEIGHT * j,
                            CHARACTER_WIDTH,
                            CHARACTER_HEIGHT
                        )
                    )
                );
            }
        }
    }
    for(int i = 0; i < 7; i++) {
        int animationOffSet = 0;
        
        for(int j = 0; j < i; j++) {
            animationOffSet += GetFramesForAnimation(static_cast<CharacterAnimations>(j));
        }
        
        headEntities[static_cast<CharacterAnimations>(i)] = std::map<CharacterDirections, std::vector<UniquePointer<Daemons::Gfx::Entity>> >();
        
        for(int j = 0; j < 8; j++) {
            headEntities[static_cast<CharacterAnimations>(i)][static_cast<CharacterDirections>(j)] = std::vector<UniquePointer<Daemons::Gfx::Entity>>();
            
            for(int k = 0; k < GetFramesForAnimation(static_cast<CharacterAnimations>(i)); k++) {
                headEntities[static_cast<CharacterAnimations>(i)][static_cast<CharacterDirections>(j)].push_back(
                    gameContext->GetDaemon<EssexEngine::Daemons::Gfx::GfxDaemon>()->GetEntity(
                        gameContext->GetDaemon<EssexEngine::Daemons::Gfx::GfxDaemon>()->GetSprite(
                            target,
                            gameContext->GetDaemon<Daemons::FileSystem::FileSystemDaemon>()->ReadFile(headTexture),
                            CHARACTER_WIDTH * (animationOffSet + k),
                            CHARACTER_HEIGHT * j,
                            CHARACTER_WIDTH,
                            CHARACTER_HEIGHT
                        )
                    )
                );
            }
        }
    }
    for(int i = 0; i < 7; i++) {
        int animationOffSet = 0;
        
        for(int j = 0; j < i; j++) {
            animationOffSet += GetFramesForAnimation(static_cast<CharacterAnimations>(j));
        }
        
        weaponEntities[static_cast<CharacterAnimations>(i)] = std::map<CharacterDirections, std::vector<UniquePointer<Daemons::Gfx::Entity>> >();
        
        for(int j = 0; j < 8; j++) {
            weaponEntities[static_cast<CharacterAnimations>(i)][static_cast<CharacterDirections>(j)] = std::vector<UniquePointer<Daemons::Gfx::Entity>>();
            
            for(int k = 0; k < GetFramesForAnimation(static_cast<CharacterAnimations>(i)); k++) {
                weaponEntities[static_cast<CharacterAnimations>(i)][static_cast<CharacterDirections>(j)].push_back(
                    gameContext->GetDaemon<EssexEngine::Daemons::Gfx::GfxDaemon>()->GetEntity(
                        gameContext->GetDaemon<EssexEngine::Daemons::Gfx::GfxDaemon>()->GetSprite(
                            target,
                            gameContext->GetDaemon<Daemons::FileSystem::FileSystemDaemon>()->ReadFile(weaponTexture),
                            CHARACTER_WIDTH * (animationOffSet + k),
                            CHARACTER_HEIGHT * j,
                            CHARACTER_WIDTH,
                            CHARACTER_HEIGHT
                        )
                    )
                );
            }
        }
    }
    
    actionQueue = std::queue<WeakPointer<MapCharacterAction>>();
    
    currentDirection = West;
    currentAnimation = Stance;
    currentAnimationFrame = 0;
    
    cooldown = 3;
    cooldownCounter = 0;
    
    speed = .2;
    sightRange = 10;
    attackRange = 1.3;
    
    life = 1;
    health = 1;
    damage = 0;
    team = 1;
}

EssexEngine::Libs::IsoMap::MapCharacter::~MapCharacter()
{
    //delete shit
}

void EssexEngine::Libs::IsoMap::MapCharacter::SetScreenPosition(int _x, int _y) {
    MapObject::SetScreenPosition(_x - (32 * GetZoom()), _y - (64 * GetZoom()));
}

void EssexEngine::Libs::IsoMap::MapCharacter::Render(WeakPointer<Context> gameContext) {
    WeakPointer<Daemons::Gfx::Entity> body = bodyEntities[currentAnimation][currentDirection].at(currentAnimationFrame).ToWeakPointer();
    WeakPointer<Daemons::Gfx::Entity> head = headEntities[currentAnimation][currentDirection].at(currentAnimationFrame).ToWeakPointer();
    WeakPointer<Daemons::Gfx::Entity> weapon = weaponEntities[currentAnimation][currentDirection].at(currentAnimationFrame).ToWeakPointer();
    
    body->SetPosition(GetScreenX(), GetScreenY());
    body->SetScale(GetZoom(), GetZoom());
    head->SetPosition(GetScreenX(), GetScreenY());
    head->SetScale(GetZoom(), GetZoom());
    weapon->SetPosition(GetScreenX(), GetScreenY());
    weapon->SetScale(GetZoom(), GetZoom());
    
    gameContext->GetDaemon<Daemons::Gfx::GfxDaemon>()->RenderEntity(target, body);
    gameContext->GetDaemon<Daemons::Gfx::GfxDaemon>()->RenderEntity(target, head);
    gameContext->GetDaemon<Daemons::Gfx::GfxDaemon>()->RenderEntity(target, weapon);
}

void EssexEngine::Libs::IsoMap::MapCharacter::Update() {
    cooldownCounter += 1;
    
    if(cooldownCounter >= cooldown) {
        int totalFrames = GetFramesForAnimation(currentAnimation);
        
        if(currentAnimationFrame + 1 < totalFrames) {
            currentAnimationFrame += 1;
        } else {
            currentAnimationFrame = 0;
        }
        
        cooldownCounter = 0;
    }
    
    if(IsDead()) {
        SetAnimation(CharacterAnimations::HitAndDie);
    }
}

void EssexEngine::Libs::IsoMap::MapCharacter::SetAnimation(CharacterAnimations animation) {
    if(currentAnimation != animation) {
        currentAnimation = animation;
        currentAnimationFrame = 0;
    }
}
void EssexEngine::Libs::IsoMap::MapCharacter::SetDirection(CharacterDirections direction) {
    if(currentDirection != direction) {
        currentDirection = direction;
    }
}

double EssexEngine::Libs::IsoMap::MapCharacter::GetSpeed() {
    return speed;
}

double EssexEngine::Libs::IsoMap::MapCharacter::GetSightRange() {
    return sightRange;
}

double EssexEngine::Libs::IsoMap::MapCharacter::GetAttackRange() {
    return attackRange;
}

int EssexEngine::Libs::IsoMap::MapCharacter::GetTeam() {
    return team;
}

int EssexEngine::Libs::IsoMap::MapCharacter::GetLife() {
    return life;
}

int EssexEngine::Libs::IsoMap::MapCharacter::GetHealth() {
    return health;
}

int EssexEngine::Libs::IsoMap::MapCharacter::GetDamage() {
    return damage;
}

void EssexEngine::Libs::IsoMap::MapCharacter::SetSpeed(double _speed) {
    speed = _speed;
}
void EssexEngine::Libs::IsoMap::MapCharacter::SetSightRange(double _sightRange) {
    sightRange = _sightRange;
}

void EssexEngine::Libs::IsoMap::MapCharacter::SetAttackRange(double _attackRange) {
    attackRange = _attackRange;
}

void EssexEngine::Libs::IsoMap::MapCharacter::SetTeam(int _team) {
    team = _team;
}

void EssexEngine::Libs::IsoMap::MapCharacter::SetLife(int _life) {
    life = _life;
}

void EssexEngine::Libs::IsoMap::MapCharacter::SetHealth(int _health) {
    health = _health;
}

void EssexEngine::Libs::IsoMap::MapCharacter::SetDamage(int _damage) {
    damage = _damage;
}

std::queue<EssexEngine::WeakPointer<EssexEngine::Libs::IsoMap::MapCharacterAction>> EssexEngine::Libs::IsoMap::MapCharacter::GetQueuedAction() {
    return actionQueue;
}

void EssexEngine::Libs::IsoMap::MapCharacter::QueueAction(MapCharacterActionTypes _type) {
    if(!IsDead()) {
        EssexEngine::WeakPointer<MapCharacterAction> action = WeakPointer<MapCharacterAction>(
            new MapCharacterAction(_type, WeakPointer<MapObject>())
        );
        actionQueue.push(action);
    }
}

void EssexEngine::Libs::IsoMap::MapCharacter::QueueAction(MapCharacterActionTypes _type, WeakPointer<MapObject> _target) {
    if(!IsDead()) {
        EssexEngine::WeakPointer<MapCharacterAction> action = WeakPointer<MapCharacterAction>(
            new MapCharacterAction(_type, _target)
        );
        actionQueue.push(action);
    }
}

int EssexEngine::Libs::IsoMap::MapCharacter::GetFramesForAnimation(CharacterAnimations animation) {
    switch(animation) {
        case Stance:
            return 4;
        case Running:
            return 8;
        case MeleeSwing:
            return 4;
        case Block:
            return 2;
        case HitAndDie:
            return 6;
        case CastSpell:
            return 4;
        case ShootBow:
            return 4;
    }
    
    return 0;
}

bool EssexEngine::Libs::IsoMap::MapCharacter::IsDead() {
    return health <= 0;
}
