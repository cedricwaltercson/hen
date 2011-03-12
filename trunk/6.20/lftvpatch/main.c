#include <stdio.h>

#include "pspsdk.h"
#include "pspkernel.h"
#include "psptypes.h"

#include "systemctrl.h"
#include "kubridge.h"

#include "log.h"

#define MAKE_CALL(__f) \
	(((((unsigned int)__f) >> 2) & 0x03FFFFFF) | 0x0C000000)

#define MAKE_BREAK(n) ((((u32)n << 6) & 0x03FFFFC0) | 0x0000000D)

PSP_MODULE_INFO("lftv_patch_module", 0, 1, 0);



static u32
get_text_addr(u32 offset)
{
	static u32 g_text_addr = 0;

	if (g_text_addr == 0) {
		g_text_addr = sctrlModuleTextAddr("sceVshLftvMw_Module");
		if (g_text_addr == 0)
			return 0;
		logstr("text_addr:");
		logint(g_text_addr);
	}

	return g_text_addr + offset;
}

#define load_text_addr(__func, __offset, __ret) do {\
	if ((__func) == NULL) {\
		(__func) = (void *) get_text_addr((__offset));\
		if ((__func) == NULL)\
			return (__ret);\
	}\
} while(0)

#if 0
u32
send_request_patched(u32 a0, u32 a1, u32 a2, char *a3, char *t0, char *t1, char *t2, u32 t3)
{
	static u32 (*send_request_original) (u32, u32, u32, char *, char *, char *, char *, u32) = NULL;
	u32 ret = -1;

	logint(a0);
	logint(a1);
	logint(a2);
	logstr(a3);
	logstr(t0);
	logstr(t1);
	logstr(t2);
	logint(t3);

	load_text_addr(send_request_original, 0x000159C8, ret);

	ret = send_request_original(a0, a1, a2, a3, t0, t1, t2, t3);
	logstr("request:");
	logint(ret);

	return ret;
}

u32
send_message_patched(u32 a0, u32 a1)
{
	static u32 (*send_message_original) (u32, u32) = NULL;

	u32 ret = -5;

	logint(a0);
	logint(a1);

	load_text_addr(send_message_original, 0x00016CB8, ret);

	ret = send_message_original(a0, a1);
	logstr("message:");
	logint(ret);

	return ret;
}

u32
parse_resp_patched(u32 a0, u32 a1, u32 a2)
{
	static u32 (*parse_resp_original) (u32, u32, u32) = NULL;

	u32 ret = -5;

	logint(a0);
	logint(a1);
	logint(a2);

	load_text_addr(parse_resp_original, 0x00016970, ret);

	ret = parse_resp_original(a0, a1, a2);
	logstr("parse resp:");
	logint(ret);

	return ret;
}

u32
send_message_http_patched(u32 a0, u32 a1, u32 a2)
{
	static u32 (*send_message_http_original) (u32, u32, u32) = NULL;
	u32 ret = 5;

	load_text_addr(send_message_http_original, 0x000163F8, ret);

	logint(_lb(a0 + 0x20));

	ret = send_message_http_original(a0, a1, a2);
	logstr("send_message_http:");
	logint(ret);

	return ret;
}

u32
sub_0001A58C_patched(u32 a0, u32 a1, u32 a2)
{
	static u32 (*sub_0001A58C_original) (u32, u32, u32) = NULL;
	u32 ret = -1;

	load_text_addr(sub_0001A58C_original, 0x0001A58C, ret);
	ret = sub_0001A58C_original(a0, a1, a2);
	logstr("sub_0001A58C:");
	logint(ret);

	return ret;
}
#endif

#if 0
u32
parse_desc_resp(u32 a0, u32 a1)
{
	static u32 (*func) (u32, u32) = NULL;
	u32 ret = 1;

	load_text_addr(func, 0x0000A44C, ret);
	ret = func(a0, a1);
	logstr("0x0000A44C:");
	logint(ret);

	return ret;
}

u32
parse_rtsp_resp(u32 a0, u32 a1, u32 a2)
{
	static u32 (*func) (u32, u32, u32) = NULL;
	u32 ret = 1;

	load_text_addr(func, 0x00009FA8, ret);
	ret = func(a0, a1, a2);
	logstr("0x00009FA8:");
	logint(ret);

	return ret;
}

u32
parse_rtsp_resp2(u32 a0, u32 a1)
{
	static u32 (*func) (u32, u32) = NULL;
	u32 ret = 1;

	load_text_addr(func, 0x00009ED0, ret);
	ret = func(a0, a1);
	logstr("0x00009ED0:");
	logint(ret);

	return ret;
}

u32
parse_rtsp_resp3(u32 a0, u32 a1)
{
	static u32 (*func) (u32, u32) = NULL;
	u32 ret = 1;

	load_text_addr(func, 0x000031A0, ret);
	ret = func(a0, a1);
	logstr("0x000031A0:");
	logint(ret);

	return ret;
}

u32
send_rtsp_req(u32 a0, u32 a1, u32 a2, u32 a3)
{
	static u32 (*func) (u32, u32, u32, u32) = NULL;
	u32 ret = 1;

	load_text_addr(func, 0x00002F94, ret);
	ret = func(a0, a1, a2, a3);
	logstr("0x00002F94:");
	logint(ret);

	return ret;
}

u32
sub_00004D54(u32 a0, u32 a1, u32 a2)
{
	static u32 (*func) (u32, u32, u32) = NULL;
	u32 ret = 1;

	load_text_addr(func, 0x00004D54, ret);
	ret = func(a0, a1, a2);
	logstr("0x00004D54:");
	logint(ret);

	return ret;
}

u32
sub_000054C8(u32 a0, u32 a1)
{
	static u32 (*func) (u32, u32) = NULL;
	u32 ret = 1;

	load_text_addr(func, 0x000054C8, ret);
	ret = func(a0, a1);
	logstr("0x000054C8:");
	logint(ret);

	return ret;
}

u32
sub_0000543C(u32 a0, u32 a1)
{
	static u32 (*func) (u32, u32) = NULL;
	u32 ret = 1;

	load_text_addr(func, 0x0000543C, ret);
	ret = func(a0, a1);
	logstr("0x0000543C:");
	logint(ret);

	return ret;
}
#endif

u32
sub_00005758(u32 a0)
{
	static u32 (*func) (u32) = NULL;
	u32 ret = 1;

	load_text_addr(func, 0x00005758, ret);
	logstr("sub_00005758:");
	logint(_lw(0x18 + _lw(a0)));
	ret = func(a0);
	logstr("0x00005758:");
	logint(ret);

	return ret;
}

u32
sub_00014C34(u32 a0, u32 a1, u32 a2, u32 a3)
{
	static u32 (*func) (u32, u32, u32, u32) = NULL;
	u32 ret = 0;

	load_text_addr(func, 0x00014C34, ret);

	logstr("sub_00014C34:");
	logint(a0);
	logint(_lb(a0 + 0x18));
	logint(_lb(a0 + 0x19));
	logint(_lw(a0));
	logint(_lw(0x20 + _lw(a0)));
	logint(_lw(0x24 + _lw(a0)));
	logint(_lw(0x4 + _lw(a0)));
	logint(_lw(0x8 + _lw(_lw(0x1C + a0))));
	logint(_lw(0x4 + _lw(_lw(0x20 + a0))));
	ret = func(a0, a1, a2, a3);
	logstr("0x00014C34:");
	logint(ret);
	logint(_lw(a3));
	logint(_lw(a1));

	return ret;
}

u32
sub_00005550(u32 a0, u32 a1)
{
	static u32 (*func) (u32, u32)= NULL;
	u32 ret = 0x15;

	load_text_addr(func, 0x00005550, ret);
	logstr("sub_00005550:");
	logint(a0);
	logint(a1);
	ret = func(a0, a1);
	logstr("0x00005550:");
	logint(ret);

	return ret;
}

u32
sub_0000604C(u32 a0)
{
	static u32 (*func) (u32) = NULL;
	u32 ret = 405;

	load_text_addr(func, 0x0000604C, ret);
	logstr("sub_0000604C:");
	logint(a0);
	ret = func(a0);
	logstr("0x0000604C:");
	logint(ret);

	return ret;
}


int
module_start(SceSize args, void* argp)
{
	sctrlPatchModule("sceVshLftvMw_Module", 0x24020000, 0x00033DA0); /* bypassing registration check */

	sctrlPatchModule("sceVshLftvMw_Module", MAKE_CALL(sub_0000604C), 0x00005570);
	sctrlPatchModule("sceVshLftvMw_Module", MAKE_CALL(sub_00014C34), 0x0000577C);
	sctrlPatchModule("sceVshLftvMw_Module", MAKE_CALL(sub_00005758), 0x00004EA8);
	sctrlPatchModule("sceVshLftvMw_Module", (u32) sub_00005550, 0x000591F8);
#if 0
	sctrlPatchModule("sceVshLftvMw_Module", MAKE_CALL(sub_000054C8), 0x00004E98);
	sctrlPatchModule("sceVshLftvMw_Module", MAKE_CALL(sub_0000543C), 0x00004EC0);
	//sctrlPatchModule("sceVshLftvMw_Module", 0x0, 0x00002D7C);
	sctrlPatchModule("sceVshLftvMw_Module", (u32) sub_00004D54, 0x000591E8);
	sctrlPatchModule("sceVshLftvMw_Module", MAKE_CALL(send_rtsp_req), 0x00002D14);
	sctrlPatchModule("sceVshLftvMw_Module", MAKE_CALL(parse_rtsp_resp3), 0x00002D84);
	sctrlPatchModule("sceVshLftvMw_Module", MAKE_CALL(parse_rtsp_resp2), 0x00003208);
	sctrlPatchModule("sceVshLftvMw_Module", MAKE_CALL(parse_rtsp_resp), 0x00009F20);
	sctrlPatchModule("sceVshLftvMw_Module", MAKE_CALL(parse_desc_resp), 0x0000A10C);
#endif

#if 0
	sctrlPatchModule("sceVshLftvMw_Module", MAKE_CALL(sub_0001A58C_patched), 0x00016BC0);
	sctrlPatchModule("sceVshLftvMw_Module", MAKE_CALL(send_message_http_patched), 0x00016D6C);
	sctrlPatchModule("sceVshLftvMw_Module", MAKE_CALL(parse_resp_patched), 0x000165D8);
	sctrlPatchModule("sceVshLftvMw_Module", MAKE_CALL(parse_resp_patched), 0x00016DA8);
	sctrlPatchModule("sceVshLftvMw_Module", MAKE_CALL(send_message_patched), 0x00015D60);
	sctrlPatchModule("sceVshLftvMw_Module", MAKE_CALL(send_message_patched), 0x00015D84);
	sctrlPatchModule("sceVshLftvMw_Module", MAKE_CALL(send_request_patched), 0x0000292C);
#endif

	return 0;
}

int
module_stop(SceSize args, void* argp)
{
	return 0;
}
