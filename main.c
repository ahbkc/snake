#include <stdio.h>
#include <SDL2/SDL.h>
#include <unistd.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

/*
 * 贪吃蛇游戏
 * 需准备：
 *      背景图
 *      蛇图片
 *      食物
 *
 *      蛇会一直动,每当吃到食物就会变长
 *      食物当被吃掉时,会一直变换位置显示
 *      蛇不能碰到墒
 */

int main() {
    // 初始化
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        const char *msg = SDL_GetError();
        printf("Initialization failed, error message: %s\n", msg);
        SDL_Quit();
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
        SDL_Quit();
        exit(-1);
    }

    SDL_SetWindowResizable(window, SDL_TRUE);

    // 声明渲染器指针
    SDL_Renderer *renderer = NULL;
    // 创建SDL渲染器
    renderer = SDL_CreateRenderer(window, -1, 0);

    // 创建渲染器失败
    if (renderer == NULL) {
        const char *msg = SDL_GetError();
        printf("Failed to create renderer, error message: %s\n", msg);
        SDL_Quit();
        exit(-1);
    }

    // 设置背景色
    SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
    // 清空渲染器
    SDL_RenderClear(renderer);

    // 设置画笔颜色
    SDL_SetRenderDrawColor(renderer, 204, 0, 0, 255);
    // 绘制一个线段
    int res = SDL_RenderDrawLine(renderer, 50, 50, 300, 300);
    if (res < 0) {
        printf("%s\n", " 绘制线段失败!");
        SDL_Quit();
        exit(-1);
    }
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            SDL_Quit();
            printf("%s\n", "退出");
        }
    }

    SDL_Quit();
    return 0;
}