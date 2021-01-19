/*This file is part of AnalisiDeiDati.

AnalisiDeiDati is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

AnalisiDeiDati is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with AnalisiDeiDati.  If not, see <http://www.gnu.org/licenses/>.*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

float value;
vector<float> x_numbers;
vector<float> y_numbers;

float average_calculation(const vector<float>& v){
    float average = accumulate(v.begin(), v.end(), 0.0);
    return average / v.size();
}
float median_calculation(vector<float>& v) {
    sort(v.begin(), v.end());
    float median = v.size();
    unsigned val = median;
    if (val % 2 != 0) {
        ((median += 1) /= 2) -= 1;
        return v[median];
    }
    return (v[(median/2)-1] += v[(median/2)]) / 2;
}

float mode_calculation(const vector<float>& v) {
    vector <float> sum(v.size());
    for (unsigned i=0;i < v.size();i++) {
        for (unsigned j = 0;j < v.size();j++) {
            if (v[i] == v[j] && i != j) {
                sum[i]++;							// add +1 in the vector every occurrence
            }
        }
        sum[i]++;									// also add +1 every for loop because there is always 1 number atleast in this position
    }
    unsigned ind = 0;
    int max = INT_MIN;
    for (unsigned i = 0;i < sum.size();i++) {
        if (max < sum[i]) {
            ind = i;								// here finding the index of the max occurrence in the vector and the returning it
            max = sum[i];
        }
    }
    return v[ind];
}

float absolute_mean_deviation(vector<float>& v, unsigned x) {
    float sum = 0;
    if (x == 0) {									// if x is 0  calculate the abs deviation from the average
        float average = average_calculation(v);
        for (unsigned i = 0; i < v.size();i++) {
            sum += abs(v[i]-average);
        }
        sum /= v.size();
        return sum;
    }
    if (x == 1) {								// if x is 1  calculate the abs deviation from the median
        float median = median_calculation(v);
        for (unsigned i = 0;i < v.size();i++) {
            sum += abs(v[i] - median);
        }
        sum /= v.size();
        return sum;
    }
}

float variance(const vector<float>& v) {
    float sum = 0;
    float average = average_calculation(v);
    for (unsigned i = 0;i < v.size();i++) {
        sum += pow((v[i] - average),2);
    }
    sum /= v.size();
    return sum;
}

float standard_deviation(const vector<float>& v) {
    return sqrt(variance(v));
}

float skewness_index(const vector<float>& v) {
    float average = average_calculation(v);
    float sum = 0;
    for (unsigned i =0 ;i < v.size();i++) {
        sum += pow((v[i] - average) / standard_deviation(v),3);
    }
    sum /= v.size();
    return sum;
}

float gini_index(const vector<float>& v) {
    float total_sum = accumulate(v.begin(), v.end(), 0);
    float cumulative_sum = 0, Qi_sum = 0, Pi_sum = 0;
    for (int i = 0;i < v.size();i++) {
        Pi_sum += static_cast<float>((i + 1)) / v.size();
        cumulative_sum += v[i];
        Qi_sum += cumulative_sum / total_sum;
    }
    return 1 - (Qi_sum / Pi_sum);

}

float covariance(const vector <float>& x, const vector <float>& y) {
    float sum_of_XY = 0;
    for (int i = 0;i < x.size();i++) {
        sum_of_XY += x[i] * y[i];
    }
    sum_of_XY /= x.size();
    return sum_of_XY - (average_calculation(x) * average_calculation(y));
}


float correlation_coefficient(const vector <float>& x, const vector <float>& y) {
    return covariance(x, y)/(standard_deviation(x)*standard_deviation(y));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_number_first_vector_clicked()
{
    value = ui->numeri->value();
    x_numbers.push_back(value);
}

void MainWindow::on_add_second_vector_clicked()
{
    value = ui->numeri_2nd->value();
    y_numbers.push_back(value);
}

void MainWindow::on_pulsante_risultato_clicked()
{
    if(ui->AVERAGE->isChecked()){
        float average = average_calculation(x_numbers);
        ui->risultato->setText(QString::number(average));

    }
    if(ui->median->isChecked()){
        float median = median_calculation(x_numbers);
        ui->risultato->setText(QString::number(median));
    }
    if(ui->MODE->isChecked()){
        float mode = mode_calculation(x_numbers);
        ui->risultato->setText(QString::number(mode));
    }
    if(ui->ABS_MEAN_DEVIATION_AVERAGE->isChecked()){
        float calc = absolute_mean_deviation(x_numbers,0);
        ui->risultato->setText(QString::number(calc));
    }
    if(ui->ABS_MEAN_DEVIATION_FROM_MEDIAN->isChecked()){
        float calc = absolute_mean_deviation(x_numbers,1);
        ui->risultato->setText(QString::number(calc));
    }
    if(ui->VARIANCE->isChecked()){
        float var = variance(x_numbers);
        ui->risultato->setText(QString::number(var));
    }
    if(ui->STANDARD_DEVIATION->isChecked()){
        float std = standard_deviation(x_numbers);
        ui->risultato->setText(QString::number(std));
    }
    if(ui->SKEWNESS_INDEX->isChecked()){
        float sk = skewness_index(x_numbers);
        ui->risultato->setText(QString::number(sk));
    }
    if(ui->GINI_INDEX->isChecked()){
        float gini = gini_index(x_numbers);
        ui->risultato->setText(QString::number(gini));
    }
    if(ui->COVARIANCE->isChecked()){
        float cov = covariance(x_numbers,y_numbers);
         ui->risultato->setText(QString::number(cov));
    }
    if(ui->CORRELATION_COEFFICIENT->isChecked()){
        float cc = correlation_coefficient(x_numbers,y_numbers);
         ui->risultato->setText(QString::number(cc));
    }
    if(ui->REGRESSION_LINE->isChecked()){
        float a, b;
        a = covariance(x_numbers, y_numbers) / variance(x_numbers);
        b = average_calculation(y_numbers) - (average_calculation(x_numbers) * covariance(x_numbers, y_numbers) / variance(x_numbers));
        ui->risultato->setText(" y = " + QString::number(a) + "x + (" + QString::number(b) + ")");
    }
}

void MainWindow::on_CLEAR_clicked()
{
    x_numbers.clear();
    y_numbers.clear();
}
