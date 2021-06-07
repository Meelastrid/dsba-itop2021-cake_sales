#ifndef CAKE_H
#define CAKE_H




struct Cake {
    QString name;
    qint16 retail_price;
    qint16 wholesale_price;
    qint16 sold_retail;
    qint16 sold_wholesale;
    qint16 calories;
    QStringList composition;
};

#endif // CAKE_H
