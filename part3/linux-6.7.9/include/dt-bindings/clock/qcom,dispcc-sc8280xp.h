/* SPDX-License-Identifier: (GPL-2.0-only OR BSD-2-Clause) */
/*
 * Copyright (c) 2021, The Linux Foundation. All rights reserved.
 */

#ifndef _DT_BINDINGS_CLK_QCOM_DISP_CC_SC8280XP_H
#define _DT_BINDINGS_CLK_QCOM_DISP_CC_SC8280XP_H

/* DISPCC clocks */
#define DISP_CC_PLL0					0
#define DISP_CC_PLL1					1
#define DISP_CC_PLL1_OUT_EVEN				2
#define DISP_CC_PLL2					3
#define DISP_CC_MDSS_AHB1_CLK				4
#define DISP_CC_MDSS_AHB_CLK				5
#define DISP_CC_MDSS_AHB_CLK_SRC			6
#define DISP_CC_MDSS_BYTE0_CLK				7
#define DISP_CC_MDSS_BYTE0_CLK_SRC			8
#define DISP_CC_MDSS_BYTE0_DIV_CLK_SRC			9
#define DISP_CC_MDSS_BYTE0_INTF_CLK			10
#define DISP_CC_MDSS_BYTE1_CLK				11
#define DISP_CC_MDSS_BYTE1_CLK_SRC			12
#define DISP_CC_MDSS_BYTE1_DIV_CLK_SRC			13
#define DISP_CC_MDSS_BYTE1_INTF_CLK			14
#define DISP_CC_MDSS_DPTX0_AUX_CLK			15
#define DISP_CC_MDSS_DPTX0_AUX_CLK_SRC			16
#define DISP_CC_MDSS_DPTX0_LINK_CLK			17
#define DISP_CC_MDSS_DPTX0_LINK_CLK_SRC			18
#define DISP_CC_MDSS_DPTX0_LINK_DIV_CLK_SRC		19
#define DISP_CC_MDSS_DPTX0_LINK_INTF_CLK		20
#define DISP_CC_MDSS_DPTX0_PIXEL0_CLK			21
#define DISP_CC_MDSS_DPTX0_PIXEL0_CLK_SRC		22
#define DISP_CC_MDSS_DPTX0_PIXEL1_CLK			23
#define DISP_CC_MDSS_DPTX0_PIXEL1_CLK_SRC		24
#define DISP_CC_MDSS_DPTX0_USB_ROUTER_LINK_INTF_CLK	25
#define DISP_CC_MDSS_DPTX1_AUX_CLK			26
#define DISP_CC_MDSS_DPTX1_AUX_CLK_SRC			27
#define DISP_CC_MDSS_DPTX1_LINK_CLK			28
#define DISP_CC_MDSS_DPTX1_LINK_CLK_SRC			29
#define DISP_CC_MDSS_DPTX1_LINK_DIV_CLK_SRC		30
#define DISP_CC_MDSS_DPTX1_LINK_INTF_CLK		31
#define DISP_CC_MDSS_DPTX1_PIXEL0_CLK			32
#define DISP_CC_MDSS_DPTX1_PIXEL0_CLK_SRC		33
#define DISP_CC_MDSS_DPTX1_PIXEL1_CLK			34
#define DISP_CC_MDSS_DPTX1_PIXEL1_CLK_SRC		35
#define DISP_CC_MDSS_DPTX1_USB_ROUTER_LINK_INTF_CLK	36
#define DISP_CC_MDSS_DPTX2_AUX_CLK			37
#define DISP_CC_MDSS_DPTX2_AUX_CLK_SRC			38
#define DISP_CC_MDSS_DPTX2_LINK_CLK			39
#define DISP_CC_MDSS_DPTX2_LINK_CLK_SRC			40
#define DISP_CC_MDSS_DPTX2_LINK_DIV_CLK_SRC		41
#define DISP_CC_MDSS_DPTX2_LINK_INTF_CLK		42
#define DISP_CC_MDSS_DPTX2_PIXEL0_CLK			43
#define DISP_CC_MDSS_DPTX2_PIXEL0_CLK_SRC		44
#define DISP_CC_MDSS_DPTX2_PIXEL1_CLK			45
#define DISP_CC_MDSS_DPTX2_PIXEL1_CLK_SRC		46
#define DISP_CC_MDSS_DPTX3_AUX_CLK			47
#define DISP_CC_MDSS_DPTX3_AUX_CLK_SRC			48
#define DISP_CC_MDSS_DPTX3_LINK_CLK			49
#define DISP_CC_MDSS_DPTX3_LINK_CLK_SRC			50
#define DISP_CC_MDSS_DPTX3_LINK_DIV_CLK_SRC		51
#define DISP_CC_MDSS_DPTX3_LINK_INTF_CLK		52
#define DISP_CC_MDSS_DPTX3_PIXEL0_CLK			53
#define DISP_CC_MDSS_DPTX3_PIXEL0_CLK_SRC		54
#define DISP_CC_MDSS_ESC0_CLK				55
#define DISP_CC_MDSS_ESC0_CLK_SRC			56
#define DISP_CC_MDSS_ESC1_CLK				57
#define DISP_CC_MDSS_ESC1_CLK_SRC			58
#define DISP_CC_MDSS_MDP1_CLK				59
#define DISP_CC_MDSS_MDP_CLK				60
#define DISP_CC_MDSS_MDP_CLK_SRC			61
#define DISP_CC_MDSS_MDP_LUT1_CLK			62
#define DISP_CC_MDSS_MDP_LUT_CLK			63
#define DISP_CC_MDSS_NON_GDSC_AHB_CLK			64
#define DISP_CC_MDSS_PCLK0_CLK				65
#define DISP_CC_MDSS_PCLK0_CLK_SRC			66
#define DISP_CC_MDSS_PCLK1_CLK				67
#define DISP_CC_MDSS_PCLK1_CLK_SRC			68
#define DISP_CC_MDSS_ROT1_CLK				69
#define DISP_CC_MDSS_ROT_CLK				70
#define DISP_CC_MDSS_ROT_CLK_SRC			71
#define DISP_CC_MDSS_RSCC_AHB_CLK			72
#define DISP_CC_MDSS_RSCC_VSYNC_CLK			73
#define DISP_CC_MDSS_VSYNC1_CLK				74
#define DISP_CC_MDSS_VSYNC_CLK				75
#define DISP_CC_MDSS_VSYNC_CLK_SRC			76
#define DISP_CC_SLEEP_CLK				77
#define DISP_CC_SLEEP_CLK_SRC				78
#define DISP_CC_XO_CLK					79
#define DISP_CC_XO_CLK_SRC				80

/* DISPCC resets */
#define DISP_CC_MDSS_CORE_BCR				0
#define DISP_CC_MDSS_RSCC_BCR				1

/* DISPCC GDSCs */
#define MDSS_GDSC					0
#define MDSS_INT2_GDSC					1

#endif
