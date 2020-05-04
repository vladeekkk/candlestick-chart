#ifndef CHARTWINDOW_H
#define CHARTWINDOW_H

#include "view.h"
#include "themewindow.h"
#include "model.h"

#include <vector>

class QWidget;

class QMdiArea;

class QPushButton;

class QTimer;

class QCandlestickModelMapper;

class QCandlestickLegendMarker;

class QCandlestickSet;

class QCandlestickSeries;

class QDateTime;

class Candle {
public:
    QtCharts::QCandlestickSet *candlestickSet;
    qreal open;
    qreal high;
    qreal low;
    qreal close;
    qreal timestamp;

    //TODO перенести конструктор в срр

    Candle(double op, double hi, double lo, double clo, double timest) {
        candlestickSet = new QtCharts::QCandlestickSet();
        open = op;
        high = hi;
        low = lo;
        close = clo;
        timestamp = timest;
        candlestickSet->setOpen(open);
        candlestickSet->setHigh(high);
        candlestickSet->setLow(low);
        candlestickSet->setClose(close);
        candlestickSet->setTimestamp(timestamp);
    }
};


namespace Ui {
    class chartwindow;
} //Ui


class chartwindow : public QWidget {
public:
    explicit chartwindow(QWidget *parent = nullptr);

    ~chartwindow();

    double str_to_timestamp(const std::string &date) const;

    void fill(const Model &model); // Гоша, нужно обусдуить как нам побольше мувать

private slots:

    // Слоты от кнопок главного окна
    void on_pushButton_clicked();

    void on_pushButton2_clicked() const;

    void theme_change();//process

    //void on_help_button_clicked();

private:
    Ui::chartwindow *ui;
    std::vector<QPushButton *> buttons;
    themewindow *themewin;
    QtCharts::QChart *chart;
    QtCharts::QChartView *chartView;
    std::vector<Candle> drawable_data;
    std::vector<ModelData> data; // это дожно быть private ->data_
protected:
    void keyPressEvent(QKeyEvent *event);
};


class DataGrouping {
public:
    DataGrouping(std::vector<ModelData> in, int compressing_by_n_days) { // Гоша, а нельзя in замувать?
        candle_vec = std::move(in);
        tmp_open = candle_vec[0].open;
        tmp_close = candle_vec[0].close;
        tmp_high = candle_vec[0].high;
        tmp_low = candle_vec[0].low;
        unix_time_cnt = 0;
        number_of_days = compressing_by_n_days;
    }

    void compress_by_n_days();

    double str_to_timestamp(const std::string &date) const; // Гоша, точно такой же метод есть chartwindow, напишу обсудим как вынести это

    std::vector<Candle> result;

private:
    std::vector<ModelData> candle_vec;

    size_t unix_time_cnt, number_of_days;
    double tmp_open, tmp_close, tmp_high, tmp_low;
};

#endif // CHARTWINDOW_H
