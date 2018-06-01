#pragma once
#include "stdafx.h"
#include "canvas.h"

class ICanvasDrawable
{
public:
	virtual ~ICanvasDrawable() {};
	virtual void Draw(ICanvas & canvas) const = 0;
};