#ifndef RENDER_HPP
#define RENDER_HPP
#include <SDL3/SDL.h>
#include "ps_math.hpp"
#include "ps.hpp"
#include <vector>
#include <utility>
namespace ps
{
    namespace RenderConstant
    {
        constexpr real PointSize = 1.0f;
        constexpr int BorderSize = 1;
        constexpr int FillAlpha = 38;
        constexpr int BasicCirclePointCount = 60;
        constexpr real BasicDashLength = 0.04f;
        constexpr real BasicDashGap = 0.04f;
        const SDL_Color Yellow = {255, 235, 59, 255};
        const SDL_Color Red = {244, 67, 54, 255};
        const SDL_Color Blue = {55, 133, 205, 255};
        const SDL_Color LightBlue = {3, 169, 244, 255};
        const SDL_Color Cyan = {78, 184, 210, 255};
        const SDL_Color LightCyan = {0, 188, 212, 255};
        const SDL_Color Green = {15, 250, 14, 255};
        const SDL_Color Pink = {233, 30, 99, 255};
        const SDL_Color DarkGreen = {44, 113, 48, 255};
        const SDL_Color Gray = {189, 189, 189, 255};
        const SDL_Color Orange = {255, 138, 101, 255};
        const SDL_Color Teal = {29, 233, 182, 255};
        const SDL_Color DarkGray = {50, 50, 50, 255};
        static real ScaleFactor = 1.0f;

    }
    class RenderSDLImpl
    {
    public:
        static SDL_FPoint toVector2f(const Vector2 &vector);
        static void renderPixle(SDL_Window *window, SDL_Renderer *renderer, const Vector2 &point,
                                const SDL_Color &color);
        static void renderLine(SDL_Window *window, SDL_Renderer *renderer, const Vector2 &p1,
                               const Vector2 &p2, const SDL_Color &color);
        static void renderPixles(SDL_Window *window, SDL_Renderer *renderer,
                                 const std::vector<Vector2> &points, const SDL_Color &color);
        static void renderLines(SDL_Window *window, SDL_Renderer *renderer,
                                const std::vector<Vector2> &lines, const SDL_Color &color);
        static void renderPolygon(SDL_Window *window, SDL_Renderer *renderer,
                                  const ShapePrimitive &shape, const SDL_Color &color);
        static void renderCircle(SDL_Window *window, SDL_Renderer *renderer,
                                 const ShapePrimitive &shape, const SDL_Color &color);
        static void renderPoint(SDL_Window *window, SDL_Renderer *renderer,
                                const Vector2 &point, const SDL_Color &color, real pointSize = RenderConstant::PointSize);
        static void renderPoints(SDL_Window *window, SDL_Renderer *renderer,
                                 const std::vector<Vector2> &points, const SDL_Color &color);
        static void renderEdge(SDL_Window *window, SDL_Renderer *renderer, const ShapePrimitive &shape,
                               const SDL_Color &color);
        static void renderShape(SDL_Window *window, SDL_Renderer *renderer, const ShapePrimitive &shape,
                                const SDL_Color &color);
        static void renderJoint(SDL_Window *window, SDL_Renderer *renderer, Joint *joint, const SDL_Color &color);
        static void renderDistanceJoint(SDL_Window *window, SDL_Renderer *renderer, Joint *joint, const SDL_Color &color);
        static void renderPointJoint(SDL_Window *window, SDL_Renderer *renderer, Joint *joint, const SDL_Color &color);
    };
}
#endif