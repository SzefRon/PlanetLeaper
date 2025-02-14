#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include <Windows.h>

const int screen_x = 128, screen_y = 64;

bool within_bounds(glm::ivec2 vec)
{
    if (vec.x >= 0 && vec.y >= 0
    && vec.x < screen_x && vec.y < screen_y) {
        return true;
    }
    return false;
}

int main()
{
    float camera_position_x = 0.0f;
    float camera_position_y = 0.0f;
    float camera_rotation = 0.0f;
    float camera_zoom = 1.0f;

    char screen[screen_y][screen_x];
    std::fill(screen[0], screen[screen_y] + screen_x, ' ');

    while (true) {
        std::cout << "\033[H";
        std::fill(screen[0], screen[screen_y] + screen_x, ' ');

        if (GetAsyncKeyState(VkKeyScan('w'))) camera_position_y += 0.1f;
        if (GetAsyncKeyState(VkKeyScan('s'))) camera_position_y -= 0.1f;
        if (GetAsyncKeyState(VkKeyScan('a'))) camera_position_x += 0.1f;
        if (GetAsyncKeyState(VkKeyScan('d'))) camera_position_x -= 0.1f;

        if (GetAsyncKeyState(VkKeyScan('q'))) camera_rotation += 0.01f;
        if (GetAsyncKeyState(VkKeyScan('e'))) camera_rotation -= 0.01f;

        if (GetAsyncKeyState(VkKeyScan('z'))) camera_zoom -= 0.01f;
        if (GetAsyncKeyState(VkKeyScan('c'))) camera_zoom += 0.01f;

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(screen_x * 0.5f, screen_y * 0.5f, 0.0f));
        view = glm::scale(view, glm::vec3(camera_zoom, camera_zoom, 1.0f));
        view = glm::rotate(view, -camera_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        view = glm::translate(view, glm::vec3(-screen_x * 0.5f, -screen_y * 0.5f, 0.0f));
        view = glm::translate(view, glm::vec3(camera_position_x, camera_position_y, 0.0f));

        for (int i = 0; i < 32; i++) {
            for (int j = 0; j < 32; j++) {

                glm::vec4 pos = {i, j, 0.0f, 1.0f};
                glm::vec4 screen_pos = view * pos;

                glm::ivec2 screen_idx_1(glm::floor(screen_pos.x), glm::floor(screen_pos.y));
                glm::ivec2 screen_idx_2(glm::round(screen_pos.x), glm::floor(screen_pos.y));
                glm::ivec2 screen_idx_3(glm::floor(screen_pos.x), glm::round(screen_pos.y));
                glm::ivec2 screen_idx_4(glm::round(screen_pos.x), glm::round(screen_pos.y));
                
                if (within_bounds(screen_idx_1)) screen[screen_idx_1.y][screen_idx_1.x] = '#';
                if (within_bounds(screen_idx_2)) screen[screen_idx_2.y][screen_idx_2.x] = '#';
                if (within_bounds(screen_idx_3)) screen[screen_idx_3.y][screen_idx_3.x] = '#';
                if (within_bounds(screen_idx_4)) screen[screen_idx_4.y][screen_idx_4.x] = '#';
            }
        }

        std::string screen_final;
        screen_final.reserve(screen_y * (screen_x + 1));
        for (int i = 0; i < screen_y; i++) {
            for (int j = 0; j < screen_x; j++) {
                screen_final.push_back(screen[i][j]);
            }
            screen_final.push_back('\n');
        }

        std::cout << screen_final;
        std::cout << camera_position_x << " " << camera_position_y;
    }

}