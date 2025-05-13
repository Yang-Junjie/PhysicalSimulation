#include "render.hpp"
#include <iostream>
SDL_FPoint ps::RenderSDLImpl::toVector2f(const Vector2 &vector)
{
     return SDL_FPoint({vector.x_, vector.y_});
}

void ps::RenderSDLImpl::renderPoint(SDL_Window *window, SDL_Renderer *renderer, const Vector2 &point, const SDL_FColor &color, real pointSize)
{
     SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
     SDL_RenderPoint(renderer, point.x_, point.y_);
}

void ps::RenderSDLImpl::renderLine(SDL_Window *window, SDL_Renderer *renderer, const Vector2 &p1, const Vector2 &p2, const SDL_FColor &color)
{
     SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
     SDL_RenderLine(renderer, p1.x_, p1.y_, p2.x_, p2.y_);
}

void ps::RenderSDLImpl::renderPoints(SDL_Window *window, SDL_Renderer *renderer, const std::vector<Vector2> &points, const SDL_FColor &color)
{
     std::vector<SDL_FPoint> vertices;
     vertices.reserve(points.size());
     for (auto &p : points)
     {
          SDL_FPoint Point;
          Point = toVector2f(p);
          vertices.emplace_back(Point);
     }
     SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
     SDL_RenderPoints(renderer, vertices.data(), vertices.size());
}

void ps::RenderSDLImpl::renderLines(SDL_Window *window, SDL_Renderer *renderer, const std::vector<Vector2> &lines, const SDL_FColor &color)
{
     std::vector<SDL_FPoint> vertices;
     vertices.reserve(lines.size() * 2);
     for (auto &elem : lines)
     {
          SDL_FPoint point;
          point = toVector2f(elem);
          vertices.emplace_back(point);
     }
     SDL_SetRenderDrawColor(renderer,  color.r, color.g, color.b, color.a);
     SDL_RenderLines(renderer, vertices.data(), vertices.size());
}
