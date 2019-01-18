#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/svg/Svg.h"
#include <time.h>
#include <sys/utime.h>

using namespace ci;
using namespace ci::app;
using namespace std;

class ClockFaceApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
	void drawHand(const float radians);
	void updateClock();

	ci::ImageSourceRef imageSource;
	gl::Texture2dRef mHandTex;
	std::time_t mCurrentTime;
	long mInitialSeconds;
};

void ClockFaceApp::setup()
{
	imageSource = loadImage(loadAsset("clock_face.png"));
	mHandTex = gl::Texture::create(imageSource);
	setWindowSize(1000, 1000);
	updateClock();
	mInitialSeconds = localtime(&mCurrentTime)->tm_sec;
}

void ClockFaceApp::mouseDown( MouseEvent event )
{
}

void ClockFaceApp::updateClock()
{
	mCurrentTime = std::time(0);
}

void ClockFaceApp::update()
{
	updateClock();
	 
}

void ClockFaceApp::drawHand(const float radians)
{
	gl::pushModelView();
	gl::translate(getWindowWidth() / 2, getWindowHeight() / 2);
	gl::rotate(radians);
	gl::translate(-250, -250);
	gl::draw(mHandTex);
	gl::popModelView();
}

void ClockFaceApp::draw()
{
	gl::clear( Color( 0, 1, 0 ) ); 
	struct tm *tm = localtime(&mCurrentTime);
	drawHand(float((mInitialSeconds + getElapsedSeconds()) * 2.f * M_PI / 60.f)); //seconds
	drawHand(float(tm->tm_min * 2.f * M_PI / 60.f)); //mins
	drawHand(float(tm->tm_hour * 2.f * M_PI / 24.f)); //hours

}

CINDER_APP( ClockFaceApp, RendererGl )
