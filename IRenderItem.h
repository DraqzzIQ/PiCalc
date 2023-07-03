#pragma once
class IRenderItem
{
	public:
		virtual ~IRenderItem() {};
		virtual void update() = 0;
};

