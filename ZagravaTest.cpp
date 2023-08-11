#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

void show(int N, int Q, vector<string> tags, vector<string> queries)
{
	cout << "Tags:\n";
	for (int i = 0; i < N; ++i)
	{
		cout << tags[i] << endl;
	}cout << endl;

	cout << "Queries:\n";
	for (int i = 0; i < Q; ++i)
	{
		cout << queries[i] << endl;
	}
}

void answer(string query, vector<string> taglines)
{
	vector<int> dotids;
	vector<string> tags;
	string attr, tmp;
	int tildaid;
	int j = 0;
	vector<int> globalids;
	int counter = 0;
	tmp = "";

	for (int i = 0; i < query.size(); ++i)
	{
		if(query[i] == '.')
			dotids.push_back(i);
	}
	tildaid = query.find("~");
	
	for (int i = 0; i < query.size(); ++i)
	{
		if (dotids.empty())
		{
			if (i == tildaid)
			{
				tags.push_back(tmp);
				tmp = "";
			}
			else if (i == query.size() - 1)
			{
				tmp += query[i];
				attr = tmp;
			}
			else
			{
				tmp += query[i];
			}
		}
		else
		{
			if (i == tildaid || i == dotids[j])
			{
				tags.push_back(tmp);
				++j;
				if (j >= dotids.size())
					j = 0;
				tmp = "";
			}
			else if (i == query.size() - 1)
			{
				tmp += query[i];
				attr = tmp;
			}
			else
			{
				tmp += query[i];
			}
		}
	}

	counter = 0;
	for (int i = 0; i < taglines.size(); ++i)
	{
		if (taglines[i].find(tags[tags.size() - 1]) != string::npos)
		{
			globalids.push_back(i);
			++counter;
		}
	}
	if (counter == 2)
	{
		string templine = taglines[globalids[0]];
		size_t tempid = templine.find(attr);
		if (tempid != string::npos || templine[tempid + 2] == '=')
		{
			cout << "\n" << attr << " of " << tags[tags.size() - 1] << ": ";
			counter = tempid + attr.size() + 4;
			while (templine[counter]!='"')
			{
				cout << templine[counter];
				++counter;
			}
		}
		else
		{
			cout << "Not Found!" << endl;
		}
	}
}

int main()
{
	int N, Q, row;
	ifstream input;
	string entireline, separator;
	vector<string> taglines, querylines;

	separator = " ";
	int tmpint = 0;
	string tmpstr = "";

	input.open("input.txt");
	if (input.is_open())
	{
		getline(input, entireline);
		tmpint = entireline.find(separator);
		for (int i = 0; i < entireline.size(); ++i)
		{
			tmpstr += entireline[i];
			if (i == tmpint)
			{
				N = atoi(tmpstr.c_str());
				tmpstr = "";
			}
		}
		Q = atoi(tmpstr.c_str());
		cout << "N = " << N << "\tQ = " << Q << endl;


		for (int i = 0; i < N + Q; ++i)
		{
			getline(input, entireline);

			if (i < N)
				taglines.push_back(entireline);
			else
				querylines.push_back(entireline);
		}
		input.close();
	}cout << endl;

	show(N, Q, taglines, querylines);

	cout << "\n\n\n";
	
	cout << "Choose the query to process(type number of it row): ";
	cin >> row;
	cout << "\n";
	answer(querylines[row-1], taglines);


	cout << "\n\n\n";
	return 0;
}