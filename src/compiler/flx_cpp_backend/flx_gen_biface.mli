val gen_biface_headers:
  Flx_mtypes2.sym_state_t ->
  Flx_bsym_table.t ->
  Flx_btype.biface_t list ->
  string

val gen_biface_bodies:
  Flx_mtypes2.sym_state_t ->
  Flx_bsym_table.t ->
  Flx_btype.biface_t list ->
  string

