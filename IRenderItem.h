#pragma once
class IRenderItem
{
	public:
		virtual ~IRenderItem() {};
		virtual void update(bool pixel[32][96]) = 0;
};

