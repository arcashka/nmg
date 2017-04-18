#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtOpenGL/QtOpenGL>
#include <QMainWindow>
#include <QUrl>
#include "src_gui/queueitem.h"
#include "src_generators/intensitymap.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    enum Channel {
        RED,
        GREEN,
        BLUE,
        ALPHA
    };

    explicit MainWindow(QWidget *parent = 0);
    void closeEvent(QCloseEvent* event);
    ~MainWindow();
    bool getUseCustomUiColors();
    QColor getUiColorMain();
    QColor getUiColorText();
    QColor getUiColorGraphicsView();
    void focusGLWidget();

public slots:
    void setUseCustomUiColors(bool value);
    void setUiColorMain(QColor value);
    void setUiColorText(QColor value);
    void setUiColorGraphicsView(QColor value);
    void resetUiColors();
    
private:
    Ui::MainWindow *ui;
    QImage input;
    QImage channelIntensity;
    QImage normalmap;
    QImage specmap;
    QImage displacementmap;
    QImage ssaomap;
    QImage normalmapRawIntensity;
    QUrl loadedImagePath;
    QUrl exportPath;
    int lastCalctime_normal;
    int lastCalctime_specular;
    int lastCalctime_displace;
    int lastCalctime_ssao;
    bool stopQueue;
    QStringList supportedImageformats;
    bool useCustomUiColors;
    QColor uiColorMainDefault;
    QColor uiColorTextDefault;
    QColor uiColorGraphicsViewDefault;
    QColor uiColorMain;
    QColor uiColorText;
    QColor uiColorGraphicsView;

    bool setExportPath(QUrl path);
    void calcNormal();
    void calcSpec();
    void calcDisplace();
    void calcSsao();
    QString generateElapsedTimeMsg(int calcTimeMs, QString mapType);
    void connectSignalSlots();
    void hideAdvancedSettings();
    void displayCalcTime(int calcTime_ms, QString mapType, int duration_ms);
    void enableAutoupdate(bool on);
    void addImageToQueue(QUrl url);
    void addImageToQueue(QList<QUrl> urls);
    void saveQueueProcessed(QUrl folderPath);
    void save(QUrl url);
    bool load(QUrl url);
    void loadAllFromDir(QUrl url);
    int calcPercentage(int value, int percentage);
    void setUiColors();
    void writeSettings();
    void readSettings();

private slots:
    void loadUserFilePath();
    void loadSingleDropped(QUrl url);
    void loadMultipleDropped(QList<QUrl> urls);
    void calcNormalAndPreview();
    void calcSpecAndPreview();
    void calcDisplaceAndPreview();
    void calcSsaoAndPreview();
    void processQueue();
    void focusToOpenGl();
    void stopProcessingQueue();
    void saveUserFilePath();
    void preview();
    void preview(int tab);
    void switchToTab1();
    void switchToTab2();
    void switchToTab3();
    void switchToTab4();
    void zoomIn();
    void zoomOut();
    void resetZoom();
    void fitInView();
    void autoUpdate();
    void displayChannelIntensity();
    void openExportFolder();
    void removeImagesFromQueue();
    void changeOutputPathQueueDialog();
    void editOutputPathQueue();
    void queueItemDoubleClicked(QListWidgetItem *item);
    void normalmapSizeChanged();
    void on_horizontalScrollBar_depthValue_valueChanged(int value);
    void on_horizontalScrollBar_valueChanged(int value);
};

#endif // MAINWINDOW_H
