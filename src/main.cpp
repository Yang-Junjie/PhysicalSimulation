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

    if (!SDL_CreateWindowAndRenderer("PhysicalSimulation", 1080, 680, 0, &window, &renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_Color blue = ps::RenderConstant::Blue;
    SDL_Color green = ps::RenderConstant::Green;
    SDL_Color red = ps::RenderConstant::Red;
    SDL_Color DarkGray = ps::RenderConstant::DarkGray;
    
    ps::Polygon polygon;
    polygon.append({{0, 0}, {0, 100}, {100, 100}, {100, 0}});
    ps::ShapePrimitive shape;
    shape.shape = &polygon;
    shape.transform.position = {100, 100};

    ps::Circle circle;
    circle.setRadius(50);
    ps::ShapePrimitive shape2;
    shape2.shape = &circle;
    shape2.transform.position = {300, 300};

    ps::Edge edge;
    edge.set({0, 0}, {500, 0});
    ps::ShapePrimitive shape3;
    shape3.shape = &edge;
    shape3.transform.position = {100, 400};

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
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, DarkGray.r, DarkGray.g, DarkGray.b, DarkGray.a);
        SDL_RenderClear(renderer);

        ps::RenderSDLImpl::renderPolygon(window, renderer, shape, blue);
        ps::RenderSDLImpl::renderCircle(window, renderer, shape2, red);
        ps::RenderSDLImpl::renderEdge(window, renderer, shape3, green);
        
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    delete shape.shape;
    return 0;
}