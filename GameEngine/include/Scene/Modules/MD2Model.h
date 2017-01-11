#ifndef MD2MODEL_H
#define MD2MOdEL_H

/* Credit to david Henry */

#include "Scene\Modules\MD2Module.h"
#include "Scene\Modules\anorms.h"


class MD2Model
{
	private:
		
		int m_n;				//!< The current frame number
		float m_interp;			//!< The current interpolation to use
		double m_curent_time;	//!< The current time value
		double m_last_time;		//!< The pervious time value
		MD2Module* m_parentModule;	//!< Pointer to the MD2Module that holds this model
		static const vec3_t anorms_table[162];		//!< Table of normals

		glm::vec3 m_position;
		glm::vec3 m_scale;
		glm::vec3 m_rotation;

	protected:

	public:
		/**
		Default constructor*/
		MD2Model();
		/**
		Destructor*/
		~MD2Model();
		/**
		Construct an MD2 Model from givne parameters
		@param pMod A pointer to the module creating this model*/
		MD2Model(MD2Module* pMod);

		md2_model_t m_mdl;		//!< The model structure data

		/**
		Render this model*/
		void render();		//!< Render this model at it's current frame with interp
		void update();

		void setPosition(glm::vec3 p);

		glm::vec3 getPosition();

		void setScale(glm::vec3 sz);

		glm::vec3 getScale();

		void setRotation(glm::vec3 r);

		glm::vec3 getRotation();
};

#endif
