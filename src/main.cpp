#include "render.hpp"
#include "ps.hpp"
static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;
int main(int argc, char *argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/renderer/primitives", 640, 480, 0, &window, &renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    ps::RenderSDLImpl draw;
    ps::Vector2 p1 = ps::Vector2(0.0f, 0.0f);
    ps::Vector2 p2 = ps::Vector2(640.0f, 480.0f);

    std::vector<ps::Vector2> vertices = {ps::Vector2(16.0f, 63.0f), ps::Vector2(32.0f, 180.0f)};
    std::vector<ps::Vector2> points = {{ 100, 354 }, { 220, 230 }, { 140, 230 }, { 320, 100 }, { 500, 230 },
        { 420, 230 }, { 540, 354 }, { 400, 354 }, { 100, 354 }};
    SDL_Color color = ps::RenderConstant::Blue;
   
    ps::Polygon polygon;
    polygon.append({{0, 0}, {100, 0}, {100, 100}});
    ps::ShapePrimitive shape;
    shape.shape = &polygon;

    SDL_Event event{};
    bool keep_going = true;

    while (keep_going)
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
        case SDL_EVENT_QUIT:
        {
            keep_going = false;
            break;
        }
        }
        // draw.renderLine(window, renderer, p1, p2, color);
        //  draw.renderPoint(window,renderer,{10,23},color);
        draw.renderLines(window, renderer, points, color);
        draw.renderPolygon(window, renderer, shape, color);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    delete shape.shape;
    return 0;
}