#ifndef PATTERNS_HPP
#define PATTERNS_HPP

#include <QStringList>
#include <QAbstractListModel>

class Patterns : public QAbstractListModel
{
  Q_OBJECT

public:

  enum Roles
  {
    NameRole = Qt::UserRole + 1 // `NameRole` is a custom-defined role.
  };

  explicit Patterns(QObject *parent = nullptr);

  // Required methods
  int rowCount (const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

  void                          setPatternIndex           (int index);
  const QStringList             getListOfPatterns         (void) const;
  int                           getCurrentPatternNumOfRows(void) const;
  int                           getCurrentPatternNumOfCols(void) const;
  const QVector<QVector<bool>>  getCurrentPatternMatrix   (void) const;

protected:

  QHash<int, QByteArray> roleNames() const override;

private:

  const QString stillLifes      = "--- Still Lifes ---";
  const QString block           = "Block";
  const QString beeHive         = "Bee-Hive";
  const QString loaf            = "Loaf";
  const QString boat            = "Boat";
  const QString tub             = "Tub";
  const QString oscillators     = "--- Oscillators ---";
  const QString blinker         = "Blinker";
  const QString toad            = "Toad";
  const QString beacon          = "Beacon";
  const QString pulsar          = "Pulsar";
  const QString pentaDecathlon  = "Penta-Decathlon";
  const QString spaceships      = "--- Spaceships ---";
  const QString glider          = "Glider";

    const QStringList m_listOfPatterns;
    QVector<QVector<bool>> m_patternMatrix;
    int m_currentIndex;
    int m_patternRows;
    int m_patternCols;
};

#endif // PATTERNS_HPP
