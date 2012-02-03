#ifndef UIGRAPHICSCURSORITEM_H
#define UIGRAPHICSCURSORITEM_H

#include "TimelineTypes.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPen>
#include <QRectF>

class UIGraphicsCursorItem : public QObject, public QGraphicsItem {

    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    enum {
        Type = UserType + 5
    };

public:
    UIGraphicsCursorItem(const QPen& pen);

public:
    virtual int type() const;
    virtual QRectF boundingRect() const;
    int cursorPos() const;
    void setHeight(int height);

protected:
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant& value);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

public slots:
    void frameChanged(qint64 position);

signals:
    void cursorPositionChanged(qint64 pos);
    void cursorMoved(qint64 pos);

private:
    QPen m_pen;
    QRectF m_boundingRect;
    bool m_mouseDown;
};

#endif // UIGRAPHICSCURSORITEM_H