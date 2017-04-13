#include <QWidget>
#include <QTimer>
#include <QApplication>
#include <QGridLayout>

#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgQt/GraphicsWindowQt>
#include <iostream>

#include "simvis/osg_camera_man.h"

class QOsgViewer : public QWidget, public osgViewer::CompositeViewer
{
public:
	QOsgViewer(QWidget* parent = 0, Qt::WindowFlags f = 0, osgViewer::ViewerBase::ThreadingModel threadingModel=osgViewer::CompositeViewer::SingleThreaded);
	QWidget* addViewWidget( osgQt::GraphicsWindowQt* gw );
	osgQt::GraphicsWindowQt* createGraphicsWindow( int x, int y, int w, int h, const std::string& name="", bool windowDecoration=false );

	virtual void paintEvent( QPaintEvent* event ) override;

	void setScene( osg::Node* s );
	void setClearColor( const osg::Vec4& col );
	void moveCamera( const osg::Vec3d& delta_pos );
	void startCapture( const std::string& filename );
	void stopCapture();
	void captureCurrentFrame( const std::string& filename );
	bool isCapturing() { return capture_handler != nullptr; }
	void startTimer() { _timer.start( 10 ); }
	void stopTimer() { _timer.stop(); }
	vis::osg_camera_man& getCameraMan() { return *camera_man; }
	void setFrameTime( double t );

protected:
	bool eventFilter( QObject* obj, QEvent* event );
	size_t frame_count;
	QTimer _timer;
	osg::ref_ptr< vis::osg_camera_man > camera_man;
	osg::Node* scene;
	osg::ref_ptr< osgViewer::ScreenCaptureHandler > capture_handler;
	osg::ref_ptr< osgViewer::View > viewer;
	double current_frame_time;
	double last_drawn_frame_time;
};
