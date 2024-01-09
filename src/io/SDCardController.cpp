#include "io/SDCardController.h"
#include "SDCardController.h"
#ifdef PICO

SDCardController::SDCardController()
{
}

bool SDCardController::save_file(std::string dir, std::string filename, const std::vector<uint8_t>& bytes)
{
	if (!ready()) return false;
	FIL file;
	FRESULT fr = f_open(&file, (dir + filename).c_str(), FA_WRITE | FA_CREATE_ALWAYS);
	if (FR_OK != fr) {
		sdt::cout << "f_open error: " << FRESULT_str(fr) << " (" << fr << ")" << std::endl;
		return false;
	}
}

void SDCardController::read_file(std::string dir, std::string filename, std::vector<uint8_t>& bytes)
{
	if (!ready()) return false;
}


void SDCardController::init()
{
	_sd_card = &SDCardHWConfig::sd_card;

	if (_sd_card->use_card_detect()) {
		// Set up an interrupt on Card Detect to detect removal of the card when it happens:
		gpio_set_irq_enabled_with_callback(
			_sd_card->card_detect_gpio,
			GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,
			true,
			&card_detect_callback);
	}

	if (sd_card_detect(_sd_card)) {
		FRESULT fr = f_mount(&_sd_card->fatfs, _sd_card->pcName, 1);
		if (FR_OK != fr) sdt::cout << "f_mount error: " << FRESULT_str(fr) << " (" << fr << ")" << std::endl;
		else std::cout << "Mounted " << _sd_card->pcName << std::endl;
	}
}
bool SDCardController::ready()
{
	return _sd_card->mounted;
}

void SDCardController::card_detect_callback(uint gpio, uint32_t events)
{
	static bool busy;
	if (busy) return; // Avoid switch bounce
	busy = true;
	for (size_t i = 0; i < sd_get_num(); ++i) {
		sd_card_t* _sd_card = sd_get_by_num(i);
		if (_sd_card->card_detect_gpio == gpio) {
			if (_sd_card->mounted) {
				std::cout << "Card Detect Interrupt: unmounting " << _sd_card->pcName << std::endl;
				FRESULT fr = f_unmount(_sd_card->pcName);
				if (FR_OK == fr) {
					_sd_card->mounted = false;
				} else {
					std::cout << "f_unmount error: " << FRESULT_str(fr) << " (" fr << ")" << std::endl;
				}
			}
			_sd_card->m_Status |= STA_NOINIT; // in case medium is removed
			sd_card_detect(_sd_card);
		}
	}
	busy = false;
}

#endif