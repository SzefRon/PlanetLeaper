#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include <Windows.h>

bool within_bounds(glm::ivec2 vec)
{
    if (vec.x >= 0 && vec.y >= 0
    && vec.x < 16 && vec.y < 16) {
        return true;
    }
    return false;
}

int main()
{
    float camera_position_x = 0.0f;
    float camera_position_y = 0.0f;
    float camera_rotation = 0.0f;

    char screen[16][16];
    std::fill(screen[0], screen[15] + 16, ' ');

    while (true) {
        std::cout << "\033[H";
        std::fill(screen[0], screen[15] + 16, ' ');

        if (GetAsyncKeyState(VkKeyScan('w'))) camera_position_y += 0.1f;
        if (GetAsyncKeyState(VkKeyScan('s'))) camera_position_y -= 0.1f;
        if (GetAsyncKeyState(VkKeyScan('a'))) camera_position_x += 0.1f;
        if (GetAsyncKeyState(VkKeyScan('d'))) camera_position_x -= 0.1f;

        if (GetAsyncKeyState(VkKeyScan('q'))) camera_rotation += 0.01f;
        if (GetAsyncKeyState(VkKeyScan('e'))) camera_rotation -= 0.01f;

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(8.0f, 8.0f, 0.0f));
        view = glm::rotate(view, -camera_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        view = glm::translate(view, glm::vec3(-8.0f, -8.0f, 0.0f));
        view = glm::translate(view, glm::vec3(camera_position_x, camera_position_y, 0.0f));

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {

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

        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                std::cout << screen[i][j];
            }
            std::cout << '\n';
        }

        std::cout << camera_position_x << " " << camera_position_y;
    }

}