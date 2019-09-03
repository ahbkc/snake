#include <stdio.h>
#include <SDL2/SDL.h>
#include <unistd.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

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

struct Custom_SDL_Render {
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Rect *src_rect;
    SDL_Rect *target_rect;
};

// 监听事件线程
int eventHandle(void *data) {
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            // 监听点击右上角叉号退出事件
            SDL_Quit();
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT:
                    printf("%s\n", "右方向");
                    break;
                case SDLK_LEFT:
                    printf("%s\n", "左方向");
                    break;
                case SDLK_UP:
                    printf("%s\n", "上方向");
                    break;
                case SDLK_DOWN:
                    printf("%s\n", "下方向");
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}

void updateWindow(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *pr, SDL_Rect *nr) {
    // 清空渲染器
    SDL_RenderClear(renderer);

    // 刷新位置
    SDL_RenderCopy(renderer, texture, pr, nr);

    // 刷新显示
    SDL_RenderPresent(renderer);
}

static int left_right_count = 0;
// 0代表左, 1代表右
static int direction = 0;
static int speed = 10;

// 定时器回调函数
Uint32 sdl_timer_callback(Uint32 interval, void *param) {
    struct Custom_SDL_Render *sdlRender = (struct Custom_SDL_Render *) param;
    SDL_Rect *src_rect = sdlRender->src_rect, *target_rect = sdlRender->target_rect;
    SDL_Renderer *renderer = sdlRender->renderer;
    SDL_Texture *texture = sdlRender->texture;
    if (left_right_count < 10 && direction == 0) {
        left_right_count++;
        target_rect->x += speed;
    } else {
        left_right_count--;
        target_rect->x -= speed;
        direction = 1;
        if (left_right_count <= 0) {
            direction = 0;
        }
    }
    updateWindow(renderer, texture, src_rect, target_rect);
    // 必须要返回一个值, 返回的值即时定时器间隔调用的值
    return interval;
}

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
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // 清空渲染器
    SDL_RenderClear(renderer);

    // 加载BMP图片
    SDL_Surface *surface = SDL_LoadBMP("/home/qinleiyin/Workspace/c/c_sdl_demo/background.bmp");
    if (surface == NULL) {
        const char *msg = SDL_GetError();
        printf("load bmp failed, error message: %s\n", msg);
        SDL_Quit();
        exit(-1);
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    // free surface
    SDL_FreeSurface(surface);

    SDL_Rect *src_rect = malloc(sizeof(SDL_Rect));
    src_rect->x = 0;
    src_rect->y = 0;
    src_rect->w = 128;
    src_rect->h = 128;

    SDL_Rect *target_rect = malloc(sizeof(SDL_Rect));
    target_rect->x = 0;
    target_rect->y = 0;
    target_rect->w = 128;
    target_rect->h = 128;

    // SDL纹理
    SDL_RenderCopy(renderer, texture, src_rect, target_rect);

    // 显示绘制结果
    SDL_RenderPresent(renderer);

    struct Custom_SDL_Render *customSdlRender = malloc(sizeof(struct Custom_SDL_Render));
    customSdlRender->renderer = renderer;
    customSdlRender->texture = texture;
    customSdlRender->src_rect = src_rect;
    customSdlRender->target_rect = target_rect;
    // 创建一个定时器
    SDL_TimerID timerId = SDL_AddTimer(1000, sdl_timer_callback, customSdlRender);
    if (timerId == 0) {
        const char *msg = SDL_GetError();
        printf("load bmp failed, error message: %s\n", msg);
        SDL_Quit();
        exit(-1);
    }

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            // 监听点击右上角叉号退出事件
            SDL_Quit();
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT:
                    target_rect->x = target_rect->x + speed;
                    printf("%s\n", "右方向");
                    break;
                case SDLK_LEFT:
                    target_rect->x = target_rect->x - speed;
                    printf("%s\n", "左方向");
                    break;
                case SDLK_UP:
                    target_rect->y = target_rect->y - speed;
                    printf("%s\n", "上方向");
                    break;
                case SDLK_DOWN:
                    target_rect->y = target_rect->y + speed;
                    printf("%s\n", "下方向");
                    break;
                default:
                    break;
            }
            updateWindow(renderer, texture, src_rect, target_rect);
        }
    }
    free(customSdlRender);
    SDL_Quit();
    return 0;
}