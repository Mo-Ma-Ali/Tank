#ifndef PRIMITIVEDRAWER_H
#define PRIMITIVEDRAWER_H

class PrimitiveDrawer {
public:
	PrimitiveDrawer();
	void DrawPoint(Point point);
	void DrawLine(Point start, Point end);

	void DrawQuad(Point v1, Point v2, Point v3, Point v4, float r, float g, float b);
		void DrawQuad4tank(Point v1, Point v2, Point v3, Point v4, float r, float g, float b,int buildingImage);
	void DrawQuadImage(Point v1, Point v2, Point v3, Point v4, float r, float g, float b,int buildingImage =0);
	void DrawQuadLand(Point v1, Point v2, Point v3, Point v4, float r, float g, float b,int buildingImage =0);
	void Draw8poly(Point v1, Point v2, Point v3, Point v4,Point v5,Point v6,Point v7,Point v8,float r,float g,float b);
	void Draw6poly(Point v1, Point v2, Point v3, Point v4,Point v5,Point v6, int textureID);
};

#endif
