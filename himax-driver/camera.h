/*
 * camera.h
 *
 *  Created on: Oct 24, 2017
 *      Author: cjoseph
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#define HM01B0ADDR              0x24    /* camera I2C address */
#define SW_RESET                0x103   // software reset (write only)
#define MODE_SELECT             0x0100  // sensor mode selection
#define BIT_CONTROL             0x3059  // interface bit width control
#define QVGA_WIN_EN             0x3010  // QVGA enable
#define READOUT_X               0x0383  // Readout for x [1:0], 1=full, 3=Horizontal BIN2 timing enable
#define READOUT_Y               0x0387  // Readout for y [1:0], 1=full, 3=Veritcal BIN2 timing enable
#define BINNING_MODE            0x0390  // [0] Vertical Binning, [1] Horizontal Binning, [3] enable v and h binning
#define LINE_LENGTH_PCK_H       0x0342  // line_length higher, 16_uint (0x0342:0x0343 controls line length)
#define LINE_LENGTH_PCK_L       0x0343  // line_length lower, 16_uint
#define FRAME_LENGTH_LINES_H    0x0340  // frame_length_lines higher, 16-bit UINT (0x0340:0x0341 controls frame length
#define FRAME_LENGTH_LINES_L    0x0341  // frame_length_lines lower, 16-bit UINT
#define TEST_PATTERN_MODE       0x0601  // [0]: test pattern enable [4]:mode selection (0=color bar, 1=walking 1's)
#define OSC_CLK_DIV             0x3060  // Clock divider, gating and LDO control

#endif /* CAMERA_H_ */
