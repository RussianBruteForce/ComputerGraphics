#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QGraphicsScene>

class Scene : public QGraphicsScene
{
public:
	Scene(QRect sceneRect) :
	QGraphicsScene(sceneRect)
	{
		addText("Kek");

	}
};

#endif // SCENE_H
