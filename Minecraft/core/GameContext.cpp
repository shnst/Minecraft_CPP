//
//  GameContext.cpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "GameContext.hpp"

#include "Camera.hpp"
#include "FieldMode.hpp"
#include "GameMode.hpp"
#include "UIManager.hpp"
#include "UIUDP.hpp"
#include "Utils.hpp"


GameContext::GameContext()
:gameMode(nullptr)
,camera(new Camera())
{
}

GameContext::~GameContext() {
    Utils::SafeDelete(gameMode);
}

void GameContext::openUDP() {
    UIManager::get().clearAllBaseUI();
    UIManager::get().addNewBaseUI(new UIUDP());
}

void GameContext::setPauseGame(bool isPaused) {
    if (gameMode == nullptr) {
        return;
    }
    gameMode->pause(isPaused);
}

void GameContext::startGame(GameMode* gameMode) {
    this->gameMode = gameMode;
    gameMode->start();
}

GameMode* GameContext::getGameMode() {
    return gameMode;
}

void GameContext::quitGame() {
    if (gameMode == nullptr) {
        return;
    }
    gameMode->quit();
    Utils::SafeDelete(gameMode);
}

void GameContext::goTitle() {
//    quitGame();
//    UIManager::get().clearAllBaseUI();
//    UIManager::get().addNewBaseUI(new UIUDP());
    startGame(new FieldMode());
}

Camera* GameContext::getCamera() {
    return camera;
}
