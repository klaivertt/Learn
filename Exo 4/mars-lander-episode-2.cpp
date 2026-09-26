#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
	int surface_n; // the number of points used to draw the surface of Mars.
	cin >> surface_n; cin.ignore();
	int lastX = -1;
	int lastY = -1;
	int dist = 0;
	int finalPosX = 0;

	for (int i = 0; i < surface_n; i++)
	{
		int land_x; // X coordinate of a surface point. (0 to 6999)
		int land_y; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
		cin >> land_x >> land_y; cin.ignore();

		if (lastX == -1)
		{
			lastX = land_x;
		}
		if (lastY == -1)
		{
			lastY = land_y;
		}

		if (lastY == land_y)
		{
			dist += land_x - lastX;
			if (dist >= 1000)
			{
				finalPosX = land_x - 500;
				break;
			}
			lastY = land_y;
			lastX = land_x;
		}
		else
		{
			lastY = land_y;
			dist = 0;
			lastX = land_x;
		}
	}

	// game loop
	while (1)
	{
		int x;
		int y;
		int h_speed; // the horizontal speed (in m/s), can be negative.
		int v_speed; // the vertical speed (in m/s), can be negative.
		int fuel; // the quantity of remaining fuel in liters.
		int rotate; // the rotation angle in degrees (-90 to 90).
		int power; // the thrust power (0 to 4).
		cin >> x >> y >> h_speed >> v_speed >> fuel >> rotate >> power; cin.ignore();

		// Write an action using cout. DON'T FORGET THE "<< endl"
		// To debug: cerr << "Debug messages..." << endl;

		int targetPower;

		if (v_speed < -40)
		{
			targetPower = 4;
		}
		else if (v_speed < -30)
		{
			targetPower = 3;
		}
		else if (v_speed < -20)
		{
			targetPower = 2;
		}
		else
		{
			targetPower = 0;
		}

		int newPower = power;

		if (newPower < targetPower)
		{
			newPower++;
		}
		else if (newPower > targetPower)
		{
			newPower--;
		}

		cout << "0 " << newPower << endl;
	}
}