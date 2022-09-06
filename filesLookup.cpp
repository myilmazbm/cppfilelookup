// joinsearch.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

vector<string> getStringParse(string line, string seperator);
vector<string> getFileContent(string filePath);

int main()
{
    string sep = "\",\"";
    ifstream inputFile ("temmuzlog_.csv");
    ofstream outputFile ("output.csv");
    vector<string> outLines = getFileContent("mudures.csv");
    string line;
    vector<string> currentLine;


    if (inputFile.is_open())
    {
        while (getline(inputFile,line))
        {
            currentLine = getStringParse(line, sep);
            for (auto var: outLines)
            {
                if ((currentLine)[1].find(var) != string::npos)
                {
                    outputFile << line << endl;
                    break;
                }
            }
        }
    }

    inputFile.close();
    outputFile.close();
    
    


}

vector<string> getFileContent(string filePath)
{
    vector<string> allLines;
    // Open the File
    std::ifstream in(filePath.c_str());
    // Check if object is valid
    if (!in)
    {
        cerr << "Cannot open the File : " << filePath << std::endl;
        return allLines;
    }
    string str;
    // Read the next line from File untill it reaches the end.
    while (std::getline(in, str))
    {
        // Line contains string of length > 0 then save it in vector
        if (str.size() > 0){
            if (str.find("\"") != string::npos) {
                str = str.substr(1, str.size()-2);
            }
            allLines.push_back(str);
        }
            
    }
    //Close The File
    in.close();
    return allLines;
}

vector<string> getStringParse(string line,string seperator) {
    string firstStr;
    string lastStr;
    size_t sepSize  = seperator.size();
    size_t lineSize = line.size();
    size_t position = line.find(seperator);
    vector<string> cellsOfLine;

    firstStr = line.substr(0, position);
    lastStr = line.substr(position + sepSize);
    if (firstStr.find("\"") != string::npos)
    {
        firstStr = firstStr.substr(1);
    }
    cellsOfLine.push_back(firstStr);
    position = lastStr.find(seperator);
    while (position != string::npos)
    {
        firstStr = lastStr.substr(0, position);
        lastStr = lastStr.substr(position + sepSize);
        cellsOfLine.push_back(firstStr);
        position = lastStr.find("\",\"");
    }
    if (lastStr.find("\"") != string::npos )
    { 
        position = lastStr.find("\"");
        lastStr = lastStr.substr(0, position);
    }
    cellsOfLine.push_back(lastStr);
    return cellsOfLine;
}

// Programı çalıştır: Ctrl + F5 veya Hata Ayıkla > Hata Ayıklamadan Başlat menüsü
// Programda hata ayıkla: F5 veya Hata Ayıkla > Hata Ayıklamayı Başlat menüsü

// Kullanmaya Başlama İpuçları: 
//   1. Dosyaları eklemek/yönetmek için Çözüm Gezgini penceresini kullanın
//   2. Kaynak denetimine bağlanmak için Takım Gezgini penceresini kullanın
//   3. Derleme çıktısını ve diğer iletileri görmek için Çıktı penceresini kullanın
//   4. Hataları görüntülemek için Hata Listesi penceresini kullanın
//   5. Yeni kod dosyaları oluşturmak için Projeye Git > Yeni Öğe ekle veya varolan kod dosyalarını projeye eklemek için Proje > Var Olan Öğeyi Ekle adımlarını izleyin
//   6. Bu projeyi daha sonra yeniden açmak için Dosya > Aç > Proje'ye gidip .sln uzantılı dosyayı seçin
