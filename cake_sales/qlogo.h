#ifndef QLOGO_H
#define QLOGO_H

#include <QWidget>

class QLogo : public QWidget
{
    Q_OBJECT
public:
    explicit QLogo(QWidget *parent = nullptr);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif // QLOGO_H
