#include <SDL3/SDL.h>
#include "ps_math.hpp"
#include "ps.hpp"
#include <vector>
#include <utility>
namespace ps
{
    namespace RenderConstant
    {
        constexpr real PointSize = 2.0f;
        const SDL_FColor Yellow = {255, 235, 59};
        const SDL_FColor Red = {244, 67, 54};
        const SDL_FColor Blue = {55, 133, 205};
        const SDL_FColor LightBlue = {3, 169, 244};
        const SDL_FColor Cyan = {78, 184, 210};
        const SDL_FColor LightCyan = {0, 188, 212};
        const SDL_FColor Green = {15, 250, 14};
        const SDL_FColor Pink = {233, 30, 99};
        const SDL_FColor DarkGreen = {44, 113, 48};
        const SDL_FColor Gray = {189, 189, 189};
        const SDL_FColor Orange = {255, 138, 101};
        const SDL_FColor Teal = {29, 233, 182};
    }
    class RenderSDLImpl
    {
    public:
        static SDL_FPoint toVector2f(const Vector2 &vector);
        static void renderPoint(SDL_Window *window, SDL_Renderer *renderer, const Vector2 &point, const SDL_FColor &color,
                                real pointSize = RenderConstant::PointSize);
        static void renderLine(SDL_Window *window, SDL_Renderer *renderer, const Vector2 &p1, const Vector2 &p2,
                               const SDL_FColor &color);
        static void renderPoints(SDL_Window* window, SDL_Renderer* renderer, const std::vector<Vector2> &points,
                                 const SDL_FColor &color);
        static void renderLines(SDL_Window* window, SDL_Renderer* renderer,
                                const std::vector<Vector2> &lines, const SDL_FColor &color);
        
    };
}
