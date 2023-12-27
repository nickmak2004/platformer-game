#include <cmath>
#include "../include/Game.h"
#include "../include/config.h"
#include "../sgg/include/graphics.h"

void Game::update() {
    if (player) {
        player->update();
    }
}

void Game::draw() {

    // Draw Background
    graphics::Brush br;
    br.texture = std::string(ASSET_PATH) + "city_background.png";
    graphics::drawRect(CANVAS_WIDTH/2.0f, CANVAS_HEIGHT/2.0f, CANVAS_WIDTH, CANVAS_HEIGHT, br);

    // Draw Player
    if (player) {
        player->draw();
    }
}


void Game::init() {

}
Game::Game() {
    if (!player) {
        player = new Player();
    }
};

Game::~Game() {
    if (player) {
        delete player;
    }
};