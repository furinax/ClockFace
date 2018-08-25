#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/svg/Svg.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ClockFaceApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

	ci::ImageSourceRef imageSource;
	gl::Texture2dRef mTexture;
};

void ClockFaceApp::setup()
{
	imageSource = loadImage(loadAsset("clock_face.png"));
	mTexture = gl::Texture::create(imageSource);
	setWindowSize(1000, 1000);
}

void ClockFaceApp::mouseDown( MouseEvent event )
{
}

void ClockFaceApp::update()
{
}

void ClockFaceApp::draw()
{
	gl::clear( Color( 0, 1, 0 ) ); 
	gl::pushModelView();

	gl::translate(getWindowWidth()/2, getWindowHeight()/2);
	gl::rotate(float(getElapsedSeconds() * 2.f * M_PI/60.f));
	gl::translate(-250, -250);

	gl::draw(mTexture);

	gl::popModelView();
}

CINDER_APP( ClockFaceApp, RendererGl )
