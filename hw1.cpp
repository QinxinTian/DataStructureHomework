#include <iostream>

std::string getCustomString(){
    std::string myName = "Qinxin, tian";
    std::string randomCharacters = "some random characters";
    std::string customString = myName + " " + randomCharacters;

    return customString;
}


int countChars(std::string words, char character){
    int count = 0;

    for (int i =0;i<words.size();i++)
    {
    	if (words[i] == character)
    		count++;
    }

    return count;
}


int countCharsCustom(char character)
{
	int count = 0;
	std::string customString = getCustomString();

	for (int i =0;i<customString.size();i++)
    {
    	if (customString[i] == character)
    		count++;
    }

    return count;
}



//��ʹ���Ѿ�����run method����Ȼ�����⣬�Ҳ�֪�����������⣬output pane��