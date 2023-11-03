#ifdef _MSC_VER
#  define _CRT_SECURE_NO_WARNINGS
#endif

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

double get_double(const std::string& msg)
{
  while (true) {
    std::cout << msg;
    double num {};
    std::cin >> num;
    if (!std::cin) {
      if (std::cin.eof()) {
        exit(0);
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Please enter a valid number.\n";
    } else {
      return num;
    }
  }
}

double get_double_nn(const std::string& msg)
{
  while (true) {
    double n = get_double(msg);
    if (n < 0) {
      std::cout << "Please only enter non-negative numbers.\n";
    } else {
      return n;
    }
  }
}

void cli_main()
{
  double bill = get_double_nn("What is the bill? $");
  double tip_rate = get_double_nn("What is the tip percentage? ");

  double tip = std::round(bill * tip_rate) / 100;
  double total = bill + tip;

  std::cout << std::fixed << std::setprecision(2) << "Tip: $" << tip
            << "\nTotal: $" << total;
}

int main(int argc, char** argv)
{
  const int screenWidth = 200;
  const int screenHeight = 120;

  SetConfigFlags(FLAG_WINDOW_UNDECORATED);
  InitWindow(screenWidth, screenHeight, "raygui - portable window");

  Vector2 mousePosition = {0};
  Vector2 windowPosition = {500, 200};
  Vector2 panOffset = mousePosition;
  bool dragWindow = false;

  int bill = 0;
  float val = 0;

  SetWindowPosition(windowPosition.x, windowPosition.y);

  bool exitWindow = false;

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
                              "#198# TIP CALCULATOR");

    GuiValueBox(Rectangle {70, 40, 100, 20},
                "Bill Amount:",
                &bill,
                0,
                std::numeric_limits<int>::max(),
                1);
    val = GuiSliderBar(Rectangle {70, 60, 100, 20},
                       "Tip Rate:",
                       TextFormat("%d%%", (int)(val * 100)),
                       val,
                       0.0f,
                       1.0f);
    GuiDrawText(TextFormat("Tip: $%.2f", (bill * val)),
                Rectangle {70, 80, 100, 20},
                1,
                DARKGRAY);
    GuiDrawText(TextFormat("Total: $%.2f", (bill * val) + bill),
                Rectangle {70, 100, 100, 20},
                1,
                DARKGRAY);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
