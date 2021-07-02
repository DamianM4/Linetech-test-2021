#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <future>

class Stat{
private:
    std::vector<double> m_dataset;

public:
    Stat(std::string filename);
    void read_data(std::string filename);
    double average();
    double median();
};

Stat::Stat(std::string filename){
    read_data(filename);
}

void Stat::read_data(std::string filename){
    std::ifstream file(filename);
    std::string buf;
    while (std::getline(file, buf)){
        if (std::isdigit(buf[0])){
            m_dataset.push_back(std::stod(buf));
        }
    }
}

double Stat::average(){
    double sum = 0;
    for(auto element: m_dataset){
        sum += element;
    }

    double ave = sum / m_dataset.size();

    return ave;
}

double Stat::median(){
    std::vector<double> data;
    data = m_dataset;
    std::sort(data.begin(), data.end());

    double median;
    if (data.size() % 2 == 0){
        median = (data[data.size()/2 - 1] + data[data.size()/2]) / 2.;
    }
    else {
        median = data[data.size()/2];
    }

    return median;
}

int main(){
    Stat stat = Stat("data.txt");

    auto average = std::async(std::launch::async, &Stat::average, &stat);

    auto median = std::async(std::launch::async, &Stat::median, &stat);

    average.wait();
    median.wait();

    auto aver = average.get();
    auto medi = median.get();

    if (aver > medi){
        std::cout << "Average: " << aver << std::endl;
    }
    else {
        std::cout << "Median: " << medi << std::endl;
    }

    return 0;
}
