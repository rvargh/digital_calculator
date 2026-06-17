#include <chrono>
#include <array>
#include "raylib.h"

// clang++ -Wall -std=c++20 -stdlib=libc++ DigitialClock.cpp -o clock -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;
constexpr float node_thickness = 18.5f;
constexpr float node_width = 37.0f;
constexpr int point_count = 6;
constexpr float gap = 5.0f;
constexpr float STEP = 25.0f;

constexpr  Color SEGMENT_ON = GREEN;
constexpr  Color SEGMENT_OFF = BLACK;

struct SegmentState
{
    bool top, top_left, top_right, middle, bottom_left, bottom_right, bottom;
};

std::array<SegmentState, 10> segment_state = {
    {
        {true, true, true, false, true, true, true},     /* 0 */
        {false, false, true, false, false, true, false}, /* 1 */
        {true, false, true, true, true, false, true},    /* 2 */
        {true, false, true, true, false, true, true},    /* 3 */
        {false, true, true, true, false, true, false},   /* 4 */
        {true, true, false, true, false, true, true},    /* 5 */
        {true, true, false, true, true, true, true},     /* 6 */
        {true, false, true, false, false, true, false},  /* 7 */
        {true, true, true, true, true, true, true},      /* 8 */
        {true, true, true, true, false, true, true},     /* 9 */
    }};

void draw_segments(Vector2 centre_points, bool horizontal, Color color = RAYWHITE)
{
    std::array<Vector2, 6> points;
    const float half_length = (node_width / 2.0f) - gap;
    const float half_thick = node_thickness / 2.0f;
    if (horizontal)
    {
        points = {{
            {centre_points.x - half_length - half_thick, centre_points.y}, // a
            {centre_points.x - half_length, centre_points.y + half_thick}, // c
            {centre_points.x - half_length, centre_points.y - half_thick}, // b
            {centre_points.x + half_length, centre_points.y + half_thick}, // e
            {centre_points.x + half_length, centre_points.y - half_thick}, // d
            {centre_points.x + half_length + half_thick, centre_points.y}, // f
        }};
    }
    else
    {
        points = {{
            {centre_points.x, centre_points.y + half_length + half_thick}, // a
            {centre_points.x + half_thick, centre_points.y + half_length}, // b
            {centre_points.x - half_thick, centre_points.y + half_length}, // c
            {centre_points.x + half_thick, centre_points.y - half_length}, // d
            {centre_points.x - half_thick, centre_points.y - half_length}, // e
            {centre_points.x, centre_points.y - half_length - half_thick}, // f
        }};
    }

    DrawTriangleStrip(points.data(), point_count, color);
}

void draw_digits(const float start_x, const float start_y, std::string digits)
{
    const float digit_spacing = 75.0f;
    const float dot_radius = 10.0f;

    for (int digit_index = 0; digit_index < digits.size(); digit_index++)
    {
        float current_x = start_x + (digit_index * digit_spacing);

        // 58 ascii for :
        if (digits[digit_index] == 58)
        {
            current_x += 25;
            DrawCircle(current_x, start_y + 25, dot_radius, GOLD); // Upper dot
            DrawCircle(current_x, start_y + 75, dot_radius, GOLD); // Lower dot
            continue;
        }

        int raw_int = digits[digit_index] - '0';

        auto state = segment_state.at(raw_int);

        draw_segments({current_x + STEP, start_y}, true, state.top ? SEGMENT_ON : SEGMENT_OFF);                          // top
        draw_segments({current_x, start_y + STEP}, false, state.top_left ? SEGMENT_ON : SEGMENT_OFF);                    // upper_left
        draw_segments({current_x + 2 * STEP, start_y + STEP}, false, state.top_right ? SEGMENT_ON : SEGMENT_OFF);        // upper_right
        draw_segments({current_x + STEP, start_y + 2 * STEP}, true, state.middle ? SEGMENT_ON : SEGMENT_OFF);            // middle
        draw_segments({current_x, start_y + 3 * STEP}, false, state.bottom_left ? SEGMENT_ON : SEGMENT_OFF);             // lower_left
        draw_segments({current_x + 2 * STEP, start_y + 3 * STEP}, false, state.bottom_right ? SEGMENT_ON : SEGMENT_OFF); // lower_right
        draw_segments({current_x + STEP, start_y + 4 * STEP}, true, state.bottom ? SEGMENT_ON : SEGMENT_OFF);            // bottom
    }
}

int main()
{

    InitWindow(WIDTH, HEIGHT, "Digital Clock");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        auto now = std::chrono::system_clock::now();
        auto now_sec = std::chrono::time_point_cast<std::chrono::seconds>(now);
        std::string format_time = std::format("{:%H:%M:%S}", now_sec);
        BeginDrawing();
        ClearBackground(BLACK);

        draw_digits(400, 300, format_time);

        EndDrawing();

    }

    CloseWindow();
}
