#include "Game.hpp"

Game::Game() {
    InitWindow(1200, 900, "Super Mario Bros");
    InitAudioDevice();
    for (auto& file : std::filesystem::directory_iterator("resource\\textures")) {
        if (file.is_regular_file() && file.path().extension() == ".png") {
            Resource::textures[file.path().stem().string()] = LoadTexture(file.path().string().c_str()); 
        }
    }

    for (auto& file : std::filesystem::directory_iterator("resource\\sounds")) {
        if (file.is_regular_file() && file.path().extension() == ".wav") {
            Resource::sounds[file.path().stem().string()] = LoadSound(file.path().string().c_str()); 
            SetSoundVolume(Resource::sounds[file.path().stem().string()], 0.6f);
        }
    }

    mMusic = LoadMusicStream("resource\\sounds\\music.ogg");
    SetMusicVolume(mMusic, 0.4f);
    mMusic.looping = true;
    PlayMusicStream(mMusic);

    Physics::init();

    mCamera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    mCamera.target = {0, 0};
    mCamera.zoom     = 32.0f;
    mCamera.rotation = 0.0f;
    Image image = LoadImage("resource\\map.png");
    mMario.mPosition = mMap.createFromImage(image);
    UnloadImage(image);
    mMario.init();
}

void Game::run() {
    float mTimeElapsed = 0;
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        mTimeElapsed += GetFrameTime();
        input();

        while (mTimeElapsed >= mTimePerFrame) {
            mTimeElapsed -= mTimePerFrame;
            update(mTimePerFrame);
        }

        UpdateMusicStream(mMusic);
        Physics::mDraw.updateBounds(mCamera);

        BeginDrawing();
            ClearBackground(BLACK);
            draw();
        EndDrawing();
    }

    for (auto texture: Resource::textures) {
        UnloadTexture(texture.second);
    }

    for (auto sound: Resource::sounds) {
        UnloadSound(sound.second);
    }

    UnloadMusicStream(mMusic);

    CloseAudioDevice();
    CloseWindow();
}

void Game::input() {

}

void Game::update(float dt) {
    mMario.update(dt);
    mCamera.target = mMario.mPosition;
    Physics::update(dt);
}

void Game::draw() {
    Texture2D sky = Resource::textures["sky"];
    SetTextureWrap(sky, TEXTURE_WRAP_REPEAT);
    SetTextureFilter(sky, TEXTURE_FILTER_POINT);
    float parallax = 1.0f;                
    Rectangle src = {                      
        fmodf(mCamera.target.x * parallax, sky.width),
        0,
        sky.width,    
        sky.height   
    };        

    Rectangle dst = {
        0,
        0,
        (float)GetScreenWidth(),
        (float)GetScreenHeight()
    }; 
    
    DrawTexturePro(sky, src, dst, {0, 0}, 0.0f, WHITE);

    BeginMode2D(mCamera);
        mMap.draw();
        mMario.draw();
        Physics::debugDraw();
    EndMode2D();
}