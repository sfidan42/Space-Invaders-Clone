#pragma once

class Scene
{
public:
	Scene();
	virtual ~Scene() = 0;
	virtual void	eventHandler(void);
	virtual void	drawingHandler(void);
};
