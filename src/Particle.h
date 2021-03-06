#ifndef CC_PARTICLE_H
#define CC_PARTICLE_H
#include "Vectors.h"
#include "VertexStructs.h"
/* Represents particle effects, and manages rendering and spawning particles.
   Copyright 2014-2019 ClassiCube | Licensed under BSD-3
*/

struct IGameComponent;
struct ScheduledTask;
extern struct IGameComponent Particles_Component;

struct Particle {
	Vec3 velocity;
	float lifetime;
	Vec3 lastPos, nextPos;
	uint8_t size;
};

/* http://www.opengl-tutorial.org/intermediate-tutorials/billboards-particles/billboards/ */
void Particle_DoRender(Vec2* size, Vec3* pos, TextureRec* rec, PackedCol col, VertexP3fT2fC4b* vertices);
void Particles_Render(double delta, float t);
void Particles_Tick(struct ScheduledTask* task);
void Particles_BreakBlockEffect(IVec3 coords, BlockID oldBlock, BlockID block);
void Particles_RainSnowEffect(Vec3 pos);
#endif
