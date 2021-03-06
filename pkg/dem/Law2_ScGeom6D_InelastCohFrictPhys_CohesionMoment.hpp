#pragma once
#include "CohesiveFrictionalContactLaw.hpp"
#include "InelastCohFrictPhys.hpp"

class Law2_ScGeom6D_InelastCohFrictPhys_CohesionMoment: public LawFunctor{
	public:
		Real normElastEnergy();
		Real shearElastEnergy();
	virtual void go(shared_ptr<IGeom>& _geom, shared_ptr<IPhys>& _phys, Interaction* I);
	YADE_CLASS_BASE_DOC_ATTRS_CTOR_PY(Law2_ScGeom6D_InelastCohFrictPhys_CohesionMoment,LawFunctor,"Law for linear traction-compression-bending-twisting, with cohesion+friction and Mohr-Coulomb plasticity surface. This law adds adhesion and moments to :yref:`Law2_ScGeom_FrictPhys_CundallStrack`.\n\nThe normal force is (with the convention of positive tensile forces) $F_n=min(k_n*u_n, a_n)$, with $a_n$ the normal adhesion. The shear force is $F_s=k_s*u_s$, the plasticity condition defines the maximum value of the shear force, by default $F_s^{max}=F_n*tan(\\phi)+a_s$, with $\\phi$ the friction angle and $a_n$ the shear adhesion. If :yref:`CohFrictPhys::cohesionDisableFriction` is True, friction is ignored as long as adhesion is active, and the maximum shear force is only $F_s^{max}=a_s$.\n\nIf the maximum tensile or maximum shear force is reached and :yref:`CohFrictPhys::fragile` =True (default), the cohesive link is broken, and $a_n, a_s$ are set back to zero. If a tensile force is present, the contact is lost, else the shear strength is $F_s^{max}=F_n*tan(\\phi)$. If :yref:`CohFrictPhys::fragile` =False (in course of implementation), the behaviour is perfectly plastic, and the shear strength is kept constant.\n\nIf :yref:`Law2_ScGeom6D_CohFrictPhys_CohesionMoment::momentRotationLaw` =True, bending and twisting moments are computed using a linear law with moduli respectively $k_t$ and $k_r$ (the two values are the same currently), so that the moments are : $M_b=k_b*\\Theta_b$ and $M_t=k_t*\\Theta_t$, with $\\Theta_{b,t}$ the relative rotations between interacting bodies. The maximum value of moments can be defined and takes the form of rolling friction. Cohesive -type moment may also be included in the future.\n\nCreep at contact is implemented in this law, as defined in [Hassan2010]_. If activated, there is a viscous behaviour of the shear and twisting components, and the evolution of the elastic parts of shear displacement and relative twist is given by $du_{s,e}/dt=-F_s/\\nu_s$ and $d\\Theta_{t,e}/dt=-M_t/\\nu_t$.",
		((bool,neverErase,false,,"Keep interactions even if particles go away from each other (only in case another constitutive law is in the scene, e.g. :yref:`Law2_ScGeom_CapillaryPhys_Capillarity`)"))
		((bool,always_use_moment_law,false,,"If true, use bending/twisting moments at all contacts. If false, compute moments only for cohesive contacts."))
		((bool,shear_creep,false,,"activate creep on the shear force, using :yref:`CohesiveFrictionalContactLaw::creep_viscosity`."))
		((bool,twist_creep,false,,"activate creep on the twisting moment, using :yref:`CohesiveFrictionalContactLaw::creep_viscosity`."))
		((bool,useIncrementalForm,false,,"use the incremental formulation to compute bending and twisting moments. Creep on the twisting moment is not included in such a case."))
		((int,plastDissipIx,-1,,"Index for plastic dissipation (with O.trackEnergy)"))
		((bool,onplastB,false,,"true if plasticity achieved on bending"))
		((bool,onplastTw,false,,"true if plasticity achieved on twisting"))
		((bool,onplastT,false,,"true if plasticity achieved on traction/compresion")) // if plasticity achieved in traction, also for later compresion, and inverse
		((Real,lastPlastUn,0,,"last tension compression un value of plasticity"))
		((Real,lastPlastBend,0,,"last bend  value of plasticity"))
		((Real,lastPlastTw,0,,"last bend  value of plasticity"))
		((Real,unPrev,0,,"previous timestep penetrationDepth"))
		((Real,creep_viscosity,1,,"creep viscosity [Pa.s/m]. probably should be moved to Ip2_CohFrictMat_CohFrictMat_CohFrictPhys."))
		,,
		.def("normElastEnergy",&Law2_ScGeom6D_InelastCohFrictPhys_CohesionMoment::normElastEnergy,"Compute normal elastic energy.")
		.def("shearElastEnergy",&Law2_ScGeom6D_InelastCohFrictPhys_CohesionMoment::shearElastEnergy,"Compute shear elastic energy.")
	);
	FUNCTOR2D(ScGeom6D,InelastCohFrictPhys);
	DECLARE_LOGGER;
	private:
	Real currentContactPhysics;
};
REGISTER_SERIALIZABLE(Law2_ScGeom6D_InelastCohFrictPhys_CohesionMoment);
