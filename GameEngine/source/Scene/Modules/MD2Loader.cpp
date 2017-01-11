/* Credit to David Henry*/
#define _CRT_SECURE_NO_WARNINGS
#include "Scene\Modules\MD2Loader.h"
#include "Scene\Modules\MD2Model.h"

MD2Loader::MD2Loader()
{

}

MD2Loader::~MD2Loader()
{

}

MD2Loader::MD2Loader(MD2Module* MDMod)
{
	m_MD2Module = MDMod;
}

bool MD2Loader::load(const char *filename, struct md2_model_t *mdl)
{
	FILE *fp;
	int i;

	fp = fopen(filename, "rb");
	if (!fp)
	{
		fprintf(stderr, "Error: couldn't open \"%s\"!\n", filename);
		return 0;
	}

	/* Read header */
	fread(&mdl->header, 1, sizeof (struct md2_header_t), fp);

	if ((mdl->header.ident != 844121161) ||
		(mdl->header.version != 8))
	{
		/* Error! */
		fprintf(stderr, "Error: bad version or identifier\n");
		fclose(fp);
		return 0;
	}

	/* Memory allocations */
	mdl->skins = (struct md2_skin_t *)
		malloc(sizeof (struct md2_skin_t) * mdl->header.num_skins);
	mdl->texcoords = (struct md2_texCoord_t *)
		malloc(sizeof (struct md2_texCoord_t) * mdl->header.num_st);
	mdl->triangles = (struct md2_triangle_t *)
		malloc(sizeof (struct md2_triangle_t) * mdl->header.num_tris);
	mdl->frames = (struct md2_frame_t *)
		malloc(sizeof (struct md2_frame_t) * mdl->header.num_frames);
	mdl->glcmds = (int *)malloc(sizeof (int)* mdl->header.num_glcmds);

	/* Read model data */
	fseek(fp, mdl->header.offset_skins, SEEK_SET);
	fread(mdl->skins, sizeof (struct md2_skin_t),
		mdl->header.num_skins, fp);

	fseek(fp, mdl->header.offset_st, SEEK_SET);
	fread(mdl->texcoords, sizeof (struct md2_texCoord_t),
		mdl->header.num_st, fp);

	fseek(fp, mdl->header.offset_tris, SEEK_SET);
	fread(mdl->triangles, sizeof (struct md2_triangle_t),
		mdl->header.num_tris, fp);

	fseek(fp, mdl->header.offset_glcmds, SEEK_SET);
	fread(mdl->glcmds, sizeof (int), mdl->header.num_glcmds, fp);

	/* Read frames */
	fseek(fp, mdl->header.offset_frames, SEEK_SET);
	for (i = 0; i < mdl->header.num_frames; ++i)
	{
		/* Memory allocation for vertices of this frame */
		mdl->frames[i].verts = (struct md2_vertex_t *)
			malloc(sizeof (struct md2_vertex_t) * mdl->header.num_vertices);

		/* Read frame data */
		fread(mdl->frames[i].scale, sizeof (vec3_t), 1, fp);
		fread(mdl->frames[i].translate, sizeof (vec3_t), 1, fp);
		fread(mdl->frames[i].name, sizeof (char), 16, fp);
		fread(mdl->frames[i].verts, sizeof (struct md2_vertex_t),
			mdl->header.num_vertices, fp);
	}

	fclose(fp);
	return true;
}