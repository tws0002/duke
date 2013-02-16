/*
 * Player.cpp
 *
 *  Created on: Dec 27, 2012
 *      Author: Guillaume Chatelet
 */

#include "Player.h"
#include <duke/cmdline/CmdLineParameters.h>

namespace duke {

Player::Player(const CmdLineParameters &parameters) :
		m_TextureCache(parameters) {
}

void Player::load(const Timeline& timeline, const FrameDuration &duration) {
	m_TextureCache.load(timeline);
	m_TimelineRange = timeline.getRange();
	const bool empty = m_TimelineRange == Range::EMPTY;
	if (empty) {
		m_FirstFrameTime = m_LastFrameTime = 0;
	} else {
		m_FirstFrameTime = frameToTime(m_TimelineRange.first, getFrameDuration());
		m_LastFrameTime = frameToTime(m_TimelineRange.last, getFrameDuration());
	}
	m_FrameDuration = duration;
	cue(empty ? 0 : m_TimelineRange.first);
}

void Player::setPlaybackTime(const Time time) {
	m_PlaybackTime = time;
}

void Player::offsetPlaybackTime(const Time time) {
	const Time offset = time * m_PlaybackSpeed;
	if (m_PlaybackMode == CONTINUE) {
		m_PlaybackTime += offset;
		return;
	}
	if (m_TimelineRange == Range::EMPTY || offset == 0)
		return;
	const bool forward = offset > 0;
	auto overshoot = forward ? (m_PlaybackTime + offset) - m_LastFrameTime : m_FirstFrameTime - (m_PlaybackTime + offset);
	if (overshoot <= 0) {
		m_PlaybackTime += offset;
		return;
	}
	switch (m_PlaybackMode) {
	case STOP:
		m_PlaybackTime = forward ? m_LastFrameTime : m_FirstFrameTime;
		m_PlaybackSpeed = 0;
		break;
	case LOOP:
		overshoot -= getFrameDuration();
		if (overshoot > (m_LastFrameTime - m_FirstFrameTime))
			return;
		m_PlaybackTime = forward ? m_FirstFrameTime + overshoot : m_LastFrameTime - overshoot;
		break;
	default:
		throw std::logic_error("Not yet implemented");
	}
}

void Player::setPlaybackSpeed(int speed) {
	m_PlaybackSpeed = speed;
}

void Player::setPlaybackMode(const Mode mode) {
	m_PlaybackMode = mode;
}

void Player::stop() {
	setPlaybackSpeed(0);
}

void Player::cue(uint32_t frame) {
	m_PlaybackTime = m_FrameDuration * frame;
	stop();
}

FrameIndex Player::getCurrentFrame() const {
	return m_PlaybackTime / m_FrameDuration;
}

Time Player::getPlaybackTime() const {
	return m_PlaybackTime;
}

FrameDuration Player::getFrameDuration() const {
	return m_FrameDuration;
}

int Player::getPlaybackSpeed() const {
	return m_PlaybackSpeed;
}

Player::Mode Player::getPlaybackMode() const {
	return m_PlaybackMode;
}

const Timeline& Player::getTimeline() const {
	return m_TextureCache.getTimeline();
}

LoadedTextureCache& Player::getTextureCache() {
	return m_TextureCache;
}

}  // namespace duke
