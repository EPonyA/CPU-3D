#pragma once
#include <vector>

#include "RasterUtil.h"
#include "fwd.h"
#include "vecs.h"

class EDGE {
 public:
  EDGE(EDGE &_edge);
  ~EDGE();
  EDGE(VECTOR_3 *_v1, VECTOR_3 *_v2);
  void Render(RASTER *raster);
  VECTOR_3 *GetVertex(unsigned int vert);

 private:
  VECTOR_3 *v1, *v2;
};

class MATRIX {
 public:
  MATRIX(float *position);
  ~MATRIX();
  float *MultBy(float *position);
  void Pos(float *position);
  float *GetMatrix();
  void DRotate(unsigned int axis, float degrees);
  void Translate(float xOff, float yOff, float zOff);
  void Negate();
  void SetCoord(unsigned int coord, float val);
  static void TestInvert(MATRIX *viewMatrix);

 private:
  float *matrix;
  static void RotateX(MATRIX *_matrix, float rads);
  static void RotateY(MATRIX *_matrix, float rads);
  static void RotateZ(MATRIX *_matrix, float rads);
  void (*rotMatrices[3])(MATRIX *_matrix, float ang) = {
      MATRIX::RotateX, MATRIX::RotateY, MATRIX::RotateZ};
};

class TRI {
 public:
  TRI(TRI &_tri);
  TRI(VECTOR_3 *_v1, VECTOR_3 *_v2, VECTOR_3 *_v3, unsigned int _col);
  ~TRI();
  void Render(RASTER *raster);
  void Render(RASTER *raster, const unsigned int *texture,
              unsigned int texWidth, unsigned int texHeight);
  VECTOR_3 *GetVertex(unsigned int vert);

 private:
  VECTOR_3 *v1, *v2, *v3;
  unsigned int col;
};

class MESH {
 public:
  MESH(MESH &_mesh);
  MESH(std::vector<EDGE *> &_edges, float *position);
  ~MESH();
  void RenderWireframe(RASTER *raster);
  void RenderFaces(RASTER *raster);
  MATRIX *GetWorldMatrix();
  void SetWorldMatrix(float *position);
  void MultWorldMatrix(MATRIX *_matrix);
  MATRIX *GetLocalMatrix();
  void SetLocalMatrix(float *position);
  void MultLocalMatrix(MATRIX *_matrix);
  std::vector<EDGE *> GetEdges();
  std::vector<TRI *> GetTris();
  void TrisFromQuad(VECTOR_3 *_v1, VECTOR_3 *_v2, VECTOR_3 *_v3, VECTOR_3 *_v4,
                    unsigned int col);
  unsigned int GetPixel(float a, float b, float c);
  void SetTexture(const unsigned int *_texture, unsigned int _width,
                  unsigned int _height);

 private:
  std::vector<EDGE *> edges;
  std::vector<TRI *> tris;
  MATRIX *localMatrix;
  MATRIX *worldMatrix;
  const unsigned int *texture;
  unsigned int texHeight;
  unsigned int texWidth;
};
