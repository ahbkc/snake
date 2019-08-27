#include <stdio.h>
#include <SDL2/SDL.h>
#include <unistd.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

int main() {
    // 初始化
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        const char *msg = SDL_GetError();
        printf("Initialization failed, error message: %s\n", msg);
        exit(-1);
    }

    // 主窗口指针
    SDL_Window *window = NULL;
    window = SDL_CreateWindow("弹球游戏", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    // 创建窗口失败处理
    if (window == NULL) {
        const char *msg = SDL_GetError();
        printf("Failed to create window, error message: %s\n", msg);
        exit(-1);
    }

    // 声明渲染器指针
    SDL_Renderer *renderer = NULL;
    // 创建SDL渲染器
    renderer = SDL_CreateRenderer(window, -1, 0);

    // 创建渲染器失败
    if (renderer == NULL) {
        const char *msg = SDL_GetError();
        printf("Failed to create renderer, error message: %s\n", msg);
        exit(-1);
    }

    // 设置背景色
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // 清空渲染器
    SDL_RenderClear(renderer);

    const char* path = "/home/qinleiyin/Workspace/c/c_sdl_demo/background.bmp";
    SDL_Surface *surface = SDL_LoadBMP(path);
    if (surface == NULL) {
        const char *msg = SDL_GetError();
        printf("load bmp failed, error message: %s\n", msg);
        exit(-1);
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    // free surface
    SDL_FreeSurface(surface);

    SDL_Rect *src_rect = malloc(sizeof(SDL_Rect));
    src_rect->x = 0;
    src_rect->y = 0;
    src_rect->w = SCREEN_WIDTH;
    src_rect->h = SCREEN_HEIGHT;

    SDL_Rect *target_rect = malloc(sizeof(SDL_Rect));
    target_rect->x = 0;
    target_rect->y = 0;
    target_rect->w = SCREEN_WIDTH;
    target_rect->h = SCREEN_HEIGHT;

    // SDL纹理
    SDL_RenderCopy(renderer, texture, src_rect, target_rect);

    // 显示绘制结果
    SDL_RenderPresent(renderer);

    SDL_Delay(5000);

    free(src_rect);
    free(target_rect);
    // SDL退出
    SDL_Quit();
    return 0;
}