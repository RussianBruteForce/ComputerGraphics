#include "Scene.h"




void Scene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	switch (event->buttons()) {
	case Qt::LeftButton:

		rotatePoint = event->scenePos().toPoint();
		break;
	default:
		break;
	}
	QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
//	qDebug() << "move";
	switch (event->buttons()) {
	case Qt::RightButton:
		drawPoint = event->scenePos().toPoint();
		//qDebug() << drawPoint;
		pi1->setPos(drawPoint);
		pi2->setPos(drawPoint);
		break;
	case Qt::LeftButton:
		rt.reset();
		rt.translate(rotatePoint.x(), rotatePoint.y());
		rt.rotate(rotatePoint.x() - event->scenePos().toPoint().x());
		rt.translate(-rotatePoint.x(), -rotatePoint.y());
		pi1->setTransform(rt);
		pi2->setTransform(rt);
		break;
	default:
		break;
	}

	//views().first()->setTransform(rt);

//	qDebug() << drawPoint;
	QGraphicsScene::mouseMoveEvent(event);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	rt.reset();
}

void Scene::wheelEvent(QGraphicsSceneMouseEvent* event)
{

}

void Scene::resizeEvent(QGraphicsSceneMouseEvent* event)
{

}
