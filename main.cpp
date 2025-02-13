#include <raylib.h>

const int WIDTH = 1000, HEIGHT = 1000;
int targetFPS = 120;

int main(){

    InitWindow(WIDTH, HEIGHT, "MandlebrotSet");
    SetTargetFPS(targetFPS);

    Shader baseShader = LoadShader(0, "Shaders/baseShader.frag");
    int timeLoc = GetShaderLocation(baseShader, "time");
    int zoomLoc = GetShaderLocation(baseShader, "zoomFactor");
    int resolutionLoc = GetShaderLocation(baseShader, "resolution");
    int offsetLoc = GetShaderLocation(baseShader, "offset");
    Vector2 resolution = {(float)WIDTH, (float)HEIGHT };
    float xOffset = 0.0f;
    float yOffset = 0.0f;

    float zoomUni = 1.0f;

    SetShaderValue(baseShader, resolutionLoc, &resolution, SHADER_UNIFORM_VEC2);

    RenderTexture2D targetTexture = LoadRenderTexture(WIDTH, HEIGHT);
    Rectangle texturedRec = {0, 0, WIDTH, HEIGHT};

    while (!WindowShouldClose()) {

        float time = GetTime();
        Vector2 offsetUniform = {xOffset, yOffset};
        SetShaderValue(baseShader, offsetLoc, &offsetUniform, SHADER_UNIFORM_VEC2);
        SetShaderValue(baseShader, timeLoc, &time, SHADER_UNIFORM_FLOAT);
        SetShaderValue(baseShader, zoomLoc, &zoomUni, SHADER_UNIFORM_FLOAT);

        // BeginTextureMode(targetTexture);
        //     ClearBackground(BLANK);
        //     DrawTextureRec(targetTexture.texture, texturedRec, (Vector2){0.0f, 0.0f}, WHITE);
        // EndTextureMode();

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginShaderMode(baseShader);
                DrawTextureRec(targetTexture.texture, texturedRec, (Vector2){0.0f, 0.0f}, WHITE);
            EndShaderMode();
        EndDrawing();

        // Controlling Zoom Factor
        if(IsKeyDown(KEY_UP))
            zoomUni -= 0.01f;
        if(IsKeyDown(KEY_DOWN))
            zoomUni += 0.01f;
        // Moving Around
        if(IsKeyDown(KEY_W))
            yOffset += 0.01f;
        if(IsKeyDown(KEY_S))
            yOffset -= 0.01f;
        if(IsKeyDown(KEY_A))
            xOffset -= 0.01f;
        if(IsKeyDown(KEY_D))
            xOffset += 0.01f;
    }
    CloseWindow();
}