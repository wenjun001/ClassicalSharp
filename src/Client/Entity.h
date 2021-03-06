#ifndef CC_ENTITY_H
#define CC_ENTITY_H
#include "EntityComponents.h"
#include "IModel.h"
#include "Typedefs.h"
#include "Vectors.h"
#include "AABB.h"
#include "GraphicsEnums.h"
#include "Matrix.h"
#include "GameStructs.h"
/* Represents an in-game entity.
   Copyright 2014-2017 ClassicalSharp | Licensed under BSD-3
*/
typedef struct IModel_ IModel; /* Forward declaration */

/* Offset used to avoid floating point roundoff errors. */
#define ENTITY_ADJUSTMENT 0.001f
/* Special value specifying an angle is not included in an orientation update. */
#define LOCATIONUPDATE_EXCLUDED -100000.31415926535f
/* Maxmimum number of characters in a model name. */
#define ENTITY_MAX_MODEL_LENGTH 10

#define ENTITIES_MAX_COUNT 256
#define ENTITIES_SELF_ID 255

UInt32 Entities_NameMode;
#define NAME_MODE_HOVERED      0
#define NAME_MODE_ALL          1
#define NAME_MODE_ALL_HOVERED  2
#define NAME_MODE_ALL_UNSCALED 3

UInt32 Entities_ShadowMode;
#define SHADOW_MODE_NONE          0
#define SHADOW_MODE_SNAP_TO_BLOCK 1
#define SHADOW_MODE_CIRCLE        2
#define SHADOW_MODE_CIRCLE_ALL    3

typedef bool (*TouchesAny_Condition)(BlockID block);

/* Represents a location update for an entity. Can be a relative position, full position, and/or an orientation update. */
typedef struct LocationUpdate_ {
	/* Position of the update (if included). */
	Vector3 Pos;
	/* Orientation of the update (if included). If not, has the value of LOCATIONUPDATE_EXCLUDED. */
	Real32 RotX, RotY, RotZ, HeadX;
	bool IncludesPosition, RelativePosition;
} LocationUpdate;

/* Clamps the given angle so it lies between [0, 360). */
Real32 LocationUpdate_Clamp(Real32 degrees);

void LocationUpdate_Construct(LocationUpdate* update, Real32 x, Real32 y, Real32 z,
	Real32 rotX, Real32 rotY, Real32 rotZ, Real32 headX, bool incPos, bool relPos);
void LocationUpdate_Empty(LocationUpdate* update);
void LocationUpdate_MakeOri(LocationUpdate* update, Real32 rotY, Real32 headX);
void LocationUpdate_MakePos(LocationUpdate* update, Vector3 pos, bool rel);
void LocationUpdate_MakePosAndOri(LocationUpdate* update, Vector3 pos, Real32 rotY, Real32 headX, bool rel);

/* Contains a model, along with position, velocity, and rotation. May also contain other fields and properties. */
typedef struct Entity_ {
	Vector3 Position;
	Real32 HeadX, HeadY, RotX, RotY, RotZ;
	Vector3 Velocity, OldVelocity;

	GfxResourceID TextureId, MobTextureId;
	AnimatedComp Anim;
	UInt8 SkinType;
	Real32 uScale, vScale;

	IModel* Model;
	UInt8 ModelNameRaw[String_BufferSize(ENTITY_MAX_MODEL_LENGTH)];
	BlockID ModelBlock; /* BlockID, if model name was originally a vaid block id. */
	AABB ModelAABB;
	Vector3 ModelScale;
	Vector3 Size;

	Matrix Transform;
	bool NoShade;

	/* TODO: SHOULD THESE BE A SEPARATE VTABLE STRUCT? (only need 1 shared pointer that way) */
	void (*Tick)(struct Entity_* entity, ScheduledTask* task);
	void (*SetLocation)(struct Entity_* entity, LocationUpdate* update, bool interpolate);
	void (*RenderModel)(struct Entity_* entity, Real64 deltaTime, Real32 t);
	void (*RenderName)(struct Entity_* entity);
	void (*ContextLost)(struct Entity_* entity);
	void (*ContextRecreated)(struct Entity_* entity);
	void (*Despawn)(struct Entity_* entity);
	PackedCol (*GetCol)(struct Entity_* entity);
} Entity;

void Entity_Init(Entity* entity);
Vector3 Entity_GetEyePosition(Entity* entity);
void Entity_GetTransform(Entity* entity, Vector3 pos, Vector3 scale);
void Entity_GetPickingBounds(Entity* entity, AABB* bb);
void Entity_GetBounds(Entity* entity, AABB* bb);
void Entity_SetModel(Entity* entity, STRING_PURE String* model);
void Entity_UpdateModelBounds(Entity* entity);
bool Entity_TouchesAny(AABB* bb, TouchesAny_Condition condition);
bool Entity_TouchesAnyRope(Entity* entity);	
bool Entity_TouchesAnyLava(Entity* entity);
bool Entity_TouchesAnyWater(Entity* entity);

Entity* Entities_List[ENTITIES_MAX_COUNT];
void Entities_Tick(ScheduledTask* task);
void Entities_RenderModels(Real64 delta, Real32 t);
void Entities_RenderNames(Real64 delta);
void Entities_RenderHoveredNames(Real64 delta);
void Entities_Init(void);
void Entities_Free(void);
void Entities_Remove(EntityID id);
EntityID Entities_GetCloset(Entity* src);
void Entities_DrawShadows(void);
#endif