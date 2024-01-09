#pragma once
#include <assert.h>
#include <string.h>
//
#include <ff.h> /* Obtains integer types */
//
#include <diskio.h> /* Declarations of disk functions */
//
#include <sd_card.h> /* Declarations of sd_card type */

class SDCardHWConfig
{
	public:
	static sd_card_t sd_card;
	static spi_t spi;
};