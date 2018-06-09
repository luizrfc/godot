/*************************************************************************/
/*  microsoft_mr_interface.h                                             */
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

#ifndef MICROSOFT_MR_INTERFACE_H
#define MICROSOFT_MR_INTERFACE_H

#include <..\winrt\WinRTBase.h>;
#include <windows.graphics.holographic.h>;
#include <..\um\HolographicSpaceInterop.h>;

#include <wrl.h>

#include "servers/arvr/arvr_interface.h"
#include "servers/arvr/arvr_positional_tracker.h"

/**
	@author Bastiaan Olij <mux213@gmail.com>

	The Microsoft MR interface is only availble on UWP and caters to MR headsets.
	This may form the basis for Hololens support in due time as well.

	Currently implemented as a module as it heavily relies on Angle.
*/

class MicrosoftMRInterface : public ARVRInterface {
	GDCLASS(MicrosoftMRInterface, ARVRInterface);

private:
	bool initialized;

protected:
	static void _bind_methods();

public:
	// interface
	virtual StringName get_name() const;
	virtual int get_capabilities() const;

	virtual bool is_initialized();
	virtual bool initialize();
	virtual void uninitialize();

	virtual Size2 get_render_targetsize();
	virtual bool is_stereo();
	virtual Transform get_transform_for_eye(ARVRInterface::Eyes p_eye, const Transform &p_cam_transform);
	virtual CameraMatrix get_projection_for_eye(ARVRInterface::Eyes p_eye, real_t p_aspect, real_t p_z_near, real_t p_z_far);
	virtual void commit_for_eye(ARVRInterface::Eyes p_eye, RID p_render_target, const Rect2 &p_screen_rect);

	virtual void process();

	MicrosoftMRInterface();
	~MicrosoftMRInterface();
};

#endif // !MICROSOFT_MR_INTERFACE_H

#endif // MICROSOFT_MR_ENABLED
