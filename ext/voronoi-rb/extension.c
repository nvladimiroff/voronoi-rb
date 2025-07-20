#include "ruby/ruby.h"
#define JC_VORONOI_IMPLEMENTATION
#include "../../voronoi/src/jc_voronoi.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

VALUE generate(VALUE self, VALUE points) {
  Check_Type(points, T_ARRAY);

  jcv_rect bounding_box = { { 0.0f, 0.0f }, { 1.0f, 1.0f } };
  jcv_diagram diagram;
  memset(&diagram, 0, sizeof(jcv_diagram));

  long len = RARRAY_LEN(points);
  jcv_point *jcv_points = malloc(sizeof(jcv_point) * len);

  for(int i = 0; i < len; i++) {
    VALUE elem = rb_ary_entry(points, i);
    float x = NUM2DBL(rb_ary_entry(elem, 0));
    float y = NUM2DBL(rb_ary_entry(elem, 1));

    jcv_points[i].x = x;
    jcv_points[i].y = y;
  }

  jcv_diagram_generate((int) len, (const jcv_point*)jcv_points, &bounding_box, 0, &diagram);

  const jcv_site* sites = jcv_diagram_get_sites(&diagram);
  VALUE out_array = rb_ary_new();
  for (int i=0; i<diagram.numsites; i++) {

    jcv_graphedge* graph_edge = sites[i].edges;
    while (graph_edge) {
      VALUE edge = rb_ary_new();
      rb_ary_push(edge, DBL2NUM(graph_edge->pos[0].x));
      rb_ary_push(edge, DBL2NUM(graph_edge->pos[0].y));
      rb_ary_push(edge, DBL2NUM(graph_edge->pos[1].x));
      rb_ary_push(edge, DBL2NUM(graph_edge->pos[1].y));
      graph_edge = graph_edge->next;
      rb_ary_push(out_array, edge);
    }
  }

  jcv_diagram_free(&diagram);

  return out_array;
}

void Init_extension(void) {
  VALUE voronoi = rb_define_module("Voronoi");
  VALUE diagram = rb_define_class_under(voronoi, "Diagram", rb_cObject);
  rb_define_singleton_method(diagram, "generate", generate, 1);
}
