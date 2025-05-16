#include "render.hpp"
#include <iostream>
SDL_FPoint ps::RenderSDLImpl::toVector2f(const Vector2 &vector)
{
     return SDL_FPoint({vector.x_, vector.y_});
}

void ps::RenderSDLImpl::renderPixle(SDL_Window *window, SDL_Renderer *renderer, const Vector2 &point, const SDL_Color &color)
{
     SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
     SDL_RenderPoint(renderer, point.x_, point.y_);
}

void ps::RenderSDLImpl::renderLine(SDL_Window *window, SDL_Renderer *renderer, const Vector2 &p1, const Vector2 &p2, const SDL_Color &color)
{
     SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
     SDL_RenderLine(renderer, p1.x_, p1.y_, p2.x_, p2.y_);
}

void ps::RenderSDLImpl::renderPixles(SDL_Window *window, SDL_Renderer *renderer, const std::vector<Vector2> &points, const SDL_Color &color)
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

void ps::RenderSDLImpl::renderLines(SDL_Window *window, SDL_Renderer *renderer, const std::vector<Vector2> &lines, const SDL_Color &color)
{
     std::vector<SDL_FPoint> vertices;
     vertices.reserve(lines.size() * 2);
     for (auto &elem : lines)
     {
          SDL_FPoint point;
          point = toVector2f(elem);
          vertices.emplace_back(point);
     }
     SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
     SDL_RenderLines(renderer, vertices.data(), vertices.size());
}

void ps::RenderSDLImpl::renderPolygon(SDL_Window *window, SDL_Renderer *renderer, const ShapePrimitive &shape, const SDL_Color &color)
{
    assert(shape.shape != nullptr);
    assert(shape.shape->type() == ShapeType::Polygon);
    auto polygon = static_cast<Polygon *>(shape.shape);
    const auto& vertices = polygon->vertices();
    const auto& indices = polygon->indices();

    if (vertices.size() < 3) return;

    std::vector<SDL_Vertex> sdlVertices;
    std::vector<Vector2> outlinePoints;
    sdlVertices.reserve(vertices.size());
    outlinePoints.reserve(vertices.size() + 1);

    SDL_FColor fillColor = {
        color.r / 255.0f,
        color.g / 255.0f,
        color.b / 255.0f,
        RenderConstant::FillAlpha / 255.0f
    };

    for (const auto& v : vertices)
    {
        Vector2 worldPos = shape.transform.translatePoint(v * RenderConstant::ScaleFactor);
        sdlVertices.emplace_back(SDL_Vertex{toVector2f(worldPos), fillColor, {0, 0}});
        outlinePoints.emplace_back(worldPos);
    }
    SDL_RenderGeometry(renderer, NULL, sdlVertices.data(), sdlVertices.size(), indices.data(), indices.size());

    if (!outlinePoints.empty())
        outlinePoints.push_back(outlinePoints.front());
    renderLines(window, renderer, outlinePoints, color);
}

void ps::RenderSDLImpl::renderCircle(SDL_Window *window, SDL_Renderer *renderer, const ShapePrimitive &shape, const SDL_Color &color)
{
     assert(shape.shape->type() == ShapeType::Circle);
     auto circle = static_cast<Circle *>(shape.shape);
     auto center = shape.transform.translatePoint(circle->center() * RenderConstant::ScaleFactor);
     auto radius = circle->radius() * RenderConstant::ScaleFactor;

     const int segments = RenderConstant::BasicCirclePointCount;
     std::vector<SDL_Vertex> vertices;
     vertices.reserve(segments + 2);
     std::vector<int> indices;
     indices.reserve(segments * 3);
     std::vector<Vector2> outlinePoints;
     outlinePoints.reserve(segments + 1);

     SDL_FColor fillColor = {
         color.r / 255.0f,
         color.g / 255.0f,
         color.b / 255.0f,
         RenderConstant::FillAlpha / 255.0f};

     vertices.emplace_back(SDL_Vertex{toVector2f(center), fillColor, {0, 0}});

     for (int i = 0; i <= segments; ++i)
     {
          float theta = float(i) / float(segments) * 2.0f * float(Constant::Pi);
          float x = center.x_ + radius * cosf(theta);
          float y = center.y_ + radius * sinf(theta);
          vertices.emplace_back(SDL_Vertex{SDL_FPoint{x, y}, fillColor, {0, 0}});
          outlinePoints.emplace_back(Vector2{x, y});
          if (i > 0)
          {
               indices.push_back(0);
               indices.push_back(i);
               indices.push_back(i + 1);
          }
     }

     SDL_RenderGeometry(renderer, NULL, vertices.data(), vertices.size(), indices.data(), indices.size());
     renderLines(window, renderer, outlinePoints, color);
}

void ps::RenderSDLImpl::renderPoint(SDL_Window *window, SDL_Renderer *renderer, const Vector2 &point, const SDL_Color &color, real pointSize)
{
     Circle circle;
     circle.setRadius(pointSize);
     ShapePrimitive shape;
     shape.shape = &circle;
     shape.transform.position = point;
     renderCircle(window, renderer, shape, color);
}

void ps::RenderSDLImpl::renderPoints(SDL_Window *window, SDL_Renderer *renderer, const std::vector<Vector2> &points, const SDL_Color &color)
{
     for (const auto &point : points)
     {
          renderPoint(window, renderer, point, color);
     }
}

void ps::RenderSDLImpl::renderEdge(SDL_Window *window, SDL_Renderer *renderer, const ShapePrimitive &shape, const SDL_Color &color)
{
     assert(shape.shape->type() == ShapeType::Edge);
     auto edge = static_cast<Edge *>(shape.shape);
     renderPoint(window, renderer, edge->startPoint() + shape.transform.position, color);
     renderPoint(window, renderer, edge->endPoint() + shape.transform.position, color);
     renderLine(window, renderer, edge->startPoint() + shape.transform.position,
                edge->endPoint() + shape.transform.position, color);

     Vector2 center = (edge->startPoint() + edge->endPoint()) / 2.0f;
     center += shape.transform.position;
     renderLine(window, renderer, center, center + 0.1f * edge->normal(), RenderConstant::Yellow);
}
