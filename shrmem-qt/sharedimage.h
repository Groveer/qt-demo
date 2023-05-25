#include <QObject>

class QSharedMemory;

class SharedImage : public QObject
{
    Q_OBJECT
public:
    SharedImage(QObject *parent = nullptr);

    void wirteMemory(const QString &imageFile);
    void beginReadMemory(void **data, int &size);
    void endReadMemory();
    char *format() const;

private:
    QSharedMemory *mShmWriter;
    QSharedMemory *mShmReader;
};
