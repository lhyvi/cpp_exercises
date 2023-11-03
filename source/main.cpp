#ifdef _MSC_VER
#  define _CRT_SECURE_NO_WARNINGS
#endif

#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main(int argc, char** argv)
{
  const int screenWidth = 200;
  const int screenHeight = 100;

  SetConfigFlags(FLAG_WINDOW_UNDECORATED);
  InitWindow(screenWidth, screenHeight, "raygui - portable window");

  Vector2 mousePosition = {0};
  Vector2 windowPosition = {500, 200};
  Vector2 panOffset = mousePosition;
  bool dragWindow = false;

  SetWindowPosition(windowPosition.x, windowPosition.y);

  bool exitWindow = false;

  char input[1024] = "";

  SetTargetFPS(60);
  while (!exitWindow && !WindowShouldClose()) {
    mousePosition = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !dragWindow) {
      if (CheckCollisionPointRec(mousePosition,
                                 Rectangle {0, 0, screenWidth, 20}))
      {
        dragWindow = true;
        panOffset = mousePosition;
      }
    }

    if (dragWindow) {
      windowPosition.x += (mousePosition.x - panOffset.x);
      windowPosition.y += (mousePosition.y - panOffset.y);

      SetWindowPosition((int)windowPosition.x, (int)windowPosition.y);

      if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        dragWindow = false;
    }

    BeginDrawing();

    ClearBackground(RAYWHITE);

    exitWindow = GuiWindowBox(Rectangle {0, 0, screenWidth, screenHeight},
                              "#198# CHARACTER COUNTER");

    GuiTextBox(Rectangle {10, 40, 180, 20}, input, 1023, 1);
    GuiDrawText(TextFormat("Total Count: %zu", strlen(input)),
                Rectangle {10, 60, 180, 20},
                1,
                DARKGRAY);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
