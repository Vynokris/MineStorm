#pragma once
#ifndef MY_MATH_H
#define MY_MATH_H

#include <assert.h>
#include <raylib.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

// ---------- DEFINES ---------- //

static bool __debug_shapes = false;
static bool __debug_bounding_boxes = false;
static bool __debug_axes = false;
static bool __debug_projections = false;
static bool __debug_failed_projections = false;
static bool __debug_points = false;

// ---------- STRUCTURES ---------- //

// Vector structure that holds values for x and y.
typedef struct MyVector2
{
    double x, y;
} MyVector2;

// Sgment structure that holds values for the starting point and the end point.
typedef struct Segment
{
    MyVector2 a, b;
} Segment;

// Triangle structure that holds values for 3 points.
typedef struct Triangle
{
    MyVector2 a, b, c;
} Triangle;

// Rectangle structure that holds values for the origin point, width and height.
typedef struct MyRectangle
{
    MyVector2 origin;
    double width, height;
} MyRectangle;

// Polygon structure that holds values for the origin point, the radius and the number of sides.
typedef struct Polygon
{
    MyVector2 origin;
    double radius;
    double rotation;
    int sides;
} Polygon;

// Circle structure that holds values for the origin point and radius.
typedef struct Circle
{
    MyVector2 origin;
    double radius;
} Circle;

// Union that can contain any shape.
typedef union Shape
{
    MyVector2 vector;
    Segment segment;
    Triangle triangle;
    MyRectangle rectangle;
    Polygon polygon;
    Circle circle;
} Shape;

// Shape types enum.
typedef enum ShapeTypes
{
    VECTOR2,
    SEGMENT,
    TRIANGLE,
    RECTANGLE,
    POLYGON,
    CIRCLE,
} ShapeTypes;

// ---------- CONVERSIONS --------- //

// Converts a my_math 2D vector to a raylib 2D vector.
static inline Vector2 toRayVec(MyVector2 v)
{
    return (Vector2){v.x, v.y};
}

// Converts a my_math rectangle to a raylib rectangle.
static inline Rectangle toRayRec(MyRectangle r)
{
    return (Rectangle){r.origin.x, r.origin.y, r.width, r.height};
}

// ---------- MATH FUNCTIONS ---------- //

// Rounds the given value to the nearest int.
static inline int roundInt(double val)
{
    return (int)round(val);
}

// Rounds down the given value.
static inline int floorInt(double val)
{
    return (int)floor(val);
}

// Rounds up the given value.
static inline int ceilInt(double val)
{
    return (int)ceil(val);
}

// Returns the sqare power of the given value.
static inline double sqpow(double val)
{
    return val * val;
}

// Returns 1 if the given value is positive or null, and -1 if it is negative.
static inline int signOf(double val)
{
    if (val == 0)
        return 1;
    return val / abs((int)val);
}

// Converts the given angle from degrees to radians.
static inline double degToRad(double deg)
{
    return deg * (PI / 180.0f);
}

// Converts the given angle from radians to degrees.
static inline double radToDeg(double rad)
{
    return rad * (180.0f / PI);
}

// Clamps the given value to be superior or equal to the minimum value and inferior or equal to the maximum value.
static inline double clamp(double val, double min, double max)
{
    assert(min <= max);

    if (val < min)
    {
        val = min;
    }
    if (val > max)
    {
        val = max;
    }

    return val;
}

// Clamps the given value to be inferior or equal to the maximum value.
static inline double clampUnder(double val, double max)
{
    if (val > max)
    {
        val = max;
    }

    return val;
}

// Clamps the given value to be superior or equal to the minimum value.
static inline double clampAbove(double val, double min)
{
    if (val < min)
    {
        val = min;
    }

    return val;
}

// Remaps the given value from one range to another.
static inline double remap(double val, double inputStart, double inputEnd, double outputStart, double outputEnd)
{
    // Source: https://stackoverflow.com/a/3451607/13858872
    // Find how far you are into the first range, scale that distance by the ratio of sizes of the ranges, and that's how far you should be into the second range.
    return outputStart + (val - inputStart) * (outputEnd - outputStart) / (inputEnd - inputStart);
}

// ---------- OBJECT CREATION ---------- //

// Creates a 2D vector from two values.
static inline MyVector2 Vector2Create(double x, double y)
{
    return (MyVector2){x, y};
}

// Creates a 2D vector from one point to another.
static inline MyVector2 Vector2FromPoints(MyVector2 p1, MyVector2 p2)
{
    return Vector2Create(p2.x - p1.x, p2.y - p1.y);
}

// Creates a 2D vector given an angle and a length.
static inline MyVector2 Vector2FromAngle(double rad, double length)
{
    return Vector2Create(cos(rad) * length, sin(rad) * length);
}

// Creates a 2D vector from a segement.
static inline MyVector2 Vector2FromSegment(Segment s)
{
    return Vector2FromPoints(s.a, s.b);
}

// Creates a segment from one point to another.
static inline Segment SegmentCreate(MyVector2 a, MyVector2 b)
{
    return (Segment){a, b};
}

// Creates a segment given an origin point and a vector.
static inline Segment SegmentFromVector2(MyVector2 origin, MyVector2 v)
{
    return SegmentCreate(origin, Vector2Create(origin.x + v.x, origin.y + v.y));
}

// Creates a triangle given three points.
static inline Triangle TriangleCreate(MyVector2 a, MyVector2 b, MyVector2 c)
{
    return (Triangle){a, b, c};
}

// Creates a rectangle given an origin point, a width and a height.
static inline MyRectangle RectangleCreate(MyVector2 origin, double width, double height)
{
    return (MyRectangle){origin, width, height};
}

// Create a polygon given an origin point, a radius and a number of sides.
static inline Polygon PolygonCreate(MyVector2 origin, double radius, double rotation, int sides)
{
    return (Polygon){origin, radius, rotation, sides};
}

// Create a circle given an origin point and a radius.
static inline Circle CircleCreate(MyVector2 origin, double radius)
{
    return (Circle){origin, radius};
}

// ---------- VECTOR MATH FUNCTIONS ---------- //

// Returns a vector of coordinates { 0, 0 }.
static inline MyVector2 Vector2Zero()
{
    return Vector2Create(0, 0);
}

// Adds two vectors together.
static inline MyVector2 Vector2Add(MyVector2 v1, MyVector2 v2)
{
    return Vector2Create(v1.x + v2.x, v1.y + v2.y);
}

// Adds a value to a vector.
static inline MyVector2 Vector2AddVal(MyVector2 v, double val)
{
    return Vector2Create(v.x + val, v.y + val);
}

// Substracts a vector by another.
static inline MyVector2 Vector2Substract(MyVector2 v1, MyVector2 v2)
{
    return Vector2Create(v1.x - v2.x, v1.y - v2.y);
}

// Substracts a value from a vector.
static inline MyVector2 Vector2SubstractVal(MyVector2 v, double val)
{
    return Vector2Create(v.x - val, v.y - val);
}

// Multiplies two vectors together.
static inline MyVector2 Vector2Multiply(MyVector2 v1, MyVector2 v2)
{
    return Vector2Create(v1.x * v2.x, v1.y * v2.y);
}

// Multiplies a vector by a value.
static inline MyVector2 Vector2MultiplyVal(MyVector2 v, double val)
{
    return Vector2Create(v.x * val, v.y * val);
}

// Divides a vector by another.
static inline MyVector2 Vector2Divide(MyVector2 v1, MyVector2 v2)
{
    return Vector2Create(v1.x / v2.x, v1.y / v2.y);
}

// Divides a vector by a value.
static inline MyVector2 Vector2DivideVal(MyVector2 v, double val)
{
    return Vector2Create(v.x / val, v.y / val);
}

// Returns the length of the given vector.
static inline double Vector2Length(MyVector2 v)
{
    return sqrt(sqpow(v.x) + sqpow(v.y));
}

// Returns the middle of the given vector
static inline MyVector2 Vector2Middle(MyVector2 v)
{
    return Vector2Create(v.x / 2, v.y / 2);
}

// Normalizes the given vector so that its length is 1.
static inline MyVector2 Vector2Normalize(MyVector2 v)
{
    return Vector2Create(v.x / Vector2Length(v), v.y / Vector2Length(v));
}

// Returns the angle (in radians) of the given vector.
static inline double Vector2GetAngle(MyVector2 v)
{
    return copysign(acos(Vector2Normalize(v).x), 
                    asin(Vector2Normalize(v).y));
}

// Modifies the length of the given vector to correspond to the given value.
static inline MyVector2 Vector2SetLength(MyVector2 v, double length)
{
    return Vector2FromAngle(Vector2GetAngle(v), length);
}

// Negates both of the coordinates of the given vector.
static inline MyVector2 Vector2Negate(MyVector2 v)
{
    return Vector2Create(-v.x, -v.y);
}

// Copies the signs from the source vector to the destination vector.
static inline MyVector2 Vector2Copysign(MyVector2 dest, MyVector2 source)
{
    return Vector2Create(copysign(dest.x, source.x), copysign(dest.y, source.y));
}

// Returns the dot product of the given vectors.
static inline double Vector2DotProduct(MyVector2 v1, MyVector2 v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y);
}

// Returns the cross product of the given vectors.
static inline double Vector2CrossProduct(MyVector2 v1, MyVector2 v2)
{
    return (v1.x * v2.y) - (v1.y * v2.x);
}

// Returns the normal of a given vector.
static inline MyVector2 Vector2Normal(MyVector2 vector)
{
    return Vector2Create(-vector.y, vector.x);
}

// Returns the angle (in radians) between two vectors.
static inline double Vector2Angle(MyVector2 v1, MyVector2 v2)
{
    // TODO: test this.
    double v1_angle = Vector2GetAngle(v1);
    double v2_angle = Vector2GetAngle(v2);
    return (v1_angle >= v2_angle ? (v1_angle - v2_angle) : (v2_angle - v1_angle));
}

// Rotates the given vector by the given angle.
static inline MyVector2 Vector2Rotate(MyVector2 v, double angle)
{
    double v_length = Vector2Length(v);
    double v_angle = Vector2GetAngle(v);
    return Vector2FromAngle(v_angle + angle, v_length);
}

// ---------- MISC. FUNCTIONS ----------- //

// Returns the distance between two points.
static inline double distancePoints(MyVector2 p1, MyVector2 p2)
{
    return Vector2Length(Vector2FromPoints(p1, p2));
}

// Returns the gravity center of a triangle
/*
static inline MyVector2 getTriangleGravityCenter(Triangle t)
{
    return Vector2Create((t.a.x + t.b.x + t.c.x) / 3, (t.a.y + t.b.y + t.c.y) / 3);
}
*/

// ---------- CENTER OF MASS ---------- //

// Returns the center of mass of a given segment.
static inline MyVector2 SegmentCenterOfMass(Segment segment)
{
    return Vector2Create((segment.a.x + segment.b.x) / 2, (segment.a.y + segment.b.y) / 2);
}

// Returns the center of mass of a given triangle.
static inline MyVector2 TriangleCenterOfMass(Triangle triangle)
{
    return Vector2Create((triangle.a.x + triangle.b.x + triangle.c.x) / 3, (triangle.a.y + triangle.b.y + triangle.c.y) / 3);
}

// Returns the center of mass of a given rectangle.
static inline MyVector2 RectangleCenterOfMass(MyRectangle rectangle)
{
    return Vector2Create(rectangle.origin.x + rectangle.width / 2, rectangle.origin.y + rectangle.height / 2);
}

// Returns the center of mass of a given polygon.
static inline MyVector2 PolygonCenterOfMass(Polygon poly)
{
    return poly.origin;
}

// Returns the center of mass of a given circle.
static inline MyVector2 CircleCenterOfMass(Circle circle)
{
    return circle.origin;
}

// Returns the center of mass of the given shape (returns a vector of coordinates 1,000,000 if the shape type isn't supported).
static inline MyVector2 ShapeCenterOfMass(Shape shape, ShapeTypes type)
{
    switch (type)
    {
    case SEGMENT:
        return SegmentCenterOfMass(shape.segment);
    case TRIANGLE:
        return TriangleCenterOfMass(shape.triangle);
    case RECTANGLE:
        return RectangleCenterOfMass(shape.rectangle);
    case POLYGON:
        return PolygonCenterOfMass(shape.polygon);
    case CIRCLE:
        return CircleCenterOfMass(shape.circle);
    default:
        return Vector2Create(1000000, 1000000);
    }
}

// ---------- DRAWING FUNCTIONS ---------- //

static inline void DrawPoint(MyVector2 p, Color color)
{
    DrawCircle(p.x, p.y, 2, color);
}

static inline void DrawVector2(MyVector2 v, MyVector2 origin, Color color)
{
    DrawLine(origin.x, origin.y, origin.x + v.x, origin.y + v.y, color);
    DrawCircle(origin.x + v.x, origin.y + v.y, 2, color);
}

static inline void DrawSegment(Segment s, Color color)
{
    DrawLine(s.a.x, s.a.y, s.b.x, s.b.y, color);
}

static inline void DrawMyTriangle(Triangle t, Color color)
{
    DrawTriangleLines(toRayVec(t.a), toRayVec(t.b), toRayVec(t.c), color);
}

static inline void DrawMyRectangle(MyRectangle r, Color color)
{
    DrawRectangleLines(r.origin.x, r.origin.y, r.width, r.height, color);
}

static inline void DrawMyPolygon(Polygon poly, Color color)
{
    DrawPolyLines(toRayVec(poly.origin), poly.sides, poly.radius, radToDeg(poly.rotation), color);
}

static inline void DrawMyCircle(Circle c, Color color)
{
    DrawCircleLines(c.origin.x, c.origin.y, c.radius, color);
}

// Draws any shape in a raylib window.
static inline void DrawShape(Shape shape, ShapeTypes type, MyVector2 origin, Color color)
{
    switch (type)
    {
    case VECTOR2:
        DrawVector2(shape.vector, origin, color);
        break;
    case SEGMENT:
        DrawSegment(shape.segment, color);
        break;
    case TRIANGLE:
        DrawMyTriangle(shape.triangle, color);
        break;
    case RECTANGLE:
        DrawMyRectangle(shape.rectangle, color);
        break;
    case POLYGON:
        DrawMyPolygon(shape.polygon, color);
        break;
    case CIRCLE:
        DrawMyCircle(shape.circle, color);
        break;
    default:
        break;
    }
}

// ---------- SHAPE SIDES ---------- //

// Returns the number of sides of a given shape (returns 2 for rectangles).
static inline int getSidesNum(Shape shape, ShapeTypes type)
{
    switch (type)
    {
    case SEGMENT:
        return 1;
    case TRIANGLE:
        return 3;
    case RECTANGLE:
        return 2; // There are only two axes to check for collision in a rectangle.
    case POLYGON:
        return shape.polygon.sides;
    case CIRCLE:
        return 1;
    default:
        return 0;
    }
}

// Returns the side of the given tiangle that corresponds to the given index.
static inline Segment TriangleGetSide(Triangle triangle, int index)
{
    assert(0 <= index && index < 3);

    switch (index)
    {
    case 0:
        return SegmentCreate(triangle.a, triangle.b);
    case 1:
        return SegmentCreate(triangle.b, triangle.c);
    case 2:
        return SegmentCreate(triangle.c, triangle.a);
    default:
        // This should never happen thanks to the assert, but is there to shut the warning up.
        return SegmentCreate(Vector2Zero(), Vector2Zero());
    }
}

// Returns the side of the given rectangle that corresponds to the given index.
static inline Segment RectangleGetSide(MyRectangle rectangle, int index)
{
    assert(0 <= index && index < 4);

    switch (index)
    {
    case 0:
        return SegmentCreate(Vector2Create(rectangle.origin.x + rectangle.width, rectangle.origin.y),
                             rectangle.origin);
    case 1:
        return SegmentCreate(rectangle.origin,
                             Vector2Create(rectangle.origin.x, rectangle.origin.y + rectangle.height));
    case 2:
        return SegmentCreate(Vector2Create(rectangle.origin.x, rectangle.origin.y + rectangle.height),
                             Vector2Create(rectangle.origin.x + rectangle.width, rectangle.origin.y + rectangle.height));
    case 3:
        return SegmentCreate(Vector2Create(rectangle.origin.x + rectangle.width, rectangle.origin.y + rectangle.height),
                             Vector2Create(rectangle.origin.x + rectangle.width, rectangle.origin.y));
    default:
        // This should never happen thanks to the assert, but is there to shut the warning up.
        return SegmentCreate(Vector2Zero(), Vector2Zero());
    }
}

// Returns the side of the given polygon that corresponds to the given index.
static inline Segment PolygonGetSide(Polygon poly, int index)
{
    assert(0 <= index && index < poly.sides);

    double corner_angle = degToRad(360 / poly.sides);
    double angle_offset = PI / 2 + (index * corner_angle);

    MyVector2 poly_point_a = Vector2Add(Vector2FromAngle(angle_offset + poly.rotation, poly.radius), poly.origin);
    MyVector2 poly_point_b = Vector2Add(Vector2FromAngle(angle_offset + corner_angle + poly.rotation, poly.radius), poly.origin);

    return SegmentCreate(poly_point_a, poly_point_b);
}

// Returns the side of the given shape that corresponds to the given index.
// Returns a (0, 0) segment if the shape type is not supported (circle and vector).
static inline Segment ShapeGetSide(Shape shape, ShapeTypes type, int index)
{
    switch (type)
    {
    case SEGMENT:
        assert(index < 1);
        return shape.segment;
    case TRIANGLE:
        return TriangleGetSide(shape.triangle, index);
    case RECTANGLE:
        return RectangleGetSide(shape.rectangle, index);
    case POLYGON:
        return PolygonGetSide(shape.polygon, index);
    default:
        return SegmentCreate(Vector2Zero(), Vector2Zero());
    }
}

// ---------- SHAPE VERTICES ---------- //

// Returns the number of vertices of a given shape.
static inline int getVerticesNum(Shape shape, ShapeTypes type)
{
    int vertices_num;

    switch (type)
    {
    case SEGMENT:
        return 2;
    case TRIANGLE:
        return 3;
    case RECTANGLE:
        return 4;
    case POLYGON:
        return shape.polygon.sides;
    default:
        return 0;
    }

    return vertices_num;
}

// Returns the vertex of the given segment that corresponds to the given index.
static inline MyVector2 SegmentGetVertex(Segment segment, int index)
{
    assert(0 <= index && index < 2);

    switch (index)
    {
    case 0:
        return segment.a;
    case 1:
        return segment.b;
    default:
        // This should never happen thanks to the assert, but is there to shut the warning up.
        return Vector2Create(100000, 1000000);
    }
}

// Returns the vertex of the given triangle that corresponds to the given index.
static inline MyVector2 TriangleGetVertex(Triangle triangle, int index)
{
    assert(0 <= index && index < 3);

    switch (index)
    {
    case 0:
        return triangle.a;
    case 1:
        return triangle.b;
    case 2:
        return triangle.c;
    default:
        // This should never happen thanks to the assert, but is there to shut the warning up.
        return Vector2Create(1000000, 1000000);
    }
}

// Returns the vertex of the given rectangle that corresponds to the given index.
static inline MyVector2 RectangleGetVertex(MyRectangle rectangle, int index)
{
    assert(0 <= index && index < 4);

    switch (index)
    {
    case 0:
        return Vector2Create(rectangle.origin.x + rectangle.width, rectangle.origin.y);
    case 1:
        return rectangle.origin;
    case 2:
        return Vector2Create(rectangle.origin.x, rectangle.origin.y + rectangle.height);
    case 3:
        return Vector2Create(rectangle.origin.x + rectangle.width, rectangle.origin.y + rectangle.height);
    default:
        // This should never happen thanks to the assert, but is there to shut the warning up.
        return Vector2Create(1000000, 1000000);
    }
}

// Returns the vertex of the given polygon that corresponds to the given index.
static inline MyVector2 PolygonGetVertex(Polygon polygon, int index)
{
    assert(index < polygon.sides);
    return PolygonGetSide(polygon, index).a;
}

// Returns the vertex of the given shape that corresponds to the given index.
// Returns a (1000000, 1000000) segment if the shape type is not supported (circle and vector).
static inline MyVector2 ShapeGetVertex(Shape shape, ShapeTypes type, int index)
{
    switch (type)
    {
    case SEGMENT:
        return SegmentGetVertex(shape.segment, index);
    case TRIANGLE:
        return TriangleGetVertex(shape.triangle, index);
    case RECTANGLE:
        return RectangleGetVertex(shape.rectangle, index);
    case POLYGON:
        return PolygonGetVertex(shape.polygon, index);
    default:
        return Vector2Create(1000000, 1000000);
    }
}

// ---------- COLLISIONS ---------- //

// Returns the smallest rectangle that contanins the given shape.
static inline MyRectangle getBoundingBox(Shape shape, ShapeTypes type)
{
    // If the shape is a circle.
    if (type == CIRCLE)
    {
        //! Debug render.
        if (__debug_bounding_boxes)
        {
            DrawMyRectangle(RectangleCreate(Vector2SubstractVal(shape.circle.origin, shape.circle.radius), shape.circle.radius * 2, shape.circle.radius * 2), GRAY);
        }

        return RectangleCreate(Vector2SubstractVal(shape.circle.origin, shape.circle.radius), shape.circle.radius * 2, shape.circle.radius * 2);
    }

    // Get the shape's vertices information.
    int vertices_num = getVerticesNum(shape, type);

    // Create the min and max values for x and y.
    MyVector2 vertex = ShapeGetVertex(shape, type, 0);
    double xmin = vertex.x;
    double xmax = vertex.x;
    double ymin = vertex.y;
    double ymax = vertex.y;

    // Loop though the vertices and find the min and max values for x and y.
    for (int i = 1; i < vertices_num; i++)
    {
        vertex = ShapeGetVertex(shape, type, i);
        if (vertex.x <= xmin)
            xmin = vertex.x;
        if (vertex.x >= xmax)
            xmax = vertex.x;
        if (vertex.y <= ymin)
            ymin = vertex.y;
        if (vertex.y >= ymax)
            ymax = vertex.y;
    }

    // Create the shape's bounding box.
    MyRectangle bounding_box = RectangleCreate(Vector2Create(xmin, ymin), xmax - xmin, ymax - ymin);

    //! Debug render.
    if (__debug_bounding_boxes)
    {
        DrawMyRectangle(bounding_box, GRAY);
    }

    return bounding_box;
}

// Returns an axis that passes through the center of the given circle and the center of the given shape.
static inline Segment CircleGetAxis(Circle circle, Shape shape, ShapeTypes type)
{
    // Make a segment that starts at the center of the circle, goes in the direction of the center of the shape and is of length 1.
    return SegmentFromVector2(circle.origin,
                              Vector2Normalize(Vector2FromPoints(circle.origin, ShapeCenterOfMass(shape, type))));
}

// Returns the axis of the given shapes that corresponds to the given index.
static inline Segment ShapesGetAxis(Shape shape1, ShapeTypes type1, Shape shape2, ShapeTypes type2, int index)
{
    assert(0 <= index && index < getSidesNum(shape1, type1) + getSidesNum(shape2, type2));

    Segment side;
    Segment axis;

    // If the given index refers to an axis of the first shape...
    if (index < getSidesNum(shape1, type1))
    {
        // If the first shape is not a circle, get the side pointed to by the index and calculate its normal.
        if (type1 != CIRCLE)
        {
            side = ShapeGetSide(shape1, type1, index);
            axis = SegmentFromVector2(Vector2DivideVal(Vector2Add(side.a, side.b), 2),
                                      Vector2Normal(Vector2Normalize(Vector2FromSegment(side))));
        }
        // If the first shape is a circle, get its axis.
        else
            axis = CircleGetAxis(shape1.circle, shape2, type2);
    }
    // If the given index refers to an axis of the second shape...
    else
    {
        // If the second shape is not a circle, get the side pointed to by the index and calculate its normal.
        if (type2 != CIRCLE)
        {
            side = ShapeGetSide(shape2, type2, index - getSidesNum(shape1, type1));
            axis = SegmentFromVector2(Vector2DivideVal(Vector2Add(side.a, side.b), 2),
                                      Vector2Normal(Vector2Normalize(Vector2FromSegment(side))));
        }
        // If the second shape is a circle, get its axis.
        else
            axis = CircleGetAxis(shape2.circle, shape1, type1);
    }

    //! Debug render.
    if (__debug_axes)
    {
        DrawVector2(Vector2MultiplyVal(Vector2FromSegment(axis), 100), axis.a, BLUE);
    }

    return axis;
}

// Returns true if the given point is colliding with the given circle.
static inline bool collisionCirclePoint(Circle c, MyVector2 p)
{
    return (distancePoints(c.origin, p) <= c.radius ? true : false);
}

// Returns true if the given circles are in collision.
static inline bool collisionCircles(Circle c1, Circle c2)
{
    return (distancePoints(c1.origin, c2.origin) <= c1.radius + c2.radius ? true : false);
}

// Checks for collision between two rectangles.
static inline bool collisionAABB(MyRectangle rec1, MyRectangle rec2)
{
    if (rec1.origin.x + rec1.width >= rec2.origin.x &&
        rec1.origin.x <= rec2.origin.x + rec2.width &&
        rec1.origin.y + rec1.height >= rec2.origin.y &&
        rec1.origin.y <= rec2.origin.y + rec2.height)
        return true;
    else
        return false;
}

// Project a shape onto a given axis.
static inline Segment projectShapeOnAxis(Segment axis, Shape shape, ShapeTypes type)
{
    // Get the axis' vector.
    MyVector2 axis_vec = Vector2FromSegment(axis);

    // Handle circles.
    if (type == CIRCLE)
    {
        // Project the circle's origin onto the axis.
        MyVector2 origin_projection = Vector2Add(axis.a, Vector2MultiplyVal(axis_vec, Vector2DotProduct(Vector2FromPoints(axis.a, shape.circle.origin), axis_vec)));

        // Create a segment of the circle's projection.
        Segment circle_projection = SegmentCreate(Vector2Substract(origin_projection, Vector2MultiplyVal(axis_vec, shape.circle.radius)),
                                                  Vector2Add(origin_projection, Vector2MultiplyVal(axis_vec, shape.circle.radius)));

        //! Debug render.
        if (__debug_points)
        {
            DrawPoint(shape.circle.origin, WHITE);
            DrawPoint(Vector2Add(origin_projection, Vector2MultiplyVal(axis_vec, shape.circle.radius)), SKYBLUE);
            DrawPoint(Vector2Substract(origin_projection, Vector2MultiplyVal(axis_vec, shape.circle.radius)), BLUE);
        }

        //! Debug render.
        if (__debug_projections)
        {
            DrawSegment(circle_projection, ORANGE);
        }

        return circle_projection;
    }

    //* https://fr.wikipedia.org/wiki/Projection_orthogonale#Projet%C3%A9_orthogonal_sur_une_droite,_distance

    // Get all the vertices of the shape.
    int vertices_num = getVerticesNum(shape, type);
    MyVector2 vertex;
    MyVector2 projected_points[vertices_num];

    // Loop over the vertices of the shape and get their projections onto the axis.
    for (int i = 0; i < vertices_num; i++)
    {
        vertex = ShapeGetVertex(shape, type, i);
        projected_points[i] = Vector2Add(axis.a, Vector2MultiplyVal(axis_vec, Vector2DotProduct(Vector2FromPoints(axis.a, vertex), axis_vec)));

        //! Debug render.
        if (__debug_points)
        {
            DrawCircle(projected_points[i].x, projected_points[i].y, 2, WHITE);
        }
    }

    // Find the closest and farthest points from the axis origin.
    MyVector2 min_point = projected_points[0];
    MyVector2 max_point = min_point;

    for (int i = 0; i < vertices_num; i++)
    {
        if (Vector2Copysign(projected_points[i], axis_vec).x > Vector2Copysign(max_point, axis_vec).x ||
            Vector2Copysign(projected_points[i], axis_vec).y > Vector2Copysign(max_point, axis_vec).y)
        {
            max_point = projected_points[i];
        }

        if (Vector2Copysign(projected_points[i], axis_vec).x < Vector2Copysign(min_point, axis_vec).x ||
            Vector2Copysign(projected_points[i], axis_vec).y < Vector2Copysign(min_point, axis_vec).y)
        {
            min_point = projected_points[i];
        }
    }

    //! Debug render.
    if (__debug_points)
    {
        DrawCircle(min_point.x, min_point.y, 2, SKYBLUE);
        DrawCircle(max_point.x, max_point.y, 2, BLUE);
    }

    MyVector2 axis_orig_to_min_point = Vector2FromPoints(axis.a, min_point);
    Segment projection = SegmentFromVector2(Vector2Add(axis.a, axis_orig_to_min_point),
                                            Vector2FromPoints(min_point, max_point));

    //! Debug render.
    if (__debug_projections)
    {
        DrawSegment(projection, ORANGE);
    }

    return projection;
}

// Returns true if the given point is colliding with the given segment.
static inline bool collisionSegmentPoint(Segment segment, MyVector2 point)
{
    if (roundInt(Vector2CrossProduct(Vector2FromSegment(segment), Vector2FromPoints(segment.a, point))) == 0)
    {
        if ((point.x >= segment.a.x && point.x <= segment.b.x) || (point.y >= segment.a.y && point.y <= segment.b.y) ||
            (point.x <= segment.a.x && point.x >= segment.b.x) || (point.y <= segment.a.y && point.y >= segment.b.y))
        {
            return true;
        }
    }
    return false;
}

// Returns true if the given projections are colliding each others
static inline bool collisionProjections(Segment projection1, Segment projection2)
{
    if (collisionSegmentPoint(projection1, projection2.a) ||
        collisionSegmentPoint(projection1, projection2.b) ||
        collisionSegmentPoint(projection2, projection1.a) ||
        collisionSegmentPoint(projection2, projection1.b))
    {
        return true;
    }
    return false;
}

// Checks for collision between two given shapes.
static inline bool collisionSAT(Shape shape1, ShapeTypes type1, Shape shape2, ShapeTypes type2)
{
    // If both shapes are circles, don't use SAT.
    if (type1 == CIRCLE && type2 == CIRCLE)
        return collisionCircles(shape1.circle, shape2.circle);

    // If both shapes are rectangles, don't use SAT.
    else if (type1 == RECTANGLE && type2 == RECTANGLE)
        return collisionAABB(shape1.rectangle, shape2.rectangle);

    // Check for collisions on the shapes' bounding boxes to not have to check if they are not in collision.
    else if (collisionAABB(getBoundingBox(shape1, type1), getBoundingBox(shape2, type2)))
    {
        //! Debug render.
        if (__debug_shapes)
        {
            DrawShape(shape1, type1, Vector2Zero(), GREEN);
            DrawShape(shape2, type2, Vector2Zero(), GREEN);
        }

        // Get the number of sides of both shapes.
        int sides = getSidesNum(shape1, type1) + getSidesNum(shape2, type2);

        // Loop over all of the axes.
        for (int i = 0; i < sides; i++)
        {
            // Project both shapes onto the axis.
            Segment projection1 = projectShapeOnAxis(ShapesGetAxis(shape1, type1, shape2, type2, i), shape1, type1);
            Segment projection2 = projectShapeOnAxis(ShapesGetAxis(shape1, type1, shape2, type2, i), shape2, type2);

            // If the projections don't overlap, the shapes are not in collision.
            if (!collisionProjections(projection1, projection2))
            {
                //! Debug render.
                if (__debug_failed_projections)
                {
                    DrawSegment(projection1, PINK);
                    DrawSegment(projection2, PINK);
                }
                return false;
            }
        }
        return true;
    }
    //! Debug render.
    if (__debug_shapes)
    {
        DrawShape(shape1, type1, Vector2Zero(), GREEN);
        DrawShape(shape2, type2, Vector2Zero(), GREEN);
    }

    return false;
}

#endif