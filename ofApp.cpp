#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(1, 5);
	this->base_location_list = ico_sphere.getMesh().getVertices();

	this->number_of_sphere = 3000;
	while (this->sphere_list.size() < this->number_of_sphere) {

		int index = ofRandom(this->base_location_list.size());
		auto tmp_location = this->base_location_list[index];
		tmp_location = glm::normalize(tmp_location) * ofRandom(0, 100);

		auto radius = this->sphere_list.size() < 110 ? ofRandom(10, 50) : ofRandom(2, 20);

		bool flag = true;
		for (int i = 0; i < this->sphere_list.size(); i++) {

			if (glm::distance(tmp_location, get<1>(this->sphere_list[i])) < get<2>(this->sphere_list[i]) + radius) {

				flag = false;
				break;
			}
		}

		if (flag) {

			ofColor color;
			color.setHsb(ofRandom(255), 200, 255);

			auto size = (radius * 2) / sqrt(3);
			
			this->sphere_list.push_back(make_tuple(color, tmp_location, size));
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.66666666666666666);

	for (int i = 0; i < this->sphere_list.size(); i++) {

		auto location = get<1>(this->sphere_list[i]);
		auto size = get<2>(this->sphere_list[i]);

		ofPushMatrix();
		ofTranslate(location);

		ofRotateZ(ofRandom(360));
		ofRotateY(ofRandom(360));
		ofRotateX(ofRandom(360));

		ofFill();
		ofSetColor(0);
		ofDrawBox(size);

		ofNoFill();
		ofSetColor(255);
		ofDrawBox(size);

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}