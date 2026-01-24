#include "Common.h"

// Tools
int Rand(int _min, int _max)
{
	return rand() % (_max - _min) + _min;
}

float RandF(int _min, int _max)
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

	std::string GetName(void)
	{
		return name;
	}

private:
	std::string name = "";
	float weight = 0;

protected:
};

struct InventorySlot
{
	Item item = Item("", 0);
	int count = 0;
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
		int itemIndex = ItemInInventory(_newItem.GetName());
		if (itemIndex != -1)
		{
			slots[itemIndex].count += _count;
		}
		else
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
	}

	void RemoveItem(Item _removeItem, int _count)
	{
		int itemIndex = ItemInInventory(_removeItem.GetName());

		if (itemIndex != -1)
		{
			slots[itemIndex].count -= _count;

			if (slots[itemIndex].count <= 0)
			{

				if (capacity == 1)
				{
					delete[] slots;
					slots = nullptr;
					capacity = 0;
					return;
				}

				InventorySlot* tempSlots = new InventorySlot[capacity - 1];
				int j = 0;

				for (int i = 0; i < capacity; i++)
				{
					if (i != itemIndex)
					{
					tempSlots[j] = slots[i];
					j++;
					}
				}

				delete[] slots;
				slots = tempSlots;
				capacity--;
			}
		}
	}

	void Show(void)
	{
		currentCount = 0;
		for (int i = 0; i < capacity; i++)
		{
			std::cout << "Slot : " << i << std::endl;
			slots[i].item.Display();
			std::cout << "Nb of " << slots[i].item.GetName() << " : " << slots[i].count << std::endl;
			currentCount += slots[i].count;
		}
		std::cout << "Total of Items in Inventory : " << currentCount << std::endl;
	}

	int ItemInInventory(std::string _name)
	{
		for (int i = 0; i < capacity; i++)
		{
			Item& itemToCompare = slots[i].item;

			if (itemToCompare.GetName() == _name)
			{
				return i;
			}
		}
		return -1;
	}


	Item GetItemFromInventory(int _index)
	{
		if (_index < 0 || _index > capacity)
		{
			return Item("", 0);
		}

		return slots[_index].item;
	}

	Item GetItemFromInventory(std::string _name)
	{
		for (int i = 0; i < capacity; i++)
		{
			Item& itemToCompare = slots[i].item;

			if (itemToCompare.GetName() == _name)
			{
				return itemToCompare;
			}
		}
		return Item("", 0);
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

	std::cout << "\n\n\n" << std::endl;
	for (int i = 0; i < totalItem; i++)
	{
		inventory->AddItem(Item(itemName[i], RandF(0.2f, 8.f)), Rand(1, 10));
	}

	inventory->Show();
	std::cout << "\n\n\n" << std::endl;

	inventory->RemoveItem(inventory->GetItemFromInventory("Shield"), 100);

	inventory->Show();
	std::cout << std::endl;
	system("pause");

	delete inventory;

	return EXIT_SUCCESS;
}