#ifndef RENDER_HPP
#define RENDER_HPP
#include <SDL3/SDL.h>
#include "ps_math.hpp"
#include "ps.hpp"
#include <vector>
#include <utility>

#include "camera.hpp"
namespace ps
{
    namespace RenderConstant
    {
        constexpr real PointSize = 1.0f;
        constexpr int BorderSize = 1;
        constexpr int FillAlpha = 40;
        constexpr int BasicCirclePointCount = 60;
        const SDL_Color White = {255, 255, 255, 255};
        const SDL_Color Yellow = {255, 235, 60, 255};
        const SDL_Color Red = {246, 65, 55, 255};
        const SDL_Color Blue = {55, 136, 205, 255};
        const SDL_Color LightBlue = {5, 170, 246, 255};
        const SDL_Color Cyan = {80, 185, 210, 255};
        const SDL_Color LightCyan = {0, 190, 210, 255};
        const SDL_Color Green = {0, 255, 0, 255};
        const SDL_Color Pink = {255, 192, 203, 255};
        const SDL_Color DarkGreen = {0, 100, 0, 255};
        const SDL_Color Gray = {190, 190, 190, 255};
        const SDL_Color Orange = {255, 105, 55, 255};
        const SDL_Color Teal = {30, 230, 180, 255};
        const SDL_Color DarkGray = {50, 50, 50, 255};
        static real ScaleFactor = 1.0f;

    }
    class RenderSDLImpl
    {
    public:
        static SDL_FPoint toSDLFPoint(const Vector2 &vector);
        static void renderPixle(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, const Vector2 &point,
                                const SDL_Color &color);
        static void renderLine(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, const Vector2 &p1,
                               const Vector2 &p2, const SDL_Color &color);
        static void renderPixles(SDL_Window *window, SDL_Renderer *renderer, Camera &camera,
                                 const std::vector<Vector2> &points, const SDL_Color &color);
        static void renderLines(SDL_Window *window, SDL_Renderer *renderer, Camera &camera,
                                const std::vector<Vector2> &lines, const SDL_Color &color);
        static void renderPolygon(SDL_Window *window, SDL_Renderer *renderer, Camera &camera,
                                  const ShapePrimitive &shape, const SDL_Color &color);
        static void renderCircle(SDL_Window *window, SDL_Renderer *renderer, Camera &camera,
                                 const ShapePrimitive &shape, const SDL_Color &color);
        static void renderPoint(SDL_Window *window, SDL_Renderer *renderer, Camera &camera,
                                const Vector2 &point, const SDL_Color &color, real pointSize = RenderConstant::PointSize);
        static void renderPoints(SDL_Window *window, SDL_Renderer *renderer, Camera &camera,
                                 const std::vector<Vector2> &points, const SDL_Color &color);
        static void renderEdge(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, const ShapePrimitive &shape,
                               const SDL_Color &color);
        static void renderShape(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, const ShapePrimitive &shape,
                                const SDL_Color &color);
        static void renderJoint(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, Joint *joint,
                                const SDL_Color &color);
        static void renderDistanceJoint(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, Joint *joint,
                                        const SDL_Color &color);
        static void renderPointJoint(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, Joint *joint,
                                     const SDL_Color &color);
        static void renderRect(SDL_Window *window, SDL_Renderer *renderer, Camera &camera,
                               float x, float y, float w, float h, const SDL_Color &color);
        static void renderRevoluteJoint(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, Joint *joint,
                                        const SDL_Color &color);
        static void renderAABB(SDL_Window *window, SDL_Renderer *renderer, Camera &camera,
                               const AABB &aabb, const SDL_Color &color);
        static void renderArrow(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, const Vector2 &start,
                                const Vector2 &end, const SDL_Color &color, float arrowHeadLength = 10.0f, float arrowHeadAngle = 25.0f);
    };
}
#endif