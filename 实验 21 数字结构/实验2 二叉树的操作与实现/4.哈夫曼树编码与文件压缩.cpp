#include <iostream>
#include <map>

using namespace std;

struct HFMNode
{
	char ch;
	int freq;
	HFMNode* left;
	HFMNode* right;
};

HFMNode* genHFMTree(map<char, int> letterFreq)
{
	HFMNode*globalRoot = NULL,* root,*tp1,*tp2;
	int minFreq;
	int minFreqNo[2];
	char minFreqLetter[2];
	bool EnWrite = false;
	if (!letterFreq.empty())//否则有预期之外的报错
		abort;
	while (!letterFreq.empty())
	{
		minFreq = INT_MAX;//让 minFreg比任何函数大
		for (auto mapPointer = letterFreq.begin(); mapPointer != letterFreq.end();mapPointer++)
		{
			if (minFreq > mapPointer->second)
			{
				minFreq = mapPointer->second;
				if(mapPointer->first != minFreqLetter[1])
				{
					minFreqNo[0] = mapPointer->second;
					minFreqLetter[0] = mapPointer->first;
				}
				if (!(letterFreq.size() == 3  && minFreqLetter[1] != NULL)&& letterFreq.size() != 1)
					EnWrite = true;
			}
			if (EnWrite && next(mapPointer) != letterFreq.end())
				mapPointer++;
			if ((EnWrite && minFreq >= mapPointer->second))//为减少压缩后空间
			{
				if (mapPointer->first != minFreqLetter[0])
				{
					minFreqNo[1] = mapPointer->second;
					minFreqLetter[1] = mapPointer->first;
				}
				EnWrite = false;
			}
			if (EnWrite && next(mapPointer) != letterFreq.end())
			{
				mapPointer--;
			}
		}
		tp1 = (HFMNode*)malloc(sizeof(HFMNode));
		tp1->ch = minFreqLetter[0];
		tp1->freq = minFreqNo[0];
		tp1->left = tp1->right = NULL; //避免出现值 0xcdcdcdcdcdcdcdcd {ch=??? freq=??? left=??? ...}，无法 if(tp1 !=NULL)
		if (minFreqLetter[1]!= NULL)
		{
			tp2 = (HFMNode*)malloc(sizeof(HFMNode));
			tp2->ch = minFreqLetter[1];
			tp2->freq = minFreqNo[1];
			tp2->left = tp2->right = NULL;
			//---//
			root = (HFMNode*)malloc(sizeof(HFMNode));
			root->left = tp1;
			root->right = tp2;
			root->freq = tp1->freq + tp2->freq;
			letterFreq.erase(minFreqLetter[1]);
			letterFreq.erase(minFreqLetter[0]);
			minFreqLetter[1] = NULL;
		}
		else
		{
			root = tp1;
			letterFreq.erase(minFreqLetter[0]);
		}
		if (globalRoot != NULL)
		{
			tp1 = globalRoot;//global root 借位 temp pointer 1
			globalRoot = (HFMNode*)malloc(sizeof(HFMNode));
			globalRoot->left = root;
			globalRoot->right = tp1;
			globalRoot->freq = globalRoot->left->freq + globalRoot->right->freq;
			letterFreq.erase(minFreqLetter[0]);
			letterFreq.erase(minFreqLetter[1]);
		}
		else
		{
			globalRoot = root;
		}
	}
	return globalRoot;
}

string pressDict(char target, string route, HFMNode* dict)
{
	string returnRoute = route;
	if (dict->ch == target)
		return route;
	if (dict->left != NULL)
		returnRoute = pressDict(target, route + "0", dict->left);
	if (dict->right != NULL && route == returnRoute) // route == returnRoute <==> NotFound
		returnRoute = pressDict(target, route + "1", dict->right);
	if (route != returnRoute )//鎵惧埌&涓嶆槸鍙跺瓙
		return returnRoute;
	route.erase(route.end()-1);
	return route;
}


string compress(string text, HFMNode* dict)
{
	string pressed = "";
	for (int i =0;i<text.size() ;i++)
		pressed = pressed + pressDict(text[i],"",dict);
	return pressed;
}

char depressDict(string route, HFMNode* dict, int *pointer)
{
	char stackReturn = NULL;
	if (dict->ch != -51)
		return dict->ch;
	*pointer += 1;
	if (route[*pointer] == '0')
		stackReturn = depressDict(route, dict->left, pointer);
	else if(stackReturn == NULL)
		stackReturn = depressDict(route, dict ->right, pointer);
	return stackReturn;
}

string depress(string pressedText, HFMNode* dict)
{
	string text;
	if (pressedText == "")
		return "";
	int pointer = -1;
	do// 用 do-while loop，因为在pointer = -1时，(pointer > pressedText.size())==true
	{
		text = text + depressDict(pressedText, dict ,&pointer);
	} while (pointer < pressedText.size()-1);
	return text;
}

void destroyHFMTree(HFMNode* node)
{
	if (node->left != NULL)
		destroyHFMTree(node->left);
	if (node->right != NULL)
		destroyHFMTree(node->right);
	free(node);
}

int main()
{
	string text = "The Chinese official said he viewed the Trump Presidency not as an aberration but as the product of a failing political system. This jibes with other accounts. The Chinese leadership believes that the United States, and Western democracies in general, haven’t risen to the challenge of a globalized economy, which necessitates big changes in production patterns, as well as major upgrades in education and public infrastructure. In Trump and Trumpism, the Chinese see an inevitable backlash to this failure.";
	cout <<"Origen text:" << text << endl;
	map<char, int>letterFreq;//获得字母频率
	for (char letter : text)
		letterFreq[letter]++;
	HFMNode *root = genHFMTree(letterFreq);
	text = compress(text,root);
	cout << "Compressed text:" << text << endl;
	text=depress(text, root);
	cout << "Depress text:" << text;
	destroyHFMTree(root);
}
