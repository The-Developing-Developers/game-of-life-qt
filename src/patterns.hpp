/**
 * @file patterns.hpp
 *
 * @brief Defines the shape patterns that the user can choose from a list.
 **/

#ifndef PATTERNS_HPP
#define PATTERNS_HPP

#include <QStringList>
#include <QAbstractListModel>

/**
 * @brief This class derives from `QAbstractListModel` because it is intended to represent a model to be used in the QML front-end by the ListView. \n
 * `Patterns` is instantiated by the `GameManager`, and is passed to the QML context in the `main` function.
 **/
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
  int       rowCount(const QModelIndex &parent = QModelIndex())             const override;
  QVariant  data    (const QModelIndex &index, int role = Qt::DisplayRole)  const override;

  void                          setPatternIndex           (int index); // TODO: for completeness, add 'getPatternIndex' (although it is never used in the QML front-end) and update 'GameManager' accordingly
  // const QStringList             getListOfPatterns         (void) const; // TODO: unused
  int                           getCurrentPatternNumOfRows(void) const;
  int                           getCurrentPatternNumOfCols(void) const;
  const QVector<QVector<bool>>  getCurrentPatternMatrix   (void) const;

protected:

  QHash<int, QByteArray> roleNames() const override;

private:

  // All the pattern shapes available to the user
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

    const QStringList       m_listOfPatterns;
    QVector<QVector<bool>>  m_patternMatrix;
    int m_currentIndex; // TODO: is it necessary to store this value? It looks like it is only used in `setPatternIndex`, and superfluously, too.
    int m_patternRows;
    int m_patternCols;
};

#endif // PATTERNS_HPP
