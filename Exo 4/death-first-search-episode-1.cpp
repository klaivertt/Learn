#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

struct Link
{
	int n1;
	int n2;
	bool isCut;

	Link(int _n1 = 0, int _n2 = 0) : n1(_n1), n2(_n2), isCut(false)
	{}
};

int main()
{
	int n; // the total number of nodes in the level, including the gateways
	int l; // the number of links
	int e; // the number of exit gateways
	cin >> n >> l >> e; cin.ignore();

	vector<Link> link(l);
	for (int i = 0; i < l; i++)
	{
		int n1; // N1 and N2 defines a link between these nodes
		int n2;
		cin >> n1 >> n2; cin.ignore();
		link[i] = Link(n1, n2);
	}

	vector<int> exit(e);
	for (int i = 0; i < e; i++)
	{
		int ei; // the index of a gateway node
		cin >> ei; cin.ignore();
		exit[i] = ei;
	}

	unordered_map<int, vector<Link>> toCut;
	for (auto e : exit)
	{
		vector<Link> attachedLink;
		for (auto l : link)
		{
			if (l.n1 == e || l.n2 == e)
			{
				attachedLink.push_back(l);
			}
		}
		toCut[e] = attachedLink;
	}

	int targetExit = 0;
	// game loop
	while (1)
	{
		int si; // The index of the node on which the Bobnet agent is positioned this turn
		cin >> si; cin.ignore();

		bool finded = false;
		Link findedLink;
		for (auto l : toCut)
		{
			vector<Link> find = l.second;
			for (auto f : find)
			{
				if (!f.isCut && (f.n1 == si || f.n2 == si))
				{
					f.isCut = true;
					finded = true;
					findedLink = f;
				}
			}
		}

		if (!finded)
		{
			vector<Link> find = toCut[exit[targetExit]];
			bool allCut = false;
			for (auto f : find)
			{
				if (!f.isCut)
				{
					f.isCut = true;
					finded = true;
					findedLink = f;
				}
				allCut = f.isCut;
			}

			if (allCut)
			{
				targetExit = targetExit + 1 < exit.size() ? targetExit + 1 : targetExit;
			}
		}

		// Example: 0 1 are the indices of the nodes you wish to sever the link between
		cout << "0 1" << endl;
	}
}