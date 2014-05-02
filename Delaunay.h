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

static real det3( mat3_t *m );

///////////////////////////////////////////////
// ����ü �޸� �Ҵ� �� ��ȯ �Լ�
///////////////////////////////////////////////
static point2d_t* point_alloc();
static void point_free( point2d_t* p );

static halfedge_t* halfedge_alloc();
static void halfedge_free( halfedge_t* d );

void del_free_halfedges( delaunay_t *del );

static face_t* face_alloc();
static void face_free(face_t *f);

///////////////////////////////////////////////
// �¿� ��
static int classify_point_seg( point2d_t *s, point2d_t *e, point2d_t *pt );
static int del_classify_point( halfedge_t *d, point2d_t *pt );

// ���������� ���� ����Լ�
void del_divide_and_conquer( delaunay_t *del, int start, int end );

// ���� ���ҵ� �� 2, 3�� ¥�� ���δ� ���� ����
static int del_init_seg( delaunay_t *del, int start );
static int del_init_tri( delaunay_t *del, int start );

// ���� �Ϸ�� �ΰ��� ���δϸ� �����Ѵ�.
static void del_link( delaunay_t *result, delaunay_t *left, delaunay_t *right );

// �������������� �ִ� ���δϿ� ���̽��� �����سִ´�.���� �������� ������ ��.
void del_build_faces( delaunay_t *del );


static void compute_circle( point2d_t *pt0, point2d_t *pt1, point2d_t *pt2, real *cx, real *cy, real *radius );
static int in_circle( point2d_t *pt0, point2d_t *pt1, point2d_t *pt2, point2d_t *p );


static void del_remove_single_halfedge( halfedge_t *d );
static void del_remove_halfedge( halfedge_t *d );

static halfedge_t* del_valid_left( halfedge_t* b );
static halfedge_t* del_valid_right( halfedge_t *b );

static halfedge_t* del_valid_link( halfedge_t *b );

// �ΰ��� ���δ��� ���� �Ʒ��κ��� ����??? �� �������� �� ���Ŀ����� ����
static halfedge_t* del_get_lower_supportant( delaunay_t *left, delaunay_t *right );





static void build_halfedge_face( delaunay_t *del, halfedge_t *d );









#ifdef __cplusplus
extern "C" {
#endif

int			delaunay2d(float *points, int num_points, int **faces);
#ifdef __cplusplus
}
#endif

#endif // DELAUNAY_H