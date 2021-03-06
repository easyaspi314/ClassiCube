#ifndef CC_PROTOCOL_H
#define CC_PROTOCOL_H
#include "Input.h"
#include "String.h"
#include "Vectors.h"
/* Implements network protocols for original classic, CPE, and WoM textures.
   Copyright 2014-2019 ClassiCube | Licensed under BSD-3
*/

struct PickedPos;
struct Stream;
void Protocol_RemoveEntity(EntityID id);
void Protocol_Reset(void);
void Protocol_Tick(void);

extern bool cpe_needD3Fix;
void Classic_SendChat(const String* text, bool partial);
void Classic_WritePosition(Vec3 pos, float rotY, float headX);
void Classic_WriteSetBlock(int x, int y, int z, bool place, BlockID block);
void Classic_SendLogin(const String* username, const String* verKey);
void CPE_SendPlayerClick(MouseButton button, bool pressed, uint8_t targetId, struct PickedPos* pos);
#endif
