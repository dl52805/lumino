#include <stdio.h>

#include <raylib.h>

constexpr int width  = 800;
constexpr int height = 800;

int main(int argc, char **argv)
{
  SetConfigFlags(FLAG_WINDOW_HIGHDPI);

  InitWindow(width, height, "raylib");

  Camera3D camera = {0};
  camera.position = (Vector3) {
    10.0f, 10.0f, 10.0f,
  };
  camera.target = (Vector3) {
    0.0f, 0.0f, 0.0f,
  };
  camera.up = (Vector3) {
    0.0f, 1.0f, 0.0f,
  };
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  Vector3 cube_position = {
    0.0f, 0.0f, 0.0f,
  };

  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    BeginDrawing();
      ClearBackground(RAYWHITE);

      BeginMode3D(camera);
        DrawCube(cube_position, 2.0f, 2.0f, 2.0f, MAROON);
      EndMode3D();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

