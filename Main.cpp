#include "Common.h"

// Tools
int Rand(int _min, int _max)
{
	return rand() % (_max - _min) + _min;
}

int RandF(int _min, int _max)
{
	return _min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (_max - _min)));
}

// Class
class Item
{
public:
	Item(std::string _name, float _weight)
	{
		name = _name;
		weight = _weight;
	}

	~Item()
	{
	}

	void Display(void)
	{
		std::cout << "Item - Name : " << name << " , Weight :" << weight << std::endl;
	}

private:
	std::string name = "";
	float weight = 0;

protected:
};

struct InventorySlot
{
	InventorySlot() : item(Item("", 0)), count(0) {}

	Item item;
	int count;
};

class Inventory
{
public:
	Inventory()
	{

	}

	~Inventory()
	{
		delete[] slots;
	}

	void AddItem(Item _newItem, int _count)
	{
		InventorySlot* tempSlots = new InventorySlot[capacity + 1];

		if (slots != nullptr)
		{
			for (int i = 0; i < capacity; i++)
			{
				tempSlots[i] = slots[i];
			}

			delete[] slots;
		}
		capacity++;

		tempSlots[capacity - 1].item = _newItem;
		tempSlots[capacity - 1].count = _count;
		slots = tempSlots;
	}

	void Show(void)
	{
		currentCount = 0;
		for (int i = 0; i < capacity; i++)
		{
			std::cout << "Slot : " << i << std::endl;
			slots[i].item.Display();
			currentCount += slots[i].count;
		}
		std::cout << "Total of Items in Inventory : " << currentCount << std::endl;
	}
private:
	InventorySlot* slots = nullptr;
	int capacity = 0;
	int currentCount = 0;
protected:
};

// main
int main(void)
{
	srand(time(NULL));

	Inventory* inventory = new Inventory();

	std::string itemName[] =
	{
		"Saucisse",
		"Sword",
		"Shield",
		"Boots",
		"Arrow",
		"Bow",
	};

	int totalItem = static_cast<int>(sizeof(itemName) / sizeof(std::string));

	for (int i = 0; i < totalItem; i++)
	{
		inventory->AddItem(Item(itemName[i], RandF(0.2f, 8.f)), Rand(1, 10));
	}

	inventory->Show();

	system("pause");

	return EXIT_SUCCESS;
}