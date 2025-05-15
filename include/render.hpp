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
        constexpr int FillAlpha = 84;
        const SDL_Color Yellow = {255, 235, 59};
        const SDL_Color Red = {244, 67, 54};
        const SDL_Color Blue = {55, 133, 205};
        const SDL_Color LightBlue = {3, 169, 244};
        const SDL_Color Cyan = {78, 184, 210};
        const SDL_Color LightCyan = {0, 188, 212};
        const SDL_Color Green = {15, 250, 14};
        const SDL_Color Pink = {233, 30, 99};
        const SDL_Color DarkGreen = {44, 113, 48};
        const SDL_Color Gray = {189, 189, 189};
        const SDL_Color Orange = {255, 138, 101};
        const SDL_Color Teal = {29, 233, 182};
        static real ScaleFactor = 1.0f;
        
    }
    class RenderSDLImpl
    {
    public:
        static SDL_FPoint toVector2f(const Vector2 &vector);
        static void renderPoint(SDL_Window *window, SDL_Renderer *renderer, const Vector2 &point, const SDL_Color &color,
                                real pointSize = RenderConstant::PointSize);
        static void renderLine(SDL_Window *window, SDL_Renderer *renderer, const Vector2 &p1, const Vector2 &p2,
                               const SDL_Color &color);
        static void renderPoints(SDL_Window *window, SDL_Renderer *renderer, const std::vector<Vector2> &points,
                                 const SDL_Color &color);
        static void renderLines(SDL_Window *window, SDL_Renderer *renderer,
                                const std::vector<Vector2> &lines, const SDL_Color &color);
        static void renderPolygon(SDL_Window *window, SDL_Renderer *renderer,
                                  const ShapePrimitive &shape, const SDL_Color &color);
    };
}
