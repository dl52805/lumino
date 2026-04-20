#include <fmt/core.h>

#include <stdio.h>

#include <raylib.h>

constexpr int width  = 800;
constexpr int height = 800;

int main(int argc, char **argv)
{
  SetConfigFlags(FLAG_WINDOW_HIGHDPI);

  InitWindow(width, height, "raylib");

  Camera3D camera = {0};
  camera.position = Vector3 {
    80.0f, 80.0f, 80.0f,
  };
  camera.target = Vector3 {
    0.0f, 12.0f, 0.0f,
  };
  camera.up = Vector3 {
    0.0f, 1.0f, 0.0f,
  };
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  Model model = LoadModel("resources/castle.obj");
  Texture2D texture = LoadTexture("resources/castle_diffuse.png");
  model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

  Vector3 model_position = {
    0.0f, 0.0f, 0.0f,
  };

  BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);

  int triangle_count = model.meshes[0].vertexCount / 3;
  Vector3 *model_vertices = (Vector3 *) model.meshes[0].vertices;
  for(int i = 0; i < triangle_count; i++)
  {
    Vector3 a, b, c;
    if (model.meshes[0].indices != nullptr)
    {
      int idx_a = model.meshes[0].indices[i * 3 + 0];
      int idx_b = model.meshes[0].indices[i * 3 + 1];
      int idx_c = model.meshes[0].indices[i * 3 + 2];

      a = model_vertices[idx_a];
      b = model_vertices[idx_b];
      c = model_vertices[idx_c];
    }
    else
    {
      a = model_vertices[i * 3 + 0];
      b = model_vertices[i * 3 + 1];
      c = model_vertices[i * 3 + 2];
    }
  }

  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    BeginDrawing();
      ClearBackground(RAYWHITE);

      BeginMode3D(camera);
        DrawModel(model, model_position, 1.0f, WHITE);
        DrawGrid(20, 10.0f);
      EndMode3D();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

