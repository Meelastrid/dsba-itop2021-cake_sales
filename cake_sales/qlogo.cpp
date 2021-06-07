#include "qlogo.h"
#include <QPainter>
#include <QTextStream>
#include <QtMath>

QLogo::QLogo(QWidget *parent) : QWidget(parent)
{
}

void QLogo::paintEvent(QPaintEvent* event)
{
  QPainter painter(this);
  QPen pen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
  painter.setPen(pen);

  //draw body of cake
  painter.drawRoundedRect(30, 50, 90, 60, 10, 10);

  //draw topping using regular arcs and inverted arcs
  int startAngle = 30 * 16;
  int spanAngle = 120 * 16;
  QRect rect(30, 45, 19, 35);
  painter.drawArc(rect, -startAngle, -spanAngle);
  QRect rect2(48, 61, 19, 35);
  painter.drawArc(rect2, startAngle, spanAngle);
  QRect rect3(66, 45, 19, 35);
  painter.drawArc(rect3, -startAngle, -spanAngle);
  QRect rect4(84, 61, 19, 35);
  painter.drawArc(rect4, startAngle, spanAngle);
  QRect rect5(102, 45, 19, 35);
  painter.drawArc(rect5, -startAngle, -spanAngle);

  //draw candles
  painter.drawLine(45, 50, 45, 22);
  painter.drawLine(75, 50, 75, 22);
  painter.drawLine(105, 50, 105, 22);

  //draw candle flames
  painter.drawEllipse(44, 5, 3, 10);
  painter.drawEllipse(74, 5, 3, 10);
  painter.drawEllipse(104, 5, 3, 10);
}

