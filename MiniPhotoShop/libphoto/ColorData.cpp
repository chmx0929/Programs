//
//  ColorData.cpp
//  Originally created by the CSci-3081W TAs.
//

#include "ColorData.h"
#include <math.h>

const float YCbCr_K_red = 0.2126;
const float YCbCr_K_blue = 0.0722;


ColorData::ColorData() : m_red(1), m_green(1), m_blue(1), m_alpha(1) {	
}

ColorData::ColorData(float r, float g, float b ) : m_red(r), m_green(g), m_blue(b), m_alpha(1) {	
}

ColorData::ColorData(float r, float g, float b, float a) : m_red(r), m_green(g), m_blue(b), m_alpha(a)  {	
}

void ColorData::setRed(float r) {
	m_red = r;
}

void ColorData::setGreen(float g) {
	m_green = g;
}

void ColorData::setBlue(float b) {
	m_blue = b;
}

void ColorData::setAlpha(float a) {
	m_alpha = a;
}

float ColorData::getRed() const {
	return m_red;
}

float ColorData::getGreen() const {
	return m_green;
}

float ColorData::getBlue() const {
	return m_blue;
}

float ColorData::getAlpha() const {
	return m_alpha;
}

float ColorData::getLuminance() const {
	return YCbCr_K_red * m_red + (1.0 - YCbCr_K_red - YCbCr_K_blue) * m_green + (YCbCr_K_blue * m_blue);
}


float ColorData::getChromaBlueDifference() const {
	return 0.5 * (m_blue - getLuminance()) / (1.0 - YCbCr_K_blue);
}


float ColorData::getChromaRedDifference() const {
	return 0.5 * (m_red - getLuminance()) / (1.0 - YCbCr_K_red);
}


ColorData ColorData::ColorDataFloor(ColorData input, float digit)
{
	input.m_red = floor(input.m_red * digit) / digit;
	input.m_green = floor(input.m_green * digit) / digit;
	input.m_blue = floor(input.m_blue * digit) / digit;
	return input;
}


ColorData ColorData::clampedColor() const {
	float clampedRed = ColorData::clampValue(this->getRed(), 0.f, 1.f);
	float clampedGreen = ColorData::clampValue(this->getGreen(), 0.f, 1.f);
	float clampedBlue = ColorData::clampValue(this->getBlue(), 0.f, 1.f);
	float clampedAlpha = ColorData::clampValue(this->getAlpha(), 0.f, 1.f);
	
	return ColorData(clampedRed, clampedGreen, clampedBlue, clampedAlpha);	
}


// Apply component-wise arithmatic operations
ColorData operator* (const ColorData& a, float f) {
	return ColorData(a.m_red*f, a.m_green*f, a.m_blue*f, a.m_alpha*f);
}

ColorData operator+ (const ColorData& a, const ColorData& b) {
	return ColorData(a.m_red + b.m_red, a.m_green + b.m_green, a.m_blue + b.m_blue, a.m_alpha + b.m_alpha);
}

ColorData operator- (const ColorData& a, const ColorData& b) {
	return ColorData(a.m_red - b.m_red, a.m_green - b.m_green, a.m_blue - b.m_blue, a.m_alpha - b.m_alpha);
}

ColorData operator/ (const ColorData& a, float f) {
	return ColorData(a.m_red/f, a.m_green/f, a.m_blue/f, a.m_alpha/f);
}

bool operator== (const ColorData& a, const ColorData& b) {
	return ((a.m_red == b.m_red) && (a.m_green == b.m_green) && (a.m_blue == b.m_blue));
}

bool operator!= (const ColorData& a, const ColorData& b) {
	return ((a.m_red != b.m_red) || (a.m_green != b.m_green) || (a.m_blue != b.m_blue));
}

bool operator< (const ColorData& a, const ColorData& b) {
	return ((a.m_red + a.m_green + a.m_blue) < (b.m_red + b.m_green + b.m_blue));
}

bool operator<= (const ColorData& a, const ColorData& b) {
	return ((a.m_red + a.m_green + a.m_blue) <= (b.m_red + b.m_green + b.m_blue));
}

bool operator> (const ColorData& a, const ColorData& b) {
	return ((a.m_red + a.m_green + a.m_blue) > (b.m_red + b.m_green + b.m_blue));
}

bool operator>= (const ColorData& a, const ColorData& b) {
	return ((a.m_red + a.m_green + a.m_blue) >= (b.m_red + b.m_green + b.m_blue));
}