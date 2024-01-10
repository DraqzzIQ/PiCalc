/* hw_config.c
Copyright 2021 Carl John Kugler III

Licensed under the Apache License, Version 2.0 (the License); you may not use
this file except in compliance with the License. You may obtain a copy of the
License at

   http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an AS IS BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
*/
#include <hw_config.h>

///
///
#include <ff.h> /* Obtains integer types */
//
#include <diskio.h> /* Declarations of disk functions */

/*
Hardware configuration:

|       | SPI0  | GPIO  | Pin   | SPI       | MicroSD   | Description            |
| ----- | ----  | ----- | ---   | --------  | --------- | ---------------------- |
| MISO  | RX    | 16    | 21    | DO        | DO        | Master In, Slave Out   |
| MOSI  | TX    | 19    | 25    | DI        | DI        | Master Out, Slave In   |
| SCK   | SCK   | 18    | 24    | SCLK      | CLK       | SPI clock              |
| CS0   | CSn   | 17    | 22    | SS or CS  | CS        | Slave (or Chip) Select |
| DET   |       | 1     | 2     |           | CD        | Card Detect            |
| GND   |       |       | 18,23 |           | GND       | Ground                 |
| 3v3   |       |       | 36    |           | 3v3       | 3.3 volt power         |

*/

// Hardware Configuration of SPI
static spi_t spi = {
	.hw_inst = spi0, // SPI component
	.miso_gpio = 16, // GPIO number (not Pico pin number)
	.mosi_gpio = 19,
	.sck_gpio = 18,
	// .baud_rate = 1000 * 1000
	.baud_rate = 12500 * 1000
	// .baud_rate = 25 * 1000 * 1000 // Actual frequency: 20833333.
};

// Hardware Configuration of the SD Card
static sd_card_t sd_card = {
	.pcName = "0:",         // Name used to mount device
	.spi = &spi,            // Pointer to the SPI driving this card
	.ss_gpio = 17,          // The SPI slave select GPIO for this SD card
	.use_card_detect = true,
	.card_detect_gpio = 1,  // Card detect
	.card_detected_true = 1 // What the GPIO read returns when a card is present.
};

size_t sd_get_num()
{
	return 1;
}
sd_card_t* sd_get_by_num(size_t num)
{
	return &sd_card;
}
size_t spi_get_num()
{
	return 1;
}
spi_t* spi_get_by_num(size_t num)
{
	return &spi;
}