#ifndef OBJECTBUTTON_H
#define OBJECTBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QEvent>

/**
 * @brief The ObjectButton class is a button with mouse hover events.
 */
class ObjectButton : public QPushButton
{
    Q_OBJECT
public:
    ObjectButton(const QString &text, QWidget *parent = nullptr);
    /**
     * @brief Default destructor.
     */
    virtual ~ObjectButton() = default;

    bool event(QEvent *event);

signals:
    void hoverEnter();
    void hoverLeave();

public slots:

};

#endif // OBJECTBUTTON_H
