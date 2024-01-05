#include "player.h"
#include "util.h"
#include <cmath>
#include <iomanip>

void Player::update(float dt)
{
	float delta_time = dt / 1000.0f;

	movePlayer(dt);

	// update offset for other game objects
	m_state->m_global_offset_x = CANVAS_WIDTH / 2.0f - m_pos_x;
	m_state->m_global_offset_y = CANVAS_HEIGHT / 2.0f - m_pos_y;
	
	GameObject::update(dt);

}

void Player::init()
{
	// stage 1
	m_pos_x = 2.0f;
	m_pos_y = 6.0f;
	
	m_state->m_global_offset_x = CANVAS_WIDTH / 2.0f - m_pos_x;
	m_state->m_global_offset_y = CANVAS_HEIGHT / 2.0f - m_pos_y;

	m_brush_player.fill_opacity = 1.0f;
	m_brush_player.outline_opacity = 0.0f;
	m_brush_player.texture = m_state->getFullAssetPath("Boing-turn3.png");

    int numSprites = 19;
    for (int i = 0; i <= numSprites; ++i) {
        // Use std::setw and std::setfill to format the index as "00", "01", etc.
        std::stringstream ss;
        ss << "player/WizardWalk" << std::setw(2) << std::setfill('0') << i << ".png";
        m_sprites.push_back(m_state->getFullAssetPath(ss.str()));
    }

	// Adjust width for finer collision detection
	m_width = 0.5f;

}

void Player::draw()
{
    if (!m_sprites.empty()) {
        // Calculate the raw index
        int rawIndex = (int)fmod(100.0f - m_pos_x * 9.0f, m_sprites.size());

        // Use modulo to wrap the index within the bounds of m_sprites
        int spriteIndex = (rawIndex + m_sprites.size()) % m_sprites.size();
        m_brush_player.texture = m_sprites[spriteIndex];
    }

    graphics::drawRect(CANVAS_WIDTH*0.5f, CANVAS_HEIGHT * 0.5f, 2.0f, 2.0f, m_brush_player);
    if (m_state->m_debugging)
        debugDraw();
}

void Player::debugDraw()
{
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 1, 0.1f, 0);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	graphics::drawRect(CANVAS_WIDTH*0.5f, CANVAS_HEIGHT * 0.5f, m_width, m_height, debug_brush);
	
	char s[20];
	sprintf(s,"(%5.2f, %5.2f)", m_pos_x, m_pos_y);
	SETCOLOR(debug_brush.fill_color, 1, 0, 0);
	debug_brush.fill_opacity = 1.0f;
	graphics::drawText(CANVAS_WIDTH * 0.5f - 0.4f, CANVAS_HEIGHT * 0.5f - 0.6f, 0.15f, s, debug_brush);
}

void Player::movePlayer(float dt)
{
	float delta_time = dt / 1000.0f;

	// Stage 2 code: Acceleration-based velocity
	float move = 0.0f;
	if (graphics::getKeyState(graphics::SCANCODE_A))
		move -= 1.0f;
	if (graphics::getKeyState(graphics::SCANCODE_D))
		move = 1.0f;

	m_vx = std::min<float>(m_max_velocity, m_vx + delta_time * move * m_accel_horizontal);
	m_vx = std::max<float>(-m_max_velocity, m_vx);

	// friction
	m_vx -= 0.2f * m_vx / (0.1f + fabs(m_vx));

	// apply static friction threshold
	if (fabs(m_vx) < 0.01f)
		m_vx = 0.0f;

	// adjust horizontal position
	m_pos_x += m_vx * delta_time;

	// jump only when not in flight:
	if (m_vy == 0.0f)
		m_vy -= (graphics::getKeyState(graphics::SCANCODE_W) ? m_accel_vertical : 0.0f) * 0.02f;// not delta_time!! Burst 

	// add gravity
	m_vy += delta_time * m_gravity;

	// adjust vertical position
	m_pos_y += m_vy * delta_time;

	
}

