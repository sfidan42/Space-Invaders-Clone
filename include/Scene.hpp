#pragma once

class Scene
{
public:
	Scene();
	virtual ~Scene() = 0;
	virtual void	eventHandler(void) = 0;
	virtual void	drawingHandler(void) = 0;
};
