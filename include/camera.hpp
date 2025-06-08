#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SDL3/SDL.h>

#include "ps.hpp"

namespace ps
{
	class Camera
	{
	public:
		enum class EasingType
		{
			Lerp,
			Exponential,
			Uniform
		};

		/**
		 * @struct Viewport
		 * @brief Represents a rectangular area in 2D space, typically used for camera or rendering viewports.
		 *
		 * The Viewport structure defines a rectangle using its top-left and bottom-right coordinates.
		 * It provides utility functions to get and set its dimensions and center.
		 *
		 * Members:
		 * - topLeft: The top-left corner of the viewport (default: {0, 0}).
		 * - bottomRight: The bottom-right corner of the viewport (default: {800, 600}).
		 *
		 * Constructors:
		 * - Viewport(): Default constructor.
		 * - Viewport(const Vector2& top_left, const Vector2& bottom_right): Constructs a viewport with specified corners.
		 *
		 * Member Functions:
		 * - real width(): Returns the width of the viewport.
		 * - real height(): Returns the height of the viewport.
		 * - Vector2 center() const: Returns the center point of the viewport.
		 * - void setWidth(const real& width): Sets the width of the viewport, adjusting the bottomRight.x accordingly.
		 * - void setHeight(const real& height): Sets the height of the viewport, adjusting the bottomRight.y accordingly.
		 * - void set(const real& width, const real& height): Sets both width and height of the viewport.
		 */
		struct Viewport
		{
			Viewport() = default;

			Viewport(const Vector2 &top_left, const Vector2 &bottom_right) : topLeft(top_left),
																			 bottomRight(bottom_right)
			{
			}

			Vector2 topLeft = {0, 0};
			Vector2 bottomRight = {1080, 680};
			real width();
			real height();
			Vector2 center() const;
			void setWidth(const real &width);
			void setHeight(const real &height);
			void set(const real &width, const real &height);
		};

		Camera();
		void render(SDL_Window *window, SDL_Renderer *renderer);
		bool &bodyVisible();
		bool &jointVisible();
		bool &aabbVisible();
		bool &velocityVisible();
		bool &visible();


		real meterToPixel() const;
		void setTargetMeterToPixel(const real &meterToPixel);
		real pixelToMeter() const;

		Vector2 transform() const;
		void setTransform(const Vector2 &transform);

		void setWorld(PhysicsWorld *world);
		PhysicsWorld *world() const;

		Viewport viewport() const;
		void setViewport(const Viewport &viewport);

		Vector2 worldToScreen(const Vector2 &pos) const;
		Vector2 screenToWorld(const Vector2 &pos) const;

		Tree *tree() const;
		void setTree(Tree *tree);

		real deltaTime() const;
		void setDeltaTime(const real &deltaTime);

		ContactMaintainer *maintainer() const;
		void setContactMaintainer(ContactMaintainer *maintainer);

		EasingType easingType() const;
		void setEasingType(EasingType type);

		UniformGrid *uniformGrid() const;
		void setUniformGrid(UniformGrid *grid);

		real defaultMeterToPixel() const;
		void setDefaultMeterToPixel(const real &number);

	private:
		bool m_visible = true;
		bool m_aabbVisible = false;
		bool m_jointVisible = true;
		bool m_bodyVisible = true;
		bool m_velocityVisible = false;

		real m_defaultMeterToPixel = 50.0f;
		real m_meterToPixel = 50.0f;
		real m_pixelToMeter = 0.02f;

		real m_targetMeterToPixel = 80.0f;
		real m_targetPixelToMeter = 0.02f;

		Vector2 m_transform;
		Vector2 m_origin;
		Viewport m_viewport;
		PhysicsWorld *m_world = nullptr;

		Tree *m_tree = nullptr;
		UniformGrid *m_grid = nullptr;
		ContactMaintainer *m_maintainer = nullptr;

		real m_restitution = 2.0f;
		real m_deltaTime = 15.0f;

		EasingType m_easingType = EasingType::Exponential;
	};
}
#endif
