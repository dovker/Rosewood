#include "Collision.h"

namespace TestGame
{
    bool Collision::RectVsRect(Rosewood::Rect a, Rosewood::Rect b)
    {
        return
        a.Left < b.Right &&
        a.Right > b.Left &&
        a.Bottom > b.Top &&
        a.Top < b.Bottom;
    }
    bool Collision::DynamicRectVsRect(Rosewood::Rect a, Rosewood::Rect b, glm::vec2 velocity, float deltaTime, glm::vec2& contactPoint, glm::vec2& contactNormal, float& contactTime)
    {
        // Check if dynamic rectangle is actually moving - we assume rectangles are NOT in collision to start
		if (velocity.x == 0 && velocity.y == 0)
			return false;

		// Expand target rectangle by source dimensions
		Rosewood::Rect expanded_target = Rosewood::Rect(b.Position()-a.RelativeWidth(), b.RelativeWidth() + a.RelativeWidth());
		

        
		if (Ray2DVsRect(Rosewood::Ray2D(a.Position(), velocity * deltaTime), expanded_target, contactPoint, contactNormal, contactTime))
        {
			return (contactTime >= 0.0f && contactTime < 1.0f);
        }
		else
        {
			return false;
        }
    }

    bool Collision::Ray2DVsRect(Rosewood::Ray2D ray, Rosewood::Rect rect, glm::vec2& contactPoint, glm::vec2& contactNormal, float& hit_t)
    {
        contactNormal = { 0,0 };
		contactPoint = { 0,0 };

		// Cache division
		glm::vec2 invdir = 1.0f/ray.Direction;

		// Calculate intersections with rectangle bounding axes
		glm::vec2 t_near = (rect.Position() - ray.Position) * invdir;
		glm::vec2 t_far = (rect.PositionWidth() - ray.Position) * invdir;

		if (std::isnan(t_far.y) || std::isnan(t_far.x)) return false;
		if (std::isnan(t_near.y) || std::isnan(t_near.x)) return false;

		// Sort distances
		if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
		if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

		// Early rejection		
		if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

		// Closest 'time' will be the first contact
		hit_t = glm::max(t_near.x, t_near.y);

		// Furthest 'time' is contact on opposite side of target
		float t_hit_far = glm::min(t_far.x, t_far.y);

			// Reject if ray direction is pointing away from object
		if (t_hit_far < 0)
			return false;

		// Contact point of collision from parametric line equation
		contactPoint = ray.Position + hit_t * ray.Direction;

		if (t_near.x > t_near.y)
        {
			if (invdir.x < 0)
            {
				contactNormal = { 1, 0 };
            }
			else
            {
				contactNormal = { -1, 0 };
            }
        }
		else if (t_near.x < t_near.y)
        {
			if (invdir.y < 0)
            {
				contactNormal = { 0, 1 };
            }
            else
            {
				contactNormal = { 0, -1 };
            }
        }
		// Note if t_near == t_far, collision is principly in a diagonal
		// so pointless to resolve. By returning a CN={0,0} even though its
		// considered a hit, the resolver wont change anything.
		return true;
    }
}
