#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

// Global variables - screen height and width
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Key press surface constants
enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

// Starts SDL & creates window
bool init();

// Loads media (image in this case)
bool loadMedia();

// Frees media & closes window
void close();

// Loads individual image
SDL_Surface* loadSurface(std::string path);

// WINDOW we will render to
SDL_Window* gWindow = NULL;

// SURFACE contained in window
SDL_Surface* gScreenSurface = NULL;

// The images that will correspond to a keypress
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

// Current displayed image
SDL_Surface* gCurrentState = NULL;

bool init() {
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        // Create Window
        gWindow = SDL_CreateWindow(
                "Hello Bitches Tutorial",
                800,
                800,
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN
                );

        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            /**
            // Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags)) {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            } else {
             **/
                // get window surface
                gScreenSurface = SDL_GetWindowSurface(gWindow);
            /** } **/
        }
    }
    return success;
}

bool loadMedia() {
    // Load a success flag
    bool success = true;

    // Load default image
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("../assets/press.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
        printf("Failed to load default image!\n");
        success = false;
    }

    // Load 'up' surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("../assets/up.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
        printf("Failed to load up image!\n");
        success = false;
    }

    // 'Down' surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("../assets/down.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
        printf("Failed to load down image!\n");
        success = false;
    }

    // 'Left' surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("../assets/left.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
        printf("Failed to load left image!\n");
        success = false;
    }

    // 'Right' surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("../assets/right.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
        printf("Failed to load right image!\n");
        success = false;
    }
    return success;
}

// loadSurface function goes here TODO
SDL_Surface* loadSurface(std::string path) {

    /**
    // The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        // Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
        if (optimizedSurface == NULL) {
            printf("Unable to optimize image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
        }
        // Get rid of loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;

     **/

    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    return loadedSurface;
}

void close() {
    //Deallocate surfaces
    for(int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i) {
        SDL_FreeSurface(gKeyPressSurfaces[i]);
        gKeyPressSurfaces[ i ] = NULL;
    }

    // Destoy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char* args[]) {
    // Starts up SDL and creates window
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            // Main loop flag
            bool quit = false;

            SDL_Event e;

            gCurrentState = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

            while (!quit) {
                while(SDL_PollEvent(&e) != 0) {
                    // User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                    //  User presses a key
                    else if (e.type == SDL_KEYDOWN) {
                        // Select surface based on key
                        switch (e.key.keysym.sym) {
                            case SDLK_UP:
                                gCurrentState = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                                break;
                            case SDLK_DOWN:
                                gCurrentState = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                                break;
                            case SDLK_LEFT:
                                gCurrentState = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                                break;
                            case SDLK_RIGHT:
                                gCurrentState = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                                break;
                        }
                    }
                }
                // Apply the image :D
                SDL_BlitSurface(gCurrentState, NULL, gScreenSurface, NULL);

                // Update the surface
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    close();

    return 0;
}
