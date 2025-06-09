#include "render.hpp"
#include <iostream>
namespace ps
{
     SDL_FPoint RenderSDLImpl::toSDLFPoint(const Vector2 &vector)
     {
          return SDL_FPoint({vector.x, vector.y});
     }

     void RenderSDLImpl::renderPixle(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, const Vector2 &point, const SDL_Color &color)
     {
          Vector2 screenPos = camera.worldToScreen(point);
          SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
          SDL_RenderPoint(renderer, screenPos.x, screenPos.y);
     }

     void RenderSDLImpl::renderLine(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, const Vector2 &p1, const Vector2 &p2, const SDL_Color &color)
     {
          Vector2 sp1 = camera.worldToScreen(p1);
          Vector2 sp2 = camera.worldToScreen(p2);
          SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
          SDL_RenderLine(renderer, sp1.x, sp1.y, sp2.x, sp2.y);
     }

     void RenderSDLImpl::renderPixles(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, const std::vector<Vector2> &points, const SDL_Color &color)
     {
          std::vector<SDL_FPoint> vertices;
          vertices.reserve(points.size());
          for (auto &p : points)
          {
               Vector2 screenPos = camera.worldToScreen(p);
               SDL_FPoint Point = toSDLFPoint(screenPos);
               vertices.emplace_back(Point);
          }
          SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
          SDL_RenderPoints(renderer, vertices.data(), vertices.size());
     }

     void RenderSDLImpl::renderLines(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, const std::vector<Vector2> &lines, const SDL_Color &color)
     {
          std::vector<SDL_FPoint> vertices;
          vertices.reserve(lines.size() * 2);
          for (auto &elem : lines)
          {
               Vector2 screenPos = camera.worldToScreen(elem);
               SDL_FPoint point = toSDLFPoint(screenPos);
               vertices.emplace_back(point);
          }
          SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
          SDL_RenderLines(renderer, vertices.data(), vertices.size());
     }

     void RenderSDLImpl::renderPolygon(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, const ShapePrimitive &shape, const SDL_Color &color)
     {
          assert(shape.shape != nullptr);
          assert(shape.shape->type() == Shape::Type::Polygon);
          auto polygon = static_cast<Polygon *>(shape.shape);
          const auto &vertices = polygon->vertices();
          const auto &indices = polygon->indices();

          if (vertices.size() < 3)
               return;

          std::vector<SDL_Vertex> sdlVertices;
          std::vector<Vector2> outlinePoints;
          sdlVertices.reserve(vertices.size());
          outlinePoints.reserve(vertices.size() + 1);

          SDL_FColor fillColor = {
              color.r / 255.0f,
              color.g / 255.0f,
              color.b / 255.0f,
              RenderConstant::FillAlpha / 255.0f};

          for (const auto &v : vertices)
          {
               Vector2 worldPos = shape.transform.translatePoint(v * RenderConstant::ScaleFactor);
               Vector2 screenPos = camera.worldToScreen(worldPos);
               sdlVertices.emplace_back(SDL_Vertex{toSDLFPoint(screenPos), fillColor, {0, 0}});
               outlinePoints.emplace_back(worldPos);
          }
          auto sate = SDL_RenderGeometry(renderer, NULL, sdlVertices.data(), sdlVertices.size(), indices.data(), indices.size());
          // std::cerr << "sate:" << sate << std::endl;
          if (!outlinePoints.empty())
               outlinePoints.push_back(outlinePoints.front());
          renderLines(window, renderer, camera, outlinePoints, color);
     }

     void RenderSDLImpl::renderCircle(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, const ShapePrimitive &shape, const SDL_Color &color)
     {
          assert(shape.shape->type() == Shape::Type::Circle);
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

          Vector2 screenCenter = camera.worldToScreen(center);
          vertices.emplace_back(SDL_Vertex{toSDLFPoint(screenCenter), fillColor, {0, 0}});

          for (int i = 0; i <= segments; ++i)
          {
               float theta = float(i) / float(segments) * 2.0f * float(Constant::Pi);
               float x = center.x + radius * cosf(theta);
               float y = center.y + radius * sinf(theta);
               Vector2 worldPos{x, y};
               Vector2 screenPos = camera.worldToScreen(worldPos); // 变换圆周点
               vertices.emplace_back(SDL_Vertex{toSDLFPoint(screenPos), fillColor, {0, 0}});
               outlinePoints.emplace_back(Vector2{x, y});
               if (i > 0)
               {
                    indices.push_back(0);
                    indices.push_back(i);
                    indices.push_back(i + 1);
               }
          }

          SDL_RenderGeometry(renderer, NULL, vertices.data(), vertices.size(), indices.data(), indices.size());
          renderLines(window, renderer, camera, outlinePoints, color);
     }

     void RenderSDLImpl::renderPoint(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, const Vector2 &point, const SDL_Color &color, real pointSize)
     {
          Circle circle;
          circle.setRadius(pointSize);
          ShapePrimitive shape;
          shape.shape = &circle;
          shape.transform.position = point;
          renderCircle(window, renderer, camera, shape, color);
     }

     void RenderSDLImpl::renderPoints(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, const std::vector<Vector2> &points, const SDL_Color &color)
     {
          for (const auto &point : points)
          {
               renderPoint(window, renderer, camera, point, color);
          }
     }

     void RenderSDLImpl::renderEdge(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, const ShapePrimitive &shape, const SDL_Color &color)
     {
          assert(shape.shape->type() == Shape::Type::Edge);
          auto edge = static_cast<Edge *>(shape.shape);
          renderPoint(window, renderer, camera, edge->startPoint() + shape.transform.position, color);
          renderPoint(window, renderer, camera, edge->endPoint() + shape.transform.position, color);
          renderLine(window, renderer, camera, edge->startPoint() + shape.transform.position,
                     edge->endPoint() + shape.transform.position, color);

          Vector2 center = (edge->startPoint() + edge->endPoint()) / 2.0f;
          center += shape.transform.position;
          renderLine(window, renderer, camera, center, center + 0.1f * edge->normal(), RenderConstant::Yellow);
     }

     void RenderSDLImpl::renderShape(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, const ShapePrimitive &shape, const SDL_Color &color)
     {
          if (!shape.shape)
               return;
          switch (shape.shape->type())
          {
          case Shape::Type::Polygon:
          {
               renderPolygon(window, renderer, camera, shape, color);
               break;
          }
          case Shape::Type::Circle:
          {
               renderCircle(window, renderer, camera, shape, color);
               break;
          }
          case Shape::Type::Edge:
          {
               renderEdge(window, renderer, camera, shape, color);
               break;
          }
          default:
               break;
          }
     }
     void RenderSDLImpl::renderJoint(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, Joint *joint, const SDL_Color &color)
     {
          switch (joint->type())
          {
          case JointType::Distance:
          {
               renderDistanceJoint(window, renderer, camera, joint, color);
               break;
          }
          case JointType::Point:
          {
               renderPointJoint(window, renderer, camera, joint, color);
               break;
          }
          default:
               break;
          }
     }
     void RenderSDLImpl::renderDistanceJoint(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, Joint *joint, const SDL_Color &color)
     {
          assert(joint != nullptr);
          auto distanceJoint = static_cast<DistanceJoint *>(joint);
          Vector2 pa = distanceJoint->primitive().bodyA->toWorldPoint(distanceJoint->primitive().localPointA);
          Vector2 pb = distanceJoint->primitive().bodyB->toWorldPoint(distanceJoint->primitive().localPointB);
          Vector2 n = (pa - pb).normal();
          Vector2 mid = pb + n * (pa - pb).length() * 0.5f;

          Vector2 maxPoint1 = mid + 0.5f * n * distanceJoint->primitive().maxDistance;
          Vector2 maxPoint2 = mid - 0.5f * n * distanceJoint->primitive().maxDistance;
          Vector2 minPoint1 = mid + 0.5f * n * distanceJoint->primitive().minDistance;
          Vector2 minPoint2 = mid - 0.5f * n * distanceJoint->primitive().minDistance;

          SDL_Color minColor = RenderConstant::Blue;
          SDL_Color maxColor = RenderConstant::Red;
          minColor.a = 204;
          maxColor.a = 204;
          renderPoint(window, renderer, camera, pa, RenderConstant::Gray);
          renderPoint(window, renderer, camera, pb, RenderConstant::Gray);
          renderPoint(window, renderer, camera, minPoint1, minColor);
          renderPoint(window, renderer, camera, maxPoint1, maxColor);
          renderPoint(window, renderer, camera, minPoint2, minColor);
          renderPoint(window, renderer, camera, maxPoint2, maxColor);
          SDL_Color lineColor = RenderConstant::DarkGreen;
          lineColor.a = 150;
          renderLine(window, renderer, camera, pa, pb, lineColor);
     }
     void RenderSDLImpl::renderPointJoint(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, Joint *joint, const SDL_Color &color)
     {
          assert(joint != nullptr);
          auto pointJoint = static_cast<PointJoint *>(joint);
          Vector2 pa = pointJoint->primitive().bodyA->toWorldPoint(pointJoint->primitive().localPointA);
          Vector2 pb = pointJoint->primitive().targetPoint;

          SDL_Color point = RenderConstant::Orange;
          SDL_Color green = RenderConstant::Green;
          point.a = 204;
          green.a = 78;

          renderPoint(window, renderer, camera, pa, point, 2);
          renderPoint(window, renderer, camera, pb, point, 2);
          renderLine(window, renderer, camera, pa, pb, green);
     }
     void RenderSDLImpl::renderRect(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, float x, float y, float w, float h, const SDL_Color &color)
     {
          Vector2 screenCenter = camera.worldToScreen({x, y});
          SDL_FRect rect = {screenCenter.x, screenCenter.y, w, h};
          SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
          SDL_RenderRect(renderer, &rect);
     }
     void RenderSDLImpl::renderAABB(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, const AABB &aabb, const SDL_Color &color)
     {
          Vector2 screenCenter = camera.worldToScreen({aabb.bottomLeft().x, aabb.bottomLeft().y});
          SDL_FRect rect = {screenCenter.x, screenCenter.y, aabb.width, aabb.height};
          SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
          SDL_RenderRect(renderer, &rect);
     }
     void RenderSDLImpl::renderArrow(SDL_Window *window, SDL_Renderer *renderer, Camera &camera, const Vector2 &start, const Vector2 &end, const SDL_Color &color, float arrowHeadLength, float arrowHeadAngle)
     {
          renderLine(window, renderer, camera, start, end, color);
          float angle = atan2f(end.y - start.y, end.x - start.x);
          float rad = arrowHeadAngle * 3.14159265f / 180.0f;

          Vector2 dir1{
              end.x - arrowHeadLength * cosf(angle - rad),
              end.y - arrowHeadLength * sinf(angle - rad)};
          Vector2 dir2{
              end.x - arrowHeadLength * cosf(angle + rad),
              end.y - arrowHeadLength * sinf(angle + rad)};

          renderLine(window, renderer, camera, end, dir1, color);
          renderLine(window, renderer, camera, end, dir2, color);
     }
}