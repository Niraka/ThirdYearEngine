#include "Scene\Modules\MD2Model.h"
#include "Scene\Modules\MD2Module.h"


MD2Model::MD2Model()
{
	m_n = 0;
	m_interp = 0;
	m_curent_time = 0;
	m_last_time = 0;	
}

MD2Model::~MD2Model()
{

}

MD2Model::MD2Model(MD2Module* pMod)
{
	m_n = 0;
	m_interp = 0;
	m_curent_time = 0;
	m_last_time = 0;
	m_parentModule = pMod;
	m_position = glm::vec3(0);
	m_scale = glm::vec3(1);
	m_rotation = glm::vec3(0);
}

void MD2Model::render()
{
	glLoadIdentity();

	glTranslatef(m_position.x, m_position.y, m_position.z);
	glScalef(m_scale.x, m_scale.y, m_scale.z);
	glRotatef(m_rotation.x, 1, 0, 0);
	glRotatef(m_rotation.y, 0, 1, 0);
	glRotatef(m_rotation.z, 0, 0, 1);

	int i, *pglcmds;
	vec3_t v_curr, v_next, v, norm;
	float* n_curr = nullptr;	
	float* n_next = nullptr;

	struct md2_frame_t *pframe1, *pframe2;
	struct md2_vertex_t *pvert1, *pvert2;
	struct md2_glcmd_t *packet;

	/* Check if n is in a valid range */
	if ((m_n < 0) || (m_n > m_mdl.header.num_frames - 1))
		return;

	/* Enable model's texture */
	glBindTexture(GL_TEXTURE_2D, m_mdl.tex_id);

	/* pglcmds points at the start of the command list */
	pglcmds = m_mdl.glcmds;

	/* Draw the model */
	while ((i = *(pglcmds++)) != 0)
	{
		if (i < 0)
		{
			glBegin(GL_TRIANGLE_FAN);
			i = -i;
		}
		else
		{
			glBegin(GL_TRIANGLE_STRIP);
		}

		/* Draw each vertex of this group */
		for (/* Nothing */; i > 0; --i, pglcmds += 3)
		{
			packet = (struct md2_glcmd_t *)pglcmds;
			pframe1 = &(&m_mdl)->frames[m_n];
			pframe2 = &(&m_mdl)->frames[m_n + 1];
			pvert1 = &pframe1->verts[packet->index];
			pvert2 = &pframe2->verts[packet->index];

			/* Pass texture coordinates to OpenGL */
			glTexCoord2f(packet->s, packet->t);

			float f1 = *anorms_table[pvert1->normalIndex];
			float f2 = *anorms_table[pvert2->normalIndex];
			/* Interpolate normals */
			*n_curr = f1;
			*n_next = f2;

			norm[0] = n_curr[0] + m_interp * (n_next[0] - n_curr[0]);
			norm[1] = n_curr[1] + m_interp * (n_next[1] - n_curr[1]);
			norm[2] = n_curr[2] + m_interp * (n_next[2] - n_curr[2]);

			glNormal3fv(norm);

			/* Interpolate vertices */
			v_curr[0] = pframe1->scale[0] * pvert1->v[0] + pframe1->translate[0];
			v_curr[1] = pframe1->scale[1] * pvert1->v[1] + pframe1->translate[1];
			v_curr[2] = pframe1->scale[2] * pvert1->v[2] + pframe1->translate[2];

			v_next[0] = pframe2->scale[0] * pvert2->v[0] + pframe2->translate[0];
			v_next[1] = pframe2->scale[1] * pvert2->v[1] + pframe2->translate[1];
			v_next[2] = pframe2->scale[2] * pvert2->v[2] + pframe2->translate[2];

			v[0] = v_curr[0] + m_interp * (v_next[0] - v_curr[0]);
			v[1] = v_curr[1] + m_interp * (v_next[1] - v_curr[1]);
			v[2] = v_curr[2] + m_interp * (v_next[2] - v_curr[2]);

			glVertex3fv(v);
		}

		glEnd();
	}
}

void MD2Model::update()
{
	m_last_time = m_curent_time;
	m_curent_time = (double)glutGet(GLUT_ELAPSED_TIME) / 1000.0;

	/* Animate model from frames 0 to num_frames-1 */
	m_interp += 10 * (m_curent_time - m_last_time);

	if (m_n < 0 || m_n > m_mdl.header.num_frames -1)		//if we are outside valid frame range
	{
		m_n = 0;		//return to first frame
	}

	if (m_interp >= 1.0f)		//if we've passed a frame
	{
		m_interp = 0.0f;		//reset interpolation
		m_n++;					//Increment to the new frame

		if (m_n >= m_mdl.header.num_frames - 1)			//if this exceeds max frames
		{
			m_n = 0;									//return to first frame - loop animation
		}
	}

}

const vec3_t MD2Model::anorms_table[162] = 
{ -0.525731f, 0.000000f, 0.850651f
- 0.442863f, 0.238856f, 0.864188f,
-0.295242f, 0.000000f, 0.955423f,
-0.309017f, 0.500000f, 0.809017f,
-0.162460f, 0.262866f, 0.951056f,
0.000000f, 0.000000f, 1.000000f,
0.000000f, 0.850651f, 0.525731f,
-0.147621f, 0.716567f, 0.681718f,
0.147621f, 0.716567f, 0.681718f,
0.000000f, 0.525731f, 0.850651f,
0.309017f, 0.500000f, 0.809017f,
0.525731f, 0.000000f, 0.850651f,
0.295242f, 0.000000f, 0.955423f,
0.442863f, 0.238856f, 0.864188f,
0.162460f, 0.262866f, 0.951056f,
-0.681718f, 0.147621f, 0.716567f,
-0.809017f, 0.309017f, 0.500000f,
-0.587785f, 0.425325f, 0.688191f,
-0.850651f, 0.525731f, 0.000000f,
-0.864188f, 0.442863f, 0.238856f,
-0.716567f, 0.681718f, 0.147621f,
-0.688191f, 0.587785f, 0.425325f,
-0.500000f, 0.809017f, 0.309017f,
-0.238856f, 0.864188f, 0.442863f,
-0.425325f, 0.688191f, 0.587785f,
-0.716567f, 0.681718f, -0.147621f,
-0.500000f, 0.809017f, -0.309017f,
-0.525731f, 0.850651f, 0.000000f,
0.000000f, 0.850651f, -0.525731f,
-0.238856f, 0.864188f, -0.442863f,
0.000000f, 0.955423f, -0.295242f,
-0.262866f, 0.951056f, -0.162460f,
0.000000f, 1.000000f, 0.000000f,
0.000000f, 0.955423f, 0.295242f,
-0.262866f, 0.951056f, 0.162460f,
0.238856f, 0.864188f, 0.442863f,
0.262866f, 0.951056f, 0.162460f,
0.500000f, 0.809017f, 0.309017f,
0.238856f, 0.864188f, -0.442863f,
0.262866f, 0.951056f, -0.162460f,
0.500000f, 0.809017f, -0.309017f,
0.850651f, 0.525731f, 0.000000f,
0.716567f, 0.681718f, 0.147621f,
0.716567f, 0.681718f, -0.147621f,
0.525731f, 0.850651f, 0.000000f,
0.425325f, 0.688191f, 0.587785f,
0.864188f, 0.442863f, 0.238856f,
0.688191f, 0.587785f, 0.425325f,
0.809017f, 0.309017f, 0.500000f,
0.681718f, 0.147621f, 0.716567f,
0.587785f, 0.425325f, 0.688191f,
0.955423f, 0.295242f, 0.000000f,
1.000000f, 0.000000f, 0.000000f,
0.951056f, 0.162460f, 0.262866f,
0.850651f, -0.525731f, 0.000000f,
0.955423f, -0.295242f, 0.000000f,
0.864188f, -0.442863f, 0.238856f,
0.951056f, -0.162460f, 0.262866f,
0.809017f, -0.309017f, 0.500000f,
0.681718f, -0.147621f, 0.716567f,
0.850651f, 0.000000f, 0.525731f,
0.864188f, 0.442863f, -0.238856f,
0.809017f, 0.309017f, -0.500000f,
0.951056f, 0.162460f, -0.262866f,
0.525731f, 0.000000f, -0.850651f,
0.681718f, 0.147621f, -0.716567f,
0.681718f, -0.147621f, -0.716567f,
0.850651f, 0.000000f, -0.525731f,
0.809017f, -0.309017f, -0.500000f,
0.864188f, -0.442863f, -0.238856f,
0.951056f, -0.162460f, -0.262866f,
0.147621f, 0.716567f, -0.681718f,
0.309017f, 0.500000f, -0.809017f,
0.425325f, 0.688191f, -0.587785f,
0.442863f, 0.238856f, -0.864188f,
0.587785f, 0.425325f, -0.688191f,
0.688191f, 0.587785f, -0.425325f,
-0.147621f, 0.716567f, -0.681718f,
-0.309017f, 0.500000f, -0.809017f,
0.000000f, 0.525731f, -0.850651f,
-0.525731f, 0.000000f, -0.850651f,
-0.442863f, 0.238856f, -0.864188f,
-0.295242f, 0.000000f, -0.955423f,
-0.162460f, 0.262866f, -0.951056f,
0.000000f, 0.000000f, -1.000000f,
0.295242f, 0.000000f, -0.955423f,
0.162460f, 0.262866f, -0.951056f,
-0.442863f, -0.238856f, -0.864188f,
-0.309017f, -0.500000f, -0.809017f,
-0.162460f, -0.262866f, -0.951056f,
0.000000f, -0.850651f, -0.525731f,
-0.147621f, -0.716567f, -0.681718f,
0.147621f, -0.716567f, -0.681718f,
0.000000f, -0.525731f, -0.850651f,
0.309017f, -0.500000f, -0.809017f,
0.442863f, -0.238856f, -0.864188f,
0.162460f, -0.262866f, -0.951056f,
0.238856f, -0.864188f, -0.442863f,
0.500000f, -0.809017f, -0.309017f,
0.425325f, -0.688191f, -0.587785f,
0.716567f, -0.681718f, -0.147621f,
0.688191f, -0.587785f, -0.425325f,
0.587785f, -0.425325f, -0.688191f,
0.000000f, -0.955423f, -0.295242f,
0.000000f, -1.000000f, 0.000000f,
0.262866f, -0.951056f, -0.162460f,
0.000000f, -0.850651f, 0.525731f,
0.000000f, -0.955423f, 0.295242f,
0.238856f, -0.864188f, 0.442863f,
0.262866f, -0.951056f, 0.162460f,
0.500000f, -0.809017f, 0.309017f,
0.716567f, -0.681718f, 0.147621f,
0.525731f, -0.850651f, 0.000000f,
-0.238856f, -0.864188f, -0.442863f,
-0.500000f, -0.809017f, -0.309017f,
-0.262866f, -0.951056f, -0.162460f,
-0.850651f, -0.525731f, 0.000000f,
-0.716567f, -0.681718f, -0.147621f,
-0.716567f, -0.681718f, 0.147621f,
-0.525731f, -0.850651f, 0.000000f,
-0.500000f, -0.809017f, 0.309017f,
-0.238856f, -0.864188f, 0.442863f,
-0.262866f, -0.951056f, 0.162460f,
-0.864188f, -0.442863f, 0.238856f,
-0.809017f, -0.309017f, 0.500000f,
-0.688191f, -0.587785f, 0.425325f,
-0.681718f, -0.147621f, 0.716567f,
-0.442863f, -0.238856f, 0.864188f,
-0.587785f, -0.425325f, 0.688191f,
-0.309017f, -0.500000f, 0.809017f,
-0.147621f, -0.716567f, 0.681718f,
-0.425325f, -0.688191f, 0.587785f,
-0.162460f, -0.262866f, 0.951056f,
0.442863f, -0.238856f, 0.864188f,
0.162460f, -0.262866f, 0.951056f,
0.309017f, -0.500000f, 0.809017f,
0.147621f, -0.716567f, 0.681718f,
0.000000f, -0.525731f, 0.850651f,
0.425325f, -0.688191f, 0.587785f,
0.587785f, -0.425325f, 0.688191f,
0.688191f, -0.587785f, 0.425325f,
-0.955423f, 0.295242f, 0.000000f,
-0.951056f, 0.162460f, 0.262866f,
-1.000000f, 0.000000f, 0.000000f,
-0.850651f, 0.000000f, 0.525731f,
-0.955423f, -0.295242f, 0.000000f,
-0.951056f, -0.162460f, 0.262866f,
-0.864188f, 0.442863f, -0.238856f,
-0.951056f, 0.162460f, -0.262866f,
-0.809017f, 0.309017f, -0.500000f,
-0.864188f, -0.442863f, -0.238856f,
-0.951056f, -0.162460f, -0.262866f,
-0.809017f, -0.309017f, -0.500000f,
-0.681718f, 0.147621f, -0.716567f,
-0.681718f, -0.147621f, -0.716567f,
-0.850651f, 0.000000f, -0.525731f,
-0.688191f, 0.587785f, -0.425325f,
-0.587785f, 0.425325f, -0.688191f,
-0.425325f, 0.688191f, -0.587785f,
-0.425325f, -0.688191f, -0.587785f,
-0.587785f, -0.425325f, -0.688191f,
-0.688191f, -0.587785f, -0.425325f
};

void MD2Model::setPosition(glm::vec3 p)
{
	m_position = p;
}

glm::vec3 MD2Model::getPosition()
{
	return m_position;
}

void MD2Model::setScale(glm::vec3 sz)
{
	m_scale = sz;
}

glm::vec3 MD2Model::getScale()
{
	return m_scale;
}

void MD2Model::setRotation(glm::vec3 r)
{
	m_rotation = r;
}

glm::vec3 MD2Model::getRotation()
{
	return m_rotation;
}