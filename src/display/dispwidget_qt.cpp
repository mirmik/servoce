#include <local/display.h>
#include <QtGui/QtGui>


void servoce::disp::DisplayWidget::wheelEvent( QWheelEvent * e ) {
    onMouseWheel(e->buttons(), e->delta(), e->pos());
}

void servoce::disp::DisplayWidget::mousePressEvent( QMouseEvent* e )
{
    if (e->button() == Qt::LeftButton) {
        onLButtonDown((e->buttons() | e->modifiers()), e->pos());
    }
    else if (e->button() == Qt::MidButton)
    {
        onMButtonDown((e->buttons() | e->modifiers()), e->pos());
    }
    else if (e->button() == Qt::RightButton)
    {
        onRButtonDown((e->buttons() | e->modifiers()), e->pos());
    }
}

void servoce::disp::DisplayWidget::mouseReleaseEvent( QMouseEvent* e ) {

}

void servoce::disp::DisplayWidget::mouseMoveEvent( QMouseEvent * e ) {
    onMouseMove(e->buttons(), e->pos());
}