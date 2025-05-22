#include "camera.hpp"

#include <iostream>

#include "render.hpp"

namespace ps
{
	Camera::Camera()
	{
	}

	void Camera::render(SDL_Window *window, SDL_Renderer *renderer)
	{
		if (m_visible)
		{
			assert(m_world != nullptr);

			real inv_dt = 1.0f / m_deltaTime;
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
			SDL_RenderClear(renderer);

			if (m_bodyVisible)
			{
				auto color = RenderConstant::Green;

				for (auto &body : m_world->bodyList())
				{
					ShapePrimitive primitive;
					primitive.shape = body->shape();
					primitive.transform.rotation = body->rotation();
					primitive.transform.position = body->position();
					if (body->sleep())
						color = RenderConstant::Gray;
					else
						color = RenderConstant::Green;
					if (body->type() == Body::BodyType::Static)
						color = RenderConstant::Teal;
					if (body->type() == Body::BodyType::Bullet)
						color = RenderConstant::Pink;
					RenderSDLImpl::renderShape(window, renderer, primitive, color);
				}
			}
			if (m_jointVisible)
			{
				for (auto iter = m_world->jointList().begin(); iter != m_world->jointList().end(); ++iter)
				{
					if ((*iter)->active())
						RenderSDLImpl::renderJoint(window, renderer, (*iter).get(), RenderConstant::Green);
				}
			}
		}
	}

	bool &Camera::bodyVisible()
	{
		return m_bodyVisible;
	}

	real Camera::meterToPixel() const
	{
		return m_meterToPixel;
	}

	void Camera::setTargetMeterToPixel(const real &meterToPixel)
	{
		if (meterToPixel < 1.0f)
		{
			m_targetMeterToPixel = 1.0f;
			m_targetPixelToMeter = 1.0f;
			return;
		}
		m_targetMeterToPixel = meterToPixel;
		m_targetPixelToMeter = 1.0f / meterToPixel;
	}

	real Camera::pixelToMeter() const
	{
		return m_pixelToMeter;
	}

	Vector2 Camera::transform() const
	{
		return m_transform;
	}

	void Camera::setTransform(const Vector2 &transform)
	{
		m_transform = transform;
	}

	void Camera::setWorld(PhysicsWorld *world)
	{
		m_world = world;
	}

	PhysicsWorld *Camera::world() const
	{
		return m_world;
	}

	Camera::Viewport Camera::viewport() const
	{
		return m_viewport;
	}

	void Camera::setViewport(const Viewport &viewport)
	{
		m_viewport = viewport;
		m_origin.set((m_viewport.topLeft.x + m_viewport.bottomRight.x) * (0.5),
					 (m_viewport.topLeft.y + m_viewport.bottomRight.y) * (0.5));
	}

	Vector2 Camera::worldToScreen(const Vector2 &pos) const
	{
		Vector2 real_origin(m_origin.x + m_transform.x, m_origin.y - m_transform.y);
		return Vector2(real_origin.x + pos.x * m_meterToPixel, real_origin.y - pos.y * m_meterToPixel);
	}

	Vector2 Camera::screenToWorld(const Vector2 &pos) const
	{
		Vector2 real_origin(m_origin.x + m_transform.x, m_origin.y - m_transform.y);
		Vector2 result = pos - real_origin;
		result.y = -result.y;
		result *= m_pixelToMeter;
		return result;
	}

	Tree *Camera::tree() const
	{
		return m_tree;
	}

	void Camera::setTree(Tree *tree)
	{
		m_tree = tree;
	}

	bool &Camera::visible()
	{
		return m_visible;
	}

	real Camera::deltaTime() const
	{
		return m_deltaTime;
	}

	void Camera::setDeltaTime(const real &deltaTime)
	{
		m_deltaTime = deltaTime;
	}

	ContactMaintainer *Camera::maintainer() const
	{
		return m_maintainer;
	}

	void Camera::setContactMaintainer(ContactMaintainer *maintainer)
	{
		m_maintainer = maintainer;
	}

	Camera::EasingType Camera::easingType() const
	{
		return m_easingType;
	}

	void Camera::setEasingType(EasingType type)
	{
		m_easingType = type;
	}

	UniformGrid *Camera::uniformGrid() const
	{
		return m_grid;
	}

	void Camera::setUniformGrid(UniformGrid *grid)
	{
		m_grid = grid;
	}

	real Camera::defaultMeterToPixel() const
	{
		return m_defaultMeterToPixel;
	}

	void Camera::setDefaultMeterToPixel(const real &number)
	{
		m_defaultMeterToPixel = number;
	}

	real Camera::Viewport::width()
	{
		return bottomRight.x - topLeft.x;
	}

	real Camera::Viewport::height()
	{
		return bottomRight.y - topLeft.y;
	}

	Vector2 Camera::Viewport::center() const
	{
		return bottomRight * 0.5f;
	}

	void Camera::Viewport::setWidth(const real &width)
	{
		bottomRight.x = topLeft.x + width;
	}

	void Camera::Viewport::setHeight(const real &height)
	{
		bottomRight.y = topLeft.y + height;
	}

	void Camera::Viewport::set(const real &width, const real &height)
	{
		setWidth(width);
		setHeight(height);
	}
}
