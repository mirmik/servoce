#include <shower/display.h>
#include <QtGui/QtGui>


void future::disp::DisplayWidget::wheelEvent( QWheelEvent * e ) {
    onMouseWheel(e->buttons(), e->delta(), e->pos());
}

void future::disp::DisplayWidget::mousePressEvent( QMouseEvent* e )
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

void future::disp::DisplayWidget::mouseReleaseEvent( QMouseEvent* e ) {

}

void future::disp::DisplayWidget::mouseMoveEvent( QMouseEvent * e ) {
    onMouseMove(e->buttons(), e->pos());
}