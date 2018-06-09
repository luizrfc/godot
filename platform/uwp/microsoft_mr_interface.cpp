/*************************************************************************/
/*  microsoft_mr_interface.cpp                                           */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2018 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2018 Godot Engine contributors (cf. AUTHORS.md)    */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

// Only include if we're building for Microsoft MR
#ifdef MICROSOFT_MR_ENABLED

#include "microsoft_mr_interface.h"
#include "servers/visual/visual_server_global.h"

StringName MicrosoftMRInterface::get_name() const {
	return "Microsoft MR";
}

int MicrosoftMRInterface::get_capabilities() const {
	return ARVRInterface::ARVR_STEREO;
}

void MicrosoftMRInterface::_bind_methods() {
	// no additional methods at this time
}

bool MicrosoftMRInterface::is_stereo() {
	// needs stereo...
	return true;
}

bool MicrosoftMRInterface::is_initialized() {
	return (initialized);
}

bool MicrosoftMRInterface::initialize() {
	ARVRServer *arvr_server = ARVRServer::get_singleton();
	ERR_FAIL_NULL_V(arvr_server, false);

	if (!initialized) {
		// This is just for compatibility with other ARVR drivers. 
		// Microsoft MR is always on as its part of the platform.
		initialized = true;
	}

	return true;
}

void MicrosoftMRInterface::uninitialize() {
	if (initialized) {
		ARVRServer *arvr_server = ARVRServer::get_singleton();
		if (arvr_server != NULL) {
			// no longer our primary interface
			arvr_server->clear_primary_interface_if(this);
		}

		initialized = false;
	}
}

Size2 MicrosoftMRInterface::get_render_targetsize() {
	_THREAD_SAFE_METHOD_

	// need to change this
	Size2 target_size;
	target_size.x = 500;
	target_size.y = 500;

	return target_size;
}

Transform MicrosoftMRInterface::get_transform_for_eye(ARVRInterface::Eyes p_eye, const Transform &p_cam_transform) {
	_THREAD_SAFE_METHOD_

	Transform transform_for_eye;

	ARVRServer *arvr_server = ARVRServer::get_singleton();
	ERR_FAIL_NULL_V(arvr_server, transform_for_eye);

	if (initialized) {
		float world_scale = arvr_server->get_world_scale();

		// need to change this to what we're getting from holographic API
		if (p_eye == ARVRInterface::EYE_LEFT) {
			transform_for_eye.origin.x = -(6.5 * 0.01 * 0.5 * world_scale);
		} else if (p_eye == ARVRInterface::EYE_RIGHT) {
			transform_for_eye.origin.x = 6.5 * 0.01 * 0.5 * world_scale;
		} else {
			// for mono we don't reposition, we want our center position.
		}

		// need to change this to what we get from the holographic API
		Transform hmd_transform;
		// hmd_transform.basis = orientation;
		hmd_transform.origin = Vector3(0.0, 1.8 * world_scale, 0.0);

		transform_for_eye = p_cam_transform * (arvr_server->get_reference_frame()) * hmd_transform * transform_for_eye;
	} else {
		// huh? well just return what we got....
		transform_for_eye = p_cam_transform;
	}

	return transform_for_eye;
}

CameraMatrix MicrosoftMRInterface::get_projection_for_eye(ARVRInterface::Eyes p_eye, real_t p_aspect, real_t p_z_near, real_t p_z_far) {
	_THREAD_SAFE_METHOD_

	CameraMatrix eye;

	// change this
	if (p_eye == ARVRInterface::EYE_MONO) {
		eye.set_perspective(60.0, p_aspect, p_z_near, p_z_far, false);
	} else {
		eye.set_perspective(60.0, p_aspect, p_z_near, p_z_far, false);
//		eye.set_for_hmd(p_eye == ARVRInterface::EYE_LEFT ? 1 : 2, p_aspect, intraocular_dist, display_width, display_to_lens, oversample, p_z_near, p_z_far);
	}

	return eye;
}

void MicrosoftMRInterface::commit_for_eye(ARVRInterface::Eyes p_eye, RID p_render_target, const Rect2 &p_screen_rect) {
	_THREAD_SAFE_METHOD_

	// We must have a valid render target
	ERR_FAIL_COND(!p_render_target.is_valid());

	// Because we are rendering to our device we must use our main viewport!
	ERR_FAIL_COND(p_screen_rect == Rect2());

	// for now just output to screen, we'll probably change this later on
	if (p_eye == 0) {
		// get the size of our screen
		Rect2 screen_rect = p_screen_rect;

		//		screen_rect.position.x += screen_rect.size.x;
		//		screen_rect.size.x = -screen_rect.size.x;
		//		screen_rect.position.y += screen_rect.size.y;
		//		screen_rect.size.y = -screen_rect.size.y;

		VSG::rasterizer->set_current_render_target(RID());
		VSG::rasterizer->blit_render_target_to_screen(p_render_target, screen_rect, 0);
	}
}

void MicrosoftMRInterface::process() {
	_THREAD_SAFE_METHOD_

	if (initialized) {
		// implement...
	}
}

MicrosoftMRInterface::MicrosoftMRInterface() {
	initialized = false;

}

MicrosoftMRInterface::~MicrosoftMRInterface() {
	// and make sure we cleanup if we haven't already
	if (is_initialized()) {
		uninitialize();
	}
}

#endif // MICROSOFT_MR_ENABLED
