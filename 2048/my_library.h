#include <iostream>
#include <SDL.h>

using namespace std;


void logSDLError(std::ostream& os,const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, int SCREEN_WIDTH,int SCREEN_HEIGHT, string WINDOW_TITLE);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
