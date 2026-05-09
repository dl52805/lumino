#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>


typedef struct Edge {
    unsigned short v1;
    unsigned short v2;
} Edge;

Vector3 GetClosestPointOnSegment(Vector3 p, Vector3 a, Vector3 b) {
    Vector3 ab = Vector3Subtract(b, a);
    float t = Vector3DotProduct(Vector3Subtract(p, a), ab) / Vector3DotProduct(ab, ab);

    // Clamp t to the range [0, 1] to stay on the segment
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    return Vector3Add(a, Vector3Scale(ab, t));
}

std::vector<Vector3> intersection_list;
int main(void) {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib - Cube Edge Detection");

    Camera camera = { 0 };
    camera.position = { 3.0f, 3.0f, 3.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Create a base cube mesh
    Mesh cubeMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
    Model cubeModel = LoadModelFromMesh(cubeMesh);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Ray ray = GetMouseRay(GetMousePosition(), camera);

            // 1. Check for collision with the mesh
            RayCollision collision = GetRayCollisionMesh(ray, cubeMesh, MatrixIdentity());

            if (collision.hit) {
                // 2. Find the nearest edge
                // A cube has 12 edges. We define the 8 vertices of a 2x2x2 cube centered at 0
                std::vector<Vector3> v;
                for (int i = 0; i < cubeMesh.vertexCount; i+=3) {
                    v.push_back({cubeMesh.vertices[i], cubeMesh.vertices[i + 1], cubeMesh.vertices[i + 2]});
                }

                // Define the indices for the 12 edges of the cube
                Edge edges[12] = {
                    {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Back face
                    {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Front face
                    {0, 4}, {1, 5}, {2, 6}, {3, 7}  // Connecting edges
                };


                int closestEdge = -1;
                float minDistance = 0.3f; // Threshold for "clicking an edge"

                for (int i = 0; i < 12; i++) {
                    std::cout << edges[i].v2 << std::endl;
                    std::cout << edges[i].v1 << std::endl;
                    Vector3 p1 = v[edges[i].v1];

                    Vector3 p2 = v[edges[i].v2];

                    std::cout << "112" << std::endl;


                    // Calculate distance from collision point to the line segment (edge)
                    float dist = Vector3Distance(collision.point,
                                 GetClosestPointOnSegment(collision.point, p1, p2));

                    if (dist < minDistance) {
                        minDistance = dist;
                        closestEdge = i;
                    }
                }
                std::cout << "124" << std::endl;
                if (closestEdge != -1) {
                    Vector3 vA = v[edges[closestEdge].v1];
                    Vector3 vB = v[edges[closestEdge].v2];
                    Vector3 intersection = GetClosestPointOnSegment(collision.point, vA, vB);
                    printf("Edge Clicked! Vertices: (%.2f, %.2f, %.2f) and (%.2f, %.2f, %.2f)\n",
                           vA.x, vA.y, vA.z, vB.x, vB.y, vB.z);
                    printf("vertex edge clicked: (%.2f, %.2f, %.2f)\n", intersection.x, intersection.y, intersection.z);
                    intersection_list.push_back(intersection);
                    printf("Exact Intersection Point: (%.2f, %.2f, %.2f)\n",
                           collision.point.x, collision.point.y, collision.point.z);
                    printf("------------------------------------------\n");
                }
            }
        }

        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
                for (int i = 0; i < intersection_list.size() / 3; i++) {
                    DrawTriangle3D(intersection_list[3 * i], intersection_list[3 * i + 1], intersection_list[3 * i + 2], RED);
                    DrawTriangle3D(intersection_list[3 * i + 2], intersection_list[3 * i + 1], intersection_list[3 * i], RED);
                    //printf("%d\n", i);
                }
                //DrawModel(cubeModel, {0, 0, 0}, 1.0f, WHITE);
                DrawModelWires(cubeModel, {0, 0, 0}, 1.0f, DARKGRAY);
                DrawGrid(10, 1.0f);

            EndMode3D();

            DrawText("Click a cube edge to print vertex data", 10, 10, 20, GRAY);
        EndDrawing();
    }

    UnloadModel(cubeModel);
    ExportMesh(cubeMesh, "test.obj");
    CloseWindow();

    return 0;
}