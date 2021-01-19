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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_add_second_vector_clicked();

    void on_pulsante_risultato_clicked();

    void on_add_number_first_vector_clicked();

    void on_CLEAR_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
