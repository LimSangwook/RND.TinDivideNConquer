#ifndef DELAUNAY_H
#define DELAUNAY_H

/*
**  delaunay.c : compute 2D delaunay triangulation in the plane.
**  Copyright (C) 2005  Wael El Oraiby <wael.eloraiby@gmail.com>
**
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define DEL_CIRCLE
#ifdef USE_DOUBLE
typedef double real;
#else
typedef float real;
#endif
#define ON_RIGHT	1
#define ON_SEG		0
#define ON_LEFT		-1

#define OUTSIDE		-1
#define	ON_CIRCLE	0
#define INSIDE		1

struct	point2d_s;
struct	face_s;
struct	halfedge_s;
struct	delaunay_s;

typedef struct point2d_s	point2d_t;
typedef struct face_s		face_t;
typedef struct halfedge_s	halfedge_t;
typedef struct delaunay_s	delaunay_t;
typedef real mat3_t[3][3];

struct point2d_s
{
	int					idx;		/* point index in input buffer */
	real				x, y;		/* point coordinates */
	halfedge_t*			he;			/* point halfedge */
};

struct face_s
{
/*	real			radius;
	real			cx, cy;
	point2d_t*		p[3];
*/
	halfedge_t*		he;				/* a pointing half edge */
	int				num_verts;		/* number of vertices on this face */
};

struct halfedge_s
{
	point2d_t*		vertex;			/* vertex */
	halfedge_t*		alpha;			/* alpha */
	halfedge_t*		sigma;			/* sigma */
	halfedge_t*		amgis;			/* sigma^-1 */
	face_t*			face;			/* halfedge face */
};

struct delaunay_s
{
	halfedge_t*		rightmost_he;		/* right most halfedge */
	halfedge_t*		leftmost_he;		/* left most halfedge */
	point2d_t**		points;				/* pointer to points */
	face_t*			faces;				/* faces of delaunay */
	int				num_faces;			/* face count */
	int				start_point;		/* start point index */
	int				end_point;			/* end point index */
};


int			delaunay2d(float *points, int num_points, int **faces);
#endif // DELAUNAY_H
