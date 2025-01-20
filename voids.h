#pragma once

#include "moving_characters.h"
#include <fstream>
#include <iostream>
#include <queue>

void insert_to_q(queue<Text>& q, const Text& text1, const Text& text2, const Text& text3, const Text& text4, const Text& text5);

void generate_pause_text(Font& font, Text& paused_text, Text& continue_text, Text& help_text, Text& quit_text, Text& confirmation);

void choose_map(RenderWindow& window, Font& font, int& choice, Sprite& background_sprite, RectangleShape& dark_background, Text& title, Text& author, string& player_name);

void display_menu(RenderWindow& window, Font& font, int& choice, string& player_name);

void display_game_over(RenderWindow& window, Font& font, int score);

void reset_game_state(punkty& punkty, labirynth& labirynth, int& score);

Texture load_texture(const string& filename);

void draw_high_scores(RenderWindow& window, Font& font);