#include "CollisionHandler.h"

CollisionHandler* CollisionHandler::s_Instance = nullptr;

bool CollisionHandler::CheckBoxCollision( SDL_Rect a, SDL_Rect b ) const
{
    bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
	bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);

	return (x_overlaps && y_overlaps);
}

bool CollisionHandler::CheckBoundary( const Vector2D& pos ) const
{
	int width = Texture::Instance()->GetWidth( "airship" );
	int height = Texture::Instance()->GetHeight( "airship" );
	bool x_boundary = ( pos.x > SCREEEN_WIDTH - width + 20 ) || ( pos.x < -20 );
	bool y_boundary = ( pos.y > SCREEEN_HEIGHT - height ) || ( pos.y < 0 );

	return ( x_boundary || y_boundary );
}
