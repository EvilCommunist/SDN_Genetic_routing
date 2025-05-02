#include <QGraphicsView>

class NetworkView : public QGraphicsView {
    Q_OBJECT
public:
    explicit NetworkView(QWidget *parent = nullptr);
    void addHost(const QPointF& pos);
    void addSwitch(const QPointF& pos);
    void connectItems(QGraphicsItem* a, QGraphicsItem* b);

private:
    QGraphicsScene *scene;
};
